#include <WinSock2.h>
#include "MWin.h"
#include <thread>
#include "scene.h"
#include "Mwin_Ex.h"
#include "winsocket.h"

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
//����������

int buf = 0;
char respond[5] = "1";
char respond2[2] = { 0 };
wchar_t num[10] = {};
int ti;

void show()
{
	axis->ResetBk();
	Sleep(50);
	mtime.begin();
	while (mission == 2)
	{
		tcp.SendMsg(respond, 1);
		tcp.RecvMsg((char *)(&buf), 4);
		ti = (int)(mtime.Getalltime() / 10000);
		if (ti >= 800)
		{
			mtime.begin();
			axis->ResetBk();
		}
		else
		{
			wax->Topoint(ti, buf);
		}
	}
	tcp.SendMsg(respond2, 1);
	tcp.RecvMsg((char*)(&buf), 4);
	buf = 0;
}

void generate()
{
	Sleep(50);
}

void MWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	
	Sleep(300);
	main_win->Ptext(50, 460, L"��   ��:");
	main_win->Ptext(50, 530, L"���ֵ:");
	main_win->Ptext(50, 590, L"ռ�ձ�:");
	Start_Socket();
	tcp.init(2526, "192.168.4.1");
	if (tcp.Run() == 0)
	{
		allbu[0]->State(CON_HIDE);
	}
	while (mission == 0);
	while (mission != -1)
	{
		switch (mission)
		{
		case 2:
			show();
			break;
		case 3:
			generate();
			break;
		case 0:
			Sleep(50);
			break;
		default:
			break;
		}
	}

	Clean_Socket();
}
////////////////////////////////////////////////////
////////////////////////////////////////////////////


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//////////////////////////////////////////////////
    //////////////////////////////////////////////////
    //////////////�����ǳ�ʼ������
	
	MWin win(hInstance, L"class1", 1);
	win.Seticon(L"pic\\face.ico");
	HWND mhwnd=win.Create(L"Elec" , 1200, 800, WS_MINIMIZE |WS_VISIBLE| WS_CAPTION| WS_OVERLAPPED| WS_SYSMENU| WS_POPUP);
	main_win = &win;
	//�����ڽ����ʼ��
	win.Pfillrect(0, 0, 1200, 800, COLOR_MAIN);
	win.Prect(350, 100, 1150, 700, 10, 0, COLOR_FRAME);//800*600
	win.Prect(10, 10, 340, 790, 10, 0, COLOR_FRAME);
	win.Prect(350, 10, 1150, 90, 10, 0, COLOR_FRAME);
	win.Prect(350, 710, 1150, 790, 10, 0, COLOR_FRAME);
	win.Prect(1160, 10, 1190, 790, 10, 0, COLOR_FRAME);
	win.Pline(10, 395, 335, 395, 10, 0, COLOR_FRAME);
	win.Prect(10, 10, 60, 60, 10, 0, COLOR_FRAME);
	win.Prect(10, 395, 60, 445, 10, 0, COLOR_FRAME);
	//�����ڰ�ť��ʼ��
	Con_Button bu_rc(hInstance, mhwnd, ID_BU_RECV, L"���ղ���");
	bu_rc.Setproc(bu_recv);//���ؼ���Ӧ������ؼ���
	bu_rc.Create(65, 15, 100, 45);//X,Y,��,��
	bu_rc.State(CON_HIDE);
	allbu[0] = &bu_rc;

	Con_Button bu_rcf(hInstance, mhwnd, ID_BU_RECVF, L"ֹͣ����");
	bu_rcf.Setproc(bu_recvf);//���ؼ���Ӧ������ؼ���
	bu_rcf.Create(65, 75, 100, 45);//X,Y,��,��
	bu_rcf.State(CON_HIDE);
	allbu[1] = &bu_rcf;

	Con_Button bu_con(hInstance, mhwnd, ID_BU_RECVF, L"�����豸");
	bu_con.Setproc(bu_connect);//���ؼ���Ӧ������ؼ���
	bu_con.Create(65, 125, 100, 45);//X,Y,��,��
	allbu[5] = &bu_con;

	Con_Button bu_sd1(hInstance, mhwnd, ID_BU_SEND1, L"���Ҳ�");
	bu_sd1.Setproc(bu_send1);//���ؼ���Ӧ������ؼ���
	bu_sd1.Create(65, 380, 100, 45);//X,Y,��,��
	allbu[2] = &bu_sd1;

	Con_Button bu_sd2(hInstance, mhwnd, ID_BU_SEND1, L"��ݲ�");
	bu_sd2.Setproc(bu_send2);//���ؼ���Ӧ������ؼ���
	bu_sd2.Create(180, 380, 100, 45);//X,Y,��,��
	allbu[3] = &bu_sd2;
	
	Con_Button bu_sdf(hInstance, mhwnd, ID_BU_SENDF, L"��������");
	bu_sdf.Setproc(bu_sendf);//���ؼ���Ӧ������ؼ���
	bu_sdf.Create(100, 700, 100, 45);//X,Y,��,��
	bu_sdf.State(CON_HIDE);
	allbu[4] = &bu_sdf;

	bu_sd2.State(CON_HIDE);
	bu_sd1.State(CON_HIDE);

	im.Initbmp(win.GetbkDC(), 1, hInstance);
	im.Loadbmp(0, L"pic\\enter.bmp", 30, 30);
	win.Setibmp(&im);
	//�����ڱ༭���ؼ�
	Con_Edit e_t(hInstance, mhwnd, ID_ED_T, 20);
	Con_Edit e_max(hInstance, mhwnd, ID_ED_T, 20);
	Con_Edit e_rate(hInstance, mhwnd, ID_ED_T, 20);
	e_t.Setproc(edfunc_t);
	e_t.Setproc(edfunc_max);
	e_rate.Setproc(edfunc_rate);
	e_t.Create(100, 420+10, 100, 30);
	e_max.Create(100, 480+10, 100, 30);
	e_rate.Create(100, 540+10, 100, 30);
	alled[0] = &e_t;
	alled[1] = &e_max;
	alled[2] = &e_rate;
	
	//�����ᴰ�ڳ�ʼ��
	wchar_t cnm[10] = L"123";
	MWin_axis ax(hInstance, cnm);
	ax.Create(L"", 340, 90, 800, 600, mhwnd, WS_CHILD | WS_BORDER|WS_VISIBLE);
	ax.SetBk(5,500, 50);
	ax.Setpen(RGB(255, 188, 72), 2);
	wax = &ax;
	
	///////////////////////////////////////////////////
    ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////
	Hinst = hInstance;
	thread MainLine(MainRun, hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	LineState = LINE_RUN;
	MainLine.detach();
	//��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))//�����Ϣ����WM_QUIT,���ط���ֵ�������Ϣ��WM_QUIT��������
	{
		TranslateMessage(&msg);//������Ϣ�����WM_KEYDOWN��WM_KEYUP�����һ��WM_CHAR��Ϣ
		DispatchMessage(&msg);//�ɷ���Ϣ
	}
	HANDLE hThread = MainLine.native_handle();
	GetExitCodeThread(hThread, &dwExitCode);
	if (dwExitCode == STILL_ACTIVE)
	{
		if (!TerminateThread(hThread, 0))
		{
			MessageBox(NULL, L"ERROR", L"�߳̽���ʧ��", MB_OK);
		}
	}
	
}

//�������ڹر�ʱִ�еĺ���
void WinClose()
{
	mission = -1;

}
