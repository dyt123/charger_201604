/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c                                                */
/*  DATE        :                                                      */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"

#include "r_cg_timer.h"

void delay_nms(uint16_t n)
{
	uint32_t i;
	while(n--)
	{
		for(i=0;i<100000;i++)NOP();
	}
}

void delay(unsigned char n)
{
	while(n--)NOP();
}


void ADC_Init(void)
{
	ADCEN = 1;
	ADM0 = 0x38; // fad = fclk/2
	ADM1 = 0; //Software and Sequential
	ADM2 = 0;
	ADS = 0x01; // AIN1
	ADUL = 0xff;
	ADLL = 0; //allow all data
	ADIF = 0; //clear INTAD request flag
	ADMK = 1; // disable INTAD
}

unsigned short ad_start( unsigned char channel )
{
	unsigned char i;
	unsigned short ad_result=0, ad_result_tmp[4];
	ADCE = 1;
	delay(2); // delay 1us or more
	ADS = channel;
	NOP();
	NOP();
	ADCS = 1;
	ADMK = 0;//add
	for(i=0;i<4;i++)
	{
		ADIF = 0;
		while(!ADIF) NOP(); // wait for INTAD interrupt
		ad_result_tmp[i] = ADCR;
	}
	ADCS = 0;
	ADCE = 0;
	for(i=0;i<4;i++) ad_result += ad_result_tmp[i];
	ad_result >>= 2;
	return ad_result;
}

uint16_t bat_vol;
uint8_t check_voltage(uint8_t channel, uint8_t cnt, uint16_t comp_vol, comp_condt_t condition)
{
	uint16_t tmp_bat_vol;
	uint8_t tmp_cnt = cnt, count=0;

	while(tmp_cnt--)
	{		
		tmp_bat_vol = ad_start(channel);
		if(condition == ABOVE)
		{
			if(tmp_bat_vol >= comp_vol) count++;
		}
		else if(condition == UNDER)
		{
			if(tmp_bat_vol <= comp_vol) count++;
		}	
	}
	if(count >= cnt*0.8) return TRUE;
	return FALSE;
}

uint8_t check_no_battery(void)
{
	if(check_voltage(1, 20, ADC_1V, UNDER))
	{
		P1_bit.no0 = 0;//Pin17
		P1_bit.no1 = 0;//Pin16
		P1_bit.no2 = 0;//Pin15
		P2_bit.no2 = 0;//Pin19
		P4_bit.no0 = 1;//Pin4
		return TRUE;
	}
	return FALSE;
}

uint8_t system_mode;
void main(void)
{

	EI();
	ADC_Init();
	while(1)
	{
		NOP();
		switch(system_mode)
		{
			case IDLE_MODE:
				//idle_process(vol_pre_charge,vol_fast_charge,vol_cv_charge);
				idle_process();
				break;
			case PRE_CHARGE_MODE:
				//pre_charge_process(vol_pre_charge, vol_fast_charge, vol_cv_charge);
				break;
			case FAST_CHARGE_MODE:
				fast_charge_process();
				break;
			case BATTERY_FAULT_MODE:
				//battery_fault_process();
				break;
			case CHARGE_CV_MODE:
				//charge_cv_process(vol_finish_charge);
				break;
			case CHARGE_FINISH_MODE:
				//charge_finish_process(vol_recharge);
				break;
			case DISCHARGE_MODE:
				//discharge_process(vol_discharge1,vol_discharge2);
				break;
			default:
				break;

		}
	}
}
