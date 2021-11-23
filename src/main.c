// Starter Code Written by Bernie Roehl, August 2021

// Colour Detection Pattern Puzzle
// Authors: Keya Tiwari, Evelyn Campbell
// November, 2021

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"

#define TIME_RAND

bool is_won(int sequence_num)
{

    if (sequence_num == 5){
        // win!!
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        return true;
    }

    else {
        return false;
    }
    
}

void play_puzzle(bool is_won)
{
}

void sequence_check (unsigned long item [3], int sequence_num){
    size_t rgb = 3;
    unsigned long item1 [rgb];  // initialize these with rgb values later
    unsigned long item2 [rgb];
    unsigned long item3 [rgb];
    unsigned long item4 [rgb];
    unsigned long item5 [rgb];

    // if sequence num = 1 --> compare to item 1
}

// measure the length of a pulse in milliseconds
// recreate HAL_TIM_IC_CaptureCallback function to return a pulse width in ms
unsigned long measure_pulse(TIM_HandleTypeDef *htim, uint16_t prescalar){
    uint16_t value1 = 0;
    uint16_t value2 = 0;
    uint16_t difference = 0;
    uint16_t width = 0;
    bool is_first_captured = false;

    if (htim->Channel == TIM_CHANNEL_1 ){

        if (is_first_captured == false) {
            // if the first value is not captured
            value1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // store the first value
            is_first_captured = true; 
        } else {
            // if the first value is captured
            value2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // store the second value
           
            if (value2 > value1) {
                difference = value2 - value1;
            } else if (value1 > value2) {
                difference = (0xffffffff - value1) + value2;
            }
        }
    }

}

// rgb value for red
unsigned long red_value(){

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);

    unsigned long red = 0; // call measure_pulse here
    return red;
}

// rgb value for blue 
unsigned long blue_value() {

    HAL_GPIO_WritePint(GPIOA, GPIO_PIN_3, 0);
    HAL_GPIO_WritePint(GPIOA, GPIO_PIN_4, 1);

    unsigned long blue = 0; // call measure_pulse
    return blue;
}

// rgb value for green
unsigned long green_value() {

    HAL_GPIO_WritePint(GPIOA, GPIO_PIN_3, 1);
    HAL_GPIO_WritePint(GPIOA, GPIO_PIN_4, 1);

    unsigned long green = 0; // call measure_pulse
    return green;
}


// collect red colour

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
    // 20% sensor output frequency scaling
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);    // S0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);    // S1

    // timer setup
    uint16_t period = 1000, prescalar = 84;
    __TIM2_CLK_ENABLE(); 
    TIM_HandleTypeDef pwmTimerInstance;  
    InitializePWMTimer(&pwmTimerInstance, TIM2, period, prescalar);   
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_1); 

    // TESTING

    unsigned long red = 0;

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);

    char buff[100];

    while (1){      //need to measure frequency here (pulse width)

    red = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

    sprintf(buff, "RED: %lu \n", red);
    SerialPuts(buff);

    }

    // output occurs in 0s and 1s -- need to use this to get an rgb value as an int 
    // create for loop out of 256 and count 1s for colour value? -- check to see if this is accurate


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
