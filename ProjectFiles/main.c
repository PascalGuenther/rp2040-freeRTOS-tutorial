#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <queue.h>
#include "pico/stdlib.h"


static QueueHandle_t xQueue = NULL;


static void led_task(void *pvParameters)
{
    (void)pvParameters;
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    uint uIValueToSend = 0;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while(1)
    {
        gpio_put(LED_PIN, 1);
        uIValueToSend = 1;
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(100);

        uIValueToSend = 0;
        gpio_put(LED_PIN, 0);
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(100);
    }
}

static void usb_task(void *pvParameters)
{
    (void)pvParameters;
    uint uIReceivedValue;

    while(1)
    {
        xQueueReceive(xQueue, &uIReceivedValue, portMAX_DELAY);

        switch (uIReceivedValue)
        {
        case 1:
            printf("LED is ON!\n");
            break;
        case 0:
            printf("LED is OFF!\n");
            break;
        
        default:
            break;
        }
    }
}

int main(void)
{
    stdio_init_all();

    xQueue = xQueueCreate(1, sizeof(uint));

    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    xTaskCreate(usb_task, "USB_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1) {};
}
