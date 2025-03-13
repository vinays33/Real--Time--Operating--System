#include <FreeRTOS.h>
#include <task.h>
#include <message_buffer.h>
#include <stdio.h>

TaskHandle_t TaskHandle1;
TaskHandle_t TaskHandle2;
TaskHandle_t TaskHandle3;
TaskHandle_t TaskHandle4;
TaskHandle_t TaskHandle5;

MessageBufferHandle_t MessageBuffer;

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
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void Task4(void *data)
{
    int Send = 100;
    while (1)
    {
        Send++;
        printf("Task T4 sending data: %d\n", Send);
        size_t bytesSent = xMessageBufferSend(MessageBuffer, &Send, sizeof(Send), pdMS_TO_TICKS(100));
        if (bytesSent != sizeof(Send))
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
        size_t bytesReceived = xMessageBufferReceive(MessageBuffer, &receive, sizeof(receive), portMAX_DELAY);
        if (bytesReceived == sizeof(receive))
        {
            printf("Task T5 received data: %d\n", receive);
        }
    }
}

int main(void)
{
    MessageBuffer = xMessageBufferCreate(256);
    if (MessageBuffer == NULL)
    {
        printf("Failed to create the message buffer\n");
        return 1;
    }

    xTaskCreatePinnedToCore(Task1, "Task1", 2048, NULL, 5, &TaskHandle1, 0);
    xTaskCreatePinnedToCore(Task2, "Task2", 2048, NULL, 6, &TaskHandle2, 0);
    xTaskCreatePinnedToCore(Task3, "Task3", 2048, NULL, 7, &TaskHandle3, 1);
    xTaskCreatePinnedToCore(Task4, "Task4", 2048, NULL, 8, &TaskHandle4, 1);
    xTaskCreatePinnedToCore(Task5, "Task5", 2048, NULL, 9, &TaskHandle5, 1);

    vTaskStartScheduler();
    return 0;
}
