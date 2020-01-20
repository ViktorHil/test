/* -----------------------------------------------------------------------------
  Filename:    drv_par.h
  Description: Toolversion: 08.08.00.01.50.00.91.02.00.00
               
               Serial Number: CBD1500091
               Customer Info: Continental Automotive
                              Package: FNOS I3v3 - CANbedded License for Ford
                              Micro: Freescale MPC5605B
                              Compiler: Wind River Diab 5.9.4.2
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyDriverBase
               
               Configuration   : D:\TCU\Bundle3\git\vuc\G3DO_VuC_w_Tp\Workspace\CANsetup\GenySetups\FordG3DO.gny
               
               ECU: 
                       TargetSystem: Hw_Mpc55xx_Flexcan2Cpu
                       Compiler:     DIABDATA
                       Derivates:    MPC5605
               
               Channel "Channel0":
                       Databasefile: D:\TCU\Bundle3\git\vuc\G3DO_VuC_w_Tp\Workspace\CANsetup\DBCs\Y2017_CGEA1.3_CMDB_B_v17.05_HS4.dbc
                       Bussystem:    CAN
                       Manufacturer: Ford
                       Node:         TCU_EM

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2014 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#if !defined(__DRV_PAR_H__)
#define __DRV_PAR_H__

/* -----------------------------------------------------------------------------
    &&&~ Signal Structures
 ----------------------------------------------------------------------------- */

typedef vbittype uint8_t;

typedef struct _c_GlobalClock_Data_HS4_msgTypeTag
{
  vbittype GlblClkYr_No_Actl : 8;
  vbittype unused0 : 8;
  vbittype GlblClkDay_No_Actl_1 : 8;
  vbittype GlblClkDay_No_Actl_0 : 8;
  vbittype GlblClkMnte_No_Actl : 8;
  vbittype GlblClkScnd_No_Actl : 8;
  vbittype GlblClkHr_No_Actl : 8;
} _c_GlobalClock_Data_HS4_msgType;
typedef struct _c_APIM_Send_Signals_2_HS4_msgTypeTag
{
  vbittype unused0 : 4;
  vbittype TCU_Final_Actvtn_St : 2;
  vbittype TCU_Init_Actvtn_St : 2;
  vbittype unused1 : 8;
  vbittype unused2 : 7;
  vbittype OnbChrgGoTUpdate_B_Rq : 1;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 6;
  vbittype OtaTrg_D_Stat : 2;
} _c_APIM_Send_Signals_2_HS4_msgType;
typedef struct _c_TCU_Request_Signals_2_msgTypeTag
{
  vbittype TCU_Final_Actvtn_Rq : 2;
  vbittype TCU_Init_Actvtn_Rq : 2;
  vbittype APIM_SwPartNo_D_Rq : 2;
  vbittype GPS_Track_D_Rq : 2;
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
} _c_TCU_Request_Signals_2_msgType;
typedef struct _c_GWM_SendSignals_05_HS4_msgTypeTag
{
  vbittype AwdRnge_D_Actl : 3;
  vbittype DasStats_D_Dsply : 2;
  vbittype DasWarn_D_Dsply : 2;
  vbittype EDRTriggerEvntSync : 1;
  vbittype FcwMemStat_B_Actl : 1;
  vbittype FirstRowBuckleDriver : 2;
  vbittype FirstRowBucklePsngr : 2;
  vbittype LaHandsOff_D_Dsply : 2;
  vbittype TCMode : 1;
  vbittype PsngrFrntDetct_D_Actl : 2;
  vbittype RearDiffLckLamp_D_Rq : 2;
  vbittype RearDiffLckMsg_D_Rq : 3;
  vbittype TRLR_SWAY_EVNT_IN_PROG : 1;
  vbittype RstrnImpactEvntStatus : 3;
  vbittype FcwAudioWarn_B_Rq : 1;
  vbittype FcwMemSens_D_Actl : 2;
  vbittype AwdRnge_D_Actl_UB : 1;
  vbittype DasStats_D_Dsply_UB : 1;
  vbittype DasWarn_D_Dsply_UB : 1;
  vbittype EDRTriggerEvntSync_UB : 1;
  vbittype FcwAudioWarn_B_Rq_UB : 1;
  vbittype FcwMemSens_D_Actl_UB : 1;
  vbittype FcwMemStat_B_Actl_UB : 1;
  vbittype FirstRowBuckleDriver_UB : 1;
  vbittype FirstRowBucklePsngr_UB : 1;
  vbittype LaHandsOff_D_Dsply_UB : 1;
  vbittype PsngrFrntDetct_D_Actl_UB : 1;
  vbittype RearDiffLckLamp_D_Rq_UB : 1;
  vbittype RstrnImpactEvntStatus_UB : 1;
  vbittype TCMode_UB : 1;
  vbittype TRLR_SWAY_EVNT_IN_PROG_UB : 1;
  vbittype RearDiffLckMsg_D_Rq_UB : 1;
  vbittype LaActvStats_D_Dsply_UB : 1;
  vbittype CmbbBrkDecel_B_Rq : 1;
  vbittype LaActvStats_D_Dsply : 5;
  vbittype CmbbBrkDecel_B_Rq_UB : 1;
  vbittype CmbbBrkPrchg_D_Rq : 2;
  vbittype CmbbBrkPrchg_D_Rq_UB : 1;
  vbittype LscmbbPostEvnt_B_Dsply : 1;
  vbittype LscmbbPostEvnt_B_Dsply_UB : 1;
  vbittype eCallNotification : 2;
  vbittype eCallNotification_UB : 1;
  vbittype unused0 : 2;
} _c_GWM_SendSignals_05_HS4_msgType;
typedef struct _c_TCU_Send_Signals_msgTypeTag
{
  vbittype ModemReset_D_Stat : 4;
  vbittype unused0 : 4;
  vbittype TCU_Sftwr_Update_D_St : 2;
  vbittype unused1 : 2;
  vbittype PtRmtRprt_D_Stat : 4;
  vbittype unused2 : 1;
  vbittype NxtUsgChrgLcID_No_Actl : 7;
  vbittype NextUsg_Toggle_St : 2;
  vbittype NxtUsgMin_No_Actl : 6;
  vbittype EmgcyCallMute_D_Stat : 3;
  vbittype NxtUsgHr_No_Actl : 5;
  vbittype TelematicsSrvc_D_St : 3;
  vbittype NxtUsgDay_No_Actl : 5;
  vbittype NxtUsgPreCndID_No_Actl : 4;
  vbittype NxtUsgMnth_No_Actl : 4;
  vbittype unused3 : 1;
  vbittype FactoryReset_St : 2;
  vbittype NxtUsgYr_No_Actl : 5;
} _c_TCU_Send_Signals_msgType;
typedef struct _c_TCU_AutoSar_Network_Mgmt_msgTypeTag
{
  vbittype TCU_AutoSarNMNodeId : 8;
  vbittype TCU_AutoSarNMControl : 8;
  vbittype TCU_AutoSarNMReserved1 : 8;
  vbittype TCU_AutoSarNMReserved2 : 8;
  vbittype TCU_GWOnBoardTester : 8;
  vbittype TCU_GWNMProxy : 8;
  vbittype TCU_AutoSarNMReserved3 : 8;
  vbittype TCU_AutoSarNMReserved4 : 8;
} _c_TCU_AutoSar_Network_Mgmt_msgType;
typedef struct _c_GWM_SendSignals_08_HS4_msgTypeTag
{
  vbittype CabnAmb_Te_Actl : 8;
  vbittype DriverWindowPosition : 3;
  vbittype DriverWindowPosition_UB : 1;
  vbittype PassWindowPosition : 3;
  vbittype PassWindowPosition_UB : 1;
  vbittype RearDriverWindowPos : 3;
  vbittype RearDriverWindowPos_UB : 1;
  vbittype RearPassWindowPos : 3;
  vbittype RearPassWindowPos_UB : 1;
  vbittype CabnAmb_Te_Actl_UB : 1;
  vbittype unused0 : 7;
} _c_GWM_SendSignals_08_HS4_msgType;
typedef struct _c_GWM_SendSignals_07_HS4_msgTypeTag
{
  vbittype Veh_V_ActlEng_1 : 8;
  vbittype Veh_V_ActlEng_0 : 8;
  vbittype Veh_V_ActlEng_UB : 1;
  vbittype VehVActlEng_D_Qf : 2;
  vbittype WhlDirFl_D_Actl : 2;
  vbittype WhlDirFl_D_Actl_UB : 1;
  vbittype unused0 : 2;
} _c_GWM_SendSignals_07_HS4_msgType;
typedef struct _c_ABS_Signals_HS4_msgTypeTag
{
  vbittype PrkBrkStatus : 3;
  vbittype BrkTot_Tq_RqArb_1 : 5;
  vbittype BrkTot_Tq_RqArb_0 : 8;
  vbittype unused0 : 3;
  vbittype Abs_B_Falt : 1;
  vbittype Abs_B_Falt_UB : 1;
  vbittype StabCtlBrkActv_B_Actl : 1;
  vbittype VehLatComp_A_Actl_1 : 2;
  vbittype VehLatComp_A_Actl_0 : 8;
  vbittype PrkBrkStatus_UB : 1;
  vbittype StabCtlBrkActv_B_Actl_UB : 1;
  vbittype TracCtlPtActv_B_Actl_UB : 1;
  vbittype VehLatComp_A_Actl_UB : 1;
  vbittype VehLongComp_A_Actl_UB : 1;
  vbittype TracCtlPtActv_B_Actl : 1;
  vbittype VehLongComp_A_Actl_1 : 2;
  vbittype VehLongComp_A_Actl_0 : 8;
  vbittype AbsActv_B_Actl_UB : 1;
  vbittype VehYawComp_W_Actl_UB : 1;
  vbittype AbsActv_B_Actl : 1;
  vbittype BrkTot_Tq_RqArb_UB : 1;
  vbittype VehYawComp_W_Actl_1 : 4;
  vbittype VehYawComp_W_Actl_0 : 8;
} _c_ABS_Signals_HS4_msgType;
typedef struct _c_GWM_SendSignals_09_HS4_msgTypeTag
{
  vbittype OdometerMasterValue_2 : 8;
  vbittype OdometerMasterValue_1 : 8;
  vbittype OdometerMasterValue_0 : 8;
  vbittype Cta_D_Rq : 2;
  vbittype FuelRange_L_DsplyGWM_1 : 6;
  vbittype FuelRange_L_DsplyGWM_0 : 8;
  vbittype Cta_D_Rq_UB : 1;
  vbittype FuelLvl_Pc_Dsply_UB : 1;
  vbittype FuelRange_L_Dsply_UB : 1;
  vbittype LscmbbStat_B_Actl : 1;
  vbittype Sod_D_Rq : 2;
  vbittype FuelLvl_Pc_Dsply_1 : 2;
  vbittype FuelLvl_Pc_Dsply_0 : 8;
  vbittype LscmbbStat_B_Actl_UB : 1;
  vbittype OdometerMasterValue_UB : 1;
  vbittype Sod_D_Rq_UB : 1;
  vbittype unused0 : 5;
} _c_GWM_SendSignals_09_HS4_msgType;
typedef struct _c_GWM_SendSignals_04_HS4_msgTypeTag
{
  vbittype EngSrvcRqd_B_Rq : 1;
  vbittype EngIdlShutDown_D_Stat : 2;
  vbittype EngPtoMde_D_Actl : 3;
  vbittype FuelFlw_Vl_Dsply_1 : 2;
  vbittype FuelFlw_Vl_Dsply_0 : 8;
  vbittype EngClnt_Te_Actl : 8;
  vbittype AirAmb_Te_ActlFilt_UB : 1;
  vbittype EngClnt_Te_Actl_UB : 1;
  vbittype EngIdlShutDown_D_Stat_UB : 1;
  vbittype EngOilLife_Pc_Actl_UB : 1;
  vbittype EngPtoMde_D_Actl_UB : 1;
  vbittype FuelFlw_Vl_Dsply_UB : 1;
  vbittype AirAmb_Te_ActlFilt_1 : 2;
  vbittype AirAmb_Te_ActlFilt_0 : 8;
  vbittype EngSrvcRqd_B_Rq_UB : 1;
  vbittype EngOilLife_Pc_Actl : 7;
  vbittype StopStrtDrvMde_D_Indic : 2;
  vbittype StopStrtDrvMde_D_Indic_UB : 1;
  vbittype EngAirFiltMsgTxt_D_Rq : 3;
  vbittype EngAirFiltMsgTxt_D_Rq_UB : 1;
  vbittype unused0 : 1;
  vbittype EngAirFiltLife_Pc_Actl : 7;
  vbittype EngAirFiltLife_Pc_Actl_UB : 1;
} _c_GWM_SendSignals_04_HS4_msgType;
typedef struct _c_GWM_SendSignals_03_HS4_msgTypeTag
{
  vbittype PrplWhlTot2_Tq_Actl_1 : 8;
  vbittype PrplWhlTot2_Tq_Actl_0 : 8;
  vbittype PwPckTq_D_Stat : 2;
  vbittype ApedPos_Pc_ActlArb_UB : 1;
  vbittype EngAout_N_Actl_1 : 5;
  vbittype EngAout_N_Actl_0 : 8;
  vbittype EngAout_N_Actl_UB : 1;
  vbittype PrplWhlTot2_Tq_Actl_UB : 1;
  vbittype PwPckTq_D_Stat_UB : 1;
  vbittype StopStrtIODTxt_D_Rq : 5;
  vbittype unused0 : 8;
  vbittype unused1 : 5;
  vbittype StopStrtIODTxt_D_Rq_UB : 1;
  vbittype ApedPos_Pc_ActlArb_1 : 2;
  vbittype ApedPos_Pc_ActlArb_0 : 8;
} _c_GWM_SendSignals_03_HS4_msgType;
typedef struct _c_GWM_SendSignals_02_HS4_msgTypeTag
{
  vbittype Eng_D_Stat : 2;
  vbittype unused0 : 6;
  vbittype Eng_D_Stat_UB : 1;
  vbittype PwSrcULoOvrTe_B_Actl : 1;
  vbittype PwSrcULoOvrTe_B_Actl_UB : 1;
  vbittype PlgActvArb_B_Actl : 1;
  vbittype PlgActvArb_B_Actl_UB : 1;
  vbittype UpftrDgtlIn10_D_Stat : 2;
  vbittype UpftrDgtlIn10_D_Stat_UB : 1;
  vbittype GboxOil_Te_Actl : 8;
  vbittype GearLvrPos_D_Actl : 4;
  vbittype TrnSrvcRqd_B_Rq : 1;
  vbittype GearRvrse_D_Actl : 3;
  vbittype BpedDrvAppl_D_Actl : 2;
  vbittype PwSysULoFalt_D_Stat : 4;
  vbittype GearLvrPos_D_Actl_UB : 1;
  vbittype PwSysULoFalt_D_Stat_UB : 1;
  vbittype TrnSrvcRqd_B_Rq_UB : 1;
  vbittype GboxOil_Te_Actl_UB : 1;
  vbittype BattULo_U_Actl_UB : 1;
  vbittype BpedDrvAppl_D_Actl_UB : 1;
  vbittype GearRvrse_D_Actl_UB : 1;
  vbittype BattTracCool_D_RqDcdc : 2;
  vbittype BattTracCool_D_RqDcdc_UB : 1;
  vbittype PwSrcULoOn_B_Actl : 1;
  vbittype PwSrcULoOn_B_Actl_UB : 1;
  vbittype UpftrDgtlIn11_D_Stat : 2;
  vbittype UpftrDgtlIn12_D_Stat : 2;
  vbittype UpftrDgtlIn11_D_Stat_UB : 1;
  vbittype UpftrDgtlIn12_D_Stat_UB : 1;
  vbittype BattULo_U_Actl : 8;
} _c_GWM_SendSignals_02_HS4_msgType;
typedef struct _c_APIM_TCU_Word_Rx_HS4_msgTypeTag
{
  vbittype APIM_TCU_Word_Rx_7 : 8;
  vbittype APIM_TCU_Word_Rx_6 : 8;
  vbittype APIM_TCU_Word_Rx_5 : 8;
  vbittype APIM_TCU_Word_Rx_4 : 8;
  vbittype APIM_TCU_Word_Rx_3 : 8;
  vbittype APIM_TCU_Word_Rx_2 : 8;
  vbittype APIM_TCU_Word_Rx_1 : 8;
  vbittype APIM_TCU_Word_Rx_0 : 8;
} _c_APIM_TCU_Word_Rx_HS4_msgType;
typedef struct _c_APIM_TCU_Word_Tx_HS4_msgTypeTag
{
  vbittype APIM_TCU_Word_Tx_7 : 8;
  vbittype APIM_TCU_Word_Tx_6 : 8;
  vbittype APIM_TCU_Word_Tx_5 : 8;
  vbittype APIM_TCU_Word_Tx_4 : 8;
  vbittype APIM_TCU_Word_Tx_3 : 8;
  vbittype APIM_TCU_Word_Tx_2 : 8;
  vbittype APIM_TCU_Word_Tx_1 : 8;
  vbittype APIM_TCU_Word_Tx_0 : 8;
} _c_APIM_TCU_Word_Tx_HS4_msgType;
typedef struct _c_TCU_Send_Signals_3_msgTypeTag
{
  vbittype WifiDataUsage_D_Stat : 2;
  vbittype WifiDevcListNew_B_Stat : 1;
  vbittype WifiEnbl_D_Stat : 2;
  vbittype WifiHtsptEnbl_D_Stat : 2;
  vbittype unused0 : 1;
  vbittype WifiHtsptScrty_D_Stat : 2;
  vbittype WifiHtsptVisbl_D_Stat : 2;
  vbittype ModemSigStren_D_Stat : 3;
  vbittype unused1 : 1;
  vbittype ModemTechnology_D_Stat : 3;
  vbittype WifiDataUsage_Pc_Actl : 4;
  vbittype unused2 : 1;
  vbittype ModemTechnology_D2_Stat : 3;
  vbittype WifiDataUsageOn_D_Stat : 2;
  vbittype WifiHtsptCnnct_D_Stat : 2;
  vbittype unused3 : 1;
  vbittype Telematics_D_Falt : 3;
  vbittype unused4 : 5;
  vbittype WifiNoDevcCnnct_No_Actl : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
} _c_TCU_Send_Signals_3_msgType;
typedef struct _c_APIM_Request_Signals_2_HS4_msgTypeTag
{
  vbittype WifiCarrierInfo_B_Rq : 1;
  vbittype WifiDataUsage_D_Rq : 2;
  vbittype WifiDevcList_D_Rq : 2;
  vbittype WifiHtsptEnbl_D_Rq : 2;
  vbittype WifiHtsptMacAddr_B_Rq : 1;
  vbittype WifiDevcListIndx_No_Rq : 8;
  vbittype WifiDevcListSize_D_Rq : 5;
  vbittype unused0 : 3;
  vbittype WifiHtsptVisbl_D_Rq : 2;
  vbittype WifiRemoveDevc_D_Rq : 2;
  vbittype WifiHtsptTrial_D_RqDrv : 2;
  vbittype unused1 : 2;
  vbittype WifiRemoveIndx_No_Rq : 8;
} _c_APIM_Request_Signals_2_HS4_msgType;
typedef struct _c_OPTIN_RDISP_WORD_Rx_HS4_msgTypeTag
{
  vbittype OPTIN_RDISP_WORD_Rx_7 : 8;
  vbittype OPTIN_RDISP_WORD_Rx_6 : 8;
  vbittype OPTIN_RDISP_WORD_Rx_5 : 8;
  vbittype OPTIN_RDISP_WORD_Rx_4 : 8;
  vbittype OPTIN_RDISP_WORD_Rx_3 : 8;
  vbittype OPTIN_RDISP_WORD_Rx_2 : 8;
  vbittype OPTIN_RDISP_WORD_Rx_1 : 8;
  vbittype OPTIN_RDISP_WORD_Rx_0 : 8;
} _c_OPTIN_RDISP_WORD_Rx_HS4_msgType;
typedef struct _c_OPTIN_RDISP_WORD_Tx_msgTypeTag
{
  vbittype OPTIN_RDISP_WORD_Tx_7 : 8;
  vbittype OPTIN_RDISP_WORD_Tx_6 : 8;
  vbittype OPTIN_RDISP_WORD_Tx_5 : 8;
  vbittype OPTIN_RDISP_WORD_Tx_4 : 8;
  vbittype OPTIN_RDISP_WORD_Tx_3 : 8;
  vbittype OPTIN_RDISP_WORD_Tx_2 : 8;
  vbittype OPTIN_RDISP_WORD_Tx_1 : 8;
  vbittype OPTIN_RDISP_WORD_Tx_0 : 8;
} _c_OPTIN_RDISP_WORD_Tx_msgType;
typedef struct _c_LocationServices_Data2_HS4_msgTypeTag
{
  vbittype LocationServices_2_7 : 8;
  vbittype LocationServices_2_6 : 8;
  vbittype LocationServices_2_5 : 8;
  vbittype LocationServices_2_4 : 8;
  vbittype LocationServices_2_3 : 8;
  vbittype LocationServices_2_2 : 8;
  vbittype LocationServices_2_1 : 8;
  vbittype LocationServices_2_0 : 8;
} _c_LocationServices_Data2_HS4_msgType;
typedef struct _c_LocationServices_Data1_HS4_msgTypeTag
{
  vbittype LocationServices_1_7 : 8;
  vbittype LocationServices_1_6 : 8;
  vbittype LocationServices_1_5 : 8;
  vbittype LocationServices_1_4 : 8;
  vbittype LocationServices_1_3 : 8;
  vbittype LocationServices_1_2 : 8;
  vbittype LocationServices_1_1 : 8;
  vbittype LocationServices_1_0 : 8;
} _c_LocationServices_Data1_HS4_msgType;
typedef struct _c_CellPhonePassport_Stat_HS4_msgTypeTag
{
  vbittype KeyProg_No_Actl : 4;
  vbittype PepsKeyActv_D_Stat : 4;
  vbittype Rstrt_T_Actl_1 : 8;
  vbittype Rstrt_T_Actl_0 : 8;
  vbittype RstrtSetting_T_Actl_1 : 8;
  vbittype RstrtSetting_T_Actl_0 : 3;
  vbittype PepsKeyFound_No_Actl : 4;
  vbittype unused0 : 1;
  vbittype HeadLghtOn_D_Rq : 3;
  vbittype VehLck_D_Dsply : 2;
  vbittype unused1 : 3;
} _c_CellPhonePassport_Stat_HS4_msgType;
typedef struct _c_CellPhonePassport_Req_msgTypeTag
{
  vbittype CellChirp_D_Rq : 3;
  vbittype CellLock_D_Rq : 3;
  vbittype CellRstrt_D_Rq : 2;
  vbittype CellPanic_D_Rq : 2;
  vbittype unused0 : 6;
  vbittype CellChirpRq_No_Actl : 8;
  vbittype CellLockRq_No_Actl : 8;
  vbittype CellPanicRq_No_Actl : 8;
  vbittype CellRstrtRq_No_Actl : 8;
  vbittype RollCodeCell_No_Actl_1 : 8;
  vbittype RollCodeCell_No_Actl_0 : 8;
} _c_CellPhonePassport_Req_msgType;
typedef struct _c_GGCC_Config_Mgmt_ID_1_HS4_msgTypeTag
{
  vbittype VehicleGGCCData_7 : 8;
  vbittype VehicleGGCCData_6 : 8;
  vbittype VehicleGGCCData_5 : 8;
  vbittype VehicleGGCCData_4 : 8;
  vbittype VehicleGGCCData_3 : 8;
  vbittype VehicleGGCCData_2 : 8;
  vbittype VehicleGGCCData_1 : 8;
  vbittype VehicleGGCCData_0 : 8;
} _c_GGCC_Config_Mgmt_ID_1_HS4_msgType;
typedef struct _c_BodyInfo_3_HS4_msgTypeTag
{
  vbittype Ignition_Status : 4;
  vbittype Parklamp_Status : 2;
  vbittype unused0 : 1;
  vbittype DrStatTgate_B_Actl : 1;
  vbittype Day_Night_Status : 2;
  vbittype unused1 : 6;
  vbittype unused2 : 8;
  vbittype Dimming_Lvl : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype PrkBrkActv_B_Actl : 1;
  vbittype unused5 : 1;
  vbittype LifeCycMde_D_Actl : 4;
  vbittype DrStatRr_B_Actl : 1;
  vbittype DrStatRl_B_Actl : 1;
  vbittype unused6 : 2;
  vbittype DrStatDrv_B_Actl : 1;
  vbittype DrStatPsngr_B_Actl : 1;
  vbittype DrStatHood_B_Actl : 1;
  vbittype DrStatInnrTgate_B_Actl : 1;
  vbittype Delay_Accy : 1;
  vbittype unused7 : 1;
} _c_BodyInfo_3_HS4_msgType;
typedef struct _c_TCU_Send_Signals_4_msgTypeTag
{
  vbittype SDNCon_St : 3;
  vbittype unused0 : 5;
  vbittype CCOI_PolicyServer_St : 4;
  vbittype unused1 : 4;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
  vbittype unused7 : 8;
} _c_TCU_Send_Signals_4_msgType;
typedef struct _c_TRAFFIC_RDISP_WORD_Rx_msgTypeTag
{
  vbittype TRAFFIC_RDISP_WORD_Rx_7 : 8;
  vbittype TRAFFIC_RDISP_WORD_Rx_6 : 8;
  vbittype TRAFFIC_RDISP_WORD_Rx_5 : 8;
  vbittype TRAFFIC_RDISP_WORD_Rx_4 : 8;
  vbittype TRAFFIC_RDISP_WORD_Rx_3 : 8;
  vbittype TRAFFIC_RDISP_WORD_Rx_2 : 8;
  vbittype TRAFFIC_RDISP_WORD_Rx_1 : 8;
  vbittype TRAFFIC_RDISP_WORD_Rx_0 : 8;
} _c_TRAFFIC_RDISP_WORD_Rx_msgType;
typedef struct _c_TRAFFIC_RDISP_WORD_Tx_msgTypeTag
{
  vbittype TRAFFIC_RDISP_WORD_Tx_7 : 8;
  vbittype TRAFFIC_RDISP_WORD_Tx_6 : 8;
  vbittype TRAFFIC_RDISP_WORD_Tx_5 : 8;
  vbittype TRAFFIC_RDISP_WORD_Tx_4 : 8;
  vbittype TRAFFIC_RDISP_WORD_Tx_3 : 8;
  vbittype TRAFFIC_RDISP_WORD_Tx_2 : 8;
  vbittype TRAFFIC_RDISP_WORD_Tx_1 : 8;
  vbittype TRAFFIC_RDISP_WORD_Tx_0 : 8;
} _c_TRAFFIC_RDISP_WORD_Tx_msgType;
typedef struct _c_TCU_Request_Signals_3_msgTypeTag
{
  vbittype OLT_FllbckTim_T_Rq : 5;
  vbittype unused0 : 3;
  vbittype OLT_QryIntvlTim_T_Rq : 4;
  vbittype unused1 : 4;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
  vbittype unused7 : 8;
} _c_TCU_Request_Signals_3_msgType;
typedef struct _c_APIM_Send_Signals_4_msgTypeTag
{
  vbittype OLT_FllbckTim_T_St : 5;
  vbittype OLT_Decoding_St : 3;
  vbittype OLT_QryIntvlTim_T_St : 4;
  vbittype OLT_Decompression_St : 3;
  vbittype unused0 : 1;
} _c_APIM_Send_Signals_4_msgType;
typedef struct _c_APIM_Send_Signals_3_msgTypeTag
{
  vbittype OLT_Route_St : 1;
  vbittype OLT_LatDeg_St : 7;
  vbittype unused0 : 4;
  vbittype OLT_LatDegFrac_St_2 : 4;
  vbittype OLT_LatDegFrac_St_1 : 8;
  vbittype OLT_LatDegFrac_St_0 : 8;
  vbittype OLT_LongDeg_St : 8;
  vbittype OLT_LongSign_St : 1;
  vbittype OLT_LatSign_St : 1;
  vbittype unused1 : 2;
  vbittype OLT_LongDegFrac_St_2 : 4;
  vbittype OLT_LongDegFrac_St_1 : 8;
  vbittype OLT_LongDegFrac_St_0 : 8;
} _c_APIM_Send_Signals_3_msgType;
typedef struct _c_TCU_Response_Signals_msgTypeTag
{
  vbittype OLT_Supported_Rsp : 2;
  vbittype unused0 : 6;
  vbittype CountryCode_Char1_Rsp : 8;
  vbittype CountryCode_Char2_Rsp : 8;
  vbittype CountryCode_Char3_Rsp : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
} _c_TCU_Response_Signals_msgType;
typedef struct _c_APIM_Request_Signals_3_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype CountryCode_Char1_Rq : 8;
  vbittype CountryCode_Char2_Rq : 8;
  vbittype CountryCode_Char3_Rq : 8;
  vbittype OLT_TPEGData_Rq : 1;
  vbittype unused1 : 7;
} _c_APIM_Request_Signals_3_msgType;
typedef struct _c_GWM_SendSignals_10_HS4_msgTypeTag
{
  vbittype Disp_LangSel_St : 5;
  vbittype HMI_HMIMode_St : 3;
  vbittype Mc_VehLangUsrSel_St : 6;
  vbittype unused0 : 2;
  vbittype VRM_BTPhoneSts_St : 5;
  vbittype unused1 : 1;
  vbittype ValetMode_D_Stat : 2;
  vbittype BttOn_B_Rq : 1;
  vbittype BttOn_B_Rq_UB : 1;
  vbittype Disp_LangSel_St_UB : 1;
  vbittype unused2 : 1;
  vbittype HMI_HMIMode_St_UB : 1;
  vbittype Mc_VehLangUsrSel_St_UB : 1;
  vbittype unused3 : 1;
  vbittype ValetMode_D_Stat_UB : 1;
  vbittype VRM_BTPhoneSts_St_UB : 1;
  vbittype SpkrDgtlRight_D_Stat : 2;
  vbittype SpkrDgtlRight_D_Stat_UB : 1;
  vbittype SpkrDgtlLeft_D_Stat : 2;
  vbittype SpkrDgtlLeft_D_Stat_UB : 1;
  vbittype SpkrStdRight_D_Stat_UB : 1;
  vbittype SpkrDgtlCntr_D_Stat : 2;
  vbittype SpkrStdRight_D_Stat : 2;
  vbittype SpkrStdLeft_D_Stat : 2;
  vbittype SpkrStdCntr_D_Stat : 2;
  vbittype SpkrDgtlCntr_D_Stat_UB : 1;
  vbittype SpkrStdCntr_D_Stat_UB : 1;
  vbittype SpkrStdLeft_D_Stat_UB : 1;
  vbittype CCOI_PolicyClient_St : 4;
  vbittype CCOI_PolicyClient_St_UB : 1;
  vbittype Disp_LangSel2_St : 7;
  vbittype Disp_LangSel2_St_UB : 1;
} _c_GWM_SendSignals_10_HS4_msgType;
typedef struct _c_GWM_SendSignals_01_HS4_msgTypeTag
{
  vbittype RollCodeUnlock_1 : 8;
  vbittype RollCodeUnlock_0 : 8;
  vbittype VehKeyActv_D_Stat : 4;
  vbittype ChrgCordLck_D_Stat : 3;
  vbittype ChrgCordLck_D_Stat_UB : 1;
  vbittype PrmtrAlrmEvnt_D_Stat : 4;
  vbittype Veh_Lock_Status : 2;
  vbittype Perimeter_Alarm_Status : 2;
  vbittype Remote_Device_Feedback : 3;
  vbittype RollCodeUnlock_UB : 1;
  vbittype Perimeter_Alarm_Status_UB : 1;
  vbittype PrmtrAlrmEvnt_D_Stat_UB : 1;
  vbittype Remote_Device_Feedback_UB : 1;
  vbittype BattTrac_Te_Actl_UB : 1;
  vbittype Veh_Lock_Status_UB : 1;
  vbittype VehKeyActv_D_Stat_UB : 1;
  vbittype Batt_Crit_SoC_B : 1;
  vbittype Batt_Crit_SoC_B_UB : 1;
  vbittype unused0 : 2;
  vbittype BattTrac_Te_Actl_1 : 2;
  vbittype BattTrac_Te_Actl_0 : 8;
  vbittype BSBattSOC_UB : 1;
  vbittype BSBattSOC : 7;
} _c_GWM_SendSignals_01_HS4_msgType;
typedef struct _c_Yaw_Data_HS4_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype VehYaw_W_Actl_1 : 8;
  vbittype VehYaw_W_Actl_0 : 8;
  vbittype unused2 : 8;
  vbittype VehRollYaw_No_Cnt : 8;
  vbittype unused3 : 2;
  vbittype VehYawWActl_D_Qf : 2;
  vbittype unused4 : 4;
} _c_Yaw_Data_HS4_msgType;
typedef struct _c_Tire_Pressure_Stat_HS4_msgTypeTag
{
  vbittype Tire_Press_System_Stat : 4;
  vbittype Tire_Press_Telltale : 2;
  vbittype TirePReset_D_Stat : 2;
  vbittype Tire_Press_LF_Stat : 4;
  vbittype Tire_Press_RF_Stat : 4;
  vbittype Tire_Press_RR_ORR_Stat : 4;
  vbittype Tire_Press_LR_OLR_Stat : 4;
  vbittype Tire_Press_IRR_Stat : 4;
  vbittype Tire_Press_ILR_Stat : 4;
  vbittype Tire_Press_Placrd_Frnt : 8;
  vbittype Tire_Press_Placrd_Rear : 8;
} _c_Tire_Pressure_Stat_HS4_msgType;
typedef struct _c_Tire_Pressure_Data_HS4_msgTypeTag
{
  vbittype Tire_Press_LF_Data_1 : 8;
  vbittype Tire_Press_LF_Data_0 : 8;
  vbittype Tire_Press_RF_Data_1 : 8;
  vbittype Tire_Press_RF_Data_0 : 8;
  vbittype Tire_Press_RR_ORR_Data_1 : 8;
  vbittype Tire_Press_RR_ORR_Data_0 : 8;
  vbittype Tire_Press_LR_OLR_Data_1 : 8;
  vbittype Tire_Press_LR_OLR_Data_0 : 8;
} _c_Tire_Pressure_Data_HS4_msgType;
typedef struct _c_Tire_Pressure_Data_DRW_HS4_msgTypeTag
{
  vbittype Tire_Press_ILR_Data_1 : 8;
  vbittype Tire_Press_ILR_Data_0 : 8;
  vbittype Tire_Press_IRR_Data_1 : 8;
  vbittype Tire_Press_IRR_Data_0 : 8;
} _c_Tire_Pressure_Data_DRW_HS4_msgType;
typedef struct _c_GWM_SendSignals_11_HS4_msgTypeTag
{
  vbittype DISP_SetVolume_Rq : 6;
  vbittype DISP_SetVolume_Rq_UB : 1;
  vbittype ChrgOvrdExitScrn_D_Rq_UB : 1;
  vbittype ChrgOvrdExitScrn_D_Rq : 2;
  vbittype unused0 : 6;
} _c_GWM_SendSignals_11_HS4_msgType;
typedef struct _c_TCU_Send_Signals_5_msgTypeTag
{
  vbittype EmgcyCall_D_Stat : 3;
  vbittype EmgcyCallCancl_T_Actl : 5;
  vbittype EmgcyCallFalt_B_Dsply : 1;
  vbittype EmgcyCallHmi_D_Stat : 4;
  vbittype unused0 : 3;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
} _c_TCU_Send_Signals_5_msgType;
typedef struct _c_TCU_Request_Signals_1_msgTypeTag
{
  vbittype ClimtBlwrLim_B_Rq : 1;
  vbittype unused0 : 7;
  vbittype unused1 : 4;
  vbittype TripDist_D_Rq_1 : 4;
  vbittype TripDist_D_Rq_0 : 8;
  vbittype unused2 : 4;
  vbittype NtfyDrvTrgtDist_L_Rq_1 : 4;
  vbittype NtfyDrvTrgtDist_L_Rq_0 : 8;
  vbittype unused3 : 1;
  vbittype NtfyDrvSocLvl1_Pc_Rq : 7;
  vbittype unused4 : 5;
  vbittype OtaTrg_D_Rq : 2;
  vbittype unused5 : 1;
  vbittype unused6 : 6;
  vbittype DrvBhavWarn_B_Rq : 1;
  vbittype PtWakeupActv1_B_Rq : 1;
} _c_TCU_Request_Signals_1_msgType;
typedef struct _c_LocationServices_3_msgTypeTag
{
  vbittype LocationServices_3_7 : 8;
  vbittype LocationServices_3_6 : 8;
  vbittype LocationServices_3_5 : 8;
  vbittype LocationServices_3_4 : 8;
  vbittype LocationServices_3_3 : 8;
  vbittype LocationServices_3_2 : 8;
  vbittype LocationServices_3_1 : 8;
  vbittype LocationServices_3_0 : 8;
} _c_LocationServices_3_msgType;
typedef struct _c_Personality_APIM_Data2_HS4_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype CntrStk_D_RqAssoc : 3;
  vbittype unused6 : 5;
} _c_Personality_APIM_Data2_HS4_msgType;
typedef struct _c_Personality_APIM_Data_HS4_msgTypeTag
{
  vbittype CtrStkFeatConfigActl_1 : 8;
  vbittype CtrStkFeatConfigActl_0 : 8;
  vbittype CtrStkFeatNoActl_1 : 8;
  vbittype CtrStkFeatNoActl_0 : 8;
  vbittype CtrStkPersIndex_D_Actl : 3;
  vbittype PersStore_D_Rq : 3;
  vbittype Pers3OptIn_B_Stats : 1;
  vbittype Pers2OptIn_B_Stats : 1;
  vbittype CtrStkDsplyOp_D_Rq : 3;
  vbittype Pers1OptIn_B_Stats : 1;
  vbittype Pers4OptIn_B_Stats : 1;
  vbittype unused0 : 3;
} _c_Personality_APIM_Data_HS4_msgType;
typedef struct _c_APIM_Request_Signals_HS4_msgTypeTag
{
  vbittype OffPeakTimeSetHR_Rq : 5;
  vbittype unused0 : 3;
  vbittype NextUsageTimeToggle_Rq : 2;
  vbittype OffPeakTimeSetMin_Rq : 6;
  vbittype unused1 : 1;
  vbittype TCU_ESN_D_Rq : 2;
  vbittype ChargePortPwr_Rq : 2;
  vbittype FactoryReset_Rq : 1;
  vbittype LongTermParking_Rq : 2;
  vbittype CbnCmrtPrefLstNmItm_Rq : 8;
  vbittype CbnCmrtPrefListIndx_Rq : 8;
  vbittype unused2 : 2;
  vbittype ModemReset_D_Rq : 4;
  vbittype unused3 : 2;
} _c_APIM_Request_Signals_HS4_msgType;
typedef struct _c_Body_Info_7_HS4_msgTypeTag
{
  vbittype KeyOffMde_D_Actl : 4;
  vbittype unused0 : 4;
} _c_Body_Info_7_HS4_msgType;
typedef struct _c_GWM_SendSignals_15_HS4_msgTypeTag
{
  vbittype ConsAvgTrip_Fe_Dsply_2 : 8;
  vbittype ConsAvgTrip_Fe_Dsply_1 : 8;
  vbittype ConsAvgTrip_Fe_Dsply_0 : 8;
  vbittype ConsAvgTrip_Fe_Dsply_UB : 1;
  vbittype unused0 : 7;
} _c_GWM_SendSignals_15_HS4_msgType;
typedef struct _c_BatteryCharge_Data1_HS4_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 2;
  vbittype PlgActv_D_ActlChrgr : 2;
  vbittype ChrgrIn_Pw_Mx_1 : 4;
  vbittype ChrgrIn_Pw_Mx_0 : 8;
  vbittype ChrgrInPwType_D_Actl : 3;
  vbittype unused3 : 2;
  vbittype PtWakeupActv3_B_Rq : 1;
  vbittype unused4 : 1;
  vbittype ChrgrOutHi_U_Actl_1 : 1;
  vbittype ChrgrOutHi_U_Actl_0 : 8;
  vbittype ChrgrRdyStat_D_Actl : 3;
  vbittype unused5 : 1;
  vbittype ChrgrOutHi_I_Actl_1 : 4;
  vbittype ChrgrOutHi_I_Actl_0 : 8;
} _c_BatteryCharge_Data1_HS4_msgType;
typedef struct _c_GWM_SendSignals_12_HS4_msgTypeTag
{
  vbittype BattTracSoc_Pc_Dsply : 8;
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 6;
  vbittype BattTracSoc_Pc_Dsply_UB : 1;
  vbittype BattTracSrvcRqd_B_Rq : 1;
  vbittype BattTracSrvcRqd_B_Rq_UB : 1;
  vbittype BattTracWarnLamp_B_Rq : 1;
  vbittype BattTracWarnLamp_B_Rq_UB : 1;
  vbittype BattTrac_E_Avail_UB : 1;
  vbittype ChrgrSrvcRqd_B_Rq : 1;
  vbittype BattTrac_E_Avail_1 : 3;
  vbittype BattTrac_E_Avail_0 : 8;
  vbittype ChrgrSrvcRqd_B_Rq_UB : 1;
  vbittype HtrnAin_UHi_Actl_1 : 7;
  vbittype HtrnAin_UHi_Actl_0 : 3;
  vbittype HtrnAin_UHi_Actl_UB : 1;
  vbittype WaterInFuel_B_Falt : 1;
  vbittype WaterInFuel_B_Falt_UB : 1;
  vbittype unused3 : 2;
} _c_GWM_SendSignals_12_HS4_msgType;
typedef struct _c_GWM_SendSignals_14_HS4_msgTypeTag
{
  vbittype HybMdeStat_D_Dsply : 3;
  vbittype HybMdeStat_D_Dsply_UB : 1;
  vbittype PlgActvArb_B_Dsply : 1;
  vbittype PlgActvArb_B_Dsply_UB : 1;
  vbittype ConsTipTot_Pc_Dsply_1 : 2;
  vbittype ConsTipTot_Pc_Dsply_0 : 8;
  vbittype ConsTipTot_Pc_Dsply_UB : 1;
  vbittype ConsTipUnitPt_D_Dsply : 2;
  vbittype ConsTipUnitPt_D_Dsply_UB : 1;
  vbittype HtrnSrvcRqd_B_Dsply : 1;
  vbittype HtrnSrvcRqd_B_Dsply_UB : 1;
  vbittype HtrnWarnLamp_B_Dsply : 1;
  vbittype HtrnWarnLamp_B_Dsply_UB : 1;
  vbittype ConsTipA_No_Dsply_1 : 8;
  vbittype ConsTipA_No_Dsply_0 : 2;
  vbittype ConsTipA_No_Dsply_UB : 1;
  vbittype ConsTipDecel_No_Dsply_1 : 5;
  vbittype ConsTipDecel_No_Dsply_0 : 5;
  vbittype ConsTipDecel_No_Dsply_UB : 1;
  vbittype ConsTipV_No_Dsply_1 : 2;
  vbittype ConsTipV_No_Dsply_0 : 8;
  vbittype ConsTipV_No_Dsply_UB : 1;
  vbittype HtrnHvilOpen_B_Actl : 1;
  vbittype HtrnHvilOpen_B_Actl_UB : 1;
  vbittype unused0 : 5;
} _c_GWM_SendSignals_14_HS4_msgType;
typedef struct _c_IPC_Send_Signals_2_HS4_msgTypeTag
{
  vbittype ElLongTerm_L_Dsply_2 : 8;
  vbittype ElLongTerm_L_Dsply_1 : 8;
  vbittype ElLongTerm_L_Dsply_0 : 8;
  vbittype ElTrip_L_Dsply_1 : 8;
  vbittype ElTrip_L_Dsply_0 : 8;
  vbittype DsplyChkActv_B_Stat : 1;
  vbittype unused0 : 1;
  vbittype FuelRange_L_Dsply_1 : 6;
  vbittype FuelRange_L_Dsply_0 : 8;
} _c_IPC_Send_Signals_2_HS4_msgType;
typedef struct _c_TCU_ChrgLoc_Signals_2_msgTypeTag
{
  vbittype ChrgLocChrgPwr_Pw_Actl : 8;
  vbittype unused0 : 6;
  vbittype ChrgLocIrupt_D_Actl : 2;
  vbittype ChargePortPwr_St : 2;
  vbittype unused1 : 6;
  vbittype unused2 : 4;
  vbittype ChrgLocSchedCat_D_Actl : 4;
  vbittype ChargeProfIDPref_St : 2;
  vbittype ChrgLocStrtMin_No_Actl : 6;
  vbittype unused3 : 3;
  vbittype ChrgLocStrtHr_No_Actl : 5;
  vbittype ChrgLocProgram_D_Actl : 3;
  vbittype ChrgLocEndHr_No_Actl : 5;
  vbittype ChrgGlobSched_D_Actl : 2;
  vbittype ChrgLocEndMin_No_Actl : 6;
} _c_TCU_ChrgLoc_Signals_2_msgType;
typedef struct _c_TCU_ChrgLoc_Signals_1_msgTypeTag
{
  vbittype ChrgLocLatMin_No_Actl : 6;
  vbittype ChrgLocLongMin_No_Actl_1 : 2;
  vbittype ChrgLocLongMin_No_Actl_0 : 4;
  vbittype ChrgLocLatDeg_No_Actl_1 : 4;
  vbittype ChrgLocLatDeg_No_Actl_0 : 4;
  vbittype ChrgLocID_No_Actl : 4;
  vbittype ChrgLocLongDeg_No_Actl_1 : 8;
  vbittype ChrgLocLongDeg_No_Actl_0 : 1;
  vbittype ChrgLocHsphs_D_Actl : 3;
  vbittype ChrgLocLongMinDNo_Actl_2 : 4;
  vbittype ChrgLocLongMinDNo_Actl_1 : 8;
  vbittype ChrgLocLongMinDNo_Actl_0 : 2;
  vbittype ChrgLocLatMinD_No_Actl_1 : 6;
  vbittype ChrgLocLatMinD_No_Actl_0 : 8;
} _c_TCU_ChrgLoc_Signals_1_msgType;
typedef struct _c_Cluster_HEV_Data4_HS4_msgTypeTag
{
  vbittype unused0 : 5;
  vbittype BattChrgTrgtLPt_T_Est_1 : 3;
  vbittype BattChrgTrgtLPt_T_Est_0 : 8;
  vbittype unused1 : 5;
  vbittype BattChrgTrgSocPt_T_Est_1 : 3;
  vbittype BattChrgTrgSocPt_T_Est_0 : 8;
  vbittype unused2 : 2;
  vbittype DrvEffLvlIncDec_D_Cmd : 2;
  vbittype unused3 : 1;
  vbittype BattChrgCmpltPt_T_Est_1 : 3;
  vbittype BattChrgCmpltPt_T_Est_0 : 8;
  vbittype BattElecPerf_D_Actl : 3;
  vbittype unused4 : 5;
} _c_Cluster_HEV_Data4_HS4_msgType;
typedef struct _c_Upfitter_Data_HS4_msgTypeTag
{
  vbittype UpftrDgtlIn01_D_Stat : 2;
  vbittype UpftrDgtlIn02_D_Stat : 2;
  vbittype UpftrDgtlIn03_D_Stat : 2;
  vbittype UpftrDgtlIn04_D_Stat : 2;
  vbittype UpftrDgtlIn05_D_Stat : 2;
  vbittype UpftrDgtlIn06_D_Stat : 2;
  vbittype UpftrDgtlIn07_D_Stat : 2;
  vbittype UpftrDgtlIn08_D_Stat : 2;
  vbittype UpftrDgtlIn09_D_Stat : 2;
  vbittype UpftrDgtlOutHi01_D_Stat : 2;
  vbittype UpftrDgtlOutHi02_D_Stat : 2;
  vbittype UpftrDgtlOutHi03_D_Stat : 2;
  vbittype UpftrDgtlOutHi04_D_Stat : 2;
  vbittype UpftrDgtlOutHi05_D_Stat : 2;
  vbittype UpftrDgtlOutHi06_D_Stat : 2;
  vbittype UpftrDgtlOutHi07_D_Stat : 2;
  vbittype UpftrDgtlOutHi08_D_Stat : 2;
  vbittype UpftrDgtlOutLo01_D_Stat : 2;
  vbittype UpftrDgtlOutLo02_D_Stat : 2;
  vbittype UpftrDgtlOutLo03_D_Stat : 2;
  vbittype UpftrDgtlOutLo04_D_Stat : 2;
  vbittype UpftrDgtlOutLo05_D_Stat : 2;
  vbittype UpftrDgtlOutLo06_D_Stat : 2;
  vbittype UpftrDgtlOutLo07_D_Stat : 2;
  vbittype UpftrAnlgIn1_U_Actl_1 : 8;
  vbittype UpftrAnlgIn1_U_Actl_0 : 2;
  vbittype UpftrAnlgIn1_B_Valid : 1;
  vbittype unused0 : 5;
} _c_Upfitter_Data_HS4_msgType;
typedef struct _c_PreCond_Hev_Data1_HS4_msgTypeTag
{
  vbittype TripSumDrvE_Pc_Dsply_1 : 8;
  vbittype TripSumDrvE_Pc_Dsply_0 : 2;
  vbittype TripClimE_Pc_Dsply_1 : 6;
  vbittype TripClimE_Pc_Dsply_0 : 4;
  vbittype TripBattULoE_Pc_Dsply_1 : 4;
  vbittype TripBattULoE_Pc_Dsply_0 : 6;
  vbittype TripExtFctrE_Pc_Dsply_1 : 2;
  vbittype TripExtFctrE_Pc_Dsply_0 : 8;
} _c_PreCond_Hev_Data1_HS4_msgType;
typedef struct _c_HEV_ChargeStat_HS4_msgTypeTag
{
  vbittype NxtUsgSocEst_Pc_Dsply : 8;
  vbittype unused0 : 4;
  vbittype VehElRngeNut_L_Dsply_1 : 4;
  vbittype VehElRngeNut_L_Dsply_0 : 8;
  vbittype ChargeNowDuration_St : 8;
  vbittype EstmChrgTimeLP_St : 8;
  vbittype EstmChrgTimeHP_St : 8;
} _c_HEV_ChargeStat_HS4_msgType;
typedef struct _c_MtrTracData_1_HS4_msgTypeTag
{
  vbittype MtrTrac2_I_Actl_1 : 8;
  vbittype MtrTrac2_I_Actl_0 : 8;
  vbittype MtrTrac2Coil_Te_Actl : 8;
  vbittype MtrTrac2Inv_Te_Actl : 8;
  vbittype MtrTrac2_U_Actl_1 : 8;
  vbittype MtrTrac2_U_Actl_0 : 2;
  vbittype Mtr2Aout_W_ActlMntr_1 : 6;
  vbittype Mtr2Aout_W_ActlMntr_0 : 4;
  vbittype Mtr2CntlTeAlrm_B_Stat : 1;
  vbittype MtrTrac2Falt_B_Stat : 1;
  vbittype MtrTrac2TeAlrm_B_Stat : 1;
  vbittype unused0 : 1;
  vbittype Inv1_Te_Actl : 8;
} _c_MtrTracData_1_HS4_msgType;
typedef struct _c_IPC_TripData_1_HS4_msgTypeTag
{
  vbittype unused0 : 6;
  vbittype TripSum_Vl_Dsply_1 : 2;
  vbittype TripSum_Vl_Dsply_0 : 8;
  vbittype unused1 : 3;
  vbittype VehElSurpStat_L_Dsply_1 : 5;
  vbittype VehElSurpStat_L_Dsply_0 : 8;
  vbittype TripSum_L_Dsply_1 : 8;
  vbittype TripSum_L_Dsply_0 : 8;
  vbittype unused2 : 7;
  vbittype TripSum_E_Dsply_1 : 1;
  vbittype TripSum_E_Dsply_0 : 8;
} _c_IPC_TripData_1_HS4_msgType;
typedef struct _c_IPC_Consumption_HS4_msgTypeTag
{
  vbittype unused0 : 5;
  vbittype ConsRelTrgtOn_B_Dsply : 1;
  vbittype unused1 : 2;
  vbittype unused2 : 8;
  vbittype unused3 : 6;
  vbittype ConsInstThres_Pc_Dsply_1 : 2;
  vbittype ConsInstThres_Pc_Dsply_0 : 8;
  vbittype unused4 : 4;
  vbittype ConsAvgTrip_No_Dsply_1 : 4;
  vbittype ConsAvgTrip_No_Dsply_0 : 8;
  vbittype ConsUnitIPC_D_Dsply : 4;
  vbittype ConsLongTerm_No_Dsply_1 : 4;
  vbittype ConsLongTerm_No_Dsply_0 : 8;
} _c_IPC_Consumption_HS4_msgType;
typedef struct _c_Cluster_HEV_Data9_HS4_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 2;
  vbittype MtrTrac2_Tq_Actl_1 : 6;
  vbittype MtrTrac2_Tq_Actl_0 : 6;
  vbittype unused4 : 2;
  vbittype unused5 : 1;
  vbittype ChrgLocID_No_Rq : 7;
  vbittype ChrgLocGPS_D_Rq : 2;
  vbittype NtfctnConflict1_D_Rq : 3;
  vbittype unused6 : 1;
  vbittype NxtUsg_D_Rq : 2;
  vbittype PreCondID_No_Rq : 4;
  vbittype PtRmtRprt_D_Rq : 4;
} _c_Cluster_HEV_Data9_HS4_msgType;
typedef struct _c_Cluster_HEV_Data1_HS4_msgTypeTag
{
  vbittype unused0 : 4;
  vbittype VehElRngeCyc_L_Dsply_1 : 4;
  vbittype VehElRngeCyc_L_Dsply_0 : 8;
  vbittype PtDataKeyId_D_Stat : 4;
  vbittype unused1 : 4;
  vbittype unused2 : 8;
  vbittype unused3 : 3;
  vbittype ChrgStat_D_Dsply : 3;
  vbittype RgenTrip_Pc_Dsply_1 : 2;
  vbittype RgenTrip_Pc_Dsply_0 : 8;
  vbittype RgenTrip_L_Dsply_1 : 8;
  vbittype RgenTrip_L_Dsply_0 : 8;
} _c_Cluster_HEV_Data1_HS4_msgType;
typedef struct _c_Cluster_HEV_Data7_HS4_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 3;
  vbittype PreCondStat_D_Dsply : 3;
  vbittype RgenEvntLvl_Pc_Dsply_1 : 2;
  vbittype RgenEvntLvl_Pc_Dsply_0 : 8;
  vbittype BrkEvntComplt_B_Dsply : 1;
  vbittype unused2 : 5;
  vbittype RgenLongTerm_Pc_Dsply_1 : 2;
  vbittype RgenLongTerm_Pc_Dsply_0 : 8;
  vbittype RgenLongTerm_L_Dsply_2 : 8;
  vbittype RgenLongTerm_L_Dsply_1 : 8;
  vbittype RgenLongTerm_L_Dsply_0 : 8;
} _c_Cluster_HEV_Data7_HS4_msgType;
typedef struct _c_GWM_HPCM_i_FrP11_HS4_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 5;
  vbittype BattChrgTrgtLMax_T_Est_1 : 3;
  vbittype BattChrgTrgtLMax_T_Est_0 : 8;
  vbittype unused2 : 2;
  vbittype ActChrgStrtMin_No_Actl : 6;
  vbittype unused3 : 3;
  vbittype ActChrgStrtHr_No_Actl : 5;
  vbittype unused4 : 3;
  vbittype ActChrgStrtDay_No_Actl : 5;
  vbittype unused5 : 4;
  vbittype ActChrgStrMnth_No_Actl : 4;
  vbittype unused6 : 3;
  vbittype ActChrgStrtYr_No_Actl : 5;
} _c_GWM_HPCM_i_FrP11_HS4_msgType;
typedef struct _c_GWM_HPCM_i_FrP10_HS4_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 5;
  vbittype BattChrgTrgtLMin_T_Est_1 : 3;
  vbittype BattChrgTrgtLMin_T_Est_0 : 8;
  vbittype unused2 : 2;
  vbittype ActChrgEndMin_No_Actl : 6;
  vbittype unused3 : 3;
  vbittype ActChrgEndHr_No_Actl : 5;
  vbittype unused4 : 3;
  vbittype ActChrgEndDay_No_Actl : 5;
  vbittype unused5 : 4;
  vbittype ActChrgEndMnth_No_Actl : 4;
  vbittype unused6 : 3;
  vbittype ActChrgEndYr_No_Actl : 5;
} _c_GWM_HPCM_i_FrP10_HS4_msgType;
typedef struct _c_BattTrac_Data1_HS4_msgTypeTag
{
  vbittype BattTracInsltn_R_Actl : 8;
  vbittype BattTracMnCell_Te_Actl : 8;
  vbittype BattTracMxCell_Te_Actl : 8;
  vbittype BattTracCell_U_Mn_1 : 8;
  vbittype BattTracCell_U_Mn_0 : 6;
  vbittype BattTracEq_B_Actl : 1;
  vbittype BattTracInsAlrm_B_Stat : 1;
  vbittype BattTracCell_U_Mx_1 : 8;
  vbittype BattTracCell_U_Mx_0 : 6;
  vbittype BattTracTeMn_B_Stat : 1;
  vbittype BattTracTeMx_B_Stat : 1;
  vbittype BattTracUAlrm_B_Stat : 1;
  vbittype BattTracUMn_B_Stat : 1;
  vbittype BattTracUMx_B_Stat : 1;
  vbittype unused0 : 5;
} _c_BattTrac_Data1_HS4_msgType;
typedef struct _c_Battery_Traction_1_HS4_msgTypeTag
{
  vbittype BattTracCnnct_B_Cmd : 1;
  vbittype BattTrac_I_Actl_1 : 7;
  vbittype BattTrac_I_Actl_0 : 8;
  vbittype VehStrtInhbt_B_RqBatt : 1;
  vbittype BattTracOffFst_D_Actl : 2;
  vbittype BattTracOff_B_Actl : 1;
  vbittype BattTracMil_D_Rq : 2;
  vbittype BattTrac_U_Actl_1 : 2;
  vbittype BattTrac_U_Actl_0 : 8;
  vbittype BattTrac_U_LimHi : 8;
  vbittype BattTrac_U_LimLo : 8;
} _c_Battery_Traction_1_HS4_msgType;
typedef struct _c_TCU_Send_Signals_2_msgTypeTag
{
  vbittype unused0 : 3;
  vbittype WeekdayEndHR_St : 5;
  vbittype unused1 : 3;
  vbittype WeekdayStartHR_St : 5;
  vbittype unused2 : 2;
  vbittype WeekdayStartMin_St : 6;
  vbittype unused3 : 2;
  vbittype WeekdayEndMin_St : 6;
  vbittype unused4 : 2;
  vbittype WeekendEndMin_St : 6;
  vbittype unused5 : 3;
  vbittype WeekendEndHR_St : 5;
  vbittype unused6 : 2;
  vbittype WeekendStartMin_St : 6;
  vbittype unused7 : 3;
  vbittype WeekendStartHR_St : 5;
} _c_TCU_Send_Signals_2_msgType;
typedef struct _c_TCU_Precond_Signals_1_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 4;
  vbittype PreCondModeSet_D_Actl : 4;
  vbittype unused5 : 3;
  vbittype PreCondTeSet_Te_Actl : 5;
  vbittype unused6 : 2;
  vbittype PreCondTPRDef_D_Actl : 2;
  vbittype PreCondID_No_Actl : 4;
  vbittype PreCondRecrcSet_D_Actl : 2;
  vbittype PreCondFanSet_D_Actl : 4;
  vbittype PreCondACSet_D_Actl : 2;
} _c_TCU_Precond_Signals_1_msgType;
typedef struct _c_GWM_SendSignals_16_HS4_msgTypeTag
{
  vbittype BattTracSoc2_Pc_Actl_1 : 8;
  vbittype BattTracSoc2_Pc_Actl_0 : 6;
  vbittype BattTracSoc2_Pc_Actl_UB : 1;
  vbittype BattTrac2_E_Avail_UB : 1;
  vbittype BattTrac2_E_Avail_1 : 8;
  vbittype BattTrac2_E_Avail_0 : 4;
  vbittype unused0 : 4;
} _c_GWM_SendSignals_16_HS4_msgType;
typedef struct _c_MtrTrac_Data2_HS4_msgTypeTag
{
  vbittype Inv1Ain_I_ActlMntr_1 : 8;
  vbittype Inv1Ain_I_ActlMntr_0 : 7;
  vbittype unused0 : 1;
  vbittype ChrgStat_D_ActlMntr : 3;
  vbittype HybVehMde_D_ActlMntr : 3;
  vbittype unused1 : 2;
  vbittype Mtr2State_D_ActlMntr : 3;
  vbittype VehElRnge_L_Dsply_1 : 5;
  vbittype VehElRnge_L_Dsply_0 : 7;
  vbittype unused2 : 1;
} _c_MtrTrac_Data2_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_9_HS4_msgTypeTag
{
  vbittype BattTracCell41_U_Actl_1 : 8;
  vbittype BattTracCell41_U_Actl_0 : 4;
  vbittype BattTracCell42_U_Actl_1 : 4;
  vbittype BattTracCell42_U_Actl_0 : 8;
  vbittype BattTracCell43_U_Actl_1 : 8;
  vbittype BattTracCell43_U_Actl_0 : 4;
  vbittype BattTracCell44_U_Actl_1 : 4;
  vbittype BattTracCell44_U_Actl_0 : 8;
  vbittype BattTracCell45_U_Actl_1 : 8;
  vbittype BattTracCell45_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_9_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_8_HS4_msgTypeTag
{
  vbittype BattTracCell36_U_Actl_1 : 8;
  vbittype BattTracCell36_U_Actl_0 : 4;
  vbittype BattTracCell37_U_Actl_1 : 4;
  vbittype BattTracCell37_U_Actl_0 : 8;
  vbittype BattTracCell38_U_Actl_1 : 8;
  vbittype BattTracCell38_U_Actl_0 : 4;
  vbittype BattTracCell39_U_Actl_1 : 4;
  vbittype BattTracCell39_U_Actl_0 : 8;
  vbittype BattTracCell40_U_Actl_1 : 8;
  vbittype BattTracCell40_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_8_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_7_HS4_msgTypeTag
{
  vbittype BattTracCell31_U_Actl_1 : 8;
  vbittype BattTracCell31_U_Actl_0 : 4;
  vbittype BattTracCell32_U_Actl_1 : 4;
  vbittype BattTracCell32_U_Actl_0 : 8;
  vbittype BattTracCell33_U_Actl_1 : 8;
  vbittype BattTracCell33_U_Actl_0 : 4;
  vbittype BattTracCell34_U_Actl_1 : 4;
  vbittype BattTracCell34_U_Actl_0 : 8;
  vbittype BattTracCell35_U_Actl_1 : 8;
  vbittype BattTracCell35_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_7_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_6_HS4_msgTypeTag
{
  vbittype BattTracCell26_U_Actl_1 : 8;
  vbittype BattTracCell26_U_Actl_0 : 4;
  vbittype BattTracCell27_U_Actl_1 : 4;
  vbittype BattTracCell27_U_Actl_0 : 8;
  vbittype BattTracCell28_U_Actl_1 : 8;
  vbittype BattTracCell28_U_Actl_0 : 4;
  vbittype BattTracCell29_U_Actl_1 : 4;
  vbittype BattTracCell29_U_Actl_0 : 8;
  vbittype BattTracCell30_U_Actl_1 : 8;
  vbittype BattTracCell30_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_6_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_5_HS4_msgTypeTag
{
  vbittype BattTracCell21_U_Actl_1 : 8;
  vbittype BattTracCell21_U_Actl_0 : 4;
  vbittype BattTracCell22_U_Actl_1 : 4;
  vbittype BattTracCell22_U_Actl_0 : 8;
  vbittype BattTracCell23_U_Actl_1 : 8;
  vbittype BattTracCell23_U_Actl_0 : 4;
  vbittype BattTracCell24_U_Actl_1 : 4;
  vbittype BattTracCell24_U_Actl_0 : 8;
  vbittype BattTracCell25_U_Actl_1 : 8;
  vbittype BattTracCell25_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_5_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_4_HS4_msgTypeTag
{
  vbittype BattTracCell16_U_Actl_1 : 8;
  vbittype BattTracCell16_U_Actl_0 : 4;
  vbittype BattTracCell17_U_Actl_1 : 4;
  vbittype BattTracCell17_U_Actl_0 : 8;
  vbittype BattTracCell18_U_Actl_1 : 8;
  vbittype BattTracCell18_U_Actl_0 : 4;
  vbittype BattTracCell19_U_Actl_1 : 4;
  vbittype BattTracCell19_U_Actl_0 : 8;
  vbittype BattTracCell20_U_Actl_1 : 8;
  vbittype BattTracCell20_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_4_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_3_HS4_msgTypeTag
{
  vbittype BattTracCell11_U_Actl_1 : 8;
  vbittype BattTracCell11_U_Actl_0 : 4;
  vbittype BattTracCell12_U_Actl_1 : 4;
  vbittype BattTracCell12_U_Actl_0 : 8;
  vbittype BattTracCell13_U_Actl_1 : 8;
  vbittype BattTracCell13_U_Actl_0 : 4;
  vbittype BattTracCell14_U_Actl_1 : 4;
  vbittype BattTracCell14_U_Actl_0 : 8;
  vbittype BattTracCell15_U_Actl_1 : 8;
  vbittype BattTracCell15_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_3_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_2_HS4_msgTypeTag
{
  vbittype BattTracCell06_U_Actl_1 : 8;
  vbittype BattTracCell06_U_Actl_0 : 4;
  vbittype BattTracCell07_U_Actl_1 : 4;
  vbittype BattTracCell07_U_Actl_0 : 8;
  vbittype BattTracCell08_U_Actl_1 : 8;
  vbittype BattTracCell08_U_Actl_0 : 4;
  vbittype BattTracCell09_U_Actl_1 : 4;
  vbittype BattTracCell09_U_Actl_0 : 8;
  vbittype BattTracCell10_U_Actl_1 : 8;
  vbittype BattTracCell10_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_2_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_23_HS4_msgTypeTag
{
  vbittype BattTracTe14_Te_Actl : 8;
  vbittype BattTracTe15_Te_Actl : 8;
  vbittype BattTracTe16_Te_Actl : 8;
  vbittype BattTracTe17_Te_Actl : 8;
  vbittype BattTracTe18_Te_Actl : 8;
  vbittype BattTracTe19_Te_Actl : 8;
} _c_HEV_Data_Monitor_23_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_22_HS4_msgTypeTag
{
  vbittype BattTracCellCnt_No_Actl : 8;
  vbittype BattTracCellUMn_No_Actl : 8;
  vbittype BattTracTeCnt_No_Actl : 8;
  vbittype BattTracTeMn_No_Actl : 8;
  vbittype BattTracTeMx_No_Actl : 8;
  vbittype BattChrgIsltn_B_Falt : 1;
  vbittype BattChrgSocErrtc_B_Falt : 1;
  vbittype BattChrgSocMn_B_Falt : 1;
  vbittype BattChrgSocMx_B_Falt : 1;
  vbittype BattTracCellDiff_B_Falt : 1;
  vbittype BattTracSoftware_B_Falt : 1;
  vbittype BattTracTeDelta_B_Falt : 1;
  vbittype BattTracTeMx_B_Falt : 1;
  vbittype BattTracUMn_B_Falt : 1;
  vbittype BattTracUMx_B_Falt : 1;
  vbittype BattChrgUMx_B_Falt : 1;
  vbittype unused0 : 5;
  vbittype BattTracCellUMx_No_Actl : 8;
} _c_HEV_Data_Monitor_22_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_21_HS4_msgTypeTag
{
  vbittype BattTracTe07_Te_Actl : 8;
  vbittype BattTracTe08_Te_Actl : 8;
  vbittype BattTracTe09_Te_Actl : 8;
  vbittype BattTracTe10_Te_Actl : 8;
  vbittype BattTracTe11_Te_Actl : 8;
  vbittype BattTracTe12_Te_Actl : 8;
  vbittype BattTracTe13_Te_Actl : 8;
} _c_HEV_Data_Monitor_21_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_20_HS4_msgTypeTag
{
  vbittype BattTracCell96_U_Actl_1 : 8;
  vbittype BattTracCell96_U_Actl_0 : 4;
  vbittype unused0 : 4;
  vbittype BattTracTe01_Te_Actl : 8;
  vbittype BattTracTe02_Te_Actl : 8;
  vbittype BattTracTe03_Te_Actl : 8;
  vbittype BattTracTe04_Te_Actl : 8;
  vbittype BattTracTe05_Te_Actl : 8;
  vbittype BattTracTe06_Te_Actl : 8;
} _c_HEV_Data_Monitor_20_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_1_HS4_msgTypeTag
{
  vbittype BattTracCell01_U_Actl_1 : 8;
  vbittype BattTracCell01_U_Actl_0 : 4;
  vbittype BattTracCell02_U_Actl_1 : 4;
  vbittype BattTracCell02_U_Actl_0 : 8;
  vbittype BattTracCell03_U_Actl_1 : 8;
  vbittype BattTracCell03_U_Actl_0 : 4;
  vbittype BattTracCell04_U_Actl_1 : 4;
  vbittype BattTracCell04_U_Actl_0 : 8;
  vbittype BattTracCell05_U_Actl_1 : 8;
  vbittype BattTracCell05_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_1_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_19_HS4_msgTypeTag
{
  vbittype BattTracCell91_U_Actl_1 : 8;
  vbittype BattTracCell91_U_Actl_0 : 4;
  vbittype BattTracCell92_U_Actl_1 : 4;
  vbittype BattTracCell92_U_Actl_0 : 8;
  vbittype BattTracCell93_U_Actl_1 : 8;
  vbittype BattTracCell93_U_Actl_0 : 4;
  vbittype BattTracCell94_U_Actl_1 : 4;
  vbittype BattTracCell94_U_Actl_0 : 8;
  vbittype BattTracCell95_U_Actl_1 : 8;
  vbittype BattTracCell95_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_19_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_18_HS4_msgTypeTag
{
  vbittype BattTracCell86_U_Actl_1 : 8;
  vbittype BattTracCell86_U_Actl_0 : 4;
  vbittype BattTracCell87_U_Actl_1 : 4;
  vbittype BattTracCell87_U_Actl_0 : 8;
  vbittype BattTracCell88_U_Actl_1 : 8;
  vbittype BattTracCell88_U_Actl_0 : 4;
  vbittype BattTracCell89_U_Actl_1 : 4;
  vbittype BattTracCell89_U_Actl_0 : 8;
  vbittype BattTracCell90_U_Actl_1 : 8;
  vbittype BattTracCell90_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_18_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_17_HS4_msgTypeTag
{
  vbittype BattTracCell81_U_Actl_1 : 8;
  vbittype BattTracCell81_U_Actl_0 : 4;
  vbittype BattTracCell82_U_Actl_1 : 4;
  vbittype BattTracCell82_U_Actl_0 : 8;
  vbittype BattTracCell83_U_Actl_1 : 8;
  vbittype BattTracCell83_U_Actl_0 : 4;
  vbittype BattTracCell84_U_Actl_1 : 4;
  vbittype BattTracCell84_U_Actl_0 : 8;
  vbittype BattTracCell85_U_Actl_1 : 8;
  vbittype BattTracCell85_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_17_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_16_HS4_msgTypeTag
{
  vbittype BattTracCell76_U_Actl_1 : 8;
  vbittype BattTracCell76_U_Actl_0 : 4;
  vbittype BattTracCell77_U_Actl_1 : 4;
  vbittype BattTracCell77_U_Actl_0 : 8;
  vbittype BattTracCell78_U_Actl_1 : 8;
  vbittype BattTracCell78_U_Actl_0 : 4;
  vbittype BattTracCell79_U_Actl_1 : 4;
  vbittype BattTracCell79_U_Actl_0 : 8;
  vbittype BattTracCell80_U_Actl_1 : 8;
  vbittype BattTracCell80_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_16_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_15_HS4_msgTypeTag
{
  vbittype BattTracCell71_U_Actl_1 : 8;
  vbittype BattTracCell71_U_Actl_0 : 4;
  vbittype BattTracCell72_U_Actl_1 : 4;
  vbittype BattTracCell72_U_Actl_0 : 8;
  vbittype BattTracCell73_U_Actl_1 : 8;
  vbittype BattTracCell73_U_Actl_0 : 4;
  vbittype BattTracCell74_U_Actl_1 : 4;
  vbittype BattTracCell74_U_Actl_0 : 8;
  vbittype BattTracCell75_U_Actl_1 : 8;
  vbittype BattTracCell75_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_15_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_14_HS4_msgTypeTag
{
  vbittype BattTracCell66_U_Actl_1 : 8;
  vbittype BattTracCell66_U_Actl_0 : 4;
  vbittype BattTracCell67_U_Actl_1 : 4;
  vbittype BattTracCell67_U_Actl_0 : 8;
  vbittype BattTracCell68_U_Actl_1 : 8;
  vbittype BattTracCell68_U_Actl_0 : 4;
  vbittype BattTracCell69_U_Actl_1 : 4;
  vbittype BattTracCell69_U_Actl_0 : 8;
  vbittype BattTracCell70_U_Actl_1 : 8;
  vbittype BattTracCell70_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_14_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_13_HS4_msgTypeTag
{
  vbittype BattTracCell61_U_Actl_1 : 8;
  vbittype BattTracCell61_U_Actl_0 : 4;
  vbittype BattTracCell62_U_Actl_1 : 4;
  vbittype BattTracCell62_U_Actl_0 : 8;
  vbittype BattTracCell63_U_Actl_1 : 8;
  vbittype BattTracCell63_U_Actl_0 : 4;
  vbittype BattTracCell64_U_Actl_1 : 4;
  vbittype BattTracCell64_U_Actl_0 : 8;
  vbittype BattTracCell65_U_Actl_1 : 8;
  vbittype BattTracCell65_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_13_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_12_HS4_msgTypeTag
{
  vbittype BattTracCell56_U_Actl_1 : 8;
  vbittype BattTracCell56_U_Actl_0 : 4;
  vbittype BattTracCell57_U_Actl_1 : 4;
  vbittype BattTracCell57_U_Actl_0 : 8;
  vbittype BattTracCell58_U_Actl_1 : 8;
  vbittype BattTracCell58_U_Actl_0 : 4;
  vbittype BattTracCell59_U_Actl_1 : 4;
  vbittype BattTracCell59_U_Actl_0 : 8;
  vbittype BattTracCell60_U_Actl_1 : 8;
  vbittype BattTracCell60_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_12_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_11_HS4_msgTypeTag
{
  vbittype BattTracCell51_U_Actl_1 : 8;
  vbittype BattTracCell51_U_Actl_0 : 4;
  vbittype BattTracCell52_U_Actl_1 : 4;
  vbittype BattTracCell52_U_Actl_0 : 8;
  vbittype BattTracCell53_U_Actl_1 : 8;
  vbittype BattTracCell53_U_Actl_0 : 4;
  vbittype BattTracCell54_U_Actl_1 : 4;
  vbittype BattTracCell54_U_Actl_0 : 8;
  vbittype BattTracCell55_U_Actl_1 : 8;
  vbittype BattTracCell55_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_11_HS4_msgType;
typedef struct _c_HEV_Data_Monitor_10_HS4_msgTypeTag
{
  vbittype BattTracCell46_U_Actl_1 : 8;
  vbittype BattTracCell46_U_Actl_0 : 4;
  vbittype BattTracCell47_U_Actl_1 : 4;
  vbittype BattTracCell47_U_Actl_0 : 8;
  vbittype BattTracCell48_U_Actl_1 : 8;
  vbittype BattTracCell48_U_Actl_0 : 4;
  vbittype BattTracCell49_U_Actl_1 : 4;
  vbittype BattTracCell49_U_Actl_0 : 8;
  vbittype BattTracCell50_U_Actl_1 : 8;
  vbittype BattTracCell50_U_Actl_0 : 4;
  vbittype unused0 : 4;
} _c_HEV_Data_Monitor_10_HS4_msgType;
typedef struct _c_TCU_RFA_WORD_Tx_HS4_msgTypeTag
{
  vbittype TCU_RFA_Word_Tx_7 : 8;
  vbittype TCU_RFA_Word_Tx_6 : 8;
  vbittype TCU_RFA_Word_Tx_5 : 8;
  vbittype TCU_RFA_Word_Tx_4 : 8;
  vbittype TCU_RFA_Word_Tx_3 : 8;
  vbittype TCU_RFA_Word_Tx_2 : 8;
  vbittype TCU_RFA_Word_Tx_1 : 8;
  vbittype TCU_RFA_Word_Tx_0 : 8;
} _c_TCU_RFA_WORD_Tx_HS4_msgType;
typedef struct _c_RFA_TCU_WORD_Tx_msgTypeTag
{
  vbittype RFA_TCU_Word_Tx_7 : 8;
  vbittype RFA_TCU_Word_Tx_6 : 8;
  vbittype RFA_TCU_Word_Tx_5 : 8;
  vbittype RFA_TCU_Word_Tx_4 : 8;
  vbittype RFA_TCU_Word_Tx_3 : 8;
  vbittype RFA_TCU_Word_Tx_2 : 8;
  vbittype RFA_TCU_Word_Tx_1 : 8;
  vbittype RFA_TCU_Word_Tx_0 : 8;
} _c_RFA_TCU_WORD_Tx_msgType;
typedef struct _c_PaakCtlData5_msgTypeTag
{
  vbittype ModemAuthrz_B_Stat : 2;
  vbittype PaakSerial_D_Rq : 2;
  vbittype PaakWakeupActv_B_Rq : 1;
  vbittype unused0 : 3;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
  vbittype unused7 : 8;
} _c_PaakCtlData5_msgType;
typedef struct _c_TCU_Request_Signals_4_msgTypeTag
{
  vbittype OfbChrgLocIdTrgt_No_Rq : 4;
  vbittype OfbChrgLocIdUns_B_Rq : 1;
  vbittype OfbChrgPrflUpdate_B_Rq : 1;
  vbittype OfbChrgSetDelete_B_Rq : 1;
  vbittype unused0 : 1;
  vbittype OfbChrgPrflWkdy_No_Rq_2 : 8;
  vbittype OfbChrgPrflWkdy_No_Rq_1 : 8;
  vbittype OfbChrgPrflWkdy_No_Rq_0 : 8;
  vbittype OfbChrgPrflWknd_No_Rq_2 : 8;
  vbittype OfbChrgPrflWknd_No_Rq_1 : 8;
  vbittype OfbChrgPrflWknd_No_Rq_0 : 8;
  vbittype OfbChrgSetNow_D_Rq : 2;
  vbittype OfbChrgToPcWkdy_D_Actl : 3;
  vbittype OfbChrgToPcWknd_D_Actl : 3;
} _c_TCU_Request_Signals_4_msgType;
typedef struct _c_TCU_Send_Signals_6_msgTypeTag
{
  vbittype OfbChrgClearAll_B_Rq : 1;
  vbittype OfbChrgGoTDelete_B_Rq : 1;
  vbittype OfbChrgGoTElement_D_Rq : 4;
  vbittype OfbChrgGoTExtHtr_D_Rq : 2;
  vbittype OfbChrgGoTHr_T_Rq : 5;
  vbittype OfbChrgGoTOn_D_Rq : 2;
  vbittype OfbChrgGoTUpdate_B_Rq : 1;
  vbittype OfbChrgGoTMnte_D_Rq : 4;
  vbittype OfbChrgGoTPrcond_D_Rq : 2;
  vbittype OfbChrgGoTTouch_D_Rq : 2;
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
} _c_TCU_Send_Signals_6_msgType;
typedef struct _c_ChargeSettings_HS4_msgTypeTag
{
  vbittype ChrgPrflWkdy_No_Actl_2 : 8;
  vbittype ChrgPrflWkdy_No_Actl_1 : 8;
  vbittype ChrgPrflWkdy_No_Actl_0 : 8;
  vbittype ChrgPrflWknd_No_Actl_2 : 8;
  vbittype ChrgPrflWknd_No_Actl_1 : 8;
  vbittype ChrgPrflWknd_No_Actl_0 : 8;
  vbittype ChrgLocIdCurnt_D_Sav : 4;
  vbittype ChrgProgIdSaved_D_Stat : 4;
  vbittype ChrgToPcWkdySav_D_Stat : 3;
  vbittype ChrgToPcWkndSav_D_Stat : 3;
  vbittype ChrgLocIdUnsAck_B_Stat : 1;
  vbittype ChrgNowEnbl_B_Saved : 1;
} _c_ChargeSettings_HS4_msgType;
typedef struct _c_Saved_Charge_Locat_HS4_msgTypeTag
{
  vbittype ChrgLocLattFrct_An_Sav_2 : 8;
  vbittype ChrgLocLattFrct_An_Sav_1 : 8;
  vbittype ChrgLocLattFrct_An_Sav_0 : 4;
  vbittype ChrgLocId_D_Sav : 4;
  vbittype ChrgLocLattDeg_An_Sav : 7;
  vbittype ChrgLocLattPostv_B_Sav : 1;
  vbittype ChrgLocLongDeg_An_Sav : 8;
  vbittype ChrgLocLongFrct_An_Sav_2 : 8;
  vbittype ChrgLocLongFrct_An_Sav_1 : 8;
  vbittype ChrgLocLongFrct_An_Sav_0 : 4;
  vbittype ChrgLocLongPostv_B_Sav : 1;
  vbittype unused0 : 3;
} _c_Saved_Charge_Locat_HS4_msgType;
typedef struct _c_Unsaved_Charge_Locat_HS4_msgTypeTag
{
  vbittype ChrgLocLattFrct_An_Uns_2 : 8;
  vbittype ChrgLocLattFrct_An_Uns_1 : 8;
  vbittype ChrgLocLattFrct_An_Uns_0 : 4;
  vbittype ChrgLocId_D_Uns : 4;
  vbittype ChrgLocLattDeg_An_Uns : 7;
  vbittype ChrgLocLattPostv_B_Uns : 1;
  vbittype ChrgLocLongDeg_An_Uns : 8;
  vbittype ChrgLocLongFrct_An_Uns_2 : 8;
  vbittype ChrgLocLongFrct_An_Uns_1 : 8;
  vbittype ChrgLocLongFrct_An_Uns_0 : 4;
  vbittype ChrgLocLongPostv_B_Uns : 1;
  vbittype unused0 : 3;
} _c_Unsaved_Charge_Locat_HS4_msgType;
typedef struct _c_GWM_SendSignals_13_HS4_msgTypeTag
{
  vbittype ChrgGoTElement_D_Stat : 4;
  vbittype ChrgGoTExtHtr_B_Stat : 1;
  vbittype ChrgGoTAllOn_B_Stat_UB : 1;
  vbittype ChrgGoTElement_D_Stat_UB : 1;
  vbittype ChrgGoTTouch_B_Stat : 1;
  vbittype ChrgGoTHr_T_Stat : 5;
  vbittype ChrgGoTPrcond_D_Stat : 2;
  vbittype ChrgGoTExtHtr_B_Stat_UB : 1;
  vbittype ChrgGoTMnte_D_Stat : 4;
  vbittype ChrgGoTNext_D_Stat : 4;
  vbittype ChrgGoTHr_T_Stat_UB : 1;
  vbittype ChrgGoTMnte_D_Stat_UB : 1;
  vbittype ChrgGoTNext_D_Stat_UB : 1;
  vbittype ChrgGoTPrcond_D_Stat_UB : 1;
  vbittype ChrgGoTTouch_B_Stat_UB : 1;
  vbittype ChrgGoTAllOn_B_Stat : 1;
  vbittype OnbChrgPrflUpdate_B_Rq : 1;
  vbittype OnbChrgPrflUpdate_B_Rq_UB : 1;
} _c_GWM_SendSignals_13_HS4_msgType;


/* -----------------------------------------------------------------------------
    &&&~ Signal value names
 ----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
    &&&~ Message Unions
 ----------------------------------------------------------------------------- */

typedef union _c_GlobalClock_Data_HS4_bufTag
{
  vuint8 _c[7];
  _c_GlobalClock_Data_HS4_msgType GlobalClock_Data_HS4;
} _c_GlobalClock_Data_HS4_buf;
typedef union _c_APIM_Send_Signals_2_HS4_bufTag
{
  vuint8 _c[6];
  _c_APIM_Send_Signals_2_HS4_msgType APIM_Send_Signals_2_HS4;
} _c_APIM_Send_Signals_2_HS4_buf;
typedef union _c_TCU_Request_Signals_2_bufTag
{
  vuint8 _c[8];
  _c_TCU_Request_Signals_2_msgType TCU_Request_Signals_2;
} _c_TCU_Request_Signals_2_buf;
typedef union _c_GWM_SendSignals_05_HS4_bufTag
{
  vuint8 _c[8];
  _c_GWM_SendSignals_05_HS4_msgType GWM_SendSignals_05_HS4;
} _c_GWM_SendSignals_05_HS4_buf;
typedef union _c_TCU_Send_Signals_bufTag
{
  vuint8 _c[8];
  _c_TCU_Send_Signals_msgType TCU_Send_Signals;
} _c_TCU_Send_Signals_buf;
typedef union _c_TCU_AutoSar_Network_Mgmt_bufTag
{
  vuint8 _c[8];
  _c_TCU_AutoSar_Network_Mgmt_msgType TCU_AutoSar_Network_Mgmt;
} _c_TCU_AutoSar_Network_Mgmt_buf;
typedef union _c_GWM_SendSignals_08_HS4_bufTag
{
  vuint8 _c[4];
  _c_GWM_SendSignals_08_HS4_msgType GWM_SendSignals_08_HS4;
} _c_GWM_SendSignals_08_HS4_buf;
typedef union _c_GWM_SendSignals_07_HS4_bufTag
{
  vuint8 _c[3];
  _c_GWM_SendSignals_07_HS4_msgType GWM_SendSignals_07_HS4;
} _c_GWM_SendSignals_07_HS4_buf;
typedef union _c_ABS_Signals_HS4_bufTag
{
  vuint8 _c[8];
  _c_ABS_Signals_HS4_msgType ABS_Signals_HS4;
} _c_ABS_Signals_HS4_buf;
typedef union _c_GWM_SendSignals_09_HS4_bufTag
{
  vuint8 _c[8];
  _c_GWM_SendSignals_09_HS4_msgType GWM_SendSignals_09_HS4;
} _c_GWM_SendSignals_09_HS4_buf;
typedef union _c_GWM_SendSignals_04_HS4_bufTag
{
  vuint8 _c[8];
  _c_GWM_SendSignals_04_HS4_msgType GWM_SendSignals_04_HS4;
} _c_GWM_SendSignals_04_HS4_buf;
typedef union _c_GWM_SendSignals_03_HS4_bufTag
{
  vuint8 _c[8];
  _c_GWM_SendSignals_03_HS4_msgType GWM_SendSignals_03_HS4;
} _c_GWM_SendSignals_03_HS4_buf;
typedef union _c_GWM_SendSignals_02_HS4_bufTag
{
  vuint8 _c[8];
  _c_GWM_SendSignals_02_HS4_msgType GWM_SendSignals_02_HS4;
} _c_GWM_SendSignals_02_HS4_buf;
typedef union _c_APIM_TCU_Word_Rx_HS4_bufTag
{
  vuint8 _c[8];
  _c_APIM_TCU_Word_Rx_HS4_msgType APIM_TCU_Word_Rx_HS4;
} _c_APIM_TCU_Word_Rx_HS4_buf;
typedef union _c_TxDynamicMsg0_bufTag
{
  vuint8 _c[8];
} _c_TxDynamicMsg0_buf;
typedef union _c_APIM_TCU_Word_Tx_HS4_bufTag
{
  vuint8 _c[8];
  _c_APIM_TCU_Word_Tx_HS4_msgType APIM_TCU_Word_Tx_HS4;
} _c_APIM_TCU_Word_Tx_HS4_buf;
typedef union _c_TCU_Send_Signals_3_bufTag
{
  vuint8 _c[8];
  _c_TCU_Send_Signals_3_msgType TCU_Send_Signals_3;
} _c_TCU_Send_Signals_3_buf;
typedef union _c_APIM_Request_Signals_2_HS4_bufTag
{
  vuint8 _c[5];
  _c_APIM_Request_Signals_2_HS4_msgType APIM_Request_Signals_2_HS4;
} _c_APIM_Request_Signals_2_HS4_buf;
typedef union _c_OPTIN_RDISP_WORD_Rx_HS4_bufTag
{
  vuint8 _c[8];
  _c_OPTIN_RDISP_WORD_Rx_HS4_msgType OPTIN_RDISP_WORD_Rx_HS4;
} _c_OPTIN_RDISP_WORD_Rx_HS4_buf;
typedef union _c_OPTIN_RDISP_WORD_Tx_bufTag
{
  vuint8 _c[8];
  _c_OPTIN_RDISP_WORD_Tx_msgType OPTIN_RDISP_WORD_Tx;
} _c_OPTIN_RDISP_WORD_Tx_buf;
typedef union _c_LocationServices_Data2_HS4_bufTag
{
  vuint8 _c[8];
  _c_LocationServices_Data2_HS4_msgType LocationServices_Data2_HS4;
} _c_LocationServices_Data2_HS4_buf;
typedef union _c_LocationServices_Data1_HS4_bufTag
{
  vuint8 _c[8];
  _c_LocationServices_Data1_HS4_msgType LocationServices_Data1_HS4;
} _c_LocationServices_Data1_HS4_buf;
typedef union _c_CellPhonePassport_Stat_HS4_bufTag
{
  vuint8 _c[6];
  _c_CellPhonePassport_Stat_HS4_msgType CellPhonePassport_Stat_HS4;
} _c_CellPhonePassport_Stat_HS4_buf;
typedef union _c_CellPhonePassport_Req_bufTag
{
  vuint8 _c[8];
  _c_CellPhonePassport_Req_msgType CellPhonePassport_Req;
} _c_CellPhonePassport_Req_buf;
typedef union _c_GGCC_Config_Mgmt_ID_1_HS4_bufTag
{
  vuint8 _c[8];
  _c_GGCC_Config_Mgmt_ID_1_HS4_msgType GGCC_Config_Mgmt_ID_1_HS4;
} _c_GGCC_Config_Mgmt_ID_1_HS4_buf;
typedef union _c_BodyInfo_3_HS4_bufTag
{
  vuint8 _c[8];
  _c_BodyInfo_3_HS4_msgType BodyInfo_3_HS4;
} _c_BodyInfo_3_HS4_buf;
typedef union _c_TCU_Send_Signals_4_bufTag
{
  vuint8 _c[8];
  _c_TCU_Send_Signals_4_msgType TCU_Send_Signals_4;
} _c_TCU_Send_Signals_4_buf;
typedef union _c_TRAFFIC_RDISP_WORD_Rx_bufTag
{
  vuint8 _c[8];
  _c_TRAFFIC_RDISP_WORD_Rx_msgType TRAFFIC_RDISP_WORD_Rx;
} _c_TRAFFIC_RDISP_WORD_Rx_buf;
typedef union _c_TRAFFIC_RDISP_WORD_Tx_bufTag
{
  vuint8 _c[8];
  _c_TRAFFIC_RDISP_WORD_Tx_msgType TRAFFIC_RDISP_WORD_Tx;
} _c_TRAFFIC_RDISP_WORD_Tx_buf;
typedef union _c_TCU_Request_Signals_3_bufTag
{
  vuint8 _c[8];
  _c_TCU_Request_Signals_3_msgType TCU_Request_Signals_3;
} _c_TCU_Request_Signals_3_buf;
typedef union _c_APIM_Send_Signals_4_bufTag
{
  vuint8 _c[2];
  _c_APIM_Send_Signals_4_msgType APIM_Send_Signals_4;
} _c_APIM_Send_Signals_4_buf;
typedef union _c_APIM_Send_Signals_3_bufTag
{
  vuint8 _c[8];
  _c_APIM_Send_Signals_3_msgType APIM_Send_Signals_3;
} _c_APIM_Send_Signals_3_buf;
typedef union _c_TCU_Response_Signals_bufTag
{
  vuint8 _c[8];
  _c_TCU_Response_Signals_msgType TCU_Response_Signals;
} _c_TCU_Response_Signals_buf;
typedef union _c_APIM_Request_Signals_3_bufTag
{
  vuint8 _c[5];
  _c_APIM_Request_Signals_3_msgType APIM_Request_Signals_3;
} _c_APIM_Request_Signals_3_buf;
typedef union _c_GWM_SendSignals_10_HS4_bufTag
{
  vuint8 _c[8];
  _c_GWM_SendSignals_10_HS4_msgType GWM_SendSignals_10_HS4;
} _c_GWM_SendSignals_10_HS4_buf;
typedef union _c_GWM_SendSignals_01_HS4_bufTag
{
  vuint8 _c[8];
  _c_GWM_SendSignals_01_HS4_msgType GWM_SendSignals_01_HS4;
} _c_GWM_SendSignals_01_HS4_buf;
typedef union _c_Yaw_Data_HS4_bufTag
{
  vuint8 _c[7];
  _c_Yaw_Data_HS4_msgType Yaw_Data_HS4;
} _c_Yaw_Data_HS4_buf;
typedef union _c_Tire_Pressure_Stat_HS4_bufTag
{
  vuint8 _c[6];
  _c_Tire_Pressure_Stat_HS4_msgType Tire_Pressure_Stat_HS4;
} _c_Tire_Pressure_Stat_HS4_buf;
typedef union _c_Tire_Pressure_Data_HS4_bufTag
{
  vuint8 _c[8];
  _c_Tire_Pressure_Data_HS4_msgType Tire_Pressure_Data_HS4;
} _c_Tire_Pressure_Data_HS4_buf;
typedef union _c_Tire_Pressure_Data_DRW_HS4_bufTag
{
  vuint8 _c[4];
  _c_Tire_Pressure_Data_DRW_HS4_msgType Tire_Pressure_Data_DRW_HS4;
} _c_Tire_Pressure_Data_DRW_HS4_buf;
typedef union _c_GWM_SendSignals_11_HS4_bufTag
{
  vuint8 _c[2];
  _c_GWM_SendSignals_11_HS4_msgType GWM_SendSignals_11_HS4;
} _c_GWM_SendSignals_11_HS4_buf;
typedef union _c_TCU_Send_Signals_5_bufTag
{
  vuint8 _c[8];
  _c_TCU_Send_Signals_5_msgType TCU_Send_Signals_5;
} _c_TCU_Send_Signals_5_buf;
typedef union _c_TCU_Request_Signals_1_bufTag
{
  vuint8 _c[8];
  _c_TCU_Request_Signals_1_msgType TCU_Request_Signals_1;
} _c_TCU_Request_Signals_1_buf;
typedef union _c_LocationServices_3_bufTag
{
  vuint8 _c[8];
  _c_LocationServices_3_msgType LocationServices_3;
} _c_LocationServices_3_buf;
typedef union _c_Personality_APIM_Data2_HS4_bufTag
{
  vuint8 _c[7];
  _c_Personality_APIM_Data2_HS4_msgType Personality_APIM_Data2_HS4;
} _c_Personality_APIM_Data2_HS4_buf;
typedef union _c_Personality_APIM_Data_HS4_bufTag
{
  vuint8 _c[6];
  _c_Personality_APIM_Data_HS4_msgType Personality_APIM_Data_HS4;
} _c_Personality_APIM_Data_HS4_buf;
typedef union _c_APIM_Request_Signals_HS4_bufTag
{
  vuint8 _c[6];
  _c_APIM_Request_Signals_HS4_msgType APIM_Request_Signals_HS4;
} _c_APIM_Request_Signals_HS4_buf;
typedef union _c_Body_Info_7_HS4_bufTag
{
  vuint8 _c[1];
  _c_Body_Info_7_HS4_msgType Body_Info_7_HS4;
} _c_Body_Info_7_HS4_buf;
typedef union _c_GWM_SendSignals_15_HS4_bufTag
{
  vuint8 _c[4];
  _c_GWM_SendSignals_15_HS4_msgType GWM_SendSignals_15_HS4;
} _c_GWM_SendSignals_15_HS4_buf;
typedef union _c_BatteryCharge_Data1_HS4_bufTag
{
  vuint8 _c[8];
  _c_BatteryCharge_Data1_HS4_msgType BatteryCharge_Data1_HS4;
} _c_BatteryCharge_Data1_HS4_buf;
typedef union _c_GWM_SendSignals_12_HS4_bufTag
{
  vuint8 _c[8];
  _c_GWM_SendSignals_12_HS4_msgType GWM_SendSignals_12_HS4;
} _c_GWM_SendSignals_12_HS4_buf;
typedef union _c_GWM_SendSignals_14_HS4_bufTag
{
  vuint8 _c[8];
  _c_GWM_SendSignals_14_HS4_msgType GWM_SendSignals_14_HS4;
} _c_GWM_SendSignals_14_HS4_buf;
typedef union _c_IPC_Send_Signals_2_HS4_bufTag
{
  vuint8 _c[7];
  _c_IPC_Send_Signals_2_HS4_msgType IPC_Send_Signals_2_HS4;
} _c_IPC_Send_Signals_2_HS4_buf;
typedef union _c_TCU_ChrgLoc_Signals_2_bufTag
{
  vuint8 _c[8];
  _c_TCU_ChrgLoc_Signals_2_msgType TCU_ChrgLoc_Signals_2;
} _c_TCU_ChrgLoc_Signals_2_buf;
typedef union _c_TCU_ChrgLoc_Signals_1_bufTag
{
  vuint8 _c[8];
  _c_TCU_ChrgLoc_Signals_1_msgType TCU_ChrgLoc_Signals_1;
} _c_TCU_ChrgLoc_Signals_1_buf;
typedef union _c_Cluster_HEV_Data4_HS4_bufTag
{
  vuint8 _c[7];
  _c_Cluster_HEV_Data4_HS4_msgType Cluster_HEV_Data4_HS4;
} _c_Cluster_HEV_Data4_HS4_buf;
typedef union _c_Upfitter_Data_HS4_bufTag
{
  vuint8 _c[8];
  _c_Upfitter_Data_HS4_msgType Upfitter_Data_HS4;
} _c_Upfitter_Data_HS4_buf;
typedef union _c_PreCond_Hev_Data1_HS4_bufTag
{
  vuint8 _c[5];
  _c_PreCond_Hev_Data1_HS4_msgType PreCond_Hev_Data1_HS4;
} _c_PreCond_Hev_Data1_HS4_buf;
typedef union _c_HEV_ChargeStat_HS4_bufTag
{
  vuint8 _c[6];
  _c_HEV_ChargeStat_HS4_msgType HEV_ChargeStat_HS4;
} _c_HEV_ChargeStat_HS4_buf;
typedef union _c_MtrTracData_1_HS4_bufTag
{
  vuint8 _c[8];
  _c_MtrTracData_1_HS4_msgType MtrTracData_1_HS4;
} _c_MtrTracData_1_HS4_buf;
typedef union _c_IPC_TripData_1_HS4_bufTag
{
  vuint8 _c[8];
  _c_IPC_TripData_1_HS4_msgType IPC_TripData_1_HS4;
} _c_IPC_TripData_1_HS4_buf;
typedef union _c_IPC_Consumption_HS4_bufTag
{
  vuint8 _c[8];
  _c_IPC_Consumption_HS4_msgType IPC_Consumption_HS4;
} _c_IPC_Consumption_HS4_buf;
typedef union _c_Cluster_HEV_Data9_HS4_bufTag
{
  vuint8 _c[8];
  _c_Cluster_HEV_Data9_HS4_msgType Cluster_HEV_Data9_HS4;
} _c_Cluster_HEV_Data9_HS4_buf;
typedef union _c_Cluster_HEV_Data1_HS4_bufTag
{
  vuint8 _c[8];
  _c_Cluster_HEV_Data1_HS4_msgType Cluster_HEV_Data1_HS4;
} _c_Cluster_HEV_Data1_HS4_buf;
typedef union _c_Cluster_HEV_Data7_HS4_bufTag
{
  vuint8 _c[8];
  _c_Cluster_HEV_Data7_HS4_msgType Cluster_HEV_Data7_HS4;
} _c_Cluster_HEV_Data7_HS4_buf;
typedef union _c_GWM_HPCM_i_FrP11_HS4_bufTag
{
  vuint8 _c[8];
  _c_GWM_HPCM_i_FrP11_HS4_msgType GWM_HPCM_i_FrP11_HS4;
} _c_GWM_HPCM_i_FrP11_HS4_buf;
typedef union _c_GWM_HPCM_i_FrP10_HS4_bufTag
{
  vuint8 _c[8];
  _c_GWM_HPCM_i_FrP10_HS4_msgType GWM_HPCM_i_FrP10_HS4;
} _c_GWM_HPCM_i_FrP10_HS4_buf;
typedef union _c_BattTrac_Data1_HS4_bufTag
{
  vuint8 _c[8];
  _c_BattTrac_Data1_HS4_msgType BattTrac_Data1_HS4;
} _c_BattTrac_Data1_HS4_buf;
typedef union _c_Battery_Traction_1_HS4_bufTag
{
  vuint8 _c[6];
  _c_Battery_Traction_1_HS4_msgType Battery_Traction_1_HS4;
} _c_Battery_Traction_1_HS4_buf;
typedef union _c_TCU_Send_Signals_2_bufTag
{
  vuint8 _c[8];
  _c_TCU_Send_Signals_2_msgType TCU_Send_Signals_2;
} _c_TCU_Send_Signals_2_buf;
typedef union _c_TCU_Precond_Signals_1_bufTag
{
  vuint8 _c[8];
  _c_TCU_Precond_Signals_1_msgType TCU_Precond_Signals_1;
} _c_TCU_Precond_Signals_1_buf;
typedef union _c_GWM_SendSignals_16_HS4_bufTag
{
  vuint8 _c[4];
  _c_GWM_SendSignals_16_HS4_msgType GWM_SendSignals_16_HS4;
} _c_GWM_SendSignals_16_HS4_buf;
typedef union _c_MtrTrac_Data2_HS4_bufTag
{
  vuint8 _c[5];
  _c_MtrTrac_Data2_HS4_msgType MtrTrac_Data2_HS4;
} _c_MtrTrac_Data2_HS4_buf;
typedef union _c_HEV_Data_Monitor_9_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_9_HS4_msgType HEV_Data_Monitor_9_HS4;
} _c_HEV_Data_Monitor_9_HS4_buf;
typedef union _c_HEV_Data_Monitor_8_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_8_HS4_msgType HEV_Data_Monitor_8_HS4;
} _c_HEV_Data_Monitor_8_HS4_buf;
typedef union _c_HEV_Data_Monitor_7_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_7_HS4_msgType HEV_Data_Monitor_7_HS4;
} _c_HEV_Data_Monitor_7_HS4_buf;
typedef union _c_HEV_Data_Monitor_6_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_6_HS4_msgType HEV_Data_Monitor_6_HS4;
} _c_HEV_Data_Monitor_6_HS4_buf;
typedef union _c_HEV_Data_Monitor_5_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_5_HS4_msgType HEV_Data_Monitor_5_HS4;
} _c_HEV_Data_Monitor_5_HS4_buf;
typedef union _c_HEV_Data_Monitor_4_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_4_HS4_msgType HEV_Data_Monitor_4_HS4;
} _c_HEV_Data_Monitor_4_HS4_buf;
typedef union _c_HEV_Data_Monitor_3_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_3_HS4_msgType HEV_Data_Monitor_3_HS4;
} _c_HEV_Data_Monitor_3_HS4_buf;
typedef union _c_HEV_Data_Monitor_2_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_2_HS4_msgType HEV_Data_Monitor_2_HS4;
} _c_HEV_Data_Monitor_2_HS4_buf;
typedef union _c_HEV_Data_Monitor_23_HS4_bufTag
{
  vuint8 _c[6];
  _c_HEV_Data_Monitor_23_HS4_msgType HEV_Data_Monitor_23_HS4;
} _c_HEV_Data_Monitor_23_HS4_buf;
typedef union _c_HEV_Data_Monitor_22_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_22_HS4_msgType HEV_Data_Monitor_22_HS4;
} _c_HEV_Data_Monitor_22_HS4_buf;
typedef union _c_HEV_Data_Monitor_21_HS4_bufTag
{
  vuint8 _c[7];
  _c_HEV_Data_Monitor_21_HS4_msgType HEV_Data_Monitor_21_HS4;
} _c_HEV_Data_Monitor_21_HS4_buf;
typedef union _c_HEV_Data_Monitor_20_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_20_HS4_msgType HEV_Data_Monitor_20_HS4;
} _c_HEV_Data_Monitor_20_HS4_buf;
typedef union _c_HEV_Data_Monitor_1_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_1_HS4_msgType HEV_Data_Monitor_1_HS4;
} _c_HEV_Data_Monitor_1_HS4_buf;
typedef union _c_HEV_Data_Monitor_19_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_19_HS4_msgType HEV_Data_Monitor_19_HS4;
} _c_HEV_Data_Monitor_19_HS4_buf;
typedef union _c_HEV_Data_Monitor_18_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_18_HS4_msgType HEV_Data_Monitor_18_HS4;
} _c_HEV_Data_Monitor_18_HS4_buf;
typedef union _c_HEV_Data_Monitor_17_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_17_HS4_msgType HEV_Data_Monitor_17_HS4;
} _c_HEV_Data_Monitor_17_HS4_buf;
typedef union _c_HEV_Data_Monitor_16_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_16_HS4_msgType HEV_Data_Monitor_16_HS4;
} _c_HEV_Data_Monitor_16_HS4_buf;
typedef union _c_HEV_Data_Monitor_15_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_15_HS4_msgType HEV_Data_Monitor_15_HS4;
} _c_HEV_Data_Monitor_15_HS4_buf;
typedef union _c_HEV_Data_Monitor_14_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_14_HS4_msgType HEV_Data_Monitor_14_HS4;
} _c_HEV_Data_Monitor_14_HS4_buf;
typedef union _c_HEV_Data_Monitor_13_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_13_HS4_msgType HEV_Data_Monitor_13_HS4;
} _c_HEV_Data_Monitor_13_HS4_buf;
typedef union _c_HEV_Data_Monitor_12_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_12_HS4_msgType HEV_Data_Monitor_12_HS4;
} _c_HEV_Data_Monitor_12_HS4_buf;
typedef union _c_HEV_Data_Monitor_11_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_11_HS4_msgType HEV_Data_Monitor_11_HS4;
} _c_HEV_Data_Monitor_11_HS4_buf;
typedef union _c_HEV_Data_Monitor_10_HS4_bufTag
{
  vuint8 _c[8];
  _c_HEV_Data_Monitor_10_HS4_msgType HEV_Data_Monitor_10_HS4;
} _c_HEV_Data_Monitor_10_HS4_buf;
typedef union _c_TCU_RFA_WORD_Tx_HS4_bufTag
{
  vuint8 _c[8];
  _c_TCU_RFA_WORD_Tx_HS4_msgType TCU_RFA_WORD_Tx_HS4;
} _c_TCU_RFA_WORD_Tx_HS4_buf;
typedef union _c_RFA_TCU_WORD_Tx_bufTag
{
  vuint8 _c[8];
  _c_RFA_TCU_WORD_Tx_msgType RFA_TCU_WORD_Tx;
} _c_RFA_TCU_WORD_Tx_buf;
typedef union _c_PaakCtlData5_bufTag
{
  vuint8 _c[8];
  _c_PaakCtlData5_msgType PaakCtlData5;
} _c_PaakCtlData5_buf;
typedef union _c_TCU_Request_Signals_4_bufTag
{
  vuint8 _c[8];
  _c_TCU_Request_Signals_4_msgType TCU_Request_Signals_4;
} _c_TCU_Request_Signals_4_buf;
typedef union _c_TCU_Send_Signals_6_bufTag
{
  vuint8 _c[8];
  _c_TCU_Send_Signals_6_msgType TCU_Send_Signals_6;
} _c_TCU_Send_Signals_6_buf;
typedef union _c_ChargeSettings_HS4_bufTag
{
  vuint8 _c[8];
  _c_ChargeSettings_HS4_msgType ChargeSettings_HS4;
} _c_ChargeSettings_HS4_buf;
typedef union _c_Saved_Charge_Locat_HS4_bufTag
{
  vuint8 _c[8];
  _c_Saved_Charge_Locat_HS4_msgType Saved_Charge_Locat_HS4;
} _c_Saved_Charge_Locat_HS4_buf;
typedef union _c_Unsaved_Charge_Locat_HS4_bufTag
{
  vuint8 _c[8];
  _c_Unsaved_Charge_Locat_HS4_msgType Unsaved_Charge_Locat_HS4;
} _c_Unsaved_Charge_Locat_HS4_buf;
typedef union _c_GWM_SendSignals_13_HS4_bufTag
{
  vuint8 _c[4];
  _c_GWM_SendSignals_13_HS4_msgType GWM_SendSignals_13_HS4;
} _c_GWM_SendSignals_13_HS4_buf;


/* -----------------------------------------------------------------------------
    &&&~ Message Buffers
 ----------------------------------------------------------------------------- */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GlobalClock_Data_HS4_buf V_MEMRAM2 GlobalClock_Data_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_APIM_Send_Signals_2_HS4_buf V_MEMRAM2 APIM_Send_Signals_2_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_Request_Signals_2_buf V_MEMRAM2 TCU_Request_Signals_2;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_05_HS4_buf V_MEMRAM2 GWM_SendSignals_05_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_Send_Signals_buf V_MEMRAM2 TCU_Send_Signals;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_AutoSar_Network_Mgmt_buf V_MEMRAM2 TCU_AutoSar_Network_Mgmt;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_08_HS4_buf V_MEMRAM2 GWM_SendSignals_08_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_07_HS4_buf V_MEMRAM2 GWM_SendSignals_07_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_ABS_Signals_HS4_buf V_MEMRAM2 ABS_Signals_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_09_HS4_buf V_MEMRAM2 GWM_SendSignals_09_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_04_HS4_buf V_MEMRAM2 GWM_SendSignals_04_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_03_HS4_buf V_MEMRAM2 GWM_SendSignals_03_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_02_HS4_buf V_MEMRAM2 GWM_SendSignals_02_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_APIM_TCU_Word_Rx_HS4_buf V_MEMRAM2 APIM_TCU_Word_Rx_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TxDynamicMsg0_buf V_MEMRAM2 TxDynamicMsg0;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_APIM_TCU_Word_Tx_HS4_buf V_MEMRAM2 APIM_TCU_Word_Tx_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_Send_Signals_3_buf V_MEMRAM2 TCU_Send_Signals_3;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_APIM_Request_Signals_2_HS4_buf V_MEMRAM2 APIM_Request_Signals_2_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_OPTIN_RDISP_WORD_Rx_HS4_buf V_MEMRAM2 OPTIN_RDISP_WORD_Rx_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_OPTIN_RDISP_WORD_Tx_buf V_MEMRAM2 OPTIN_RDISP_WORD_Tx;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_LocationServices_Data2_HS4_buf V_MEMRAM2 LocationServices_Data2_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_LocationServices_Data1_HS4_buf V_MEMRAM2 LocationServices_Data1_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_CellPhonePassport_Stat_HS4_buf V_MEMRAM2 CellPhonePassport_Stat_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_CellPhonePassport_Req_buf V_MEMRAM2 CellPhonePassport_Req;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GGCC_Config_Mgmt_ID_1_HS4_buf V_MEMRAM2 GGCC_Config_Mgmt_ID_1_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_BodyInfo_3_HS4_buf V_MEMRAM2 BodyInfo_3_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_Send_Signals_4_buf V_MEMRAM2 TCU_Send_Signals_4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TRAFFIC_RDISP_WORD_Rx_buf V_MEMRAM2 TRAFFIC_RDISP_WORD_Rx;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TRAFFIC_RDISP_WORD_Tx_buf V_MEMRAM2 TRAFFIC_RDISP_WORD_Tx;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_Request_Signals_3_buf V_MEMRAM2 TCU_Request_Signals_3;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_APIM_Send_Signals_4_buf V_MEMRAM2 APIM_Send_Signals_4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_APIM_Send_Signals_3_buf V_MEMRAM2 APIM_Send_Signals_3;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_Response_Signals_buf V_MEMRAM2 TCU_Response_Signals;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_APIM_Request_Signals_3_buf V_MEMRAM2 APIM_Request_Signals_3;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_10_HS4_buf V_MEMRAM2 GWM_SendSignals_10_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_01_HS4_buf V_MEMRAM2 GWM_SendSignals_01_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Yaw_Data_HS4_buf V_MEMRAM2 Yaw_Data_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Tire_Pressure_Stat_HS4_buf V_MEMRAM2 Tire_Pressure_Stat_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Tire_Pressure_Data_HS4_buf V_MEMRAM2 Tire_Pressure_Data_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Tire_Pressure_Data_DRW_HS4_buf V_MEMRAM2 Tire_Pressure_Data_DRW_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_11_HS4_buf V_MEMRAM2 GWM_SendSignals_11_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_Send_Signals_5_buf V_MEMRAM2 TCU_Send_Signals_5;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_Request_Signals_1_buf V_MEMRAM2 TCU_Request_Signals_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_LocationServices_3_buf V_MEMRAM2 LocationServices_3;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Personality_APIM_Data2_HS4_buf V_MEMRAM2 Personality_APIM_Data2_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Personality_APIM_Data_HS4_buf V_MEMRAM2 Personality_APIM_Data_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_APIM_Request_Signals_HS4_buf V_MEMRAM2 APIM_Request_Signals_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Body_Info_7_HS4_buf V_MEMRAM2 Body_Info_7_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_15_HS4_buf V_MEMRAM2 GWM_SendSignals_15_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_BatteryCharge_Data1_HS4_buf V_MEMRAM2 BatteryCharge_Data1_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_12_HS4_buf V_MEMRAM2 GWM_SendSignals_12_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_14_HS4_buf V_MEMRAM2 GWM_SendSignals_14_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_IPC_Send_Signals_2_HS4_buf V_MEMRAM2 IPC_Send_Signals_2_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_ChrgLoc_Signals_2_buf V_MEMRAM2 TCU_ChrgLoc_Signals_2;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_ChrgLoc_Signals_1_buf V_MEMRAM2 TCU_ChrgLoc_Signals_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Cluster_HEV_Data4_HS4_buf V_MEMRAM2 Cluster_HEV_Data4_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Upfitter_Data_HS4_buf V_MEMRAM2 Upfitter_Data_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_PreCond_Hev_Data1_HS4_buf V_MEMRAM2 PreCond_Hev_Data1_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_ChargeStat_HS4_buf V_MEMRAM2 HEV_ChargeStat_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_MtrTracData_1_HS4_buf V_MEMRAM2 MtrTracData_1_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_IPC_TripData_1_HS4_buf V_MEMRAM2 IPC_TripData_1_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_IPC_Consumption_HS4_buf V_MEMRAM2 IPC_Consumption_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Cluster_HEV_Data9_HS4_buf V_MEMRAM2 Cluster_HEV_Data9_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Cluster_HEV_Data1_HS4_buf V_MEMRAM2 Cluster_HEV_Data1_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Cluster_HEV_Data7_HS4_buf V_MEMRAM2 Cluster_HEV_Data7_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_HPCM_i_FrP11_HS4_buf V_MEMRAM2 GWM_HPCM_i_FrP11_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_HPCM_i_FrP10_HS4_buf V_MEMRAM2 GWM_HPCM_i_FrP10_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_BattTrac_Data1_HS4_buf V_MEMRAM2 BattTrac_Data1_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Battery_Traction_1_HS4_buf V_MEMRAM2 Battery_Traction_1_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_Send_Signals_2_buf V_MEMRAM2 TCU_Send_Signals_2;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_Precond_Signals_1_buf V_MEMRAM2 TCU_Precond_Signals_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_16_HS4_buf V_MEMRAM2 GWM_SendSignals_16_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_MtrTrac_Data2_HS4_buf V_MEMRAM2 MtrTrac_Data2_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_9_HS4_buf V_MEMRAM2 HEV_Data_Monitor_9_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_8_HS4_buf V_MEMRAM2 HEV_Data_Monitor_8_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_7_HS4_buf V_MEMRAM2 HEV_Data_Monitor_7_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_6_HS4_buf V_MEMRAM2 HEV_Data_Monitor_6_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_5_HS4_buf V_MEMRAM2 HEV_Data_Monitor_5_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_4_HS4_buf V_MEMRAM2 HEV_Data_Monitor_4_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_3_HS4_buf V_MEMRAM2 HEV_Data_Monitor_3_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_2_HS4_buf V_MEMRAM2 HEV_Data_Monitor_2_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_23_HS4_buf V_MEMRAM2 HEV_Data_Monitor_23_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_22_HS4_buf V_MEMRAM2 HEV_Data_Monitor_22_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_21_HS4_buf V_MEMRAM2 HEV_Data_Monitor_21_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_20_HS4_buf V_MEMRAM2 HEV_Data_Monitor_20_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_1_HS4_buf V_MEMRAM2 HEV_Data_Monitor_1_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_19_HS4_buf V_MEMRAM2 HEV_Data_Monitor_19_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_18_HS4_buf V_MEMRAM2 HEV_Data_Monitor_18_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_17_HS4_buf V_MEMRAM2 HEV_Data_Monitor_17_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_16_HS4_buf V_MEMRAM2 HEV_Data_Monitor_16_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_15_HS4_buf V_MEMRAM2 HEV_Data_Monitor_15_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_14_HS4_buf V_MEMRAM2 HEV_Data_Monitor_14_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_13_HS4_buf V_MEMRAM2 HEV_Data_Monitor_13_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_12_HS4_buf V_MEMRAM2 HEV_Data_Monitor_12_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_11_HS4_buf V_MEMRAM2 HEV_Data_Monitor_11_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HEV_Data_Monitor_10_HS4_buf V_MEMRAM2 HEV_Data_Monitor_10_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_RFA_WORD_Tx_HS4_buf V_MEMRAM2 TCU_RFA_WORD_Tx_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_RFA_TCU_WORD_Tx_buf V_MEMRAM2 RFA_TCU_WORD_Tx;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_PaakCtlData5_buf V_MEMRAM2 PaakCtlData5;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_Request_Signals_4_buf V_MEMRAM2 TCU_Request_Signals_4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_Send_Signals_6_buf V_MEMRAM2 TCU_Send_Signals_6;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_ChargeSettings_HS4_buf V_MEMRAM2 ChargeSettings_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Saved_Charge_Locat_HS4_buf V_MEMRAM2 Saved_Charge_Locat_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Unsaved_Charge_Locat_HS4_buf V_MEMRAM2 Unsaved_Charge_Locat_HS4;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GWM_SendSignals_13_HS4_buf V_MEMRAM2 GWM_SendSignals_13_HS4;
/* RAM CATEGORY 2 END */






/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 273455553
      #error "The magic number of the generated file <D:\TCU\Bundle3\git\vuc\G3DO_VuC_w_Tp\Workspace\CANsetup\GenySetups\genCANFiles\drv_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 273455553
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __DRV_PAR_H__ */
