#pragma once
#include <iostream>
using namespace std;
//////////////////////////////
//#########################///
/*###########链表###########*/
//#########################//
/////////////////////////////
class Clist;

typedef struct HWND_list
{
	int hid;        //代号(id不允许使用0)
	void *win;      //窗口框架类或控件类指针
	HWND_list* next;    //下一个
}Hlist;



class Clist
{
public:
	Clist();
	void  Addlist(int id, void *member);  //增加成员
	int  Dellist(int id);                //删除成员(1:成功,0:没有此id,-1:链表没有元素)
	void* Findlist(int id);               //找到成员
	void  Zerolist();                     //清空链表
	int   Getnum() { return num; }        //获取成员总数
	Hlist* Gethead() { return &head; }    //获取链表头地址
	Hlist* Getend() { return &end; }      //获取链表尾地址
protected:
	Hlist head;
	Hlist end;
	int num;

protected:  //实现遍历函数
	Hlist* current;//遍历指针
public:     //遍历函数
	void Next();
	void Reset();
	int Getcurid() { return current->hid; }
	void* Getcurwin() { return current->win; }
	bool iscurnull();

};
//////////////////////////
//////////////////////////
////////其他函数
void chartoint(char s[], const int a);
void wchartoint(wchar_t s[], const int a);
int comparestr(const char *a,const char *b, int lenth);
int comparestrW(const wchar_t *a, const wchar_t *b, int lenth);
int strnum(const char*str);
int strnumW(const wchar_t*str);
void copystrW(wchar_t* buff, const wchar_t* stample, int bufflenth);
int strtointW(wchar_t s[]);
////////////////////////计时器
