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
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G12 V2.03.02.01 [15 May 2015]
* Device(s)    : R5F1026A
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 2015/10/09
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
//#include "r_cg_serial.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
//#include "fsl.h"
//#include "fsl_types.h"
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
extern uint8_t g_intcsi00_flag;                                            /* INTCSI00 flag */
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
    {
        uint32_t read_data = 0;
        float    average = 0;
        uint16_t rx_length = 0;
        uint8_t  rx_buf[RXSIZE] = {0,0,0,0,0,0};
        uint8_t  ret = 0;
        uint8_t  tmp[4] = {0,0,0,0};

        R_CSI00_Start();                                                   /* Enable CSI00 */

        /* ---- Main loop ---- */
        while ( 1 )
        {
            EI();                                                          /* Enable interrupt */
            read_data = (*( __far uint32_t* )READADDR);                     /* Read data from the code flash */

            /* The average of the data of address 0x3BFC to 0x3BFF is calculate ---- */
            tmp[0]   = ( uint8_t )read_data;
            tmp[1]   = ( uint8_t )( read_data >> 8 );
            tmp[2]   = ( uint8_t )( read_data >> 16 );
            tmp[3]   = ( uint8_t )( read_data >> 24 );
            average  = ( ( uint16_t )tmp[0] + ( uint16_t )tmp[1] +
                         ( uint16_t )tmp[2] + ( uint16_t )tmp[3] ) / 4.00;
            LED1     = LED_ON;                                             /* LED1 on */

            if ( average > 0 )
            {
                r_main_led_blink( average );                                /* LED1 blink start */
            }
            else
            {
                /* Do nothing */
            }
        
            P2_bit.no0 = PORT_HIGH;                                        /* Set not busy status */

            /* ---- Wait for INTCSI00 ---- */
            while ( g_intcsi00_flag == 0 )
            {
                HALT();                                                    /* Halt mode */
            }

            DI();                                                          /* Disable interrupt */
            ret = r_csi00_receive_start( &rx_length, rx_buf );                /* Data receive */ 
            r_main_clear_csi_flag();                                         /* Clear CSI interrupt flag */
            if ( average > 0 )
            {
                R_TAU0_Channel0_Stop();                                    /* Stop TAU0 channel0 */                            
            }

            if ( ret == NORMAL_END )
            {
                ret = r_main_packet_analyze( rx_length, rx_buf );             /* Analyze receive data */

                if ( ret == START )
                {
                    ret = r_main_self_execute();                            /* Flash self programming execution */

                    if ( ret != NORMAL_END )
                    {
                        break;
                    }
                    else
                    {
                        /* Do nothing */
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }

        /* ---- Error process ---- */
        LED1 = LED_ON;                                                     /* LED1 on */
        LED2 = LED_ON;                                                     /* LED2 off */

        /* ==== Error loop ==== */
        while ( 1 )
        {
            NOP();
        }
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: r_main_led_blink
* Description  : This function LED1, LED2 control.
* Arguments    : average -
                     Average value of the data of address 0x3BFC to 0x3BFF
* Return Value : None
***********************************************************************************************************************/
void r_main_led_blink( float average )
{
    TDR00 = ( uint16_t )( average * 234.4) ;                               /* Set interval time ( readdata * 10ms ) */
    R_TAU0_Channel0_Start();                                               /* Start TAU0 channel0 */
}

/***********************************************************************************************************************
* Function Name: r_main_packet_analyze
* Description  : This function receive data analyze.
* Arguments    : rxlength -
                     Length of receive data
                 rxbuf -
                     Receive buffer pointer
* Return Value : START -
                     Receive command is START
                 WRITE -
                     Receive command is WRITE
                 END -
                     Receive command is END
                 ERROR -
                     Receive data error
***********************************************************************************************************************/
uint8_t r_main_packet_analyze( uint16_t rx_length, uint8_t *rx_buf )
{
    uint16_t count = 0;
    uint8_t  checksum = 0;
    uint8_t  ret = 0;

    /* ---- Calculation checksum ---- */
    for ( count = 0; count < ( rx_length - 1 ); count++ )
    {
        checksum = (checksum + rx_buf[count]);                              /* A value is added to checksum */
    }

    /* ---- Compare checksum and check command ---- */
    if ( ( checksum == rx_buf[rx_length - 1] ) &&
         ( ((rx_buf[0] == START) || (rx_buf[0] == WRITE)) || (rx_buf[0] == END) ) )
    {
        ret = rx_buf[0];                                                    /* Set return value ( command ) */
    }
    else
    {
        ret = ERROR;                                                       /* Set return value ( error ) */
    }
    return ret;
}

/***********************************************************************************************************************
* Function Name: r_main_self_initialize
* Description  : This function initialize of flash self programming.
* Arguments    : None
* Return Value : FSL_OK -
                     Normal end
                 OTHER -
                     Error
***********************************************************************************************************************/
uint8_t r_main_self_initialize( void )
{
    __far fsl_descriptor_t init_arg;
    uint8_t                ret = 0;

    /* ---- Set argument of FSL_Init() ---- */
    init_arg.fsl_flash_voltage_u08     = FULL_SPEED_MODE;
    init_arg.fsl_frequency_u08         = FREQUENCY_24M;
    init_arg.fsl_auto_status_check_u08 = INTERNAL_MODE;
    ret                               = FSL_Init( &init_arg );              /* Flash self library initialize */

    if ( ret == FSL_OK )
    {
        FSL_Open();                                                        /* Flash self programming start */
        FSL_PrepareFunctions();                                            /* Enables flash function ( normal ) */
    }

    else
    {
        /* Do nothing */
    }
    return ret;
}

/***********************************************************************************************************************
* Function Name: r_main_self_execute
* Description  : This function flash self programming execution.
* Arguments    : None
* Return Value : NORMAL_END -
                     Normal end
                 ERROR -
                     Error
***********************************************************************************************************************/
uint8_t r_main_self_execute( void )
{
    uint8_t ret = 0;

    LED2 = LED_ON;                                                         /* LED2 on */
    ret  = r_main_self_initialize();                                        /* Initialize flash self libraly */

    /* ---- Check initialize result ---- */
    if ( ret == FSL_OK )
    {
        ret = r_main_write_execute( ( uint32_t )WRITEADDR );                /* Write execute */
    }

    LED2 = LED_OFF;                                                        /* LED2 off */
    return ret;
}

/***********************************************************************************************************************
* Function Name: r_main_write_execute
* Description  : This function rewrites from the specified address.
* Arguments    : WriteAddr -
                     Start address
* Return Value : NORMAL_END -
                     Normal end
                 ERROR -
                     Error
***********************************************************************************************************************/
uint8_t r_main_write_execute( uint32_t write_addr )
{
    fsl_write_t write_arg;
    uint16_t    rx_length = 0;
    uint16_t    write_block = 0;
    uint8_t     rx_buf[RXSIZE] = {0,0,0,0,0};
    uint8_t     ret = 0;
    uint8_t     com = 0;
    
    P2_bit.no0 = PORT_HIGH;                                            /* Set not busy status */
    ret  = r_csi00_receive_start( &rx_length, rx_buf );                   /* Data receive */

    if ( ret == NORMAL_END )
    {
        write_block = ( uint16_t )( write_addr / BLOCK_SIZE );           /* Calculation write block */
        ret        = FSL_BlankCheck( write_block );                     /* Blanc check execution */

        /* ---- Check black check result ---- */
        if ( ret == FSL_ERR_BLANKCHECK )
        {
            ret = FSL_Erase( write_block );                             /* Erase execution */
        }
        else
        {
            /* Do nothing */
        }

        if ( ret == FSL_OK )
        {
            com = r_main_packet_analyze( rx_length, rx_buf );             /* Analyze receive data */
        }
        else
        {
            /* Do nothing */
        }

        if ( com == WRITE )
        {
            /* ---- Set argument of FSL_Write() ---- */
            write_arg.fsl_data_buffer_p_u08       = (&rx_buf[1]);
            write_arg.fsl_destination_address_u32 = write_addr;
            write_arg.fsl_word_count_u08          = WRITESIZE;
            ret                                  = FSL_Write
                                                   ( &write_arg );      /* Write execution */

            if ( ret == FSL_OK )
            {
                P2_bit.no0 = PORT_HIGH;                                /* Set not busy status */
                ret  = r_csi00_receive_start( &rx_length,rx_buf );        /* Receive data */ 
            }
            else
            {
                /* Do nothing */
            }

            if ( ret == NORMAL_END )
            {
                com = r_main_packet_analyze( rx_length, rx_buf );        /* Analyze receive data */
            }
            else
            {
                /* Do nothing */
            }
        }
        else
        {
            /* Do nothing */
        }

        /* ---- Check receive command ---- */
        if ( com == END )
        {
            ret = FSL_IVerify( write_block );                           /* Verify execution */
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        /* Do nothing */
    }

    /* ---- Execution result check ---- */
    if ( (com == END) && (ret == FSL_OK) )
    {
        ret = NORMAL_END;
    }
    else
    {
        ret = ERROR;
    }
    return ret;
}

/***********************************************************************************************************************
* Function Name: r_main_csi_uart_flag
* Description  : This function is clear Csi receive interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_main_clear_csi_flag( void )
{
    g_intcsi00_flag = 0;                                               /* Clear g_intcsi00_flag */
}
/* End user code. Do not edit comment generated here */
