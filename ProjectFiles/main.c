#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "semphr.h"

static SemaphoreHandle_t count;

static void led_task(void* pvParameters)
{
    (void)pvParameters;
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true)
    {
        if (xSemaphoreTake(count, 10u) == pdTRUE)
        {
            gpio_put(LED_PIN, true);
            vTaskDelay(100);
        }
        else
        {
            gpio_put(LED_PIN, false);
            vTaskDelay(1);
        }
    }
}

static void button_task(void* pvParameters)
{
    (void)pvParameters;
    // use polling instead of IRQs for the sake of simplicity
    const uint BUTTON_PIN = 20;
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_OUT);

    while (true)
    {
        if (gpio_get(BUTTON_PIN) != 0)
        {
            xSemaphoreGive(count);
            // debouncing
            vTaskDelay(20);
        }
        else {
            vTaskDelay(1);
        }
    }
}


int main(void)
{
    stdio_init_all();

    count = xSemaphoreCreateCounting(5, 0);

    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    xTaskCreate(button_task, "Button Task", 256, NULL, 1, NULL);

    vTaskStartScheduler();

    while(1) {};
}
