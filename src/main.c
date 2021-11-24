// Starter Code Written by Bernie Roehl, August 2021

// Colour Detection Pattern Puzzle
// Authors: Keya Tiwari, Evelyn Campbell
// November, 2021

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"

#define TIME_RAND

bool in_colour_range (int item, int mid_value, int uncertainty){

    if (item > (mid_value-uncertainty) && item < (mid_value+uncertainty)){
        return true;
    }
    else{
        return false;
    }
}

void play_puzzle(bool is_won)
{
}

bool sequence_check (unsigned long item [3], int sequence_num){
    size_t rgb = 3;
    unsigned long ans1 [rgb];   // purple
    unsigned long ans2 [rgb];   // orange
    unsigned long ans3 [rgb];   // blue
    unsigned long ans4 [rgb];   // green
    unsigned long ans5 [rgb];   // pink

    // purple
    const ans1[0] = 150;
    const ans1[1] = 45;
    const ans1[2] = 200;

    // orange
    const ans2[0] = 220;
    const ans2[1] = 125;
    const ans2[2] = 50;

    // blue
    const ans3[0] = 70;
    const ans3[1] = 150;
    const ans3[2] = 190;

    // green
    const ans4[0] = 85;
    const ans4[1] = 185;
    const ans4[2] = 85;

    // pink
    const ans5[0] = 205;
    const ans5[1] = 80;
    const ans5[2] = 170;

    if (sequence_num == 1){
        // compare rgb values
        if (in_colour_range(item[0], ans1[0], 60) && in_colour_range(item[1], ans1[1], 45) && in_colour_range(item[2], ans1[2], 75)){
            return true;
        }
        else {
            return false;
        }
    }
    else if (sequence_num == 2){
        if (in_colour_range(item[0], ans2[0], 35) && in_colour_range(item[1], ans2[1], 50) && in_colour_range(item[2], ans2[2], 50)){
            return true;
        }
        else {
            return false;
        }

    }
    else if (sequence_num == 3){
         if (in_colour_range(item[0], ans3[0], 70) && in_colour_range(item[1], ans3[1], 60) && in_colour_range(item[2], ans3[2], 60)){
            return true;
        }
        else {
            return false;
        }
    }
    else if (sequence_num == 4){
        if (in_colour_range(item[0], ans4[0], 85) && in_colour_range(item[1], ans4[1], 70) && in_colour_range(item[2], ans4[2], 85)){
            return true;
        }
        else {
            return false;
        }
    }
    else if (sequence_num == 5){
        if (in_colour_range(item[0], ans5[0], 50) && in_colour_range(item[1], ans5[1], 80) && in_colour_range(item[2], ans5[2], 85)){
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            return true;
        }
        else {
            return false;
        }
    }
    else{
        sequence_num = 0;
    }


    // if sequence num = 1 --> compare to item 1
}


// measure frequency  - change to frequency alg when possible
unsigned long measure_frequency(){
    uint16_t value1 = 0;
    uint16_t value2 = 0;
    uint16_t difference = 0;
    uint16_t width = 0;
    uint16_t prescalar = 84;
    bool is_first_captured = false;
    TIM_HandleTypeDef *htim = TIM2;

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

            float reference_clock = 84/(prescalar);
            float mul_factor = 1000000/reference_clock;

            width = difference*mul_factor;

            __HAL_TIM_SET_COUNTER(htim, 0);
            is_first_captured = false;

            return width;
        }
    }
}

// rgb value for red
unsigned long red_value(){

    // write to sensor to use red photodiode type
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);

    unsigned long red = measure_frequency(); 
}

// rgb value for blue 
unsigned long blue_value() {

    // write to sensor to use blue photodiode type
    HAL_GPIO_WritePint(GPIOA, GPIO_PIN_3, 0);
    HAL_GPIO_WritePint(GPIOA, GPIO_PIN_4, 1);

    unsigned long blue = measure_frequency(); 
    return blue;
}

// rgb value for green
unsigned long green_value() {

    // write to sensor to use green photodiode type
    HAL_GPIO_WritePint(GPIOA, GPIO_PIN_3, 1);
    HAL_GPIO_WritePint(GPIOA, GPIO_PIN_4, 1);

    unsigned long green = measure_frequency(); 
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

    // timer setup (for frequency measurements)
    uint16_t period = 1000, prescalar = 84;
    __TIM2_CLK_ENABLE(); 
    TIM_HandleTypeDef pwmTimerInstance;  
    InitializePWMTimer(&pwmTimerInstance, TIM2, period, prescalar);   
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_1); 

    // TESTING
    char buff[100];

    while (1){      //need to measure frequency here (pulse width)

    unsigned long red = red_value();

    sprintf(buff, "RED: %lu \n", red);
    SerialPuts(buff);

    }

    return 0;
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}
