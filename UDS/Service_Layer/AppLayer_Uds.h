/*!******************************************************************************************************
*	@file 	appuds.h
*	@brief 	appuds.cͷ�ļ�
*	@author Matt Zhang
*	@version 0.1
*	@date  2012-2-15
*	@warning
*                (c) Copyright 2010, Vast Automotive Technology(Shanghai) Co., Ltd.
*                                       All Rights Reserved
*
**********************************************************************************************************/
#ifndef APPLAYER_UDS_H
#define APPLAYER_UDS_H

#ifdef   APPLAYER_GLOBALS
	#define  APPLAYER_EXT
#else
	#define  APPLAYER_EXT  extern
#endif
#include "NetworkLayerServices_GF.h"
#include "NetworkLayerServices_GF_private.h"

/*--------------------------------���������Զ��� BEGIN--------------------------------*/
typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;
typedef signed   char  INT8S;
typedef unsigned int   INT16U;
typedef signed   int   INT16S;
typedef unsigned long  INT32U;
typedef signed   long  INT32S;
typedef float          FP32;
typedef double         FP64;
#define BYTEPTR        unsigned char*
/*--------------------------------���������Զ���END--------------------------------*/
/*
*********************************************************************************************************
*                                                MACROS
*********************************************************************************************************
*/
/*--------------------------------Boot��AppCode����BEGIN--------------------------------*/
#define APP_CODE    1//Boot��������Ϊ0��������������Ϊ1
#define UDS_DTC_OPEN 1//1����ʹ��UDS�����DTC������0����ʹ���Զ���
/*--------------------------------Boot��AppCode����END----------------------------------*/

/*--------------------------------ECU RESET ��ַ BEGIN----------------------------------*/
#define ECU_SWRESET   (void (*)(void))  0x3F7FF6//flash F�׵�ַ
/*--------------------------------ECU RESET ��ַ END----------------------------------*/

/*--------------------------------��Sub_Function���ܷ���Ŷ��� BEGIN----------------------------------*/
#define DIAGNOSTIC_SESSION_CONTROL 0x10 /*�Ựģʽ*/
#define ECU_RESET 0x11/*ECU RESET*/
#define SECURITY_ACCESS 0x27/*����*/
#define COMMUNICATION_CONTROL 0x28/*ͨ��*/
#define TESTER_PRESENT 0x3E/*����*/
#define CONTROL_DTC_SETTING 0x85/*DTC����*/
#define RESPONSE_ON_EVENT 0x86/*Ԥ��*/
#define LINK_CONTROL 0x87 /*Ԥ��*/
#define DYNAMICALLY_DEFINE_DATA_IDENTIFIER 0x2C/*Ԥ��*/
#define READ_DTC_INFORMATION 0x19/*��ȡ������*/
#define ROUTINE_CONTROL 0x31/*������*/
/*--------------------------------��Sub_Function���ܷ���Ŷ��� END-------------------------------------*/

/*--------------------------------����Sub_Function���ܷ���Ŷ��� BEGIN----------------------------------*/
#define SECURED_DATA_TRANSMISSTION 0x84/*Ԥ��*/
#define READ_DATA_BY_IDENTIFIER 0x22/*DID��ȡ����*/
#define READ_MEMORY_BY_ADDRESS 0x23/*��ַ��ȡ����*/
#define READ_SCALING_DATA_BY_IDENTIFIER 0x24/*Ԥ��*/
#define READ_DATA_BY_PERIODIC_IDENTIFIER 0x2A/*Ԥ��*/
#define WRITE_DATA_BY_IDENTIFIER 0x2E/*DIDд����*/
#define WRITE_MEMORY_BY_ADDRESS 0x3D/*��ַд����*/
#define CLEAR_DIAGNOSTIC_INFORMATION 0x14/*���������д����*/
#define INPUT_OUTPUT_CONTROL_BY_IDENTIFIER 0x2F/*�����������*/
#define REQUEST_DOWNLOAD 0x34/*��������*/
#define REQUEST_UPLOAD 0x35/*Ԥ��*/
#define TRANSFER_DATA 0x36/*��������*/
#define REQUEST_TRANSFER_EXIT 0x37/*�������˳�*/
/*--------------------------------����Sub_Function���ܷ���Ŷ��� END-------------------------------------*/


#if APP_CODE==0
#define CODECEF                             4 /*������1ms�ı���*/
#define CODE_CYCLE                          1 /*��������*/
#else
#define CODE_CYCLE                          5 /*��������*/
#endif
#define NR_SI                               0x7F/*����ӦNSID*/
#define DEFAULT_SESSION                     0x01/*Ĭ�ϻỰģʽ*/
#define PROGRANMMING_SESSION                0x02/*��̻Ựģʽ*/
#define EXTEND_SESSION                      0x03/*��չ�Ựģʽ*/
#define SAFETY_SESSION                      0x04/*Ԥ��*/

#define HARD_RESET                          0x01/*Ӳ����*/
#define KEYOFFON_RESET                      0x02/*Ԥ��*/
#define SW_RESET                            0x03/*Ԥ��*/
#define RAPIDSHUTDOWN_ENABLE                0x04/*Ԥ��*/
#define RAPIDSHUTDOWN_DISABLE               0x05/*Ԥ��*/

#define APPTONET_SENDOK                     0x01/*Ӧ�ò���������㴦�����ݱ�־ֵ*/

#define POS_RSP                             0x00/*��������־*/
#define NEG_RSP                             0x01/*��������־*/

#define SEED_KEY_TIMES                      0x02/*���ܳ���ֵ*/


#define DTCSETTING_ON                       0x01/*����DTC״̬*/
#define DTCSETTING_OFF                      0x02/*������DTC״̬*/


#define DTCGROUP                            0x00000000 /*��������ֵ*/
#define ALLDTCGROUP                         0x00FFFFFF /*��������ֵ*/
#define DTCFMT115031                        0x00 /*���������յĸ�ʽ*/
#define DTCFMT14229                         0x01 /*���������յĸ�ʽ*/
#define DTCNUM                              8    /*���������*/
#define MASKSTATUS                          0x7F /*��֧�ֵ�����*/


#if APP_CODE==1
/*-----------------------------APPCODEʱ�������ֵBEGIN------------------------------*/
#define  AS_TIME                            (110/CODE_CYCLE)
#define  BS_TIME                            (75/CODE_CYCLE)
#define  CR_TIME                            (150/CODE_CYCLE)

#define  P2_CANSERVER                       (50/CODE_CYCLE)   /*�ظ���ֵʱ��*/
#define  P2_FLEXCANSERVER                   (5000/CODE_CYCLE) /*��ǿ����ʱʱ��*/
#define  S3SERVER                           (5000/CODE_CYCLE) /*��Ĭ�ϻỰģʽ��ֵʱ��*/
#define  SECUR_LIMIT_TIME                   (10000/CODE_CYCLE)/*������ֵʱ��*/
/*-----------------------------APPCODEʱ�������ֵEND------------------------------*/
#else
/*-----------------------------BOOTCODEʱ�������ֵBEGIN------------------------------*/
#define  AS_TIME                            (110*CODECEF/CODE_CYCLE)
#define  BS_TIME                            (75*CODECEF/CODE_CYCLE)
#define  CR_TIME                            (150*CODECEF/CODE_CYCLE)

#define  P2_CANSERVER                       (50*CODECEF/CODE_CYCLE)
#define  P2_FLEXCANSERVER                   ((INT32U)5000*CODECEF/CODE_CYCLE)
#define  S3SERVER                           ((INT32U)5000*CODECEF/CODE_CYCLE)
#define  SECUR_LIMIT_TIME                   ((INT32U)10000*CODECEF/CODE_CYCLE)
/*-----------------------------BOOTCODEʱ�������ֵEND------------------------------*/
#endif
/*-----------------------------BootˢдAppCode�ĵ�ַ��ΧBEGIN-----------------------------*/
#define  ERASE_FLASH_SECTORB_ADR            0x3F4000
#define  ERASE_FLASH_SECTORB_LENGTH         0x001FFE

#define  ERASE_FLASH_SECTORF_ADR            0x3EC000
#define  ERASE_FLASH_SECTORF_LENGTH         0x006000

#define  ERASE_FLASH_SECTORD_ADR            0x3F5FFE
#define  ERASE_FLASH_SECTORD_LENGTH         0x000002

#define  ERASE_FLASH_ADRBYTES               4  /*��ַ֧�ֵ�Byte��*/
#define  ERASE_FLASH_DATALENBYTES           4  /*����֧�ֵ�Byte��*/

#define  WRITE_FLASH_ADRBYTES               4 
#define  WRITE_FLASH_DATALENBYTES           4

#define  MAX_NUM_BLOCK                      216 /*һ��Block����������*/
#define  LEN_MFT                            0x20

/*-----------------------------BootˢдAppCode�ĵ�ַ��ΧBEGIN-----------------------------*/

/*-----------------------------EEPROM��ַ��ΧBEGIN--------------------------------------*/
#define  ERASE_FLASH_SECTORC_ADR            0x3F2000
#define  ERASE_FLASH_SECTORC_LENGTH         0x002000
#define  ERASE_BASE                         0x3F2000
#define  ECU_SUPPROT_ADDRESSLEN             0x04
#define  MAX_DATANUMBYTE                    0x02
#define  RWDATA_MINADR                      0x3F2000
#define  RWDATA_MAXADR                      0x3F3FFF
#define  MAX_MEMWRITENUM                    100
/*-----------------------------EEPROM��ַ��ΧEND---------------------------------------*/

/*-----------------------------��������붨��BEGIN---------------------------------------*/
#define  SEVICE_NOTSUPPORT_ERR           0x11
#define  SUBFUNCTION_NOTSUPPORT_ERR      0x12
#define  CMD_LENGTH_ERR                  0x13
#define  CONDITION_NOTSURRORT_ERR        0x22
#define  ORDER_ERR                       0x24
#define  OVERRANGE_ERR                   0x31
#define  NOTGETAUTHORITY_ERR             0x33
#define  KEY_ERR                         0x35
#define  UNLOCKOVERTIME_ERR              0x36
#define  UNLOCKDELAY_ERR                 0x37
#define  SESSIONNOTSUPPROT_ERR           0x7F
#define  SESSION_SUB_NOTSUPPROT_ERR      0x7E
#define  FLEXRSPTIME_ERR                 0x78
#define  ERWRMEN_ERR                     0x72
#define  BLOCKSN_ERR                     0x73
#define  TRANDATA_STOP_ERR               0x71
/*-----------------------------��������붨��END---------------------------------------*/

/*-----------------------------��������Ŷ���BEGIN---------------------------------------*/
#define  U000187   0
#define  U000288   1
#define  U000387   2
#define  U000487   3
#define  P000112   4
#define  P000209   5
#define  P000396   6
#define  P000429   7
/*-----------------------------��������Ŷ���END----------------------------------------*/
/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/ 
/*-----------------------------DTC�ṹ��3��Byte����BEGIN----------------------------------------*/
typedef struct {
INT16U byte1;
INT16U byte2;
INT16U byte3;
}ST_DTC;
/*-----------------------------DTC�ṹ��3��Byte����END------------------------------------------*/

/*-----------------------------DTC Extend Data�ṹ��4��Byte����BEGIN----------------------------------------*/
typedef struct {
INT16U FualtCnt;
INT16U PendCnt;
INT16U AgedCnt;
INT16U AgingCnt;
}DTC_EXTENDDATA;
/*-----------------------------DTC Extend Data�ṹ��4��Byte����END----------------------------------------*/

/*-----------------------------DTC Snapshot Data�ṹ�嶨��BEGIN----------------------------------------*/
typedef struct {
INT16U SupBatt;
INT32U Odreading;
INT16U CoolTemp;
INT16U IgStatus;
}DTC_SNAPSHOT;
/*-----------------------------DTC Snapshot Data�ṹ�嶨��END----------------------------------------*/

/*-----------------------------DTC Status �ṹ�嶨��BEGIN--------------------------------------------*/
typedef struct {
       union {
      INT8U Byte;
      struct {
        INT8U testFailed    :1;                                       
        INT8U testFailedThisOperationCycle    :1;                                       
        INT8U pendingDTC    :1;                                       
        INT8U confirmedDTC    :1;                                       
        INT8U testNotCompletedSinceLastClear    :1;                                      
        INT8U testFailedSinceLastClear    :1;                                       
        INT8U testNotCompletedThisOperationCycle    :1;                                     
        INT8U warningIndicatorRequested    :1;                                       
      } Bits;
    } Status;
    //INT8U  Severity;
} ST_DTC_STATUS;
/*-----------------------------DTC Status �ṹ�嶨��END--------------------------------------------*/

/*-----------------------------Flash��д״̬ö�� �ṹ����BEGIN--------------------------------------------*/
typedef enum {
  noErr=0,
  WErr  
}WRFlash_Status;
/*-----------------------------Flash��д״̬ö�� �ṹ����END--------------------------------------------*/
typedef enum {
  TAtype_phiscal=1,
  TAtype_functional
}ETA_type;

typedef enum {
  Mtype_Diagnostics=1,
  Mtype_Rdiagnostics  
}EM_type;
/*-----------------------------����״̬ö�� �ṹ����BEGIN--------------------------------------------*/
typedef enum{
  Lock=0,
  UnLock_Level, 
  UnLock_Level2,
  UnLock_Level3
}SecurMode; 
/*-----------------------------����״̬ö�� �ṹ����END----------------------------------------------*/

/*-----------------------------Boot��������״̬ö�� �ṹ����BEGIN--------------------------------------------*/
typedef enum{
  Not_Req=0,
  Req_Sucess, 
  Tran_Sucess, 
  Exit_Sucess
}DownLoadr; 
/*-----------------------------Boot��������״̬ö�ٽṹ����END--------------------------------------------*/

/*-----------------------------FlashƬ��ö�� �ṹ����BEGIN--------------------------------------------*/
typedef enum{
  A_Sector=0,
  B_Sector, 
  AB_Sector, 
  F_Sector
}ERASE_SECTOR; 
/*-----------------------------FlashƬ��ö�� �ṹ����END--------------------------------------------*/

/*-----------------------------UdsӦ�ò�ԭ�� �ṹ����BEGIN--------------------------------------------*/
typedef struct {
INT8U A_SA;
INT8U A_TA;
ETA_type A_TA_type;
INT8U A_RA;
INT8U A_SI;
INT8U  *IndReceiveMsg_u8_Sig; 
INT16U A_PLength;
}REQ_A_PDU;/*����ԭ��ṹ��*/

typedef struct {
INT8U A_SA;
INT8U A_TA;
ETA_type A_TA_type;
INT8U A_RA;
INT8U A_NR_SI;
INT8U A_SI;
INT8U *ReqSendMsg_u8_Tmp;
INT16U A_PLength; 
}RSP_A_PDU,*LPRSP_APDU;/*��Ӧԭ��ṹ��*/
/*-----------------------------UdsӦ�ò�ԭ�� �ṹ����END--------------------------------------------*/
APPLAYER_EXT REQ_A_PDU Req_Msg;/*����ṹ���������*/
APPLAYER_EXT RSP_A_PDU Rsp_Msg;/*��Ӧ�ṹ���������*/

#if APP_CODE==0
APPLAYER_EXT INT8U     Jump_u8_Sig; /*Bootд������ɲ���ת��־λ*/
APPLAYER_EXT INT8U     BootApp_u8_Sig;/*20ms���״̬λ*/
APPLAYER_EXT INT8U     CANNumb_u8_Sig;/*CAN���ĵ�����*/
APPLAYER_EXT INT8U     CANIndex_u8_Sig;/*CAN���Ĵ�����������ֵ*/
APPLAYER_EXT INT8U     CANGetOut_u8_Sig;/*CAN���Ĵ�����������ֵ*/
APPLAYER_EXT INT8U     CANRevBuff_u8a160_Par[160];/*���CAN���ĵ�����*/
APPLAYER_EXT INT16U    CANFrameLen_u16a20_Par[20];/*CAN���ĵĳ��ȴ洢����*/
APPLAYER_EXT INT16U    CANId_u16a20_Par[20];/*CAN���ĵ�Id�洢����*/
APPLAYER_EXT INT8U     Jump_u8_Sig; /*Bootд������ɲ���ת��־λ*/
APPLAYER_EXT INT8U     BootApp_u8_Sig;/*20ms���״̬λ*/
#endif
APPLAYER_EXT INT8U     NormalComTx_u8_Sig;/*һ��Canͨ�ŷ��ͱ�־λ��ͨ���˱�־λ�ж��Ƿ�ر�Can�ķ��ͣ�Uds��can���ͳ���*/
APPLAYER_EXT INT8U     NormalComRx_u8_Sig;/*һ��Canͨ�ŷ��ͱ�־λ��ͨ���˱�־λ�ж��Ƿ�ر�Can�Ľ��գ�Uds��can���ճ���*/
APPLAYER_EXT INT8U     NetWorkComTx_u8_Sig;/*�������Canͨ�ŷ��ͱ�־λ*/
APPLAYER_EXT INT8U     NetWorkComRx_u8_Sig;/*�������Canͨ�Ž��ձ�־λ*/

APPLAYER_EXT INT8U   DtcOnOff_u8_Sig;/*DTC���±�־λ�����Dtc�رո��±�־λ��DTc��Ϣ���ڸ���*/
APPLAYER_EXT INT8U     UDS_Timeout_u8_Sig; /*��ʱ״̬����*/
APPLAYER_EXT INT8U     STmin_u8_Par; /*STʱ��*/
APPLAYER_EXT INT8U     CFCount_u8_Sig; /*CF�ļ�����*/
APPLAYER_EXT INT8U     SFLength_Ovrn_u8_Sig; /*SF�ĳ���״̬*/
APPLAYER_EXT INT8U     CANLength_u8_Sig; /*CAN���ĳ���*/
APPLAYER_EXT INT8U     FrameSequ_u8_Sig;
APPLAYER_EXT INT8U     FrameErr_u8_Sig;/*֡����״̬*/
APPLAYER_EXT INT8U     FC_RecStatus_u8_Sig;/*FC��״̬*/
APPLAYER_EXT INT8U     UDStick_u8_Par;/*��ʱ*/
APPLAYER_EXT INT8U     STminCoef_u8_Par;/*STʱ�����*/

APPLAYER_EXT INT16U    VehicleSpeed_u16_Sig;
APPLAYER_EXT INT16U    EngineSpeed_u16_Sig;

APPLAYER_EXT INT16U    WrCheckSum_u16_Sig;/*Bootˢд�����У���*/
APPLAYER_EXT INT8U     SessionMode_u8_Sig;/*�Ựģʽ����*/

APPLAYER_EXT INT16U    PEF_u16_Par;/*AppToBoot��־λλ*/
APPLAYER_EXT INT16U    SVF_u16_Par;/*����������־λ*/
APPLAYER_EXT INT8U     PefEep_u8_Sig;/*AppToBootдEEPROM��־λ*/


#if UDS_DTC_OPEN==1
APPLAYER_EXT ST_DTC         DtcNumb_u24a8_Par[8];/*������ṹ�����*/
APPLAYER_EXT ST_DTC_STATUS  DtcStatus_u16a8_Par[8];/*������״̬�ṹ�����*/
APPLAYER_EXT ST_DTC_STATUS  LastDtcStatus_u16a8_Par[8];/*�ϸ����ڹ�����״̬�ṹ�����*/
APPLAYER_EXT DTC_EXTENDDATA DtcExtend_u64a8_Par[8];/*��չ���ݽṹ�����*/
APPLAYER_EXT DTC_SNAPSHOT   DtcSnapShot_u80a8_Par[8];/*Snapshot���ݽṹ�����*/
#endif
APPLAYER_EXT INT8U    ParkStatus_u8_Sig;/*Park״̬�����ͽ�ʵ��ֵ��ֵ���������*/
APPLAYER_EXT INT8U    EppStatus_u8_Sig;/*EPP״̬����Ҳ�Ǻ��������򽻻��ı���*/
APPLAYER_EXT INT16U   MotorSpd_u16_Sig;/*���ת�ٱ���Ҳ�Ǻ��������򽻻��ı���*/
APPLAYER_EXT INT16S   MotorSpd_s16_Sig;/*���ת�ٱ���Ҳ�Ǻ��������򽻻��ı���*/

APPLAYER_EXT INT8U    TesterRefNumb_u8a6_Par[6];
APPLAYER_EXT INT8U    Odmeter_u8a3_Sig[3];
APPLAYER_EXT INT8U    Resever_u8a2_Sig[2];
APPLAYER_EXT INT8U    OldSessionMode_u8_Sig;/*�ϵĻỰģʽ*/

APPLAYER_EXT INT8U    EepRomTimes_u8_Sig;


APPLAYER_EXT INT16U   BootTimes_u16_Par;/*Bootˢд����*/
APPLAYER_EXT INT16U   PifPtcb_u16a16a16_Par[16][8];/*DID:FF10-FF1F*/
APPLAYER_EXT INT16U   BootSwRefNumb_u16a10_Par[5];/*DID:F183*/
APPLAYER_EXT INT16U   ECUPartNumb_u16a6_Par[3];/*DID:F187*/
APPLAYER_EXT INT16U   SysSupplierId_u16a6_Par[3];/*DID:F18A*/
APPLAYER_EXT INT16U   Vin_u16a17_Par[9];/*DID:F190*/
APPLAYER_EXT INT16U   EcuHwNumb_u16a6_Par[3];/*DID:F191*/
APPLAYER_EXT INT16U   EcuHwRefNumb_u16a10_Par[5];/*DID:F192*/
APPLAYER_EXT INT16U   EcuSwRefNumb_u16a10_Par[5];/*DID:F194*/

APPLAYER_EXT INT16U   EcuCalSwNumb_u16a6_Par[3];/*DID:F1A1*/
APPLAYER_EXT INT16U   EcuNetRefNumb_u16a6_Par[3];/*DID:F1A2*/
APPLAYER_EXT INT16U   VehFeature_u16a20_Par[10];/*DID:F1A8*/
APPLAYER_EXT INT16U   EcuMData_u16a3_Par[2];/*DID:F18B*/
APPLAYER_EXT INT16U   EcuSupplierSN_u16a10_Par[5];/*DID:F18C*/



APPLAYER_EXT INT16U   AsTime_Limited_u16_Par;/*�����ʱ�����*/
APPLAYER_EXT INT16U   BsTime_Limited_u16_Par;/*�����ʱ�����*/
APPLAYER_EXT INT16U   CrTime_Limited_u16_Par;/*�����ʱ�����*/

extern const INT16U   EcuAppSwNumb_u16a6_Par[3];/*DID:F1A0*/

/*********************************************************************************************************
*                                               FUNCTIONS
*********************************************************************************************************
*/
APPLAYER_EXT  void SwReset_v_g(void);/*�����λ����*/
APPLAYER_EXT  void   MailBoxRd_v_g(INT16U MBXnbr);/*Boot Can������պ���*/
#if APP_CODE==0
APPLAYER_EXT  void   CanOutHandel_v_g(void);/*Boot Canȡ���ݺ���*/
APPLAYER_EXT INT16U  CheckAppCode_v_g(void);/*Boot Flash����У��ͺ���*/
APPLAYER_EXT INT16U  PFlash_Check(INT32U StartAddr, INT16U Len, INT16U LastValue);/*Boot Flash����У����㺯��*/
#else
/*------------------------------Dtc------------------------------------*/
#if UDS_DTC_OPEN==1
APPLAYER_EXT void    DtcBackFlashInit_v_g (void);/*DTC EEPROM��ȡ��ĳ�ʼ������*/
APPLAYER_EXT void    DtcDual_v_g(INT8U DtcNumb);/*DTC ״̬��ֵ����*/
APPLAYER_EXT void    DtcCycleDef_v_g(void);/*DTC ���ڴ�����*/
APPLAYER_EXT void    ClearDtc_v_g(void);/*DTC �������*/
APPLAYER_EXT void    DTCExtendDual_v_g (void);/*DTC ��չ���ݴ�����*/
APPLAYER_EXT void    ClearSignelDtc_v_g(INT8U DtcNumb);/*DTC�����������*/
APPLAYER_EXT void    WDtcSnapshot_v_g(INT8U DtcNumb,INT8U SupBatt,INT32U Odreading,INT8U CoolTemp,INT8U Igstatus );/*DTCSnapshot���ݴ�����*/
#endif
#endif
/*------------------------------Crc And seedKey------------------------------------*/
APPLAYER_EXT INT32U  SeedToKey_v_g (INT32U Seed, INT32U Mask);/*SeedKey�����㷨*/
APPLAYER_EXT INT32U  GenerateCRC32(BYTEPTR DataBuf, INT32U len, INT32U oldcrc32);/*CRCУ���㷨*/

/*------------------------------EEPROM And Flash������------------------------------------*/
APPLAYER_EXT void    SaveData_v_g(void);/*дEEPROM����*/
APPLAYER_EXT void    ReadData_v_g(void);/*��EEPROM����*/


APPLAYER_EXT void    WriteFlashDual(void);/*дFlash������*/
APPLAYER_EXT void    EraseFlashDual(void);/*����Flash������*/
APPLAYER_EXT void    WriteMemDual(void);/*ͨ����ַдEEPROM������*/
APPLAYER_EXT void    ReadMemDual(void);/*ͨ����ַ��EEPROM������*/
/*------------------------------EEPROM And Flash������------------------------------------*/
APPLAYER_EXT void    UdsInit_v_g(void);/*��ʼ������*/
APPLAYER_EXT void    UDSApp_v_g(void);/*����ִ�к�������Ҫ��ʱ�����*/
APPLAYER_EXT INT8U   AppConFrimNet_v_g(USDATACONFIRM *ConFirmPdu);/*����ȷ�Ϻ���*/
APPLAYER_EXT void    AppReceiveFFind_v_g();/*������֡����*/
APPLAYER_EXT void    TimeDual_v_g(void);/*ʱ�䴦����*/
APPLAYER_EXT void    AppReqNetSend_v_g(RSP_A_PDU AppRspPdu,USDATAREQUEST *AppToNet);/*Ӧ�ò�����������������ݽ�������*/
APPLAYER_EXT void    AppSendRspMsg(void);/*Ӧ�ò㷢�ͺ���*/
APPLAYER_EXT void    AppRevNetData_v_g(USDATAINDICATION *NetPdu ,REQ_A_PDU AppReqPud);/*��������������Ӧ�ò㽻������*/
APPLAYER_EXT void    AppUdsService_v_g(BYTEPTR Services);/*������������*/
APPLAYER_EXT void    RspPduAdr_v_g(REQ_A_PDU AppReqPdu,RSP_A_PDU *AppRspPdu);/*��Ӧ��ַ������*/

/*-------------------------------Sub_Function ���ܷ�����----------------------------------*/
APPLAYER_EXT void   DiagnosticSessionControl_v_g(BYTEPTR RevData);
APPLAYER_EXT void   EcuReset_v_g(BYTEPTR RevData);                                        
APPLAYER_EXT void   SecurityAccess_v_g(BYTEPTR RevData);
APPLAYER_EXT void   CommunicationControl_v_g(BYTEPTR RevData);
APPLAYER_EXT void   ControlDTCSetting_v_g(BYTEPTR RevData);
APPLAYER_EXT void   TesterPresent_v_g(BYTEPTR RevData);
APPLAYER_EXT void   ResponseOnEvent_v_g(BYTEPTR RevData);
APPLAYER_EXT void   LinkControl_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   DynamicallyDefineDataIdentifier_v_g(BYTEPTR RevData);
APPLAYER_EXT void   ReadDtcMsg_v_g(BYTEPTR RevData);
APPLAYER_EXT void   RoutineControl_v_g(BYTEPTR RevData);   
/*-------------------------------WithOut Sub_Function ���ܷ�����----------------------------------*/
APPLAYER_EXT void   ClearDiagImfor_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   RequestDownload_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   RequestUpload_v_g(BYTEPTR RevData);   
APPLAYER_EXT void   TansferData_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   RequestTansferExit_v_g(BYTEPTR RevData);  
APPLAYER_EXT void   SecuredDataTransmission_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   ReadDataById_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   ReadMemoryByAddress_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   ReadScalingDataByIdentifier_v_g(BYTEPTR RevData);  
APPLAYER_EXT void   ReadDataByPeriodicIdentifier_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   WriteDataById_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   WriteMemoryByAddress_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   InputOutputControlById(BYTEPTR RevData); 

APPLAYER_EXT void DtcInit_v_s(void);
APPLAYER_EXT void DtcBackFlashInit_v_g (void);

#endif








