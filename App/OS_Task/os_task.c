#include "rtwtypes.h"
#include "os_task.h"
#include "hal_pulse.h"
#include "hal_can.h"
#include "motor_cnm.h"
#include "motor_cnm.h"
#include "iomm.h"
#include "AppLayer_Uds.h"
#include "epp.h"
#include "can_matrix.h"
#include "Rom_checksum.h"





void OSTK_Powerup_Task(void)
{
	EPP_Motor_Init();
	Epp_initialize();
	Rom_Checksum_init();

}



void OSTK_10msTasks_Interrupt(void)
{
	UpdateEPP_State();
	Epp_step();

}

void OSTK_FreeTasks(void)
{


}

void OSTK_1msTasks(void)
{


}

void OSTK_5msTasks(void)
{

	UDSApp_v_g();




}

void OSTK_10msTasks(void)
{
	Cal_Analog_input();
	
	Rom_Checksum_cal_10ms();

}


void OSTK_20msTasks0(void)
{

	CAN_Msg_Lost_Update();
	CAN_Msg_error_Update();

}


void OSTK_20msTasks1(void)
{

	Hal_WatchDog_Service();






}

void OSTK_50msTasks0(void)
{






}


void OSTK_50msTasks1(void)
{




}



void OSTK_50msTasks2(void)
{


}


void OSTK_50msTasks3(void)
{




}


void OSTK_50msTasks4(void)
{




}


void OSTK_100msTasks0(void)
{

	CAN_Msg_100ms_Tasks();

}


void OSTK_100msTasks1(void)
{
	




}



void OSTK_100msTasks2(void)
{




}


void OSTK_100msTasks3(void)
{




}


void OSTK_100msTasks4(void)
{


}



