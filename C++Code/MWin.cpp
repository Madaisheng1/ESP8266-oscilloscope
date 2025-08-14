#include "MWin.h"

HINSTANCE Hinst;
/////////////////////////////
//#########################//
/*###########位图##########*/
//#########################//
////////////////////////////
imgbmp::imgbmp(HDC hdc, int num, HINSTANCE hinstance)
{
	if (hdc == NULL)
	{
		MessageBox(NULL, L"绘画设备为NULL", L"错误", MB_OK);
	}
	i_hdc = CreateCompatibleDC(hdc);
	if (i_hdc == NULL)
	{
		MessageBox(NULL, L"绘图设备加载失败", L"错误", MB_OK);
	}
	ibmp = (IBMP*)malloc(num * sizeof(IBMP));
	hinst = hinstance;
	snum = num;
	m_hdc = hdc;
}



void SetBmp(int num, imgbmp b, int x, int y)
{
	b.Setbmp(num, x, y);
}



void imgbmp::Initbmp(HDC hdc, int num, HINSTANCE hinstance)
{
	if (hdc == NULL)
	{
		MessageBox(NULL, L"绘画设备为NULL", L"错误", MB_OK);
	}
	i_hdc = CreateCompatibleDC(hdc);
	if (i_hdc == NULL)
	{
		MessageBox(NULL, L"绘图设备加载失败", L"错误", MB_OK);
	}
	ibmp = (IBMP*)malloc(num * sizeof(IBMP));
	hinst = hinstance;
	snum = num;
	m_hdc = hdc;
}

void imgbmp::Setbmp(int num, int x, int y, DWORD model)
{
	SelectObject(i_hdc, ibmp[num].hbmp);
	BitBlt(m_hdc, x, y, ibmp[num].w, ibmp[num].h, i_hdc, 0, 0, model);
}

void imgbmp::Zero()
{
	for (int i = 0; i < snum; i++)
	{
		DeleteObject(ibmp[i].hbmp);
	}
	free(ibmp);
}

void imgbmp::Delbmp(int num)
{
	DeleteObject(ibmp[num].hbmp);
}

void imgbmp::Loadbmp(int num, const wchar_t filename[], int w, int h)
{
	ibmp[num].hbmp = (HBITMAP)LoadImage(hinst, filename, IMAGE_BITMAP, w, h, LR_LOADFROMFILE);//LoadBitmap(hinstance, filename);
	GetObject(ibmp[num].hbmp, sizeof(BITMAP), &(ibmp[num].bmp));
	ibmp[num].h = h;
	ibmp[num].w = w;
}

/////////////////////////////
//#########################//
/*########主窗口函数########*/
//#########################//
////////////////////////////
Clist winlist;       //主窗口容器
////////////回调函数
void wm_create(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

}
void wm_command(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MWin*win = HwndFindMWin(hwnd);
	win->AllConRun(wParam, lParam);
}
void wm_paint(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT m_ps;
	MWin*win = HwndFindMWin(hwnd);
	HDC hdc = BeginPaint(hwnd, &m_ps);
	for (int i = 0; i < 10; i++)
	{
		switch (win->vpmsg[i].pid)
		{
		case 1:   //画圆
			Ellipse(win->bkhdc, win->vpmsg[i].c1 - win->vpmsg[i].c3, win->vpmsg[i].c2 - win->vpmsg[i].c3, win->vpmsg[i].c1 + win->vpmsg[i].c3, win->vpmsg[i].c2 + win->vpmsg[i].c3);
			DeleteObject(win->hpen);
			win->initmsg(i);
			break;
		case 2:   //矩形
			Rectangle(win->bkhdc, win->vpmsg[i].c1, win->vpmsg[i].c2, win->vpmsg[i].c3, win->vpmsg[i].c4);
			DeleteObject(win->hpen);
			win->initmsg(i);
			break;
		case 3:   //直线
			MoveToEx(win->bkhdc, win->vpmsg[i].c1, win->vpmsg[i].c2, NULL);
			LineTo(win->bkhdc, win->vpmsg[i].c3, win->vpmsg[i].c4);
			DeleteObject(win->hpen);
			win->initmsg(i);
			break;
		case 4:   //位图
			win->ib->Setbmp(win->vpmsg[i].c3, win->vpmsg[i].c1, win->vpmsg[i].c2);
			win->initmsg(i);
			break;
		case 5:   //文本
			SetBkMode(win->bkhdc, TRANSPARENT);
			TextOutW(win->bkhdc, win->vpmsg[i].c1, win->vpmsg[i].c2, win->vpmsg[i].str, win->vpmsg[i].c3);
			win->initmsg(i);
			break;
		case 6:   //背景填充纯色
			FillRect(win->bkhdc, (RECT*)win->vpmsg[i].c1, win->hbrush);
			DeleteObject(win->hbrush);
			free((RECT*)win->vpmsg[i].c1);
			win->initmsg(i);
			break;
		case 7:   //实心矩形
			FillRect(win->bkhdc, (RECT*)win->vpmsg[i].c1, win->hbrush);
			DeleteObject(win->hbrush);
			free((RECT*)win->vpmsg[i].c1);
			win->initmsg(i);
			break;
		case 8:
			Ellipse(win->bkhdc, win->vpmsg[i].c1 - win->vpmsg[i].c3, win->vpmsg[i].c2 - win->vpmsg[i].c3, win->vpmsg[i].c1 + win->vpmsg[i].c3, win->vpmsg[i].c2 + win->vpmsg[i].c3);
			DeleteObject(win->hpen);
			DeleteObject(win->hbrush);
			win->initmsg(i);
			break;
		case 9:
			win->ib->Setbmp(win->vpmsg[i].c4, win->vpmsg[i].c1, win->vpmsg[i].c2, SRCAND);
			win->ib->Setbmp(win->vpmsg[i].c3, win->vpmsg[i].c1, win->vpmsg[i].c2, SRCPAINT);
			win->initmsg(i);
			break;
		default:
			break;
		}
	}
	StretchBlt(hdc, 0, 0, win->client_w, win->client_h, win->bkhdc, 0, 0,win->ow,win->oh, SRCCOPY);
	EndPaint(hwnd, &m_ps);
}
void wm_size(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MWin*win = HwndFindMWin(hwnd);
	if (win != NULL)
	{
		RECT cr;
		GetClientRect(hwnd, &cr);
		win->client_h = cr.bottom - cr.top;
		win->client_w = cr.right - cr.left;
	}
}
void wm_close(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MWin*win = HwndFindMWin(hwnd);
	win->Delself();
}
void wm_drwaitem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MWin*win = HwndFindMWin(hwnd);
	LPDRAWITEMSTRUCT p = (LPDRAWITEMSTRUCT)lParam;
	ConWin_Base* c = ((ConWin_Base*)win->con.Findlist(p->CtlID));
	switch (c->Gettype())
	{
	case CON_DRWABUTTON:
	{
		HDC dc = CreateCompatibleDC(p->hDC);
		IBMP* ib = (((Con_DrawButton*)c)->cbmp);
		if (p->itemState&ODS_SELECTED)
		{
				SelectObject(dc, ((Con_DrawButton*)c)->cbmp[0].hbmp);
				BitBlt(p->hDC, 0, 0, ib[0].w, ib[0].h, dc, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(dc, ((Con_DrawButton*)c)->cbmp[1].hbmp);
			BitBlt(p->hDC, 0, 0, ib[1].w, ib[1].h, dc, 0, 0, SRCCOPY);
		}
		DeleteDC(dc);
	}
	break;
	default:
		break;
	}
}



LRESULT CALLBACK WinSunProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)//通过判断消息进行消息响应
	{
	case WM_DRAWITEM:
		wm_drwaitem(hwnd, uMsg, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_CREATE:
		wm_create(hwnd,uMsg,wParam,lParam);
		
		break;
	case WM_COMMAND:
		wm_command(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MOVE:
		break;
	case WM_PAINT:
		wm_paint(hwnd, uMsg, wParam, lParam);
		break;
	case WM_SIZE:
		wm_size(hwnd, uMsg, wParam, lParam);
		break;
	case WM_CLOSE:
		wm_close(hwnd, uMsg, wParam, lParam);
		break;
	case WM_DESTROY:
		if (winlist.Getnum() == 0)
		{
			LineState = LINE_WAITCLOSE;
			WinClose();
			LineState = LINE_CLOSED;
			PostQuitMessage(0);//发出WM_QUIT消息，结束消息循环，子窗口不要这个
		}
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//对不感兴趣的消息进行缺省处理，必须有该代码，否则程序有问题
	}
	return 0;
}
///////////////////
///////////////////
MWin* HwndFindMWin(HWND hwnd)
{
	Hlist *n;
	n = winlist.Gethead()->next;
	while (n != winlist.Getend())
	{
		if (((MWin*)(n->win))->Gethwnd() == hwnd)
		{
			return ((MWin*)(n->win));
		}
		n = n->next;
	}
	return NULL;
}
///////////////////
///////////////////
MWin* IDFindMWin(int id)
{
	return (MWin*)(winlist.Findlist(id));
}
///////////////////
///////////////////
int DelMWin(int id)
{
	return winlist.Dellist(id);
}
///////////////////
///////////////////
MWin::MWin(HINSTANCE hInstance, LPCWSTR classname, int id)
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
	wndcls.lpfnWndProc = WinSunProc;
	m_hwnd = NULL;

	m_id = id;
	hinst = hInstance;
	for (int i = 0; i < 10; i++)
	{
		vpmsg[i].c1 = 0;
		vpmsg[i].c2 = 0;
		vpmsg[i].c3 = 0;
		vpmsg[i].c4 = 0;
		vpmsg[i].pid = 0;
	}
	ifinit = false;
}

HWND MWin::Create(const wchar_t winname[],int w, int h, DWORD style)
{
	if (ifinit == false)
	{
		m_parent = NULL;
		RegisterClass(&wndcls);//向操作系统注册窗体
		m_hwnd = CreateWindow(wndcls.lpszClassName, winname, style, 100, 100, w, h, NULL, NULL, wndcls.hInstance, NULL);
		if (m_hwnd == NULL)
		{
			MessageBox(NULL, L"窗口创建失败", L"错误", MB_OK);
			Delself();
			return NULL;
		}
		//将窗口句柄加入链表
		winlist.Addlist(m_id, this);
		SetHDC(GetDC(m_hwnd));

		//背景位图初始化  
		bkhdc = CreateCompatibleDC(m_hdc);
		chbmp = CreateCompatibleBitmap(m_hdc, w, h);
		GetObject(chbmp, sizeof(BITMAP), &cbmp);
		SelectObject(bkhdc, chbmp);
		RECT r;
		r.bottom = h;
		r.left = 0;
		r.right = w;
		r.top = 0;
		FillRect(bkhdc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));
		client_h = h;
		client_w = w;
		oh = h;
		ow = w;
		ifinit = true;
		return m_hwnd;
	}
	else
	{
		return m_hwnd;
	}
}

HWND MWin::Createson(const wchar_t winname[], int x, int y,int w, int h, DWORD style, HWND parent)
{
	if(ifinit==false)
	{
		m_parent = parent;
		RegisterClass(&wndcls);//向操作系统注册窗体
		m_hwnd = CreateWindowEx(0,wndcls.lpszClassName, winname, style, x, y, w, h,parent, NULL, wndcls.hInstance, NULL);
		if (m_hwnd == NULL)
		{
			MessageBox(NULL, L"窗口创建失败", L"错误", MB_OK);
			Delself();
			return NULL;
		}
		//将窗口句柄加入链表
		winlist.Addlist(m_id, this);
		SetHDC(GetDC(m_hwnd));

		//背景位图初始化  
		bkhdc = CreateCompatibleDC(m_hdc);
		chbmp = CreateCompatibleBitmap(m_hdc, w, h);
		GetObject(chbmp, sizeof(BITMAP), &cbmp);
		SelectObject(bkhdc, chbmp);
		RECT r;
		r.bottom = h;
		r.left = 0;
		r.right = w;
		r.top = 0;
		FillRect(bkhdc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));
		client_h = h;
		client_w = w;
		oh = h;
		ow = w;
		ifinit = true;
		MWin *win = HwndFindMWin(parent);
		win->sonwin.Addlist(m_id, this);
	}
	return m_hwnd;
}

void MWin::SetHDC(HDC dc)
{
	m_hdc = dc;
}

void MWin::Seticon(const wchar_t filename[])
{
	
	wndcls.hIcon = (HICON)LoadImage(wndcls.hInstance, filename, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);	//设置窗体左上角的图标
	if (wndcls.hIcon == NULL)
	{
		MessageBox(NULL, L"1", L"1", MB_OK);
	}
}

void MWin::Setibmp(imgbmp * ibm)
{
	ib = ibm;
	ibm->ChangeDC(bkhdc);
}

void MWin::initmsg(int i)
{
	vpmsg[i].pid = 0;
}

void MWin::Delself()
{

	//删除子窗口
	sonwin.Reset();
	sonwin.Next();
	while (sonwin.iscurnull())
	{
		((MWin*)(sonwin.Getcurwin()))->Delself();
		sonwin.Reset();
		sonwin.Next();
	}
	sonwin.Zerolist();
	if (m_parent != NULL)
	{
		MWin *win = HwndFindMWin(m_parent);
		(win->sonwin).Dellist(m_id);
	}
	//删除控件
	con.Reset();
	con.Next();
	while (con.iscurnull())
	{
		DelCon(con.Getcurid());
		con.Reset();
		con.Next();
	}
	con.Zerolist();
	//删除自身
	int i = winlist.Dellist(m_id);
	if (i != 1)
	{
		MessageBox(NULL, L"链表删除失败,未能成功销毁窗口", L"错误", MB_OK);
	}
	//释放资源
	ReleaseDC(m_hwnd, bkhdc);
	DeleteObject(chbmp);
	DestroyWindow(m_hwnd);
}

void MWin::addmsg(int id, int x1, int x2, int x3, int x4)
{
	vpmsg->pid = id;
	vpmsg->c1 = x1;
	vpmsg->c2 = x2;
	vpmsg->c3 = x3;
	vpmsg->c4 = x4;
}

BOOL MWin::Pcircle(int cx,int cy, int R, int penwidth, int penstyle, COLORREF pencolor)
{
	hpen = CreatePen(penstyle, penwidth, pencolor); // 设置画笔
	for (int i = 0; i< 10; i++)
	{
		if (vpmsg[i].pid == 0)
		{
			vpmsg[i].c1 = cx;
			vpmsg[i].c2 = cy;
			vpmsg[i].c3 = R;
			vpmsg[i].pid = 1;
			SelectObject(bkhdc, hpen);
			InvalidateRect(m_hwnd, NULL, TRUE);
			return 1;
		}
	}
	return 0;
}

BOOL MWin::Prect(int x1, int y1, int x2, int y2, int penwidth, int penstyle, COLORREF pencolor)
{
	hpen = CreatePen(penstyle, penwidth, pencolor); // 设置画笔
	for (int i = 0; i < 10; i++)
	{
		if (vpmsg[i].pid == 0)
		{
			vpmsg[i].c1 = x1;
			vpmsg[i].c2 = y1;
			vpmsg[i].c3 = x2;
			vpmsg[i].c4 = y2;
			vpmsg[i].pid = 2;
			SelectObject(bkhdc, hpen);
			InvalidateRect(m_hwnd, NULL, TRUE);
			return 1;
		}
	}
	return 0;
}

BOOL MWin::Pline(int x1, int y1, int x2, int y2, int penwidth, int penstyle, COLORREF pencolor)
{
	hpen = CreatePen(penstyle, penwidth, pencolor); // 设置画笔
	for (int i = 0; i < 10; i++)
	{
		if (vpmsg[i].pid == 0)
		{
			vpmsg[i].c1 = x1;
			vpmsg[i].c2 = y1;
			vpmsg[i].c3 = x2;
			vpmsg[i].c4 = y2;
			vpmsg[i].pid = 3;
			SelectObject(bkhdc, hpen);
			InvalidateRect(m_hwnd, NULL, TRUE);
			return 1;
		}
	}
	return 0;
}

BOOL MWin::Psetbmp(int x, int y,int num)
{
	for (int i = 0; i < 10; i++)
	{
		if (vpmsg[i].pid == 0)
		{
			vpmsg[i].c1 = x;
			vpmsg[i].c2 = y;
			vpmsg[i].c3 = num;
			vpmsg[i].pid = 4;
			InvalidateRect(m_hwnd, NULL, TRUE);
			return 1;
		}
	}
	return 0;
}

BOOL MWin::Ptext(int x, int y, const wchar_t t[])
{
	for (int i = 0; i < 10; i++)
	{
		if (vpmsg[i].pid == 0)
		{
			vpmsg[i].c1 = x;
			vpmsg[i].c2 = y;
			vpmsg[i].c3 = strnumW(t);
			vpmsg[i].pid = 5;
			SelectObject(bkhdc, hpen);
			copystrW(vpmsg[i].str, t, strnumW(t)+1);
			InvalidateRect(m_hwnd, NULL, TRUE);
			return 1;
		}
	}
	return 0;
}

BOOL MWin::Psetbkcolor(COLORREF brushcolor)
{
	hbrush = CreateSolidBrush(brushcolor);
	for (int i = 0; i < 10; i++)
	{
		if (vpmsg[i].pid == 0)
		{
			RECT *r = (RECT*)malloc(sizeof(RECT));
			r->left = 0;
			r->top = 0;
			r->right = ow;
			r->bottom = oh;
			vpmsg[i].c1 = (int)r;
			vpmsg[i].pid = 6;
			SelectObject(bkhdc, hbrush);
			InvalidateRect(m_hwnd, NULL, TRUE);
			return 1;
		}
	}
	return 0;
}

BOOL MWin::Pfillrect(int x1, int y1, int x2, int y2, COLORREF brushcolor) //目前有问题
{
	hbrush = CreateSolidBrush(brushcolor);
	for (int i = 0; i < 10; i++)
	{
		if (vpmsg[i].pid == 0)
		{
			RECT *r = (RECT*)malloc(sizeof(RECT));
			r->left = x1;
			r->top = y1;
			r->right = x2;
			r->bottom = y2;
			vpmsg[i].c1 = (int)r;
			vpmsg[i].pid = 7;
			SelectObject(bkhdc, hbrush);
			InvalidateRect(m_hwnd, NULL, TRUE);
			return 1;
		}
	}
	return 0;
}

BOOL MWin::Pfillcircle(int cx, int cy, int R, int penwidth, int penstyle, COLORREF pencolor, COLORREF brushcolor)  //目前有问题
{
	hpen = CreatePen(penstyle, penwidth, pencolor); // 设置画笔
	hbrush = CreateSolidBrush(brushcolor);//设置画刷
	for (int i = 0; i < 10; i++)
	{
		if (vpmsg[i].pid == 0)
		{
			vpmsg[i].c1 = cx;
			vpmsg[i].c2 = cy;
			vpmsg[i].c3 = R;
			vpmsg[i].pid = 8;
			SelectObject(bkhdc, hpen);
			SelectObject(bkhdc, hbrush);
			InvalidateRect(m_hwnd, NULL, TRUE);
			return 1;
		}
	}
	return 0;
}

BOOL MWin::Pmaskbmp(int num, int masknum, int x, int y)
{
	for (int i = 0; i < 10; i++)
	{
		if (vpmsg[i].pid == 0)
		{
			vpmsg[i].c1 = x;
			vpmsg[i].c2 = y;
			vpmsg[i].c3 = num;
			vpmsg[i].c4 = masknum;
			vpmsg[i].pid = 9;
			InvalidateRect(m_hwnd, NULL, TRUE);
			return 1;
		}
	}
	return 0;
}

void MWin::AddCon(void * icon)
{
	con.Addlist(((ConWin_Base*)icon)->Getid(), icon);
}

void MWin::DelCon(int ID)
{
	ConWin_Base* c=(ConWin_Base*)con.Findlist(ID);
	switch (c->Gettype())
	{
	case CON_EDIT:
		((Con_Edit*)c)->Delself();
		break;
	case CON_BUTTON:
		((Con_Button*)c)->Delself();
		break;
	case CON_DRWABUTTON:
		((Con_DrawButton*)c)->Delself();
		break;
	default:
		break;
	}
	con.Dellist(ID);
}

void* MWin::Getcon(int ID)
{
	return ((void *)con.Findlist(ID));
}

void MWin::AllConRun(WPARAM wParam, LPARAM lParam)
{
	con.Reset();
	con.Next();
	while (con.iscurnull())
	{
		if (con.Getcurid() == LOWORD(wParam))
		{
			((ConWin_Base*)con.Getcurwin())->Run(wParam, lParam);
			break;
		}
		con.Next();
	}
}

/////////////////////////////
//#########################//
/*############控件类########*/
//#########################//
/////////////////////////////
/////////////////////////////
//############控件执行函数模板
//
void zhixingmubanhanshu(HWND hwndWPARAM, WPARAM wParam, LPARAM lParam)
{

}
//
/////////////////////////////
ConWin_Base::ConWin_Base(HINSTANCE hInstance, HWND parent, int id, int type1)
{
	c_hinst = hInstance;
	c_parent = parent;
	c_type = type1;
	c_id = id;
	c_hwnd = NULL;
	MWin*win = HwndFindMWin(parent);
	win->AddCon(this);
}


void ConWin_Base::Setproc(Conrun run)
{
	proc = run;
}

void ConWin_Base::Run(WPARAM wParam, LPARAM lParam)
{
	(*proc)(c_parent, wParam, lParam);
}

void ConWin_Base::State(int s)
{
	if (s == CON_SHOW)
	{
		EnableWindow(c_hwnd, TRUE);
	}
	else if(s == CON_HIDE)
	{
		EnableWindow(c_hwnd, FALSE);
	}
}

void ConWin_Base::init(HINSTANCE hInstance, HWND parent, int id, int type1)
{
	c_hinst = hInstance;
	c_parent = parent;
	c_type = type1;
	c_id = id;
	c_hwnd = NULL;
	MWin*win = HwndFindMWin(parent);
	win->AddCon(this);
}




//////////////////////////////////
////////////////////////编辑框控件
//////////////////////////////////


Con_Edit::Con_Edit(HINSTANCE hInstance, HWND parent, int id, int size)
{
	init(hInstance, parent, id, CON_EDIT);
	buff = (wchar_t*)malloc((size + 1) * sizeof(wchar_t));
	bsize = size;
}

HWND Con_Edit::Create(int x, int y, int w, int h, DWORD style)
{
	c_hwnd = CreateWindow(L"edit", NULL, style, x, y, w, h, c_parent, (HMENU)c_id, c_hinst, NULL);
	if (c_hwnd == NULL)
	{
		MessageBox(NULL, L"窗口创建失败", L"错误", MB_OK);
		Delself();
		return NULL;
	}
	return c_hwnd;
}

wchar_t * Con_Edit::GetText()
{
	GetWindowText(c_hwnd, buff, bsize);
	return buff;
}

void Con_Edit::SetText(const wchar_t text[])
{
	SetWindowText(c_hwnd, text);
}

void Con_Edit::Delself()
{
	free(buff);
	DestroyWindow(c_hwnd);
}





//////////////////////////////////
////////////////////////按钮控件
//////////////////////////////////

///////按钮控件函数

Con_Button::Con_Button(HINSTANCE hInstance, HWND parent, int id, const wchar_t content[])
{
	init(hInstance, parent, id, CON_BUTTON);
	copystrW(text, content, 20);
}

HWND Con_Button::Create(int x, int y, int w, int h, DWORD style)
{
	if (c_parent == NULL)
	{
		MessageBox(NULL, L"父窗口句柄不能为空2", L"错误", MB_OK);
		return NULL;
		return NULL;
	}
	c_hwnd = CreateWindow(L"button", text, style, x, y, w, h, c_parent, (HMENU)c_id, c_hinst, NULL);
	if (c_hwnd == NULL)
	{
		MessageBox(NULL, L"窗口创建失败", L"错误", MB_OK);
		Delself();
	}

	return c_hwnd;
}

void Con_Button::Delself()
{
	DestroyWindow(c_hwnd);
}




//////////////////////////////////
////////////////////////自绘按钮控件
//////////////////////////////////

Con_DrawButton::Con_DrawButton(HINSTANCE hInstance, HWND parent, int id, const wchar_t content[])
{
	init(hInstance, parent, id, CON_DRWABUTTON);
	copystrW(text, content, 20);
}

HWND Con_DrawButton::Create(int x, int y, int w, int h,  const wchar_t file1[], const wchar_t file2[], DWORD style)
{
	cbmp[0].hbmp = (HBITMAP)LoadImage(Hinst, file1, IMAGE_BITMAP, w, h, LR_LOADFROMFILE);
	GetObject(cbmp[0].hbmp, sizeof(BITMAP), &(cbmp[0].bmp));
	cbmp[0].h = h;
	cbmp[0].w = w;

	cbmp[1].hbmp = (HBITMAP)LoadImage(Hinst, file2, IMAGE_BITMAP, w, h, LR_LOADFROMFILE);
	GetObject(cbmp[0].hbmp, sizeof(BITMAP), &(cbmp[1].bmp));
	cbmp[1].h = h;
	cbmp[1].w = w;

	if (c_parent == NULL)
	{
		MessageBox(NULL, L"父窗口句柄不能为空2", L"错误", MB_OK);
		return NULL;
	}
	c_hwnd = CreateWindow(L"button", text, style, x, y, w, h, c_parent, (HMENU)c_id, c_hinst, NULL);
	if (c_hwnd == NULL)
	{
		MessageBox(NULL, L"窗口创建失败", L"错误", MB_OK);
		Delself();
		return NULL;
	}
	return c_hwnd;
}

void Con_DrawButton::Delself()
{
	DeleteObject((cbmp[0].hbmp));
	DeleteObject((cbmp[1].hbmp));
	DestroyWindow(c_hwnd);
}

//////////////////////////////////
////////////////////////运行函数
//////////////////////////////////
int LineState=0;
DWORD dwExitCode=0;
void MainRun(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MWinMain(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	LineState = LINE_CLOSED;
}


//////////////////////////////////
////////////////////////时间函数
//////////////////////////////////

Mtimer_us::Mtimer_us()
{
	QueryPerformanceFrequency(&freq_);
}

void Mtimer_us::begin()
{
	QueryPerformanceCounter(&begin_time);
	QueryPerformanceCounter(&gap_time);
}

int Mtimer_us::Getalltime()
{
	QueryPerformanceCounter(&end_time);
	QueryPerformanceCounter(&gap_time);
	return (int)((end_time.QuadPart - begin_time.QuadPart) * 1000000.0 / freq_.QuadPart);
}

int Mtimer_us::Getgaptime()
{
	int res;
	QueryPerformanceCounter(&end_time);
	res = (int)((end_time.QuadPart - gap_time.QuadPart) * 1000000.0 / freq_.QuadPart);
	QueryPerformanceCounter(&gap_time);
	return res;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////