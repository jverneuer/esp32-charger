/* 
    main entry point tasks are started from here.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "config/config.h"


void getTaskStatus(void* pvParameters){
    if(DEBUG){
        while (1){
            char ptrTaskList[250];
            vTaskList(ptrTaskList);
            printf("%s ", ptrTaskList);
            vTaskDelay(5000 / portTICK_PERIOD_MS);
        }
    }
}

