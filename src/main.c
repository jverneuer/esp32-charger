/* 
    main entry point tasks are started from here.
*/
#include "blink/blinktask.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "config/config.h"
#include "freertos/task.h"



TaskHandle_t xHandle = NULL;
TaskStatus_t xTaskDetails;
char ptrTaskList[250];

void assertTaskCreateSuccess(BaseType_t xReturned){
    if(DEBUG){
        if( xReturned == pdPASS ){
            printf("%s task creation succesfull", pcTaskGetName( xHandle ));
        }
        else{
            printf("Error %s task creation FAILED", pcTaskGetName( xHandle ));
        }

    }

}

void getTaskStatus(){
    if(DEBUG){
        while (1){
            vTaskList(ptrTaskList);
            printf("%s ", ptrTaskList);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
    }
}

void app_main(){
    assertTaskCreateSuccess(xTaskCreate(blink, "blink", 3000, NULL, 1, &xHandle));
    if(DEBUG){
        assertTaskCreateSuccess(xTaskCreate(getTaskStatus, "getTaskStatus", 3000, NULL, 1, &xHandle));
    }
}

