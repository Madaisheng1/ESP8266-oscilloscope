#pragma once
#include <iostream>
using namespace std;
//////////////////////////////
//#########################///
/*###########����###########*/
//#########################//
/////////////////////////////
class Clist;

typedef struct HWND_list
{
	int hid;        //����(id������ʹ��0)
	void *win;      //���ڿ�����ؼ���ָ��
	HWND_list* next;    //��һ��
}Hlist;



class Clist
{
public:
	Clist();
	void  Addlist(int id, void *member);  //���ӳ�Ա
	int  Dellist(int id);                //ɾ����Ա(1:�ɹ�,0:û�д�id,-1:����û��Ԫ��)
	void* Findlist(int id);               //�ҵ���Ա
	void  Zerolist();                     //�������
	int   Getnum() { return num; }        //��ȡ��Ա����
	Hlist* Gethead() { return &head; }    //��ȡ����ͷ��ַ
	Hlist* Getend() { return &end; }      //��ȡ����β��ַ
protected:
	Hlist head;
	Hlist end;
	int num;

protected:  //ʵ�ֱ�������
	Hlist* current;//����ָ��
public:     //��������
	void Next();
	void Reset();
	int Getcurid() { return current->hid; }
	void* Getcurwin() { return current->win; }
	bool iscurnull();

};
//////////////////////////
//////////////////////////
////////��������
void chartoint(char s[], const int a);
void wchartoint(wchar_t s[], const int a);
int comparestr(const char *a,const char *b, int lenth);
int comparestrW(const wchar_t *a, const wchar_t *b, int lenth);
int strnum(const char*str);
int strnumW(const wchar_t*str);
void copystrW(wchar_t* buff, const wchar_t* stample, int bufflenth);
int strtointW(wchar_t s[]);
////////////////////////��ʱ��
