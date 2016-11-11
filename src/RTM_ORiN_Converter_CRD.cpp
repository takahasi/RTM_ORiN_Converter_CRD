// -*- C++ -*-
/*!
 * @file  RTM_ORiN_Converter_CRD.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "RTM_ORiN_Converter_CRD.h"
#include "defcommand.h"
#include "useORiN.h"

// Module specification
// <rtc-template block="module_spec">
static const char* rtm_orin_converter_crd_spec[] =
  {
    "implementation_id", "RTM_ORiN_Converter_CRD",
    "type_name",         "RTM_ORiN_Converter_CRD",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "Saitama Univ. Design Lab.",
    "category",          "Industrial Robot",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.Port", "com:1",
    "conf.default.Timeout", "50000",
    "conf.default.XMLFilePath", "Path=C:/Sample.xml",
    // Widget
    "conf.__widget__.Port", "text",
    "conf.__widget__.Timeout", "text",
    "conf.__widget__.XMLFilePath", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTM_ORiN_Converter_CRD::RTM_ORiN_Converter_CRD(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_ManipulatorCommonInterface_CommonPort("ManipulatorCommonInterface_Common"),
    m_ManipulatorCommonInterface_MiddlePort("ManipulatorCommonInterface_Middle")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RTM_ORiN_Converter_CRD::~RTM_ORiN_Converter_CRD()
{
}



RTC::ReturnCode_t RTM_ORiN_Converter_CRD::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  m_ManipulatorCommonInterface_CommonPort.registerProvider("ManipulatorCommonInterface_Common", "JARA_ARM::ManipulatorCommonInterface_Common", m_ManipulatorCommonInterface_Common);
  m_ManipulatorCommonInterface_MiddlePort.registerProvider("ManipulatorCommonInterface_Middle", "JARA_ARM::ManipulatorCommonInterface_Middle", m_ManipulatorCommonInterface_Middle);
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort(m_ManipulatorCommonInterface_CommonPort);
  addPort(m_ManipulatorCommonInterface_MiddlePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("Port", m_Port, "com:1");
  bindParameter("Timeout", m_Timeout, "50000");
  bindParameter("XMLFilePath", m_XMLFilePath, "Path=C:/Sample.xml");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTM_ORiN_Converter_CRD::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTM_ORiN_Converter_CRD::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTM_ORiN_Converter_CRD::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RTM_ORiN_Converter_CRD::onActivated(RTC::UniqueId ec_id)
{
	std::cout<<std::endl<<"******************************"<<std::endl<<"           Activate           "<<std::endl<<"******************************"<<std::endl<<std::endl;

	//Config値の代入
	timeout = m_Timeout;
	int len = m_Port.length();
	PortParam = new char[len+1];
	memcpy(PortParam, m_Port.c_str(), len+1);

	len = m_XMLFilePath.length();
	XMLFilePath = new char[len+1];
	memcpy(XMLFilePath, m_XMLFilePath.c_str(), len+1);

	std::cout<<"Configuration"<<std::endl<<"通信ポートパラメータ"<<std::endl<<" PortParam : "<<PortParam<<std::endl<<"通信タイムアウト"<<std::endl<<" Timeout : "<<timeout<<std::endl<<"XMLファイルパス"<<std::endl<<" XMLFilePath : "<<XMLFilePath<<std::endl<<std::endl;

	//CRDプロバイダによるパラメータ値設定
	hr = ORiNInit();
	if(FAILED(hr)){
		std::cout.setf(std::ios::hex,std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout<<"【失敗】: "<<hr<<std::endl;
		return RTC::RTC_ERROR;
	}

	std::cout<<std::endl<<"******************************"<<std::endl<<"           Execute            "<<std::endl<<"******************************"<<std::endl<<std::endl;

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RTM_ORiN_Converter_CRD::onDeactivated(RTC::UniqueId ec_id)
{
	std::cout<<std::endl<<"******************************"<<std::endl<<"          Deactivate          "<<std::endl<<"******************************"<<std::endl<<std::endl;

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RTM_ORiN_Converter_CRD::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RTM_ORiN_Converter_CRD::onAborting(RTC::UniqueId ec_id)
{
	std::cout<<std::endl<<"******************************"<<std::endl<<"            Error             "<<std::endl<<"******************************"<<std::endl<<std::endl;

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTM_ORiN_Converter_CRD::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RTM_ORiN_Converter_CRD::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTM_ORiN_Converter_CRD::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTM_ORiN_Converter_CRD::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RTM_ORiN_Converter_CRDInit(RTC::Manager* manager)
  {
    coil::Properties profile(rtm_orin_converter_crd_spec);
    manager->registerFactory(profile,
                             RTC::Create<RTM_ORiN_Converter_CRD>,
                             RTC::Delete<RTM_ORiN_Converter_CRD>);
  }
  
};


