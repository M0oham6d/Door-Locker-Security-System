/***************************************************************************************************************
 * pir_sensor.h
 * Author: Muhammed Ayman
 * Module: PIR Sensor
 **************************************************************************************************************/

#ifndef HAL_PIR_SENSOR_H_
#define HAL_PIR_SENSOR_H_

#include "../Standard_Types/standard_types.h"

/*******************************************************************************
 *                                Configurations                               *
 *******************************************************************************/
#define PIR_PORT_CONNECTION			PORTC_ID
#define PIN_CONNECTION				PIN2_ID

/*******************************************************************************
 *                      	Functions Prototypes                               *
 *******************************************************************************/

/*
 *  Function to initialize the PIR driver.
 *  Set up pin direction as input pin.
 */
void PIR_init(void);

/*
 *  Function to return PIR State.
 */
uint8 PIR_getState(void);

#endif /* HAL_PIR_SENSOR_H_ */
