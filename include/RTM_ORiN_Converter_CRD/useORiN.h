//useORiN.h
#ifndef __USEORIN_H__
#define __USEORIN_H__

#include "atlbase.h"
#include "CAO.h"
#include "string"
#include <iostream>
#include <comutil.h>

#pragma comment(lib, "comsuppw.lib")

extern	HRESULT hr;
extern	ICaoEngine* pEng;
extern	ICaoWorkspaces* pWss;
extern	ICaoWorkspace* pWs;
extern	ICaoController* pCtrl;
extern	ICaoRobot* pRobot;
extern	ICaoVariable* pVar;
extern	ICaoVariable* pPosJ;
extern	ICaoVariable* pPosC;
extern	ICaoVariable* pServo;
extern	ICaoVariable* pSPEED;
extern	ICaoVariable* pJSPEED;
extern LPSTR lstr;
extern int bstrlen;
extern char char_buffer[100];
extern char char_option[100];
extern BSTR bstr_option;
extern VARIANT variant_param;
extern VARIANT variant_pose;
extern VARIANT variant_pVal;
extern char* PortParam;
extern char* XMLFilePath;
extern long timeout;
extern double JUpperLimit[7];
extern double JLowerLimit[7];
extern double CUpperLimit[3];
extern double CLowerLimit[3];
extern double JMinAccelTime;
extern double CMinAccelTime;
extern double JHomePoint[7];
extern double JPoint[7];
extern double CPoint[6];
extern double CPointR[6];
extern double CPointT[6];
extern int CFlag;
extern int CFlagR;
extern int CFlagT;

extern HRESULT ORiNAct();
extern HRESULT ORiNDeact();
extern HRESULT ORiNInit();

#define ORiNActivate() {ORiNAct();}
#define ORiNDeactivate() {ORiNDeact();}
#define ORiNInitialize() {ORiNInit();}

#endif//__USEORIN_H__