#include "scene.h"
///////////////////////////
MWin_axis *wax;
///////////////////////////
imgbmp im;
///////////////////////////
MWin *main_win;
Mtimer_us mtime;
SKClient_TCP tcp;
Con_Button *allbu[6];
Con_Edit *alled[3];

int mission=0;

//信号发生器参数
#define WAVE_ZIGZAG 1
#define WAVE
///////////////////////////

///////////////////////////
void bu_recv(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam)
{
	mission = 0;
	Sleep(50);
	char buff[5] = "02";
	main_win->Psetbmp(20, 20, 0);
	main_win->Pfillrect(20, 405, 50, 435, COLOR_MAIN);
	tcp.SendMsg(buff, 2);
	tcp.RecvMsg(buff, 4);
	Sleep(50);
	mission = 2;
	allbu[0]->State(CON_HIDE);
	allbu[1]->State(CON_SHOW);
	allbu[2]->State(CON_HIDE);
	allbu[3]->State(CON_HIDE);
	allbu[4]->State(CON_HIDE);
}
void bu_recvf(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam)
{
	mission = 0;
	main_win->Pfillrect(20, 20, 50, 50, COLOR_MAIN);
	allbu[0]->State(CON_SHOW);
	allbu[1]->State(CON_HIDE);
	allbu[2]->State(CON_SHOW);
	allbu[3]->State(CON_SHOW);
	allbu[4]->State(CON_HIDE);
}

void bu_connect(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam)
{
	if (tcp.Run())
	{
		allbu[0]->State(CON_SHOW);
	}
}

int cheakstrnum(wchar_t *s)
{
	if (s[0] == '\0')
	{
		MessageBox(NULL, L"请输入内容", L"error", MB_OK);
		return 0;
	}
	for (int i = 0; i < 20 && s[i] != '\0'; i++)
	{
		if (s[i] <= 57 && s[i] >= 48)
		{

		}
		else
		{
			MessageBox(NULL, L"输入必须是数字", L"error", MB_OK);
			return 0;
		}
	}
	return 1;
}


void bu_send1(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam)
{
	mission = 3;
	Sleep(50);

	
	main_win->Pfillrect(20, 20, 50, 50, COLOR_MAIN);
	main_win->Psetbmp(20, 405, 0);
	
	wchar_t *tt;
	wchar_t *tmax;
	tt = alled[0]->GetText();
	tmax = alled[1]->GetText();
	int ck;
	ck = cheakstrnum(tt)&cheakstrnum(tmax);
	if (ck == 1)
	{
		char buff[5] = "03";
		tcp.SendMsg(buff, 2);
		tcp.RecvMsg(buff, 4);
		int nn[5];
		nn[0] = 1;
		nn[1] = strtointW(tt);
		nn[2] = strtointW(tmax);
		nn[3] = 0;
		nn[4] = 0;
		tcp.SendMsg((char*)nn, 20);
		allbu[0]->State(CON_HIDE);
		allbu[1]->State(CON_HIDE);
		allbu[2]->State(CON_HIDE);
		allbu[3]->State(CON_HIDE);
		allbu[4]->State(CON_SHOW);
	}
}


void bu_send2(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam)
{
	wchar_t *trate;
	trate = alled[2]->GetText();
	mission = 3;
	Sleep(50);
	main_win->Pfillrect(20, 20, 50, 50, COLOR_MAIN);
	main_win->Psetbmp(20, 405, 0);
	char buff[5] = "03";
	tcp.SendMsg(buff, 2);
	tcp.RecvMsg(buff, 4);
	wchar_t *tt;
	wchar_t *tmax;
	
	tt = alled[0]->GetText();
	tmax = alled[1]->GetText();
	
	int ck=0;
	ck=cheakstrnum(tt)&cheakstrnum(trate)&cheakstrnum(tmax);
	if (ck == 1)
	{

		int nn[5];
		nn[0] = 2;
		nn[1] = strtointW(tt);
		nn[2] = strtointW(tmax);
		nn[3] = strtointW(trate);
		nn[4] = 0;
		tcp.SendMsg((char*)nn, 20);
		allbu[0]->State(CON_HIDE);
		allbu[1]->State(CON_HIDE);
		allbu[2]->State(CON_HIDE);
		allbu[3]->State(CON_HIDE);
		allbu[4]->State(CON_SHOW);
	}
}

void bu_sendf(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam)
{
	main_win->Pfillrect(20, 405, 50, 435, COLOR_MAIN);
	char buff[5] = "01";
	tcp.SendMsg(buff, 2);
	allbu[0]->State(CON_SHOW);
	allbu[1]->State(CON_HIDE);
	allbu[2]->State(CON_SHOW);
	allbu[3]->State(CON_SHOW);
	allbu[4]->State(CON_HIDE);
}

void edfunc_t(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam)
{

}
void edfunc_max(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam)
{

}
void edfunc_rate(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam)
{

}
///////////////////////////