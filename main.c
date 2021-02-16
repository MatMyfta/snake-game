//****************************************************************************
//
// main.c - MSP-EXP432P401R + Educational Boosterpack MkII - Snake game
//
// author:  Mateo Myftaraj
//
//****************************************************************************

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/driverlib/gpio.h>
#include <ti/devices/msp432p4xx/driverlib/interrupt.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "graphics.h"

#define LF_DW   4000
#define RG_UP   12000

#define EASY_DIFF   2
#define HARD_DIFF   1

#define SLEEP       5

typedef enum { EASY, HARD } Difficulty;

Difficulty diff = EASY;
uint8_t menu, game;
uint8_t count;
uint8_t highscore = 0;

/* Graphic library context */
Graphics_Context g_sContext;

/* ADC results buffer */
static uint16_t resultsBuffer[2];

Snake snake;

/* Statics */
const Timer_A_UpModeConfig upConfig = {
    TIMER_A_CLOCKSOURCE_ACLK,                   // 32kHz
    TIMER_A_CLOCKSOURCE_DIVIDER_12,             // divider by / 12 ~= 3kHz
    120,                                        // 120/3000 kHz ~= 40ms
    TIMER_A_TAIE_INTERRUPT_DISABLE,             // Disable Timer interrupt
    TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,         // Enable CCR0 interrupt
    TIMER_A_DO_CLEAR                            // Clear value
};

Timer_A_CompareModeConfig compareConfig_PWM = {
    TIMER_A_CAPTURECOMPARE_REGISTER_4,          // Use CCR3
    TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
    TIMER_A_OUTPUTMODE_TOGGLE_SET,
    5000
};

void _delayTimerInit() {

    MAP_Timer_A_clearTimer(TIMER_A0_BASE);

    /* Initializing ACLK to LFXT (effectively 32khz) */
    MAP_CS_initClockSignal(CS_ACLK, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /* Configuring Timer_A1 for Up Mode */
    MAP_Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);

    /* Enabling interrupts and starting the timer */
    MAP_Interrupt_enableInterrupt(INT_TA0_0);
    MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
}

void _buzzerInit() {
    /* Configures P2.7 to PM_TA0.4 for using Timer PWM to control LED */
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN7,
    GPIO_PRIMARY_MODULE_FUNCTION);
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

    /* Configuring P1.1 as an input and enabling interrupts */
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);  // left
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);  // right
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);
    MAP_Interrupt_enableInterrupt(INT_PORT1);
    MAP_Interrupt_enableInterrupt(INT_PORT4);

    _graphicsInit();
    _delayTimerInit();
    _buzzerInit();

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


/* Initializes all the game structure */
void _gameInit() {
    game = 1;
    menu = 0;

    count = 0;

    /* Initialize snake and apple structures */
    s_init(&snake);
    init_apple();

    Graphics_clearDisplay(&g_sContext);

    _graphics_drawSnake(&snake);
    _graphics_drawApple(&apple);
}

void _menuInit() {
    menu = 1;
    game = 0;

    Graphics_clearDisplay(&g_sContext);

    _graphics_initMenu(highscore);
}

void changeDifficulty() {
    diff = (diff == EASY ? HARD : EASY);
}
int getDifficultyValue() {
    return (diff == EASY ? EASY_DIFF : HARD_DIFF);
}

int main(void) {

    /* Initialize hardware */
    _hwInit();

    /* generate seed for random function */
    srand( time(NULL) );

    _menuInit();
//    _gameInit();

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

    count = 0;
}

// left button
void PORT1_IRQHandler(void)
{
    uint32_t status_p1;
    status_p1 = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);

    if(menu && (status_p1 & GPIO_PIN1)) {
        _gameInit();
    }
    if (!game && !menu &&(status_p1 & GPIO_PIN1)) {
        _menuInit();
    }
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
}

// This is the TIMERA interrupt vector service routine.
void TA0_0_IRQHandler(void) {
    if (game) {
        count += 1;
        /*
         * If count>=3 means that the user is sleeping;
         * this means that the snake should go straight by himself.
         */
        if (count >= SLEEP*getDifficultyValue()) {
            /* helper variables */
            uint8_t x = snake.head->x;
            uint8_t _x = snake.head->next->x;
            uint8_t y = snake.head->y;
            uint8_t _y = snake.head->next->y;

            /* no interrupts triggered */
            if (x == _x-1 || (x==MAX_RANGE-1 && _x==MIN_RANGE+1))
                s_move(&snake,x-1,y);
            else if (x == _x+1 || (x==MIN_RANGE+1 && _x==MAX_RANGE-1))
                s_move(&snake,x+1,y);
            else if (y == _y-1 || (y==MAX_RANGE-1 && _y==MIN_RANGE+1))
                s_move(&snake,x,y-1);
            else if (y == _y+1 || (y==MIN_RANGE+1 && _y==MAX_RANGE-1))
                s_move(&snake,x,y+1);
            count = 0;
        }
    }
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_0);
}

/* This interrupt is fired whenever a conversion is completed and placed in
 * ADC_MEM1. This signals the end of conversion and the results array is
 * grabbed and placed in resultsBuffer */
void ADC14_IRQHandler(void) {
    uint64_t status;

    /* Returns the status of a the ADC interrupt register masked with the
     * enabled interrupts. */
    status = MAP_ADC14_getEnabledInterruptStatus();
    /* Clears the indicated ADCC interrupt sources. */
    MAP_ADC14_clearInterruptFlag(status);

    // disable the interrupt to compute the results
    MAP_Interrupt_disableInterrupt(INT_ADC14);

    if (game) {
        // helper variables
        Node *_h = snake.head;
        uint8_t _x = _h->x, _y = _h->y;

        /* ADC_MEM1 conversion completed
         * if count>=1 means that one timer interrupt has occurred;
         * that means, that a delay has been waited */
        if(count >= 1*getDifficultyValue() && count < SLEEP*getDifficultyValue() && (status & ADC_INT1)) {
            /* Returns the conversion result for the specified memory channel in
             * the format assigned by the ADC14_setResultFormat (unsigned binary
             * by default) function. Then stores the value in a buffer.*/
            resultsBuffer[0] = ADC14_getResult(ADC_MEM0);
            resultsBuffer[1] = ADC14_getResult(ADC_MEM1);

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
    }
    // enable interrupt again
    MAP_Interrupt_enableInterrupt(INT_ADC14);
}

