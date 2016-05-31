/******************************************************************************
Simple blink program with ESP32 software timer
LED connected to GPIO4 , can be configured in user_config.h

ESP32 RTOS SDK v2.0
ESP32 RTOS SDK: https://github.com/espressif/ESP32_RTOS_SDK
Tested with ESP31B developer board ESP-WROOM-03
gpio.h needs to be included from /driver_lib

Markus Ulsass, Hamburg Germany
https://github.com/markbeee/ESP32_Examples
******************************************************************************/

#include <esp_common.h>  // Needed for common definitions
#include "gpio.h" // Manipulate GPIOs
#include "user_config.h" // define user related stuff

/* Definitions */

os_timer_t timer; // struct - see esp_timer.h
uint32_t interval = 500; // Initializing interval to 500ms

void blink(void); // Blink function
void blinkIntervalTimer(uint32_t); // Function for setting blink interval

/* user_init - Entry point of application */

void user_init(void)
{
	GPIO_AS_OUTPUT(LED_PIN); // Set LED as output
	GPIO_OUTPUT_SET(LED_PIN,1);
	blinkIntervalTimer(interval);
}

/*****************************************
 * Calls blink function every interval   *
 * os_timer is a software timer          *
 * See SDK APIs for detailed information *
 *****************************************/

void blinkIntervalTimer(uint32_t interval)
{
	os_timer_disarm(&timer);
	os_timer_setfn(&timer, (os_timer_func_t *) blink, (void *) 0);
	os_timer_arm(&timer, interval, 1);
}

void blink(void)
{
	static bool state = false; // Used to toggle LED state
	if(state == true)
		{
		GPIO_OUTPUT_SET(LED_PIN, 1); // Turn LED on
		state = false;
		}
	else
		{
		GPIO_OUTPUT_SET(LED_PIN, 0); // Turn LED off
		state = true;
		}
}
