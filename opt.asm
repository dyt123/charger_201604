;************************************************************************
; DISCLAIMER
; This software is supplied by Renesas Electronics Corporation and is only
; intended for use with Renesas products. No other uses are authorized. This
; software is owned by Renesas Electronics Corporation and is protected under
; all applicable laws, including copyright laws.
; THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
; THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
; LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
; AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
; TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
; ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
; FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
; ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
; BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
; Renesas reserves the right, without notice, to make changes to this software
; and to discontinue the availability of this software. By using this software,
; you agree to the additional terms and conditions found by accessing the
; following link:
; http://www.renesas.com/disclaimer
;
; Copyright (C) 2015 Renesas Electronics Corporation. All rights reserved.
;************************************************************************/
;************************************************************************
; File Name    : OPT.asm
; Version      : 1.00
; Device(s)    : RL78/G12 (R5F1026A)
; Tool-Chain   : CC-RL V1.01.00
; Description  : Option bytes are set in this file.
; Creation Date: 2015/08/27
;************************************************************************/
.section .option_byte, opt_byte

    .DB	0b01101110       ; WDT function
;         |||||||+--------- WDSTBYON
;         |||||||           0 : stop WDT when in  HALT/STOP mode
;         ||||
;         ||||+++---------- WDCS2-0(WDT overflow time )
;         ||||              111 : 2^16/fIL
;         ||||
;         |||+------------- WDTON(operation of WDT)
;         |||               0 : stop WDT
;         |||
;         |++-------------- WINDOW1-0
;         |                 11 : 100% open
;         |
;         +---------------- WDTINT
;                            0 : not use 75% interrupt

    .DB	0b01010011       ; LVD and RESET pin function
;         ||||||++--------- LVIMDS1-0
;         ||||||            11 : reset mode
;         ||||||
;         +++|++----------- VPOC2-0,LVIS1-0(LVD detect voltage)
;         |                 01000 : 3.75V
;         |
;         +---------------- PORTSELB(usage of RESET/P125 pin)
;                             1 : RESET pin

    .DB	0b11100000       ; HOCO and operarion mode
;         |||+||||--------- must be 0
;         ||+-||||--------- must be 1
;         ||  ||||
;         ||  ++++--------- FRQSEL3-0(HOCO frequency)
;         ||                0000 : 24MHz
;         ||
;         ++--------------- CMODE1-0
;                             11 : high speed main mode

    .DB	0b10000101       ; onchip debug option
;         |++++|+|--------- must be 0
;         |    +-|--------- must be 1
;         |      |
;         +------+--------- OCDENSET,OCDERSD
;                             11 :Enable OCD and not clear falsh when fail

