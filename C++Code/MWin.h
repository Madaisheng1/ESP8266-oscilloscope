#pragma once
#include <Windows.h>
#include "tool_m.h"
//////////////////////////////
//#################���ⶨ��
//////////////////////////////
class Clist;
class MWin;
class ConWin_Base;
class Con_Edit;
extern HINSTANCE Hinst;
/////////////////////////////
//#########################//
/*###########λͼ##########*/
//#########################//
////////////////////////////
//�������̣�1.�����Initbmp��ʼ������   2.Loadbmp����λͼ   3.SetBmp����ͼƬ
class imgbmp;
typedef struct HWND_list Hlist;
void SetBmp(int num, imgbmp b, int x, int y);//��λͼ�ŵ�������

//////////λͼ��Ϣ�ṹ��
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
	int snum;              //λͼ�ܸ���
	HINSTANCE hinst;       //ʵ��
	HDC i_hdc;             //λͼ�滭�豸
	IBMP* ibmp;            //λͼ����
	HDC m_hdc;             //�����ڻ滭�豸
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
/*############������########*/
//#########################//
/////////////////////////////
extern Clist winlist;
//////////
//////////���ھ���Ҵ��ڶ���
MWin* HwndFindMWin(HWND hwnd);
//////////
//////////ID�Ҵ��ڶ���
MWin* IDFindMWin(int id);
//////////
//////////����IDɾ������
int DelMWin(int id);
//////////
//////////��ͼ��Ϣ��
typedef struct PAINT_MSG
{
	int pid;
	int c1;
	int c2;
	int c3;
	int c4;
	wchar_t str[100];
}PAINTMSG;
//��������
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
	HWND Create(const wchar_t winname[], int w, int h,DWORD style= WS_OVERLAPPEDWINDOW | WS_VISIBLE);//��������
	HWND Createson(const wchar_t winname[], int x,int y,int w, int h, DWORD style, HWND parent);
	HWND Gethwnd() { return m_hwnd; }//��ȡ���ھ��
	void Setibmp(imgbmp* ibm);       //��λͼ���ݸ�������
	void SetHDC(HDC dc);             //����HDC
	HDC GetbkDC() { return bkhdc; }
	void Seticon(const wchar_t filename[]);
protected:
	WNDCLASS wndcls;    //���ڽṹ��
	HWND m_hwnd;        //���ھ��
	HICON m_ico;        //ͼ   ��
	int m_id;           //��������
	HDC m_hdc;          //�滭�豸
	PAINTMSG vpmsg[10];     //�滭��Ϣ����,�����10����Ϣ
	void initmsg(int i);
	HPEN hpen;        //����
	HBRUSH hbrush;    //��ˢ
	imgbmp* ib;       //λͼ
	HINSTANCE hinst;
	bool ifinit;
	Clist sonwin;
	HWND m_parent;
	//����λͼ
protected:
	HBITMAP chbmp;
	BITMAP cbmp;
	int client_w;
	int client_h;
	int ow;
	int oh;
	HDC bkhdc;

	//��ͼ����
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
	//��ͼ��������

	//�����ڿؼ�����
protected:
	Clist con;                //�ؼ�����
	void AllConRun(WPARAM wParam, LPARAM lParam);//����
public:
	void AddCon(void *icon);         //���ӿؼ�
	void DelCon(int ID);//ɾ���ؼ�
	void* Getcon(int ID);            //��ȡ�ؼ�
	//�ؼ��������
};

/////////////////////////////
//#########################//
/*############�ؼ���########*/
//#########################//
/////////////////////////////
#define CON_EDIT   0  //�༭��ؼ�
#define CON_BUTTON 1  //��ť�ؼ�
#define CON_WIN    2  //�Ӵ��ڿؼ�
#define CON_DRWABUTTON 3 //�Ի水ť



#define CON_SHOW 1
#define CON_HIDE 0
//�ؼ�ִ�к���
typedef void(*Conrun)(HWND hwnd,WPARAM wParam, LPARAM lParam);
//�����ؼ���
class ConWin_Base
{
public:
	ConWin_Base(HINSTANCE hInstance, HWND parent, int id, int type1);//id�Ǳ�ʶ��type�ǿؼ����ͣ�1����༭��2����ť
	HWND Gethwnd() { return c_hwnd; }      //��ȡ���ھ��
	ConWin_Base() {}
	void Setproc(Conrun run);              //����ִ�к���
	void Run(WPARAM wParam, LPARAM lParam);//ִ�лص�����
	int Getid() { return c_id; }           //��ÿؼ�ID
	int Gettype() { return c_type; }       //��ÿؼ�����
	virtual void Delself() {}
	void State(int s);                     //�رջ����ؼ�
protected:
	HWND c_hwnd;        //���
	HWND c_parent;      //������
	int c_type;         //�������� 1�Ǳ༭��  2�ǰ�ť
	int c_id;           //���ڵı�ʶid
	HINSTANCE c_hinst;  //����ʵ��
	Conrun proc;        //ִ�к���
	void init(HINSTANCE hInstance, HWND parent, int id, int type1);
};


//�༭����
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


//��ť��
//
//��׼��ť���к���

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




//�Ի�ؼ���

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
//#####ִ�к���######//
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
////////////////////////ʱ�亯��
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
