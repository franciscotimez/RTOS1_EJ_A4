/*=============================================================================
 * Copyright (c) 2020, Francisco Timez <franciscotimez@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/09/02
 *===========================================================================*/

/*=====[Inclusion of own header]=============================================*/

#include "userTasks.h"
 
/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/
#define CUENTAS_1MS 9251

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/
extern TaskHandle_t task_handles[4];

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

void delay_con_for( uint32_t ms ){
	volatile uint32_t i;
	volatile uint32_t j;

	for( i=0 ; i<ms ; i++ )
	{
		/* delay de aprox 1 ms */
		for( j=0 ; j<CUENTAS_1MS ; j++ )
		{
		}
	}
	return;
}

void blink_n_500( uint32_t n, uint32_t led )
{
	/* genero 2 blinks*/
	int blink_count  = n;
	int cycles       = blink_count*2;

	for( ; cycles>0 ; cycles-- )
	{
		taskYIELD ();
		gpioToggle( led );
		taskYIELD ();
		delay_con_for( 500 );
	}
	return;
}



void tarea_A_code( void* taskParmPtr )
{
	BaseType_t res;

	printf( "Tarea A\r\n" );

	UBaseType_t my_prio = uxTaskPriorityGet( 0 );   /* se podria haber usado uxTaskPriorityGet( task_handles[0] ) */

	/* creo la tarea B C y D */
	res = xTaskCreate(
			  tarea_B_code,                // Funcion de la tarea a ejecutar
			  ( const char * )"tarea_b",   // Nombre de fantasia
			  configMINIMAL_STACK_SIZE*2,  /* tamaño del stack de cada tarea (words) */
			  NULL,                        // Parametros de tarea
			  my_prio - 2,                 /* le doy menos prioridad que la tarea actual (la A) */
			  &task_handles[1]             // Puntero a la tarea creada en el sistema
		  );

	configASSERT( res == pdPASS );

	res = xTaskCreate(
			  tarea_C_code,                // Funcion de la tarea a ejecutar
			  ( const char * )"tarea_c",   // Nombre de fantasia
			  configMINIMAL_STACK_SIZE*2,  /* tamaño del stack de cada tarea (words) */
			  NULL,                        // Parametros de tarea
			  my_prio - 2,                 /* le doy menos prioridad que la tarea actual (la A) */
			  &task_handles[2]             // Puntero a la tarea creada en el sistema
		  );

	configASSERT( res == pdPASS );

	res = xTaskCreate(
			  tarea_D_code,                // Funcion de la tarea a ejecutar
			  ( const char * )"tarea_d",   // Nombre de fantasia
			  configMINIMAL_STACK_SIZE*2,  /* tamaño del stack de cada tarea (words) */
			  NULL,                        // Parametros de tarea
			  my_prio - 4,                 /* le doy menos prioridad que la tarea actual (la A) */
			  &task_handles[3]             // Puntero a la tarea creada en el sistema
		  );

	configASSERT( res == pdPASS );

	/* suspendo la tarea actual */
	vTaskSuspend( 0 );                              /* se podria haber usado vTaskSuspend( task_handles[0] ) */

	blink_n_500( 2 , LEDB );

	/* suspendo la tarea actual */
	vTaskSuspend( task_handles[0] );                /* se podria haber usado vTaskSuspend( 0 ) */
}

void tarea_B_code( void* taskParmPtr )
{
	printf( "Tarea B\r\n" );

	blink_n_500( 3, LED1 );

	/* retomo tarea A, como tiene mayor prioridad, habra un cambio de contexto.*/
	vTaskResume( task_handles[0] );

	/* suspendo la tarea actual, le va a dar el CPU a las tareas de menor prioridad (porque la tarea A esta suspendida) */
	vTaskSuspend( task_handles[1] );   /* se podria haber usado vTaskSuspend( 0 ) */
}

void tarea_C_code( void* taskParmPtr )
{
	printf( "Tarea C\r\n" );

	blink_n_500( 3, LED2 );

	/* suspendo la tarea actual, le va a dar el CPU a las tareas de menor prioridad (porque la tarea A esta suspendida) */
	vTaskSuspend( task_handles[2] );   /* se podria haber usado vTaskSuspend( 0 ) */
}

void tarea_D_code( void* taskParmPtr )
{
	printf( "Tarea D\r\n" );

	/* termino todas las tareas de mas prioridad */
	vTaskDelete( task_handles[0] );
	vTaskDelete( task_handles[1] );
	vTaskDelete( task_handles[2] );

	while( 1 )
	{
		gpioToggle( LED3 );
		delay_con_for( 500 );
	}
}


// Task overflow hook
void vApplicationStackOverflowHook(TaskHandle_t pxTask , char *pcTaskName){

	printf("\r\nApplication Stack Overflow!! on Task: %s\r\n", (char*)pcTaskName);

	taskENTER_CRITICAL();
	configASSERT(0);
	taskEXIT_CRITICAL();

}

/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/

