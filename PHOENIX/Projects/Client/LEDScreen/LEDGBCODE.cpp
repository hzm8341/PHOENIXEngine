// LEDGBCODE.cpp: implementation of the LEDGBCODE class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "lednm.h"
#include "LEDGBCODE.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//----------------------------------------------------------------------------
filedll::filedll()
{
}
//----------------------------------------------------------------------------
filedll::filedll(CString dllname)
{
	//加载动态链接库
	Ddll = LoadLibrary(dllname);
}
//----------------------------------------------------------------------------
filedll::~filedll()
{
	//释放动态链接库
	if (Ddll !=NULL)
	{
		FreeLibrary(Ddll);	
	}
}
//----------------------------------------------------------------------------
BOOL CLEDGBCODEtcp::openserverC(const HINSTANCE Ddll)
{
	bool sign =false;
	if (Ddll !=NULL)
	{
		Topenserver =(openserver)GetProcAddress(Ddll, "OpenServer");
		sign =Topenserver(localport);
	};	
	return sign;
}
//----------------------------------------------------------------------------
BOOL CLEDGBCODEtcp::closeserverC(const HINSTANCE Ddll)
{
	bool sign =false;
	if (Ddll !=NULL)
	{
		Tcloseserver=(closeserver)GetProcAddress(Ddll, "CloseServer");
		sign = Tcloseserver();
	};		 
	return sign;
}
//----------------------------------------------------------------------------
BOOL CLEDGBCODEtcp::senddt(const HINSTANCE Ddll)
{
	BOOL sign = false;
	if (Ddll !=NULL)
	{
		Tledshowtcp_nb =(ledshowtcp_nb)GetProcAddress(Ddll, "LEDShowTCP_nb");
		sign = Tledshowtcp_nb
		(mateuid, movestyle, movespeed, stoptim, brownsave, pixelcolor,	fontcolor, 
		 fontbody, fontsize, str, areaW, areaH, ip);
	}
	return sign;
}
//----------------------------------------------------------------------------
BOOL CLEDGBCODEudp::senddt(const HINSTANCE Ddll)
{
	BOOL sign = false;
	if (Ddll !=NULL)
	{
		Tledshowudp_nb = (ledshowudp_nb)GetProcAddress(Ddll, "LEDShowUDP_nb");
		sign = Tledshowudp_nb
		(mateuid, movestyle, movespeed, stoptim, brownsave, pixelcolor,	fontcolor, 
		 fontbody, fontsize, str, areaW, areaH, ip);
	}
	return sign;
}
//----------------------------------------------------------------------------
BOOL CLEDGBCODEcom::senddt(const HINSTANCE Ddll)
{
	const int timOut = 1000;
	const int updStyle = 51;
	BOOL sign = false;
	if (Ddll !=NULL)
	{
		Tledshowcom_nb = (ledshowcom_nb)GetProcAddress(Ddll, "LEDShowCOM_nb");
		sign = Tledshowcom_nb
			(mateuid, movestyle, movespeed, stoptim, brownsave, pixelcolor,	fontcolor, 
			fontbody, fontsize, str, areaW, areaH, port, baud, rstype, adr, updStyle,
			timOut, endTag);
	}
	return sign;
}
//----------------------------------------------------------------------------