/* 
    main entry point tasks are started from here.
*/
#include "blink/blinktask.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "config/config.h"
#include "helpers/helpers.h"


TaskHandle_t xHandle = NULL; // holds a handle to the task to determine success or failure of starting it.

// logs the success/no success of creating the tasks if global debug var is set to true
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

// main function tasks are started here, nothing than a simple entry point executed once on start
void app_main(){
    assertTaskCreateSuccess(xTaskCreate(blink, "blink", 3000, NULL, 1, &xHandle));

    if(DEBUG){
        assertTaskCreateSuccess(xTaskCreate(getTaskStatus, "getTaskStatus", 3000, NULL, 1, &xHandle));
    }
}