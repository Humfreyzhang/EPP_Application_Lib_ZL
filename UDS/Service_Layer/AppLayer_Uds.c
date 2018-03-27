/*!******************************************************************************************************
*	@file 	AppLayer_Uds.c
*	@brief 	AppLayer_Uds Դ�ļ�
*	@author Matt Zhang
*	@version 1.0
*	@date  2015-9-3
*	@warning  
*                (c) Copyright 2015, KAIT Automotive Technology(Suzhou) Co., Ltd.
*                                       All Rights Reserved
*	@note	
- 
*********************************************************************************************************
*/
#define  APPLAYER_GLOBALS
#include "AppLayer_Uds.h"
#include "DSP2803x_Device.h"
#include "interface_other.h"
#include "DSP2803x_function.h"
#include "interface_file.h"

//#include "F2803x_EEPROM.h"
//#include "EPC_parameter.h"     // DSP28 Headerfile Include File
//#include "EPC_AppECan.h"
//#include "EPC_AppFaultProcess.h"
//#include "EPC_AppSequence.h"
//#include "EPC_AppADC.h"
//#pragma DATA_SECTION(DtcNumb_u24a8_Par,     "EEPROM");
//#pragma DATA_SECTION(DtcStatus_u16a8_Par,     "EEPROM");
#pragma DATA_SECTION(LastDtcStatus_u16a8_Par,     "EEPROM");
//#pragma DATA_SECTION(DtcExtend_u64a8_Par,     "EEPROM");
//#pragma DATA_SECTION(DtcSnapShot_u80a8_Par,     "EEPROM");
#pragma DATA_SECTION(BootTimes_u16_Par,     "EEPROM");
#pragma DATA_SECTION(PifPtcb_u16a16a16_Par,     "EEPROM");
#pragma DATA_SECTION(BootSwRefNumb_u16a10_Par,     "EEPROM");
#pragma DATA_SECTION(ECUPartNumb_u16a6_Par,     "EEPROM");
#pragma DATA_SECTION(SysSupplierId_u16a6_Par,     "EEPROM");
#pragma DATA_SECTION(Vin_u16a17_Par,     "EEPROM");
#pragma DATA_SECTION(EcuHwNumb_u16a6_Par,     "EEPROM");
#pragma DATA_SECTION(EcuHwRefNumb_u16a10_Par,     "EEPROM");
#pragma DATA_SECTION(EcuSwRefNumb_u16a10_Par,     "EEPROM");
#pragma DATA_SECTION(EcuCalSwNumb_u16a6_Par,     "EEPROM");
#pragma DATA_SECTION(EcuNetRefNumb_u16a6_Par,     "EEPROM");
#pragma DATA_SECTION(VehFeature_u16a20_Par,     "EEPROM");
#pragma DATA_SECTION(EcuMData_u16a3_Par,     "EEPROM");
#pragma DATA_SECTION(EcuSupplierSN_u16a10_Par,     "EEPROM");
#pragma DATA_SECTION(PifBlockNumb_u16_Sig,     "EEPROM");


/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/
/*-------------------Crc32У����-----------------------*/
#if 0
unsigned long  crc_32_tab[256] =
{
0X00000000L,  0X04c11db7L,  0X09823b6eL,  0X0d4326d9L,  
0X130476dcL,  0X17c56b6bL,  0X1a864db2L,  0X1e475005L,  
0X2608edb8L,  0X22c9f00fL,  0X2f8ad6d6L,  0X2b4bcb61L,  
0X350c9b64L,  0X31cd86d3L,  0X3c8ea00aL,  0X384fbdbdL,  
0X4c11db70L,  0X48d0c6c7L,  0X4593e01eL,  0X4152fda9L,  
0X5f15adacL,  0X5bd4b01bL,  0X569796c2L,  0X52568b75L,
0X6a1936c8L,  0X6ed82b7fL,  0X639b0da6L,  0X675a1011L,  
0X791d4014L,  0X7ddc5da3L,  0X709f7b7aL,  0X745e66cdL,  
0X9823b6e0L,  0X9ce2ab57L,  0X91a18d8eL,  0X95609039L,  
0X8b27c03cL,  0X8fe6dd8bL,  0X82a5fb52L,  0X8664e6e5L,  
0Xbe2b5b58L,  0Xbaea46efL,  0Xb7a96036L,  0Xb3687d81L,  
0Xad2f2d84L,  0Xa9ee3033L,  0Xa4ad16eaL,  0Xa06c0b5dL,
0Xd4326d90L,  0Xd0f37027L,  0Xddb056feL,  0Xd9714b49L,  
0Xc7361b4cL,  0Xc3f706fbL,  0Xceb42022L,  0Xca753d95L,  
0Xf23a8028L,  0Xf6fb9d9fL,  0Xfbb8bb46L,  0Xff79a6f1L,  
0Xe13ef6f4L,  0Xe5ffeb43L,  0Xe8bccd9aL,  0Xec7dd02dL,  
0X34867077L,  0X30476dc0L,  0X3d044b19L,  0X39c556aeL,  
0X278206abL,  0X23431b1cL,  0X2e003dc5L,  0X2ac12072L,  
0X128e9dcfL,  0X164f8078L,  0X1b0ca6a1L,  0X1fcdbb16L,  
0X018aeb13L,  0X054bf6a4L,  0X0808d07dL,  0X0cc9cdcaL,  
0X7897ab07L,  0X7c56b6b0L,  0X71159069L,  0X75d48ddeL,  
0X6b93dddbL,  0X6f52c06cL,  0X6211e6b5L,  0X66d0fb02L,  
0X5e9f46bfL,  0X5a5e5b08L,  0X571d7dd1L,  0X53dc6066L,
0X4d9b3063L,  0X495a2dd4L,  0X44190b0dL,  0X40d816baL,  
0Xaca5c697L,  0Xa864db20L,  0Xa527fdf9L,  0Xa1e6e04eL,  
0Xbfa1b04bL,  0Xbb60adfcL,  0Xb6238b25L,  0Xb2e29692L,  
0X8aad2b2fL,  0X8e6c3698L,  0X832f1041L,  0X87ee0df6L,  
0X99a95df3L,  0X9d684044L,  0X902b669dL,  0X94ea7b2aL,  
0Xe0b41de7L,  0Xe4750050L,  0Xe9362689L,  0Xedf73b3eL,
0Xf3b06b3bL,  0Xf771768cL,  0Xfa325055L,  0Xfef34de2L,  
0Xc6bcf05fL,  0Xc27dede8L,  0Xcf3ecb31L,  0Xcbffd686L,  
0Xd5b88683L,  0Xd1799b34L,  0Xdc3abdedL,  0Xd8fba05aL,  
0X690ce0eeL,  0X6dcdfd59L,  0X608edb80L,  0X644fc637L,  
0X7a089632L,  0X7ec98b85L,  0X738aad5cL,  0X774bb0ebL,  
0X4f040d56L,  0X4bc510e1L,  0X46863638L,  0X42472b8fL,  
0X5c007b8aL,  0X58c1663dL,  0X558240e4L,  0X51435d53L,  
0X251d3b9eL,  0X21dc2629L,  0X2c9f00f0L,  0X285e1d47L,  
0X36194d42L,  0X32d850f5L,  0X3f9b762cL,  0X3b5a6b9bL,  
0X0315d626L,  0X07d4cb91L,  0X0a97ed48L,  0X0e56f0ffL,  
0X1011a0faL,  0X14d0bd4dL,  0X19939b94L,  0X1d528623L,
0Xf12f560eL,  0Xf5ee4bb9L,  0Xf8ad6d60L,  0Xfc6c70d7L,  
0Xe22b20d2L,  0Xe6ea3d65L,  0Xeba91bbcL,  0Xef68060bL,  
0Xd727bbb6L,  0Xd3e6a601L,  0Xdea580d8L,  0Xda649d6fL,  
0Xc423cd6aL,  0Xc0e2d0ddL,  0Xcda1f604L,  0Xc960ebb3L,  
0Xbd3e8d7eL,  0Xb9ff90c9L,  0Xb4bcb610L,  0Xb07daba7L,  
0Xae3afba2L,  0Xaafbe615L,  0Xa7b8c0ccL,  0Xa379dd7bL,
0X9b3660c6L,  0X9ff77d71L,  0X92b45ba8L,  0X9675461fL,  
0X8832161aL,  0X8cf30badL,  0X81b02d74L,  0X857130c3L,  
0X5d8a9099L,  0X594b8d2eL,  0X5408abf7L,  0X50c9b640L,  
0X4e8ee645L,  0X4a4ffbf2L,  0X470cdd2bL,  0X43cdc09cL,  
0X7b827d21L,  0X7f436096L,  0X7200464fL,  0X76c15bf8L,  
0X68860bfdL,  0X6c47164aL,  0X61043093L,  0X65c52d24L,  
0X119b4be9L,  0X155a565eL,  0X18197087L,  0X1cd86d30L,  
0X029f3d35L,  0X065e2082L,  0X0b1d065bL,  0X0fdc1becL,  
0X3793a651L,  0X3352bbe6L,  0X3e119d3fL,  0X3ad08088L,  
0X2497d08dL,  0X2056cd3aL,  0X2d15ebe3L,  0X29d4f654L,  
0Xc5a92679L,  0Xc1683bceL,  0Xcc2b1d17L,  0Xc8ea00a0L,
0Xd6ad50a5L,  0Xd26c4d12L,  0Xdf2f6bcbL,  0Xdbee767cL,
0Xe3a1cbc1L,  0Xe760d676L,  0Xea23f0afL,  0Xeee2ed18L,
0Xf0a5bd1dL,  0Xf464a0aaL,  0Xf9278673L,  0Xfde69bc4L,
0X89b8fd09L,  0X8d79e0beL,  0X803ac667L,  0X84fbdbd0L,
0X9abc8bd5L,  0X9e7d9662L,  0X933eb0bbL,  0X97ffad0cL,
0Xafb010b1L,  0Xab710d06L,  0Xa6322bdfL,  0Xa2f33668L,
0Xbcb4666dL,  0Xb8757bdaL,  0Xb5365d03L,  0Xb1f740b4L

};
#endif


/*------------F1A0��F1A1��F1A2����ͨ��ˢ�³�����¡�����ݿͻ���Ҫ�������޸����������ֵ����������DID��ο�h�ļ�-----------------------*/
//ASCII��5��BCD
//20160309�����ṩ
//����ţ�C0006858400��Ӳ����F191��E6900610001,�����F1A0��E6900620001���궨�ţ�E6900630001,F18A:P0110900000

uint16_T ECUPartNumb_u16a6_Par[3]={0x43,0x00,0x06,0x85,0x84,0x00};		//C0006858400   LJH0226
uint16_T EcuHwNumb_u16a6_Par[3]={0x45,0x69,0x00,0x61,0x00,0x01};			//Ӳ����
uint16_T EcuCalSwNumb_u16a6_Par[3]={0x45,0x69,0x00,0x63,0x00,0x01};		//�궨��
uint16_T SysSupplierId_u16a6_Par[3]={0x50,0x01,0x10,0x09,0x00,0x00};


static uint16_T  PifBlockNumb_u16_Sig;/*F110-F11Fд������ֵ*/

//static uint8_T   WrDidBackUp_Sig[2]={0};/*���ڼ�¼WrId*/
static uint32_T  Level1Mask_u32_Sig=0xC66969C6;/*1����������*/
static uint32_T  Level2Mask_u32_Sig=0x69F6F669;/*2����������*/
static uint32_T  Seed_u32_Sig=0;/*32λSeed*/
//static uint16_T  BootEepFlag_u16_Par;/*boot����д��EEPROM��־*/
//static uint16_T  AppEepFlag_u16_Par;/*AppCode����д��EEPROM��־*/
/*----------------ԭ����Ϣ-----------------*/
static uint8_T   AdrType_u8_Sig;/*Ѱַ��ʽ*/
static uint8_T   Mtype_u8_Sig;/*Ѱַ��ʽ*/
static uint8_T   SI_u8_Tmp;/*�����*/
static uint8_T   NegRsp_u8_Sig;/*�����Ӧ�����*/
static uint8_T   DefSub_u8_Tmp;/*�����ж��Ƿ�ΪSub���ܵķ���*/
static uint8_T   RspFmt_u8_Sig;/*��Ӧģʽ*/
static uint8_T   supPosRspMsgIndBit_u8_Tmp;/*��ȡ����Sub-funtion�����λ�����ж��Ƿ�Ҫ��Ӧ*/
static uint16_T  RevMsgLen_u16_Sig;/*���յĳ���*/
static uint16_T  RspMsgLen_u16_Sig;/*��Ӧ�ĳ���*/
/*----------------Resetģʽ����-----------------*/
static uint8_T   ResetMode_u8_Sig;/*Resetģʽ*/
/*----------------���ܷ�������-----------------*/
static uint8_T   LockMode_u8_Sig=0;/*����״̬*/
static uint16_T  UnlockLimitTime_u16_Sig;/*���ܴ������*/
static uint8_T   UnLockTimeOver_u8_Sig;/*���ܳ��ޱ�־*/
static uint8_T   ScurReqTimes_u8_Sig=0;/*���ڼ�¼27�����Ƿ������*/
/*----------------AppLayer Time Control-----------------*/
static uint8_T   P2CntStart_u8_Sig=0 ;/*50ms��ʱ������ʼ��־*/
static uint8_T   P2FlexCntStart_u8_Sig=0;/*5000ms��ʱ������ʼ��־*/
static uint16_T  P2Sever_u16_Sig=0;/*50ms��ʱ������*/
static uint16_T  P2FlexSever_u16_Sig=0;/*5000ms��ʱ������*/
static uint16_T  S3Sever_u16_Sig=0;/*5000ms��Ĭ�ϻỰģʽ��ʱ*/
static uint32_T  Secur_u32_Sig=0;/*���ܱ��������ʱ��*/
/*----------------Mem Data-----------------*/
static uint32_T  MemAdr_u32_Sig=0;
static uint16_T  MemDataLen_u16_Sig=0;
static uint8_T   WMemDataFLag_u8_Sig=0;/*дMEM���ݱ�־λ*/
static uint8_T   RMemDataFLag_u8_Sig=0;/*��MEM���ݱ�־λ*/
static uint8_T   BackUpMemInfor_u8_Sig[6];/*��¼MEM��Ϣ����*/
static uint16_T  BackUpPosLen_u16_Sig;/*��¼����Ӧ�ĳ���*/
static uint16_T  MemData_u16_Sig[120];/*��дMEM����Buffer*/
static uint8_T   adrLenFmtId_u8_Sig;/*��ַ��ʽ����*/
static uint8_T   BackSub_u8_Sig;/*Sub_Funtion����*/
static uint32_T  crcData_u32_Sig;/*CrcУ��ֵ*/
static uint8_T   BackUpExit_u8_Sig=0 ;/*�����˳���־��¼*/
/*----------------BootLoader DownLoad Code Para-----------------*/
#if APP_CODE==0
static uint8_T    WFlashFlag_u8_Sig=0;/*дFlash��־λ*/
static uint8_T    BlockCnt_u8_Sig=0 ;/*�������*/
static uint8_T    ReqTranExitStatus_u8_Sig=0;/*����״̬*/
static uint8_T    EndHex_u8_Sig=0;/*Hex����־λ*/

static uint8_T    TranBlock_u8_Sig=0;/*Block�ļ���*/
static uint8_T    TranBuff_u8_Sig[500];/*Block���ݴ��Buffer*/
static uint16_T   FlashWBuffer_u16_Sig[200];/*дFlash����Buffer*/
static uint16_T   BootWFalshLen_u16_Sig=0;/*дFlash���ݳ���*/
static uint32_T   TransferLen_u32_Sig=0;/*���͵ĳ���*/
static uint32_T   WriteMemLen_u32_Sig=0;/*����д��ַ����*/
static uint32_T   TranRevCnt_u32_Sig=0;/*дFlash����Buffer��������*/
static uint32_T   WFlashAdr_u32_Sig=0;/*дFlash��ʼ��ַ*/
static uint32_T   FlashLen_u32_Sig=0;/*дFlash�������ݵĳ�����ֵ*/
#endif

static uint8_T    EraseFStatus_u8_Sg=0;/*����Flash״̬*/
static uint8_T    EraseABStatus_u8_Sg=0;/*����Flash״̬*/
static uint8_T    EFlashFlag_u8_Sig=0;/*����Flash��־λ*/
static uint8_T    EraseDid_u8_Sig[2];/*����Flash��־λ*/
static uint16_T   EraseSector_u8_Sig=0;/*������Flash����*/
/*----------------Flash define-----------------*/
static uint16_T   SIS_u16_Sig;/*����������*/
static uint16_T   SCS_u16_Sig;/*���������*/

/*----------------EEPROM Marks-----------------*/
#if APP_CODE==1
static uint8_T    DtcEep_u8_Sig;/*DTCдEEPROM��־λ*/
#endif
//static uint8_T    DidEep_u8_Sig;/*DidдEEPROM��־λ*/
static uint8_T    SvfEep_u8_Sig;/*SVFдEEPROM��־λ*/


/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/
#if APP_CODE==1
static void   DtcInit_v_s(void);/*DTC��ʼ������*/
static void   Progam_v_s();/*AppToBoot����*/
#endif

static uint16_T EraseSector_v_s(uint16_T sector);/*����Flash��������*/
static uint8_T  ResponseMechanism_v_s() ;/*�ж��Ƿ��Ӧ����*/
/*
*********************************************************************************************************
*                                             C ENTRY POINT
*********************************************************************************************************
*/

void Service_RamdomGen(void)
{
	uint32_T temp1, temp2, temp3;

	temp1 = IO_Get_SystemTimerValue();
	temp2 = Seed_u32_Sig^ 0xA55A5AA5 + (temp1*65536)^0x5AA5A5A5 + temp1;
	temp3 = temp2 + Seed_u32_Sig;
	Seed_u32_Sig = temp3;
}


/*!******************************************************************************************************
*	@fn void UdsInit_v_g(void)
*	@brief	Uds��ʼ������
*	@author Matt Zhang
*	@param[in]	void
*	@return	void
*	@note
*	Uds����㼰Ӧ�ò����г�ʼ��
*********************************************************************************************************
*/
void UdsInit_v_g(void)
{	
	

NetworkLayerServices_GF_initialize();/*Network��ʼ��*/
Req_Msg.IndReceiveMsg_u8_Sig=&UdsIndication.MessageData[0];/*ָ���ʼ��*/
Rsp_Msg.ReqSendMsg_u8_Tmp=&UdsRequest.MessageData[0];/*ָ���ʼ��*/
RequestCmd_u8_Sig          = 0;
VehicleSpeed_u16_Sig       = 0;
EngineSpeed_u16_Sig        = 0;


AdrType_u8_Sig             = 0;
Mtype_u8_Sig               = 0;
WrCheckSum_u16_Sig         = 0;
RspMsgLen_u16_Sig          = 0;
ResetMode_u8_Sig           = 0;
SI_u8_Tmp                  = 0;
NegRsp_u8_Sig              = 0;
DefSub_u8_Tmp              = 0;
RspFmt_u8_Sig              = 0;
RevMsgLen_u16_Sig          = 0;
OldSessionMode_u8_Sig      = DEFAULT_SESSION;
SessionMode_u8_Sig         = DEFAULT_SESSION;
supPosRspMsgIndBit_u8_Tmp  = 0;

LockMode_u8_Sig            = Lock;
UnlockLimitTime_u16_Sig    = 0;
UnLockTimeOver_u8_Sig      = 0;


NormalComTx_u8_Sig         = 1;
NormalComRx_u8_Sig         = 1;
NetWorkComTx_u8_Sig        = 1;
NetWorkComRx_u8_Sig        = 1;

P2FlexCntStart_u8_Sig      = 0;
P2Sever_u16_Sig            = 0;
P2FlexSever_u16_Sig        = 0;
S3Sever_u16_Sig            = 0;
P2CntStart_u8_Sig          = 0;
Secur_u32_Sig              = 0;
ScurReqTimes_u8_Sig        = 0;
BackSub_u8_Sig             = 0;
#if APP_CODE==0
CANNumb_u8_Sig             = 0;
CANIndex_u8_Sig            = 0;
CANGetOut_u8_Sig           = 0;
Jump_u8_Sig                = 0;
BootApp_u8_Sig             = 0;
BlockCnt_u8_Sig            = 1;
TransferLen_u32_Sig        = 0;
WriteMemLen_u32_Sig        = 0;
ReqTranExitStatus_u8_Sig   = 0;
TranRevCnt_u32_Sig         = 0;
WFlashFlag_u8_Sig          = 0;
FC_RecStatus_u8_Sig=0;
#endif
#if APP_CODE==1
DtcEep_u8_Sig              = 0;
#endif
EepRomTimes_u8_Sig		   = 0;
PEF_u16_Par                = 0;
SVF_u16_Par                = 0;
//BootTimes_u16_Par          = 0;
SIS_u16_Sig                = 1;
SCS_u16_Sig                = 1;
//DidEep_u8_Sig              = 0;
PefEep_u8_Sig              = 0;
SvfEep_u8_Sig              = 0;

WMemDataFLag_u8_Sig        = 0;
RMemDataFLag_u8_Sig        = 0;
EppStatus_u8_Sig           = 0;
AsTime_Limited_u16_Par     = AS_TIME;
BsTime_Limited_u16_Par     = BS_TIME;
CrTime_Limited_u16_Par     = CR_TIME;
UDS_Timeout_u8_Sig         = 0;
CFCount_u8_Sig             = 0;
SFLength_Ovrn_u8_Sig       = 0;
CANLength_u8_Sig           = 0;
FrameSequ_u8_Sig           = 0;
FrameErr_u8_Sig            = 0;
UDStick_u8_Par             = CODE_CYCLE;

//PifBlockNumb_u16_Sig       = 0;
#if APP_CODE==1
STminCoef_u8_Par           = 1;
STmin_u8_Par               = 0x14;
#else
STminCoef_u8_Par           = CODECEF;
STmin_u8_Par               = 0x01;
#endif

#if APP_CODE==1
DtcOnOff_u8_Sig           = DTCSETTING_ON;
DtcInit_v_s();/*DTC��ʼ��*/
#endif
//ReadData_v_g();/*��ȡEEPROM*/

#if APP_CODE==1
DtcBackFlashInit_v_g();/*DTCEEPROM���ʼ��*/
#endif


}
/*!******************************************************************************************************
*	@fn uint8_T AppConFrimNet_v_g(USDATACONFIRM *ConFirmPdu)
*	@brief	Udsȷ��ԭ�ﺯ��
*	@author Matt Zhang
*	@param[in]	ConFirmPdu �����ȷ��ԭ��ṹ��
*	@return	uint8_T
*	@note 
*	��������ظ�ȷ�Ϻ��жϻỰģʽ
*********************************************************************************************************
*/
uint8_T AppConFrimNet_v_g(USDATACONFIRM *ConFirmPdu)
{
  /*-------------------�жϴ˴εĻ�Ӧ�ǲ��ǳɹ����ҷ����ǲ��ǻỰģʽ----------------------*/
  if(ConFirmPdu->N_Result==N_OK && SI_u8_Tmp==DIAGNOSTIC_SESSION_CONTROL && RspFmt_u8_Sig==POS_RSP) 
  {
    LockMode_u8_Sig=Lock;
  }
  /*-------------------�жϴ˴εĻ�Ӧ�ǲ��ǳɹ������ϵĻỰģʽ�͵�ǰ�Ựģʽ�Ƿ�һ��----------------------*/
  if(ConFirmPdu->N_Result==N_OK && OldSessionMode_u8_Sig!=SessionMode_u8_Sig && RspFmt_u8_Sig==POS_RSP) 
  {
    LockMode_u8_Sig=Lock;
    OldSessionMode_u8_Sig=SessionMode_u8_Sig;
  } 
  
  return 1;
}
/*!******************************************************************************************************
*	@fn	void AppRevNetData_v_g(USDATAINDICATION *NetPdu ,REQ_A_PDU AppReqPud)
*	@brief	�����������ݺ�Ӧ�ò㽻������
*	@author Matt Zhang
*	@param[in]	*NetPdu ��������ԭ��ṹ�����  ��AppReqPudӦ�ò�ṹ�����
*	@return	void
*	@note 
- ��������ȡ���������ݸ�Ӧ�ò�
*********************************************************************************************************
*/
void AppRevNetData_v_g(USDATAINDICATION *NetPdu ,REQ_A_PDU AppReqPud)     
{
  if(NetPdu->Mtype==Mtype_Diagnostics && NetPdu->N_Result==N_OK)/*�ж���Ϸ�ʽ�����ݽ����Ƿ�OK*/
   {
     Mtype_u8_Sig=Mtype_Diagnostics;/*��Ϸ�ʽ��ֵ*/
     
   }
   if(NetPdu->Mtype==Mtype_Rdiagnostics && NetPdu->N_Result==N_OK) {/*�ж���Ϸ�ʽ�����ݽ����Ƿ�OK*/
   
     AppReqPud.A_RA      =NetPdu->N_AE; /*���ص�ַ��ֵ*/
     Mtype_u8_Sig        =Mtype_Rdiagnostics;/*��Ϸ�ʽ��ֵ*/
   }
   
  if(NetPdu->N_Result==N_OK) {/*�жϽ��յ������Ƿ�OK*/
     
     P2CntStart_u8_Sig     =1;/*��Ӧʱ���ʱ*/
     
     AppReqPud.A_TA_type =NetPdu->N_TAtype; /*��ȡѰַ��ʽ��Ϣ*/
     AdrType_u8_Sig      =AppReqPud.A_TA_type; /*��ȡѰַ��ʽ��Ϣ*/
     AppReqPud.A_SA      =NetPdu->N_SA;/*Դ��ַ��Ϣ*/
     AppReqPud.A_TA      =NetPdu->N_TA; /*Ŀ���ַ��Ϣ*/
     
     AppReqPud.A_PLength   =NetPdu->Length; /*��ȡ���ݳ���*/
     RevMsgLen_u16_Sig   =AppReqPud.A_PLength; /*��ȡ���ݳ���*/
   
     AppReqPud.IndReceiveMsg_u8_Sig=&NetPdu->MessageData[0];/*���ݸ�ֵ*/
     
     RspPduAdr_v_g(AppReqPud,&Rsp_Msg);   /*��ַ��Ϣ����*/
  }
}

/*!******************************************************************************************************
*	@fn	void RspPduAdr_v_g(REQ_A_PDU AppReqPdu,RSP_A_PDU *AppRspPdu)
*	@brief	���������ĵ�ַת���ɻ�Ӧ����ĵ�ַ����
*	@author Matt Zhang
*	@param[in]	*AppRspPdu Ӧ�ò��Ӧ����ṹ��  ��AppReqPudӦ�ò�����ṹ�����
*	@return	void
*	@note 
-
*********************************************************************************************************
*/
void RspPduAdr_v_g(REQ_A_PDU AppReqPdu,RSP_A_PDU *AppRspPdu)
{
 AppRspPdu->A_SA      =AppReqPdu.A_TA;  /*��Ŀ���ַ��ֵ����Ӧ���ĵ�Դ��ַ*/
 AppRspPdu->A_TA      =AppReqPdu.A_SA;  /*��Դ��ַ��ֵ����Ӧ���ĵ�Ŀ���ַ*/
 AppRspPdu->A_TA_type =AppReqPdu.A_TA_type;/*Ѱַ��ʽ��ֵ*/
 if(Mtype_u8_Sig==Mtype_Rdiagnostics) /*�ж��Ƿ�ΪԶ������*/
 {
  AppRspPdu->A_RA=AppReqPdu.A_RA; /*�м����ظ�ֵ*/
 } 
 
}

/*!******************************************************************************************************
*	@fn	void AppReqNetSend_v_g(RSP_A_PDU AppRspPdu,USDATAREQUEST *AppToNet)
*	@brief	��Ӧ�ò��Ӧ���������������㣬��������㷢������
*	@author Matt Zhang
*	@param[in]	AppRspPdu Ӧ�ò��Ӧ����ṹ��  ��AppToNet������Ӧ����ṹ��
*	@return	void
*	@note 
-
*********************************************************************************************************
*/
void AppReqNetSend_v_g(RSP_A_PDU AppRspPdu,USDATAREQUEST *AppToNet)
{                                                                                            
  AppToNet->N_SA        =AppRspPdu.A_SA;/*Դ��ַ��ֵ*/
  AppToNet->N_TA        =AppRspPdu.A_TA;/*Ŀ���ַ��ֵ*/
  AppToNet->N_TAtype    =AppRspPdu.A_TA_type;/*Ѱַ��ʽ��ֵ*/
  AppRspPdu.A_PLength  =RspMsgLen_u16_Sig;/*���ȸ�ֵ*/
 
 
 if(Mtype_u8_Sig==Mtype_Rdiagnostics) /*�ж��Ƿ�ΪԶ������*/
 { 
  AppToNet->Mtype =Mtype_Rdiagnostics;
  AppToNet->N_AE  =AppRspPdu.A_RA;/*�м����ظ�ֵ*/
 }
 else
 {
  AppToNet->Mtype =Mtype_Diagnostics;
 }
 
   /*-------------------�����Ӧ��ֵ----------------------*/
 if(RspFmt_u8_Sig==NEG_RSP) 
 {
   AppRspPdu.A_NR_SI= NR_SI;
   AppRspPdu.A_SI   = SI_u8_Tmp;
   __byte(&AppToNet->MessageData[0], LSB)=AppRspPdu.A_NR_SI;
   __byte(&AppToNet->MessageData[0], MSB)=AppRspPdu.A_SI;
   __byte(&AppToNet->MessageData[1], LSB)=NegRsp_u8_Sig;
   AppToNet->Length=AppRspPdu.A_PLength+1;
 } 
 /*-------------------�����Ӧ��ֵ----------------------*/
 if(RspFmt_u8_Sig==POS_RSP)
 {
   AppRspPdu.A_SI   = SI_u8_Tmp+0x40;
   AppToNet->Length=AppRspPdu.A_PLength+1;
   __byte(&AppToNet->MessageData[0], LSB)= AppRspPdu.A_SI;
 } 
 
 RequestCmd_u8_Sig=APPTONET_SENDOK;/*��������㷢�ͱ�־λ*/

 if(P2CntStart_u8_Sig==1)/*�ж��Ƿ�һ��ʼ��ʱ*/
 {
    P2CntStart_u8_Sig = 0;
 }
 
 if(P2FlexCntStart_u8_Sig==1)/*�ж��Ƿ�һ��ʼ��ʱ*/
 {
 	P2FlexCntStart_u8_Sig = 0;
 }

}

/*!******************************************************************************************************
*	@fn	void DiagnosticSessionControl_v_g(BYTEPTR RevData)
*	@brief	�Ựģʽ������
*	@author Matt Zhang
*	@param[in]	RevDataΪӦ����������ָ��
*	@return	void
*	@note 
-
*********************************************************************************************************
*/
void DiagnosticSessionControl_v_g(BYTEPTR RevData) 
 {
   uint8_T subFunction;
   /*---------------��ȡ������ֵ----------------*/
   subFunction=__byte(RevData, MSB);/*sub_funtion��ֵ*/
   RspFmt_u8_Sig=POS_RSP; /*��Ӧ���͸�ֵ*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*��Ӧ״̬��ֵ*/
   subFunction=subFunction&0x7F;/*Sub_Funtionȥ��λ����*/
   SI_u8_Tmp=DIAGNOSTIC_SESSION_CONTROL;/*Sub_Funtionȥ��λ����*/
   OldSessionMode_u8_Sig = SessionMode_u8_Sig;/*��ǰ�Ựģʽ��ֵ���ϵĻỰģʽ*/
   DefSub_u8_Tmp=0x01;/*Sub�����־λ��1*/
  /*--------------����Ӧ���ݸ�ֵ----------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;
   //Rsp_Msg.ReqSendMsg_u8_Tmp [2]=00;
   //Rsp_Msg.ReqSendMsg_u8_Tmp [3]=0x32;
   //Rsp_Msg.ReqSendMsg_u8_Tmp [4]=0x01;
   //Rsp_Msg.ReqSendMsg_u8_Tmp [5]=0xF4;
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], LSB, 0x00);
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], MSB, 0x32);
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], LSB, 0x01);
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], MSB, 0xF4);

   /*----------------Len Nor Right--------------*/
   if(RevMsgLen_u16_Sig!=2)/*���Ȳ����������ĳ���*/ 
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/  
   } 
   /*----------------SubFun Not Support--------------*/
   if((subFunction<0x01 || subFunction>=0x04) &&RspFmt_u8_Sig!=NEG_RSP)/*��֧�ֵ�Sub-Function*/
   {
     RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR; /*Sub��֧�ִ�����0x12*/
   }
   /*0x01  Default Session; 0x02  Programming Session; 0x03  Extend Session*/
   if(subFunction==DEFAULT_SESSION && RspFmt_u8_Sig!=NEG_RSP)/*�ж������Ƿ�ΪĬ�ϻỰ*/
   {
      SessionMode_u8_Sig= DEFAULT_SESSION;/*�Ựģʽ��ֵ*/
      NormalComTx_u8_Sig = 1;/*��ͨ�ŷ���*/
      NormalComRx_u8_Sig = 1;/*��ͨ�Ž���*/
   
   } 
   if(subFunction==PROGRANMMING_SESSION && RspFmt_u8_Sig!=NEG_RSP) {/*�ж������Ƿ�Ϊ��̻Ự*/
#if APP_CODE==0
      SessionMode_u8_Sig = PROGRANMMING_SESSION;/*�Ựģʽ��ֵ*/
      NormalComTx_u8_Sig = 1;/*��ͨ�ŷ���*/
      NormalComRx_u8_Sig = 1;/*��ͨ�Ž���*/
#else
      PEF_u16_Par = 1;/*AppToBoot��λ*/
      PefEep_u8_Sig=1;/*дEEPROM��־λ*/
#endif
	 unClearRam.reset_cnt = 0;
     unClearRam.Pattern[0] = 0x3223;
	 unClearRam.Pattern[1] = 0x5AA5;
	 ResetMode_u8_Sig = SW_RESET;

   }
   
   if(subFunction==EXTEND_SESSION && RspFmt_u8_Sig!=NEG_RSP) {/*�ж������Ƿ�Ϊ��չ�Ự*/
      SessionMode_u8_Sig= EXTEND_SESSION;/*�Ựģʽ��ֵ*/
   }
   
   if(SessionMode_u8_Sig!=OldSessionMode_u8_Sig && supPosRspMsgIndBit_u8_Tmp==0x80)
   {
	   LockMode_u8_Sig=Lock;/*�Ựģʽ�л��������*/

   }

   if (RspFmt_u8_Sig==NEG_RSP  ) /*�жϻ�Ӧ�����Ƿ��Ǹ����Ӧ*/
   {
     RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
   } 
   else {
     RspMsgLen_u16_Sig=5;/*�������ݵĳ���*/
   } 
 }
/*!******************************************************************************************************
*	@fn	void EcuReset_v_g(BYTEPTR RevData)
*	@brief	��λ������
*	@author Matt Zhang
*	@param[in]	RevDataΪӦ����������ָ��
*	@return	void
*	@note 
-
*********************************************************************************************************
*/
void EcuReset_v_g(BYTEPTR RevData) 
 {
   uint8_T subFunction;
   /*----------------��ȡ������ֵ--------------*/
   subFunction=__byte(RevData, MSB);/*sub_funtion��ֵ*/
   RspFmt_u8_Sig=POS_RSP; /*��Ӧ���͸�ֵ*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*��Ӧ״̬��ֵ*/
   subFunction=subFunction&0x7F;/*Sub_Funtionȥ��λ����*/
   SI_u8_Tmp=ECU_RESET;
   DefSub_u8_Tmp=0x01;/*Sub�����־λ��1*/
   /*--------------����Ӧ���ݸ�ֵ----------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;
   
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
   /*----------------Len Nor Right--------------*/
   if(RevMsgLen_u16_Sig!=2)
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=CMD_LENGTH_ERR;    /*���Ȳ��Դ�����0x13*/
   }
   /*----------------SubFun Not Support--------------*/ 
   if((subFunction<HARD_RESET||subFunction>RAPIDSHUTDOWN_DISABLE)&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR; /*Sub������0x12*/
   	
   }
   /*----------------SeCur Level1 UnLock Err--------------*/ 
   if(LockMode_u8_Sig!=UnLock_Level &&  SessionMode_u8_Sig==EXTEND_SESSION && AdrType_u8_Sig==TAtype_phiscal && RspFmt_u8_Sig!=NEG_RSP)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*��ȫ��ͨ��0x33*/
   	
   }
   /*----------------SeCur Level2 UnLock Err--------------*/ 
   if(LockMode_u8_Sig!=UnLock_Level2 &&  SessionMode_u8_Sig==PROGRANMMING_SESSION && AdrType_u8_Sig==TAtype_phiscal && RspFmt_u8_Sig!=NEG_RSP)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*��ȫ��ͨ��0x33*/
   	
   }
   
   /*-----------------------------���ӹ��ܽ����ж�--------------------------------*/
   
   /*0x01  hard Reset*/
   if(subFunction==HARD_RESET && RspFmt_u8_Sig!=NEG_RSP )
   {
   ResetMode_u8_Sig = HARD_RESET;/*��λ���͸�ֵ*/
   } 
   /*0x02  Key_Off_On Reset*/
   else if(subFunction==KEYOFFON_RESET && RspFmt_u8_Sig!=NEG_RSP) {
   ResetMode_u8_Sig = KEYOFFON_RESET;/*��λ���͸�ֵ*/
   }
   /*0x03  Sw Reset*/
   else if(subFunction==SW_RESET && RspFmt_u8_Sig!=NEG_RSP) {

	ResetMode_u8_Sig=SW_RESET;/*��λ���͸�ֵ*/
   }
   /*0x04  RapidShutDown enable*/
   else if(subFunction==RAPIDSHUTDOWN_ENABLE && RspFmt_u8_Sig!=NEG_RSP)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CONDITION_NOTSURRORT_ERR;  /*���������������0x22*/
   }
   /*0x05  RapidShutDown disable*/
   else if(subFunction==RAPIDSHUTDOWN_DISABLE && RspFmt_u8_Sig!=NEG_RSP)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CONDITION_NOTSURRORT_ERR;  /*���������������0x22*/
   } 
   else {
    
   }
   
   if(RspFmt_u8_Sig==NEG_RSP  )  /*�жϻ�Ӧ�����Ƿ��Ǹ����Ӧ*/
   {
     RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
   } 
   else {
     RspMsgLen_u16_Sig=1;/*�������ݵĳ���*/
   }
 }
/*!******************************************************************************************************
*	@fn	void SecurityAccess_v_g(BYTEPTR RevData)
*	@brief ������ܷ�����
*	@author Matt Zhang
*	@param[in]	RevDataΪӦ����������ָ��
*	@return	void
*	@note 
-
*********************************************************************************************************
*/
void SecurityAccess_v_g(BYTEPTR RevData)
 {

   static uint8_T   seedReqmrk=0;
   static uint32_T  TestetKey;/*����Ƿ��͵�Keyֵ*/
   static uint32_T  EcuKey=0;/*ECU�����Keyֵ*/
   static uint8_T   seedSub_u8_Tmp;
   uint8_T subFunction;
   /*--------------��ȡ������ֵ-----------*/
   subFunction=__byte(RevData, MSB);/*sub_funtion��ֵ*/
   RspFmt_u8_Sig=POS_RSP; /*��Ӧ���͸�ֵ*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*��Ӧ״̬��ֵ*/
   subFunction=subFunction&0x7F;/*Sub_Funtionȥ��λ����*/
   SI_u8_Tmp=SECURITY_ACCESS;
   DefSub_u8_Tmp=0x01;/*Sub�����־λ��1*/
   /*--------------����Ӧ���ݸ�ֵ----------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction; 
   
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
   /*----------------Session Not Support--------------*/ 
   if(SessionMode_u8_Sig==DEFAULT_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*�Ựģʽ��֧�ִ�����0x7F*/
   }
   /*----------------Len Err--------------*/ 
   if((subFunction&0x01)==0x01 && RevMsgLen_u16_Sig!=2 && RspFmt_u8_Sig!=NEG_RSP)/*���Ȳ����������ĳ���*/ 
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/  
   } 
   /*----------------subFun Err--------------*/ 
   if(subFunction!=0x01 && subFunction!=0x05  \
   &&subFunction!=0x02 && subFunction!=0x06 &&  RspFmt_u8_Sig!=NEG_RSP )
   {
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR;  /*sub��֧�ִ�����0x12*/
   	
   }
    /*----------------Session Not Support Sub--------------*/ 
   if(SessionMode_u8_Sig!=EXTEND_SESSION && (subFunction==01||subFunction==0x09||subFunction==02||subFunction==0x0A)&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSION_SUB_NOTSUPPROT_ERR; /*sub��֧�ִ�����0x12*/
   }
   
   /*----------------Session Not Support Sub--------------*/ 
   if(SessionMode_u8_Sig!=PROGRANMMING_SESSION && (subFunction==0x05||subFunction==0x06)&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSION_SUB_NOTSUPPROT_ERR;  /*sub��֧�ִ�����0x12*/
   }
   /*----------------Sequence Err--------------*/
   if(seedReqmrk==0 &&(subFunction==0x06 ||subFunction==02||subFunction==0x0A ) && RspFmt_u8_Sig!=NEG_RSP) {
      RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=ORDER_ERR;  /*˳����������0x24*/
   }
   if((subFunction&0x01)==0x00 &&seedReqmrk==1&& ((seedSub_u8_Tmp ==0x01 &&subFunction!=0x02 )||(seedSub_u8_Tmp==0x05 &&subFunction!=0x06 ) ||(seedSub_u8_Tmp ==0x09 &&subFunction!=0x0A ))&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=ORDER_ERR;  /*˳����������0x24*/
   }  
   /*----------------Key Frame Len Err--------------*/
   if((subFunction&0x01)==0x00 && RevMsgLen_u16_Sig!=6 && RspFmt_u8_Sig!=NEG_RSP)/*���Ȳ����������ĳ���*/ 
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=KEY_ERR;  /*���Ȳ��Դ�����0x35*/  
   } 
   /*----------------SeedKey OverTime--------------*/
   if(ScurReqTimes_u8_Sig==1 && UnLockTimeOver_u8_Sig==1 &&\
    UnlockLimitTime_u16_Sig==SEED_KEY_TIMES && RspFmt_u8_Sig!=NEG_RSP)
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=UNLOCKDELAY_ERR;  /*���ܹ�����ʱ������0x37*/
   }
   
   if(UnlockLimitTime_u16_Sig!=0 && ScurReqTimes_u8_Sig==0 && RspFmt_u8_Sig!=NEG_RSP)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=UNLOCKDELAY_ERR;  /**���ܹ�����ʱ������0x37*/
   }
   
   /*-----------------------����Seed�ӷ���-------------------------------------*/
   
   if((subFunction&0x01)==0x01 &&   subFunction<=0x41 && RspFmt_u8_Sig!=NEG_RSP) {
   RspMsgLen_u16_Sig=5; /*�����Ӧ�ĳ���*/
   if(LockMode_u8_Sig == Lock) {/*�ж��Ƿ����*/
   /*---------------------Seed�����ֵ----------------------------------*/
   Service_RamdomGen();
   //Rsp_Msg.ReqSendMsg_u8_Tmp[2]=__byte(&Seed_u32_Sig,0);
   //Rsp_Msg.ReqSendMsg_u8_Tmp[3]=__byte(&Seed_u32_Sig,1);
   //Rsp_Msg.ReqSendMsg_u8_Tmp[4]=__byte(&Seed_u32_Sig,2);
   //Rsp_Msg.ReqSendMsg_u8_Tmp[5]=__byte(&Seed_u32_Sig,3);

   CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], &Seed_u32_Sig, LSB, LSB, 4);
   /*---------------------4��8λ��Seed���ϳ�32λ----------------------------------*/
   //Seed_u32_Sig=Rsp_Msg.ReqSendMsg_u8_Tmp[2]&0xFF;
   //Seed_u32_Sig=(Seed_u32_Sig<<8)+(Rsp_Msg.ReqSendMsg_u8_Tmp[3]&0xFF);
   //Seed_u32_Sig=(Seed_u32_Sig<<8)+(Rsp_Msg.ReqSendMsg_u8_Tmp[4]&0xFF);
   //Seed_u32_Sig=(Seed_u32_Sig<<8)+(Rsp_Msg.ReqSendMsg_u8_Tmp[5]&0xFF);
   EcuKey=0;
   /*---------------------�жϽ��ܵȼ�----------------------------------*/
   if(subFunction==0x01)
   {
	   EcuKey =SeedToKey_v_g(Seed_u32_Sig,Level1Mask_u32_Sig);/*�����㷨�õ�Key*/
   }
   if(subFunction==0x05)
   {
	   EcuKey =SeedToKey_v_g(Seed_u32_Sig,Level2Mask_u32_Sig);/*�����㷨�õ�Key*/
   }
   seedReqmrk=1;
   TestetKey = 0;/*�����Key��0*/
   seedSub_u8_Tmp = subFunction;/*��¼Seed��Sub*/
   } 
   else {
   /*---------------------�ѽ���ȫ���ظ�Ϊ0----------------------------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [2]=0x00; 
   //Rsp_Msg.ReqSendMsg_u8_Tmp [3]=0x00; 
   //Rsp_Msg.ReqSendMsg_u8_Tmp [4]=0x00; 
   //Rsp_Msg.ReqSendMsg_u8_Tmp [5]=0x00;

   Rsp_Msg.ReqSendMsg_u8_Tmp [1]=0x0000; 
   Rsp_Msg.ReqSendMsg_u8_Tmp [2]=0x0000; 

   RspFmt_u8_Sig=POS_RSP; 
   }
  }
   
   /*-------------------------------����Key�ӷ���-------------------------------------*/
   if((subFunction&0x01)==0x00 &&   subFunction<=0x42 && RspFmt_u8_Sig!=NEG_RSP) {
      /*--------------Key��������---------------------*/
      TestetKey=RevData[1];
      TestetKey=(TestetKey<<8)+RevData[2];
      TestetKey=(TestetKey<<8)+RevData[3];
      TestetKey=(TestetKey<<8)+RevData[4];

      if(EcuKey!=TestetKey) {/*�ܳ��ж�*/
      RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=KEY_ERR;  /*�ܳ״��������0x35*/
      } 
      else {
       
       if(subFunction ==0x02)/*�ж�Sub*/
       {
       	LockMode_u8_Sig=UnLock_Level; /*���ܵȼ���ֵ*/
       }
       if(subFunction ==0x06)/*�ж�Sub*/
       {
       	LockMode_u8_Sig=UnLock_Level2;/*���ܵȼ���ֵ*/
       }
       if(subFunction ==0x0A)/*�ж�Sub*/
       {
       	LockMode_u8_Sig=UnLock_Level3;/*���ܵȼ���ֵ*/
       }
        UnlockLimitTime_u16_Sig=0;/*���ܴ����������*/
        RspMsgLen_u16_Sig=1;/*�������ݵĳ���*/
      } 
      if(LockMode_u8_Sig == Lock && UnLockTimeOver_u8_Sig!=1) {/*���ܴ����ж�*/
      UnlockLimitTime_u16_Sig++;/*���ܴ����������*/
      if(UnlockLimitTime_u16_Sig==SEED_KEY_TIMES) {/*���ܴ�����������ж�*/
      UnLockTimeOver_u8_Sig=1;/*���ܴ���������ޱ�־λ��1*/
      RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=UNLOCKOVERTIME_ERR;  /*���ܴ�������*/ 
      }
   }
   
   }

   if(RspFmt_u8_Sig==NEG_RSP  ) { /*�жϻ�Ӧ�����Ƿ��Ǹ����Ӧ*/
   	 seedReqmrk   = 0;   
   	 EcuKey       = 0;
     RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
   } 
   else {
     
   } 
 }
 
/*!******************************************************************************************************
*	@fn	 void ControlDTCSetting_v_g(BYTEPTR RevData)
*	@brief DTC���÷�����
*	@author Matt Zhang
*	@param[in]	RevDataΪӦ����������ָ��
*	@return	void
*	@note 
-
*********************************************************************************************************
*/
 void ControlDTCSetting_v_g(BYTEPTR RevData)
 {
   uint8_T subFunction;
   
   /*--------------��ȡ������ֵ-----------*/
   subFunction=__byte(RevData, MSB);/*sub_funtion��ֵ*/
   RspFmt_u8_Sig=POS_RSP; /*��Ӧ���͸�ֵ*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*��Ӧ״̬��ֵ*/
   subFunction=subFunction&0x7F;/*Sub_Funtionȥ��λ����*/
   SI_u8_Tmp=CONTROL_DTC_SETTING;
   DefSub_u8_Tmp=0x01;/*Sub�����־λ��1*/
   /*--------------����Ӧ���ݸ�ֵ----------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
  /*----------------Session Not Support--------------*/  
   if(SessionMode_u8_Sig!=EXTEND_SESSION)
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*�Ựģʽ��֧�ִ�����0x7F*/
   } 
  /*----------------Len Err-------------------------*/  
   if(RevMsgLen_u16_Sig!=2 && RspFmt_u8_Sig!=NEG_RSP)/*���Ȳ����������ĳ���*/ 
   {
     RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/  
   } 
   /*----------------SubFun Err-------------------------*/   
   if(subFunction!=DTCSETTING_ON && subFunction!=DTCSETTING_OFF && RspFmt_u8_Sig!=NEG_RSP)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR;/*sub��֧�ִ�����0x12*/
   	
   }
  /*----------------Sub_Function -------------------------*/
   if(subFunction==DTCSETTING_ON && RspFmt_u8_Sig!=NEG_RSP)  /*On DTC Setting*/
   {
     DtcOnOff_u8_Sig=DTCSETTING_ON;
   } 
   else if(subFunction==DTCSETTING_OFF && RspFmt_u8_Sig!=NEG_RSP )/*Off DTC Setting*/ 
   {
     DtcOnOff_u8_Sig=DTCSETTING_OFF; 
   } 
   else {
    
   }
   
   if(RspFmt_u8_Sig==NEG_RSP  ) {/*�жϻ�Ӧ�����Ƿ��Ǹ����Ӧ*/
     RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
   } 
   else {
     RspMsgLen_u16_Sig=1;/*�������ݵĳ���*/
   } 
 }
 /*!******************************************************************************************************
 *	@fn	 void CommunicationControl_v_g(BYTEPTR RevData)
 *	@brief ͨ�ſ��Ʒ�����
 *	@author Matt Zhang
 *	@param[in]	RevDataΪӦ����������ָ��
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void CommunicationControl_v_g(BYTEPTR RevData)
 {
   uint8_T subFunction;
   uint8_T comType;
   uint8_T txStatus;
   uint8_T rxStatus;
   
   /*-------------------��ȡ������ֵ-----------------------*/
   subFunction=__byte(RevData, MSB);/*sub_funtion��ֵ*/
   comType=RevData[1];/*ͨ�����͸�ֵ*/
   RspFmt_u8_Sig=POS_RSP;/*��Ӧ���͸�ֵ*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*��Ӧ״̬��ֵ*/
   subFunction=subFunction&0x7F; /*Sub_Funtionȥ��λ����*/
   SI_u8_Tmp=COMMUNICATION_CONTROL;
   DefSub_u8_Tmp=0x01;/*Sub�����־λ��1*/
   /*----------------����Ӧ���ݸ�ֵ-------------------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;
   
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
 /*----------------Session Not Support--------------*/  
   if(SessionMode_u8_Sig!=EXTEND_SESSION)
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*�Ựģʽ��֧�ִ�����0x7F*/
   }
 /*----------------Len Err-------------------------*/  
   if(RevMsgLen_u16_Sig!=3 && RspFmt_u8_Sig!=NEG_RSP ) 
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 
   } 
/*----------------SubFun Err-------------------------*/    
   if(subFunction!=0x00 && subFunction!=0x03 && RspFmt_u8_Sig!=NEG_RSP)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR; /*sub��֧�ִ�����0x12*/
   }
/*----------------ComType Err-------------------------*/   
   if((comType<0x01 || comType>0x03 )&& RspFmt_u8_Sig!=NEG_RSP)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=OVERRANGE_ERR; /*ֵ����Χ������0x31*/
   }
 /*----------------Sub Function����------------------------*/

   if(RspFmt_u8_Sig!=NEG_RSP ) {
      
   if(subFunction ==0x00) {  /*Tx��Rx��Enable*/
      txStatus=1;
      rxStatus=1;
   } 
   else if (subFunction ==0x01) {/*Tx Enable �� Rx Disable*/
      txStatus=1;
      rxStatus=0;
    
   }
   else if (subFunction ==0x02) { /*Tx Disable �� Rx Enable*/
      txStatus=0;
      rxStatus=1;
    
   }
   else if (subFunction ==0x03) { /*Tx��Rx��Disable*/
      txStatus=0;
      rxStatus=0;
    
   } 
   else
   {
   	
   	
   }
 
   }
   
   if(RspFmt_u8_Sig!=NEG_RSP ) {
   
   if(comType==0x01) {/*һ��ͨ��*/
   NormalComTx_u8_Sig = txStatus;/*��������ֻ�õ�һ��ͨ�ţ���NormalComTx_u8_SigΪ1ʱ���ܷ��ͳ�UDS����֮��ı���*/
   NormalComRx_u8_Sig = rxStatus;/*��NormalComRx_u8_SigΪ1ʱ���ܽ��ճ�UDS����֮��ı���*/
   }
   
   else if(comType==0x02) {/*һ��ͨ��*/
   NetWorkComTx_u8_Sig = txStatus;
   NetWorkComRx_u8_Sig = rxStatus;
   }
   
   else if(comType==0x03) {/*һ��ͨ��*/
   NormalComTx_u8_Sig =  txStatus;
   NormalComRx_u8_Sig =  rxStatus;
   NetWorkComTx_u8_Sig = txStatus;
   NetWorkComRx_u8_Sig = rxStatus; 
   } 
   
   else {
   
   }
   
   }
    
     
   if(RspFmt_u8_Sig==NEG_RSP  ) {/*�жϻ�Ӧ�����Ƿ��Ǹ����Ӧ*/
     RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
   } 
   else {
     RspMsgLen_u16_Sig=1;/*�������ݵĳ���*/
   }    
     
}
/*!******************************************************************************************************
*	@fn	  void TesterPresent_v_g(BYTEPTR RevData)
*	@brief ���ֺ�����һ����Ϊ�˲��ûỰģʽת��Ĭ�ϻỰ
*	@author Matt Zhang
*	@param[in]	RevDataΪӦ����������ָ��
*	@return	void
*	@note 
-
*********************************************************************************************************
*/  
 void TesterPresent_v_g(BYTEPTR RevData) 
 {
   uint8_T subFunction;
   /*---------------------��ȡ������ֵ----------------------*/
   subFunction=__byte(RevData, MSB);/*sub_funtion��ֵ*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*��Ӧ״̬��ֵ*/
   subFunction=subFunction&0x7F;/*Sub_Funtionȥ��λ����*/
   RspFmt_u8_Sig=POS_RSP;/*��Ӧ���͸�ֵ*/
   SI_u8_Tmp=TESTER_PRESENT;
   DefSub_u8_Tmp=0x01;/*Sub�����־λ��1*/
   /*----------------����Ӧ���ݸ�ֵ-------------------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;
   
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
   /*----------------Len Err--------------*/
   if(RevMsgLen_u16_Sig!=2) 
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 
   } 
   /*----------------Sub Not��Support--------------*/
   if(RspFmt_u8_Sig!=NEG_RSP && subFunction!=0x00 ) 
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR; /*Sub��֧�ִ�����0x12*/
   }

   if(RspFmt_u8_Sig==NEG_RSP  ) {/*�жϻ�Ӧ�����Ƿ��Ǹ����Ӧ*/
     RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
   } 
   else {
     RspMsgLen_u16_Sig=1;/*�������ݵĳ���*/
   }  
   
 }
 
 /*!******************************************************************************************************
 *	@fn	 void ClearDiagImfor_v_g(BYTEPTR RevData)
 *	@brief ��������뺯��
 *	@author Matt Zhang
 *	@param[in]	RevDataΪӦ����������ָ��
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void ClearDiagImfor_v_g(BYTEPTR RevData) 
{
  
uint32_T dtcGroup;/*���������������*/
SI_u8_Tmp=CLEAR_DIAGNOSTIC_INFORMATION;
DefSub_u8_Tmp=0x00;/*Sub״̬λ��ֵ*/
RspFmt_u8_Sig=POS_RSP;/*��Ӧ���͸�ֵ*/
/*------------------Dtc Group ��ϸ�ֵ*---------------------*/
dtcGroup=RevData[0];
dtcGroup=(dtcGroup<<8)+RevData[1];
dtcGroup=(dtcGroup<<8)+RevData[2];
/*-----------------------Session Not Support--------------*/
if(SessionMode_u8_Sig==PROGRANMMING_SESSION)
{
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*�Ựģʽ���Դ�����0x7F*/
}
/*----------------Len Err--------------*/ 
   
if(RevMsgLen_u16_Sig!=4 && RspFmt_u8_Sig !=NEG_RSP) 
{
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 
} 
/*----------------Group Err--------------*/ 
if(dtcGroup!=DTCGROUP && dtcGroup!=ALLDTCGROUP && RspFmt_u8_Sig !=NEG_RSP)
{
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=OVERRANGE_ERR; /*������Χ���Դ�����0x31*/
	
}
/*----------------Condition Err--------------*/ 
if(VehicleSpeed_u16_Sig!=0 && RspFmt_u8_Sig !=NEG_RSP ) {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CONDITION_NOTSURRORT_ERR;  /*�������Դ�����0x22*/
 }
 
if(RspFmt_u8_Sig !=NEG_RSP) {
#if APP_CODE ==1
   ClearDtc_v_g();/*�����������������뺯��*/
#endif   
}

if(RspFmt_u8_Sig==NEG_RSP  ) {/*�жϻ�Ӧ�����Ƿ��Ǹ����Ӧ*/
   RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
} 
else {
   RspMsgLen_u16_Sig=0;/*�������ݵĳ���*/
}  



}
/*!******************************************************************************************************
 *	@fn	 void ReadDtcMsg_v_g(BYTEPTR RevData)
 *	@brief ��ȡ��������Ϣ����
 *	@author Matt Zhang
 *	@param[in]	RevDataΪӦ����������ָ��
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void ReadDtcMsg_v_g(BYTEPTR RevData)
{
	
   uint8_T  subFunction;
   uint8_T  dtcStatusMark;
   uint8_T  dtcStatus;
   uint8_T  dtcNumcycle;
   uint16_T dtcMarkNum=0;
   uint16_T ExtendIndex=0;
   uint16_T SnapIndex=0;
   #define DTCHIGTBYTE    RevData[1]
   #define DTCLOWBYTE     RevData[2]
   #define DTCFAILUREBYTE RevData[3]
   uint8_T temp;
   /*-----------------------��ȡ������ֵ----------------------*/
   RspFmt_u8_Sig=POS_RSP;/*��Ӧ���͸�ֵ*/
   subFunction=__byte(RevData, MSB);/*Sub_Function��ֵ*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*��Ӧ���͸�ֵ*/
   subFunction=subFunction&0x7F;/*��Ӧ���͸�ֵ*/
   SI_u8_Tmp=READ_DTC_INFORMATION; /*��Ӧ���͸�ֵ*/
   DefSub_u8_Tmp=0x01;
   /*-----------------------��Ӧ���鸳ֵ----------------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;
   
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
   /*-----------------------Session Not Support----------------------*/
   if(SessionMode_u8_Sig==PROGRANMMING_SESSION)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*�Ựģʽ��֧�ִ�����0x7F*/
   }
   /*-----------------------Len Err-------------------------------*/
   if(RevMsgLen_u16_Sig<2&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 
   }
   if((subFunction==0x01  || subFunction==0x02) && RevMsgLen_u16_Sig!=3 && RspFmt_u8_Sig!=NEG_RSP)
   {
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 
   }
   
   if(subFunction==0x0A && RevMsgLen_u16_Sig!=2&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 
   }
   
   if((subFunction==0x06 ||subFunction==0x04 ) && RevMsgLen_u16_Sig!=6&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 
   }
   
   /*-----------------------Sub Not Support-------------------------------*/
   if(subFunction!=0x01 && subFunction!=0x02 &&subFunction!=0x04&& subFunction!=0x06 && subFunction!=0x0A&& RspFmt_u8_Sig!=NEG_RSP)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR;  /*Sub��֧�ִ�����0x12*/
   }
   /*-------------------------------Condition Err--------------------------*/
   if(VehicleSpeed_u16_Sig!=0 && RspFmt_u8_Sig!=NEG_RSP ) {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=CONDITION_NOTSURRORT_ERR;  /*���������������0x22*/
   } 
   /*-----------------------------Sub_Function����-------------------------*/
   if(RspFmt_u8_Sig!=NEG_RSP)
   {
   	switch(subFunction) {
   	/*-------------------------------��ȡ��������״̬�Ĺ�������--------------------*/
   	case 0x01:
   	for(dtcNumcycle=0;dtcNumcycle<DTCNUM;dtcNumcycle++) 
    {
       dtcStatus=DtcStatus_u16a8_Par[dtcNumcycle].Status.Byte; /*��ȡ������״̬��������Լ�������滻���Լ���*/
       if((dtcStatus&dtcStatusMark)!=0) { /*������״̬�ж�*/
         dtcMarkNum++;/*����*/
       }
    }
   	/*-----------------------------��Ӧ���ݺͳ��ȸ�ֵ--------------------------*/
    //Rsp_Msg.ReqSendMsg_u8_Tmp [2]= MASKSTATUS;/*���븳ֵ��������Լ�������滻���Լ���*/
    //Rsp_Msg.ReqSendMsg_u8_Tmp [3]= DTCFMT14229;
    //Rsp_Msg.ReqSendMsg_u8_Tmp [4]=(uint8_T)(dtcMarkNum>>8);
    //Rsp_Msg.ReqSendMsg_u8_Tmp [5]=(uint8_T)dtcMarkNum;

	temp = (uint8_T)(dtcMarkNum>>8);
	Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], LSB, MASKSTATUS);
	Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], MSB, DTCFMT14229);
	Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], LSB, temp);
	temp = (uint8_T)(dtcMarkNum);
	Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], MSB, temp);
    RspMsgLen_u16_Sig = 5;
   	break;
   	
   	case 0x02:
   /*-----------------------------��ȡ��������״̬�Ĺ����뼰״̬-------------------*/
   	dtcStatusMark =RevData[1];
   	for(dtcNumcycle=0;dtcNumcycle<DTCNUM;dtcNumcycle++) 
    {
    dtcStatus=DtcStatus_u16a8_Par[dtcNumcycle].Status.Byte; /*��ȡ������״̬,������Լ�������滻���Լ���*/
    if((dtcStatus&dtcStatusMark)!=0) {/*������״̬�ж�*/
    /*----------------------�������뼰״̬��ֵ����Ӧ����--------------------------*/
    //Rsp_Msg.ReqSendMsg_u8_Tmp [3+(dtcMarkNum<<2)]=(uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte1;/*������������Լ��������滻���Լ���*/
    //Rsp_Msg.ReqSendMsg_u8_Tmp [4+(dtcMarkNum<<2)]=(uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte2;/*������������Լ��������滻���Լ���*/
    //Rsp_Msg.ReqSendMsg_u8_Tmp [5+(dtcMarkNum<<2)]=(uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte3;/*������������Լ��������滻���Լ���*/
    //Rsp_Msg.ReqSendMsg_u8_Tmp [6+(dtcMarkNum<<2)]=(uint8_T)dtcStatus;
    dtcMarkNum++;
       }
    }
    //Rsp_Msg.ReqSendMsg_u8_Tmp [2]= MASKSTATUS;/*���븳ֵ��������Լ�������滻���Լ���*/
	
	Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], LSB, MASKSTATUS);
    RspMsgLen_u16_Sig = 2+(dtcMarkNum<<2);/*���븳ֵ*/
   	break;
   	
   	case 0x04:
   /*-----------------------------��ȡ�������Snapshot����--------------------------*/
    for(dtcNumcycle=0;dtcNumcycle<DTCNUM;dtcNumcycle++) 
    {       
     if(DTCHIGTBYTE==((uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte1) && DTCLOWBYTE==((uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte2) \
     && DTCFAILUREBYTE==((uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte3))/*�жϹ������Ƿ��з��ϵģ�������Լ�������滻���Լ���*/
     {
     dtcStatus=(uint8_T)DtcStatus_u16a8_Par[dtcNumcycle].Status.Byte;/*��ȡ������״̬,������Լ�������滻���Լ���*/
     SnapIndex = dtcNumcycle;
   /*-------------�����뼰״̬��ֵ----------------*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [2]=DTCHIGTBYTE;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [3]=DTCLOWBYTE;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [4]=DTCFAILUREBYTE;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [5]=dtcStatus;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [6]=0x01;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [7]=0x04;
	 
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], LSB, DTCHIGTBYTE);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], MSB, DTCLOWBYTE);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], LSB, DTCFAILUREBYTE);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], MSB, dtcStatus);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[3], LSB, 0x01);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[3], MSB, 0x04);
     dtcMarkNum++;
     }
   
    }
    /*-------------Snap���ݸ�ֵ����Ӧ����----------------*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [8]=0x01;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [9]=0x12;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [10]=(uint8_T)DtcSnapShot_u80a8_Par[SnapIndex].SupBatt;/*��ѹ,������Լ�������滻���Լ���*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [11]=0xE1;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [12]=0x01;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [13]=(uint8_T)((DtcSnapShot_u80a8_Par[SnapIndex].Odreading &0xFF0000)>>16);/*�����,������Լ�������滻���Լ���*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [14]=(uint8_T)((DtcSnapShot_u80a8_Par[SnapIndex].Odreading &0x00FF00)>>8);/*�����,������Լ�������滻���Լ���*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [15]=(uint8_T)(DtcSnapShot_u80a8_Par[SnapIndex].Odreading&0x0000FF);/*�����,������Լ�������滻���Լ���*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [16]=0xD0;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [17]=0x01;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [18]=(uint8_T)DtcSnapShot_u80a8_Par[SnapIndex].IgStatus;/*Ig״̬,������Լ�������滻���Լ���*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [19]=0x01;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [20]=0x0C;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [21]=(uint8_T)DtcSnapShot_u80a8_Par[SnapIndex].CoolTemp;/*�¶�,������Լ�������滻���Լ���*/

	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[4], LSB, 0x01);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[4], MSB, 0x12);

	 temp = (uint8_T)DtcSnapShot_u80a8_Par[SnapIndex].SupBatt;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[5], LSB, temp);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[5], MSB, 0xE1);
	 
	 temp = (uint8_T)((DtcSnapShot_u80a8_Par[SnapIndex].Odreading &0xFF0000)>>16);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[6], LSB, 0x01);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[6], MSB, temp);

 	 temp = (uint8_T)((DtcSnapShot_u80a8_Par[SnapIndex].Odreading &0x00FF00)>>8);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[7], LSB, temp);
 	 temp = (uint8_T)((DtcSnapShot_u80a8_Par[SnapIndex].Odreading &0xFF0000));
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[7], MSB, temp);

	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[8], LSB, 0xD0);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[8], MSB, 0x01);

	 temp = (uint8_T)DtcSnapShot_u80a8_Par[SnapIndex].IgStatus;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[9], LSB, temp);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[9], MSB, 0x01);

	 temp = (uint8_T)DtcSnapShot_u80a8_Par[SnapIndex].CoolTemp;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[10], LSB, 0x0C);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[10], MSB, temp);

     RspMsgLen_u16_Sig =21;
   	 if(dtcMarkNum == 0)/*�ж�֧��DTC�Ƿ�Ϊ0*/
     {
       RspFmt_u8_Sig=NEG_RSP;
       NegRsp_u8_Sig=OVERRANGE_ERR;/*�����������Χ������0x31*/
     }
   	break;
   	
   	case 0x06:
   	/*-----------------------------��ȡ�������Extend����--------------------------*/
    for(dtcNumcycle=0;dtcNumcycle<DTCNUM;dtcNumcycle++) 
    {       
     if(DTCHIGTBYTE==((uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte1) && DTCLOWBYTE==((uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte2) \
     && DTCFAILUREBYTE==((uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte3))/*�жϹ������Ƿ��з��ϵģ�������Լ�������滻���Լ���*/
     {
     dtcStatus=(uint8_T)DtcStatus_u16a8_Par[dtcNumcycle].Status.Byte;/*��ȡ������״̬,������Լ�������滻���Լ���*/
     ExtendIndex = dtcNumcycle;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [2]=DTCHIGTBYTE;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [3]=DTCLOWBYTE;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [4]=DTCFAILUREBYTE;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [5]=dtcStatus;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [6]=0x01;

	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], LSB, DTCHIGTBYTE);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], MSB, DTCLOWBYTE);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], LSB, DTCFAILUREBYTE);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], MSB, dtcStatus);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[3], LSB, 0x01);
	 
        dtcMarkNum++;
     }
   
    }
     //Rsp_Msg.ReqSendMsg_u8_Tmp [7]=(uint8_T)DtcExtend_u64a8_Par[ExtendIndex].FualtCnt;/*���ϼ���,������Լ�������滻���Լ���*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [8]=(uint8_T)DtcExtend_u64a8_Par[ExtendIndex].PendCnt;/*δȷ�Ϲ��ϼ���,������Լ�������滻���Լ���*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [9]=(uint8_T)DtcExtend_u64a8_Par[ExtendIndex].AgedCnt;/*�Ѿ���ѯ�����ֵ�Ĵ���,������Լ�������滻���Լ���*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [10]=(uint8_T)DtcExtend_u64a8_Par[ExtendIndex].AgingCnt;/*��ѯ����,������Լ�������滻���Լ���*/

	 temp = (uint8_T)DtcExtend_u64a8_Par[ExtendIndex].FualtCnt;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[3], MSB, temp);

	 temp = (uint8_T)DtcExtend_u64a8_Par[ExtendIndex].PendCnt;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[4], LSB, temp);
	 temp = (uint8_T)DtcExtend_u64a8_Par[ExtendIndex].AgedCnt;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[4], MSB, temp);
	 temp = (uint8_T)DtcExtend_u64a8_Par[ExtendIndex].AgingCnt;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[5], LSB, temp);


	 RspMsgLen_u16_Sig =10;
 	 if(dtcMarkNum == 0)/*�ж�֧��DTC�Ƿ�Ϊ0*/
     {
       RspFmt_u8_Sig=NEG_RSP;
       NegRsp_u8_Sig=OVERRANGE_ERR;/*�����������Χ������0x31*/
     }
   	break;
   	
   	case 0x0A:
   	/*-----------------------------��ȡ���й�����״̬--------------------------*/
   	for(dtcNumcycle=0;dtcNumcycle<DTCNUM;dtcNumcycle++) 
    {
     dtcStatus=DtcStatus_u16a8_Par[dtcNumcycle].Status.Byte;/*��ȡ������״̬,������Լ�������滻���Լ���*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [3+(dtcNumcycle<<2)]=(uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte1;/*������������Լ��������滻���Լ���*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [4+(dtcNumcycle<<2)]=(uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte2;/*������������Լ��������滻���Լ���*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [5+(dtcNumcycle<<2)]=(uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte3;/*������������Լ��������滻���Լ���*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [6+(dtcNumcycle<<2)]=dtcStatus;
    }
     //Rsp_Msg.ReqSendMsg_u8_Tmp [2]= MASKSTATUS;
	 
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], LSB, MASKSTATUS);
     RspMsgLen_u16_Sig = 2+(DTCNUM<<2);/*���븳ֵ��������Լ�������滻���Լ���*/
   	break;
   	
   	default:
   	
   	break;
   		
   	}
   	
   }
  
   
if(RspFmt_u8_Sig==NEG_RSP  ) {/*�жϻ�Ӧ�����Ƿ��Ǹ����Ӧ*/
  RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
} 
else {

}  

}
/*!******************************************************************************************************
 *	@fn	 void ReadDataById_v_g(BYTEPTR RevData)
 *	@brief ����DATAID��ȡ���ݺ���
 *	@author Matt Zhang
 *	@param[in]	RevDataΪӦ����������ָ��
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void ReadDataById_v_g(BYTEPTR RevData)
{
 uint16_T  idNum=0;
 uint16_T  dataId=0;
 uint16_T  defIdNum=0;
 uint8_T   i;
 
 SI_u8_Tmp=READ_DATA_BY_IDENTIFIER;
 DefSub_u8_Tmp=0x00;/*Sub״̬λ��ֵ*/
 RspFmt_u8_Sig=POS_RSP;/*��Ӧ���͸�ֵ*/
 /*-----------------------Len Err----------------------*/
 if((RevMsgLen_u16_Sig%2)==0 || RevMsgLen_u16_Sig<2) 
 {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 
 } 
 /*-----------------------��಻����3��DID��ȡ----------------------*/
 if(RspFmt_u8_Sig!=NEG_RSP)
 {
 //idNum =(RevMsgLen_u16_Sig-1)>>1; 
 if(RevMsgLen_u16_Sig!=3) {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*Length error 0x13*/
 }
 }		
if(RspFmt_u8_Sig!=NEG_RSP)
{
/*-----------------------DID��ȡ������---------------------------*/
 //for(i=0;i<idNum;i++) {
 //dataId=RevData[0+(i<<1)];
 //dataId=(dataId<<8)+RevData[1+(i<<1)];
 dataId = __byte(&RevData[0], MSB)*256;
 dataId += __byte(&RevData[1], LSB);

 switch(dataId) {
  case 0xF110: /*---PIF Pointer to Current Block---*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
  						   &RevData[0],
  						   MSB,
  						   MSB,
  						   2);

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
  						   &PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][0],
  						   MSB,
  						   LSB,
  						   16);
  defIdNum=18;
  break;
  
  case 0xF111:/*---PIF Spe Blocks---*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[1][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF112:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[2][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF113:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[3][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF114:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[4][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF115:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[5][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF116:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[6][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF117:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[7][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF118:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[8][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF119:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[9][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF11A:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[10][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF11B:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[11][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF11C:/*---SoftWare Version---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[12][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF11D:/*---SoftWare Version---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[13][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF11E:/*---SoftWare Version---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[14][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF11F:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[15][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF183:/*---ECU BootLoader Software Reference Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &BootSwRefNumb_u16a10_Par[0],
							MSB,
							LSB,
							10);
  defIdNum=12;
  
  break;
  
  
  case 0xF187:/*---ECU Part Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &ECUPartNumb_u16a6_Par[0],
              MSB,
              LSB,
              6);
  defIdNum=8;
  break;
  
  case 0xF18A:/*---System Supplier Id---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &SysSupplierId_u16a6_Par[0],
              MSB,
              LSB,
              6);
  defIdNum=8;
  break;
  
  case 0xF190:/*---VIN---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &Vin_u16a17_Par[0],
              MSB,
              LSB,
              17);
  defIdNum=19;
  break;
  
  case 0xF191:/*---ECU HardWare Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuHwNumb_u16a6_Par[0],
              MSB,
              LSB,
              6);
  defIdNum=8;
  break;
  
  case 0xF192:/*---Supplier Ecu HardWare Reference Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuHwRefNumb_u16a10_Par[0],
              MSB,
              LSB,
              10);
  defIdNum=12;
  break;
  
  case 0xF194:/*---Supplier Ecu SoftWare Reference Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuSwRefNumb_u16a10_Par[0],
              MSB,
              LSB,
              10);
  defIdNum=12;
  break;

  case 0xF1A0:/*---Ecu Application Software Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuAppSwNumb_u16a6_Par[0],
              MSB,
              LSB,
              6);
  defIdNum=8;
  break;
  
  
  case 0xF1A1:/*---Ecu Calibration Software Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuCalSwNumb_u16a6_Par[0],
              MSB,
              LSB,
              6);
  defIdNum=8;
  break;
  
  case 0xF1A2:/*---ECU Net Reference Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuNetRefNumb_u16a6_Par[0],
              MSB,
              LSB,
              6);
  defIdNum=8;
  break;
  
  case 0xF1A8:/*---Vehicle Feature Information---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &VehFeature_u16a20_Par[0],
              MSB,
              LSB,
              20);
  defIdNum=22;
  break;
  
  case 0xF18B:/*---Ecu Manufacture Data---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuMData_u16a3_Par[0],
              MSB,
              LSB,
              3);
  defIdNum=5;
  break;
  
  case 0xF18C:/*---VINDataId---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuSupplierSN_u16a10_Par[0],
              MSB,
              LSB,
              10);
  defIdNum=12;
  break;
  case 0xAFFC:/*---Bootloaderˢд����---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &BootTimes_u16_Par,
              MSB,
              LSB,
              2);
  defIdNum=4;
  break; 
  case 0xAFFD:/*---�������---*/
/*  Rsp_Msg.ReqSendMsg_u8_Tmp[1+defIdNum]=RevData[0+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[2+defIdNum]=RevData[1+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[3+defIdNum]=(uint8_T)SIS_u16_Sig;*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &SIS_u16_Sig,
              MSB,
              LSB,
              1);
  defIdNum=3;  
  break; 
  case 0xAFFE:/*---�������---*/
/*  Rsp_Msg.ReqSendMsg_u8_Tmp[1+defIdNum]=RevData[0+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[2+defIdNum]=RevData[1+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[3+defIdNum]=(uint8_T)SCS_u16_Sig;*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &SCS_u16_Sig,
              MSB,
              LSB,
              1);
  defIdNum=3; 
  break;   
  case 0xAFFF:/*---�����Ч---*/
/*  Rsp_Msg.ReqSendMsg_u8_Tmp[1+defIdNum]=RevData[0+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[2+defIdNum]=RevData[1+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[3+defIdNum]=(uint8_T)SVF_u16_Par;*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &SVF_u16_Par,
              MSB,
              LSB,
              1);
  defIdNum=3;
  break;
  
  case 0xD110:/*---MotorSpeed---*/

 #if APP_CODE ==0
//  MotorSpd_u16_Sig= g_CANDataVar.nEngine_RMP_dCAN;  /*����ĸ�ֵ�����Լ�ȥ�޸�*/
  MotorSpd_u16_Sig= g_CANDataVar.nEngine_RMP_dCAN*2;  // factor:0.5, intel  20160306 by ljh.
 #endif
/*  Rsp_Msg.ReqSendMsg_u8_Tmp[1+defIdNum]=RevData[0+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[2+defIdNum]=RevData[1+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[3+defIdNum]=(uint8_T)(MotorSpd_u16_Sig>>8);
  Rsp_Msg.ReqSendMsg_u8_Tmp[4+defIdNum]=(uint8_T)(MotorSpd_u16_Sig);*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &MotorSpd_u16_Sig,
              MSB,
              LSB,
              2);

  defIdNum=4;
  break; 
  case 0xD002:/*---Park Status---*/
#if APP_CODE ==0
	  ParkStatus_u8_Sig=(g_CANDataVar.nParkLock_St_dCAN<<5)+(CanDataVar.bit.nPark_Active<<4)+(CanDataVar.bit.nDrive_Ready<<3)+(g_CANDataVar.nParkReq_dCAN<<1);
 // ParkStatus_u8_Sig=  g_CANDataVar.nParkReq_dCAN; /*����ĸ�ֵ�����Լ�ȥ�޸�*/
#endif
/*  Rsp_Msg.ReqSendMsg_u8_Tmp[1+defIdNum]=RevData[0+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[2+defIdNum]=RevData[1+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[3+defIdNum]=ParkStatus_u8_Sig;*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &ParkStatus_u8_Sig,
              MSB,
              LSB,
              1);
  defIdNum=3;  
  break; 

  case 0xD003:/*---EPP Status---*/
#if APP_CODE ==0
	//  EppStatus_u8_Sig=  eppstatus; /*����ĸ�ֵ�����Լ�ȥ�޸�,�޸ĺ��뽫ǰ���ע��˫б��ȥ��*/
	//  EppStatus_u8_Sig= CanDataVar.bit.nPark_Active;				//ljh 20160224
	//20160306 ljh
  EppStatus_u8_Sig=((FltSt1Var.FLTST1.bit.nMot_Jam_Middle_Fault<<5)+(FltSt1Var.FLTST1.bit.nPark_Stalled_Fault<<4)+(FltSt1Var.FLTST1.bit.nUnpark_Stalled_Fault<<3)+(FltSt1Var.FLTST1.bit.nNo_Load_Fault<<2))&0x3C;
#endif
/*  Rsp_Msg.ReqSendMsg_u8_Tmp[1+defIdNum]=RevData[0+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[2+defIdNum]=RevData[1+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[3+defIdNum]=EppStatus_u8_Sig;*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EppStatus_u8_Sig,
              MSB,
              LSB,
              1);
  defIdNum=3;
  break;
  default:
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=OVERRANGE_ERR;  /*���ݷ�Χ���޴�����0x31*/
  break;
  
 }
  
 //}
 
 }
if(RspFmt_u8_Sig==NEG_RSP  ) {/*�жϻ�Ӧ�����Ƿ��Ǹ����Ӧ*/
  RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
} 
else {
  RspMsgLen_u16_Sig=defIdNum;/*�������ݵĳ���*/
} 
 
}
/*!******************************************************************************************************
 *	@fn	void WriteDataById_v_g(BYTEPTR RevData)
 *	@brief ����DATAIDд���ݺ���
 *	@author Matt Zhang
 *	@param[in]	RevDataΪӦ����������ָ��
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */

void WriteDataById_v_g(BYTEPTR RevData)
{
uint16_T dataId;

SI_u8_Tmp=WRITE_DATA_BY_IDENTIFIER;
DefSub_u8_Tmp=0x00;/*Sub״̬λ��ֵ*/
RspFmt_u8_Sig=POS_RSP;/*��Ӧ���͸�ֵ*/


dataId = __byte(&RevData[0], MSB)*256;
dataId += __byte(&RevData[1], LSB);

//WrDidBackUp_Sig[0]=RevData[0];/*DID��ֵ*/
//WrDidBackUp_Sig[1]=RevData[1];/*DID��ֵ*/
//LockMode_u8_Sig= UnLock_Level;
//SessionMode_u8_Sig=EXTEND_SESSION;

/*-----------------------Seesion Not Support----------------------*/
if(SessionMode_u8_Sig==DEFAULT_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
{
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*�Ựģʽ���Դ�����0x7F*/
}
/*-----------------------SeedKey Err----------------------*/
if(LockMode_u8_Sig!=UnLock_Level &&  SessionMode_u8_Sig==EXTEND_SESSION && RspFmt_u8_Sig!=NEG_RSP)
{
	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*δ���ܴ�����0x33*/
	
}
if(LockMode_u8_Sig!=UnLock_Level2 &&  SessionMode_u8_Sig==PROGRANMMING_SESSION && RspFmt_u8_Sig!=NEG_RSP)
{
	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*δ���ܴ�����0x33*/
	
}

if(RspFmt_u8_Sig!=NEG_RSP)
{
 switch(dataId) {
  case 0xF110:/*---PIF---*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=19)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 		
  }
  else
  {
  PifBlockNumb_u16_Sig++;/*block����*/
  if(PifBlockNumb_u16_Sig==16)
  {
	 PifBlockNumb_u16_Sig=2;/*��15����д���˺�ӵ�2����ʼд*/
  }
  /*---PIF Pointer to Current Block---*/
  #if 0
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][0]   =RevData[2];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][1]   =RevData[3];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][2]   =RevData[4];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][3]   =RevData[5];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][4]   =RevData[6];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][5]   =RevData[7];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][6]   =RevData[8];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][7]   =RevData[9];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][8]   =RevData[10];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][9]   =RevData[11];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][10]  =RevData[12];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][11]  =RevData[13];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][12]  =RevData[14];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][13]  =RevData[15];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][14]  =RevData[16];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][15]  =RevData[17];
  #endif
  CopyMemory_WithNone_Byte(&PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][0], 
               &RevData[1],
              LSB,
              MSB,
              16);
  
  //DidEep_u8_Sig=1;/*дDID��־λ*/
 #if APP_CODE==0
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=FLEXRSPTIME_ERR;  /*дEEPROM��ʱ 0x78*/
 #endif
  }
  break;
  
  case 0xA300:/*---ECU Part Numb---F187*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=9)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 		
  }
  else
  {
  #if 0
  ECUPartNumb_u16a6_Par[0] =RevData[2];
  ECUPartNumb_u16a6_Par[1] =RevData[3];
  ECUPartNumb_u16a6_Par[2] =RevData[4];
  ECUPartNumb_u16a6_Par[3] =RevData[5];
  ECUPartNumb_u16a6_Par[4] =RevData[6];
  ECUPartNumb_u16a6_Par[5] =RevData[7];	
  #endif
  CopyMemory_WithNone_Byte(&ECUPartNumb_u16a6_Par[0], 
           &RevData[1],
          LSB,
          MSB,
          6);

  }
 
  break;

  case 0xA301:/*---Supper ID---F18A*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=9)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 		
  }
  else
  {

  CopyMemory_WithNone_Byte(&SysSupplierId_u16a6_Par[0], 
       &RevData[1],
      LSB,
      MSB,
      6);
  //DidEep_u8_Sig=1;/*дDID��־λ*/

  }
  break;

  case 0xA302:/*---Manufacture Data---F18B*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=6)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 		
  }
  else
  {

  CopyMemory_WithNone_Byte(&EcuMData_u16a3_Par[0], 
       &RevData[1],
      LSB,
      MSB,
      3);
  //DidEep_u8_Sig=1;/*дDID��־λ*/

  }
  break;

  case 0xA303:/*---Supplier serial number---F18C*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=13)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 		
  }
  else
  {

  CopyMemory_WithNone_Byte(&EcuSupplierSN_u16a10_Par[0], 
       &RevData[1],
      LSB,
      MSB,
      10);
  //DidEep_u8_Sig=1;/*дDID��־λ*/

  }
  break;

  case 0xA304:/*---Hardware version---F191*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=9)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 		
  }
  else
  {

  CopyMemory_WithNone_Byte(&EcuHwNumb_u16a6_Par[0], 
       &RevData[1],
      LSB,
      MSB,
      6);
  //DidEep_u8_Sig=1;/*дDID��־λ*/

  }
  break;
  
  case 0xF190:/*---VIN---*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=20)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 		
  }
  else
  {

  CopyMemory_WithNone_Byte(&Vin_u16a17_Par[0], 
       &RevData[1],
      LSB,
      MSB,
      17);
  //DidEep_u8_Sig=1;/*дDID��־λ*/
 #if APP_CODE==0
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=FLEXRSPTIME_ERR; /*дEEPROM��ʱ 0x78*/
 #endif
  }
  
  break;
  
  
  case 0xF1A8:/*---VehFeature---*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=23)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 		
  }
  else
  {
  #if 0
  VehFeature_u16a20_Par[0]  =RevData[2];
  VehFeature_u16a20_Par[1]  =RevData[3];
  VehFeature_u16a20_Par[2]  =RevData[4];
  VehFeature_u16a20_Par[3]  =RevData[5];
  VehFeature_u16a20_Par[4]  =RevData[6];
  VehFeature_u16a20_Par[5]  =RevData[7];	
  VehFeature_u16a20_Par[6]  =RevData[8];
  VehFeature_u16a20_Par[7]  =RevData[9];
  VehFeature_u16a20_Par[8]  =RevData[10];
  VehFeature_u16a20_Par[9]  =RevData[11];
  VehFeature_u16a20_Par[10] =RevData[12];
  VehFeature_u16a20_Par[11] =RevData[13];
  VehFeature_u16a20_Par[12] =RevData[14];	
  VehFeature_u16a20_Par[13] =RevData[15];
  VehFeature_u16a20_Par[14] =RevData[16];
  VehFeature_u16a20_Par[15] =RevData[17];
  VehFeature_u16a20_Par[16] =RevData[18];
  VehFeature_u16a20_Par[17] =RevData[19];
  VehFeature_u16a20_Par[18] =RevData[20];
  VehFeature_u16a20_Par[19] =RevData[21];
  #endif
  CopyMemory_WithNone_Byte(&VehFeature_u16a20_Par[0], 
       &RevData[1],
      LSB,
      MSB,
      20);
  //DidEep_u8_Sig=1;/*дDID��־λ*/
 #if APP_CODE==0
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=FLEXRSPTIME_ERR; /*дEEPROM��ʱ 0x78*/
 #endif

  }
  break;
  
  
  default:
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=OVERRANGE_ERR;/*���ݳ���Χ������ 0x78*/
  break;
  
 }	
 
}

if(RspFmt_u8_Sig==NEG_RSP  ) {
  RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
} 
else {
  RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
  //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=RevData[0];
  //Rsp_Msg.ReqSendMsg_u8_Tmp [2]=RevData[1];
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);

} 
}
/*!******************************************************************************************************
 *	@fn	void ReadMemoryByAddress_v_g(BYTEPTR RevData)
 *	@brief ͨ����ַ��ȡ����
 *	@author Matt Zhang
 *	@param[in]	RevDataΪӦ����������ָ��
 *	@return	void
 *	@note
 -Ŀǰ֧�ֵĵ�ַ��EEPROM�ĵ�ַ
 *********************************************************************************************************
 */
void ReadMemoryByAddress_v_g(BYTEPTR RevData) {
#define RM_ADRBYTES (RevData[0]&0x0F)
#define RM_DATALENBYTES (RevData[0]>>4)
uint8_T  cmdLen;
uint32_T memAdr;
uint16_T dataLen;

RspFmt_u8_Sig=POS_RSP;/*��Ӧ���͸�ֵ*/
SI_u8_Tmp=READ_MEMORY_BY_ADDRESS;
DefSub_u8_Tmp=0x00;/*Sub״̬��ֵ*/

cmdLen=ECU_SUPPROT_ADDRESSLEN+MAX_DATANUMBYTE+2;/*����Ҫ�����С����*/
/*-----------��ַ��ȡ----------------*/
memAdr=RevData[1];
memAdr=(memAdr<<8)+RevData[2];
memAdr=(memAdr<<8)+RevData[3];
memAdr=(memAdr<<8)+RevData[4];
/*-----------���ݳ��Ȼ�ȡ----------------*/
dataLen=RevData[5];
dataLen=(dataLen<<8)+RevData[6];
dataLen=dataLen>>1;
MemAdr_u32_Sig=memAdr;/*��ַ��ֵ*/
MemDataLen_u16_Sig =dataLen;/*���ݳ��ȸ�ֵ*/
/*-----------------------Session Not Support----------------------*/
if(((SessionMode_u8_Sig==DEFAULT_SESSION) && (AdrType_u8_Sig!=TAtype_phiscal))|| ((SessionMode_u8_Sig==EXTEND_SESSION) && (AdrType_u8_Sig!=TAtype_phiscal)) \
||(SessionMode_u8_Sig==PROGRANMMING_SESSION))
{
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*�Ựģʽ��֧��Ϊ0x7F*/
	
}
/*-----------------------Len Err----------------------*/
if(RevMsgLen_u16_Sig!=cmdLen && RspFmt_u8_Sig!=NEG_RSP) {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/  
}
/*----------------------SeedKey Err----------------------*/
if(LockMode_u8_Sig!=UnLock_Level &&  SessionMode_u8_Sig==EXTEND_SESSION && RspFmt_u8_Sig!=NEG_RSP)
{
	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*δ���ܴ�����Ϊ0x33*/
	
}
/*----------------------Condition Err----------------------*/
if((RM_ADRBYTES!=ECU_SUPPROT_ADDRESSLEN ||RM_DATALENBYTES!=MAX_DATANUMBYTE)&&RspFmt_u8_Sig!= NEG_RSP) {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=OVERRANGE_ERR;  /*��ַ��ʽ�����ȸ�ʽ���Դ�����0x31*/
}

if(dataLen>MAX_MEMWRITENUM &&RspFmt_u8_Sig!= NEG_RSP) {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=OVERRANGE_ERR;  /*���ȳ��޴�����0x31*/
}
if((memAdr<RWDATA_MINADR ||(memAdr+dataLen-1)>RWDATA_MAXADR) && RspFmt_u8_Sig!= NEG_RSP  )
{
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=OVERRANGE_ERR;   /*��ַ���޴�����0x31*/
}


if(RspFmt_u8_Sig!= NEG_RSP) { 
 RMemDataFLag_u8_Sig = 1;/*��ַ�����ݱ�־λ��λ*/
 RspFmt_u8_Sig=NEG_RSP;
 NegRsp_u8_Sig=FLEXRSPTIME_ERR; /*дEEPROM��ʱ0x78*/
}


if(RspFmt_u8_Sig==NEG_RSP  ) {
  RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
} 
else {
} 

}

/*!******************************************************************************************************
 *	@fn	void WriteMemoryByAddress_v_g(BYTEPTR RevData)
 *	@brief ͨ����ַд����
 *	@author Matt Zhang
 *	@param[in]	RevDataΪӦ����������ָ��
 *	@return	void
 *	@note
 -Ŀǰ֧�ֵĵ�ַ��EEPROM�ĵ�ַ
 *********************************************************************************************************
 */
void WriteMemoryByAddress_v_g(BYTEPTR RevData) {
#define WM_ADRBYTES (RevData[0]&0x0F)
#define WM_DATALENBYTES (RevData[0]>>4)
uint8_T    cmdLen;
uint32_T   memAdr;
uint16_T   dataLen;
uint16_T   Index;
uint16_T   cnt;
RspFmt_u8_Sig=POS_RSP;/*��Ӧ���͸�ֵ*/
SI_u8_Tmp=WRITE_MEMORY_BY_ADDRESS;
DefSub_u8_Tmp=0x00;/*Sub״̬��ֵ*/

Index=ECU_SUPPROT_ADDRESSLEN+MAX_DATANUMBYTE+1;/*дEEPROM��ʼԪ��*/

adrLenFmtId_u8_Sig =RevData[0];
/*---------------------��ȡ��ַ--------------------------------*/
memAdr=RevData[1];
memAdr=(memAdr<<8)+RevData[2];
memAdr=(memAdr<<8)+RevData[3];
memAdr=(memAdr<<8)+RevData[4];
/*---------------------��ַ��¼--------------------------------*/
BackUpMemInfor_u8_Sig[0]=RevData[1];/*��ַ��¼*/
BackUpMemInfor_u8_Sig[1]=RevData[2];/*��ַ��¼*/
BackUpMemInfor_u8_Sig[2]=RevData[3];/*��ַ��¼*/
BackUpMemInfor_u8_Sig[3]=RevData[4];/*��ַ��¼*/
/*---------------------��ȡ��ַ--------------------------------*/
dataLen=RevData[5];
dataLen=(dataLen<<8)+RevData[6];
cmdLen=ECU_SUPPROT_ADDRESSLEN+MAX_DATANUMBYTE+2+dataLen;/*�����*/
dataLen=dataLen>>1;
/*---------------------��ȡ��ַ--------------------------------*/
BackUpMemInfor_u8_Sig[4] =RevData[5]; /*���ȼ�¼*/
BackUpMemInfor_u8_Sig[5] =RevData[6]; /*���ȼ�¼*/
MemAdr_u32_Sig=memAdr;/*��ַ��ֵ*/
MemDataLen_u16_Sig =dataLen;/*���ݳ���*/


/*----------------------Session Not Support----------------------*/
if(SessionMode_u8_Sig!=EXTEND_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
{
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*�Ựģʽ������0x7F*/
}
/*----------------------Len Err----------------------*/
if(RevMsgLen_u16_Sig!=cmdLen && RspFmt_u8_Sig!=NEG_RSP) {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/  
}
/*----------------------SeedKey Err----------------------*/
if(LockMode_u8_Sig!=UnLock_Level &&  SessionMode_u8_Sig==EXTEND_SESSION && RspFmt_u8_Sig!=NEG_RSP)
{
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*δ���ܴ�����0x33*/
	
}
/*----------------------Over Range----------------------*/
if((WM_ADRBYTES!=ECU_SUPPROT_ADDRESSLEN ||WM_DATALENBYTES!=MAX_DATANUMBYTE) && RspFmt_u8_Sig!= NEG_RSP) {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=OVERRANGE_ERR;  /*��ʽ���Դ�����0x31*/
}

if(dataLen>MAX_MEMWRITENUM && RspFmt_u8_Sig!= NEG_RSP) {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=OVERRANGE_ERR;  /*���ȳ��޴�����0x31*/
}
if((memAdr<RWDATA_MINADR ||(memAdr+dataLen-1)>RWDATA_MAXADR) && RspFmt_u8_Sig!= NEG_RSP  )
{
 RspFmt_u8_Sig=NEG_RSP;
 NegRsp_u8_Sig=OVERRANGE_ERR;/*���ȳ��޴�����0x31*/
}

if(RspFmt_u8_Sig!= NEG_RSP) {
for(cnt=0;cnt<dataLen;cnt++)
{
	MemData_u16_Sig[cnt]= RevData[Index+(cnt*2)];/*��ֵд��ֵַ*/
	MemData_u16_Sig[cnt]=(MemData_u16_Sig[cnt]<<8)+RevData[Index+1+(cnt*2)];/*��ֵд��ֵַ*/
}
 WMemDataFLag_u8_Sig = 1;/*д��ַ��־λ��λ*/
 BackUpPosLen_u16_Sig=ECU_SUPPROT_ADDRESSLEN+MAX_DATANUMBYTE+1;/*��¼������Ӧ�ĳ���*/
 RspFmt_u8_Sig=NEG_RSP;
 NegRsp_u8_Sig=FLEXRSPTIME_ERR; /*��ʱ��0x78*/
}

if(RspFmt_u8_Sig==NEG_RSP  ) {
  RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
} 
else {
} 

}

/*!******************************************************************************************************
 *	@fn	void InputOutputControlById(BYTEPTR RevData)
 *	@brief �����������
 *	@author Matt Zhang
 *	@param[in]	RevDataΪӦ����������ָ��
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */

void InputOutputControlById(BYTEPTR RevData) 
{
#define CONTROLPAPA RevData[2]
uint16_T dataId=0;
RspFmt_u8_Sig=POS_RSP;/*��Ӧ���͸�ֵ*/
SI_u8_Tmp=INPUT_OUTPUT_CONTROL_BY_IDENTIFIER;
DefSub_u8_Tmp=0x00;/*Sub״̬��ֵ*/

dataId= RevData[0];/*DID ��ȡ��ֵ*/
dataId=(dataId<<8)+  RevData[1];/*DID ��ȡ��ֵ*/
/*----------------------Session Not Support----------------------*/
if(SessionMode_u8_Sig!=EXTEND_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
{
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*�Ựģʽ������0x7F*/
}
/*---------------------Len Err----------------------*/
if(RevMsgLen_u16_Sig<5 && RspFmt_u8_Sig!=NEG_RSP )
{
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*���Ȳ��Դ�����0x13*/ 	
}
/*---------------------SeedKey Err----------------------*/
if(SessionMode_u8_Sig==EXTEND_SESSION && LockMode_u8_Sig!=UnLock_Level && RspFmt_u8_Sig!=NEG_RSP)
{
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*δ���ܴ�����0x33*/
}
/*---------------------Condition Err----------------------*/
if(CONTROLPAPA!=0x00 && CONTROLPAPA!=0x02 && CONTROLPAPA!=0x03 && RspFmt_u8_Sig!=NEG_RSP)
{
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CONDITION_NOTSURRORT_ERR;/*���������������0x22*/
}
if(RspFmt_u8_Sig!=NEG_RSP)
{
 	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=OVERRANGE_ERR;  /*Ŀǰû��֧�ֵ�DID������ȫ��������0x31*/
}

if(RspFmt_u8_Sig==NEG_RSP  ) {
  RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
} 
else {
} 
}
/*!******************************************************************************************************
 *	@fn	void RoutineControl_v_g(BYTEPTR RevData)
 *	@brief �����ƺ���
 *	@author Matt Zhang
 *	@param[in]	RevDataΪӦ����������ָ��
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void RoutineControl_v_g(BYTEPTR RevData) 
{
   #define ROUTINE_ADRBYTES (__byte(&RevData[2], LSB)&0x0F)
   #define ROUTINE_DATALENBYTES (__byte(&RevData[2], LSB)>>4)
   uint8_T  subFunction;
   uint8_T  routineId;

   RspFmt_u8_Sig=POS_RSP;/*��Ӧ���͸�ֵ*/
   //subFunction=RevData[0];/*Sub��ֵ*/
   subFunction=__byte(RevData, MSB);
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*��Ӧ״̬��ֵ*/
   subFunction=subFunction&0x7F;/*Sub_Funtionȥ��λ����*/
   SI_u8_Tmp=ROUTINE_CONTROL; 
   DefSub_u8_Tmp=0x01;	/*Sub״̬��ֵ*/
   
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;/*��Ӧ���ݸ�ֵ*/
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],MSB,subFunction);
   /*----------------DID��ֵ-----------------*/
   routineId = __byte(&RevData[1], LSB)*256;
   routineId +=__byte(&RevData[1], MSB);
   //routineId = (routineId<<8)+RevData[2];

   /*----------------------Sub Not Support----------------------*/
   if(subFunction!=0x01 && RspFmt_u8_Sig!=NEG_RSP)
   {
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR;  /*���Ȳ��Դ�����0x13*/ 	
   }
   /*----------------------SeedKey Err----------------------*/
   if(SessionMode_u8_Sig==EXTEND_SESSION &&(LockMode_u8_Sig!=UnLock_Level)&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;
   }
   
   /*----------------------DID Err----------------------*/
   if((routineId!=0xAF10)&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=OVERRANGE_ERR;  	
   }
  
   if(RspFmt_u8_Sig!=NEG_RSP)
   {
   	switch(routineId)
   	{
   		
   		case 0xAF10:/*���������*/

		CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], &RevData[1], LSB, LSB, 2);
		EEPROM_Backup();
   		break;
   		
   		default:
			RspFmt_u8_Sig = NEG_RSP;

   		break;
   	}
   } 
   
   if(RspFmt_u8_Sig==NEG_RSP)
   {
	  RspMsgLen_u16_Sig = 2;
   }
   else{
      RspMsgLen_u16_Sig = 3; 
   }
 }
 

#if APP_CODE==0
/*!******************************************************************************************************
 *	@fn	void RequestDownload_v_g(BYTEPTR RevData)
 *	@brief �������غ���
 *	@author Matt Zhang
 *	@param[in]	RevDataΪӦ����������ָ��
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void RequestDownload_v_g(BYTEPTR RevData) 
{
#define  DATAFMT            RevData[0]
#define  RQ_ADRBYTES       (RevData[1]&0x0F)
#define  RQ_DATALENBYTES   (RevData[1]>>4)
uint8_T    cmdLen;
uint32_T   dnloadAdr;
uint32_T   dnloadLen;
uint16_T   maxBlock;

RspFmt_u8_Sig=POS_RSP;/*��Ӧ���͸�ֵ*/
SI_u8_Tmp=REQUEST_DOWNLOAD;
DefSub_u8_Tmp=0x00;	/*Sub״̬��ֵ*/
cmdLen = WRITE_FLASH_ADRBYTES+WRITE_FLASH_DATALENBYTES+3;/*����ȸ�ֵ*/

/*-------------���ص�ַ��ֵ-----------------------*/
dnloadAdr=RevData[2];
dnloadAdr=(dnloadAdr<<8)+RevData[3];
dnloadAdr=(dnloadAdr<<8)+RevData[4];
dnloadAdr=(dnloadAdr<<8)+RevData[5];
/*-------------���س��ȸ�ֵ-----------------------*/
dnloadLen=RevData[6];
dnloadLen=(dnloadLen<<8)+RevData[7];
dnloadLen=(dnloadLen<<8)+RevData[8];
dnloadLen=(dnloadLen<<8)+RevData[9];
dnloadLen=dnloadLen>>1;
/*-------------Session Not Support-----------------------*/
if(SessionMode_u8_Sig!=PROGRANMMING_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
{
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;
}
/*-----------------------Len Err-----------------------*/
if(RevMsgLen_u16_Sig!= cmdLen && RspFmt_u8_Sig!=NEG_RSP)
{ 
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;
}
/*-----------------------SeedKey Err-----------------------*/
if(SessionMode_u8_Sig==PROGRANMMING_SESSION && LockMode_u8_Sig!=UnLock_Level2 && RspFmt_u8_Sig!=NEG_RSP)
{
     RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;
}
/*-----------------------Over Range-----------------------*/
if(DATAFMT!=0x00  && RspFmt_u8_Sig!= NEG_RSP)
{
    RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=OVERRANGE_ERR;
}
/*-----------------------Over Range-----------------------*/
if((RQ_ADRBYTES!=WRITE_FLASH_ADRBYTES || RQ_DATALENBYTES!=WRITE_FLASH_DATALENBYTES) && RspFmt_u8_Sig!= NEG_RSP) {
       RspFmt_u8_Sig=NEG_RSP;
       NegRsp_u8_Sig=OVERRANGE_ERR;
 }
/*-----------------------Over Range-----------------------*/
if((dnloadAdr+dnloadLen)>(ERASE_FLASH_SECTORB_ADR+ERASE_FLASH_SECTORB_LENGTH+ERASE_FLASH_SECTORD_LENGTH) && RspFmt_u8_Sig!= NEG_RSP)
{
   	    RspFmt_u8_Sig=NEG_RSP;
        NegRsp_u8_Sig=OVERRANGE_ERR;  
}
/*-----------------------Over Range-----------------------*/
if( dnloadAdr<ERASE_FLASH_SECTORF_ADR&& RspFmt_u8_Sig!= NEG_RSP)
{
   	    RspFmt_u8_Sig=NEG_RSP;
        NegRsp_u8_Sig=OVERRANGE_ERR;  
}
/*-----------------------Over Range-----------------------*/
if(dnloadAdr<(ERASE_FLASH_SECTORF_ADR+ERASE_FLASH_SECTORF_LENGTH)\
&&(dnloadAdr+dnloadLen)>(ERASE_FLASH_SECTORF_ADR+ERASE_FLASH_SECTORF_LENGTH)&& RspFmt_u8_Sig!= NEG_RSP)
{
   	    RspFmt_u8_Sig=NEG_RSP;
        NegRsp_u8_Sig=OVERRANGE_ERR;  
}
/*-----------------------Over Range-----------------------*/
if(dnloadAdr>=ERASE_FLASH_SECTORC_ADR && dnloadAdr<ERASE_FLASH_SECTORB_ADR&& RspFmt_u8_Sig!= NEG_RSP)
{
   	    RspFmt_u8_Sig=NEG_RSP;
        NegRsp_u8_Sig=OVERRANGE_ERR; 
}
/*-----------------------Over Range-----------------------*/
if((dnloadAdr+dnloadLen)>=ERASE_FLASH_SECTORC_ADR && (dnloadAdr+dnloadLen)<ERASE_FLASH_SECTORB_ADR\
&& RspFmt_u8_Sig!= NEG_RSP)
{
   	    RspFmt_u8_Sig=NEG_RSP;
        NegRsp_u8_Sig=OVERRANGE_ERR; 
} 
/*-----------------------Over Range-----------------------*/
if(dnloadAdr== ERASE_FLASH_SECTORD_ADR && dnloadLen!=ERASE_FLASH_SECTORD_LENGTH && RspFmt_u8_Sig!= NEG_RSP  )
{
     RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=OVERRANGE_ERR;  	
}
/*-----------------------Over Range-----------------------*/
if(RspFmt_u8_Sig!= NEG_RSP)
{
	/*-----------------------�ж��Ƿ����һ������-----------------------*/
	if(dnloadAdr== ERASE_FLASH_SECTORD_ADR && dnloadLen==ERASE_FLASH_SECTORD_LENGTH)
	{
		EndHex_u8_Sig=1;/*���һ��������λ*/
	}
	else
	{
		EndHex_u8_Sig=0;
	}
	maxBlock = MAX_NUM_BLOCK;/*���Block���ݸ�ֵ*/
	Rsp_Msg.ReqSendMsg_u8_Tmp [1]=LEN_MFT;/*��ʽ��ֵ*/
	Rsp_Msg.ReqSendMsg_u8_Tmp [2]=(uint8_T)(maxBlock>>8);/*Block��С��ֵ����Ӧ����*/
	Rsp_Msg.ReqSendMsg_u8_Tmp [3]=(uint8_T)(maxBlock);/*Block��С��ֵ����Ӧ����*/
	WFlashAdr_u32_Sig = dnloadAdr;/*��ַ��ֵ*/
    WriteMemLen_u32_Sig=dnloadLen;/*���ȸ�ֵ*/
    ReqTranExitStatus_u8_Sig = Req_Sucess;/*����״̬��ֵ*/
    TransferLen_u32_Sig = 0;/*���ͳ�����0*/
    BlockCnt_u8_Sig=1;/*Blockֵ��1*/
    TranRevCnt_u32_Sig = 0;/*�������ݼ�����0*/
    crcData_u32_Sig = 0;/*CrcУ��ֵ��ֵ0*/
}


if(RspFmt_u8_Sig==NEG_RSP  ) {
  RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
} 
else {
  RspMsgLen_u16_Sig=3;/*�������ݵĳ���*/
} 

}
/*!******************************************************************************************************
 *	@fn	void TansferData_v_g(BYTEPTR RevData)
 *	@brief �������ݺ���
 *	@author Matt Zhang
 *	@param[in]	RevDataΪӦ����������ָ��
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void TansferData_v_g(BYTEPTR RevData)
{
#define  BLOCKCOUNTER      RevData[0] 
uint16_T wflashlen;
uint8_T  cnt;
RspFmt_u8_Sig=POS_RSP;/*��Ӧ���͸�ֵ*/
SI_u8_Tmp=TRANSFER_DATA;
DefSub_u8_Tmp=0x00;	/*Sub״̬��ֵ*/
TranRevCnt_u32_Sig = 0;/*���ͼ�����0*/
/*-------------Session Not Support-----------------------*/
if(SessionMode_u8_Sig!=PROGRANMMING_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
{
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;
}
/*----------------------Len Err-------------------------*/
if(RevMsgLen_u16_Sig>MAX_NUM_BLOCK && RspFmt_u8_Sig!=NEG_RSP)
{ 
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;
}
/*----------------------SeedKey Err-------------------------*/
if(SessionMode_u8_Sig==PROGRANMMING_SESSION && LockMode_u8_Sig!=UnLock_Level2 && RspFmt_u8_Sig!=NEG_RSP)
{
     RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;
}
/*----------------------Order Err-------------------------*/
if((ReqTranExitStatus_u8_Sig != Req_Sucess && ReqTranExitStatus_u8_Sig != Tran_Sucess)&& RspFmt_u8_Sig!=NEG_RSP)
{
	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=ORDER_ERR;
}
/*----------------------Block Cnt Err-------------------------*/
if(BlockCnt_u8_Sig!=BLOCKCOUNTER && RspFmt_u8_Sig!=NEG_RSP)
{
 	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=BLOCKSN_ERR;
}
/*----------------------Len To long-------------------------*/
if(TransferLen_u32_Sig>WriteMemLen_u32_Sig && RspFmt_u8_Sig!=NEG_RSP)
{
	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=TRANDATA_STOP_ERR;
}

if(RspFmt_u8_Sig!=NEG_RSP)
{
WFlashFlag_u8_Sig=1;/*дFlash��־λ*/
wflashlen = RevMsgLen_u16_Sig-2;/*��ȡ��Ч���ݳ���*/
wflashlen= wflashlen>>1;/*дFlash�ĳ���*/
for(cnt=0;cnt<wflashlen;cnt++)
{
	FlashWBuffer_u16_Sig[cnt]= RevData[1+(cnt*2)];/*дFlashBuffer���ݸ�ֵ*/
	FlashWBuffer_u16_Sig[cnt]=(FlashWBuffer_u16_Sig[cnt]<<8)+RevData[2+(cnt*2)];/*дFlashBuffer���ݸ�ֵ*/

	TranBuff_u8_Sig[TranRevCnt_u32_Sig]=RevData[1+(cnt*2)];/*Crc��ҪУ������ݸ�ֵ*/
	TranBuff_u8_Sig[TranRevCnt_u32_Sig+1]=RevData[2+(cnt*2)];/*Crc��ҪУ������ݸ�ֵ*/
	TranRevCnt_u32_Sig=TranRevCnt_u32_Sig+2;
	FlashLen_u32_Sig=FlashLen_u32_Sig+2;/*����дFlash�����ݳ��ȼ���*/
}
/*--------------------------------CRCУ�����-------------------------------*/
crcData_u32_Sig=GenerateCRC32(TranBuff_u8_Sig, wflashlen, crcData_u32_Sig);
crcData_u32_Sig=0xFFFFFFFF-crcData_u32_Sig;

BootWFalshLen_u16_Sig = wflashlen;/*BootдFlash����*/
TransferLen_u32_Sig = TransferLen_u32_Sig+wflashlen;/*ÿһ�������ܹ����͵����ݳ���*/
TranBlock_u8_Sig=BLOCKCOUNTER;
RspFmt_u8_Sig=NEG_RSP;
NegRsp_u8_Sig=FLEXRSPTIME_ERR;  /*��ʱ0x78*/
if(BlockCnt_u8_Sig<0xFF)
{
BlockCnt_u8_Sig++;/*block counter����*/
}
else
{
BlockCnt_u8_Sig=0;		
}
ReqTranExitStatus_u8_Sig = Tran_Sucess;/*���̸�ֵ*/
}

if(RspFmt_u8_Sig==NEG_RSP)
{
 RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
}
else
{
 RspMsgLen_u16_Sig=1;/*�������ݵĳ���*/
}
}
/*!******************************************************************************************************
 *	@fn	void RequestTansferExit_v_g(BYTEPTR RevData)
 *	@brief �������ݴ����˳�����
 *	@author Matt Zhang
 *	@param[in]	RevDataΪӦ����������ָ��
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void RequestTansferExit_v_g(BYTEPTR RevData)
{
#define  CRCTYPE      RevData[0] 

RspFmt_u8_Sig=POS_RSP;/*��Ӧ���͸�ֵ*/
SI_u8_Tmp=REQUEST_TRANSFER_EXIT;
DefSub_u8_Tmp=0x00;	/*Sub״̬��ֵ*/
BackUpExit_u8_Sig = CRCTYPE;/*��¼��������*/
/*-------------Session Not Support-----------------------*/
if(SessionMode_u8_Sig!=PROGRANMMING_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
{
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;
}
/*-------------Len Err-----------------------*/
if(RevMsgLen_u16_Sig!=2 && RspFmt_u8_Sig!=NEG_RSP)
{ 
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=CMD_LENGTH_ERR;
}
/*-------------Len Err-----------------------*/
if(CRCTYPE!=0x00 && CRCTYPE!=0x01 && RspFmt_u8_Sig!=NEG_RSP)
{
	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR;
}
/*-------------SeedKey Err-----------------------*/
if(SessionMode_u8_Sig==PROGRANMMING_SESSION && LockMode_u8_Sig!=UnLock_Level2 && RspFmt_u8_Sig!=NEG_RSP)
{
      RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;
}
/*-------------Order Err-----------------------*/
if(ReqTranExitStatus_u8_Sig!=Tran_Sucess&& RspFmt_u8_Sig!=NEG_RSP)
{
 	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=ORDER_ERR;
}
/*----------------------Data Len Err-------------------------*/
if(TransferLen_u32_Sig!=WriteMemLen_u32_Sig && RspFmt_u8_Sig!=NEG_RSP)
{
	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=ORDER_ERR;
}

if(RspFmt_u8_Sig!=NEG_RSP)
{
	Rsp_Msg.ReqSendMsg_u8_Tmp [1]=CRCTYPE;/*Crc Type��ֵ*/
	
	switch(CRCTYPE)
	{
		case 0:
		RspMsgLen_u16_Sig=1;/*�������ݵĳ���*/
		break;
		case 1:
		/*-------------Crc ��ֵ��Ӧ����---------------*/
        Rsp_Msg.ReqSendMsg_u8_Tmp [2]=(uint8_T)(crcData_u32_Sig>>24);
        Rsp_Msg.ReqSendMsg_u8_Tmp [3]=(uint8_T)(crcData_u32_Sig>>16);
        Rsp_Msg.ReqSendMsg_u8_Tmp [4]=(uint8_T)(crcData_u32_Sig>>8);
        Rsp_Msg.ReqSendMsg_u8_Tmp [5]=(uint8_T)(crcData_u32_Sig);
        RspMsgLen_u16_Sig=5;/*�������ݵĳ��ȣ���ȥSI��N_SI��*/ 	
		break;
		
		default:
		break;
	
	}	
	if(EndHex_u8_Sig==1)/*�������ݱ�־λ�ж�*/
	{
	if(FlashLen_u32_Sig>52800)/*�ܵĳ����ж�*/
	{
	 SvfEep_u8_Sig=1;/*SVFдEEPROM��־λ*/
	 SVF_u16_Par=1;/*SVF��λ*/
	 Jump_u8_Sig =1;/*��ת��־λ��λ*/
	 RspFmt_u8_Sig=NEG_RSP;
	 NegRsp_u8_Sig=FLEXRSPTIME_ERR;  /*��ʱ0x78*/
	 FlashLen_u32_Sig = 0;/*�ܳ�����0*/
	}
	 EndHex_u8_Sig = 0;	
	}
    ReqTranExitStatus_u8_Sig = Exit_Sucess;/*���̸�ֵ*/
    TransferLen_u32_Sig = 0;/*ʵ�ʷ������ݳ�����0*/

    BlockCnt_u8_Sig=1;/*�����ֵ��λ1*/
    WriteMemLen_u32_Sig=0;/*Ҫ�������ݳ�����0*/


}

if(RspFmt_u8_Sig==NEG_RSP)
{
 RspMsgLen_u16_Sig=2;/*�������ݵĳ���*/
}
else
{
 
}

}

#endif
/*!******************************************************************************************************
 *	@fn	void AppUdsService_v_g(BYTEPTR Services)
 *	@brief ���������Ⱥ���
 *	@author Matt Zhang
 *	@param[in]	ServicesΪӦ����������ָ��
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void AppUdsService_v_g(BYTEPTR Services) 
{
 #define   ServiceId   __byte(Services,0)
 //uint8_T ServiceId;
 //ServiceId = __byte(&Services[0],0);
 
 RspFmt_u8_Sig=POS_RSP;
 switch(ServiceId) 
 {  
 
  /*With Sub-Function UDS Service*/
  case DIAGNOSTIC_SESSION_CONTROL:/*�Ựģʽ�л�*/
  DiagnosticSessionControl_v_g(Services);
  break;
  
  case ECU_RESET:/*ECU��������*/
  EcuReset_v_g(Services);
  break;
  
  case SECURITY_ACCESS:   /*��ȫ�������*/
  SecurityAccess_v_g(Services);
  break;
  
  case COMMUNICATION_CONTROL: /*ͨ�ŷ������*/
  CommunicationControl_v_g(Services);
  break;
  
  case CONTROL_DTC_SETTING:   /*����DTC*/
  ControlDTCSetting_v_g(Services);
  break;
  
  case TESTER_PRESENT:   /*����*/
  TesterPresent_v_g(Services);
  break;

  case READ_DTC_INFORMATION: /*��ȡDTC��Ϣ*/
  ReadDtcMsg_v_g(Services);
  break;
  

  case ROUTINE_CONTROL: /*������*/
#if APP_CODE==1
  RoutineControl_v_g(Services);
#endif
  break;
  
  /*Without Sub-Function UDS Service*/ 
  case READ_DATA_BY_IDENTIFIER: /*ͨ��DID��ȡ����*/
  ReadDataById_v_g(Services);
  break;

  case READ_MEMORY_BY_ADDRESS : /*ͨ����ַ��ȡ����*/
  ReadMemoryByAddress_v_g(Services);
  break;
  
  case WRITE_DATA_BY_IDENTIFIER:/*ͨ��DIDд����*/
  WriteDataById_v_g(Services);
  break;
                             
  case WRITE_MEMORY_BY_ADDRESS:/*ͨ����ַд����*/
  WriteMemoryByAddress_v_g(Services);
  break;
  
  case CLEAR_DIAGNOSTIC_INFORMATION:/*���������*/
  ClearDiagImfor_v_g(Services);
  break;
  
  case INPUT_OUTPUT_CONTROL_BY_IDENTIFIER:/*�����������*/
  InputOutputControlById(Services); 
  break;
  default:
  SI_u8_Tmp=ServiceId;
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=SEVICE_NOTSUPPORT_ERR; 
  RspMsgLen_u16_Sig = 2; 
  break;  
 }
 
}
/*!******************************************************************************************************
 *	@fn	void AppSendRspMsg(void)
 *	@brief Ӧ�ò㷢�ͻ�Ӧ���ݺ���
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void AppSendRspMsg(void) 
{                      
 AppReqNetSend_v_g(Rsp_Msg,&UdsRequest); 
}
/*!******************************************************************************************************
 *	@fn	void UDSApp_v_g(void)
 *	@brief Udsִ�к�������Ҫ����ʱ���е���
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void UDSApp_v_g(void) 
{
#if APP_CODE==0
	/* ---------Canȡ���ĺ���---------------*/
	CanOutHandel_v_g();
#endif
	/*------------- �����ִ�к���------------*/
 	NetworkLayerServices_GF_step();
 	/*------------- ʱ�䴦����------------*/
 	TimeDual_v_g();
 #if APP_CODE==0
 	/*------------- дFlash������------------*/
 	WriteFlashDual();
 	/*------------- ����Flash������------------*/
 	EraseFlashDual();
 #endif
 #if APP_CODE==1
 	/*------------- Dtc������------------*/
     DtcCycleDef_v_g();
 #endif
     /*-------------дEEPROM������------------*/
 	 //SaveData_v_g();
 	/*------------- Reset������------------*/
     SwReset_v_g();
     /*-------------���ݵ�ַ�����ݴ�����------------*/
 	 ReadMemDual();
 	 /*-------------���ݵ�ַд���ݴ�����------------*/
 	 //WriteMemDual();
 	 /*-------------��֡�ж�------------*/
	if(IndicationCmd_u8_Sig==1){ 	
	  IndicationCmd_u8_Sig=0;
	  AppReceiveFFind_v_g();/*��֡������*/
	}
	 /*-------------����ȷ�������ж�------------*/
	if(IndicationCmd_u8_Sig==2){ 	
	  IndicationCmd_u8_Sig = 0;
	  P2CntStart_u8_Sig    = 1;/*��Ӧ��ʱ��־��λ*/
	  S3Sever_u16_Sig      = 0;/*�Ựģʽ��ʱ��0*/
	  AppRevNetData_v_g(&UdsIndication,Req_Msg);/*Ӧ�ò��ȡ��ֵ*/
	  if(UDS_Timeout_u8_Sig ==0 && SFLength_Ovrn_u8_Sig==0 \
			&&  FrameErr_u8_Sig==0)/*�ж����ޱ���*/
	  {
	  AppUdsService_v_g(Req_Msg.IndReceiveMsg_u8_Sig); /*����������*/
	  }
	  if(!ResponseMechanism_v_s() && UDS_Timeout_u8_Sig ==0 && SFLength_Ovrn_u8_Sig==0 \
			&&  FrameErr_u8_Sig==0 )/*�ж����ޱ����Ƿ�Ҫ��Ӧ*/
	  {
	     AppSendRspMsg();/*��������㷢������*/
	  }

	}

	if(ConfirmCmd_u8_Sig==1){
	  ConfirmCmd_u8_Sig=0;
	  AppConFrimNet_v_g(&UdsConfirm);/*ȷ�Ϻ�������*/
	}
}  

/*!******************************************************************************************************
 *	@fn	uint8_T ResponseMechanism_v_s()
 *	@brief ��Ӧ���ƺ���
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	uint8_T �Ƿ��Ӧ״̬λ
 *	@note
 -
 *********************************************************************************************************
 */
uint8_T ResponseMechanism_v_s() 
{
/*-----------------------------------------------------
*��TAtype_phiscalģʽֻ��suppress-PosRspMsg-Indication-BitΪ��ʱ��ID��Sub��֧�֣���������һ��������֧�ֵ�
*��TAtype_functionalģʽ��suppress-PosRspMsg-Indication-BitΪ�٣�ID��֧�֡�Sub��֧�֣�һ����������֧�ֵ� 
*��TAtype_functionalģʽ��suppress-PosRspMsg-Indication-BitΪ�棬ID��֧�֡�Sub��֧�֣�һ����������֧�ֵġ�������һ������֧�� 
-------------------------------------------------------*/
 if (AdrType_u8_Sig==TAtype_phiscal)
 {
   if(supPosRspMsgIndBit_u8_Tmp==0x80 && RspFmt_u8_Sig==POS_RSP && DefSub_u8_Tmp==0x01)
   {
   	return 1;
   }
 	
 }
 if(AdrType_u8_Sig==TAtype_functional)
 {
   if(NegRsp_u8_Sig==SUBFUNCTION_NOTSUPPORT_ERR && DefSub_u8_Tmp==0x01)
   {
   	return 1;
   }
   
   if(NegRsp_u8_Sig==SESSIONNOTSUPPROT_ERR && DefSub_u8_Tmp==0x01)
   {
   	return 1;
   }
   
 }
return 0;
}
/*!******************************************************************************************************
 *	@fn	void  AppReceiveFFind_v_g()
 *	@brief Ӧ�ò���֡������
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void  AppReceiveFFind_v_g()
{
	  P2CntStart_u8_Sig    = 1;/*��Ӧ��ʱ��־��λ*/
	  S3Sever_u16_Sig      = 0;/*�Ựģʽ��ʱ��0*/
}
/*!******************************************************************************************************
 *	@fn	void TimeDual_v_g(void)
 *	@brief Ӧ�ò�ʱ����ƴ�����
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void TimeDual_v_g(void)
{
 if(P2CntStart_u8_Sig==1) {/*�жϼ�ʱ�Ƿ�ʼ*/
    P2Sever_u16_Sig++;/*�������ۼ�*/
    if(P2Sever_u16_Sig==P2_CANSERVER) {/*�жϼ������Ƿ�ﵽ�趨ֵ*/
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=FLEXRSPTIME_ERR;/*��Ӧ��ǿ��ʱ����*/
    RspMsgLen_u16_Sig = 2;/*��Ӧ����*/
    P2FlexCntStart_u8_Sig=1;/*��ǿ����ʱ����*/
    }
  } 
  else {
    P2Sever_u16_Sig=0; /*��������0*/
  }
  
  if(P2FlexCntStart_u8_Sig==1) {/*�жϼ�ʱ�Ƿ�ʼ*/
    P2FlexSever_u16_Sig++;
    if(P2FlexSever_u16_Sig==P2_FLEXCANSERVER ) {/*�жϼ������Ƿ�ﵽ�趨ֵ*/
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=FLEXRSPTIME_ERR; /*��Ӧ��ǿ��ʱ����*/
    RspMsgLen_u16_Sig = 2;	/*��Ӧ����*/
    }
    else
    {
    P2FlexSever_u16_Sig = 0;	
    }
    
  } 
  else {
   P2FlexSever_u16_Sig=0; /*��������0*/
  }
  
  if(SessionMode_u8_Sig!= DEFAULT_SESSION ) {/*�жϻỰģʽ�Ƿ���Ĭ�ϻỰģʽ*/
    S3Sever_u16_Sig++;/*����������*/
    if(S3Sever_u16_Sig==S3SERVER) {/*�жϼ������Ƿ�ﵽ�趨ֵ*/
    SessionMode_u8_Sig = DEFAULT_SESSION;
    EraseFStatus_u8_Sg=0;
    EraseABStatus_u8_Sg=0;
    LockMode_u8_Sig=Lock;
    NormalComTx_u8_Sig = 1;
    NormalComRx_u8_Sig = 1;
    }
  } 
  else
  {
  	S3Sever_u16_Sig=0;	
  }
  
  /*--------------------------�жϽ��ܴ����Ƿ������-------------------------------*/
if(UnLockTimeOver_u8_Sig==1 && UnlockLimitTime_u16_Sig==SEED_KEY_TIMES && ScurReqTimes_u8_Sig!=0)
  {
  	Secur_u32_Sig++;/*����������*/
  	if(Secur_u32_Sig==SECUR_LIMIT_TIME)/*�жϼ���ֵ*/
  	{
  		UnlockLimitTime_u16_Sig--;/*���ܴ��������ȥ1*/
  		UnLockTimeOver_u8_Sig = 0;
  		Secur_u32_Sig=0;/*��������0*/
  	}
  }
  
 /*----------------------Power On /Reset----------------------------------*/ 
 if(UnlockLimitTime_u16_Sig!=0 && ScurReqTimes_u8_Sig==0)
  {
  	if(UnlockLimitTime_u16_Sig>SECUR_LIMIT_TIME)
    {
	   UnlockLimitTime_u16_Sig=SEED_KEY_TIMES;
    }
  	Secur_u32_Sig++;/*����������*/
  	if(Secur_u32_Sig==SECUR_LIMIT_TIME)/*�жϼ���ֵ*/
  	{
  		UnlockLimitTime_u16_Sig--;/*���ܴ��������ȥ1*/
  		UnLockTimeOver_u8_Sig = 0;
  		ScurReqTimes_u8_Sig=1;
  		Secur_u32_Sig=0;
  	}
  }
} 


/*!******************************************************************************************************
 *	@fn	uint32_T  GenerateCRC32(BYTEPTR DataBuf, uint32_T len, uint32_T oldcrc32)
 *	@brief CRC32У�麯��
 *	@author Matt Zhang
 *	@param[in]	DataBufУ�������ָ�룬lenУ������ݳ��ȣ�oldcrc32У��ֵ����
 *	@return	uint32_TУ��ֵ
 *	@note
 -
 *********************************************************************************************************
 */
uint32_T  GenerateCRC32(BYTEPTR DataBuf, uint32_T len, uint32_T oldcrc32)
{
	unsigned long i; 
	for(i=0; i<len; ++i) 
	{    
    // oldcrc32 = ((oldcrc32<<8))^crc_32_tab[(long)((oldcrc32>>24)^DataBuf[i])];  
    }  
    
    return oldcrc32; 
}
/*!******************************************************************************************************
 *	@fn	uint32_T seedToKey (uint32_T seed, uint32_T MASK)
 *	@brief SeedKeyУ�麯��
 *	@author Matt Zhang
 *	@param[in]	seed���ӣ�MASKУ������
 *	@return	uint32_TΪKey
 *	@note
 -
 *********************************************************************************************************
 */
 uint32_T SeedToKey_v_g (uint32_T Seed, uint32_T Mask)
{
uint32_T key = 0;
int i;
if (Seed !=0 )
{
for ( i=0; i<35; i++ )
{
if (Seed & 0x80000000)
{
	Seed = Seed <<1;
	Seed = Seed^Mask;
}
else
{
	Seed = Seed << 1;
}
}
key = Seed;
}
return key;
}

#if APP_CODE==1 
/*!******************************************************************************************************
 *	@fn	void DtcInit_v_s(void)
 *	@brief DTC��ʼ������
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
#if UDS_DTC_OPEN==1
void DtcInit_v_s(void)
{

/*-----------------------�����뼰״̬��ʼ��--------------------*/
   DtcNumb_u24a8_Par[U000187].byte1        = 0xC0;
   DtcNumb_u24a8_Par[U000187].byte2        = 0x01;
   DtcNumb_u24a8_Par[U000187].byte3        = 0x87;
   DtcStatus_u16a8_Par[U000187].Status.Byte  = 0x50;
   
   DtcNumb_u24a8_Par[U000387].byte1        = 0xC0;
   DtcNumb_u24a8_Par[U000387].byte2        = 0x03;
   DtcNumb_u24a8_Par[U000387].byte3        = 0x87;
   DtcStatus_u16a8_Par[U000387].Status.Byte  = 0x50;
   
   DtcNumb_u24a8_Par[U000288].byte1        = 0xC0;
   DtcNumb_u24a8_Par[U000288].byte2        = 0x02;
   DtcNumb_u24a8_Par[U000288].byte3        = 0x88;
  //DtcStatus_u16a8_Par[U000288].Severity=0x00;
   DtcStatus_u16a8_Par[U000288].Status.Byte  = 0x50;
   
   DtcNumb_u24a8_Par[P000112].byte1        = 0x00;
   DtcNumb_u24a8_Par[P000112].byte2        = 0x01;
   DtcNumb_u24a8_Par[P000112].byte3        = 0x12;
   //DtcStatus_u16a8_Par[U000111].Severity=0x00;
   DtcStatus_u16a8_Par[P000112].Status.Byte  = 0x50;
   
   
   DtcNumb_u24a8_Par[P000209].byte1        = 0x00;
   DtcNumb_u24a8_Par[P000209].byte2        = 0x02;
   DtcNumb_u24a8_Par[P000209].byte3        = 0x09;
   //DtcStatus_u16a8_Par[U000212].Severity=0x00;
   DtcStatus_u16a8_Par[P000209].Status.Byte  = 0x50;
   
   
   DtcNumb_u24a8_Par[P000396].byte1        = 0x00;
   DtcNumb_u24a8_Par[P000396].byte2        = 0x03;
   DtcNumb_u24a8_Par[P000396].byte3        = 0x96;
   //DtcStatus_u16a8_Par[U000313].Severity=0x00;
   DtcStatus_u16a8_Par[P000396].Status.Byte  = 0x50;
   
   
   DtcNumb_u24a8_Par[U000487].byte1        = 0xC0;
   DtcNumb_u24a8_Par[U000487].byte2        = 0x04;
   DtcNumb_u24a8_Par[U000487].byte3        = 0x87;
   //DtcStatus_u16a8_Par[U000414].Severity=0x00;
   DtcStatus_u16a8_Par[U000487].Status.Byte  = 0x50;
   
   DtcNumb_u24a8_Par[P000429].byte1        = 0x00;
   DtcNumb_u24a8_Par[P000429].byte2        = 0x04;
   DtcNumb_u24a8_Par[P000429].byte3        = 0x29;
   //DtcStatus_u16a8_Par[U000515].Severity=0x00;
   DtcStatus_u16a8_Par[P000429].Status.Byte  = 0x50;
  
   /*-----------------------������Extend���ݳ�ʼ��--------------------*/
  
   DtcExtend_u64a8_Par[U000187].FualtCnt       = 0x00;
   DtcExtend_u64a8_Par[U000187].PendCnt        = 0x00;
   DtcExtend_u64a8_Par[U000187].AgedCnt        = 0x00;
   DtcExtend_u64a8_Par[U000187].AgingCnt=0x00;
   
   DtcExtend_u64a8_Par[U000387].FualtCnt       = 0x00;
   DtcExtend_u64a8_Par[U000387].PendCnt        = 0x00;
   DtcExtend_u64a8_Par[U000387].AgedCnt        = 0x00;
   DtcExtend_u64a8_Par[U000387].AgingCnt=0x00;
   
   DtcExtend_u64a8_Par[U000288].FualtCnt       = 0x00;
   DtcExtend_u64a8_Par[U000288].PendCnt        = 0x00;
   DtcExtend_u64a8_Par[U000288].AgedCnt        = 0x00;
   DtcExtend_u64a8_Par[U000288].AgingCnt=0x00;
   
   DtcExtend_u64a8_Par[P000112].FualtCnt       = 0x00;
   DtcExtend_u64a8_Par[P000112].PendCnt        = 0x00;
   DtcExtend_u64a8_Par[P000112].AgedCnt        = 0x00;
   DtcExtend_u64a8_Par[P000112].AgingCnt=0x00;

   
   
   DtcExtend_u64a8_Par[P000209].FualtCnt        = 0x00;
   DtcExtend_u64a8_Par[P000209].PendCnt         = 0x00;
   DtcExtend_u64a8_Par[P000209].AgedCnt         = 0x00;
   DtcExtend_u64a8_Par[P000209].AgingCnt=0x00;
   
   
   DtcExtend_u64a8_Par[P000396].FualtCnt        = 0x00;
   DtcExtend_u64a8_Par[P000396].PendCnt         = 0x00;
   DtcExtend_u64a8_Par[P000396].AgedCnt         = 0x00;
   DtcExtend_u64a8_Par[P000396].AgingCnt=0x00;
   
   
   DtcExtend_u64a8_Par[U000487].FualtCnt        = 0x00;
   DtcExtend_u64a8_Par[U000487].PendCnt         = 0x00;
   DtcExtend_u64a8_Par[U000487].AgedCnt         = 0x00;
   DtcExtend_u64a8_Par[U000487].AgingCnt=0x00;

   
   DtcExtend_u64a8_Par[P000429].FualtCnt        = 0x00;
   DtcExtend_u64a8_Par[P000429].PendCnt         = 0x00;
   DtcExtend_u64a8_Par[P000429].AgedCnt         = 0x00;
   DtcExtend_u64a8_Par[P000429].AgingCnt        = 0x00;
   /*-----------------------������Snapshot���ݳ�ʼ��--------------------*/
   
   DtcSnapShot_u80a8_Par[U000288].SupBatt       =0x00;
   DtcSnapShot_u80a8_Par[U000288].Odreading     =0x00;
   DtcSnapShot_u80a8_Par[U000288].IgStatus      =0x00;
   DtcSnapShot_u80a8_Par[U000288].CoolTemp      =0x00;
   
   DtcSnapShot_u80a8_Par[P000112].SupBatt       =0x00;
   DtcSnapShot_u80a8_Par[P000112].Odreading     =0x00;
   DtcSnapShot_u80a8_Par[P000112].IgStatus      =0x00;
   DtcSnapShot_u80a8_Par[P000112].CoolTemp      =0x00;
   
   
   DtcSnapShot_u80a8_Par[P000209].SupBatt       =0x00;
   DtcSnapShot_u80a8_Par[P000209].Odreading     =0x00;
   DtcSnapShot_u80a8_Par[P000209].IgStatus      =0x00;
   DtcSnapShot_u80a8_Par[P000209].CoolTemp      =0x00;
   
   DtcSnapShot_u80a8_Par[P000396].SupBatt       =0x00;
   DtcSnapShot_u80a8_Par[P000396].Odreading     =0x00;
   DtcSnapShot_u80a8_Par[P000396].IgStatus      =0x00;
   DtcSnapShot_u80a8_Par[P000396].CoolTemp      =0x00;
   
   DtcSnapShot_u80a8_Par[U000487].SupBatt       =0x00;
   DtcSnapShot_u80a8_Par[U000487].Odreading     =0x00;
   DtcSnapShot_u80a8_Par[U000487].IgStatus      =0x00;
   DtcSnapShot_u80a8_Par[U000487].CoolTemp      =0x00;
   
   DtcSnapShot_u80a8_Par[P000429].SupBatt       =0x00;
   DtcSnapShot_u80a8_Par[P000429].Odreading     =0x00;
   DtcSnapShot_u80a8_Par[P000429].IgStatus      =0x00;
   DtcSnapShot_u80a8_Par[P000429].CoolTemp      =0x00;
   

   

}
/*!******************************************************************************************************
 *	@fn	void DtcCycleDef_v_g()
 *	@brief Dtcִ�к���
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void DtcCycleDef_v_g(void)
{
	uint8_T canBuserr;
	uint8_T nXerr;
	uint8_T nParkerr;
	uint8_T nUnParkerr;
	uint8_T overTemperr;
	uint8_T nNoLoaderr;
	uint8_T losPcuerr;
	uint8_T losVcmerr;
#if 0
    losPcuerr = 0;//��Ҫ��״̬λ��ֵ
    losVcmerr = 0;//��Ҫ��״̬λ��ֵ
	canBuserr =FltSt1Var.FLTST1.bit.nCAN_Bus_Error ;
	nXerr     = FltSt1Var.FLTST1.bit.nMot_Jam_Middle_Fault ;
	nParkerr  = FltSt1Var.FLTST1.bit.nPark_Stalled_Fault;
	nUnParkerr= FltSt1Var.FLTST1.bit.nUnpark_Stalled_Fault;
	nNoLoaderr = FltSt1Var.FLTST1.bit.nNo_Load_Fault;
	overTemperr =FltStVar.FLTST.bit.nOverTemp_Limit;
	#endif
   if(DtcOnOff_u8_Sig==DTCSETTING_ON)
   {
   	if(losPcuerr==1)
	{
	 DtcDual_v_g(U000387);/*losPcuerr*/
	  //WDtcSnapshot_v_g();//��Ҫ��Snapshot��Ӧ�Ĳ������뺯���У����忴WDtcSnapshot_v_g��������
	}
	if(losVcmerr==1)
	{
	  DtcDual_v_g(U000487);/*losVcmerr*/
	  //WDtcSnapshot_v_g();
	}	
	if(canBuserr==1)
	{
	  DtcDual_v_g(U000288);/*CAN_Bus_Error*/
	  //WDtcSnapshot_v_g();
	}
	if(nXerr==1)
	{
	  DtcDual_v_g(P000112);/*Mot_Jam_Middle_Fault*/
	  //WDtcSnapshot_v_g();
	}
	if(nParkerr==1)
	{
	  DtcDual_v_g(P000209);/*Park_Stalled_Fault*/
	  //WDtcSnapshot_v_g();
	}
	if(nUnParkerr==1)
	{
	 DtcDual_v_g(P000396);/*Unpark_Stalled_Fault*/
	 //WDtcSnapshot_v_g();
	}
	if(nNoLoaderr==1)
	{
	 DtcDual_v_g(U000187);/*No_Load_Fault*/
	 //WDtcSnapshot_v_g();
	}
	if(overTemperr==1)
	{
	DtcDual_v_g(P000429);/*OverTemp_Limit*/
	//WDtcSnapshot_v_g();
	}

    if(canBuserr==1 || nXerr==1||nParkerr==1||nUnParkerr==1\
    ||nNoLoaderr==1||overTemperr==1||losPcuerr==1||losVcmerr==1)
    {
    DtcEep_u8_Sig=1;/*дEEPROM��־λ*/
    }
}
else
{
}
}

/*!******************************************************************************************************
 *	@fn	void DtcDual_v_g(uint8_T DtcNumb)
 *	@brief Dtc���ϴ���
 *	@author Matt Zhang
 *	@param[in]	DtcNumbΪDTC�����
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void DtcDual_v_g(uint8_T DtcNumb)
{
  DtcStatus_u16a8_Par[DtcNumb].Status.Bits.testFailed= 1; /*ȷ�ϲ���ʧ�ܸ�ֵ*/
  DtcStatus_u16a8_Par[DtcNumb].Status.Bits.testFailedThisOperationCycle=1;/*���ι���ѭ�����ڲ���ʧ�ܸ�ֵ*/
  DtcStatus_u16a8_Par[DtcNumb].Status.Bits.testFailedSinceLastClear= 1;/*���ϴ������ʼ����ʧ�ܸ�ֵ*/
  DtcStatus_u16a8_Par[DtcNumb].Status.Bits.pendingDTC= 1;/*δȷ��ʧ�ܸ�ֵ*/
  DtcStatus_u16a8_Par[DtcNumb].Status.Bits.confirmedDTC=1;/*ȷ�ϸ�ֵ*/
}
/*!******************************************************************************************************
 *	@fn	void DtcBackFlashInit_v_g (void)
 *	@brief��ȡEEPROM��DTC������
 *	@author Matt Zhang
 *	@param[in]	viod
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void DtcBackFlashInit_v_g (void)
{
/*--��¼��һ�ε�DTC״̬--*/
LastDtcStatus_u16a8_Par[U000187].Status.Byte = DtcStatus_u16a8_Par[U000187].Status.Byte;
LastDtcStatus_u16a8_Par[U000387].Status.Byte = DtcStatus_u16a8_Par[U000387].Status.Byte;
LastDtcStatus_u16a8_Par[U000288].Status.Byte = DtcStatus_u16a8_Par[U000288].Status.Byte;
LastDtcStatus_u16a8_Par[P000112].Status.Byte = DtcStatus_u16a8_Par[P000112].Status.Byte;
LastDtcStatus_u16a8_Par[P000209].Status.Byte = DtcStatus_u16a8_Par[P000209].Status.Byte;
LastDtcStatus_u16a8_Par[P000396].Status.Byte = DtcStatus_u16a8_Par[P000396].Status.Byte;
LastDtcStatus_u16a8_Par[U000487].Status.Byte = DtcStatus_u16a8_Par[U000487].Status.Byte;
LastDtcStatus_u16a8_Par[P000429].Status.Byte = DtcStatus_u16a8_Par[P000429].Status.Byte;
/*--��ȡEEPROM����Ҫ�ĳ�ʼ��--*/
DtcStatus_u16a8_Par[U000187].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[U000187].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[U000387].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[U000387].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[U000288].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[U000288].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[P000112].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[P000112].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[P000209].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[P000209].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[P000396].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[P000396].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[U000487].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[U000487].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[P000429].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[P000429].Status.Bits.testNotCompletedThisOperationCycle = 1;



}

/*!******************************************************************************************************
 *	@fn	void ClearSignelDtc_v_g(uint8_T DtcNumb)
 *	@brief������������봦����
 *	@author Matt Zhang
 *	@param[in]	DtcNumbΪDTC�����
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void ClearSignelDtc_v_g(uint8_T DtcNumb)
{
	 DtcStatus_u16a8_Par[DtcNumb].Status.Byte  = 0x00;/*״̬��0*/
	 DtcExtend_u64a8_Par[DtcNumb].FualtCnt = 0; /*δȷ�ϼ�����0*/
     DtcExtend_u64a8_Par[DtcNumb].PendCnt  = 0;/*δȷ�ϼ�����0*/
     LastDtcStatus_u16a8_Par[DtcNumb].Status.Byte = DtcStatus_u16a8_Par[DtcNumb].Status.Byte;
     DtcSnapShot_u80a8_Par[DtcNumb].SupBatt       =0x00;/*Snapshot������0*/
     DtcSnapShot_u80a8_Par[DtcNumb].Odreading     =0x00;/*Snapshot������0*/
     DtcSnapShot_u80a8_Par[DtcNumb].IgStatus      =0x00;/*Snapshot������0*/
     DtcSnapShot_u80a8_Par[DtcNumb].CoolTemp      =0x00;/*Snapshot������0*/

}
/*!******************************************************************************************************
 *	@fn	void WDtcSnapshot_v_g(uint8_T DtcNumb,uint8_T SupBatt,uint32_T Odreading,uint8_T CoolTemp,uint8_T Igstatus )
 *	@brief SnapShot������
 *	@author Matt Zhang
 *	@param[in]	DtcNumbΪDTC����ţ�SupBatt�����ѹ��Odreading��������CoolTempΪ�¶ȣ�IgstatusΪIg��״̬
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void WDtcSnapshot_v_g(uint8_T DtcNumb,uint8_T SupBatt,uint32_T Odreading,uint8_T CoolTemp,uint8_T Igstatus )
{
	 DtcSnapShot_u80a8_Par[DtcNumb].SupBatt       =SupBatt;/*��ѹ��ֵ*/
     DtcSnapShot_u80a8_Par[DtcNumb].Odreading     =Odreading;/*��̸�ֵ*/
     DtcSnapShot_u80a8_Par[DtcNumb].IgStatus      =CoolTemp;/*�¶ȸ�ֵ*/
     DtcSnapShot_u80a8_Par[DtcNumb].CoolTemp      =Igstatus;/*Ig��ֵ*/

}


/*!******************************************************************************************************
 *	@fn	void  DTCExtendDual_v_g (void)
 *	@brief Extend���ݴ�����
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void  DTCExtendDual_v_g (void)
{
  uint8_T i;

  for(i = 0; i <DTCNUM; i++){
    if (DtcStatus_u16a8_Par[i].Status.Bits.testFailedThisOperationCycle == 0){/*�жϵ�ǰ�����Ƿ����ʧ��*/
      DtcExtend_u64a8_Par[i].AgingCnt = DtcExtend_u64a8_Par[i].AgingCnt + 1;  /*���������1*/
      
        if(DtcExtend_u64a8_Par[i].AgingCnt>= 40){/*������Ƿ����40*/
          DtcExtend_u64a8_Par[i].AgedCnt = DtcExtend_u64a8_Par[i].AgedCnt + 1;/*�ϻ������1*/
          if(DtcExtend_u64a8_Par[i].AgedCnt==256)/*�ϻ������Ƿ�Ϊ256*/
          {
          	 DtcExtend_u64a8_Par[i].AgedCnt=0;/*�ϻ�������0*/
          }
          /*--- ��Aged Counter��Ϊ0ʱ���DTC��Ϣ --- */
          ClearSignelDtc_v_g(i);
          DtcExtend_u64a8_Par[i].AgingCnt = 0;   
        } 
        if(LastDtcStatus_u16a8_Par[i].Status.Bits.pendingDTC==1)/*�ж�δȷ��״̬�Ƿ�Ϊ1*/
        {
         
          if(DtcExtend_u64a8_Par[i].PendCnt<255)/*�жϼ����Ƿ�С��255*/
          {
          	  DtcExtend_u64a8_Par[i].PendCnt++; /*������1*/
          }
        }
        else
        {
          DtcStatus_u16a8_Par[i].Status.Bits.pendingDTC=0; /*������0*/
        }
        
    }   
    else
    {
         DtcExtend_u64a8_Par[i].AgingCnt=0;/*���������0*/
         if(DtcExtend_u64a8_Par[i].PendCnt<255)/*�жϼ����Ƿ�С��255*/
          {
                   	  DtcExtend_u64a8_Par[i].PendCnt++; /*������1*/
         }
         
         if(DtcExtend_u64a8_Par[i].FualtCnt<255)/*�жϼ����Ƿ�С��255*/
         {
          DtcExtend_u64a8_Par[i].FualtCnt++;/*������1*/
         }
    }
    /* --- ��������bit��дEEPROM�����Ը�Ϊ0 --- */
    DtcStatus_u16a8_Par[i].Status.Bits.testFailedThisOperationCycle = 0;
    DtcStatus_u16a8_Par[i].Status.Bits.testNotCompletedThisOperationCycle = 0;
  }
    
}

/*!******************************************************************************************************
 *	@fn	void ClearDtc_v_g(void)
 *	@brief ������й����뺯��
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void ClearDtc_v_g(void)
{
/*--------------������й�����-----------*/
ClearSignelDtc_v_g(U000187);
ClearSignelDtc_v_g(U000387);
ClearSignelDtc_v_g(U000288);
ClearSignelDtc_v_g(P000112);
ClearSignelDtc_v_g(P000209);
ClearSignelDtc_v_g(P000396);
ClearSignelDtc_v_g(U000487);
ClearSignelDtc_v_g(P000429);
}
#endif
#endif
/*!******************************************************************************************************
 *	@fn	void ReadData_v_g(void)
 *	@brief ��ȡEEPROM����
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
// void ReadData_v_g(void)
// {
//     EEPROM_Read((uint16_T*)&BootEepFlag_u16_Par,(uint16_T*)(ERASE_BASE+408),1);
// 	EEPROM_Read((uint16_T*)&AppEepFlag_u16_Par,(uint16_T*)(ERASE_BASE+409),1);
//     if(BootEepFlag_u16_Par==1 || AppEepFlag_u16_Par==1)
//     {
// 	EEPROM_Read((uint16_T*)BootSwRefNumb_u16a10_Par,(uint16_T*)(ERASE_BASE),10);
// 	EEPROM_Read((uint16_T*)PifPtcb_u16a16a16_Par,(uint16_T*)(ERASE_BASE+10),256);
// 	EEPROM_Read((uint16_T*)ECUPartNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+266),6);
// 	EEPROM_Read((uint16_T*)SysSupplierId_u16a6_Par,(uint16_T*)(ERASE_BASE+272),6);
// 	EEPROM_Read((uint16_T*)EcuHwNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+278),6);
// 	EEPROM_Read((uint16_T*)EcuHwRefNumb_u16a10_Par,(uint16_T*)(ERASE_BASE+284),10);
// 	EEPROM_Read((uint16_T*)EcuSwRefNumb_u16a10_Par,(uint16_T*)(ERASE_BASE+294),10);
// #if APP_CODE==0
// 	EEPROM_Read((uint16_T*)EcuAppSwNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+304),6);
// 	EEPROM_Read((uint16_T*)EcuCalSwNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+310),6);
// 	EEPROM_Read((uint16_T*)EcuNetRefNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+316),6);
// #endif
// 	EEPROM_Read((uint16_T*)VehFeature_u16a20_Par,(uint16_T*)(ERASE_BASE+322),20);
// 	EEPROM_Read((uint16_T*)EcuSupplierSN_u16a10_Par,(uint16_T*)(ERASE_BASE+342),10);
// 	EEPROM_Read((uint16_T*)EcuMData_u16a3_Par,(uint16_T*)(ERASE_BASE+352),3);
// 	EEPROM_Read((uint16_T*)Vin_u16a17_Par,(uint16_T*)(ERASE_BASE+355),17);
// 	EEPROM_Read((uint16_T*)&PifBlockNumb_u16_Sig,(uint16_T*)(ERASE_BASE+372),1);
//     }
//    if(BootEepFlag_u16_Par==1)
//    {
// 	EEPROM_Read((uint16_T*)&SVF_u16_Par,(uint16_T*)(ERASE_BASE+373),1);
// 	EEPROM_Read((uint16_T*)&BootTimes_u16_Par,(uint16_T*)(ERASE_BASE+374),1);
// 	EEPROM_Read((uint16_T*)&SIS_u16_Sig,(uint16_T*)(ERASE_BASE+375),1);
// 	EEPROM_Read((uint16_T*)&SCS_u16_Sig,(uint16_T*)(ERASE_BASE+376),1);
// 	EEPROM_Read((uint16_T*)&WrCheckSum_u16_Sig,(uint16_T*)(ERASE_BASE+410),1);

//    }

// 	if(AppEepFlag_u16_Par==1)
// 	{
//     EEPROM_Read((uint16_T*)&PEF_u16_Par,(uint16_T*)(ERASE_BASE+412),1);
//     /*����DTC���������Զ���Ŀ����Լ����������дEEPROM��ַ��ȷ�����������ַ��Flash��ַ��ͻ�Ϳ���*/
// #if UDS_DTC_OPEN==1
// 	EEPROM_Read((uint16_T*)DtcStatus_u16a8_Par,(uint16_T*)(ERASE_BASE+378),8);
// 	EEPROM_Read((uint16_T*)DtcExtend_u64a8_Par,(uint16_T*)(ERASE_BASE+380),32);
// 	EEPROM_Read((uint16_T*)DtcSnapShot_u80a8_Par,(uint16_T*)(ERASE_BASE+413),40);
// #endif
// 	}
	
		
// }
/*!******************************************************************************************************
 *	@fn	void ReadData_v_g(void)
 *	@brief дEEPROM����
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
// void SaveData_v_g(void)
// {
// /*-------------------dtc Eep--------------------------*/
// uint16_T Status;
// static uint8_T cnt=0;
// static uint8_T cnteep=0;
// #if APP_CODE==0
// if(SvfEep_u8_Sig==1|| DidEep_u8_Sig==1 || (PefEep_u8_Sig==1 && SessionMode_u8_Sig==DEFAULT_SESSION))
// {
// cnt++;	
// }
// #endif
// #if APP_CODE==0
// if((SvfEep_u8_Sig==1 || DidEep_u8_Sig==1 || PefEep_u8_Sig==1) && cnt==4)
// {
// BootEepFlag_u16_Par=1;
// if(SvfEep_u8_Sig==1 && SVF_u16_Par==1)/*�ж�дFlash�Ƿ�ɹ��������Ա�־��λ*/
// {
// 	SIS_u16_Sig=SIS_u16_Sig&0xFE;/*��������λ*/
//     SCS_u16_Sig=SIS_u16_Sig&0xFE;/*��������λ*/
// 	SVF_u16_Par=1;
//     if(BootTimes_u16_Par <65535)
// 	{
//     	 BootTimes_u16_Par++;/*ˢд������1*/
// 	}
// }

// #else
// //if(g_CANDataVar.nParkLock_St_dCAN==1)
// //{
// //EepRomTimes_u8_Sig=0;
// //}
// if(PEF_u16_Par==1)
// {
// 	cnt++;
// }
// //ljh 20160225
// if(EepRomTimes_u8_Sig==0 && g_AdcCalVar.nV_Ign_ConF <= 55)
// {
// 	cnteep++;
// }
// if(g_AdcCalVar.nV_Ign_ConF > 55)	cnteep=0;
// /*if((g_CANDataVar.nEngine_RMP_dCAN<200 && EepRomTimes_u8_Sig==0\
// 		&& g_CANDataVar.nParkLock_St_dCAN==2 && cnteep==200 ) || (g_CANDataVar.nEngine_RMP_dCAN<200&&PEF_u16_Par==1 && cnt==2))*/		//ljh 20160225
// if((g_AdcCalVar.nV_Ign_ConF <= 55 && cnteep==20 && EepRomTimes_u8_Sig==0 )||(PEF_u16_Par==1 && cnt==2))
// {
// cnteep=0;
// AppEepFlag_u16_Par=1;/*App дEEPROM��־λ��ֵ*/
// if(DtcOnOff_u8_Sig==DTCSETTING_ON)
// {
// DTCExtendDual_v_g();/*extend ���ݴ���*/
// }
// #endif
// cnt=0;
// DINT;
// Status=EEPROM_Erase(SECTORC);/*����EEPROM*/
// EEPROM_Write((uint16_T*)&BootEepFlag_u16_Par,(uint16_T*)(ERASE_BASE+408),1);
// EEPROM_Write((uint16_T*)&AppEepFlag_u16_Par,(uint16_T*)(ERASE_BASE+409),1);
// EEPROM_Write((uint16_T*)&WrCheckSum_u16_Sig,(uint16_T*)(ERASE_BASE+410),1);
// EEPROM_Write((uint16_T*)BootSwRefNumb_u16a10_Par,(uint16_T*)(ERASE_BASE),10);
// EEPROM_Write((uint16_T*)PifPtcb_u16a16a16_Par,(uint16_T*)(ERASE_BASE+10),256);
// EEPROM_Write((uint16_T*)ECUPartNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+266),6);
// EEPROM_Write((uint16_T*)SysSupplierId_u16a6_Par,(uint16_T*)(ERASE_BASE+272),6);
// EEPROM_Write((uint16_T*)EcuHwNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+278),6);
// EEPROM_Write((uint16_T*)EcuHwRefNumb_u16a10_Par,(uint16_T*)(ERASE_BASE+284),10);
// EEPROM_Write((uint16_T*)EcuSwRefNumb_u16a10_Par,(uint16_T*)(ERASE_BASE+294),10);
// EEPROM_Write((uint16_T*)EcuAppSwNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+304),6);
// EEPROM_Write((uint16_T*)EcuCalSwNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+310),6);
// EEPROM_Write((uint16_T*)EcuNetRefNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+316),6);
// EEPROM_Write((uint16_T*)VehFeature_u16a20_Par,(uint16_T*)(ERASE_BASE+322),20);
// EEPROM_Write((uint16_T*)EcuSupplierSN_u16a10_Par,(uint16_T*)(ERASE_BASE+342),10);
// EEPROM_Write((uint16_T*)EcuMData_u16a3_Par,(uint16_T*)(ERASE_BASE+352),3);
// EEPROM_Write((uint16_T*)Vin_u16a17_Par,(uint16_T*)(ERASE_BASE+355),17);
// EEPROM_Write((uint16_T*)&PifBlockNumb_u16_Sig,(uint16_T*)(ERASE_BASE+372),1);
// EEPROM_Write((uint16_T*)&SVF_u16_Par,(uint16_T*)(ERASE_BASE+373),1);
// EEPROM_Write((uint16_T*)&BootTimes_u16_Par,(uint16_T*)(ERASE_BASE+374),1);
// EEPROM_Write((uint16_T*)&SIS_u16_Sig,(uint16_T*)(ERASE_BASE+375),1);
// EEPROM_Write((uint16_T*)&SCS_u16_Sig,(uint16_T*)(ERASE_BASE+376),1);
// EEPROM_Write((uint16_T*)&PEF_u16_Par,(uint16_T*)(ERASE_BASE+412),1);
// /*����DTC���������Զ���Ŀ����Լ����������дEEPROM��ַ��ȷ�����������ַ��Flash��ַ��ͻ�������*/
// #if UDS_DTC_OPEN==1
// EEPROM_Write((uint16_T*)DtcStatus_u16a8_Par,(uint16_T*)(ERASE_BASE+378),8);
// EEPROM_Write((uint16_T*)DtcExtend_u64a8_Par,(uint16_T*)(ERASE_BASE+380),32);
// EEPROM_Write((uint16_T*)DtcSnapShot_u80a8_Par,(uint16_T*)(ERASE_BASE+413),40);
// #endif
// #if APP_CODE==1
// Progam_v_s();/*reset*/
// #endif
// if(SvfEep_u8_Sig==1 && SVF_u16_Par==1)/*�жϳ�����������дEEPROM��־λ�Ƿ�Ϊ1*/
// {
// 	RspFmt_u8_Sig =POS_RSP;/*��Ӧ���͸�ֵ*/
// 	if(BackUpExit_u8_Sig==1)
// 	{

// 		/*--------------------------��Ӧ���ݸ�ֵ----------------------*/
// 	  Rsp_Msg.ReqSendMsg_u8_Tmp [1]=BackUpExit_u8_Sig;
// 	  Rsp_Msg.ReqSendMsg_u8_Tmp [2]=(uint8_T)(crcData_u32_Sig>>24);
// 	  Rsp_Msg.ReqSendMsg_u8_Tmp [3]=(uint8_T)(crcData_u32_Sig>>16);
// 	  Rsp_Msg.ReqSendMsg_u8_Tmp [4]=(uint8_T)(crcData_u32_Sig>>8);
// 	  Rsp_Msg.ReqSendMsg_u8_Tmp [5]=(uint8_T)(crcData_u32_Sig);
// 	  RspMsgLen_u16_Sig = 5;/*���ȸ�ֵ*/
// 	}
// 	else
// 	{

// 	/*--------------------------��Ӧ���ݸ�ֵ----------------------*/
// 		Rsp_Msg.ReqSendMsg_u8_Tmp [1]=BackUpExit_u8_Sig;
// 		RspMsgLen_u16_Sig = 1;
// 	}
// 	if(!ResponseMechanism_v_s())
// 	{
// 		  AppSendRspMsg();/*��������㷢������*/
// 	}

// }
// if(DidEep_u8_Sig==1)/*�ж�DIDдEEPROM��־λ*/
// {
// /*--------------------------��Ӧ���ݸ�ֵ----------------------*/
// Rsp_Msg.ReqSendMsg_u8_Tmp [1]=WrDidBackUp_Sig[0];
// Rsp_Msg.ReqSendMsg_u8_Tmp [2]=WrDidBackUp_Sig[1];	
// RspFmt_u8_Sig =POS_RSP;/*��Ӧ���͸�ֵ*/
// RspMsgLen_u16_Sig = 2;/*���ȸ�ֵ*/
// if(!ResponseMechanism_v_s())
// {
// 	  AppSendRspMsg();/*��������㷢������*/
// }
// }
// SvfEep_u8_Sig=0;
// DidEep_u8_Sig=0;
// PefEep_u8_Sig=0;

// if(g_AdcCalVar.nV_Ign_ConF <= 55){
// 	EepRomTimes_u8_Sig=1;
// 	}
// delay_ms(9.0L);			//20160310  ljh
// EINT;
// }
// }
#if APP_CODE==0

/*!******************************************************************************************************
 *	@fn	uint16_T PFlash_Check(uint32_T StartAddr, uint16_T Len, uint16_T LastValue)
 *	@brief дEEPROM����
 *	@author Matt Zhang
 *	@param[in]	StartAddr��ʼ��ַ��Len��ҪУ��ĳ��ȣ�LastValueУ��ͱ���
 *	@return	uint16_TУ���
 *	@note
 -
 *********************************************************************************************************
 */

uint16_T PFlash_Check(uint32_T StartAddr, uint16_T Len, uint16_T LastValue)
{
	 uint32_T start = StartAddr;
	 uint32_T len   = Len;
	 uint16_T checksum = LastValue;
	 uint16_T cnt;

	 for( cnt=0;cnt<len;cnt++)
	 {
	 checksum += *((uint16_T far*)(start+cnt));/*����ʼ��ַȡ�趨���ȵ������ۼ�*/
	 }

	 return checksum;/*����У���*/

}


/*!******************************************************************************************************
*	@fn void CommunicationControl_v_g(UDSBYTEPTR SubFun)
*	@brief ���Ʒ��ͺͽ���ͨ��(�����ͨ��)
*	@param[in]	SubFun
*	@return	void
*	@note
*		-
*********************************************************************************************************
*/
uint16_T CheckAppCode_v_g(void)
{

	  uint16_T checksum = 0;
	  DINT;
	  checksum = PFlash_Check(0x3EC000, 0x6000, checksum);/*�趨����ȡF����У���*/

	  checksum = PFlash_Check(0x3F4000, 0x2000, checksum);/*F����B���ۼ�У���*/

      EINT;
	  return checksum;/*����У��ֵ*/
}

/*!******************************************************************************************************
 *	@fn	void WriteFlashDual(void)
 *	@brief дFlash������
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void WriteFlashDual(void)
{
    uint16_T Status;
    static uint8_T cnt=0;
    if(WFlashFlag_u8_Sig==1)/*�ж�дFlash��־λ�Ƿ�Ϊ1*/
    {
	cnt++;/*��������1*/
    }
	if(WFlashFlag_u8_Sig==1 && cnt==4)/*�ж�Flash�ͼ���ֵ�Ƿ�ﵽ�趨ֵ*/
	{
		cnt=0;
		DINT;/*���ж�*/
		Status =Boot(WFlashAdr_u32_Sig, FlashWBuffer_u16_Sig, BootWFalshLen_u16_Sig);/*дFlash*/
		if(EndHex_u8_Sig==1)/*�ж��Ƿ����һ������*/
		{
		WrCheckSum_u16_Sig = CheckAppCode_v_g();/*����У���*/
		}
		EINT;
        WFlashAdr_u32_Sig= WFlashAdr_u32_Sig+BootWFalshLen_u16_Sig;/*дFlash�����ۼ�*/
        if(Status!=noErr)/*�ж�дFlash״̬�Ƿ���ȷ*/
        {
          RspFmt_u8_Sig=NEG_RSP;
          NegRsp_u8_Sig=ERWRMEN_ERR;  /*дFlash����*/
        }
        else
        {
          RspFmt_u8_Sig =POS_RSP;/*��Ӧ���͸�ֵ*/
          Rsp_Msg.ReqSendMsg_u8_Tmp [1] =TranBlock_u8_Sig;	
        }
		WFlashFlag_u8_Sig = 0;/*дFlash��־λ��0*/
		 
	    if(RspFmt_u8_Sig==NEG_RSP)
        {
 	     RspMsgLen_u16_Sig = 2;
        }	
        else
        {
  	     RspMsgLen_u16_Sig = 1;
        }
        if(!ResponseMechanism_v_s())
	    {
	     AppSendRspMsg();
	    }
  
	}

}
/*!******************************************************************************************************
 *	@fn	void EraseFlashDual(void)
 *	@brief ����Flash������
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void EraseFlashDual(void)
{
    uint16_T Status;
    static uint8_T cnt=0;
    if(EFlashFlag_u8_Sig==1)/*�жϲ�Flash��־λ�Ƿ�Ϊ1*/
    {
    	cnt++;
    }
    
	if(EFlashFlag_u8_Sig==1 && cnt==4)/*�жϲ�Flash��־λ������ֵ*/
	{
		
		cnt=0;
		DINT;
		Status = EraseSector_v_s(EraseSector_u8_Sig);/*����flash*/
		EINT;
        if(Status!=noErr)/*�жϲ�Flash״̬�Ƿ���ȷ*/
        {
          RspFmt_u8_Sig=NEG_RSP;
          NegRsp_u8_Sig=ERWRMEN_ERR;  /*��flash����*/
        }
        else
        {
       /*----------------�����Ӧ��ֵ---------------*/
        Rsp_Msg.ReqSendMsg_u8_Tmp [1]=BackSub_u8_Sig;
        Rsp_Msg.ReqSendMsg_u8_Tmp [2]=EraseDid_u8_Sig[0];
   		Rsp_Msg.ReqSendMsg_u8_Tmp [3]=EraseDid_u8_Sig[1];	
   		RspFmt_u8_Sig =POS_RSP;
   		RspMsgLen_u16_Sig = 3;
        }
		EFlashFlag_u8_Sig = 0;/*�����Flash��־λ*/
		
	    if(RspFmt_u8_Sig==NEG_RSP)
        {
 	     RspMsgLen_u16_Sig = 2;
        }
        
        if(!ResponseMechanism_v_s())
	    {
	     AppSendRspMsg();
	    }
	}

}
/*!******************************************************************************************************
 *	@fn	uint16_T EraseSector_v_s(uint16_T sector)
 *	@brief ����Flash����
 *	@author Matt Zhang
 *	@param[in]	sector����������
 *	@return	uint16_T����״ֵ̬
 *	@note
 -
 *********************************************************************************************************
 */
uint16_T EraseSector_v_s(uint16_T sector)
{
	uint16_T Status;
	switch(sector)
	{
		case A_Sector:
		//Status=AppFlash_Erase(SECTORA); /*����A��*/
		break;
		case B_Sector:
		//Status=AppFlash_Erase(SECTORB);/*����B��*/
		break;
		case AB_Sector:
		//Status=AppFlash_Erase(SECTORB);/*����B��*/
		break;
		case F_Sector:
		//Status=AppFlash_Erase(SECTORF)|AppFlash_Erase(SECTORE)|AppFlash_Erase(SECTORD)|AppFlash_Erase(SECTORB);/*����F��E��D��B��*/
		break;
	}
	
	return Status;
}

#endif
/*!******************************************************************************************************
 *	@fn	void ReadMemDual(void)
 *	@brief ��ȡ�ڴ��ַ���ݴ�����
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void ReadMemDual(void)
{
uint16_T Index=0;
static uint8_T cnt=0;
if( RMemDataFLag_u8_Sig ==1)/*�жϵ�ַ�����ݱ�־λ�Ƿ�Ϊ1*/
{
	cnt++;
}
	if( RMemDataFLag_u8_Sig ==1 && cnt==4)/*�жϵ�ַ�����ݱ�־λ�Ƿ�Ϊ1�Ҽ���ֵ�ﵽ*/
	{
		cnt=0;
		DINT;
		/*---------------------��ȡ����-----------------------*/
        //EEPROM_Read((uint16_T*)MemData_u16_Sig,(uint16_T*)MemAdr_u32_Sig,MemDataLen_u16_Sig);
        EINT;
      
        RspFmt_u8_Sig =POS_RSP;
        /*---------------------��ȡ�����ݸ�ֵ����Ӧ����-----------------------*/
        for(Index=0;Index<MemDataLen_u16_Sig;Index++)
        {
          	//Rsp_Msg.ReqSendMsg_u8_Tmp [1+(Index<<1)] =(uint8_T)(MemData_u16_Sig[Index]>>8);
          	//Rsp_Msg.ReqSendMsg_u8_Tmp [2+(Index<<1)] =(uint8_T)(MemData_u16_Sig[Index]&0xFF);

			//Set_Byte();
        }
		RMemDataFLag_u8_Sig = 0;
	    if(RspFmt_u8_Sig==NEG_RSP)
        {
 	     RspMsgLen_u16_Sig = 2;
        }	
        else
        {
  	     RspMsgLen_u16_Sig = MemDataLen_u16_Sig<<1;
        }
        if(!ResponseMechanism_v_s())
	    {
	     AppSendRspMsg();
	    }
  
	}

}
/*!******************************************************************************************************
 *	@fn	void WriteMemDual(void)
 *	@brief д�ڴ��ַ���ݴ�����
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void WriteMemDual(void)
{

uint16_T Status;
uint16_T Index=0;
static uint8_T cnt=0;
if( WMemDataFLag_u8_Sig ==1)/*�жϵ�ַд���ݱ�־λ�Ƿ�Ϊ1*/
{
	cnt++;
}
	if( WMemDataFLag_u8_Sig ==1 && cnt==4)/*�жϵ�ַд���ݱ�־λ�Ƿ�Ϊ1�Ҽ���ֵ�ﵽ*/
	{
		cnt=0;
		DINT;
        //Status=EEPROM_Erase(SECTORC);/*����EEPROm*/
       
        if(Status!=noErr)/*�жϲ���EEPROm�Ƿ���ȷ*/
        {
          RspFmt_u8_Sig=NEG_RSP;
          NegRsp_u8_Sig=ERWRMEN_ERR;
        }
        else
        {

        /*--------------------ͨ����ַдEEPROM---------------------*/
          //Status=EEPROM_Write((uint16_T*)MemData_u16_Sig,(uint16_T*)MemAdr_u32_Sig,MemDataLen_u16_Sig);
        }
        EINT;
        if(Status!=noErr)/*�ж�дEEPROm�Ƿ���ȷ*/
        {
          RspFmt_u8_Sig=NEG_RSP;
          NegRsp_u8_Sig=ERWRMEN_ERR;  /*���Ȳ��Դ�����0x13*/  
        }
        else
        {
          RspFmt_u8_Sig =POS_RSP;
          //Rsp_Msg.ReqSendMsg_u8_Tmp [1] =adrLenFmtId_u8_Sig;
		  Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, adrLenFmtId_u8_Sig);
          //for(Index=1;Index<BackUpPosLen_u16_Sig;Index++)
          //{
          //	Rsp_Msg.ReqSendMsg_u8_Tmp [1+Index] =BackUpMemInfor_u8_Sig[Index-1];
          //}
		  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], &BackUpMemInfor_u8_Sig, LSB, LSB, (BackUpPosLen_u16_Sig -1));
        }
		WMemDataFLag_u8_Sig = 0;
	    if(RspFmt_u8_Sig==NEG_RSP)
        {
 	     RspMsgLen_u16_Sig = 2;
        }	
        else
        {
  	     RspMsgLen_u16_Sig = BackUpPosLen_u16_Sig;
        }
        if(!ResponseMechanism_v_s())
	    {
	     AppSendRspMsg();
	    }
  
	}

}
/*!******************************************************************************************************
 *	@fn	void SwReset_v_g(void)
 *	@brief SwREset������
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void SwReset_v_g(void)
{
	static uint8_T cnt =0;
	if(ResetMode_u8_Sig==SW_RESET ||  ResetMode_u8_Sig == HARD_RESET)/*�ж�Reset�����Ƿ�ΪSw��Hw*/
	{
		 cnt++;
	}
	/*�ж�Reset�����Ƿ�ΪSw��Hw�Ҽ���ֵ�ж�*/
    if(ResetMode_u8_Sig == HARD_RESET && cnt ==4)
	{
		cnt=0;
	    DINT;
		IER = 0x0000;
		IFR = 0x0000;
		while(1)
		{};
	}
	else if(ResetMode_u8_Sig == SW_RESET && cnt ==4)
	{   
		cnt=0;
	    DINT;
		IER = 0x0000;
		IFR = 0x0000;
		while(1)
		{};
	}
}

#if APP_CODE==1
/*!******************************************************************************************************
 *	@fn	void SwReset_v_g(void)
 *	@brief Boot_SwREset������
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void Progam_v_s(void)
{

    if(PEF_u16_Par==1 )/*�ж�APPtoBoot��־λ�Ƿ�Ϊ1*/
	{
		DINT;
		IER = 0x0000;
		IFR = 0x0000;
		(*ECU_SWRESET)();// Reset

	}
}
#endif
