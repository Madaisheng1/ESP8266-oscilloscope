#pragma once
#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib,"Ws2_32.lib")

void Start_Socket();
void Clean_Socket();

class BasicSocket
{
public:
	BasicSocket();//初始化
	void InitAddr(ADDRESS_FAMILY famliy1, u_short TCPnum, const wchar_t ip1[], sockaddr_in * sa);
	void InitAddr(ADDRESS_FAMILY famliy1, u_short TCPnum, ULONG ip1, sockaddr_in * sa);
	SOCKET CreateSocket(SOCKET& sk, int af, int type, int protocol);
	int Bindsk(SOCKET &sk, sockaddr* addr);
	int Listen(SOCKET &sk, int backlog);
	int Connect(SOCKET &sk, sockaddr* name, int namelen);
	int Accept(SOCKET&sk, sockaddr* addr, SOCKET&back_s);
	int Send(SOCKET&s, char*buf, int len, int flags);
	int Recieve(SOCKET&sk, char*buf, int len, int flags);
	int ShutDown(SOCKET&sk, int how);
	int Close(SOCKET&sk);
};


class SKSever_TCP :public BasicSocket
{
	friend void thread_pose_tcp(SKSever_TCP* sever);
protected:
	SOCKET lis_sk;
	sockaddr_in lis_addr;
	std::thread *th;
	sockaddr_in *cl_addr;
	int num_conn;
	int max_conn;
	SOCKET *acc_sk;
	BOOL son_line;
public:
	SKSever_TCP(unsigned short port);
	void SetAddr(unsigned short port);
	void Run(int backlog);
	void Sever_recv(char* buf, int len);
	void shutup();
};


class SKClient_TCP :public BasicSocket
{
protected:
	SOCKET c_sk;
	sockaddr_in sever_add;
public:
	SKClient_TCP(int port, const char severadd[], BOOL name = FALSE);
	SKClient_TCP() {};
	void init(int port, const char severadd[], BOOL name = FALSE);
	int Run();
	void SendMsg(char *buf, int len);
	void shutup();
	void RecvMsg(char * buf,int len);
	int cheakrecvnum();
};

////////////socket容器
struct SK_Line
{
	SOCKET sk;
	SK_Line* next;
};
class SK_vector
{
public:
	SK_vector();
	SOCKET* operator[](int n);
	SOCKET* it(int n);
	void add(SOCKET as);
	void zero();
	void dele(int n);
	int cheaknum() { return num; }
	int cheakend(int n);
protected:
	SK_Line head;
	SK_Line end;
	int num;
};

////////////select模型


class SESever_TCP:public BasicSocket
{
protected:
	SOCKET lis_sk;
	sockaddr_in lis_addr;
	fd_set fdread;
	fd_set fdwrite;
	fd_set fdexcept;
	SK_vector sk_vr;
	SK_vector sk_vw;
public:
	SESever_TCP(unsigned short port);
	void RestFd();
	void CheckAccept();
	void Run();
	void Procssing();
	void shutup();
};