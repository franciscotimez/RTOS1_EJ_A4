/*=============================================================================
 * Copyright (c) 2020, Francisco Timez <franciscotimez@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/09/02
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "RTOS1_EJ_A4.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "sapi.h"
#include "userTasks.h"

/*=====[Definition macros of private constants]==============================*/
#define CUENTAS_1MS 9251

/*=====[Definitions of extern global variables]==============================*/
print_t debugPrint;

/*=====[Definitions of public global variables]==============================*/
BaseType_t res;
TaskHandle_t task_handles[4];
/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
	boardInit();

	/* solo creo la tarea A */
	res = xTaskCreate(
			tarea_A_code,               // Funcion de la tarea a ejecutar
			( const char * )"tarea_a",  // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE*2, /* tamaño del stack de cada tarea (words) */
			NULL,                       // Parametros de tarea
			tskIDLE_PRIORITY+4,         // Prioridad de la tarea
			&task_handles[0]            // Puntero a la tarea creada en el sistema
	);

	configASSERT( res == pdPASS );

	vTaskStartScheduler(); // Initialize scheduler

	while( true ); // If reach heare it means that the scheduler could not start

	// YOU NEVER REACH HERE, because this program runs directly or on a
	// microcontroller and is not called by any Operating System, as in the
	// case of a PC program.
	return 0;
}
