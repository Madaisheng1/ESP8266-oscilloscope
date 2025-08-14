#include "winsocket.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib,"Ws2_32.lib")

WSADATA wsadata;
WORD version;//版本号
BOOL socket_star = FALSE;

void Start_Socket()
{
	memset(&wsadata, 0, sizeof(wsadata));
	version = MAKEWORD(2, 2);//版本号
	int nret=WSAStartup(version, &wsadata);
	if (nret != 0)
	{
		MessageBox(NULL, L"初始化失败", L"Error", MB_OK);
		exit(0);
	}
	socket_star = TRUE;
}

void Clean_Socket()
{
	WSACleanup();
}

//////////////////////////////////////
BasicSocket::BasicSocket()
{
	if (socket_star = FALSE)
	{
		MessageBox(NULL, L"未初始化", L"Error", MB_OK);
		exit(0);
	}
}

void BasicSocket::InitAddr(ADDRESS_FAMILY famliy1, u_short TCPnum, const wchar_t ip1[], sockaddr_in * sa)
{
	sa->sin_family = famliy1;
	sa->sin_port = htons(TCPnum);
	InetPton(AF_INET, ip1, &sa->sin_addr.S_un.S_addr);
}

void BasicSocket::InitAddr(ADDRESS_FAMILY famliy1, u_short TCPnum, ULONG ip1, sockaddr_in * sa)
{
	sa->sin_family = famliy1;
	sa->sin_port = htons(TCPnum);
	sa->sin_addr.S_un.S_addr = ip1;
}



SOCKET BasicSocket::CreateSocket(SOCKET& sk, int af, int type, int protocol)
{
	sk = socket(af, type, protocol);
	if (sk == INVALID_SOCKET)
	{
		int err = WSAGetLastError();
		if (err == WSAEAFNOSUPPORT)
			MessageBox(NULL, L"不支持所指定的通信域或地址簇", L"Error", MB_OK);
		else 		if (err == WSAEMFILE)
			MessageBox(NULL, L"创建的套接字数目超过限额", L"Error", MB_OK);
		else		if (err == WSAENOBUFS)
			MessageBox(NULL, L"没有可用的缓冲区", L"Error", MB_OK);
		else		if (err == WSAEPROTONOSUPPORT)
			MessageBox(NULL, L"不支持指定的协议", L"Error", MB_OK);
		else		if (err == WSAEPROTOTYPE)
			MessageBox(NULL, L"指定协议类型不适用于本套接字", L"Error", MB_OK);
		else 		if (err == WSAESOCKTNOSUPPORT)
			MessageBox(NULL, L"本地址簇中不支持该类型的套接字", L"Error", MB_OK);

		closesocket(sk);
		return INVALID_SOCKET;
	}
	else 	 return sk;

}

int BasicSocket::Bindsk(SOCKET &sk, sockaddr* addr)
{
	int cheak = bind(sk, addr, sizeof(sockaddr));
	if (cheak != 0)
	{
		cheak = WSAGetLastError();
		if (cheak == WSAEAFNOSUPPORT)
			MessageBox(NULL, L"不支持所指定的通信域或地址簇", L"Error", MB_OK);
		else if (cheak == WSAEADDRINUSE)
			MessageBox(NULL, L"指定了已在使用的端口", L"Error", MB_OK);
		else if (cheak == WSAEFAULT)
			MessageBox(NULL, L"入口参数错误", L"Error", MB_OK);
		else if (cheak == WSAEINVAL)
			MessageBox(NULL, L"套接字已绑定", L"Error", MB_OK);
		else if (cheak == WSAENOBUFS)
			MessageBox(NULL, L"没有可用缓冲区", L"Error", MB_OK);
		else if (cheak == WSAENOTSOCK)
			MessageBox(NULL, L"描述符不是套接字", L"Error", MB_OK);
	}
	return cheak;
}

int BasicSocket::Listen(SOCKET &sk, int backlog)
{
	int cheak = listen(sk, backlog);
	if (cheak != 0)
	{
		cheak = WSAGetLastError();
		if (cheak == WSAEADDRINUSE)
			MessageBox(NULL, L"监听地址正在使用中", L"Error", MB_OK);
		else if (cheak == WSAEINVAL)
			MessageBox(NULL, L"套接字未绑定或已被链接", L"Error", MB_OK);
		else if (cheak == WSAEISCONN)
			MessageBox(NULL, L"套接字已被链接", L"Error", MB_OK);
		else if (cheak == WSAEMFILE)
			MessageBox(NULL, L"无可用文件描述符", L"Error", MB_OK);
		else if (cheak == WSAENOBUFS)
			MessageBox(NULL, L"无可用缓冲区空间", L"Error", MB_OK);
		else if (cheak == WSAENOTSOCK)
			MessageBox(NULL, L"描述符不是套接字", L"Error", MB_OK);
		else if (cheak == WSAEOPNOTSUPP)
			MessageBox(NULL, L"套接字不支持监听", L"Error", MB_OK);
	}
	return cheak;
}

int BasicSocket::Connect(SOCKET &sk, sockaddr* name, int namelen)

{
	int cheak = connect(sk, name, namelen);
	if (cheak == SOCKET_ERROR)
	{

		cheak = WSAGetLastError();
		if (cheak == WSAEADDRINUSE)
			MessageBox(NULL, L"地址已在使用", L"Error-connect", MB_OK);
		else if (cheak == WSAEINTR)
			MessageBox(NULL, L"取消一个阻塞的调用", L"Error-connect", MB_OK);
		else if (cheak == WSAEADDRNOTAVAIL)
			MessageBox(NULL, L"找不到所指地址", L"Error-connect", MB_OK);
		else if (cheak == WSAVERNOTSUPPORTED)
			MessageBox(NULL, L"所指地址无法与套接字一起使用", L"Error-connect", MB_OK);
		else if (cheak == WSAECONNREFUSED)
			MessageBox(NULL, L"连接尝试被强制拒绝", L"Error-connect", MB_OK);
		else if (cheak == WSAEDESTADDRREQ)
			MessageBox(NULL, L"需要目的地址", L"Error-connect", MB_OK);
		else if (cheak == WSAEFAULT)
			MessageBox(NULL, L"namelen参数不正确", L"Error-connect", MB_OK);
		else if (cheak == WSAEINVAL)
			MessageBox(NULL, L"套接字没准备好与地址捆绑", L"Error-connect", MB_OK);
		else if (cheak == WSAEISCONN)
			MessageBox(NULL, L"套接字早已连接", L"Error-connect", MB_OK);
		else if (cheak == WSAEMFILE)
			MessageBox(NULL, L"无多余的文件描述符", L"Error-connect", MB_OK);
		else if (cheak == WSAENETUNREACH)
			MessageBox(NULL, L"无法从主机访问网络", L"Error-connect", MB_OK);
		else if (cheak == WSAENOBUFS)
			MessageBox(NULL, L"无可用缓冲区", L"Error-connect", MB_OK);
		else if (cheak == WSAENOTSOCK)
			MessageBox(NULL, L"描述符不是一个套接字", L"Error-connect", MB_OK);
		else if (cheak == WSAETIMEDOUT)
			MessageBox(NULL, L"连接超时", L"Error-connect", MB_OK);
		else if (cheak == WSAEWOULDBLOCK)
			MessageBox(NULL, L"非阻塞方式且连接不能立即建立", L"Error-connect", MB_OK);
	}
	return cheak;
}

int BasicSocket::Accept(SOCKET&sk, sockaddr* addr, SOCKET&s)
{
	int cheak = 0;
	int a = sizeof(sockaddr);
	s = accept(sk, addr, &a);
	if (s == INVALID_SOCKET)
	{
		cheak = WSAGetLastError();
		if (cheak == WSAEFAULT)
			MessageBox(NULL, L"长度错误", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAEINTR)
			MessageBox(NULL, L"取消一个阻塞的调用", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAEINVAL)
			MessageBox(NULL, L"未监听", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAEMFILE)
			MessageBox(NULL, L"无可用描述符", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAENOBUFS)
			MessageBox(NULL, L"无可用的缓冲区空间", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAENOTSOCK)
			MessageBox(NULL, L"描述符不是套接字", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAEOPNOTSUPP)
			MessageBox(NULL, L"该套接字不支持面向的服务", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAEWOULDBLOCK)
			MessageBox(NULL, L"该套接字为非阻塞方式且无可连接可供接受", L"Error-accpet", MB_OK);
	}
	return cheak;
}

int BasicSocket::Send(SOCKET&s, char*buf, int len, int flags)
{
	int nlentf = len;
	int idx = 0;
	int ret = 0;
	while (nlentf > 0)
	{
		ret = send(s, &buf[idx], nlentf, flags);
		if (ret == SOCKET_ERROR)
		{
			int cheak = WSAGetLastError();
			if (cheak == WSAEACCES)
				MessageBox(NULL, L"要求地址为广播地址", L"Error-send", MB_OK);
			else			if (cheak == WSAEINTR)
				MessageBox(NULL, L"取消阻塞的调用", L"Error-send", MB_OK);
			else			if (cheak == WSAEFAULT)
				MessageBox(NULL, L"buf参数不在有效位置", L"Error-send", MB_OK);
			else			if (cheak == WSAENETRESET)
				MessageBox(NULL, L"连接必须复位", L"Error-send", MB_OK);
			else			if (cheak == WSAENOTCONN)
				MessageBox(NULL, L"套接字未连接", L"Error-send", MB_OK);
			else			if (cheak == WSAENOTSOCK)
				MessageBox(NULL, L"描述符不是套接字", L"Error-send", MB_OK);
			else			if (cheak == WSAEOPNOTSUPP)
				MessageBox(NULL, L"已设置MSG_OOB,但套接字不是STREAM类型", L"Error-send", MB_OK);
			else			if (cheak == WSAESHUTDOWN)
				MessageBox(NULL, L"套接字已关闭", L"Error-send", MB_OK);
			else			if (cheak == WSAEWOULDBLOCK)
				MessageBox(NULL, L"套接字未非阻塞，发送操作会产生阻塞", L"Error-send", MB_OK);
			else			if (cheak == WSAEMSGSIZE)
				MessageBox(NULL, L"套接字为DGRAM类型且数据大于套接字所支持的最大值", L"Error-send", MB_OK);
			else			if (cheak == WSAEINVAL)
				MessageBox(NULL, L"套接字未捆绑", L"Error-send", MB_OK);
			else			if (cheak == WSAECONNABORTED)
				MessageBox(NULL, L"虚电路中断", L"Error-send", MB_OK);
			else			if (cheak == WSAECONNRESET)
				MessageBox(NULL, L"虚电路被远端复位", L"Error-send", MB_OK);
			else			if (cheak == WSAENOBUFS)
				MessageBox(NULL, L"缓冲区死锁", L"Error-send", MB_OK);
			return cheak;
		}
		else
		{
			nlentf -= ret;
			idx += ret;
		}
	}
	return 0;
}

int BasicSocket::Recieve(SOCKET&sk, char*buf, int len, int flags)
{
	int nlenft = len;
	int idx = 0;
	int ret = 0;
	int cheak = 0;
	while (nlenft > 0)
	{
		ret = recv(sk, &buf[idx], nlenft, 0);
		if (ret == SOCKET_ERROR)
		{
			cheak = WSAGetLastError();
			if (cheak == WSAENOTCONN)
				MessageBox(NULL, L"套接字未连接", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAEINTR)
				MessageBox(NULL, L"阻塞被取消", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAENOTSOCK)
				MessageBox(NULL, L"描述符不是套接字", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAEOPNOTSUPP)
				MessageBox(NULL, L"指定了MSG_OOB,但套接字不是STREAM", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAESHUTDOWN)
				MessageBox(NULL, L"套接字已关闭", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAEWOULDBLOCK)
				MessageBox(NULL, L"套接字为非阻塞,但被阻塞", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAEMSGSIZE)
				MessageBox(NULL, L"数据太大,无法装入缓冲区", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAEINVAL)
				MessageBox(NULL, L"套接字为捆绑", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAECONNABORTED)
				MessageBox(NULL, L"虚电路中断", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAECONNRESET)
				MessageBox(NULL, L"虚电路被远端复位", L"Error-Recieve", MB_OK);
			return cheak;
		}
		else if (ret == 0)
		{
			return 0;
		}
		idx += ret;
		nlenft -= ret;
	}
	return 0;
}

int BasicSocket::ShutDown(SOCKET&sk, int how)
{
	int cheak = shutdown(sk, how);
	if (cheak == SOCKET_ERROR)
	{
		cheak = WSAGetLastError();
		if (cheak == WSAEINVAL)
			MessageBox(NULL, L"how参数非法", L"Error-shut", MB_OK);
		else 		if (cheak == WSAENOTCONN)
			MessageBox(NULL, L"套接字未连接", L"Error-shut", MB_OK);
		else		if (cheak == WSAENOTSOCK)
			MessageBox(NULL, L"描述符不是套接字", L"Error-shut", MB_OK);
	}
	return cheak;
}

int BasicSocket::Close(SOCKET&sk)
{
	int cheak = closesocket(sk);
	if (cheak == SOCKET_ERROR)
	{
		cheak = WSAGetLastError();
		if (cheak == WSAEINTR)
			MessageBox(NULL, L"取消一个阻塞的调用", L"Error-shut", MB_OK);
		else 		if (cheak == WSAENOTSOCK)
			MessageBox(NULL, L"描述符不是套接字", L"Error-shut", MB_OK);
		else		if (cheak == WSAEWOULDBLOCK)
			MessageBox(NULL, L"非阻塞方式且SO_LINGER设为非零超时间隔", L"Error-shut", MB_OK);
		return cheak;
	}
	return cheak;
}


/////////////////////////////////////////////
void SKSever_TCP::SetAddr(unsigned short port)
{
	lis_addr.sin_family = AF_INET;
	lis_addr.sin_port = htons(port);
	lis_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
}

SKSever_TCP::SKSever_TCP(unsigned short port) :BasicSocket()
{
	lis_sk = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SetAddr(port);
	Bindsk(lis_sk, (sockaddr*)&lis_addr);
	num_conn = 0;
	max_conn = 0;
}

//
//
//
//
//需要自己编程的函数
//线程接收函数
void thread_pose_tcp(SKSever_TCP* sever)
{
	int cheak;
	for (int i = 0; i < sever->max_conn&&sever->son_line == TRUE; i++)
	{
		cheak = sever->Accept(sever->lis_sk, (sockaddr*)&(sever->cl_addr[sever->num_conn]), sever->acc_sk[sever->num_conn]);
		if (cheak == 0)
			sever->num_conn++;
	}
}
//消息函数
void SKSever_TCP::Run(int backlog)
{
	son_line = TRUE;
	Listen(lis_sk, backlog);
	max_conn = backlog;
	cl_addr = (sockaddr_in*)malloc(backlog * sizeof(sockaddr_in));
	acc_sk = (SOCKET*)malloc(backlog * sizeof(SOCKET));
	th = new std::thread(thread_pose_tcp, this);
	th->detach();
}

void SKSever_TCP::Sever_recv(char* buf, int len)
{
	std::cout << "正在等待连接";
	while (num_conn == 0);
	int r_n=0;
	std::cin >> r_n;
	while (r_n != 0)
	{
		int cheak = Recieve(acc_sk[0], buf, len, 0);
		if (cheak != 0)
		{
			std::cout << "recv-error";
		}
	}
	Send(acc_sk[0], buf, len, 0);
}

void SKSever_TCP::shutup()
{
	ShutDown(acc_sk[0], SD_SEND);
	char buff[10];
	Recieve(acc_sk[0], buff, 10, 0);
	Close(acc_sk[0]);
	Close(lis_sk);
	free(acc_sk);
	free(th);
	free(cl_addr);
}

//////////////////////////////////////////////
//
//客户端



SKClient_TCP::SKClient_TCP(int port, const char severadd[], BOOL name) :BasicSocket()
{
	c_sk = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
	sever_add.sin_family = AF_INET;
	sever_add.sin_port = htons(port);
	if (name == FALSE)
	{
		InetPtonA(AF_INET, severadd, &sever_add.sin_addr.S_un.S_addr);
	}
	else
	{
		/*hostent* ent = gethostbyname(severadd);
		if (ent == NULL)
			MessageBox(NULL, L"主机名输入错误", L"Error-gethostname", MB_OK);
		sever_add.sin_addr.S_un.S_addr = *((u_long*)ent->h_addr_list[0]);*/
	}
}

void SKClient_TCP::init(int port, const char severadd[], BOOL name)
{
	c_sk = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sever_add.sin_family = AF_INET;
	sever_add.sin_port = htons(port);
	if (name == FALSE)
	{
		InetPtonA(AF_INET, severadd, &sever_add.sin_addr.S_un.S_addr);
	}
	else
	{
		/*hostent* ent = gethostbyname(severadd);
		if (ent == NULL)
			MessageBox(NULL, L"主机名输入错误", L"Error-gethostname", MB_OK);
		sever_add.sin_addr.S_un.S_addr = *((u_long*)ent->h_addr_list[0]);*/
	}
}

int SKClient_TCP::Run()
{
	if (Connect(c_sk, (sockaddr*)&sever_add, sizeof(sockaddr_in)) != 0)
	{
		MessageBox(NULL, L"连接失败", L"Error", MB_OK);
		return 0;
	}
	return 1;
}

void SKClient_TCP::SendMsg(char*buf, int len)
{
	Send(c_sk, buf, len, 0);
	//Recieve(c_sk, buf, len, 0);
}

void SKClient_TCP::shutup()
{
	Close(c_sk);
}

void SKClient_TCP::RecvMsg(char * buf,int len)//len为缓冲区大小
{
	int num = cheakrecvnum();
	while (num == 0)
	{
		num = cheakrecvnum();
	}
	if (num <= len)
	{
		Recieve(c_sk, buf, num, 0);
	}
	else
	{
		printf("缓冲区不够");
	}
	
}

int SKClient_TCP::cheakrecvnum()
{
	u_long bytesToRecv;
	ioctlsocket(c_sk, FIONREAD, &bytesToRecv);
	return (int)bytesToRecv;
}

////////////
/////
////
////
////
/////socket容器
SK_vector::SK_vector()
{
	head.next = &end;
	head.sk = INVALID_SOCKET;
	end.sk = INVALID_SOCKET;
	end.next = NULL;
	num = 0;
}
SOCKET* SK_vector::operator[](int n)
{
	if (n < num)
	{
		SK_Line *now = &head;
		for (int i = 0; i <= n; i++)
		{
			now = now->next;
		}
		return &now->sk;
	}
	else
	{
		return NULL;
	}
}
SOCKET* SK_vector::it(int n)
{
	if (n < num)
	{
		SK_Line *now = &head;
		for (int i = 0; i <= n; i++)
		{
			now = now->next;
		}
		return &now->sk;
	}
	else
	{
		return NULL;
	}
}
void SK_vector::add(SOCKET as)
{
	SK_Line *l1, *lnow,*le;
	lnow = &head;
	le = &end;
	while (lnow->next != le)
	{
		lnow = lnow->next;
	}
	l1 = (SK_Line*)malloc(sizeof(SK_Line));
	l1->sk = as;
	l1->next = le;
	lnow->next = l1;
	num++;
}
void SK_vector::zero()
{
	SK_Line *now, *ne,*de,*le;
	now = &head;
	ne = now->next;
	le = &end;
	while (ne->next == le)
	{
		de = ne;
		ne = ne->next;
		free(de);
	}
	num = 0;
}
void SK_vector::dele(int n)
{
	if (n < num)
	{
		SK_Line *l1, *lnow, *le, *lf, *ln;
		lf = &head;
		le = &end;
		lnow = lf->next;
		ln = lnow->next;
		for (int i = 0; i <= n; i++)
		{
			lnow = lnow->next;
			ln = lnow->next;
			lf = lf->next;
		}
		free(lnow);
		lf->next = ln;
		num--;
	}
	else {
		MessageBox(NULL, L"SOCKET删除下标有误",L"Error",MB_OK);
		exit(0);
	}
}
int SK_vector::cheakend(int n)
{
	if (n == num)
		return 1;
	else return 0;
}
///////////
//select模型

SESever_TCP::SESever_TCP(unsigned short port) :BasicSocket()
{
	lis_sk = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	lis_addr.sin_family = AF_INET;
	lis_addr.sin_port = htons(port);
	lis_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	Bindsk(lis_sk, (sockaddr*)&lis_addr);
	Listen(lis_sk, 5);
	u_long block = 1;
	if (ioctlsocket(lis_sk, FIONBIO, &block) == SOCKET_ERROR)
	{
		MessageBox(NULL, L"ioctlsocket-error", L"Error", MB_OK);
		exit(0);
	}
}


void SESever_TCP::RestFd()
{
	FD_ZERO(&fdwrite);
	FD_ZERO(&fdread);
	FD_ZERO(&fdexcept);
	FD_SET(lis_sk, &fdread);
	FD_SET(lis_sk, &fdexcept);
	for (int i = 0; sk_vr.cheakend(i) == 0; i++)
	{
		FD_SET(*sk_vr.it(i), &fdread);
		FD_SET(*sk_vr.it(i), &fdexcept);
	}
	for (int i = 0; sk_vw.cheakend(i) == 0; i++)
	{
		FD_SET(*sk_vw.it(i), &fdwrite);
		FD_SET(*sk_vw.it(i), &fdexcept);
	}
}

void SESever_TCP::CheckAccept()
{
	if (FD_ISSET(lis_sk, &fdexcept))
	{
		MessageBox(NULL, L"监听套接字异常", L"Error", MB_OK);
		exit(0);
	}
	if (FD_ISSET(lis_sk, &fdread))
	{
		if (sk_vr.cheaknum() >= FD_SETSIZE - 1)
		{
			MessageBox(NULL, L"用户已达到上限", L"Error", MB_OK);
		}
		else
		{
			SOCKET cl;
			Accept(lis_sk, NULL, cl);
			sk_vr.add(cl);
			u_long block = 1;
			if (ioctlsocket(cl, FIONBIO, &block) == SOCKET_ERROR)
			{
				MessageBox(NULL, L"ioctlsocket-error", L"Error", MB_OK);
				exit(0);
			}
		}
	}
}

void SESever_TCP::Procssing()
{
	for (int i = 0; sk_vr.cheakend(i) == 0; i++)
	{
		if (FD_ISSET(*sk_vr.it(i), &fdexcept))
		{
			sk_vr.dele(i);
			i--;
		}
		else if (FD_ISSET(*sk_vr.it(i), &fdread))
		{
			//////读操作





			//////
		}
	}
	for (int i = 0; sk_vw.cheakend(i) == 0; i++)
	{
		if (FD_ISSET(*sk_vw.it(i), &fdexcept))
		{
			sk_vw.dele(i);
			i--;
		}
		else if (FD_ISSET(*sk_vr.it(i), &fdwrite))
		{
			/////////写操作



			////////
		}
	}
}

void SESever_TCP::Run()
{
	RestFd();
	select(0,&fdread, &fdwrite, &fdexcept, NULL);
	CheckAccept();
	Procssing();
}

void SESever_TCP::shutup()
{
	for (int i = 0; sk_vr.cheakend(i) == 0; i++)
	{
		ShutDown(*sk_vr.it(i), SD_SEND);
	}
	for (int i = 0; sk_vw.cheakend(i) == 0; i++)
	{
		ShutDown(*sk_vw.it(i), SD_SEND);
	}
	ShutDown(lis_sk, SD_SEND);
}

