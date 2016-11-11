#include "useORiN.h"
#include "defcommand.h"
#include "CAO_i.c"

	HRESULT hr = S_OK;
	ICaoEngine* pEng = NULL;
	ICaoWorkspaces* pWss = NULL;
	ICaoWorkspace* pWs = NULL;
	ICaoController* pCtrl = NULL;
	ICaoRobot* pRobot = NULL;
	ICaoVariable* pPosJ;
	ICaoVariable* pPosC;
	ICaoVariable* pServo;
	ICaoVariable* pSPEED;
	ICaoVariable* pJSPEED;
	ICaoVariable* pVar = NULL;
	LPSTR lstr;
	int bstrlen;
	char char_buffer[100];
	char char_option[100];
	BSTR bstr_option;
	VARIANT variant_param;
	VARIANT variant_pose;
	VARIANT variant_pVal;
	char* PortParam = "";
	char* XMLFilePath = "";
	long timeout = 50000;
	double JUpperLimit[7] = { 10000.0 , 10000.0 , 10000.0 , 10000.0 , 10000.0 , 10000.0 , 10000.0 };
	double JLowerLimit[7] = {-10000.0 ,-10000.0 ,-10000.0 ,-10000.0 ,-10000.0 ,-10000.0 ,-10000.0 };
	double CUpperLimit[3] = { 10000.0 , 10000.0 , 10000.0 };
	double CLowerLimit[3] = {-10000.0 ,-10000.0 ,-10000.0 };
	double JMinAccelTime = 1;
	double CMinAccelTime = 1;
	double JHomePoint[7];
	double JPoint[7];
	double CPoint[6];
	double CPointR[6];
	double CPointT[6];
	int CFlag;
	int CFlagR;
	int CFlagT;
	

HRESULT ORiNAct(){
		std::cout<<"DCOMÇÃèâä˙âª"<<std::endl;
	CoInitialize(0);

	//CaoEngineÇÃê∂ê¨
	std::cout<<"CaoEngineÇÃê∂ê¨"<<std::endl;
	hr = CoCreateInstance(CLSID_CaoEngine,NULL,CLSCTX_LOCAL_SERVER,IID_ICaoEngine,(void **)&pEng);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	//CaoWorkspaceÉRÉåÉNÉVÉáÉìÇÃéÊìæ
	std::cout<<"CaoWorkspaceÉRÉåÉNÉVÉáÉìÇÃéÊìæ"<<std::endl;
	hr = pEng->get_Workspaces(&pWss);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	//CaoWorkspaceÇÃéÊìæ
	std::cout<<"CaoWorkspaceÇÃéÊìæ"<<std::endl;
	hr = pWss->Item(CComVariant(0L), &pWs);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	
	//CaoControllerÇÃê∂ê¨
	std::cout<<"CaoControllerÇÃê∂ê¨"<<std::endl;
	//ConfigurationÇÃï∂éöóÒïœä∑
	sprintf(char_option,ConnectionParam,PortParam,timeout);
	//É}ÉbÉvå≥ï∂éöóÒÇÃÉAÉhÉåÉXë„ì¸
	lstr=char_option;
	//BSTRÇ…ïKóvÇ»ÉoÉbÉtÉ@ÉTÉCÉYÇãÅÇﬂÇÈ
	bstrlen=(int)MultiByteToWideChar(CP_ACP,0,lstr,strlen(lstr),NULL,0);
	//ÉoÉbÉtÉ@Çämï€Ç∑ÇÈ
	bstr_option=SysAllocStringLen(NULL,bstrlen);
	//BSTRÇ…ï°êª
	MultiByteToWideChar(CP_ACP,0,lstr,strlen(lstr),bstr_option,bstrlen);

	hr = pWs->AddController(CComBSTR(ControllerName),CComBSTR(CaoProvName),CComBSTR(L""),bstr_option,&pCtrl);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}

	//CaoProvRobotÉIÉuÉWÉFÉNÉgÇÃê∂ê¨
	std::cout<<"CaoProvRobotÉIÉuÉWÉFÉNÉgÇÃê∂ê¨"<<std::endl;
	hr = pCtrl->AddRobot(CComBSTR(RobotName),CComBSTR(L""),&pRobot);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
		return S_OK;
}

HRESULT ORiNDeact(){
	//ÉIÉuÉWÉFÉNÉgÇÃâï˙
	std::cout<<"ÉIÉuÉWÉFÉNÉgÇÃâï˙"<<std::endl;
	
	//âï˙èàóù
	if(pRobot) pRobot->Release();
	if(pCtrl) pCtrl->Release();
	if(pWs) pWs->Release();
	if(pWss) pWss->Release();
	if(pEng) pEng->Release();

	//DCOMÇÃèIóπèàóù
	std::cout<<"DCOMÇÃèIóπèàóù"<<std::endl;
	CoUninitialize();

		return S_OK;
	}

HRESULT ORiNInit(){
//XMLÉtÉ@ÉCÉãÇÃì«Ç›çûÇ›
	//std::cout<<"DCOMÇÃèâä˙âª"<<std::endl;
	CoInitialize(0);
	//CaoEngineÇÃê∂ê¨
	//std::cout<<"CaoEngineÇÃê∂ê¨"<<std::endl;
	hr = CoCreateInstance(CLSID_CaoEngine,NULL,CLSCTX_LOCAL_SERVER,IID_ICaoEngine,(void **)&pEng);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	//CaoWorkspaceÉRÉåÉNÉVÉáÉìÇÃéÊìæ
	//std::cout<<"CaoWorkspaceÉRÉåÉNÉVÉáÉìÇÃéÊìæ"<<std::endl;
	hr = pEng->get_Workspaces(&pWss);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	//CaoWorkspaceÇÃéÊìæ
	//std::cout<<"CaoWorkspaceÇÃéÊìæ"<<std::endl;
	hr = pWss->Item(CComVariant(0L), &pWs);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	//CaoControllerÇÃê∂ê¨
	//std::cout<<"CaoControllerÇÃê∂ê¨"<<std::endl;
	hr = pWs->AddController(CComBSTR(L"ControllerName"),CComBSTR(L"CaoProv.CRD"),CComBSTR(L""),CComBSTR(XMLFilePath),&pCtrl);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		std::cout<<"XML file path is wrong"<<std::endl;
		return S_FALSE;
	}
//CaoProvider
	//ControllerName
	hr = pCtrl->AddVariable(CComBSTR(L"ControllerName"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	ControllerName = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//CaoProvName
	hr = pCtrl->AddVariable(CComBSTR(L"CaoProvName"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	CaoProvName = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//ConnectionParam
	hr = pCtrl->AddVariable(CComBSTR(L"ConnectionParam"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	ConnectionParam = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//Manufactur
	hr = pCtrl->AddVariable(CComBSTR(L"Manufactur"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	Manufactur = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//RobotName
	hr = pCtrl->AddVariable(CComBSTR(L"RobotName"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	RobotName = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//AxisNum
	hr = pCtrl->AddVariable(CComBSTR(L"AxisNum"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_I2;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	AxisNum = variant_pVal.iVal;
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();

	//AxialType
	hr = pCtrl->AddVariable(CComBSTR(L"AxialType"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR|VT_ARRAY;
	SAFEARRAYBOUND bound = {AxisNum,0};
		variant_pVal.parray = SafeArrayCreate(VT_BSTR,1,&bound);
		hr = pVar->get_Value(&variant_pVal);
		if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
		}
		BSTR* bstr_AxialType;
		SafeArrayAccessData(variant_pVal.parray , (void**)&bstr_AxialType);
		for(int i=0;i<AxisNum;i++){
			AxialType[i] = _com_util::ConvertBSTRToString(bstr_AxialType[i]);
			
			if((strcmp(AxialType[i],"rotation") != 0)&&(strcmp(AxialType[i],"linear") != 0)){
				std::cout<<"AxialType is wrong"<<std::endl;
				return S_FALSE;
			}
			
		}
		SafeArrayUnaccessData(variant_pVal.parray);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();

	//IsGripper
	hr = pCtrl->AddVariable(CComBSTR(L"IsGripper"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_I2;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	if(variant_pVal.iVal == 0){
		IsGripper = false;
	}else if(variant_pVal.iVal == 1){
		IsGripper = true;
	}else{
		return S_FALSE;
	}
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();


//CommonCommand
	//C1
	hr = pCtrl->AddVariable(CComBSTR(L"C1"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	C1_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//C2
	hr = pCtrl->AddVariable(CComBSTR(L"C2"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	C2_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//C3
	hr = pCtrl->AddVariable(CComBSTR(L"C3"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	C3_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//C4
	hr = pCtrl->AddVariable(CComBSTR(L"C4"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	C4_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//C5
	hr = pCtrl->AddVariable(CComBSTR(L"C5"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	C5_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//C6
	hr = pCtrl->AddVariable(CComBSTR(L"C6"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	C6_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//C7
	hr = pCtrl->AddVariable(CComBSTR(L"C7"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	C7_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//C7_Option
	hr = pCtrl->AddVariable(CComBSTR(L"C7_Option"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	C7_Option = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	//C7_Option = SysAllocString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//C8
	hr = pCtrl->AddVariable(CComBSTR(L"C8"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	C8_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//C8_Option
	hr = pCtrl->AddVariable(CComBSTR(L"C8_Option"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	C8_Option = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//C9
	hr = pCtrl->AddVariable(CComBSTR(L"C9"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	C9_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();

//MiddleLevelMotionCommand
	//M1
	hr = pCtrl->AddVariable(CComBSTR(L"M1"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M1_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M2
	hr = pCtrl->AddVariable(CComBSTR(L"M2"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M2_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M3
	hr = pCtrl->AddVariable(CComBSTR(L"M3"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M3_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M4
	hr = pCtrl->AddVariable(CComBSTR(L"M4"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M4_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M5
	hr = pCtrl->AddVariable(CComBSTR(L"M5"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M5_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M6
	hr = pCtrl->AddVariable(CComBSTR(L"M6"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M6_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M7
	hr = pCtrl->AddVariable(CComBSTR(L"M7"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M7_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M8
	hr = pCtrl->AddVariable(CComBSTR(L"M8"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M8_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M9
	hr = pCtrl->AddVariable(CComBSTR(L"M9"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M9_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M10
	hr = pCtrl->AddVariable(CComBSTR(L"M10"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M10_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M11
	hr = pCtrl->AddVariable(CComBSTR(L"M11"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M11_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M12
	hr = pCtrl->AddVariable(CComBSTR(L"M12"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M12_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M13
	hr = pCtrl->AddVariable(CComBSTR(L"M13"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M13_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M14
	hr = pCtrl->AddVariable(CComBSTR(L"M14"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M14_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M15
	hr = pCtrl->AddVariable(CComBSTR(L"M15"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M15_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M16
	hr = pCtrl->AddVariable(CComBSTR(L"M16"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M16_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M17
	hr = pCtrl->AddVariable(CComBSTR(L"M17"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M17_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M18
	hr = pCtrl->AddVariable(CComBSTR(L"M18"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M18_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M19
	hr = pCtrl->AddVariable(CComBSTR(L"M19"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M19_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M20
	hr = pCtrl->AddVariable(CComBSTR(L"M20"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M20_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M21
	hr = pCtrl->AddVariable(CComBSTR(L"M21"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M21_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M22
	hr = pCtrl->AddVariable(CComBSTR(L"M22"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M22_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M23
	hr = pCtrl->AddVariable(CComBSTR(L"M23"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M23_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M24
	hr = pCtrl->AddVariable(CComBSTR(L"M24"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M24_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M25
	hr = pCtrl->AddVariable(CComBSTR(L"M25"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M25_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M26
	hr = pCtrl->AddVariable(CComBSTR(L"M26"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M26_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M27
	hr = pCtrl->AddVariable(CComBSTR(L"M27"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M27_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M28
	hr = pCtrl->AddVariable(CComBSTR(L"M28"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M28_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M29
	hr = pCtrl->AddVariable(CComBSTR(L"M29"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M29_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M30
	hr = pCtrl->AddVariable(CComBSTR(L"M30"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M30_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M31
	hr = pCtrl->AddVariable(CComBSTR(L"M31"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M31_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M32
	hr = pCtrl->AddVariable(CComBSTR(L"M32"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M32_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M33
	hr = pCtrl->AddVariable(CComBSTR(L"M33"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M33_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M34
	hr = pCtrl->AddVariable(CComBSTR(L"M34"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M34_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();
	//M35
	hr = pCtrl->AddVariable(CComBSTR(L"M35"),CComBSTR(L""),&pVar);
	if(FAILED(hr)){
			std::cout.setf(std::ios::hex,std::ios::basefield);
			std::cout.setf(std::ios::showbase);
			std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
			return S_FALSE;
	}
	VariantInit( &variant_pVal );
	variant_pVal.vt=VT_BSTR;
	hr = pVar->get_Value(&variant_pVal);
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"Åyé∏îsÅz: "<<hr<<std::endl;
		return S_FALSE;
	}
	M35_Command = _com_util::ConvertBSTRToString(variant_pVal.bstrVal);
	VariantClear(&variant_pVal);
	if(pVar) pVar->Release();

//ÉIÉuÉWÉFÉNÉgÇÃâï˙
	//âï˙èàóù
	if(pVar) pVar->Release();
	if(pCtrl) pCtrl->Release();
	if(pWs) pWs->Release();
	if(pWss) pWss->Release();
	if(pEng) pEng->Release();
	//DCOMÇÃèIóπèàóù
	CoUninitialize();

	return S_OK;
}
