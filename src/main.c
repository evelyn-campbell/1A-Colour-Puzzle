// Starter Code Written by Bernie Roehl, August 2021

// Colour Detection Pattern Puzzle
// Authors: Keya Tiwari, Evelyn Campbell

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"

bool is_won (void){

    // if (check sequences)
    // true --> turn on on-board LED
    // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true);   // turn on LED (can change to off-board LED later if needed)
    
    //else
    return false;
}

void play_puzzle(bool is_won){


}

int main(void)
{
    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    // initialize the pins to be input, output, alternate function, etc...

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED
    InitializePin(GPIOA, GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_NOPULL, 0);      // sensor output --> RGB values
    InitializePin(GPIOA, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,0);   // S3 Port on sensor (select colour filters)
    InitializePin(GPIOA, GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,0);   // S2 Port on sensor (select colour filters)
    InitializePin(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);   // S0 Port on sensor (select output frequency)
    InitializePin(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);   // S1 Port on sensor (select output frequency)

    // initialize output frequency of sensor
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);    // S0 set at low frequency
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);    // S1 set at high frequency

    //TESTING
    unsigned long red = 0;
    char buff[100];

    while (1){
    //red value
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);  // low  
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);  // low

    red = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
    sprintf(buff, "RED: %d", red);

    }


    // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // is required, since there's one on the board)

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);

    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)

    return 0;
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}

