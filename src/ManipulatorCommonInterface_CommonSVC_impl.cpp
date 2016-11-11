// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_CommonSVC_impl.cpp
 * @brief Service implementation code of ManipulatorCommonInterface_Common.idl
 *
 */

#include "ManipulatorCommonInterface_CommonSVC_impl.h"
#include "defreturnid.h"
#include "defcommand.h"
#include "useORiN.h"
#include <string>

/*
 * Example implementational code for IDL interface JARA_ARM::ManipulatorCommonInterface_Common
 */
ManipulatorCommonInterface_CommonSVC_impl::ManipulatorCommonInterface_CommonSVC_impl()
{
  // Please add extra constructor code here.
}


ManipulatorCommonInterface_CommonSVC_impl::~ManipulatorCommonInterface_CommonSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
JARA_ARM::RETURN_ID* ManipulatorCommonInterface_CommonSVC_impl::clearAlarms()
{
	std::cout<<"ƒAƒ‰[ƒ€‰ðœ"<<std::endl;
	if(strcmp(C1_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		
		VariantInit(&variant_param);
		variant_param.vt = VT_BSTR | VT_ARRAY;
		SAFEARRAYBOUND bound = {1,0};
		variant_param.parray = SafeArrayCreate(VT_BSTR,1,&bound);
		BSTR* iarray;
		SafeArrayAccessData(variant_param.parray,(void**)&iarray);
		iarray[0] = SysAllocString(L"");
		SafeArrayUnaccessData(variant_param.parray);
		
		hr = pCtrl->Execute(CComBSTR(C1_Command),variant_param,&variant_pVal);

		VariantClear(&variant_param);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"yŽ¸”sz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		ORiNDeactivate();
		std::cout<<"y¬Œ÷z"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_CommonSVC_impl::getActiveAlarm(JARA_ARM::AlarmSeq_out alarms)
{
	std::cout<<"ƒAƒ‰[ƒ€î•ñ‚ÌŽæ“¾"<<std::endl;
	if(strcmp(C2_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"yŽ¸”sz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		ORiNDeactivate();
		std::cout<<"y¬Œ÷z"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_CommonSVC_impl::getFeedbackPosJoint(JARA_ARM::JointPos_out pos)
{
	std::cout<<"ŠÖßÀ•WŒn‚ÌˆÊ’uƒtƒB[ƒhƒoƒbƒNî•ñ‚ÌŽæ“¾"<<std::endl;
	if(strcmp(C3_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();

		hr = pRobot->AddVariable(CComBSTR(C3_Command),CComBSTR(L""),&pPosJ);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"yŽ¸”sz: "<<hr<<std::endl;
			RETURNID_NG;
		}

		pos=new JARA_ARM::JointPos;
		pos->length(AxisNum);
		VariantInit( &variant_pVal );
		variant_pVal.vt=VT_R4|VT_ARRAY;
		SAFEARRAYBOUND bound = {AxisNum,0};
		variant_pVal.parray = SafeArrayCreate(VT_R4,1,&bound);
		hr = pPosJ->get_Value(&variant_pVal);
		float* iArray;
		SafeArrayAccessData(variant_pVal.parray , (void**)&iArray);
		for(int i=0;i<AxisNum;i++){
			if(strcmp(AxialType[i],"rotation") == 0){
				(*pos)[i]=iArray[i]*M_PI/180.0;//[deg]->[rad]•ÏŠ·
			}else if(strcmp(AxialType[i],"linear") == 0){
				(*pos)[i]=iArray[i]/1000.0;//[mm]->[m]•ÏŠ·
			}
		}
		SafeArrayUnaccessData(variant_pVal.parray);
		VariantClear(&variant_pVal);

		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"yŽ¸”sz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		if(pPosJ) pPosJ->Release();
		ORiNDeactivate();
		std::cout<<"y¬Œ÷z"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_CommonSVC_impl::getManipInfo(JARA_ARM::ManipInfo_out mInfo)
{
	std::cout<<"ƒ}ƒjƒsƒ…ƒŒ[ƒ^î•ñ‚ÌŽæ“¾"<<std::endl;
	if(strcmp(C4_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		mInfo=new JARA_ARM::ManipInfo;
		mInfo->manufactur=(const char*)Manufactur;
		mInfo->type = (const char*)RobotName;
		mInfo->axisNum=AxisNum;
		mInfo->isGripper=IsGripper;
		std::cout<<"y¬Œ÷z"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_CommonSVC_impl::getSoftLimitJoint(JARA_ARM::LimitSeq_out softLimit)
{
	std::cout<<"ŠÖßÀ•WŒn‚Ìƒ\ƒtƒgƒŠƒ~ƒbƒg’l‚ðŽæ“¾"<<std::endl;
	if(strcmp(C5_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		softLimit=new JARA_ARM::LimitSeq;
		softLimit->length(AxisNum);
		for(int i=0;i<AxisNum;i++){
			(*softLimit)[i].upper=JUpperLimit[i];
			(*softLimit)[i].lower=JLowerLimit[i];
		}
		std::cout<<"y¬Œ÷z"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_CommonSVC_impl::getState(ULONG& state)
{
	std::cout<<"ƒ†ƒjƒbƒg‚Ìó‘ÔŽæ“¾"<<std::endl;
	if(strcmp(C6_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		m_state=0x00;
		//ƒT[ƒ{ó‘ÔŽæ“¾
		ORiNActivate();
		hr = pRobot->AddVariable(CComBSTR(C6_Command),CComBSTR(L""),&pServo);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"yŽ¸”sz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		VariantInit( &variant_pVal );
		if(strcmp(CaoProvName,"CaoProv.YAMAHA.RCX") == 0){//YAMAHA RCX
			variant_pVal.vt=VT_BSTR;
			hr = pServo->get_Value(&variant_pVal);
			char ServoState[]="OFF";
			WideCharToMultiByte(CP_ACP,0,(OLECHAR*)variant_pVal.bstrVal,-1,ServoState,sizeof(ServoState) - 1,NULL,NULL);
			std::cout<<"yServoStatez: "<<ServoState<<std::endl;
			if(strncmp(ServoState,"ON",2) == 0){
				std::cout<<"yONz"<<std::endl;
				m_state|=0x01;
			}
			VariantClear(&variant_pVal);
		}else {
			variant_pVal.vt=VT_BOOL;
			hr = pServo->get_Value(&variant_pVal);
			bool ServoState = variant_pVal.boolVal;
			std::cout<<"yServoStatez: "<<ServoState<<std::endl;
			if(ServoState == true){
				std::cout<<"yONz"<<std::endl;
				m_state|=0x01;
			}
			VariantClear(&variant_pVal);
		}

		if(FAILED(hr)){
				std::cout.setf(std::ios::hex,std::ios::basefield);
				std::cout.setf(std::ios::showbase);
				std::cout<<"yŽ¸”sz: "<<hr<<std::endl;
				RETURNID_NG;
		}
		if(pServo) pServo->Release();
		ORiNDeactivate();
		state=stateData();
		std::cout<<"y¬Œ÷z"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_CommonSVC_impl::servoOFF()
{
	std::cout<<"‘SŽ²ƒT[ƒ{OFF"<<std::endl;
	if(strcmp(C7_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		VariantInit(&variant_param);
		variant_param.vt = VT_BSTR | VT_ARRAY;
		SAFEARRAYBOUND bound = {1,0};
		variant_param.parray = SafeArrayCreate(VT_BSTR,1,&bound);
		BSTR* iarray;
		SafeArrayAccessData(variant_param.parray,(void**)&iarray);
		iarray[0] = _com_util::ConvertStringToBSTR(C7_Option);
		SafeArrayUnaccessData(variant_param.parray);
		hr = pRobot->Execute(CComBSTR(C7_Command),variant_param,&variant_pVal);
		VariantClear(&variant_param);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"yŽ¸”sz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		ORiNDeactivate();
		std::cout<<"y¬Œ÷z"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_CommonSVC_impl::servoON()
{
	std::cout<<"‘SŽ²ƒT[ƒ{ON"<<std::endl;
	if(strcmp(C8_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		VariantInit(&variant_param);
		variant_param.vt = VT_BSTR | VT_ARRAY;
		SAFEARRAYBOUND bound = {1,0};
		variant_param.parray = SafeArrayCreate(VT_BSTR,1,&bound);
		BSTR* iarray;
		SafeArrayAccessData(variant_param.parray,(void**)&iarray);
		iarray[0] = _com_util::ConvertStringToBSTR(C8_Option);
		SafeArrayUnaccessData(variant_param.parray);
		hr = pRobot->Execute(CComBSTR(C8_Command),variant_param,&variant_pVal);
		VariantClear(&variant_param);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"yŽ¸”sz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		ORiNDeactivate();
		std::cout<<"y¬Œ÷z"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_CommonSVC_impl::setSoftLimitJoint(const JARA_ARM::LimitSeq& softLimit)
{
	std::cout<<"ŠÖßÀ•WŒn‚Ìƒ\ƒtƒgƒŠƒ~ƒbƒg’lÝ’è"<<std::endl;
	if(strcmp(C9_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		for(int i=0;i<AxisNum;i++){
			JUpperLimit[i]=softLimit[i].upper;
			JLowerLimit[i]=softLimit[i].lower;
		}
		std::cout<<"y¬Œ÷z"<<std::endl;
		RETURNID_OK;
	}
}



// End of example implementational code



