#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include "MWin.h"
#include "Mwin_Ex.h"
#include "winsocket.h"
//ÑÕÉ«
#define COLOR_BACK  RGB(0,70,140)
#define COLOR_FRAME RGB(165,233,242)
#define COLOR_MAIN  RGB(92,130,135)

//°´Å¥
#define ID_BU_RECV   1
#define ID_BU_RECVF 7
#define ID_BU_SEND1 2
#define ID_BU_SEND2 3
#define ID_BU_SENDF 8
#define ID_ED_T 4
#define ID_ED_MAX 5
#define ID_ED_RATE 6
void bu_send1(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam);
void bu_send2(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam);
void bu_recv(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam);
void bu_recvf(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam);
void edfunc_t(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam);
void edfunc_max(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam);
void edfunc_rate(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam);
void bu_sendf(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam);
void bu_connect(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam);
/////////////////////////////////////
extern MWin *main_win;
/////////////////////////////////////
extern imgbmp im;
extern MWin_axis *wax;
extern Mtimer_us mtime;
extern SKClient_TCP tcp;
extern int mission;
extern Con_Button *allbu[6];
extern Con_Edit *alled[3];
/////////////////////////////////////


