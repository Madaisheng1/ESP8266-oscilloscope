#include "winsocket.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib,"Ws2_32.lib")

WSADATA wsadata;
WORD version;//�汾��
BOOL socket_star = FALSE;

void Start_Socket()
{
	memset(&wsadata, 0, sizeof(wsadata));
	version = MAKEWORD(2, 2);//�汾��
	int nret=WSAStartup(version, &wsadata);
	if (nret != 0)
	{
		MessageBox(NULL, L"��ʼ��ʧ��", L"Error", MB_OK);
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
		MessageBox(NULL, L"δ��ʼ��", L"Error", MB_OK);
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
			MessageBox(NULL, L"��֧����ָ����ͨ������ַ��", L"Error", MB_OK);
		else 		if (err == WSAEMFILE)
			MessageBox(NULL, L"�������׽�����Ŀ�����޶�", L"Error", MB_OK);
		else		if (err == WSAENOBUFS)
			MessageBox(NULL, L"û�п��õĻ�����", L"Error", MB_OK);
		else		if (err == WSAEPROTONOSUPPORT)
			MessageBox(NULL, L"��֧��ָ����Э��", L"Error", MB_OK);
		else		if (err == WSAEPROTOTYPE)
			MessageBox(NULL, L"ָ��Э�����Ͳ������ڱ��׽���", L"Error", MB_OK);
		else 		if (err == WSAESOCKTNOSUPPORT)
			MessageBox(NULL, L"����ַ���в�֧�ָ����͵��׽���", L"Error", MB_OK);

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
			MessageBox(NULL, L"��֧����ָ����ͨ������ַ��", L"Error", MB_OK);
		else if (cheak == WSAEADDRINUSE)
			MessageBox(NULL, L"ָ��������ʹ�õĶ˿�", L"Error", MB_OK);
		else if (cheak == WSAEFAULT)
			MessageBox(NULL, L"��ڲ�������", L"Error", MB_OK);
		else if (cheak == WSAEINVAL)
			MessageBox(NULL, L"�׽����Ѱ�", L"Error", MB_OK);
		else if (cheak == WSAENOBUFS)
			MessageBox(NULL, L"û�п��û�����", L"Error", MB_OK);
		else if (cheak == WSAENOTSOCK)
			MessageBox(NULL, L"�����������׽���", L"Error", MB_OK);
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
			MessageBox(NULL, L"������ַ����ʹ����", L"Error", MB_OK);
		else if (cheak == WSAEINVAL)
			MessageBox(NULL, L"�׽���δ�󶨻��ѱ�����", L"Error", MB_OK);
		else if (cheak == WSAEISCONN)
			MessageBox(NULL, L"�׽����ѱ�����", L"Error", MB_OK);
		else if (cheak == WSAEMFILE)
			MessageBox(NULL, L"�޿����ļ�������", L"Error", MB_OK);
		else if (cheak == WSAENOBUFS)
			MessageBox(NULL, L"�޿��û������ռ�", L"Error", MB_OK);
		else if (cheak == WSAENOTSOCK)
			MessageBox(NULL, L"�����������׽���", L"Error", MB_OK);
		else if (cheak == WSAEOPNOTSUPP)
			MessageBox(NULL, L"�׽��ֲ�֧�ּ���", L"Error", MB_OK);
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
			MessageBox(NULL, L"��ַ����ʹ��", L"Error-connect", MB_OK);
		else if (cheak == WSAEINTR)
			MessageBox(NULL, L"ȡ��һ�������ĵ���", L"Error-connect", MB_OK);
		else if (cheak == WSAEADDRNOTAVAIL)
			MessageBox(NULL, L"�Ҳ�����ָ��ַ", L"Error-connect", MB_OK);
		else if (cheak == WSAVERNOTSUPPORTED)
			MessageBox(NULL, L"��ָ��ַ�޷����׽���һ��ʹ��", L"Error-connect", MB_OK);
		else if (cheak == WSAECONNREFUSED)
			MessageBox(NULL, L"���ӳ��Ա�ǿ�ƾܾ�", L"Error-connect", MB_OK);
		else if (cheak == WSAEDESTADDRREQ)
			MessageBox(NULL, L"��ҪĿ�ĵ�ַ", L"Error-connect", MB_OK);
		else if (cheak == WSAEFAULT)
			MessageBox(NULL, L"namelen��������ȷ", L"Error-connect", MB_OK);
		else if (cheak == WSAEINVAL)
			MessageBox(NULL, L"�׽���û׼�������ַ����", L"Error-connect", MB_OK);
		else if (cheak == WSAEISCONN)
			MessageBox(NULL, L"�׽�����������", L"Error-connect", MB_OK);
		else if (cheak == WSAEMFILE)
			MessageBox(NULL, L"�޶�����ļ�������", L"Error-connect", MB_OK);
		else if (cheak == WSAENETUNREACH)
			MessageBox(NULL, L"�޷���������������", L"Error-connect", MB_OK);
		else if (cheak == WSAENOBUFS)
			MessageBox(NULL, L"�޿��û�����", L"Error-connect", MB_OK);
		else if (cheak == WSAENOTSOCK)
			MessageBox(NULL, L"����������һ���׽���", L"Error-connect", MB_OK);
		else if (cheak == WSAETIMEDOUT)
			MessageBox(NULL, L"���ӳ�ʱ", L"Error-connect", MB_OK);
		else if (cheak == WSAEWOULDBLOCK)
			MessageBox(NULL, L"��������ʽ�����Ӳ�����������", L"Error-connect", MB_OK);
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
			MessageBox(NULL, L"���ȴ���", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAEINTR)
			MessageBox(NULL, L"ȡ��һ�������ĵ���", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAEINVAL)
			MessageBox(NULL, L"δ����", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAEMFILE)
			MessageBox(NULL, L"�޿���������", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAENOBUFS)
			MessageBox(NULL, L"�޿��õĻ������ռ�", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAENOTSOCK)
			MessageBox(NULL, L"�����������׽���", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAEOPNOTSUPP)
			MessageBox(NULL, L"���׽��ֲ�֧������ķ���", L"Error-accpet", MB_OK);
		else 		if (cheak == WSAEWOULDBLOCK)
			MessageBox(NULL, L"���׽���Ϊ��������ʽ���޿����ӿɹ�����", L"Error-accpet", MB_OK);
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
				MessageBox(NULL, L"Ҫ���ַΪ�㲥��ַ", L"Error-send", MB_OK);
			else			if (cheak == WSAEINTR)
				MessageBox(NULL, L"ȡ�������ĵ���", L"Error-send", MB_OK);
			else			if (cheak == WSAEFAULT)
				MessageBox(NULL, L"buf����������Чλ��", L"Error-send", MB_OK);
			else			if (cheak == WSAENETRESET)
				MessageBox(NULL, L"���ӱ��븴λ", L"Error-send", MB_OK);
			else			if (cheak == WSAENOTCONN)
				MessageBox(NULL, L"�׽���δ����", L"Error-send", MB_OK);
			else			if (cheak == WSAENOTSOCK)
				MessageBox(NULL, L"�����������׽���", L"Error-send", MB_OK);
			else			if (cheak == WSAEOPNOTSUPP)
				MessageBox(NULL, L"������MSG_OOB,���׽��ֲ���STREAM����", L"Error-send", MB_OK);
			else			if (cheak == WSAESHUTDOWN)
				MessageBox(NULL, L"�׽����ѹر�", L"Error-send", MB_OK);
			else			if (cheak == WSAEWOULDBLOCK)
				MessageBox(NULL, L"�׽���δ�����������Ͳ������������", L"Error-send", MB_OK);
			else			if (cheak == WSAEMSGSIZE)
				MessageBox(NULL, L"�׽���ΪDGRAM���������ݴ����׽�����֧�ֵ����ֵ", L"Error-send", MB_OK);
			else			if (cheak == WSAEINVAL)
				MessageBox(NULL, L"�׽���δ����", L"Error-send", MB_OK);
			else			if (cheak == WSAECONNABORTED)
				MessageBox(NULL, L"���·�ж�", L"Error-send", MB_OK);
			else			if (cheak == WSAECONNRESET)
				MessageBox(NULL, L"���·��Զ�˸�λ", L"Error-send", MB_OK);
			else			if (cheak == WSAENOBUFS)
				MessageBox(NULL, L"����������", L"Error-send", MB_OK);
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
				MessageBox(NULL, L"�׽���δ����", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAEINTR)
				MessageBox(NULL, L"������ȡ��", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAENOTSOCK)
				MessageBox(NULL, L"�����������׽���", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAEOPNOTSUPP)
				MessageBox(NULL, L"ָ����MSG_OOB,���׽��ֲ���STREAM", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAESHUTDOWN)
				MessageBox(NULL, L"�׽����ѹر�", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAEWOULDBLOCK)
				MessageBox(NULL, L"�׽���Ϊ������,��������", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAEMSGSIZE)
				MessageBox(NULL, L"����̫��,�޷�װ�뻺����", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAEINVAL)
				MessageBox(NULL, L"�׽���Ϊ����", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAECONNABORTED)
				MessageBox(NULL, L"���·�ж�", L"Error-Recieve", MB_OK);
			else			if (cheak == WSAECONNRESET)
				MessageBox(NULL, L"���·��Զ�˸�λ", L"Error-Recieve", MB_OK);
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
			MessageBox(NULL, L"how�����Ƿ�", L"Error-shut", MB_OK);
		else 		if (cheak == WSAENOTCONN)
			MessageBox(NULL, L"�׽���δ����", L"Error-shut", MB_OK);
		else		if (cheak == WSAENOTSOCK)
			MessageBox(NULL, L"�����������׽���", L"Error-shut", MB_OK);
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
			MessageBox(NULL, L"ȡ��һ�������ĵ���", L"Error-shut", MB_OK);
		else 		if (cheak == WSAENOTSOCK)
			MessageBox(NULL, L"�����������׽���", L"Error-shut", MB_OK);
		else		if (cheak == WSAEWOULDBLOCK)
			MessageBox(NULL, L"��������ʽ��SO_LINGER��Ϊ���㳬ʱ���", L"Error-shut", MB_OK);
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
//��Ҫ�Լ���̵ĺ���
//�߳̽��պ���
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
//��Ϣ����
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
	std::cout << "���ڵȴ�����";
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
//�ͻ���



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
			MessageBox(NULL, L"�������������", L"Error-gethostname", MB_OK);
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
			MessageBox(NULL, L"�������������", L"Error-gethostname", MB_OK);
		sever_add.sin_addr.S_un.S_addr = *((u_long*)ent->h_addr_list[0]);*/
	}
}

int SKClient_TCP::Run()
{
	if (Connect(c_sk, (sockaddr*)&sever_add, sizeof(sockaddr_in)) != 0)
	{
		MessageBox(NULL, L"����ʧ��", L"Error", MB_OK);
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

void SKClient_TCP::RecvMsg(char * buf,int len)//lenΪ��������С
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
		printf("����������");
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
/////socket����
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
		MessageBox(NULL, L"SOCKETɾ���±�����",L"Error",MB_OK);
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
//selectģ��

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
		MessageBox(NULL, L"�����׽����쳣", L"Error", MB_OK);
		exit(0);
	}
	if (FD_ISSET(lis_sk, &fdread))
	{
		if (sk_vr.cheaknum() >= FD_SETSIZE - 1)
		{
			MessageBox(NULL, L"�û��Ѵﵽ����", L"Error", MB_OK);
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
			//////������





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
			/////////д����



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

