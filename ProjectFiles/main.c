#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"




static void printer_task(void* pvParameters)
{
    while (true)
    {
        printf("Task %d is currently running\n", (int)pvParameters);
        vTaskDelay(100);
    }
}

int main(void)
{
    stdio_init_all();


    xTaskCreate(printer_task, "Task 1", 256, (void*)1, 1, NULL);
    xTaskCreate(printer_task, "Task 2", 256, (void*)2, 2, NULL);
    vTaskStartScheduler();

    while(1) {};
}
