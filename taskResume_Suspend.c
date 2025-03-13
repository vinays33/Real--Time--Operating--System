#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle;
TaskHandle_t task2_handle;
TaskHandle_t task3_handle;
TaskHandle_t task4_handle;

void task1(void *data)
{
    printf("task1: Started\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("task1: Resuming task2\n");
    vTaskResume(task2_handle);
    printf("task1: Resuming task3\n");
    vTaskResume(task3_handle);
    printf("task1: Resuming task4\n");
    vTaskResume(task4_handle);
    printf("task1: Deleting itself\n");
    vTaskDelete(task1_handle);
}

void task2(void *data)
{
    printf("task2: Started\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("task2: Deleting itself\n");
    vTaskDelete(NULL);
}

void task3(void *data)
{
    printf("task3: Started\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("task3: Deleting itself\n");
    vTaskDelete(NULL);
}

void task4(void *data)
{
    printf("task4: Started\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("task4: Suspending task2 and task3\n");
    vTaskSuspend(task2_handle);
    vTaskSuspend(task3_handle);
    printf("task4: Suspending itself\n");
    vTaskSuspend(NULL);
    printf("task4: Deleting itself\n");
    vTaskDelete(task4_handle);
}

void app_main()
{
    BaseType_t res;
    printf("Starting task suspend/resume demo\n");
    res = xTaskCreate(task1, "TASK1", 2048, NULL, 1, &task1_handle);
    res = xTaskCreate(task2, "TASK2", 2048, NULL, 2, &task2_handle);
    res = xTaskCreate(task3, "TASK3", 2048, NULL, 3, &task3_handle);
    res = xTaskCreate(task4, "TASK4", 2048, NULL, 4, &task4_handle);
}
