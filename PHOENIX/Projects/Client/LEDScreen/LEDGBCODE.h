// LEDGBCODE.h: interface for the LEDGBCODE class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEDGBCODE_H__BFC05BE8_A5FA_4ED9_B0D2_B7AEDC9A3591__INCLUDED_)
#define AFX_LEDGBCODE_H__BFC05BE8_A5FA_4ED9_B0D2_B7AEDC9A3591__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//定义函数指针类型(TCP方式)
typedef BOOL(__stdcall *openserver)(int port);
typedef BOOL(__stdcall *closeserver)();
typedef BOOL(__stdcall *ledshowtcp_nb)
(int mateuid, int movestyle, int movespeed, int stoptim,bool brownsave,int pixelcolor, 
 int fontcolor, int fontbody,int fontsize, CString str, int areaW, int areaH, CString ip);
//定义函数指针类型(UCP方式)
typedef BOOL(__stdcall *ledshowudp_nb)
(int mateuid, int movestyle, int movespeed, int stoptim,bool brownsave,int pixelcolor, 
 int fontcolor, int fontbody,int fontsize, CString str, int areaW, int areaH, CString ip);
//定义函数指针类型(COM方式)
typedef BOOL(__stdcall *ledshowcom_nb)
(int mateuid, int movestyle, int movespeed, int stoptim, bool brownsave, int pixelcolor, 
 int fontcolor, int fontbody, int fontsize, CString str, int areaw, int areah, int port, 
 int baud, int rstype, CString rsadr, int updStyle, int timOut, bool endTag);

class filedll
{
public:	
	HINSTANCE Ddll;					//QYLED.Dll文件句柄
	filedll();
	filedll(CString dllname);		//构造函数
	~filedll();						//析构函数	
};

class material
{
public:
	UINT mateuid;		//素材UID
	UINT areaW;			//区域宽度
	UINT areaH;			//区域高度
	UINT pixelcolor;	//像素颜色
	BOOL brownsave;		//掉电保存
	
	UINT fontbody;		//显示字体
	UINT fontsize;		//显示字号
	UINT movestyle;		//显示方式
	UINT movespeed;		//移动速度	
	UINT fontcolor;		//显示颜色
	UINT stoptim;		//停留时间
	CString str;		//显示信息
	BOOL endTag;		//结束标记
};

class CLEDGBCODEtcp:public material  
{
public:
	CString ip;					 		   //目标IP
	UINT localport;				 		   //本地端口

	openserver Topenserver;		 		   //函数指针变量(TCP通讯)
	closeserver Tcloseserver;	 		   //函数指针变量
	ledshowtcp_nb Tledshowtcp_nb;		   //函数指针变量

	BOOL openserverC(const HINSTANCE Ddll); //开启服务
	BOOL closeserverC(const HINSTANCE Ddll);//关闭服务
	BOOL senddt(const HINSTANCE Ddll);		//下发数据
};

class CLEDGBCODEudp:public material
{
public:
	CString ip;					   		    //目标IP
	ledshowudp_nb Tledshowudp_nb;  		    //函数指针变量

	BOOL senddt(const HINSTANCE Ddll);	    //下发数据
};

class CLEDGBCODEcom:public material
{
public:
	UINT rstype;				 //COM通讯类型(RS232/RS485)
	UINT port;					 //端口号
	UINT baud;					 //波特率
	CString adr;				 //地址(若通讯类型为RS485则有效，若通讯为RS232则无效)
	ledshowcom_nb Tledshowcom_nb;//函数指针变量

	BOOL senddt(const HINSTANCE Ddll);//下发数据
};

#endif // !defined(AFX_LEDGBCODE_H__BFC05BE8_A5FA_4ED9_B0D2_B7AEDC9A3591__INCLUDED_)
