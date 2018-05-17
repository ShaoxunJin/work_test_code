/**************************************************************************
* Copyright (C) 2008, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : SS B500/10
* 所属组件 : WRGN
* 模块名称 : WRGN
* 文件名称 : WRGN.cpp
* 概要描述 :
* 历史记录 :
* 版本    日期         作者        内容
  1.0       2010830    zhengjz     添加延迟函数
**************************************************************************/

#include "stdafx.h"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
//#include <poll.h>
#include "smee_type.h"

#include "EH4A_config.h"
#include "EH4A_if.h"
#include "EH4A_tc.h"

#include "WRGN_if.h"
#include "WRGN_tc.h"

const char * WRbool2str(const SMEE_BOOL &t);
const char * WRbool2str(const SMEE_BOOL *t);

const char * WRenum2str(const WRGN_TRANSFER_TYPE_ENUM &t)
{
	const char *str = 0;
	switch(t)
	{
	case WRGN_MECHANICS:
		str = "MECHANICS";
		break;
	case WRGN_CONTROLLER:
		str = "CONTROLLER";
		break;
    case WRGN_OPENTOTAL:
        str = "OPENTOTAL";
        break;
    case WRGN_CLOSEDLOOP:
        str = "CLOSEDLOOP";
        break;
    case WRGN_SENSITIVITY:
        str = "SENSITIVITY";
        break;
    case WRGN_PROCESSSENSITIVITY:
        str = "PROCESSSENSITIVITY";
        break;
	default:
		str = "INVALID_ENUM";
		break;
	}

	return str;

}
/*
void WRGN_wait_mseconds(int ms)
{
	pollfd *fd = 0;
	poll(fd, 0, ms);
    return ;
}
*/
/*
void WRGN_set_table_item(QTableWidget *qtable,int row,int column,QString sText)
{
    QTableWidgetItem *qTmp;

    qTmp = qtable->item(row, column);
    if (NULL == qTmp)
    {
        qTmp = new QTableWidgetItem;
    }

    qTmp->setText(sText);
    qtable->setItem(row,column,qTmp);
    return ;
}
*/

int WRGN_cal_tf(IN SMEE_BOOL bSim,
			 IN WRGN_TRANSFER_TYPE_STRUCT sType,
			 IN double *pdTrace_data_crl_out,
			 IN double *pdTrace_data_crl_err,
			 IN double *pdTrace_data_crl_north2_out,
			 IN double *pdTrace_data_crl_after_signal,
                IN double dServoPeriod,            //伺服周期
                IN int iTestNum,                // 测多少次
                OUT WRGN_TF_STRUCT *psTF_out)

{
    int iErrorCode = 0;
    int iErrorLink[2] = {0, 0};
    char *psErrorText = NULL;
//	SMEE_INT32 iFreq_points = 0;
	static WRGN_SPECTRUM_STRUCT sSperctrum[WRGN_MAX_TRANSFER_TYPE];

/*	TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,">(dServoPeriod =%f,"
										"iTestNum =%d,"
										"sType.bMechanical =%s,"
										"sType.bController =%s,"
										"sType.bOpenTotal =%s,"
										"sType.bClosedLoop =%s,"
										"sType.bSensity =%s,"
										"sType.bProcessSensity =%s)",
										dServoPeriod,
										iTestNum,
										WRbool2str(sType.bMechanical),
										WRbool2str(sType.bController),
										WRbool2str(sType.bOpenTotal),
										WRbool2str(sType.bClosedLoop),
										WRbool2str(sType.bSensity),
										WRbool2str(sType.bProcessSensity));
*/

    if(0 == iTestNum)
    {
       memset((void *)&sSperctrum,0x0,WRGN_MAX_TRANSFER_TYPE* sizeof(WRGN_SPECTRUM_STRUCT));
    }
	if(!bSim)
	{
//	    for (int iIndex = 1;iIndex <= iTestNum &&(0 == iErrorCode);iIndex++)
//	    {
//	        TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,"<(iTest_number = %d)",iIndex);

		if(sType.bMechanical)
	     {
			if(0 == iErrorCode)
			{
			  //计算机械传函频谱
	           iErrorCode = WRGN_spectrum(iTestNum,
        									  dServoPeriod,
								     		  pdTrace_data_crl_out,
                                              pdTrace_data_crl_err,
                                              &(sSperctrum[WRGN_MECHANICS]),
                                              psTF_out->sMechanical.freq);
		        if(OK != (iErrorLink[0] = iErrorCode))
		        {
		            iErrorCode = WRGN_HW_CAL_TF_ERROR;
		            //psErrorText = EH4A_create_text("%s: Error occurred when WRGN_spectrum!", __FUNCTION__);
		            //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
		            //free(psErrorText);
		            //psErrorText = NULL;
		        }
			}
			if(0 == iErrorCode)
			{
			    iErrorCode = WRGN_bode(sSperctrum[WRGN_MECHANICS],
										 &(psTF_out->sMechanical));
 		         if(OK != (iErrorLink[0] = iErrorCode))
 		         {
 		             iErrorCode = WRGN_HW_CAL_TF_ERROR;
 		             //psErrorText = EH4A_create_text("%s: Error occurred when WRGN_bode!", __FUNCTION__);
 		             //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
 		             //free(psErrorText);
 		             //psErrorText = NULL;
 		         }
			}
/*	    		TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,">(psTF_out->sMechanical.freq[0] =%f"
												"psTF_out->sMechanical.freq[1] =%f,"
												"psTF_out->sMechanical.mag[0] =%f,"
												"psTF_out->sMechanical.mag[1] =%f,"
												"psTF_out->sMechanical.phase[0] =%f,"
												"psTF_out->sMechanical.phase[1] =%f,"
												"psTF_out->sMechanical.cohere[0] =%f,"
												"psTF_out->sMechanical.cohere[1] =%f)",
												psTF_out->sMechanical.freq[0],
												psTF_out->sMechanical.freq[1],
												psTF_out->sMechanical.mag[0],
												psTF_out->sMechanical.mag[1],
												psTF_out->sMechanical.phase[0],
												psTF_out->sMechanical.phase[1],
												psTF_out->sMechanical.cohere[0],
												psTF_out->sMechanical.cohere[1]);
*/	

	     }
	    	if(sType.bOpenTotal)
	     {
        		if(0 == iErrorCode)
        		{
        			//计算开环总传函
        			iErrorCode = WRGN_spectrum(iTestNum,
                								dServoPeriod,
                                                pdTrace_data_crl_out,
                                                pdTrace_data_crl_north2_out,
                                                &(sSperctrum[WRGN_OPENTOTAL]),
                                                psTF_out->sOpenTotal.freq);
        	        if(OK != (iErrorLink[0] = iErrorCode))
        	        {
        	            //iErrorCode = WRGN_HW_CAL_TF_ERROR;
        	            //psErrorText = EH4A_create_text("%s: Error occurred when WRGN_spectrum!", __FUNCTION__);
						//EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
        	            //free(psErrorText);
        	            //psErrorText = NULL;
        	        }
        		}
        		if(0 == iErrorCode)
        		{
        			iErrorCode = WRGN_bode(sSperctrum[WRGN_OPENTOTAL],
        									 &(psTF_out->sOpenTotal));
        	        if(OK != (iErrorLink[0] = iErrorCode))
        	        {
        	            iErrorCode = WRGN_HW_CAL_TF_ERROR;
        	            //psErrorText = EH4A_create_text("%s: Error occurred when WRGN_bode!", __FUNCTION__);
        	            //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
        	            //free(psErrorText);
        	            //psErrorText = NULL;
        	        }
        		}
/*	    		TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,"<(psTF_out->sOpenTotal.freq[0] =%f"
												"psTF_out->sOpenTotal.freq[1] =%f,"
												"psTF_out->sOpenTotal.mag[0] =%f,"
												"psTF_out->sOpenTotal.mag[1] =%f,"
												"psTF_out->sOpenTotal.phase[0] =%f,"
												"psTF_out->sOpenTotal.phase[1] =%f,"
												"psTF_out->sOpenTotal.cohere[0] =%f,"
												"psTF_out->sOpenTotal.cohere[1] =%f)",
												psTF_out->sOpenTotal.freq[0],
												psTF_out->sOpenTotal.freq[1],
												psTF_out->sOpenTotal.mag[0],
												psTF_out->sOpenTotal.mag[1],
												psTF_out->sOpenTotal.phase[0],
												psTF_out->sOpenTotal.phase[1],
												psTF_out->sOpenTotal.cohere[0],
												psTF_out->sOpenTotal.cohere[1]);
*/
	        }
	        if( sType.bController)
	        {
			if(0 == iErrorCode)
			{
				//计算控制器传函
				iErrorCode = WRGN_spectrum(iTestNum,
	            							dServoPeriod,
		                                        pdTrace_data_crl_err,
		                                        pdTrace_data_crl_north2_out,
	                                             &(sSperctrum[WRGN_CONTROLLER]),
	                                             psTF_out->sControl.freq);
		        if(OK != (iErrorLink[0] = iErrorCode))
		        {
		            iErrorCode = WRGN_HW_CAL_TF_ERROR;
		            //psErrorText = EH4A_create_text("%s: Error occurred when WRGN_spectrum!", __FUNCTION__);
		            //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
		            //free(psErrorText);
		            //psErrorText = NULL;
		        }
			}
			if(0 == iErrorCode)
			{
				iErrorCode = WRGN_bode(sSperctrum[WRGN_CONTROLLER],
										 &(psTF_out->sControl));
		        if(OK != (iErrorLink[0] = iErrorCode))
		        {
		            iErrorCode = WRGN_HW_CAL_TF_ERROR;
		            //psErrorText = EH4A_create_text("%s: Error occurred when WRGN_bode!", __FUNCTION__);
		            //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
		            //free(psErrorText);
		            //psErrorText = NULL;
		        }
			}
	    		/*
	    		TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,"<(psTF_out->sControl.freq[0] =%f"
												"psTF_out->sControl.freq[1] =%f,"
												"psTF_out->sControl.mag[0] =%f,"
												"psTF_out->sControl.mag[1] =%f,"
												"psTF_out->sControl.phase[0] =%f,"
												"psTF_out->sControl.phase[1] =%f,"
												"psTF_out->sControl.cohere[0] =%f,"
												"psTF_out->sControl.cohere[1] =%f)",
												psTF_out->sControl.freq[0],
												psTF_out->sControl.freq[1],
												psTF_out->sControl.mag[0],
												psTF_out->sControl.mag[1],
												psTF_out->sControl.phase[0],
												psTF_out->sControl.phase[1],
												psTF_out->sControl.cohere[0],
												psTF_out->sControl.cohere[1]);
				*/
	        }
	        if(sType.bClosedLoop)
	        {
			if(0 == iErrorCode)
			{
				//计算闭环传函
	            iErrorCode = WRGN_spectrum(iTestNum,
	        							dServoPeriod,
	                                        pdTrace_data_crl_after_signal,
	                                        pdTrace_data_crl_north2_out,
	                                        &(sSperctrum[WRGN_CLOSEDLOOP]),
	                                        psTF_out->sClosedLoop.freq);
		        if(OK != (iErrorLink[0] = iErrorCode))
		        {
		            iErrorCode = WRGN_HW_CAL_TF_ERROR;
		            //psErrorText = EH4A_create_text("%s: Error occurred when WRGN_spectrum!", __FUNCTION__);
		            //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
		            //free(psErrorText);
		            //psErrorText = NULL;
		        }
			}
			if(0 == iErrorCode)
			{
				iErrorCode = WRGN_bode(sSperctrum[WRGN_CLOSEDLOOP],
										 &(psTF_out->sClosedLoop));
		        if(OK != (iErrorLink[0] = iErrorCode))
		        {
		            iErrorCode = WRGN_HW_CAL_TF_ERROR;
		            //psErrorText = EH4A_create_text("%s: Error occurred when WRGN_bode!", __FUNCTION__);
		            //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
		            //free(psErrorText);
		            //psErrorText = NULL;
		        }
			}
	    		/*
	    		TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,"<(psTF_out->sClosedLoop.freq[0] =%f"
												"psTF_out->sClosedLoop.freq[1] =%f,"
												"psTF_out->sClosedLoop.mag[0] =%f,"
												"psTF_out->sClosedLoop.mag[1] =%f,"
												"psTF_out->sClosedLoop.phase[0] =%f,"
												"psTF_out->sClosedLoop.phase[1] =%f,"
												"psTF_out->sClosedLoop.cohere[0] =%f,"
												"psTF_out->sClosedLoop.cohere[1] =%f)",
												psTF_out->sClosedLoop.freq[0],
												psTF_out->sClosedLoop.freq[1],
												psTF_out->sClosedLoop.mag[0],
												psTF_out->sClosedLoop.mag[1],
												psTF_out->sClosedLoop.phase[0],
												psTF_out->sClosedLoop.phase[1],
												psTF_out->sClosedLoop.cohere[0],
												psTF_out->sClosedLoop.cohere[1]);
												*/
	        }
	        if(sType.bSensity)
	        {
			if(0 == iErrorCode)
			{
				//测试敏感度传函
	            iErrorCode = WRGN_spectrum(iTestNum,
		        						dServoPeriod,
									pdTrace_data_crl_after_signal,
	                                        pdTrace_data_crl_out,
		                                   &(sSperctrum[WRGN_SENSITIVITY]),
		                                   psTF_out->sSensity.freq);
		        if(OK != (iErrorLink[0] = iErrorCode))
		        {
		            iErrorCode = WRGN_HW_CAL_TF_ERROR;
		            //psErrorText = EH4A_create_text("%s: Error occurred when WRGN_spectrum!", __FUNCTION__);
		            //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
		            //free(psErrorText);
		            //psErrorText = NULL;
		        }
			}
			if(0 == iErrorCode)
			{
				iErrorCode = WRGN_bode(sSperctrum[WRGN_SENSITIVITY],
										 &(psTF_out->sSensity));
		        if(OK != (iErrorLink[0] = iErrorCode))
		        {
		            iErrorCode = WRGN_HW_CAL_TF_ERROR;
		            //psErrorText = EH4A_create_text("%s: Error occurred when WRGN_bode!", __FUNCTION__);
		            //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
		            //free(psErrorText);
		            //psErrorText = NULL;
		        }
			}
	    		/*
	    		TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,"<(psTF_out->sSensity.freq[0] =%f"
												"psTF_out->sSensity.freq[1] =%f,"
												"psTF_out->sSensity.mag[0] =%f,"
												"psTF_out->sSensity.mag[1] =%f,"
												"psTF_out->sSensity.phase[0] =%f,"
												"psTF_out->sSensity.phase[1] =%f,"
												"psTF_out->sSensity.cohere[0] =%f,"
												"psTF_out->sSensity.cohere[1] =%f)",
												psTF_out->sSensity.freq[0],
												psTF_out->sSensity.freq[1],
												psTF_out->sSensity.mag[0],
												psTF_out->sSensity.mag[1],
												psTF_out->sSensity.phase[0],
												psTF_out->sSensity.phase[1],
												psTF_out->sSensity.cohere[0],
												psTF_out->sSensity.cohere[1]);
				*/
	        }
	        if(sType.bProcessSensity)
	        {
			if(0 == iErrorCode)
			{
				//测试过程传函
	             iErrorCode = WRGN_spectrum(iTestNum,
		        						dServoPeriod,
	                                        pdTrace_data_crl_after_signal,
	                                        pdTrace_data_crl_err,
		                                   &(sSperctrum[WRGN_PROCESSSENSITIVITY]),
		                                   psTF_out->sProcessSensity.freq);
		        if(OK != (iErrorLink[0] = iErrorCode))
		        {
		            iErrorCode = WRGN_HW_CAL_TF_ERROR;
		            //psErrorText = EH4A_create_text("%s: Error occurred when WRGN_spectrum!", __FUNCTION__);
		            //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
		            //free(psErrorText);
		            //psErrorText = NULL;
		        }
			}
			if(0 == iErrorCode)
			{
				iErrorCode = WRGN_bode(sSperctrum[WRGN_PROCESSSENSITIVITY],
										 &(psTF_out->sProcessSensity));
		        if(OK != (iErrorLink[0] = iErrorCode))
		        {
		            iErrorCode = WRGN_HW_CAL_TF_ERROR;
		            //psErrorText = EH4A_create_text("%s: Error occurred when WRGN_bode!", __FUNCTION__);
		            //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
		            //free(psErrorText);
		            //psErrorText = NULL;
		        }
			}
/*
				TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,"<(psTF_out->sProcessSensity.freq[0] =%f"
												"psTF_out->sProcessSensity.freq[1] =%f,"
												"psTF_out->sProcessSensity.mag[0] =%f,"
												"psTF_out->sSensity.mag[1] =%f,"
												"psTF_out->sProcessSensity.phase[0] =%f,"
												"psTF_out->sProcessSensity.phase[1] =%f,"
												"psTF_out->sProcessSensity.cohere[0] =%f,"
												"psTF_out->sProcessSensity.cohere[1] =%f)",
												psTF_out->sProcessSensity.freq[0],
												psTF_out->sProcessSensity.freq[1],
												psTF_out->sProcessSensity.mag[0],
												psTF_out->sProcessSensity.mag[1],
												psTF_out->sProcessSensity.phase[0],
												psTF_out->sProcessSensity.phase[1],
												psTF_out->sProcessSensity.cohere[0],
												psTF_out->sProcessSensity.cohere[1]);
*/
	        }
	    }
//	}
    //TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,">(0x%x)",iErrorCode);

    return iErrorCode;

}

int WRGN_cal_openloop(IN SMEE_BOOL bSim,
					 IN WRGN_BODE_STRUCT sTf_out,
					 IN double dServoPeriod,
					 IN double dStart_fr,
					 IN double dStop_fr,
					 OUT WRGN_OPEN_LOOP_RESULT_STRUCT *psResult)
{
    int iErrorCode = 0;
    int iErrorLink[2] = {0, 0};
    char *psErrorText = NULL;

    int iFreq_points = 0;
    double dBw = 0.0;
    double dPh_mar = 0.0;
    double dPh_freq = 0.0;
    double dAmpl_freq = 0.0;
    double dAmpl_mar = 0.0;

    SMEE_BOOL iIf_found = SMEE_FALSE;
    /*TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,">(dServoPeriod =%f,"
										"dStart_fr =%f,"
										"dStop_fr =%f)",
										dServoPeriod,
										dStart_fr,
										dStop_fr);*/

    //计算带宽，幅值裕度，相位裕度
    if(!bSim)
    {
        if(0 == iErrorCode)
        {
            iErrorCode = GNMA_freq_size(WRGN_TRACE_DATA_NUMBER, 1, &iFreq_points);
    	        if(OK != (iErrorLink[0] = iErrorCode))
    	        {
        	        iErrorCode = WRGN_CAL_OPENLOOP_ERROR;
        	        //psErrorText = EH4A_create_text("%s: Error occurred when ME4A_freq_size!", __FUNCTION__);
        	        //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
        	        //free(psErrorText);
        	        //psErrorText = NULL;
    	         }
        }
	   if(0 == iErrorCode)
	   {
	       iErrorCode = GNMA_calc_bandwidth(bSim,
	                                       sTf_out.freq,
	                                       sTf_out.mag,
	                                       iFreq_points,
	                                       dServoPeriod,
	                                       dStart_fr,
	                                       dStop_fr,
	                                       &iIf_found,
	                                       &dBw);
            if(OK != (iErrorLink[0] = iErrorCode))
            {
                iErrorCode = WRGN_CAL_OPENLOOP_ERROR;
                //psErrorText = EH4A_create_text("%s: Error occurred when ME4A_calc_bandwidth!", __FUNCTION__);
                //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
                //free(psErrorText);
                //psErrorText = NULL;
            }
            if(0 ==iErrorCode && !iIf_found)
            {
                iErrorCode = WRGN_BANDWIDTH_NOT_FOUND_ERROR;
                if(OK != (iErrorLink[0] = iErrorCode))
                {
                    iErrorCode = WRGN_CAL_OPENLOOP_ERROR;
                    //psErrorText = EH4A_create_text("%s: Error occurred when bandwidth not found!", __FUNCTION__);
                    //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
                    //free(psErrorText);
                    //psErrorText = NULL;
                }
            }
		 if(0 == iErrorCode && iIf_found)
		 {
       	 	 psResult->dBandwidth = dBw;
           }
        }
	   if (0 == iErrorCode)
	    {
	        iErrorCode = GNMA_calc_amplitude_margin(bSim,
	                                                sTf_out.freq,
	                                                sTf_out.mag,
	                                                sTf_out.phase,
	                                                iFreq_points,
	                                                dServoPeriod,
	                                                dBw,
	                                                dStop_fr,
	                                                &iIf_found,
	                                                &dAmpl_mar,
	                                                &dAmpl_freq);
		    if(OK != (iErrorLink[0] = iErrorCode))
		    {
		        iErrorCode = WRGN_CAL_OPENLOOP_ERROR;
		        //psErrorText = EH4A_create_text("%s: Error occurred when ME4A_calc_amplitude_margin!", __FUNCTION__);
		        //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
		        //free(psErrorText);
		        //psErrorText = NULL;
		    }
	        if(0 == iErrorCode && !iIf_found)
	        {
	            iErrorCode = WRGN_AMPLTITUDE_MARGIN_NOT_FOUND_ERROR;
			    if(OK != (iErrorLink[0] = iErrorCode))
			    {
			        iErrorCode = WRGN_CAL_OPENLOOP_ERROR;
			        //psErrorText = EH4A_create_text("%s: Error occurred when AP-Margin not found!", __FUNCTION__);
			        //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
			        //free(psErrorText);
			        //psErrorText = NULL;
			    }
	        }
			if(0 == iErrorCode && iIf_found)
			{
	       		psResult->dMagnt_margin = dAmpl_mar;
			}
	    }

	    if (0 == iErrorCode)
	    {
	        iErrorCode = GNMA_calc_phase_margin(bSim,
	                                            sTf_out.freq,
	                                            sTf_out.mag,
	                                            sTf_out.phase,
	                                            iFreq_points,
	                                            dServoPeriod,
	                                            dBw,
	                                            dStop_fr,
	                                            &iIf_found,
	                                            &dPh_mar,
	                                            &dPh_freq);
		    if(OK != (iErrorLink[0] = iErrorCode))
		    {
		        iErrorCode = WRGN_CAL_OPENLOOP_ERROR;
		        //psErrorText = EH4A_create_text("%s: Error occurred when ME4A_calc_phase_margin!", __FUNCTION__);
		        //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
		        //free(psErrorText);
		        //psErrorText = NULL;
		    }
	        if(0 ==iErrorCode && !iIf_found )
	        {
	            iErrorCode = WRGN_PHASE_MARGIN_NOT_FOUND_ERROR;
			    if(OK != (iErrorLink[0] = iErrorCode))
			    {
			        iErrorCode = WRGN_CAL_OPENLOOP_ERROR;
			        //psErrorText = EH4A_create_text("%s: Error occurred when PH-Margin not found!", __FUNCTION__);
			        //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
			        //free(psErrorText);
			        //psErrorText = NULL;
			    }
	        }
			if(0 == iErrorCode && iIf_found)
			{
	        	psResult->dPhase_margin = dPh_mar;
			}
	    }
    }
    /*TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,"<(0x%x, psResult->dBandwidth =%f,"
                                                    "psResult->dMagnt_margin =%f,"
                                                    "psResult->dPhase_margin =%f)",
                                                    iErrorCode,
                                                    psResult->dBandwidth,
                                                    psResult->dMagnt_margin,
                                                    psResult->dPhase_margin);*/
    return iErrorCode;

}

int WRGN_spectrum(IN int iIndex,              //第几次计算功率谱（要和前面的 iIndex-1 次做平均）
                  IN double dServoPeriod,                    //伺服周期
                  IN double *pdDataIn,                        //输入点追到的数据
                  IN double *pdDataOut,                        //输出点追到的数据
                  OUT WRGN_SPECTRUM_STRUCT *psSpectrum,		//功率谱
                  OUT double *pdFreq)
{
    int iErrorCode = 0;
    int iErrorLink[2] = {0, 0};
    char *psErrorText = NULL;

    int iFreq_points = 0;
    double *pdPxx_temp = NULL;
    double *pdPyy_temp = NULL;
    GNMA_complex_type *psPxy_temp = NULL;

	pdPxx_temp = (double *)malloc(WRGN_TRACE_DATA_NUMBER * sizeof(double));
	pdPyy_temp = (double *)malloc(WRGN_TRACE_DATA_NUMBER * sizeof(double));
	psPxy_temp = (GNMA_complex_type *)malloc(WRGN_TRACE_DATA_NUMBER * sizeof(GNMA_complex_type));

    /*TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,">(iIndex =%d,"
                                                    "dServoPeriod = %f)",
                                                    iIndex,
                                                    dServoPeriod);*/

	//计算频率点
    if(0 == iErrorCode)
    {
        iErrorCode =  GNMA_freq_size(WRGN_TRACE_DATA_NUMBER,1,&iFreq_points);
	    if(OK != (iErrorLink[0] = iErrorCode))
	    {
	        iErrorCode = WRGN_SPECTRUM_ERROR;
	        //psErrorText = EH4A_create_text("%s: Error occurred when ME4A_freq_size!", __FUNCTION__);
	        //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
	        //free(psErrorText);
	        //psErrorText = NULL;
	    }
    }

    //计算频谱
    if(0 == iErrorCode)
    {
        iErrorCode = GNMA_spectrum(WRGN_TRACE_DATA_NUMBER,1,iFreq_points,dServoPeriod,
                                     pdDataIn,
                                     pdDataOut,
                                     pdFreq,
                                     pdPxx_temp,pdPyy_temp,psPxy_temp);
	    if(OK != (iErrorLink[0] = iErrorCode))
	    {
	        iErrorCode = WRGN_SPECTRUM_ERROR;
	        //psErrorText = EH4A_create_text("%s: Error occurred when ME4A_freq_size!", __FUNCTION__);
	        //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
	        //free(psErrorText);
	        //psErrorText = NULL;
	    }
    }
	
    //多次频谱求平均
    for (int i = 0; i < iFreq_points &&(0 == iErrorCode); i++)
    {
        psSpectrum->Pxx[i] = (psSpectrum->Pxx[i] * iIndex + pdPxx_temp[i]) / (iIndex + 1);
        psSpectrum->Pyy[i] = ( psSpectrum->Pyy[i] * iIndex + pdPyy_temp[i]) / (iIndex + 1);
        psSpectrum->Pxy[i].Re= ( psSpectrum->Pxy[i].Re* iIndex +
                                    psPxy_temp[i].Re) /(iIndex + 1);
        psSpectrum->Pxy[i].Im= ( psSpectrum->Pxy[i].Im* iIndex +
                                    psPxy_temp[i].Im) /(iIndex + 1);
    }

    /*TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,"<(0x%x,pdFreq[0] =%f,"
                                                    "pdFreq[1] =%f,"
                                                    "pdFreq[2] =%f)",
                                                    iErrorCode,
                                                    pdFreq[0],
                                                    pdFreq[1],
                                                    pdFreq[2]);*/

	free(psPxy_temp);
	free(pdPxx_temp);
	free(pdPyy_temp);

    return iErrorCode;

}
 int WRGN_bode(IN WRGN_SPECTRUM_STRUCT sSpectrum,        //功率谱
              OUT WRGN_BODE_STRUCT *psTF_Bode)       //传函（伯德图）
 {
    int iErrorCode = 0;
    int iErrorLink[2] = {0, 0};
    char *psErrorText = NULL;

	GNMA_complex_type *psComplex = NULL;
    int iFreq_points = 0;
    //TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,">()");

	psComplex = (GNMA_complex_type *)malloc(WRGN_TRACE_DATA_NUMBER * sizeof(GNMA_complex_type));

	//计算频率点
    if(0 == iErrorCode)
    {
        iErrorCode =  GNMA_freq_size(WRGN_TRACE_DATA_NUMBER,1,&iFreq_points);
	    if(OK != (iErrorLink[0] = iErrorCode))
	    {
	        iErrorCode = WRGN_BODE_ERROR;
	        //psErrorText = EH4A_create_text("%s: Error occurred when ME4A_freq_size!", __FUNCTION__);
	        //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
	        //free(psErrorText);
	        //psErrorText = NULL;
	    }
    }

    //计算伯特图
    if (0 == iErrorCode)
    {
	    for (int i = 0; i < iFreq_points &&(0 == iErrorCode); i++)
	    {
			psComplex[i].Re= sSpectrum.Pxy[i].Re;
			psComplex[i].Im= sSpectrum.Pxy[i].Im;

	    }
		iErrorCode = GNMA_transfer( iFreq_points,
									sSpectrum.Pxx,
									sSpectrum.Pyy,
									psComplex,
                                    psTF_Bode->mag,
                                    psTF_Bode->phase,
                                    psTF_Bode->cohere);
	    if(OK != (iErrorLink[0] = iErrorCode))
	    {
	        iErrorCode = WRGN_BODE_ERROR;
	        //psErrorText = EH4A_create_text("%s: Error occurred when ME4A_transfer!", __FUNCTION__);
	        //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
	        //free(psErrorText);
	        //psErrorText = NULL;
	    }
    }
    /*TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,"<(0x%x,"
                                                    "psTF_Bode->mag[0] =%f,"
                                                    "psTF_Bode->mag[1] =%f,"
                                                    "psTF_Bode->mag[2] =%f,"
                                                    "psTF_Bode->cohere[0] =%f,"
                                                    "psTF_Bode->cohere[1] =%f,"
                                                    "psTF_Bode->cohere[2] =%f,"
                                                    "psTF_Bode->cohere[0] =%f,"
                                                    "psTF_Bode->cohere[1] =%f,"
                                                    "psTF_Bode->cohere[2] =%f)",
                                                    iErrorCode,
                                                    psTF_Bode->mag[0],
                                                    psTF_Bode->mag[1],
                                                    psTF_Bode->mag[2],
                                                    psTF_Bode->phase[0],
                                                    psTF_Bode->phase[1],
                                                    psTF_Bode->phase[2],
                                                    psTF_Bode->cohere[0],
                                                    psTF_Bode->cohere[1],
                                                    psTF_Bode->cohere[2]);*/
//	free(psComplex);
	return iErrorCode;
 }
 int WRGN_measured_mass(IN double dServoPeriod,
								  IN double dFrequence_start,
								  IN double dFrequence_stop,
					              IN WRGN_BODE_STRUCT sBode,
					              OUT double *pdMeasured_mass,
					              OUT double *pdCoherance)
 {
    int iErrorCode = 0;
    int iErrorLink[2] = {0, 0};
    char *psErrorText = NULL;

    int iIndex_start = 0;
    int iIndex_stop = 0;

    double dMeasured_mass_temp_rcpc = 0.0;
    double dMagntRaw_temp = 0.0;
    double dCoher_temp = 0.0;
	double dMeasured_mass_sum = 0.0;

	SMEE_BOOL bResult = SMEE_FALSE;
    /*TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,">(dServoPeriod =%f,"
                                                        "dFrequence_start =%f,"
                                                        "dFrequence_stop =%f)",
                                                        dServoPeriod,
                                                        dFrequence_start,
                                                        dFrequence_stop);*/
    //计算指定频率点对应的频率数组的编号
    iIndex_start = (int)(dFrequence_start * dServoPeriod * WRGN_TRACE_DATA_NUMBER);//fi=i/T
    iIndex_stop = (int)(dFrequence_stop * dServoPeriod * WRGN_TRACE_DATA_NUMBER);//fi=i/T

	for(int i = iIndex_start;i <= iIndex_stop; i++)
	{
		//将辐值由分贝还原为倍数A=20lg(B),以便求测量质量
	    dMagntRaw_temp = pow(1.0e1, sBode.mag[i] / 2.0e1);

	    dCoher_temp += sBode.cohere[i];

	    //计算"测量质量"的倒数（2Pi*f）*（2Pi*f）*H（f）
	    dMeasured_mass_temp_rcpc = pow(2 * WRGN_PI * sBode.freq[i], 2.0) * dMagntRaw_temp;
        if (fabs(fabs(dMeasured_mass_temp_rcpc)) < 4.450147717014403e-308)
        {
             bResult = SMEE_TRUE;
        }
        else
        {
            bResult = SMEE_FALSE;
        }
	    if (0 == iErrorCode && bResult)
	    {
	        iErrorCode = WRGN_MEASURED_MASS_IS_ZERO_ERROR;
		    if(OK != (iErrorLink[0] = iErrorCode))
		    {
		        iErrorCode = WRGN_MEASURED_MASS_ERROR;
		        //psErrorText = EH4A_create_text("%s: Error occurred when mass is ZERO!", __FUNCTION__);
		        //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
		        //free(psErrorText);
		        //psErrorText = NULL;
		    }
	    }

	    if(0 == iErrorCode && !bResult)
	    {
	         dMeasured_mass_sum += 1.0 / dMeasured_mass_temp_rcpc;
   			 //TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,">(dMeasured_mass_sum =%f,",dMeasured_mass_sum);
	    }
	}
	if(0 == iErrorCode)
	{
		*pdMeasured_mass = dMeasured_mass_sum / (iIndex_stop - iIndex_start + 1);
		*pdCoherance = dCoher_temp / (iIndex_stop - iIndex_start + 1);
	}

    /*TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,"<(0x%x,"
														"iIndex_start = %d,"
                                                        "iIndex_stop= %d,"
                                                        "pdMeasured_mass =%f,"
                                                        "pdCoherance =%f)",
                                                        iErrorCode,
                                                        iIndex_start,
                                                        iIndex_stop,
                                                        *pdMeasured_mass,
                                                        *pdCoherance);*/
    return iErrorCode;

 }

 int WRGN_norm_random_error(IN double dCoherence,
			               IN int iTest_Number,
			               OUT double *pdNRE)
 {
    int iErrorCode = 0;
    int iErrorLink[2] = {0, 0};
    char *psErrorText = NULL;

    double dNRE_temp = 0.;

	/*TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,">(dCoherence =%f,iTest_Number =%d",
												dCoherence,
												iTest_Number);*/
    if(0.0 == dCoherence)
    {
        iErrorCode = WRGN_PARAM_ERROR;
	    if(OK != (iErrorLink[0] = iErrorCode))
	    {
	        iErrorCode = WRGN_NORM_RANDOM_ERROR_FAILED;
	        //psErrorText = EH4A_create_text("%s: Error occurred when input Coherence is ZERO!", __FUNCTION__);
	        //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
	        //free(psErrorText);
	        //psErrorText = NULL;
	    }
    }

    if (0 == iErrorCode && 0 >= iTest_Number)
    {
        iErrorCode = WRGN_NORM_RANDOM_ERROR_FAILED;
	    if(OK != (iErrorLink[0] = iErrorCode))
	    {
	        iErrorCode = WRGN_NORM_RANDOM_ERROR_FAILED;
	        //psErrorText = EH4A_create_text("%s: Error occurred when input times is ZERO!", __FUNCTION__);
	        //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
	        //free(psErrorText);
	        //psErrorText = NULL;
	    }
    }

    if (0 == iErrorCode)
    {
        dNRE_temp = (1.0 / dCoherence - 1.0) * (1.0 / (2 * iTest_Number));

        if (dNRE_temp < 0)    //开根号的数是否小于0；
        {
            iErrorCode = WRGN_NRE_LESS_THAN_ZERO;
		    if(OK != (iErrorLink[0] = iErrorCode))
		    {
		        iErrorCode = WRGN_NORM_RANDOM_ERROR_FAILED;
		        //psErrorText = EH4A_create_text("%s: Error occurred when nre is less than ZERO!", __FUNCTION__);
		        //EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
		        //free(psErrorText);
		        //psErrorText = NULL;
		    }
        }
        if (0 == iErrorCode)
        {
            *pdNRE = sqrt(dNRE_temp);
        }
    }

    //TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,"<(0x%x,*pdNRE =%f)",iErrorCode,*pdNRE);
    return iErrorCode;

 }
int WRGN_cal_stable_err(IN double dPos_err[WRGN_TRACE_DATA_NUMBER],
								IN int iUpdate_rate,
								IN double dServoPeriod,
								IN double dSettling_time,
								OUT	double *pdMean,
								OUT double *pd3Sigma)

{
	int iErrorCode = 0;
	int iErrorLink[2] = {0, 0};
	char *psErrorText = NULL;

	double dSigma = 0.;
	double dMean_temp = 0.;

//	int i = WRGN_TRACE_DATA_NUMBER;
	int iSettling_time_start = 0;
	int iStart = 0;

	/*TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,">(iUpdate_rate = %d,"
												"dSettling_time = %f)",
												iUpdate_rate,
												dSettling_time);*/

	iSettling_time_start = 0;

	//找到调节时间过后的点
	iStart = iSettling_time_start + (int)(dSettling_time /
							(iUpdate_rate * dServoPeriod));
	if(iStart >= WRGN_TRACE_DATA_NUMBER)
	{
		iErrorCode = WRGN_STABLE_TIME_TOO_LONG_ERROR;
		//iErrorLink[0] = WRGN_STABLE_TIME_TOO_LONG_ERROR;
		//psErrorText = EH4A_create_text("%s: Error occurred when settling time is too long!", __FUNCTION__);
		//EH4A_log_error(WRGN_CAL_STABLE_ERROR, iErrorLink, psErrorText, __FILE__, __LINE__);
		//free(psErrorText);
		//psErrorText = NULL;
	}
	//计算均值，Sigma值
	if(0 == iErrorCode)
	{
		iErrorLink[0] = GNMA_average_value(&dPos_err[iStart],
											(WRGN_TRACE_DATA_NUMBER-iStart),
											sizeof(double),
											&dMean_temp,
											&dSigma);
		if(OK !=  iErrorLink[0])
		{
			iErrorCode = WRGN_CAL_STABLE_ERROR;
			//psErrorText = EH4A_create_text("%s: Error occurred when cal max pos err!", __FUNCTION__);
			//EH4A_log_error(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
			//free(psErrorText);
			//psErrorText = NULL;
		}
		*pdMean = dMean_temp;
		*pd3Sigma = dSigma * 3;
	}
	/*TR4A_trace("HW", TR4A_TRACE_INT, __FUNCTION__, "<(0x%x,iStart = %d,"
													"iSettling_time_start = %d,"
													"Mean = %f,"
													"3Sigma = %f)",
													iErrorCode,
													iStart,iSettling_time_start,
													*pdMean,*pd3Sigma);*/
	return iErrorCode;
}

int WRGN_cal_setting_time(IN double dPos_err[WRGN_TRACE_DATA_NUMBER],
						IN double dServoPeriod,
						IN double dError_window,
						IN int iUpdate_rate,
						OUT double *pdSettling_time)
{
	int iErrorCode = 0;
	int iErrorLink[2] = {0, 0};
	char *psErrorText = NULL;
	/*TR4A_trace("HW",TR4A_TRACE_INT,__FUNCTION__,">(dError_window = %f,"
													"iUpdate_rate = %d)",
													dError_window,
													iUpdate_rate);*/
	int iStart = 0;

	//根据给定的稳态误差指标计算调节时间
	int i = WRGN_TRACE_DATA_NUMBER;
	if(fabs(dPos_err[2047]) >= dError_window)
	{
		iErrorCode = WRGN_REACH_SET_ERR_WINDOW_FAILED;
		//iErrorLink[0] = WRGN_REACH_SET_ERR_WINDOW_FAILED;
		//psErrorText = EH4A_create_text("%s: Error occurred when error_window is too small!", __FUNCTION__);
		//EH4A_log_error(WRGN_CAL_SETTLING_TIME_ERROR, iErrorLink, psErrorText, __FILE__, __LINE__);
		//free(psErrorText);
		//psErrorText = NULL;
	}

	while(i > iStart && fabs(dPos_err[i - 1]) < dError_window)
	{
		i--;
	}

	*pdSettling_time = (i- iStart) * iUpdate_rate * dServoPeriod;
	/*TR4A_trace("HW", TR4A_TRACE_INT, __FUNCTION__, "<0x%x,Start = %d,"
        										"Index = %d,"
        										"pdSettling_time = %f)",
        										iErrorCode,
        										iStart,
        										i,
        										*pdSettling_time);*/
	return iErrorCode;
}

const char * WRbool2str(const SMEE_BOOL &t)
{
    return (t ? "SMEE_TRUE" : "SMEE_FALSE");
}

const char * WRbool2str(const SMEE_BOOL *t)
{
    return (*t ? "SMEE_TRUE" : "SMEE_FALSE");
}


