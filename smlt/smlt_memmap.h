/************************************************************
  Copyright (C), AISpeechTech. Co., Ltd.

  FileName   : aispeech_type.h
  Project    : 
  Module     : 
  Version    : 
  Date       : 2017/02/15
  Author     : Youhai.Jiang
  Document   : 
  Description: 

  Function List :

  History :
  <author>      <time>            <version >        <desc> 
  Youhai.Jiang  2017/02/15         1.00              Create

************************************************************/
#ifndef _SMLT_MEMMAP_H_
#define  _SMLT_MEMKEY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "smlt_common.h"
#include "smlt_cfg.h"


#pragma  pack(1)
typedef struct _Memmory_1_Pra
{
	UINT8_t  Device_Type;
	
	UINT8_t   Device_Box;          
	
	UINT8_t   Device_version[2];      
	
	UINT8_t   reserve_1[3];        
	
	UINT8_t   Device_Switch_Flag;         
 
    UINT8_t   reserve_2;       
	
	UINT8_t   Device_Duplic_Flag;       
	
	UINT8_t   Device_Duplic_Flag_2; 
	
	UINT8_t   reserve_3[5];
	
}Memmory_1_t;

#pragma  pack(1)
typedef struct _Memmory_2_Pra
{
	
	UINT8_t   reserve_1[16];       
	
}Memmory_2_t;

#pragma  pack(1)
typedef struct _Memmory_3_Pra
{
	
	UINT8_t   reserve_1[16];        
	
}Memmory_3_t;

#pragma  pack(1)
typedef struct _Memmory_4_Pra
{

	UINT8_t   reserve_1[16];       
	
}Memmory_4_t;

#pragma  pack(1)
typedef struct _Memmory_5_Pra
{

	
	UINT8_t   reserve_1[16];       
	
}Memmory_5_t;


#pragma  pack(1)
typedef struct _Memmory_6_Pra
{
	UINT8_t   Aux_Push[8];        
	UINT8_t   Aux_Release[8];
	
}Memmory_6_t;


#pragma  pack(1)
typedef struct _Memmory_7_Pra
{
	UINT8_t   Device_Area[12];        
	
	UINT8_t   Device_Jonn_1[4];         
	
}Memmory_7_t; 

#pragma  pack(1)
typedef struct _Memmory_8_Pra
{
	UINT8_t   Device_Jonn_2[8];       
	
	UINT8_t   Device_Set_Logic_Channel_1[8];
	
}Memmory_8_t;


#pragma  pack(1)
typedef struct _Memmory_9_Pra
{
	
	UINT8_t   Device_Set_Logic_Channel_2[4];      
	
	UINT8_t   Device_Max_Level[12];       
		
}Memmory_9_t;


#pragma  pack(1)
typedef struct _Memmory_10_Pra
{
	UINT8_t   reserve_1[12];  
	
	UINT8_t   Device_Switch_On_Delay_Time[4];   
}Memmory_10_t;

#pragma  pack(1)
typedef struct _Memmory_11_Pra
{
	UINT8_t   Device_Switch_On_Delay_Time[8];        
	
	UINT8_t   Device_Switch_Off_Delay_Time[8];        
	
}Memmory_11_t;


#pragma  pack(1)
typedef struct _Memmory_12_Pra
{
	
	UINT8_t   Device_Switch_Off_Delay_Time[4]; 
	
    UINT8_t    Device_Switch_Level[12];       
	
}Memmory_12_t;


#pragma  pack(1)
typedef struct _Memmory_13_Pra
{
	
	UINT8_t   reserve_1[16];        
	
}Memmory_13_t;


#pragma  pack(1)
typedef struct _Memmory_14_Pra
{
	UINT8_t   reserve_1[16];        
	
}Memmory_14_t;


#pragma  pack(1)
typedef struct _Memmory_15_Pra
{
	UINT8_t   reserve_1[16];      
	
}Memmory_15_t;


#pragma  pack(1)
typedef struct _Memmory_16_Pra
{
	UINT8_t   Device_Preset_1[12];       
	
	UINT8_t   Device_Preset_2[4];      
	
}Memmory_16_t;


#pragma  pack(1)
typedef struct _Memmory_17_Pra
{
	UINT8_t   Device_Preset_2[8];           
  
  UINT8_t   Device_Preset_3[8];         
	
}Memmory_17_t;


#pragma  pack(1)
typedef struct _Memmory_18_Pra
{
	UINT8_t   Device_Preset_3[4];         //
	
	UINT8_t   Device_Preset_4[12];         //
	
}Memmory_18_t;


#pragma  pack(1)
typedef struct _Memmory_19_Pra
{
	UINT8_t   Device_Preset_5[12];         //
	
	UINT8_t   Device_Preset_6[4];         //
	
}Memmory_19_t;

#pragma  pack(1)
typedef struct _Memmory_20_Pra
{
	UINT8_t   Device_Preset_6[8];         //
	
	UINT8_t   Device_Preset_7[8];         //
	
}Memmory_20_t;

#pragma  pack(1)
typedef struct _Memmory_21_Pra
{
	UINT8_t   Device_Preset_7[4];         //
	
	UINT8_t   Device_Preset_8[12];         //
	
}Memmory_21_t;


#pragma  pack(1)
typedef struct _Memmory_22_Pra
{
	UINT8_t   Device_Preset_9[12];         //
	
	UINT8_t   Device_Preset_10[4];         //
	
}Memmory_22_t;


#pragma  pack(1)
typedef struct _Memmory_23_Pra
{
	UINT8_t   Device_Preset_10[8];         //
	
	UINT8_t   Device_Preset_11[8];         //
	
}Memmory_23_t;


#pragma  pack(1)
typedef struct _Memmory_24_Pra
{
	UINT8_t   Device_Preset_11[4];         //
	
	UINT8_t   Device_Preset_12[12];         //
	
}Memmory_24_t;

#pragma  pack(1)
typedef struct _Memmory_25_Pra
{
	UINT8_t   Device_Preset_13[12];         //
	
	UINT8_t   Device_Preset_14[4];         //
	
}Memmory_25_t;

#pragma  pack(1)
typedef struct _Memmory_26_Pra
{
	UINT8_t   Device_Preset_14[8];         //
	
	UINT8_t   Device_Preset_15[8];         //
	
}Memmory_26_t;


#pragma  pack(1)
typedef struct _Memmory_27_Pra
{
	UINT8_t   Device_Preset_15[4];         //
	
	UINT8_t   Device_Preset_16[12];         //
	
}Memmory_27_t;

#pragma  pack(1)
typedef struct _Memmory_28_Pra
{
	UINT8_t   level_save[12]; 
	
	UINT8_t   reserve_16[4];         //
		
}Memmory_28_t;


#pragma  pack(1)
typedef struct _Memmory_29_Pra
{ 
	
	UINT8_t   reserve_16[16];         //
	
}Memmory_29_t;

#pragma  pack(1)
typedef struct _Memmory_30_Pra
{ 
	
	UINT8_t   reserve_16[16];         //
	
}Memmory_30_t;

#pragma  pack(1)
typedef struct _Memmory_31_Pra
{ 
	
	UINT8_t   reserve_16[16];         //
	
}Memmory_31_t;

#pragma  pack(1)
typedef struct _Memmory_32_Pra
{ 
	
	UINT8_t   reserve_16[16];         //
	
}Memmory_32_t;

#pragma  pack(1)
typedef struct _Memmory_33_Pra
{ 
	
	UINT8_t   reserve_16[16];         //
	
}Memmory_33_t;


#pragma  pack(1)
typedef struct _Memmory_34_Pra
{ 
	
	UINT8_t   reserve_16[16];         //
	
}Memmory_34_t;

#pragma  pack(1)
typedef struct _Memmory_35_Pra
{ 
	
	UINT8_t   set_save[16];         //
	
}Memmory_35_t;

#pragma  pack(1)
typedef struct _Memmory_36_Pra
{ 
	
	UINT8_t   reserve_16[16];         //
	
}Memmory_36_t;


#pragma  pack(4)
typedef struct _Device_Pra
{
	Memmory_1_t  Memmory_1;
	Memmory_2_t  Memmory_2;
	Memmory_3_t  Memmory_3;
	Memmory_4_t  Memmory_4;
	Memmory_5_t  Memmory_5;
	Memmory_6_t  Memmory_6;
	Memmory_7_t  Memmory_7;
	Memmory_8_t  Memmory_8;
	Memmory_9_t  Memmory_9;
	Memmory_10_t  Memmory_10;
	Memmory_11_t  Memmory_11;
	Memmory_12_t  Memmory_12;
	Memmory_13_t  Memmory_13;
	Memmory_14_t  Memmory_14;
	Memmory_15_t  Memmory_15;
	Memmory_16_t  Memmory_16;
	Memmory_17_t  Memmory_17;
	Memmory_18_t  Memmory_18;
	Memmory_19_t  Memmory_19;
	Memmory_20_t  Memmory_20;
	Memmory_21_t  Memmory_21;
	Memmory_22_t  Memmory_22;
	Memmory_23_t  Memmory_23;
	Memmory_24_t  Memmory_24;
	Memmory_25_t  Memmory_25;
	Memmory_26_t  Memmory_26;
	Memmory_27_t  Memmory_27;
	Memmory_28_t  Memmory_28;
	Memmory_29_t  Memmory_29;
	Memmory_30_t  Memmory_30;
	Memmory_31_t  Memmory_31;
	Memmory_32_t  Memmory_32;
	Memmory_33_t  Memmory_33;
	Memmory_34_t  Memmory_34;
	Memmory_35_t  Memmory_35;
	Memmory_36_t  Memmory_36;
	//Memmory__t  Memmory_29[80];
}Device_Set_Pra_t;        



#ifdef __cplusplus
};
#endif

#endif

