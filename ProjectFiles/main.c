#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "semphr.h"

static SemaphoreHandle_t mutex;

static void task1(void* pvParameters)
{
    (void)pvParameters;
    char ch = '1';
    while (true)
    {
        if (xSemaphoreTake(mutex, 0) == pdTRUE)
        {
            for (int i = 0; i < 9; i++)
            {
                putchar(ch);
            }
            puts("");
            xSemaphoreGive(mutex);
        }
    }
}

static void task2(void* pvParameters)
{
    (void)pvParameters;
    char ch = '2';
    while (true)
    {
        if (xSemaphoreTake(mutex, 0) == pdTRUE)
        {
            for (int i = 0; i < 9; i++)
            {
                putchar(ch);
            }
            puts("");
            xSemaphoreGive(mutex);
        }
    }
}


int main(void)
{
    stdio_init_all();

    mutex = xSemaphoreCreateMutex();

    xTaskCreate(task1, "Task 1", 256, NULL, 1, NULL);
    xTaskCreate(task2, "Task 2", 256, NULL, 1, NULL);

    vTaskStartScheduler();

    while(1) {};
}
