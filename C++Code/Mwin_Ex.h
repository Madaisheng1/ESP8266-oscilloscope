#pragma once
#ifndef  MWINEX__
#define MWINEX__
#include <WinSock2.h>
#include "MWin.h"
#include <Windows.h>
class MWin_axis
{
	friend LRESULT CALLBACK AxisProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	MWin_axis(HINSTANCE hInstance, LPCWSTR classname);
	HWND Create(const wchar_t winname[],int x,int y, int w, int h,HWND parent, DWORD style = WS_CHILD);//创建窗口
	HWND Gethwnd() { return m_hwnd; }//获取窗口句柄
protected:
	WNDCLASS wndcls;    //窗口结构体
	HWND m_hwnd;        //窗口句柄
	HICON m_ico;        //图   标
	HDC m_hdc;          //绘画设备
	HINSTANCE hinst;
	HWND m_parent;
	//缓冲位图
protected:
	int client_w;
	int client_h;
	int ow;
	int oh;
	HBITMAP chbmp;
	BITMAP cbmp;
	BOOL ifinit;
	HDC bkhdc;
	HPEN hpen;        //画笔
	HBRUSH hbrush;    //画刷
	HBITMAP mhbmp;
	BITMAP mbmp;
	HDC hhdc;

	int y_max;
	int x_max;
	int xlgap;
	int xgap;
	int ygap;
protected:
	int msg[5][5];
	void DelMsg(int i);
	void Setline(COLORREF color, int pensize);
	//绘图函数
public:
	void Setpoint(int x, int y);//1
	void Setpen(COLORREF color, int pensize);//3
	void Topoint(int x, int y);//2
	void Delself();
	void SetBk(int xl, int xm, int ym);
	void ResetBk();
};
extern MWin_axis *axis;
#endif

