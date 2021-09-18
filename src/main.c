#include <stdio.h>

//freertos stuff
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"

//common lib stuf
#include "config/config.h"
#include "helpers/helpers.h"

//tasks
#include "blink/blinktask.h"



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
    // tasks which are not needed for production use.
    if(DEBUG){
        // prints a table of all tasks including basic stats every few seconds or so
        assertTaskCreateSuccess(xTaskCreate(getTaskStatus, "getTaskStatus", 3000, NULL, 1, &xHandle));
    }
}