/*=============================================================================
 * Copyright (c) 2020, Francisco Timez <franciscotimez@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/09/02
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __USER_TASKS_H__
#define __USER_TASKS_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include "FreeRTOS.h"
#include "task.h"
#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

/*=====[Prototypes (declarations) of public functions]=======================*/

void delay_con_for( uint32_t ms );
void blink_n_500( uint32_t n, uint32_t led );

void tarea_A_code( void*  );
void tarea_B_code( void*  );
void tarea_C_code( void*  );
void tarea_D_code( void*  );


/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __USER_TASKS_H__ */
