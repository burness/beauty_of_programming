struct Node{
	int data;
	Node * next;
	Node(const int& d):data(d),next(NULL){}
};

class List {
public:
	List(){create_List();}
	~List(){clear();}
	//创建头结点
	void create_List();
	//插入函数
	void insert(const int& d);
	//在指定位置插入
	void insert_pos(const int& d,const int& d1);
	//删除指定数据的节点
	void erase(const int& d);
	void erase_without_head(Node* pCurrent);
	//修改指定数据
	void updata(const int& d,const int& d1);
	////反转链表函数
	//void reverse();
	Node * head;
	//打印
	void print();
private:
	//节点结构
	
	//头节点
	//清理链表函数
	void clear(){
		Node * p = head;
		//从头节点开始循环删除
		while(p){
			Node * q = p->next;
			delete p;
			p = q;
		}
	}
	//查找数据d的上一个节点位置的函数
	//为了方便后面删除操作
	Node* find(const int& d){
		Node * p = head;
		for(;p;p=p->next){
			if(p->next->data==d)
				break;
		}
		return p;
	}
};