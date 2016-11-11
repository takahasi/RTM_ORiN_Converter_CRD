// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_MiddleLevelSVC_impl.cpp
 * @brief Service implementation code of ManipulatorCommonInterface_MiddleLevel.idl
 *
 */

#include "ManipulatorCommonInterface_MiddleLevelSVC_impl.h"
#include "defreturnid.h"
#include "defcommand.h"
#include "useORiN.h"

/*
 * Example implementational code for IDL interface JARA_ARM::ManipulatorCommonInterface_Middle
 */
ManipulatorCommonInterface_MiddleSVC_impl::ManipulatorCommonInterface_MiddleSVC_impl()
{
  // Please add extra constructor code here.

}


ManipulatorCommonInterface_MiddleSVC_impl::~ManipulatorCommonInterface_MiddleSVC_impl()
{
  // Please add extra destructor code here.
}

void RobotMove(int movetype){
	VariantInit(&variant_pose);
	variant_pose.vt = VT_BSTR;
	//É}ÉbÉvå≥ï∂éöóÒÇÃÉAÉhÉåÉXë„ì¸
	lstr=char_buffer;
	//BSTRÇ…ïKóvÇ»ÉoÉbÉtÉ@ÉTÉCÉYÇãÅÇﬂÇÈ
	bstrlen=(int)MultiByteToWideChar(CP_ACP,0,lstr,strlen(lstr),NULL,0);
	//ÉoÉbÉtÉ@Çämï€Ç∑ÇÈ
	variant_pose.bstrVal=SysAllocStringLen(NULL,bstrlen);
	//BSTRÇ…ï°êª
	MultiByteToWideChar(CP_ACP,0,lstr,strlen(lstr),variant_pose.bstrVal,bstrlen);
	hr = pRobot->Move(movetype,variant_pose,SysAllocString(L""));
	VariantClear(&variant_pose);
}

/*
 * Methods corresponding to IDL attributes and operations
 */
JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::closeGripper()
{
	std::cout<<"ÉOÉäÉbÉpÇï¬Ç∂ÇÈ"<<std::endl;
	RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::getBaseOffset(JARA_ARM::HgMatrix offset)
{
	std::cout<<"É}ÉjÉsÉÖÉåÅ[É^ÇÃê›íËà íuÇéÊìæ"<<std::endl;
	if(strcmp(M2_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::getFeedbackPosCartesian(JARA_ARM::CarPosWithElbow& pos)
{
	std::cout<<"íºåç¿ïWånÇÃà íuÉtÉBÅ[ÉhÉoÉbÉNèÓïÒÇÃéÊìæ"<<std::endl;
	if(strcmp(M3_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		hr = pRobot->AddVariable(CComBSTR(M3_Command),CComBSTR(L""),&pPosC);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		double CPos[6];
		for(int i=0;i<6;i++){
			CPos[i]=0.00;
		}
		VariantInit( &variant_pVal );
		variant_pVal.vt=VT_R4|VT_ARRAY;
		SAFEARRAYBOUND bound = {AxisNum,0};
		variant_pVal.parray = SafeArrayCreate(VT_R4,1,&bound);
		hr = pPosC->get_Value(&variant_pVal);
		float* iArray;
		SafeArrayAccessData(variant_pVal.parray , (void**)&iArray);
		if(AxisNum<=3){
			for(int i=0;i<AxisNum;i++){
				std::cout<<"Åy"<<iArray[i]<<"Åz"<<std::endl;
				CPos[i]=iArray[i]/1000.0;//[mm]->[m]
			}
		}else{
			for(int i=0;i<3;i++){
				std::cout<<"Åy"<<iArray[i]<<"Åz"<<std::endl;
				CPos[i]=iArray[i]/1000.0;//[mm]->[m]
			}
			for(int i=3;i<6;i++){
				std::cout<<"Åy"<<iArray[i]<<"Åz"<<std::endl;
				CPos[i]=iArray[i]*M_PI/180.0;
			}
		}
		SafeArrayUnaccessData(variant_pVal.parray);
		VariantClear(&variant_pVal);

		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		if(pPosC) pPosC->Release();
		ORiNDeactivate();

		//âÒì]èáèòÇÕA->B->C
		//1çsñ⁄
		pos.carPos[0][0]=cos(CPos[5])*cos(CPos[4]);
		pos.carPos[0][1]=sin(CPos[5])*cos(CPos[4]);
		pos.carPos[0][2]=-sin(CPos[4]);
		pos.carPos[0][3]=CPos[0];

		//2çsñ⁄
		pos.carPos[1][0]=-sin(CPos[5])*cos(CPos[3])+cos(CPos[5])*sin(CPos[4])*sin(CPos[3]);
		pos.carPos[1][1]=cos(CPos[5])*cos(CPos[3])+sin(CPos[5])*sin(CPos[4])*sin(CPos[3]);
		pos.carPos[1][2]=cos(CPos[4])*sin(CPos[3]);
		pos.carPos[1][3]=CPos[1];

		//3çsñ⁄
		pos.carPos[2][0]=sin(CPos[5])*sin(CPos[3])+cos(CPos[5])*sin(CPos[4])*cos(CPos[3]);
		pos.carPos[2][1]=-cos(CPos[5])*sin(CPos[3])+sin(CPos[5])*sin(CPos[4])*cos(CPos[3]);
		pos.carPos[2][2]=cos(CPos[4])*cos(CPos[3]);
		pos.carPos[2][3]=CPos[2];

		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::getMaxSpeedCartesian(JARA_ARM::CartesianSpeed& speed)
{
	std::cout<<"íºåìÆçÏéûÇÃç≈ëÂìÆçÏë¨ìxÇéÊìæ"<<std::endl;
	if(strcmp(M4_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		hr = pRobot->AddVariable(CComBSTR(M4_Command),CComBSTR(L""),&pSPEED);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		speed.rotation=0.0;
		speed.translation=0.0;
		VariantInit( &variant_pVal );
		variant_pVal.vt=VT_BSTR|VT_ARRAY;
		SAFEARRAYBOUND bound = {2,0};
		variant_pVal.parray = SafeArrayCreate(VT_BSTR,1,&bound);
		hr = pSPEED->get_Value(&variant_pVal);
		BSTR* iArray;
		SafeArrayAccessData(variant_pVal.parray , (void**)&iArray);
		WideCharToMultiByte(CP_ACP,0,(OLECHAR*)iArray[1],-1,char_buffer,sizeof(iArray[1]) - 1,NULL,NULL);
		speed.translation = atoi(char_buffer);
		SafeArrayUnaccessData(variant_pVal.parray);
		VariantClear(&variant_pVal);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		if(pSPEED) pSPEED->Release();
		ORiNDeactivate();
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::getMaxSpeedJoint(JARA_ARM::DoubleSeq_out speed)
{
	std::cout<<"ä÷êﬂìÆçÏéûÇÃç≈ëÂìÆçÏë¨ìxÇéÊìæ"<<std::endl;
	if(strcmp(M5_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		speed=new JARA_ARM::DoubleSeq;
		speed->length(1);
		hr = pRobot->AddVariable(CComBSTR(M5_Command),CComBSTR(L""),&pJSPEED);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		VariantInit( &variant_pVal );
		variant_pVal.vt=VT_BSTR|VT_ARRAY;
		SAFEARRAYBOUND bound = {2,0};
		variant_pVal.parray = SafeArrayCreate(VT_BSTR,1,&bound);
		hr = pJSPEED->get_Value(&variant_pVal);
		BSTR* iArray;
		SafeArrayAccessData(variant_pVal.parray , (void**)&iArray);
		WideCharToMultiByte(CP_ACP,0,(OLECHAR*)iArray[1],-1,char_buffer,sizeof(iArray[1]) - 1,NULL,NULL);
		(*speed)[0] = atoi(char_buffer);
		SafeArrayUnaccessData(variant_pVal.parray);
		VariantClear(&variant_pVal);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		if(pJSPEED) pJSPEED->Release();
		ORiNDeactivate();
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::getMinAccelTimeCartesian(CORBA::Double& aclTime)
{
	std::cout<<"íºåìÆçÏéûÇÃç≈è¨ìÆçÏâ¡ë¨ë¨ìxÇéÊìæ"<<std::endl;
	if(strcmp(M6_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		aclTime=CMinAccelTime;
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::getMinAccelTimeJoint(CORBA::Double& aclTime)
{
	std::cout<<"ä÷êﬂìÆçÏéûÇÃç≈è¨ìÆçÏâ¡ë¨ë¨ìxÇéÊìæ"<<std::endl;
	if(strcmp(M7_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		aclTime=JMinAccelTime;
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::getSoftLimitCartesian(JARA_ARM::LimitValue& xLimit, JARA_ARM::LimitValue& yLimit, JARA_ARM::LimitValue& zLimit)
{
	std::cout<<"íºåç¿ïWånÇÃÉ\ÉtÉgÉäÉ~ÉbÉgílÇéÊìæ"<<std::endl;
	if(strcmp(M8_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		xLimit.upper=CUpperLimit[0];
		yLimit.upper=CUpperLimit[1];
		zLimit.upper=CUpperLimit[2];
		xLimit.lower=CLowerLimit[0];
		yLimit.lower=CLowerLimit[1];
		zLimit.lower=CLowerLimit[2];
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::moveGripper(ULONG angleRatio)
{
	std::cout<<"ÉOÉäÉbÉpÇÃäJï¬ìÆçÏ"<<std::endl;
	RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::moveLinearCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint)
{
	std::cout<<"íºåç¿ïWånÇÃíºê¸ï‚ä‘(ê‚ëŒéwóﬂ)"<<std::endl;
	if(strcmp(M10_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else if(AxisNum <= 3){
		std::cout<<"NG"<<std::endl;
		RETURNID_NG;
	}else{

		//É\ÉtÉgÉäÉ~ÉbÉg
		if((carPoint.carPos[0][3]<CLowerLimit[0])||(carPoint.carPos[0][3]>CUpperLimit[0])||(carPoint.carPos[1][3]<CLowerLimit[1])||(carPoint.carPos[1][3]>CUpperLimit[1])||(carPoint.carPos[2][3]<CLowerLimit[2])||(carPoint.carPos[2][3]>CUpperLimit[2])){
			std::cout<<"VALUE_ERR"<<std::endl;
			RETURNID_VALUE_ERR;
		}else{
			CPoint[0]=carPoint.carPos[0][3]*1000.0;//x[m]->[mm]
			CPoint[1]=carPoint.carPos[1][3]*1000.0;//y[m]->[mm]
			CPoint[2]=carPoint.carPos[2][3]*1000.0;//z[m]->[mm]
			CPoint[4]=asin(-carPoint.carPos[0][2])*180.0/M_PI;
			if(fabs(CPoint[4])==90){
				CPoint[3]=0.0;//A
				CPoint[5]=atan2(carPoint.carPos[1][1],carPoint.carPos[0][1])*180.0/M_PI;//C
			}else{
				CPoint[3]=atan2(carPoint.carPos[1][2],carPoint.carPos[2][2])*180.0/M_PI;//A
				CPoint[5]=atan2(carPoint.carPos[0][1],carPoint.carPos[0][0])*180.0/M_PI;//C
			}
			
			if(carPoint.structFlag == 1){
				CFlag=carPoint.structFlag;
			}else{
				CFlag=5;
			}
			
			ORiNActivate();
			//ñ⁄ïWç¿ïWÇÃï∂éöóÒïœä∑
			sprintf(char_buffer,M10_Command,CPoint[0],CPoint[1],CPoint[2],CPoint[3],CPoint[4],CPoint[5],CFlag);
			//ÉçÉ{ÉbÉgìÆçÏ
			RobotMove(2);
			if(FAILED(hr)){
				std::cout.setf(std::ios::hex,std::ios::basefield);
				std::cout.setf(std::ios::showbase);
				std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
				RETURNID_NG;
			}
			ORiNDeactivate();
			std::cout<<"Åyê¨å˜Åz"<<std::endl;
			RETURNID_OK;

		}
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::moveLinearCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint)
{
	std::cout<<"íºåç¿ïWånÇÃíºê¸ï‚ä‘(ëäëŒéwóﬂ)"<<std::endl;
	if((strcmp(M11_Command,"NOT_IMPLEMENTED") == 0)||(strcmp(M3_Command,"NOT_IMPLEMENTED") == 0)){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else if(AxisNum <= 3){
		std::cout<<"NG"<<std::endl;
		RETURNID_NG;
	}else{
		
		CPoint[0]=carPoint.carPos[0][3]*1000.0;//x[m]->[mm]
		CPoint[1]=carPoint.carPos[1][3]*1000.0;//y[m]->[mm]
		CPoint[2]=carPoint.carPos[2][3]*1000.0;//z[m]->[mm]
		CPoint[4]=asin(-carPoint.carPos[0][2])*180.0/M_PI;
		if(fabs(CPoint[4])==90){
			CPoint[3]=0.0;//A
			CPoint[5]=atan2(carPoint.carPos[1][1],carPoint.carPos[0][1])*180.0/M_PI;//C
		}else{
			CPoint[3]=atan2(carPoint.carPos[1][2],carPoint.carPos[2][2])*180.0/M_PI;//A
			CPoint[5]=atan2(carPoint.carPos[0][1],carPoint.carPos[0][0])*180.0/M_PI;//C
		}
		
		if(carPoint.structFlag == 1){
			CFlag=carPoint.structFlag;
		}else{
			CFlag=5;
		}

		//åªç›íléÊìæ
		ORiNActivate();
		hr = pRobot->AddVariable(CComBSTR(M3_Command),CComBSTR(L""),&pPosC);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		VariantInit( &variant_pVal );
		variant_pVal.vt=VT_R4|VT_ARRAY;
		SAFEARRAYBOUND bound = {AxisNum,0};
		variant_pVal.parray = SafeArrayCreate(VT_R4,1,&bound);
		hr = pPosC->get_Value(&variant_pVal);
		float* iArray;
		SafeArrayAccessData(variant_pVal.parray , (void**)&iArray);
		for(int i=0;i<6;i++){
			std::cout<<"Åy"<<iArray[i]<<"Åz"<<std::endl;
			CPoint[i]=CPoint[i]+iArray[i];
		}
		SafeArrayUnaccessData(variant_pVal.parray);
		VariantClear(&variant_pVal);

		//É\ÉtÉgÉäÉ~ÉbÉg
		if((CPoint[0]<CLowerLimit[0]*1000.0)||(CPoint[0]>CUpperLimit[0]*1000.0)||(CPoint[1]<CLowerLimit[1]*1000.0)||(CPoint[1]>CUpperLimit[1]*1000.0)||(CPoint[2]<CLowerLimit[2]*1000.0)||(CPoint[2]>CUpperLimit[2]*1000.0)){
			std::cout<<"VALUE_ERR"<<std::endl;
			RETURNID_VALUE_ERR;
		}else{
				
			//ñ⁄ïWç¿ïWÇÃï∂éöóÒïœä∑
			sprintf(char_buffer,M11_Command,CPoint[0],CPoint[1],CPoint[2],CPoint[3],CPoint[4],CPoint[5],CFlag);
			//ÉçÉ{ÉbÉgìÆçÏ
			RobotMove(2);
			if(FAILED(hr)){
				std::cout.setf(std::ios::hex,std::ios::basefield);
				std::cout.setf(std::ios::showbase);
				std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
				RETURNID_NG;
			}
			if(pPosC) pPosC->Release();
			ORiNDeactivate();
			std::cout<<"Åyê¨å˜Åz"<<std::endl;
			RETURNID_OK;

		}
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::movePTPCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint)
{
	std::cout<<"ä÷êﬂç¿ïWånÇÃíºê¸ï‚ä‘(íºåÅEê‚ëŒéwóﬂ)"<<std::endl;
	if(strcmp(M12_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else if(AxisNum <= 3){
		std::cout<<"NG"<<std::endl;
		RETURNID_NG;
	}else{
		//É\ÉtÉgÉäÉ~ÉbÉg
		if((carPoint.carPos[0][3]<CLowerLimit[0])||(carPoint.carPos[0][3]>CUpperLimit[0])||(carPoint.carPos[1][3]<CLowerLimit[1])||(carPoint.carPos[1][3]>CUpperLimit[1])||(carPoint.carPos[2][3]<CLowerLimit[2])||(carPoint.carPos[2][3]>CUpperLimit[2])){
			std::cout<<"VALUE_ERR"<<std::endl;
			RETURNID_VALUE_ERR;
		}else{
			CPoint[0]=carPoint.carPos[0][3]*1000.0;//x[m]->[mm]
			CPoint[1]=carPoint.carPos[1][3]*1000.0;//y[m]->[mm]
			CPoint[2]=carPoint.carPos[2][3]*1000.0;//z[m]->[mm]
			CPoint[4]=asin(-carPoint.carPos[0][2])*180.0/M_PI;
			if(fabs(CPoint[4])==90){
				CPoint[3]=0.0;//A
				CPoint[5]=atan2(carPoint.carPos[1][1],carPoint.carPos[0][1])*180.0/M_PI;//C
			}else{
				CPoint[3]=atan2(carPoint.carPos[1][2],carPoint.carPos[2][2])*180.0/M_PI;//A
				CPoint[5]=atan2(carPoint.carPos[0][1],carPoint.carPos[0][0])*180.0/M_PI;//C
			}
			
			if(carPoint.structFlag == 1){
				CFlag=carPoint.structFlag;
			}else{
				CFlag=5;
			}
			ORiNActivate();
			//ñ⁄ïWç¿ïWÇÃï∂éöóÒïœä∑
			sprintf(char_buffer,M12_Command,CPoint[0],CPoint[1],CPoint[2],CPoint[3],CPoint[4],CPoint[5],CFlag);
			//ÉçÉ{ÉbÉgìÆçÏ
			RobotMove(1);
			if(FAILED(hr)){
				std::cout.setf(std::ios::hex,std::ios::basefield);
				std::cout.setf(std::ios::showbase);
				std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
				RETURNID_NG;
			}
			ORiNDeactivate();
			std::cout<<"Åyê¨å˜Åz"<<std::endl;
			RETURNID_OK;
		}
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::movePTPCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint)
{
	std::cout<<"ä÷êﬂç¿ïWånÇÃíºê¸ï‚ä‘(íºåÅEëäëŒéwóﬂ)"<<std::endl;
	if((strcmp(M13_Command,"NOT_IMPLEMENTED") == 0)||(strcmp(M3_Command,"NOT_IMPLEMENTED") == 0)){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else if(AxisNum <= 3){
		std::cout<<"NG"<<std::endl;
		RETURNID_NG;
	}else{
		
		CPoint[0]=carPoint.carPos[0][3]*1000.0;//x[m]->[mm]
		CPoint[1]=carPoint.carPos[1][3]*1000.0;//y[m]->[mm]
		CPoint[2]=carPoint.carPos[2][3]*1000.0;//z[m]->[mm]
		CPoint[4]=asin(-carPoint.carPos[0][2])*180.0/M_PI;
		if(fabs(CPoint[4])==90){
			CPoint[3]=0.0;//A
			CPoint[5]=atan2(carPoint.carPos[1][1],carPoint.carPos[0][1])*180.0/M_PI;//C
		}else{
			CPoint[3]=atan2(carPoint.carPos[1][2],carPoint.carPos[2][2])*180.0/M_PI;//A
			CPoint[5]=atan2(carPoint.carPos[0][1],carPoint.carPos[0][0])*180.0/M_PI;//C
		}
		
		if(carPoint.structFlag == 1){
			CFlag=carPoint.structFlag;
		}else{
			CFlag=5;
		}

		//åªç›íléÊìæ
		ORiNActivate();
		hr = pRobot->AddVariable(CComBSTR(M3_Command),CComBSTR(L""),&pPosC);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		VariantInit( &variant_pVal );
		variant_pVal.vt=VT_R4|VT_ARRAY;
		SAFEARRAYBOUND bound = {AxisNum,0};
		variant_pVal.parray = SafeArrayCreate(VT_R4,1,&bound);
		hr = pPosC->get_Value(&variant_pVal);
		float* iArray;
		SafeArrayAccessData(variant_pVal.parray , (void**)&iArray);
		for(int i=0;i<6;i++){
			std::cout<<"Åy"<<iArray[i]<<"Åz"<<std::endl;
			CPoint[i]=CPoint[i]+iArray[i];
		}
		SafeArrayUnaccessData(variant_pVal.parray);
		VariantClear(&variant_pVal);

		//É\ÉtÉgÉäÉ~ÉbÉg
		if((CPoint[0]<CLowerLimit[0]*1000.0)||(CPoint[0]>CUpperLimit[0]*1000.0)||(CPoint[1]<CLowerLimit[1]*1000.0)||(CPoint[1]>CUpperLimit[1]*1000.0)||(CPoint[2]<CLowerLimit[2]*1000.0)||(CPoint[2]>CUpperLimit[2]*1000.0)){
			std::cout<<"VALUE_ERR"<<std::endl;
			RETURNID_VALUE_ERR;
		}else{
				
			//ñ⁄ïWç¿ïWÇÃï∂éöóÒïœä∑
			sprintf(char_buffer,M13_Command,CPoint[0],CPoint[1],CPoint[2],CPoint[3],CPoint[4],CPoint[5],CFlag);
			//ÉçÉ{ÉbÉgìÆçÏ
			RobotMove(1);
			if(FAILED(hr)){
				std::cout.setf(std::ios::hex,std::ios::basefield);
				std::cout.setf(std::ios::showbase);
				std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
				RETURNID_NG;
			}
			if(pPosC) pPosC->Release();
			ORiNDeactivate();
			std::cout<<"Åyê¨å˜Åz"<<std::endl;
			RETURNID_OK;

		}
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::movePTPJointAbs(const JARA_ARM::JointPos& jointPoints)
{
	std::cout<<"ä÷êﬂç¿ïWånÇÃíºê¸ï‚ä‘(ä÷êﬂÅEê‚ëŒéwóﬂ)"<<std::endl;
	if(strcmp(M14_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		for(int i=0;i<7;i++){
			JPoint[i]=0.0;
			if(i<AxisNum){
				if(strcmp(AxialType[i],"rotation") == 0){
					JPoint[i]=jointPoints[i]*180.0/M_PI;//[rad]->[deg]
				}else if(strcmp(AxialType[i],"linear") == 0){
					JPoint[i]=jointPoints[i]*1000.0;//[m]->[mm]
				}
			}
		}
		//ä÷êﬂÉ\ÉtÉgÉäÉ~ÉbÉg
		for(int i=0;i<AxisNum;i++){
			if(strcmp(AxialType[i],"rotation") == 0){
					if((jointPoints[i]<JLowerLimit[i]*180.0/M_PI)||(jointPoints[i]>JUpperLimit[i]*180.0/M_PI)){
						std::cout<<"VALUE_ERR"<<std::endl;
						RETURNID_VALUE_ERR;
					}
				}else if(strcmp(AxialType[i],"linear") == 0){
					if((jointPoints[i]<JLowerLimit[i]*1000.0)||(jointPoints[i]>JUpperLimit[i]*1000.0)){
						std::cout<<"VALUE_ERR"<<std::endl;
						RETURNID_VALUE_ERR;
					}
				}
		}
		ORiNActivate();	
		//ñ⁄ïWç¿ïWÇÃï∂éöóÒïœä∑
		sprintf(char_buffer,M14_Command,JPoint[0],JPoint[1],JPoint[2],JPoint[3],JPoint[4],JPoint[5]);
		//ÉçÉ{ÉbÉgìÆçÏ
		RobotMove(1);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		ORiNDeactivate();
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::movePTPJointRel(const JARA_ARM::JointPos& jointPoints)
{
	std::cout<<"ä÷êﬂç¿ïWånÇÃíºê¸ï‚ä‘(ä÷êﬂÅEëäëŒéwóﬂ)"<<std::endl;
	if((strcmp(M15_Command,"NOT_IMPLEMENTED") == 0)||(strcmp(M3_Command,"NOT_IMPLEMENTED") == 0)){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		for(int i=0;i<7;i++){
			JPoint[i]=0.0;
			if(i<AxisNum){
				if(strcmp(AxialType[i],"rotation") == 0){
					JPoint[i]=jointPoints[i]*180.0/M_PI;//[rad]->[deg]
				}else if(strcmp(AxialType[i],"linear") == 0){
					JPoint[i]=jointPoints[i]*1000.0;//[m]->[mm]
				}
			}
		}
		//åªç›íléÊìæ
		ORiNActivate();
		hr = pRobot->AddVariable(CComBSTR(C3_Command),CComBSTR(L""),&pPosJ);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		VariantInit( &variant_pVal );
		variant_pVal.vt=VT_R4|VT_ARRAY;
		SAFEARRAYBOUND bound = {AxisNum,0};
		variant_pVal.parray = SafeArrayCreate(VT_R4,1,&bound);
		hr = pPosJ->get_Value(&variant_pVal);
		float* iArray;
		SafeArrayAccessData(variant_pVal.parray , (void**)&iArray);
		for(int i=0;i<AxisNum;i++){
			JPoint[i]=JPoint[i]+iArray[i];
		}
		SafeArrayUnaccessData(variant_pVal.parray);
		VariantClear(&variant_pVal);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		//ä÷êﬂÉ\ÉtÉgÉäÉ~ÉbÉg
		for(int i=0;i<AxisNum;i++){
			if(strcmp(AxialType[i],"rotation") == 0){
					if((jointPoints[i]<JLowerLimit[i]*180.0/M_PI)||(jointPoints[i]>JUpperLimit[i]*180.0/M_PI)){
						std::cout<<"VALUE_ERR"<<std::endl;
						RETURNID_VALUE_ERR;
					}
				}else if(strcmp(AxialType[i],"linear") == 0){
					if((jointPoints[i]<JLowerLimit[i]*1000.0)||(jointPoints[i]>JUpperLimit[i]*1000.0)){
						std::cout<<"VALUE_ERR"<<std::endl;
						RETURNID_VALUE_ERR;
					}
				}
		}
		
		//ñ⁄ïWç¿ïWÇÃï∂éöóÒïœä∑
		sprintf(char_buffer,M15_Command,JPoint[0],JPoint[1],JPoint[2],JPoint[3],JPoint[4],JPoint[5]);
		//ÉçÉ{ÉbÉgìÆçÏ
		RobotMove(1);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		if(pPosJ) pPosJ->Release();
		ORiNDeactivate();
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::openGripper()
{
	std::cout<<"ÉOÉäÉbÉpÇäJÇ≠"<<std::endl;
	RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::pause()
{
	std::cout<<"ìÆçÏÇÃàÍéûí‚é~"<<std::endl;
	if(strcmp(M17_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		hr = pRobot->Hold(SysAllocString(L""));
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		ORiNDeactivate();
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::resume()
{
	std::cout<<"ìÆçÏÇÃçƒäJ"<<std::endl;
	if(strcmp(M18_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		hr = pRobot->Unhold(SysAllocString(L""));
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		ORiNDeactivate();
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::stop()
{
	std::cout<<"ìÆçÏÇÃí‚é~"<<std::endl;
	if(strcmp(M19_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		hr = pRobot->Halt(SysAllocString(L""));
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		ORiNDeactivate();
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::setAccelTimeCartesian(CORBA::Double aclTime)
{
	std::cout<<"íºåìÆçÏéûÇÃâ¡ë¨éûä‘Çê›íË"<<std::endl;
	if(strcmp(M20_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		if(CMinAccelTime>aclTime){
			std::cout<<"VALUE_ERR"<<std::endl;
			RETURNID_VALUE_ERR;
		}else{
			ORiNActivate();
			hr = pRobot->Accelerate(-1,(CMinAccelTime/aclTime)*100.0,(CMinAccelTime/aclTime)*100.0);
			if(FAILED(hr)){
				std::cout.setf(std::ios::hex,std::ios::basefield);
				std::cout.setf(std::ios::showbase);
				std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
				RETURNID_NG;
			}
			ORiNDeactivate();
			std::cout<<"Åyê¨å˜Åz"<<std::endl;
			RETURNID_OK;
		}
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::setAccelTimeJoint(CORBA::Double aclTime)
{
	std::cout<<"ä÷êﬂìÆçÏéûÇÃâ¡ë¨éûä‘Çê›íË"<<std::endl;
	if(strcmp(M21_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		if(JMinAccelTime>aclTime){
			std::cout<<"VALUE_ERR"<<std::endl;
			RETURNID_VALUE_ERR;
		}else{
			ORiNActivate();
			hr = pRobot->Accelerate(0,(JMinAccelTime/aclTime)*100.0,(JMinAccelTime/aclTime)*100.0);
			if(FAILED(hr)){
				std::cout.setf(std::ios::hex,std::ios::basefield);
				std::cout.setf(std::ios::showbase);
				std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
				RETURNID_NG;
			}
			ORiNDeactivate();
			std::cout<<"Åyê¨å˜Åz"<<std::endl;
			RETURNID_OK;
		}
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::setBaseOffset(const JARA_ARM::HgMatrix offset)
{
	std::cout<<"É}ÉjÉsÉÖÉåÅ[É^ÇÃê›íuà íuÇê›íË"<<std::endl;
	if(strcmp(M22_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::setControlPointOffset(const JARA_ARM::HgMatrix offset)
{
	std::cout<<"êßå‰ì_ÇÃÉtÉâÉìÉWñ Ç©ÇÁÇÃÉIÉtÉZÉbÉgó Çê›íË"<<std::endl;
	if(strcmp(M23_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::setMaxSpeedCartesian(const JARA_ARM::CartesianSpeed& speed)
{
	std::cout<<"íºåìÆçÏéûÇÃç≈ëÂìÆçÏë¨ìxÇê›íË"<<std::endl;
	if(strcmp(M24_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		hr = pRobot->Speed(-1,speed.translation);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		ORiNDeactivate();
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::setMaxSpeedJoint(const JARA_ARM::DoubleSeq& speed)
{
	std::cout<<"ä÷êﬂìÆçÏéûÇÃç≈ëÂìÆçÏë¨ìxÇê›íË"<<std::endl;
	if(strcmp(M25_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		hr = pRobot->Speed(0,speed[0]);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		ORiNDeactivate();
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::setMinAccelTimeCartesian(CORBA::Double aclTime)
{
	std::cout<<"íºåìÆçÏéûÇÃç≈è¨ìÆçÏâ¡ë¨éûä‘Çê›íË"<<std::endl;
	if(strcmp(M26_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		CMinAccelTime=aclTime;
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::setMinAccelTimeJoint(CORBA::Double aclTime)
{
	std::cout<<"ä÷êﬂìÆçÏéûÇÃç≈è¨ìÆçÏâ¡ë¨éûä‘Çê›íË"<<std::endl;
	if(strcmp(M27_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		JMinAccelTime=aclTime;
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::setSoftLimitCartesian(const JARA_ARM::LimitValue& xLimit, const JARA_ARM::LimitValue& yLimit, const JARA_ARM::LimitValue& zLimit)
{
	std::cout<<"íºåç¿ïWånÇÃÉ\ÉtÉgÉäÉ~ÉbÉgílÇê›íË"<<std::endl;
	if(strcmp(M28_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		CUpperLimit[0]=xLimit.upper;
		CUpperLimit[1]=yLimit.upper;
		CUpperLimit[2]=zLimit.upper;
		CLowerLimit[0]=xLimit.lower;
		CLowerLimit[1]=yLimit.lower;
		CLowerLimit[2]=zLimit.lower;
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::setSpeedCartesian(ULONG spdRatio)
{
	std::cout<<"íºåìÆçÏéûÇÃë¨ìxÇê›íË"<<std::endl;
	if(strcmp(M29_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		VariantInit(&variant_param);
		if(strcmp(CaoProvName,"CaoProv.YAMAHA.RCX") == 0){
			variant_param.vt = VT_I4;
			variant_param.lVal = spdRatio;
		}else{
			variant_param.vt = VT_R4;
			variant_param.fltVal = (float)spdRatio;
		}
		hr = pRobot->Execute(CComBSTR(M29_Command),variant_param,&variant_pVal);
		VariantClear(&variant_param);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		ORiNDeactivate();
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::setSpeedJoint(ULONG spdRatio)
{
	std::cout<<"ä÷êﬂìÆçÏéûÇÃë¨ìxÇê›íË"<<std::endl;
	if(strcmp(M30_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		ORiNActivate();
		VariantInit(&variant_param);
		if(strcmp(CaoProvName,"CaoProv.YAMAHA.RCX") == 0){
			variant_param.vt = VT_I4;
			variant_param.lVal = spdRatio;
		}else{
			variant_param.vt = VT_R4;
			variant_param.fltVal = (float)spdRatio;
		}
		hr = pRobot->Execute(CComBSTR(M30_Command),variant_param,&variant_pVal);
		VariantClear(&variant_param);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		ORiNDeactivate();
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::moveCircularCartesianAbs(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT)
{
	std::cout<<"íºåç¿ïWånÇÃâ~å ï‚ä‘(ê‚ëŒéwóﬂ)"<<std::endl;
	if(strcmp(M31_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		//É\ÉtÉgÉäÉ~ÉbÉg
		if((carPointR.carPos[0][3]<CLowerLimit[0])||(carPointR.carPos[0][3]>CUpperLimit[0])||(carPointR.carPos[1][3]<CLowerLimit[1])||(carPointR.carPos[1][3]>CUpperLimit[1])||(carPointR.carPos[2][3]<CLowerLimit[2])||(carPointR.carPos[2][3]>CUpperLimit[2])||(carPointT.carPos[0][3]<CLowerLimit[0])||(carPointT.carPos[0][3]>CUpperLimit[0])||(carPointT.carPos[1][3]<CLowerLimit[1])||(carPointT.carPos[1][3]>CUpperLimit[1])||(carPointT.carPos[2][3]<CLowerLimit[2])||(carPointT.carPos[2][3]>CUpperLimit[2])){
			std::cout<<"VALUE_ERR"<<std::endl;
			RETURNID_VALUE_ERR;
		}else{
			//íÜåpì_
			CPointR[0]=carPointR.carPos[0][3]*1000.0;//x1[m]->[mm]
			CPointR[1]=carPointR.carPos[1][3]*1000.0;//y1[m]->[mm]
			CPointR[2]=carPointR.carPos[2][3]*1000.0;//z1[m]->[mm]
			CPointR[4]=180.0-asin(-carPointR.carPos[0][2])*180.0/M_PI;//B1
			if(fabs(CPoint[4])==90){
				CPointR[3]=0.0;//A1
				CPointR[5]=atan2(carPointR.carPos[1][1],carPointR.carPos[0][1])*180.0/M_PI;//C1
			}else{
				CPointR[3]=atan2(carPointR.carPos[1][2],carPointR.carPos[2][2])*180.0/M_PI;//A1
				CPointR[5]=atan2(carPointR.carPos[0][1],carPointR.carPos[0][0])*180.0/M_PI;//C1
			}
			if(carPointR.structFlag == 1){
				CFlagR=carPointR.structFlag;
			}else{
				CFlagR=5;
			}
			//ñ⁄ïWì_
			CPointT[0]=carPointT.carPos[0][3]*1000.0;//x1[m]->[mm]
			CPointT[1]=carPointT.carPos[1][3]*1000.0;//y1[m]->[mm]
			CPointT[2]=carPointT.carPos[2][3]*1000.0;//z1[m]->[mm]
			CPointT[4]=180.0-asin(-carPointT.carPos[0][2])*180.0/M_PI;//B1
			if(fabs(CPoint[4])==90){
				CPointT[3]=0.0;//A1
				CPointT[5]=atan2(carPointT.carPos[1][1],carPointT.carPos[0][1])*180.0/M_PI;//C1
			}else{
				CPointT[3]=atan2(carPointT.carPos[1][2],carPointT.carPos[2][2])*180.0/M_PI;//A1
				CPointT[5]=atan2(carPointT.carPos[0][1],carPointT.carPos[0][0])*180.0/M_PI;//C1
			}
			if(carPointT.structFlag == 1){
				CFlagT=carPointT.structFlag;
			}else{
				CFlagT=5;
			}

			ORiNActivate();	
			//ñ⁄ïWç¿ïWÇÃï∂éöóÒïœä∑
			sprintf(char_buffer,M31_Command,CPointR[0],CPointR[1],CPointR[2],CPointR[3],CPointR[4],CPointR[5],CFlagR,CPointT[0],CPointT[1],CPointT[2],CPointT[3],CPointT[4],CPointT[5],CFlagT);
			VariantInit(&variant_pose);
			variant_pose.vt = VT_BSTR;
			//É}ÉbÉvå≥ï∂éöóÒÇÃÉAÉhÉåÉXë„ì¸
			lstr=char_buffer;
			//BSTRÇ…ïKóvÇ»ÉoÉbÉtÉ@ÉTÉCÉYÇãÅÇﬂÇÈ
			bstrlen=(int)MultiByteToWideChar(CP_ACP,0,lstr,strlen(lstr),NULL,0);
			//ÉoÉbÉtÉ@Çämï€Ç∑ÇÈ
			variant_pose.bstrVal=SysAllocStringLen(NULL,bstrlen);
			//BSTRÇ…ï°êª
			MultiByteToWideChar(CP_ACP,0,lstr,strlen(lstr),variant_pose.bstrVal,bstrlen);
			hr = pRobot->Move(3,variant_pose,SysAllocString(L""));
			VariantClear(&variant_pose);
	
			if(FAILED(hr)){
				std::cout.setf(std::ios::hex,std::ios::basefield);
				std::cout.setf(std::ios::showbase);
				std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
				RETURNID_NG;
			}
			ORiNDeactivate();
			std::cout<<"Åyê¨å˜Åz"<<std::endl;
			RETURNID_OK;

		}
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::moveCircularCartesianRel(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT)
{
	std::cout<<"íºåç¿ïWånÇÃâ~å ï‚ä‘(ëäëŒéwóﬂ)"<<std::endl;
	if((strcmp(M32_Command,"NOT_IMPLEMENTED") == 0)||(strcmp(M3_Command,"NOT_IMPLEMENTED") == 0)){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		//íÜåpì_
		CPointR[0]=carPointR.carPos[0][3]*1000.0;//x1[m]->[mm]
		CPointR[1]=carPointR.carPos[1][3]*1000.0;//y1[m]->[mm]
		CPointR[2]=carPointR.carPos[2][3]*1000.0;//z1[m]->[mm]
		CPointR[4]=180.0-asin(-carPointR.carPos[0][2])*180.0/M_PI;//B1
		if(fabs(CPoint[4])==90){
			CPointR[3]=0.0;//A1
			CPointR[5]=atan2(carPointR.carPos[1][1],carPointR.carPos[0][1])*180.0/M_PI;//C1
		}else{
			CPointR[3]=atan2(carPointR.carPos[1][2],carPointR.carPos[2][2])*180.0/M_PI;//A1
			CPointR[5]=atan2(carPointR.carPos[0][1],carPointR.carPos[0][0])*180.0/M_PI;//C1
		}
		if(carPointR.structFlag == 1){
			CFlagR=carPointR.structFlag;
		}else{
			CFlagR=5;
		}
		//ñ⁄ïWì_
		CPointT[0]=carPointT.carPos[0][3]*1000.0;//x1[m]->[mm]
		CPointT[1]=carPointT.carPos[1][3]*1000.0;//y1[m]->[mm]
		CPointT[2]=carPointT.carPos[2][3]*1000.0;//z1[m]->[mm]
		CPointT[4]=180.0-asin(-carPointT.carPos[0][2])*180.0/M_PI;//B1
		if(fabs(CPoint[4])==90){
			CPointT[3]=0.0;//A1
			CPointT[5]=atan2(carPointT.carPos[1][1],carPointT.carPos[0][1])*180.0/M_PI;//C1
		}else{
			CPointT[3]=atan2(carPointT.carPos[1][2],carPointT.carPos[2][2])*180.0/M_PI;//A1
			CPointT[5]=atan2(carPointT.carPos[0][1],carPointT.carPos[0][0])*180.0/M_PI;//C1
		}
		if(carPointT.structFlag == 1){
			CFlagT=carPointT.structFlag;
		}else{
			CFlagT=5;
		}

		//åªç›íléÊìæ
		ORiNActivate();
		hr = pRobot->AddVariable(CComBSTR(M3_Command),CComBSTR(L""),&pPosC);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		VariantInit( &variant_pVal );
		variant_pVal.vt=VT_R4|VT_ARRAY;
		SAFEARRAYBOUND bound = {AxisNum,0};
		variant_pVal.parray = SafeArrayCreate(VT_R4,1,&bound);
		hr = pPosC->get_Value(&variant_pVal);
		float* iArray;
		SafeArrayAccessData(variant_pVal.parray , (void**)&iArray);
		for(int i=0;i<6;i++){
			std::cout<<"Åy"<<iArray[i]<<"Åz"<<std::endl;
			CPointR[i]=CPointR[i]+iArray[i];
			CPointT[i]=CPointT[i]+iArray[i];
		}
		SafeArrayUnaccessData(variant_pVal.parray);
		VariantClear(&variant_pVal);

		//É\ÉtÉgÉäÉ~ÉbÉg
		if((CPointR[0]<CLowerLimit[0]*1000.0)||(CPointR[0]>CUpperLimit[0]*1000.0)||(CPointR[1]<CLowerLimit[1]*1000.0)||(CPointR[1]>CUpperLimit[1]*1000.0)||(CPointR[2]<CLowerLimit[2]*1000.0)||(CPointR[2]>CUpperLimit[2]*1000.0)||(CPointT[0]<CLowerLimit[0]*1000.0)||(CPointT[0]>CUpperLimit[0]*1000.0)||(CPointT[1]<CLowerLimit[1]*1000.0)||(CPointT[1]>CUpperLimit[1]*1000.0)||(CPointT[2]<CLowerLimit[2]*1000.0)||(CPointT[2]>CUpperLimit[2]*1000.0)){
			std::cout<<"VALUE_ERR"<<std::endl;
			RETURNID_VALUE_ERR;
		}else{
			
			//ñ⁄ïWç¿ïWÇÃï∂éöóÒïœä∑
			sprintf(char_buffer,M31_Command,CPointR[0],CPointR[1],CPointR[2],CPointR[3],CPointR[4],CPointR[5],CFlagR,CPointT[0],CPointT[1],CPointT[2],CPointT[3],CPointT[4],CPointT[5],CFlagT);
			VariantInit(&variant_pose);
			variant_pose.vt = VT_BSTR;
			//É}ÉbÉvå≥ï∂éöóÒÇÃÉAÉhÉåÉXë„ì¸
			lstr=char_buffer;
			//BSTRÇ…ïKóvÇ»ÉoÉbÉtÉ@ÉTÉCÉYÇãÅÇﬂÇÈ
			bstrlen=(int)MultiByteToWideChar(CP_ACP,0,lstr,strlen(lstr),NULL,0);
			//ÉoÉbÉtÉ@Çämï€Ç∑ÇÈ
			variant_pose.bstrVal=SysAllocStringLen(NULL,bstrlen);
			//BSTRÇ…ï°êª
			MultiByteToWideChar(CP_ACP,0,lstr,strlen(lstr),variant_pose.bstrVal,bstrlen);
			hr = pRobot->Move(3,variant_pose,SysAllocString(L""));
			VariantClear(&variant_pose);
	
			if(FAILED(hr)){
				std::cout.setf(std::ios::hex,std::ios::basefield);
				std::cout.setf(std::ios::showbase);
				std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
				RETURNID_NG;
			}
			if(pPosC) pPosC->Release();
			ORiNDeactivate();
			std::cout<<"Åyê¨å˜Åz"<<std::endl;
			RETURNID_OK;

		}
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::setHome(const JARA_ARM::JointPos& jointPoint)
{
	std::cout<<"å¥ì_ïúãAéûÇÃà íuÅEépê®Çê›íË"<<std::endl;
	if(strcmp(M33_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		for(int i=0;i<7;i++){
			JHomePoint[i]=0.0;
		}
		for(int i=0;i<AxisNum;i++){
			JHomePoint[i]=jointPoint[i];
		}
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::getHome(JARA_ARM::JointPos_out jointPoint)
{
	std::cout<<"å¥ì_ïúãAéûÇÃà íuÅEépê®ÇéÊìæ"<<std::endl;
	if(strcmp(M34_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		jointPoint=new JARA_ARM::JointPos;
		jointPoint->length(AxisNum);
		for(int i=0;i<AxisNum;i++){
			(*jointPoint)[i]=JHomePoint[i];
		}
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}

JARA_ARM::RETURN_ID* ManipulatorCommonInterface_MiddleSVC_impl::goHome()
{
	std::cout<<"å¥ì_ïúãAìÆçÏ"<<std::endl;
	if(strcmp(M35_Command,"NOT_IMPLEMENTED") == 0){
		std::cout<<"NOT_IMPLEMENTED"<<std::endl;
		RETURNID_NOT_IMPLEMENTED;
	}else{
		for(int i=0;i<7;i++){
			JPoint[i]=0.0;
			if(i<AxisNum){
				if(strcmp(AxialType[i],"rotation") == 0){
					JPoint[i]=JHomePoint[i]*180.0/M_PI;//[rad]->[deg]
				}else if(strcmp(AxialType[i],"linear") == 0){
					JPoint[i]=JHomePoint[i]*1000.0;//[m]->[mm]
				}

				//ä÷êﬂÉ\ÉtÉgÉäÉ~ÉbÉg
				if(strcmp(AxialType[i],"rotation") == 0){
					if((JHomePoint[i]<JLowerLimit[i]*180.0/M_PI)||(JHomePoint[i]>JUpperLimit[i]*180.0/M_PI)){
						std::cout<<"VALUE_ERR"<<std::endl;
						RETURNID_VALUE_ERR;
					}
				}else if(strcmp(AxialType[i],"linear") == 0){
					if((JHomePoint[i]<JLowerLimit[i]*1000.0)||(JHomePoint[i]>JUpperLimit[i]*1000.0)){
						std::cout<<"VALUE_ERR"<<std::endl;
						RETURNID_VALUE_ERR;
					}
				}
			}
		}
		ORiNActivate();	
		//ñ⁄ïWç¿ïWÇÃï∂éöóÒïœä∑
		sprintf(char_buffer,M35_Command,JPoint[0],JPoint[1],JPoint[2],JPoint[3],JPoint[4],JPoint[5]);
		VariantInit(&variant_pose);
		variant_pose.vt = VT_BSTR;
		//É}ÉbÉvå≥ï∂éöóÒÇÃÉAÉhÉåÉXë„ì¸
		lstr=char_buffer;
		//BSTRÇ…ïKóvÇ»ÉoÉbÉtÉ@ÉTÉCÉYÇãÅÇﬂÇÈ
		bstrlen=(int)MultiByteToWideChar(CP_ACP,0,lstr,strlen(lstr),NULL,0);
		//ÉoÉbÉtÉ@Çämï€Ç∑ÇÈ
		variant_pose.bstrVal=SysAllocStringLen(NULL,bstrlen);
		//BSTRÇ…ï°êª
		MultiByteToWideChar(CP_ACP,0,lstr,strlen(lstr),variant_pose.bstrVal,bstrlen);
		hr = pRobot->Move(1,variant_pose,SysAllocString(L""));
		VariantClear(&variant_pose);
	
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			RETURNID_NG;
		}
		ORiNDeactivate();
		std::cout<<"Åyê¨å˜Åz"<<std::endl;
		RETURNID_OK;
	}
}



// End of example implementational code



