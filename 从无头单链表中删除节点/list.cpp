#include <iostream>
#include "list.h"
using namespace std;



//创建头结点
void List::create_List()
{
	head = new Node(0);
}
//从尾部插入一个节点
void List::insert(const int& d)
{
	
	//p->next = head->next;
	//head->next = p;
	Node* p=head;
	while(p->next){
		p=p->next;
	}
	Node *temp = new Node(d);
	p->next=temp;
	temp->next=NULL;
}
//打印函数
void List::print()
{
	for(Node * p = head->next;p;p=p->next){
		cout << p->data << endl;
	}
}
//在d位置之前插入d1
void List::insert_pos(const int& d,const int& d1)
{
	Node * p = find(d);
	Node * q = new Node(d1);
	q->next = p->next;
	p->next = q;
}

//删除
void List::erase(const int& d)
{
	Node * p = find(d);
	//因为p是上一个节点的位置，用q来保存
	//要删除的节点的地址
	Node *q = p->next;
	//通过将上一个节点的next指针指向要删除节点的next指
	//针志向的节点实现断开要删除节点的目的
	p->next = p->next->next;
	//删除要删除的节点q
	delete q;
}

void List::erase_without_head(Node* pCurrent){
	Node* pNext=pCurrent->next;
	pCurrent->next=pNext->next;
	pCurrent->data=pNext->data;
	delete pNext;
}

//修改指定数据
void List::updata(const int& d,const int& d1)
{
	Node * p = find(d);
	p->next->data = d1;
}

////反转链表
//void List::reverse()
//{
//	Node * p = head->next;//头结点之后的第1个节点
//	Node * q = head->next->next;//头结点之后的第2节点
//	Node * m = head->next->next->next;//头结点之后的第3个节点
//	p->next = NULL;//将头接点之后的第1个节点的next指针置为空
//	//根据m是否为空来判断 以此逆序每一个节点
//	while(m){
//		q->next = p;
//		p = q;
//		q = m;
//		m = m->next;
//	}
//	//将最后一个节点逆序
//	q->next = p;
//	//将头从新指向新的的第1个节点(之前的最后一个节点)
//	head ->next = q;
//}