#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <stdio.h>

TaskHandle_t TaskHandle1;
TaskHandle_t TaskHandle2;
TaskHandle_t TaskHandle3;

TimerHandle_t OneShotTimer;

void OneShotCallback(TimerHandle_t xTimer)
{
    printf("One-shot timer callback executed after 10000ms\n");
}

void Task1(void *data)
{
    while (1)
    {
        printf("Task T1 executed\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void Task2(void *data)
{
    while (1)
    {
        printf("Task T2 executed\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void Task3(void *data)
{
    while (1)
    {
        printf("Task T3 executed\n");
        vTaskDelay(pdMS_TO_TICKS(500float.c
        0));
        printf("Task T3 starting the one-shot timer\n");
        xTimerStart(OneShotTimer, 0);
    }
}

void app_main(void)
{
    OneShotTimer = xTimerCreate("OneShotTimer", pdMS_TO_TICKS(10000), pdFALSE, NULL, OneShotCallback);
    if (OneShotTimer == NULL)
    {
        printf("Failed to create the one-shot timer\n");
        return;
    }
    
    xTaskCreate(Task1, "Task1", 2048, NULL, 5, &TaskHandle1);
    xTaskCreate(Task2, "Task2", 2048, NULL, 6, &TaskHandle2);
    xTaskCreate(Task3, "Task3", 2048, NULL, 7, &TaskHandle3);
}
