//****************************************************************************
//
// main.c - MSP-EXP432P401R + Educational Boosterpack MkII - Snake game
//
// author:  Mateo Myftaraj
//
//****************************************************************************

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "graphics.h"

#define LF_DW   4000
#define RG_UP   12000

uint8_t freeze;

/* Graphic library context */
Graphics_Context g_sContext;

/* ADC results buffer */
static uint16_t resultsBuffer[2];

Snake snake;

void _graphicsInit()
{
    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(&g_sContext);

}

void _delayTimerInit() {
    /* Initializes timer */
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
    TIMER_A0->CCR[0] = 240*32;
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | // SMCLK, continuous mode
            TIMER_A_CTL_MC__CONTINUOUS;

    // Enable timer interrupt
    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);

    freeze = 1;
}

void _hwInit() {
    /* Halting WDT and disabling master interrupts */
    MAP_WDT_A_holdTimer();
    MAP_Interrupt_disableMaster();

    /* Set the core voltage level to VCORE1 */
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

    /* Set 2 flash wait states for Flash bank 0 and 1*/
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

    /* Initializes Clock System */
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    _graphicsInit();
    _delayTimerInit();

    /* Configures Pin 6.0 and 4.4 as ADC input */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);

    /* Initializing ADC (ADCOSC/64/8) */
    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8, 0);

    /* Configuring ADC Memory (ADC_MEM0 - ADC_MEM1 (A15, A9)  with repeat)
     * with internal 2.5v reference */
    MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);
    MAP_ADC14_configureConversionMemory(ADC_MEM0,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);

    MAP_ADC14_configureConversionMemory(ADC_MEM1,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);

    /* Enabling the interrupt when a conversion on channel 1 (end of sequence)
     *  is complete and enabling conversions */
    MAP_ADC14_enableInterrupt(ADC_INT1);

    /* Enabling Interrupts */
    MAP_Interrupt_enableInterrupt(INT_ADC14);
    MAP_Interrupt_enableMaster();

    /* Setting up the sample timer to automatically step through the sequence
     * convert.
     */
    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    /* Triggering the start of the sample */
    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();
}


int main(void) {
    /* generate seed for random function */
    srand( CS_DCOCLK_SELECT );

    /* Initialize hardware */
    _hwInit();

    freeze = 0;

    /* Initialize snake and apple structures */
    s_init(&snake);
    init_apple();

    _graphics_drawSnake(&snake);
    _graphics_drawApple(&apple);

    while(1)
    {
        MAP_PCM_gotoLPM0();
    }

}

/*
 * Draw the snake and the apple on the screen
 */
void draw() {
    _graphics_drawSnake(&snake);
    _graphics_drawApple(&apple);

    _delayTimerInit();
}

void TA0_0_IRQHandler(void) {
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    P1->OUT ^= BIT0;
    freeze = 0;
}

/* This interrupt is fired whenever a conversion is completed and placed in
 * ADC_MEM1. This signals the end of conversion and the results array is
 * grabbed and placed in resultsBuffer */
void ADC14_IRQHandler(void)
{
    uint64_t status;

    /* Returns the status of a the ADC interrupt register masked with the
     * enabled interrupts. */
    status = MAP_ADC14_getEnabledInterruptStatus();
    /* Clears the indicated ADCC interrupt sources. */
    MAP_ADC14_clearInterruptFlag(status);

    // disable the interrupt to compute the results
    MAP_Interrupt_disableInterrupt(INT_ADC14);

    /* ADC_MEM1 conversion completed */
    if(status & ADC_INT1 && game && !freeze)
    {
        /* Returns the conversion result for the specified memory channel in
         * the format assigned by the ADC14_setResultFormat (unsigned binary
         * by default) function. Then stores the value in a buffer.*/
        resultsBuffer[0] = ADC14_getResult(ADC_MEM0);
        resultsBuffer[1] = ADC14_getResult(ADC_MEM1);

        // helper variables
        Node *_h = snake.head;
        uint8_t _x = _h->x, _y = _h->y;


        /* go left */
        if (resultsBuffer[0] <= LF_DW && _h->next->x != _x-1) {
            s_move(&snake,_x-1,_y);
            draw();
        }
        /* go right */
        else if (resultsBuffer[0] >= RG_UP && _h->next->x != _x+1) {
            s_move(&snake,_x+1,_y);
            draw();
        }
        /* go down */
        else if (resultsBuffer[1] <= LF_DW && _h->next->y != _y+1) {
            s_move(&snake,_x,_y+1);
            draw();
        }
        /* go up */
        else if (resultsBuffer[1] >= RG_UP && _h->next->y != _y-1) {
            s_move(&snake,_x,_y-1);
            draw();
        }
    }
    // enable interrupt again
    MAP_Interrupt_enableInterrupt(INT_ADC14);
}

