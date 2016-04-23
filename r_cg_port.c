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
* File Name    : r_cg_port.c
* Version      : CodeGenerator for RL78/G12 V2.03.02.01 [15 May 2015]
* Device(s)    : R5F1026A
* Tool-Chain   : CCRL
* Description  : This file implements device driver for PORT module.
* Creation Date: 2015/10/09
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
//#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
/*	P1 = _00_Pn3_OUTPUT_0 | _00_Pn4_OUTPUT_0;
	P2 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0;
	P4 = _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0;
	P6 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0;
	PMC1 = _01_PMCn0_NOT_USE | _02_PMCn1_NOT_USE | _04_PMCn2_NOT_USE | _00_PMCn3_DI_ON | _00_PMCn4_DI_ON |
	       _E0_PMC1_DEFAULT;
	PMC4 = _00_PMCn1_DI_ON | _00_PMCn2_DI_ON | _F9_PMC4_DEFAULT;
	ADPC = 0x03; // P20 and P21 as analog input
	PM1 = _01_PMn0_NOT_USE | _02_PMn1_NOT_USE | _04_PMn2_NOT_USE | _00_PMn3_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT |
	      _E0_PM1_DEFAULT;
	PM2 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _F0_PM2_DEFAULT;
	PM4 = _01_PMn0_NOT_USE | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _F8_PM4_DEFAULT;
	PM6 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _FC_PM6_DEFAULT;
*/

	PMC1 = _E0_PMC1_DEFAULT;
	PMC4 = _F9_PMC4_DEFAULT;
	ADPC = 0x03; // P20 and P21 as analog input
	PM1 = 0xE0; // all output
	PM2 = 0xF3; // P20 and P21 as input, P22 and P23 as output
	PM4 = 0xF8; //all output
	PM6 = 0xFC; //all output
	P1 = _08_Pn3_OUTPUT_1 | _10_Pn4_OUTPUT_1 | _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0;
	P2 = _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0;
	P4 = 0x07; // all high
	P6 = 0x03; // all high
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
