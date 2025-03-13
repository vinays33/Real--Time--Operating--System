#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stdio.h>

TaskHandle_t TaskHandle1;
TaskHandle_t TaskHandle2;
TaskHandle_t TaskHandle3;
TaskHandle_t TaskHandle4;
TaskHandle_t TaskHandle5;

QueueHandle_t MessageQueue;

void Task1(void *data)
{
    while (1)
    {
        printf("Task T1 executed\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("Task T1 calling Task2\n");
        xTaskNotifyGive(TaskHandle2);
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}

void Task2(void *data)
{
    while (1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("Task T2 executed\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
        printf("Task T2 calling Task3\n");
        xTaskNotifyGive(TaskHandle3);
    }
}

void Task3(void *data)
{
    while (1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("Task T3 executed\n");
        vTaskDelay(pdMS_TO_TICKS(5000));
        printf("Task T3 calling Task1\n");
        xTaskNotifyGive(TaskHandle1);
    }
}

void Task4(void *data)
{
    int Send = 100;
    while (1)
    {
        Send++;
        printf("Task T4 sending data: %d\n", Send);
        int abc = xQueueSend(MessageQueue, &Send, pdMS_TO_TICKS(100));
        if (abc != pdPASS)
        {
            printf("Task T4 failed to send data\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void Task5(void *data)
{
    int receive;
    while (1)
    {
        int abc = xQueueReceive(MessageQueue, &receive, portMAX_DELAY);
        if (abc == pdPASS)
        {
            printf("Task T5 received data: %d\n", receive);
        }
    }
}

int main(void)
{
    MessageQueue = xQueueCreate(10, sizeof(int));
    if (MessageQueue == NULL)
    {
        printf("Failed to create the message queue\n");
        return 1;
    }

    xTaskCreatePinnedToCore(Task1, "Task1", 2048, NULL, 5, &TaskHandle1, 0);
    xTaskCreatePinnedToCore(Task2, "Task2", 2048, NULL, 6, &TaskHandle2, 0);
    xTaskCreatePinnedToCore(Task3, "Task3", 2048, NULL, 7, &TaskHandle3, 1);
    xTaskCreatePinnedToCore(Task4, "Task4", 2048, NULL, 8, &TaskHandle4, 1);
    xTaskCreatePinnedToCore(Task5, "Task5", 2048, NULL, 9, &TaskHandle5, 1);

    xTaskNotifyGive(TaskHandle1);

    vTaskStartScheduler();
    return 0;
}
