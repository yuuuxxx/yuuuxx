#include<iostream>
#include<time.h>
using namespace std;

typedef struct LinkList {//�������������
	int key;
	struct LinkList* next;
};

LinkList* Create(int n){//��������
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


typedef struct BSTNode {//����ƽ�������
	LinkList* data;
	int bf;//����ƽ������
	struct BSTNode* lchild;
	struct BSTNode* rchild;//���Һ���ָ��
}BSTNode,*BSTree;


void R_Rotate(BSTree& p) {//����
	BSTree lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
}
void L_Rotate(BSTree& p) {//����
	BSTree rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}

#define LH +1//���
#define EH 0//�ȸ�
#define RH -1//�Ҹ�

void LeftBalance(BSTree& T,int& num) {//��ƽ�⴦��
	BSTree lc = T->lchild;
	switch (lc->bf){
	case LH:
		T->bf = lc->bf = EH;
		R_Rotate(T);
		cout << "��" << num++ << "����ת�ķ���Ϊ��LL" << endl;
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
		cout << "��" << num++ << "����ת�ķ���Ϊ��LR" << endl;
	}
}
void RightBalance(BSTree& T,int& num) {//��ƽ��
	BSTree rc = T->rchild;
	switch (rc->bf) {
	case RH:
		T->bf = rc->bf = EH;
		L_Rotate(T);
		cout << "��" << num ++ << "����ת�ķ���Ϊ��RR" << endl;
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
		cout << "��" << num++ << "����ת�ķ���Ϊ��RL" << endl;
	}
}


bool InsertAVL(BSTree& T, LinkList* e, bool& taller,int& num) {//��ƽ��������в����½��
	if(!T){
		T = (BSTree)malloc(sizeof(BSTNode));
		T->data = e;
		T->lchild = T->rchild = NULL;
		T->bf = EH;
		taller = 1;
	}
	else {
		if (e->key == T->data->key) {//���д��ں�e����ͬ�ؼ��ֵĽ��
			taller = 0;
			return 0;
		}
		//������
		if (e->key < T->data->key) {
			if (!InsertAVL(T->lchild, e, taller,num)) {//����ʧ�ܣ�������ͬ���
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
		//������
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


BSTree Conversion(LinkList* head,int n) {//����ƽ�������
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


void PreOrder(BSTree T) {//�������
	if (T) {
		cout << T->data->key << ' ';
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
	else
		return;
}
void InOrder(BSTree T) {//�������
	if (T) {
		cout << T->data->key << ' ';
		InOrder(T->lchild);
		InOrder(T->rchild);
	}
	else
		return;
}
void PostOrder(BSTree T) {//�������
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
	cout << "��ѡ����Ҫ�ı�����ʽ��" << endl;
	cout << "1���������    2���������    3���������" << endl;
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
	cout << "����������Ҫ��ʲô�أ�  0���˳�   1������һ��" << endl;
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


void FreeLinkList(LinkList* head,int n) {//�ͷſռ�
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
	cout << "������Ԫ�ظ�����";
	int n;
	cin >> n;
	if (n <= 0) {
		cout << "�����������������룡" << endl;
		goto label;
	}
	cout << "���Ԫ�طֱ�Ϊ��";
	LinkList* head = Create(n);
	BSTree T = Conversion(head, n);
	Menu01(T);
	if (Menu02(head))
		goto label;
	return 0;
}