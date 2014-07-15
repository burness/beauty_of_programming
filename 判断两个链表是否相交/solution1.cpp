//判断链表是否相交可以通过判断链表是否有环即可
#include <iostream>
using namespace std;

struct LinkList{
	int value;
	LinkList* next;
};

void InsertList(LinkList *&list){
	LinkList* head;
	LinkList* newNode;
	int data;
	head=list;
	while(head->next)
		head=head->next;

	while(1){
		cin>>data;
		if(data==0)break;
		newNode=new LinkList;
		if(!newNode)
			exit(0);
		newNode->value=data;
		newNode->next=NULL;
		head->next=newNode;
		head=newNode;
		head->next=NULL;
	}
}

void Traverse(LinkList* list){
	LinkList* p;
	p=list->next;
	while(p){
		cout<<" "<<p->value<<" address="<<p<<endl;
		p=p->next;
	}
}

int main(){
	LinkList *first,*second;
	LinkList *fhead,*shead,*h1,*h2,*p,*q;
	int flen=0,slen=0,len;
	first=new LinkList;
	first->next=NULL;
	second=new LinkList;
	second->next=NULL;
	InsertList(first);
	cout<<endl;
	InsertList(second);


	///////////////////////////////////////////////// 
	//将第一个链表中从第四个结点起链接到第二个链表，构造两个相交的链表
	p=second;
	while(p->next)
		p=p->next;//找到第二个链表的尾结点

	q=first;
	for(int i=0;i<4;i++)
		q=q->next;//找到第一个链表的第四个结点
	p->next=q;//插入到第二个链表中
	//////////////////////////////////////////////////
	Traverse(first);
	cout<<endl;
	Traverse(second);
	cout<<endl;

	h1=first->next;
	fhead=first;
	while(fhead->next)//遍历链表到表尾 （执行length1次，记n2次）

	{
		fhead=fhead->next;
		flen++;
	}

	h2=second->next;
	shead=second;
	while(shead->next)//遍历链表到表尾， （执行length2次，记n1次）
	{
		shead=shead->next;
		slen++;
	}
	if(fhead==shead)//最后一个结点的地址相同，则相交
	{ 
		cout<<"两链表相交"<<endl;
		// 计算差值，比较长的先从头遍历差值个长度
		if(flen>=slen)//求两个链表长度的差值
		{
			len=flen-slen;
			while(len--) //遍历差值个步长 （执行abs(length1-length2)次）

				h1=h1->next;  
		}
		else
		{
			len=slen-flen;
			while(len--)
				h2=h2->next; 
		}

		while(1)
		{

			if(h1==h2)//两个链表中地址相同的结点   （最多执行的次数为：min(length1,length2))

			{
				cout<<"第一个相交的结点："<<h1->value;
				break;
			}
			else if(h1->next&&h2->next)
			{
				h1=h1->next;
				h2=h2->next;
			} 
		}
	}
	else 
		cout<<"两链表不相交"<<endl;

} 