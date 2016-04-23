#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"

#include "r_cg_timer.h"

volatile int32_t charge_time;
volatile int16_t pulse_charge_high_time;
volatile int16_t pulse_charge_low_time;
volatile uint8_t pulse_charging;


void idle_process(void)
{
	uint16_t cur_vol;

	while(1)
	{
		if(check_voltage(1, 50, ADC_1V25, ABOVE))
		{
			P1_bit.no0 = 1; //Pin17
			delay_nms(1000);//delay 1s
			P4_bit.no0 = 0; //Pin4
			charge_time = 1800; // 30 min
			if(check_voltage(1, 50, ADC_2V7, UNDER) == FALSE) // >2.7V
			{
				if(check_voltage(1, 50, ADC_3V25, UNDER))
				{
					system_mode = FAST_CHARGE_MODE;
				}
				else
				{
					system_mode = CHARGE_END_MODE;
				}
				break;
			}
			else // <=2.7V
			{
				while(charge_time >= 0)
				{
					if(check_voltage(1, 50, ADC_2V7, UNDER)) // <= 2.7V
					{
						delay_nms(1000);
					}
					else // >2.7V
					{
						break;
					}

					if(P13_bit.no7 == 0 || P12_bit.no2 == 0 || P12_bit.no1 == 0) //check Pin6,Pin7,Pin8
					{
						P4_bit.no2 = 0;//Pin2
						P1_bit.no0 = 0;//Pin17
						P1_bit.no1 = 0;//Pin16
						P1_bit.no2 = 0;//Pin15
						P2_bit.no2 = 0;//Pin19
					}
				}
				system_mode = FAST_CHARGE_MODE;
				break;
			}
			
		}
		else //<1.25V
		{
			if(check_voltage(1, 180, ADC_0V5, ABOVE)) 
			{
				delay_nms(3000);
				if(check_voltage(1, 60, ADC_0V5, ABOVE)) 
				{
					P4_bit.no2 = 1; //Pin2
				}
			}
		}
		delay_nms(100);
	}
}


void fast_charge_process(void)
{
	uint8_t charging = 0;
	P1_bit.no2 = 1;//Pin15
	P2_bit.no2 = 1;//Pin19

	charge_time = 86400; // 24H
	while(charge_time >= 0)
	{
		if(check_voltage(1, 50, ADC_3V45, UNDER) == FALSE) //>3.45V
			break;
		delay_nms(10);
	}

	pulse_charge_high_time = 300;//300s
	pulse_charging = PULSE_CHARGING_HIGH;	
	while(charge_time >= 0)
	{
		if(pulse_charging == PULSE_CHARGING_HIGH)
		{
			if(check_voltage(1, 50, ADC_3V45, UNDER))
				break;
		}
		
		if(pulse_charge_high_time <= 0 && pulse_charging == PULSE_CHARGING_HIGH)
		{
			pulse_charge_low_time = 30;
			P1_bit.no0 = 0; //Pin17
			pulse_charging = PULSE_CHARGING_LOW;
		}
		else if(pulse_charge_low_time <= 0 && pulse_charging == PULSE_CHARGING_LOW)
		{
			pulse_charge_high_time = 300;
			P1_bit.no0 = 1; //Pin17
			pulse_charging = PULSE_CHARGING_HIGH;
		}
		else if(pulse_charge_low_time == 10 && pulse_charging == PULSE_CHARGING_LOW)
		{
			if(check_no_battery())
			{
				system_mode = IDLE_MODE;
				return;
			}
		}
		delay_nms(10);
	}

	pulse_charge_high_time = 200;//200s
	P1_bit.no0 = 1; //Pin17
	pulse_charging = PULSE_CHARGING_HIGH;
	charge_time = 21600; //4h
	while(charge_time >= 0)
	{
		if(pulse_charging == PULSE_CHARGING_HIGH)
		{
			if(check_voltage(0, 50, ADC_0V5, UNDER)) //<=0.5V
				break;	
			else 
			{
				if(check_voltage(1, 50, ADC_3V675, UNDER) == FALSE)
				system_mode = CHARGE_END_MODE;
				break;
			}
		}
		
		if(pulse_charge_high_time <= 0 && pulse_charging == PULSE_CHARGING_HIGH)
		{
			pulse_charge_low_time = 30;
			P1_bit.no0 = 0; //Pin17
			pulse_charging = PULSE_CHARGING_LOW;
		}
		else if(pulse_charge_low_time <= 0 && pulse_charging == PULSE_CHARGING_LOW)
		{
			pulse_charge_high_time = 200;
			P1_bit.no0 = 1; //Pin17
			pulse_charging = PULSE_CHARGING_HIGH;
		}
		delay_nms(10);
	}	
	
}

void charge_end_process(void)
{
	pulse_charge_high_time = 200;//3
	P1_bit.no0 = 1; //Pin17
	pulse_charging = PULSE_CHARGING_HIGH;
	P2_bit.no2 = 0; //Pin19=0;
	P4_bit.no0 = 1; //Pin4 = 1;
	P4_bit.no1 = 0; //Pin3 = 0;
	charge_time = 10800; //3h
	while(charge_time >= 0)
	{
		/*if(pulse_charging == PULSE_CHARGING_HIGH)
		{
			if(check_voltage(1, 50, ADC_3V45, UNDER))
				break;
		}*/
		
		if(pulse_charge_high_time <= 0 && pulse_charging == PULSE_CHARGING_HIGH)
		{
			pulse_charge_low_time = 5;
			P1_bit.no0 = 0; //Pin17
			pulse_charging = PULSE_CHARGING_LOW;
		}
		else if(pulse_charge_low_time <= 0 && pulse_charging == PULSE_CHARGING_LOW)
		{
			pulse_charge_high_time = 200;
			P1_bit.no0 = 1; //Pin17
			pulse_charging = PULSE_CHARGING_HIGH;
		}
		delay_nms(10);
	}

	pulse_charge_high_time = 30;//3
	P1_bit.no0 = 1; //Pin17
	pulse_charging = PULSE_CHARGING_HIGH;
	while(1)
	{
		/*if(pulse_charging == PULSE_CHARGING_HIGH)
		{
			if(check_voltage(1, 50, ADC_3V45, UNDER))
				break;
		}*/
		
		if(pulse_charge_high_time <= 0 && pulse_charging == PULSE_CHARGING_HIGH)
		{
			pulse_charge_low_time = 120;
			P1_bit.no0 = 0; //Pin17
			pulse_charging = PULSE_CHARGING_LOW;
		}
		else if(pulse_charge_low_time <= 0 && pulse_charging == PULSE_CHARGING_LOW)
		{
			pulse_charge_high_time = 30;
			P1_bit.no0 = 1; //Pin17
			pulse_charging = PULSE_CHARGING_HIGH;
		}
		delay_nms(10);
	}

}



