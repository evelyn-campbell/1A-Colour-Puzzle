// Starter Code Written by Bernie Roehl, August 2021

// Colour Detection Pattern Puzzle
// Authors: Keya Tiwari, Evelyn Campbell
// November, 2021

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"

#define TIME_RAND

bool is_won(void)
{

    // if sequence number is final (this function will only be called when there is a colour match)
    // true --> turn on on-board LED (other LED if have time)
    // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true);   // turn on LED (can change to off-board LED later if needed)

    //else
    return false;
}

void play_puzzle(bool is_won)
{
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

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); // on-board LED
    InitializePin(GPIOA, GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_NOPULL, 0);     // sensor output --> RGB values
    InitializePin(GPIOA, GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); // S2 Port on sensor (select colour filters)
    InitializePin(GPIOA, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); // S3 Port on sensor (select colour filters)
    InitializePin(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // S0 Port on sensor (select output frequency)
    InitializePin(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // S1 Port on sensor (select output frequency)

    SerialSetup(9600);

    // initialize frequencies
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);    // S0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);    // S1

    // TESTING

    unsigned long red = 0;

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);

    char buff[100];

    while (1){

    red = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

    sprintf(buff, "RED: %lu \n", red);
    SerialPuts(buff);

    }

    // output occurs in 0s and 1s -- need to use this to get an rgb value as an int


    // TO DO:
    // figure out how to get outputs to serial monitor working (nothing prints)
    // figure out how to receive inputs from TSC3200 sensor and what data type these inputs come in (long, int, etc)
    // everything from here is simpler

    // C is not OOP (might lose marks on design document oops)

    // SEQUENCE CHECK CODE
    // array [3] = (red, blue, green)
    // bool foo (array, sequence number){
    //compare to answer
    // if wrong, (maybe send output) set sequence number to 0
    // otherwise, call is_won
    // call is_won
    // do stuff

    return 0;
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}
