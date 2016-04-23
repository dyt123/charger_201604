/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_macrodriver.h
* Version      : CodeGenerator for RL78/G12 V2.03.02.01 [15 May 2015]
* Device(s)    : R5F1026A
* Tool-Chain   : CCRL
* Description  : This file implements general head file.
* Creation Date: 2015/10/09
***********************************************************************************************************************/

#ifndef STATUS_H
#define STATUS_H
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "iodefine.h"

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#ifndef __TYPEDEF__
#define DI      __DI
#define EI      __EI
#define HALT    __halt
#define NOP     __nop
#define STOP    __stop
#define BRK     __brk

/* Status list definition */
#define MD_STATUSBASE       (0x00U)
#define MD_OK               (MD_STATUSBASE + 0x00U) /* register setting OK */
#define MD_SPT              (MD_STATUSBASE + 0x01U) /* IIC stop */
#define MD_NACK             (MD_STATUSBASE + 0x02U) /* IIC no ACK */
#define MD_BUSY1            (MD_STATUSBASE + 0x03U) /* busy 1 */
#define MD_BUSY2            (MD_STATUSBASE + 0x04U) /* busy 2 */
#define MD_OVERRUN           (MD_STATUSBASE + 0x05U) /* IIC OVERRUN occur */

/* Error list definition */
#define MD_ERRORBASE        (0x80U)
#define MD_ERROR            (MD_ERRORBASE + 0x00U)  /* error */
#define MD_ARGERROR         (MD_ERRORBASE + 0x01U)  /* error agrument input error */
#define MD_ERROR1           (MD_ERRORBASE + 0x02U)  /* error 1 */
#define MD_ERROR2           (MD_ERRORBASE + 0x03U)  /* error 2 */
#define MD_ERROR3           (MD_ERRORBASE + 0x04U)  /* error 3 */
#define MD_ERROR4           (MD_ERRORBASE + 0x05U)  /* error 4 */
#endif

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
#ifndef __TYPEDEF__
typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef signed short        int16_t;
typedef unsigned short      uint16_t;
typedef signed long         int32_t;
typedef unsigned long       uint32_t;
typedef unsigned short      MD_STATUS;
#define __TYPEDEF__
#endif

typedef enum
{
	UNDER,
	ABOVE
}comp_condt_t;

#define TRUE 1
#define FALSE 0

enum
{
	IDLE_MODE = 0,
	NO_BATTERY_MODE,
	PRE_CHARGE_MODE, 
	FAST_CHARGE_MODE,
	BATTERY_FAULT_MODE,
	CHARGE_END_MODE,
	CHARGE_FINISH_MODE,
	DISCHARGE_MODE,
	CHARGE_CV_MODE,
};

#define PULSE_CHARGING_HIGH 1
#define PULSE_CHARGING_LOW 2



#define ADC_0V5	102
#define ADC_1V		205
#define ADC_1V25		256
#define ADC_1V5		307
#define ADC_1V95	399
#define ADC_2V		410
#define ADC_2V25	461
#define ADC_2V3		471
#define ADC_2V32	475
#define ADC_2V5		512
#define ADC_2V58	528
#define ADC_2V6		532
#define ADC_2V62	536
#define ADC_2V63	539
#define ADC_2V65	543
#define ADC_2V7	553
#define ADC_2V75	563
#define ADC_2V83	580
#define ADC_2V85	584
#define ADC_2V93	600
#define ADC_3V		614
#define ADC_3V02	618
#define ADC_3V05	625
#define ADC_3V07	629
#define ADC_3V08	631	
#define ADC_3V1		635
#define ADC_3V11	637
#define ADC_3V12	639
#define ADC_3V13	641
#define ADC_3V15	645
#define ADC_3V19	653
#define ADC_3V2		655
#define ADC_3V22	659
#define ADC_3V25	666
#define ADC_3V3		676
#define ADC_3V33	682
#define ADC_3V45	707
#define ADC_3V5		717
#define ADC_3V55	727
#define ADC_3V6		737
#define ADC_3V62	741
#define ADC_3V65	748
#define ADC_3V66	750
#define ADC_3V675 753
#define ADC_3V75	768
#define ADC_3V87	793
#define ADC_3V9		799
#define ADC_3V93	805
#define ADC_4V		819
#define ADC_4V02	823
#define ADC_4V1		840
#define ADC_4V13	846
#define ADC_4V14	848
#define ADC_4V15	850
#define ADC_4V2		860
#define ADC_4V25	870
#define ADC_4V26	872
#define ADC_4V29	879
#define ADC_4V33	886
#define ADC_4V4		901
#define ADC_4V5		922
#define ADC_4V6		942

#define CHECK_CYCLE 3 //lion:3, nimh:2, unit: s.
#define STOP_TIME 100 //lion:100, nimh:20, unit: 10ms.

extern unsigned short	bat_vol;
extern volatile int32_t 	charge_time; // unit: second
extern volatile short		delay_time;
extern unsigned char 	system_mode;
extern unsigned char 	battery_id;
extern unsigned char 	pwm_width;
extern unsigned char 	freq_LED_RED;
extern unsigned char	freq_LED_GREEN;

extern volatile int16_t pulse_charge_high_time;
extern volatile int16_t pulse_charge_low_time;
extern volatile uint8_t pulse_charging;


//extern void delay_10ms(unsigned short n);
extern void delay_nms(uint16_t n);
extern void delay(unsigned char n);
extern void TMH1_start(void);
extern void TMH1_stop(void);
//extern void check_voltage(void);
uint8_t check_voltage(uint8_t channel, uint8_t cnt, uint16_t comp_vol, comp_condt_t condition);

extern void voltage_monitor(void);

extern void idle_process(void);
extern void fast_charge_process(void);
extern void charge_end_process(void);
extern uint8_t check_no_battery(void);



/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/

#endif
