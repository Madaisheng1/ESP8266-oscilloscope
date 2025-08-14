#include "Mwin_Ex.h"
MWin_axis *axis;



LRESULT CALLBACK AxisProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)//通过判断消息进行消息响应
	{
	case WM_DRAWITEM:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_MOVE:
		break;
	case WM_PAINT:
	{
		
		PAINTSTRUCT m_ps;
		MWin*win = HwndFindMWin(hwnd);
		HDC hdc = BeginPaint(hwnd, &m_ps);
		for (int i = 0; i < 5; i++)
		{
			switch (axis->msg[i][0])
			{
			case -2:
			{
				SelectObject(axis->hhdc, axis->hpen);
				MoveToEx(axis->hhdc, axis->msg[i][1], axis->msg[i][2], NULL);
				LineTo(axis->hhdc, axis->msg[i][1], axis->msg[i][2]);

				StretchBlt(axis->hhdc, 0, 0, axis->client_w, axis->client_h, axis->bkhdc, 0, 0, axis->ow, axis->oh, SRCCOPY);
				axis->DelMsg(i);
				break;
			}
			case -1:
			{
				axis->hbrush = CreateSolidBrush(BLACK_BRUSH);
				SelectObject(axis->bkhdc, axis->hbrush);
				RECT rect;
				rect.bottom = axis->client_h;
				rect.top = 0;
				rect.left = 0;
				rect.right = axis->client_w;
				FillRect(axis->bkhdc, &rect, axis->hbrush);
				axis->hpen = CreatePen(0, 3, RGB(255, 255, 255)); // 设置画笔
				SelectObject(axis->bkhdc, axis->hpen);
				MoveToEx(axis->bkhdc, 0, 0, NULL);
				LineTo(axis->bkhdc, 0, 600);

				MoveToEx(axis->bkhdc, 0, 480, NULL);
				LineTo(axis->bkhdc, 800, 480);
				DeleteObject(axis->hpen);

				axis->hpen = CreatePen(0, 1, RGB(255, 255, 255)); // 设置画笔
				SelectObject(axis->bkhdc, axis->hpen);

				MoveToEx(axis->bkhdc, 0, 120, NULL);
				LineTo(axis->bkhdc, 800, 120);
				MoveToEx(axis->bkhdc, 0, 240, NULL);
				LineTo(axis->bkhdc, 800, 240);
				MoveToEx(axis->bkhdc, 0, 360, NULL);
				LineTo(axis->bkhdc, 800, 360);



				for (int i = 0; i <= 800; i = i + axis->xlgap)
				{
					MoveToEx(axis->bkhdc, i, 0, NULL);
					LineTo(axis->bkhdc, i, 600);
				}
				DeleteObject(axis->hbrush);
				DeleteObject(axis->hpen);
				axis->DelMsg(i);
				
				StretchBlt(axis->hhdc, 0, 0, axis->client_w, axis->client_h, axis->bkhdc, 0, 0, axis->ow, axis->oh, SRCCOPY);
				break;
			}
			case 1:
			{
				SelectObject(axis->hhdc, axis->hpen);
				MoveToEx(axis->hhdc, axis->msg[i][1], axis->msg[i][2], NULL);
				LineTo(axis->hhdc, axis->msg[i][1], axis->msg[i][2]);
				
				axis->DelMsg(i);
				break;
			}
			case 2:
			{
				
				LineTo(axis->hhdc, axis->msg[i][1], axis->msg[i][2]);
				axis->DelMsg(i);
				break;
			}
			case 3:
			{
				axis->Setline((COLORREF)axis->msg[i][1], axis->msg[i][2]);
				axis->DelMsg(i);
				break;
			}
			default:
				break;
			}
		}
		StretchBlt(hdc, 0, 0, axis->client_w, axis->client_h, axis->hhdc, 0, 0, axis->ow, axis->oh, SRCCOPY);
		EndPaint(hwnd, &m_ps);
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
	}
		break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//对不感兴趣的消息进行缺省处理，必须有该代码，否则程序有问题
	}
	return 0;
}

MWin_axis::MWin_axis(HINSTANCE hInstance, LPCWSTR classname)
{
	wndcls.hInstance = hInstance;//设置窗体所属的应用程序实例
	wndcls.cbClsExtra = 0;       //类的额外内存，默认为0即可
	wndcls.cbWndExtra = 0;       //窗口的额外内存，默认为0即可
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//获取画刷句柄（将返回的HGDIOBJ进行强制类型转换）
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);//设置光标
	wndcls.hIcon = LoadIcon(wndcls.hInstance, IDI_ERROR);	//设置窗体左上角的图标
	wndcls.lpszClassName = classname;//设置窗体的类名
	wndcls.lpszMenuName = NULL;      //设置窗体的菜单,没有，填NULL
	wndcls.style = CS_HREDRAW | CS_VREDRAW;//设置窗体风格为水平重画和垂直重画
	wndcls.lpfnWndProc = AxisProc;
	m_hwnd = NULL;

	hinst = hInstance;
	ifinit = FALSE;
}

HWND MWin_axis::Create(const wchar_t winname[], int x, int y, int w, int h, HWND parent, DWORD style)
{
	if (ifinit == false)
	{
		m_parent = NULL;
		RegisterClass(&wndcls);//向操作系统注册窗体
		m_hwnd = CreateWindow(wndcls.lpszClassName, winname, style, x, y, w, h, parent, NULL, wndcls.hInstance, NULL);
		if (m_hwnd == NULL)
		{
			MessageBox(NULL, L"窗口创建失败", L"错误", MB_OK);
			Delself();
			return NULL;
		}
		m_hdc = GetDC(m_hwnd);
		//背景位图初始化 
		hhdc = CreateCompatibleDC(m_hdc);
		mhbmp = CreateCompatibleBitmap(m_hdc, w, h);
		GetObject(mhbmp, sizeof(BITMAP), &mbmp);
		SelectObject(hhdc, mhbmp);

		bkhdc = CreateCompatibleDC(hhdc);
		chbmp = CreateCompatibleBitmap(hhdc, w, h);
		GetObject(chbmp, sizeof(BITMAP), &cbmp);
		SelectObject(bkhdc, chbmp);

		
		RECT r;
		r.bottom = h;
		r.left = 0;
		r.right = w;
		r.top = 0;
		FillRect(bkhdc, &r, (HBRUSH)GetStockObject(BLACK_BRUSH));
		client_h = h;
		client_w = w;
		oh = h;
		ow = w;
		ifinit = true;
		axis = this;
		return m_hwnd;
	}
	else
	{
		return m_hwnd;
	}
}

void MWin_axis::DelMsg(int i)
{
	msg[i][0] = 0;
	msg[i][1] = 0;
	msg[i][2] = 0;
	msg[i][3] = 0;
	msg[i][4] = 0;
}

void MWin_axis::Setpoint(int x, int y)
{

	for (int i = 0; i < 5; i++)
	{
		if (msg[i][0] == 0)
		{
			msg[i][0] = 1;
			msg[i][1] = xgap * x;
			msg[i][2] = 480 - ygap * y;
			break;
		}
	}
	InvalidateRect(m_hwnd, NULL, FALSE);
}

void MWin_axis::Setpen(COLORREF color, int pensize)
{
	for (int i = 0; i < 5; i++)
	{
		if (msg[i][0] == 0)
		{
			msg[i][0] = 3;
			msg[i][1] = color;
			msg[i][2] = pensize;
			break;
		}
	}
	InvalidateRect(m_hwnd, NULL, FALSE);
}

void MWin_axis::Setline(COLORREF color, int penwidth)
{
	DeleteObject(hpen);
	hpen = CreatePen(0, penwidth, color); // 设置画笔
	//SelectObject(m_hdc, hpen);
}

void MWin_axis::Topoint(int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		if (msg[i][0] == 0)
		{
			msg[i][0] = 2;
			msg[i][1] = xgap * x;
			msg[i][2] = 480 - ygap * y;
			break;
		}
	}
	InvalidateRect(m_hwnd, NULL, FALSE);
}

void MWin_axis::Delself()
{
	DestroyWindow(m_hwnd);
}

void MWin_axis::SetBk(int xl,int xm, int ym)
{
	for (int i = 0; i < 5; i++)
	{
		if (msg[i][0] == 0)
		{
			msg[i][0] = -1;
			break;
		}
	}
	y_max = ym;
	x_max = xm;
	xgap = 800 / x_max;
	ygap = 360 / y_max;
	xlgap = 800/xl;
	InvalidateRect(m_hwnd, NULL, FALSE);
}

void MWin_axis::ResetBk()
{
	for (int i = 0; i < 5; i++)
	{
		if (msg[i][0] == 0)
		{
			msg[i][0] = -2;
			break;
		}
	}
	InvalidateRect(m_hwnd, NULL, FALSE);
}


