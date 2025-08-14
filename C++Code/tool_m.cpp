#include "tool_m.h"

/////////////////////////////
//#########################//
/*###########链表##########*/
//#########################//
////////////////////////////
Clist::Clist()
{
	head.hid = 0;
	head.next = &end;
	head.win = NULL;
	end.hid = 0;
	end.next = NULL;
	end.win = NULL;
	current = NULL;
	num = 0;
}

void Clist::Addlist(int id, void * member)
{
	//创建中间变量
	Hlist *add;
	add = (Hlist*)malloc(sizeof(Hlist));
	add->hid = id;
	add->win = member;
	add->next = NULL;

	//将新成员加入链表
	Hlist *f;
	Hlist *n;
	f = &head;
	n = head.next;
	while (n->next != NULL)
	{
		f = f->next;
		n = n->next;
	}
	f->next = add;
	add->next = n;
	num++;
}

int Clist::Dellist(int id)
{
	if (id != 0)
	{
		Hlist *f, *n, *now;
		f = &head;
		now = f->next;
		n = now->next;
		if (n == NULL)
		{
			return -1;//链表没有元素
		}
		if (now->hid == id)
		{
			f->next = n;
			free(now);
			num--;
			return 1;
		}
		while (n != NULL)
		{
			f = f->next;
			now = now->next;
			n = n->next;
			if (now->hid == id)
			{
				f->next = n;
				free(now);
				num--;
				return 1;
			}
		}
	}
	return 0;
}

void * Clist::Findlist(int id)
{
	Hlist *now;
	now = head.next;
	while (now->next != NULL)
	{
		if (now->hid == id)
		{
			return now->win;
		}
		now = now->next;
	}
	return NULL;
}

void Clist::Zerolist()
{
	Hlist *f;
	f = head.next;
	while (head.next != &end)
	{
		head.next = f->next;
		free(f);
		f = head.next;
	}
	num = 0;
}

void Clist::Next()
{
	if (num == 0)
	{
		current = NULL;
	}
	else if (current == NULL)
	{
		current = head.next;
	}
	else if (current->next == &end)
	{
		current = NULL;
	}
	else
	{
		current = current->next;
	}
}

void Clist::Reset()
{
	current = NULL;
}

bool Clist::iscurnull()
{
	if (current == NULL)
		return 0;
	else return 1;
}
/////////


void chartoint(char s[], const int a)
{
	int n = a, i = 0;
	memset(s, '\0', sizeof(s));
	s[0] = '0';
	int b[1000] = { 0 }, c[1000] = { 0 };
	while (n != 0)
	{
		b[i] = n % 10;
		n = n / 10;
		i++;
	}
	register int x = i;
	for (i = 0; i < x; i++)
	{
		c[x - 1 - i] = b[i];
	}
	for (i = 0; i < x; i++)
	{
		if (c[i] == 0) s[i] = '0';
		else if (c[i] == 1) s[i] = '1';
		else if (c[i] == 2) s[i] = '2';
		else if (c[i] == 3) s[i] = '3';
		else if (c[i] == 4) s[i] = '4';
		else if (c[i] == 5) s[i] = '5';
		else if (c[i] == 6) s[i] = '6';
		else if (c[i] == 7) s[i] = '7';
		else if (c[i] == 8) s[i] = '8';
		else if (c[i] == 9) s[i] = '9';
	}
}

void wchartoint(wchar_t s[], const int a)
{
	int n = a, i = 0;
	memset(s, '\0', sizeof(s));
	s[0] = '0';
	int b[1000] = { 0 }, c[1000] = { 0 };
	while (n != 0)
	{
		b[i] = n % 10;
		n = n / 10;
		i++;
	}
	register int x = i;
	for (i = 0; i < x; i++)
	{
		c[x - 1 - i] = b[i];
	}
	for (i = 0; i < x; i++)
	{
		if (c[i] == 0) s[i] = '0';
		else if (c[i] == 1) s[i] = '1';
		else if (c[i] == 2) s[i] = '2';
		else if (c[i] == 3) s[i] = '3';
		else if (c[i] == 4) s[i] = '4';
		else if (c[i] == 5) s[i] = '5';
		else if (c[i] == 6) s[i] = '6';
		else if (c[i] == 7) s[i] = '7';
		else if (c[i] == 8) s[i] = '8';
		else if (c[i] == 9) s[i] = '9';
	}
}

int comparestr(const char *a,const char *b,int lenth)
{
	for (int i = 0; i < lenth; i++)
	{
		if (a[i] == '\0'&&b[i] == '\0')
			return 1;
		if (a[i] != b[i])
			return 0;
	}
	return 1;
}

int comparestrW(const wchar_t * a, const wchar_t * b, int lenth)
{
	for (int i = 0; i < lenth; i++)
	{
		if (a[i] == '\0'&&b[i] == '\0')
			return 1;
		if (a[i] != b[i])
			return 0;
	}
	return 1;
}

int strnum(const char * str)
{
	int num=0;
	while (str[num] != '\0')
	{
		num++;
	}
	return num;
}

int strnumW(const wchar_t * str)
{
	int num = 0;
	while (str[num] != '\0')
	{
		num++;
	}
	return num;
}

void copystrW(wchar_t * buff, const wchar_t * stample,int bufflenth)
{
	for (int i = 0; i < bufflenth &&i<strnumW(stample); i++)
	{
		buff[i] = stample[i];
	}
	buff[bufflenth-1] = '\0';
}

int strtointW(wchar_t s[])
{
	int a=0;
	int j=0;
	int e=1;
	for (int i = 0; s[i] <= 57 && s[i] >= 48; i++)
	{
		j++;
	}
	if (j == 0)
		return 0;
	for (int i = 0; i < j; i++)
	{
		a = a + e * (s[j-1-i] - 48);
		e = e * 10;
	}
	return a;
}

