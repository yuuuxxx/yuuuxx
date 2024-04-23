#include<iostream>
#include<time.h>
using namespace std;

typedef struct LinkList {//定义随机数链表
	int key;
	struct LinkList* next;
};

LinkList* Create(int n){//创建链表
	LinkList* head = (LinkList*)malloc(sizeof(LinkList));
	if (head) {
		LinkList* p = head;
		srand(time(0));
		for (int i = 0; i < n; i++) {
			p->key = rand();
			cout << p->key << ' ';
			LinkList* q = (LinkList*)malloc(sizeof(LinkList));
			p->next = q;
			p = q;
		}
		p->next = NULL;
		cout << endl;
	}
	return head;
}


typedef struct BSTNode {//定义平衡二叉树
	LinkList* data;
	int bf;//结点的平衡因子
	struct BSTNode* lchild;
	struct BSTNode* rchild;//左右孩子指针
}BSTNode,*BSTree;


void R_Rotate(BSTree& p) {//右旋
	BSTree lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
}
void L_Rotate(BSTree& p) {//左旋
	BSTree rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}

#define LH +1//左高
#define EH 0//等高
#define RH -1//右高

void LeftBalance(BSTree& T,int& num) {//左平衡处理
	BSTree lc = T->lchild;
	switch (lc->bf){
	case LH:
		T->bf = lc->bf = EH;
		R_Rotate(T);
		cout << "第" << num++ << "次旋转的方法为：LL" << endl;
		break;
	case RH:
		BSTree rd = lc->rchild;
		switch (rd->bf){
		case LH:T->bf = RH; lc->bf = EH; break;
		case EH:T->bf = lc->bf = EH; break;
		case RH:T->bf = EH; lc->bf = LH; break;
		}
		rd->bf = EH;
		L_Rotate(T->lchild);
		R_Rotate(T);
		cout << "第" << num++ << "次旋转的方法为：LR" << endl;
	}
}
void RightBalance(BSTree& T,int& num) {//右平衡
	BSTree rc = T->rchild;
	switch (rc->bf) {
	case RH:
		T->bf = rc->bf = EH;
		L_Rotate(T);
		cout << "第" << num ++ << "次旋转的方法为：RR" << endl;
		break;
	case LH:
		BSTree ld = rc->lchild;
		switch (ld->bf) {
		case LH:T->bf = EH; rc->bf = RH; break;
		case EH:T->bf = rc->bf = EH; break;
		case RH:T->bf = LH; rc->bf = EH; break;
		}
		ld->bf = EH;
		R_Rotate(T->rchild);
		L_Rotate(T);
		cout << "第" << num++ << "次旋转的方法为：RL" << endl;
	}
}


bool InsertAVL(BSTree& T, LinkList* e, bool& taller,int& num) {//在平衡二叉树中插入新结点
	if(!T){
		T = (BSTree)malloc(sizeof(BSTNode));
		T->data = e;
		T->lchild = T->rchild = NULL;
		T->bf = EH;
		taller = 1;
	}
	else {
		if (e->key == T->data->key) {//树中存在和e有相同关键字的结点
			taller = 0;
			return 0;
		}
		//左子树
		if (e->key < T->data->key) {
			if (!InsertAVL(T->lchild, e, taller,num)) {//插入失败，遇到相同结点
				taller = 0;
				return 0;
			}
			if (taller) {
				switch (T->bf) {
				case LH:
					LeftBalance(T,num);
					taller = 0;
					break;
				case EH:
					T->bf = LH;
					taller = 1;
					break;
				case RH:
					T->bf = EH;
					taller = 0;
					break;
				}
			}
		}//if (e->key != T->data->key)
		//右子树
		else {
			if (!(InsertAVL(T->rchild, e, taller,num))) 	return 0;
			if (taller) {
				switch (T->bf){
				case LH:
					T->bf = EH;
					taller = 0;
					break;
				case EH:
					T->bf = RH;
					taller = 1;
					break;
				case RH:
					RightBalance(T,num);
					taller = 0;
					break;
				}
			}
		}//else
	}//else
	return 1;
}


BSTree Conversion(LinkList* head,int n) {//建立平衡二叉树
	LinkList* e = head;
	BSTree T = (BSTree)malloc(sizeof(BSTNode));
	if (T) {
		T->lchild = T->rchild = NULL;
		T->data = e; 
		T->bf = EH;
		bool taller;
		int num = 1;
		for (int i = 1; i < n; i++) {
			e = e->next;
			InsertAVL(T, e, taller,num);
		}
		return T;
	}
}


void PreOrder(BSTree T) {//先序遍历
	if (T) {
		cout << T->data->key << ' ';
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
	else
		return;
}
void InOrder(BSTree T) {//中序遍历
	if (T) {
		cout << T->data->key << ' ';
		InOrder(T->lchild);
		InOrder(T->rchild);
	}
	else
		return;
}
void PostOrder(BSTree T) {//后序遍历
	if (T) {	
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		cout << T->data->key << ' ';
	}
	else
		return;
}


void Menu01(BSTree T) {
	int n;
	cout << "请选择想要的遍历方式：" << endl;
	cout << "1：先序遍历    2：中序遍历    3：后序遍历" << endl;
	cin >> n;
	switch (n) {
	case 1:
		PreOrder(T);
		break;
	case 2:
		InOrder(T);
		break;
	case 3:
		PostOrder(T);
		break;
	}
	cout << endl;
 }

void FreeLinkList(LinkList* head, int n);

bool Menu02(LinkList* head) {
	cout << "您接下来想要干什么呢？  0：退出   1：再来一次" << endl;
	int n;
	cin >> n;
	if (!n) {
		FreeLinkList(head, n);
		return 0;
	}
	else{
		FreeLinkList(head, n);
		system("cls");
		return 1;
	}	
}


void FreeLinkList(LinkList* head,int n) {//释放空间
	LinkList* p = head;
	LinkList* q = p;
	for (int i = 0; i < n; i++) {
		q = p->next;
		free(p);
		p = q;
	}
}


int main() {
	label:
	cout << "请输入元素个数：";
	int n;
	cin >> n;
	if (n <= 0) {
		cout << "输入有误，请重新输入！" << endl;
		goto label;
	}
	cout << "随机元素分别为：";
	LinkList* head = Create(n);
	BSTree T = Conversion(head, n);
	Menu01(T);
	if (Menu02(head))
		goto label;
	return 0;
}