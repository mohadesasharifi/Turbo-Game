#include "led.h"

void bluLed_init(void)
{
    led_init ();
    led_set (LED1, 0);
}

void turn_on_blue_led(void)
{
    led_set (LED1, 1);
}

void turn_off_blue_led(void)
{
    led_set (LED1, 0);
}