#pragma once
#include <Windows.h>
#include "tool_m.h"
//////////////////////////////
//#################额外定义
//////////////////////////////
class Clist;
class MWin;
class ConWin_Base;
class Con_Edit;
extern HINSTANCE Hinst;
/////////////////////////////
//#########################//
/*###########位图##########*/
//#########################//
////////////////////////////
//操作流程：1.类里的Initbmp初始化数据   2.Loadbmp加载位图   3.SetBmp放置图片
class imgbmp;
typedef struct HWND_list Hlist;
void SetBmp(int num, imgbmp b, int x, int y);//将位图放到窗口上

//////////位图信息结构体
typedef struct BMP_INFOR
{
	HBITMAP hbmp;
	BITMAP bmp;
	int w;
	int h;
}IBMP;
//////////
class imgbmp
{
	friend void SetBmp(int, imgbmp, int x, int y);
protected:
	int snum;              //位图总个数
	HINSTANCE hinst;       //实例
	HDC i_hdc;             //位图绘画设备
	IBMP* ibmp;            //位图储存
	HDC m_hdc;             //主窗口绘画设备
public:
	void Loadbmp(int num, const wchar_t filename[], int w, int h);
	imgbmp(HDC, int num, HINSTANCE);
	imgbmp() {}
	void Initbmp(HDC, int num, HINSTANCE);
	void Setbmp(int num, int x, int y, DWORD model = SRCCOPY);
	void Zero();
	void Delbmp(int num);
	void ChangeDC(HDC dc) { m_hdc = dc; }
};

/////////////////////////////
//#########################//
/*############主窗口########*/
//#########################//
/////////////////////////////
extern Clist winlist;
//////////
//////////窗口句柄找窗口对象
MWin* HwndFindMWin(HWND hwnd);
//////////
//////////ID找窗口对象
MWin* IDFindMWin(int id);
//////////
//////////根据ID删除对象
int DelMWin(int id);
//////////
//////////绘图消息类
typedef struct PAINT_MSG
{
	int pid;
	int c1;
	int c2;
	int c3;
	int c4;
	wchar_t str[100];
}PAINTMSG;
//主窗口类
class MWin
{
	friend LRESULT CALLBACK WinSunProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	friend void wm_create(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	friend void wm_command(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	friend void wm_paint(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	friend void wm_size(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	friend void wm_drwaitem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	MWin(HINSTANCE hInstance, LPCWSTR classname, int id);
	HWND Create(const wchar_t winname[], int w, int h,DWORD style= WS_OVERLAPPEDWINDOW | WS_VISIBLE);//创建窗口
	HWND Createson(const wchar_t winname[], int x,int y,int w, int h, DWORD style, HWND parent);
	HWND Gethwnd() { return m_hwnd; }//获取窗口句柄
	void Setibmp(imgbmp* ibm);       //将位图传递给主窗口
	void SetHDC(HDC dc);             //设置HDC
	HDC GetbkDC() { return bkhdc; }
	void Seticon(const wchar_t filename[]);
protected:
	WNDCLASS wndcls;    //窗口结构体
	HWND m_hwnd;        //窗口句柄
	HICON m_ico;        //图   标
	int m_id;           //窗口名称
	HDC m_hdc;          //绘画设备
	PAINTMSG vpmsg[10];     //绘画消息容器,最多有10个消息
	void initmsg(int i);
	HPEN hpen;        //画笔
	HBRUSH hbrush;    //画刷
	imgbmp* ib;       //位图
	HINSTANCE hinst;
	bool ifinit;
	Clist sonwin;
	HWND m_parent;
	//缓冲位图
protected:
	HBITMAP chbmp;
	BITMAP cbmp;
	int client_w;
	int client_h;
	int ow;
	int oh;
	HDC bkhdc;

	//绘图函数
public:
	void Delself();
	void addmsg(int id, int x1, int x2, int x3, int x4);
	BOOL Pcircle(int cx, int cy, int R, int penwidth = 2, int penstyle = PS_SOLID, COLORREF pencolor = RGB(0, 0, 0));
	BOOL Prect(int x1, int y1, int x2, int y2, int penwidth = 2, int penstyle = PS_SOLID, COLORREF pencolor = RGB(0, 0, 0));
	BOOL Pline(int x1, int y1, int x2, int y2, int penwidth = 2, int penstyle = PS_SOLID, COLORREF pencolor = RGB(0, 0, 0));
	BOOL Psetbmp(int x, int y, int num);
	BOOL Ptext(int x, int y, const wchar_t t[]);
	BOOL Psetbkcolor(COLORREF pencolor);
	BOOL Pfillrect(int x1, int y1, int x2, int y2, COLORREF brushcolor = RGB(0, 0, 0));
	BOOL Pfillcircle(int cx, int cy, int R, int penwidth = 2, int penstyle = PS_SOLID, COLORREF pencolor = RGB(0, 0, 0), COLORREF brushcolor = RGB(0, 0, 0));
	BOOL Pmaskbmp(int num, int masknnum, int x, int y);
	//绘图函数结束

	//主窗口控件代码
protected:
	Clist con;                //控件容器
	void AllConRun(WPARAM wParam, LPARAM lParam);//运行
public:
	void AddCon(void *icon);         //增加控件
	void DelCon(int ID);//删除控件
	void* Getcon(int ID);            //获取控件
	//控件代码结束
};

/////////////////////////////
//#########################//
/*############控件类########*/
//#########################//
/////////////////////////////
#define CON_EDIT   0  //编辑框控件
#define CON_BUTTON 1  //按钮控件
#define CON_WIN    2  //子窗口控件
#define CON_DRWABUTTON 3 //自绘按钮



#define CON_SHOW 1
#define CON_HIDE 0
//控件执行函数
typedef void(*Conrun)(HWND hwnd,WPARAM wParam, LPARAM lParam);
//基础控件类
class ConWin_Base
{
public:
	ConWin_Base(HINSTANCE hInstance, HWND parent, int id, int type1);//id是标识，type是控件类型，1代表编辑框，2代表按钮
	HWND Gethwnd() { return c_hwnd; }      //获取窗口句柄
	ConWin_Base() {}
	void Setproc(Conrun run);              //设置执行函数
	void Run(WPARAM wParam, LPARAM lParam);//执行回调函数
	int Getid() { return c_id; }           //获得控件ID
	int Gettype() { return c_type; }       //获得控件类型
	virtual void Delself() {}
	void State(int s);                     //关闭或开启控件
protected:
	HWND c_hwnd;        //句柄
	HWND c_parent;      //父类句柄
	int c_type;         //窗口类型 1是编辑框  2是按钮
	int c_id;           //窗口的标识id
	HINSTANCE c_hinst;  //窗口实例
	Conrun proc;        //执行函数
	void init(HINSTANCE hInstance, HWND parent, int id, int type1);
};


//编辑框类
class Con_Edit : public ConWin_Base
{
public:
	Con_Edit(HINSTANCE hInstance, HWND parent, int id, int size);
	HWND Create(int x, int y, int w, int h, DWORD style = WS_CHILD | WS_VISIBLE | ES_MULTILINE);
public:
	wchar_t* GetText();
	void SetText(const wchar_t text[]);
	void Delself();
protected:
	wchar_t* buff;
	int bsize;
};


//按钮类
//
//标准按钮运行函数

//
class Con_Button : public ConWin_Base
{
public:
	Con_Button(HINSTANCE hInstance, HWND parent, int id, const wchar_t content[]);
	HWND Create(int x, int y, int w, int h, DWORD style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON);
	void Delself();
protected:
	wchar_t text[20];

};




//自绘控件类

class Con_DrawButton :public ConWin_Base
{
	friend void wm_drwaitem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	Con_DrawButton(HINSTANCE hInstance, HWND parent, int id, const wchar_t content[] = L"");
	HWND Create(int x, int y, int w, int h, const wchar_t file1[], const wchar_t file2[], DWORD style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW);
	void Delself();
protected:
	wchar_t text[20];
	IBMP cbmp[2];
	int cw;
	int ch;
};


//////////////////////
//##################//
//#####执行函数######//
//##################//
//////////////////////
#define LINE_RUN 1
#define LINE_WAITCLOSE 2
#define LINE_CLOSED 3 
extern int LineState;
extern DWORD dwExitCode;
void MWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
void WinClose();
void MainRun(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


//////////////////////////////////
////////////////////////时间函数
//////////////////////////////////
class Mtimer_us
{
public:
	Mtimer_us();
	void begin();
	int Getalltime();
	int Getgaptime();
protected:
	LARGE_INTEGER begin_time;
	LARGE_INTEGER end_time;
	LARGE_INTEGER gap_time;
	LARGE_INTEGER freq_;
};
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
