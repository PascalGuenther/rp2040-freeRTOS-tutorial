#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"


static void led_task(void * data)
{
    (void)data;
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while(1)
    {
        gpio_put(LED_PIN, 1);
        vTaskDelay(100);
        gpio_put(LED_PIN, 0);
        vTaskDelay(100);
    }
}

int main(void)
{
    stdio_init_all();
    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1) {};
}
