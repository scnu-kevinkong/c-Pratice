#pragma once
#include <string>
#include <iostream>
// ����Ϊģ������
typedef int ElementType;
struct Node {
	ElementType data;
	Node *next;
};
// ��ͷ�������
class Link {
public:
	Link();
	~Link();
	//ѡ������ 
	void select_sort();
	//ð������ 
	void bubble_sort();
	//ͷ������ 
	void insert_head(ElementType data);
	//β������ 
	void insert_tail(ElementType data);
	//���ҽ��,������ţ���������ڷ���-1 
	int find(ElementType data);
	//ɾ����� 
	bool delete_node(int pos);
	//���� 
	void reverse();
	//��ӡ���� 
	void display();
	//��ӡ��ʾ��Ϣ 
	void printhelp();
	//���س���
	int size();
private:
	//ͷ���ָ�� 
	Node * pHead;
	//������ 
	size_t iSize;
};
Link::Link(){
    pHead = new Node;
    pHead->next = NULL;
	iSize = 0;
}

Link::~Link() {
    Node * tmpNode = NULL;
    Node * p = pHead->next;
    while (p != NULL)
    {
        tmpNode = p->next;
        delete p;
        p = tmpNode;
    }
    delete tmpNode;
    tmpNode = NULL;

    delete pHead;
    p = NULL;

    iSize = 0;
}

/**********************************
   ����ѡ������(����)
***********************************/
void Link::select_sort()
{
    Node * p , *q;
    int temp;

    for (p = pHead; p != NULL; p = p->next)
        for (q = p->next; q != NULL; q = q->next)
        {
            if (p->data > q->data)
            {
                temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
}

/**********************************
   ����ð������(����)
***********************************/
void Link::bubble_sort()
{
    Node *p;
    int temp;
	int len = iSize;

    /************************************************************************/
    /*       ð��������ÿ�δ�ͷ��ʼ�Ƚ����ڵ�����������С�෴�򽻻��������� */
    /*        ��������һ����û�з���������flag������¼�Ƿ����˽���          */
    /************************************************************************/
    int flag;
	int times;
    while (len > 0)
    {
        flag = 0;
		times = 0;
        for (p = pHead; p->next != NULL; p = p->next)
        {
			times++;
            if (p->data > p->next->data)
            {
                temp = p->data;
                p->data = p->next->data;
                p->next->data = temp;
                flag = 1;
            }
			if (times == len)
				break;
        }
        if (flag == 0)
            break;
		len--;
    }
}

/********************************
   ����ͷ������
*****************************/
void Link::insert_head(ElementType data)
{
    Node * tmpNode = new Node;
    tmpNode->data = data;
    
    tmpNode->next = pHead->next;
    pHead->next = tmpNode;
    
    iSize++;

    tmpNode = NULL;
}

/********************************
   ����β������
*****************************/
void Link::insert_tail(ElementType data)
{
    Node * tmpNode = new Node;
    tmpNode->data = data;
    tmpNode->next = NULL;

    Node * p = NULL;
    p = pHead;
    while (p->next != NULL)
    {
        p = p->next;
    }

    p->next = tmpNode;
    iSize++;

    //delete tmpNode;
    tmpNode = NULL;
    //delete p;
    p = NULL;
}

/********************************
   ��ӡ����
*****************************/
void Link::display()
{
    int count = 1;
    Node * tmpNode = NULL;

    tmpNode = pHead->next;
    while (tmpNode != NULL)
    {
        std::cout<<tmpNode->data<<" ";
        tmpNode = tmpNode->next;

        /********************************
        *  �����ʽ���ƣ�ÿ��10��
        **********************************/
        if (count % 10 == 0)
        {
            std::cout<<std::endl;
        }
        count++;
    }
    std::cout<<std::endl;
    tmpNode = NULL;
}

/********************************
   ���ҽ��
*****************************/
int Link::find(ElementType data)
{
    int pos = 0;
    Node * tmpNode = NULL;

    tmpNode = pHead->next;
    while (tmpNode != NULL)
    {
        if ( tmpNode->data == data)
        {
            return pos;
        }
        tmpNode = tmpNode->next;
        pos++;
    }

    tmpNode = NULL;
    return -1;
}

/********************************
   ɾ�����
*****************************/
bool Link::delete_node(int pos)
{
    //��ų�������Χ�򱨴��˳�
    if (pos > iSize -1)
    {
        return false;
    }
    else
    {
        int k = 0;
        Node * tmpNode = NULL;
        tmpNode = pHead;
        while ( k < pos)
        {
            tmpNode = tmpNode->next;
            k++;
        }
        Node * p = NULL;
        p = tmpNode->next;

        tmpNode->next = tmpNode->next->next;
        delete p;
        p = NULL;
        iSize--;
        return true;
    }
}

/********************************
   ��������ĳ���
*****************************/
int Link::size()
{
    return iSize;
}

/********************************
   ���������
*****************************/
void Link::reverse()
{
    Node * preNode = NULL;
    Node * curNode = NULL;
    Node * afterNode = NULL;

    if ( iSize == 1 || iSize == 0)
    {
        return;
    }
    else if ( iSize >= 2)
    {
        preNode = pHead->next;
        curNode = preNode->next;
        afterNode = curNode->next;

        preNode->next = NULL;
        
        while (afterNode != NULL)
        {
            curNode->next = preNode;

            preNode = curNode;
            curNode = afterNode;

            afterNode = afterNode->next;
        }

        /********************************************************************
        * ����ǰ����next��Ϊǰһ�����Ĺ�������ÿһ��ѭ���Ŀ�ʼ�������һ��
        * ѭ�����޷�������һ��ѭ������Ҫ��һ������curNode��next�Ĺ���
        *********************************************************************/
        curNode->next = preNode;

        pHead->next = curNode;
    }
    preNode = NULL;
    curNode = NULL;
    afterNode = NULL;
}

void Link::printhelp()
{
    std::cout<<"*****************************************\n";
    std::cout<<"��ǰ����Ϊ:"<<std::endl;
    if (iSize == 0)
        std::cout<<"NULL"<<std::endl;
    else
        display();
    std::cout<<"�������ѡ��:\n"
        "0.��ͷ��������\n"
        "1.��β��������\n"
        "2.��������\n"
        "3.��ӡ����\n"
        "4.ɾ�����\n"
        "5.���������\n"
        "6.���ҽ��\n"
        "7.ѡ������\n"
        "8.ð������\n"
        "9.�˳�"<<std::endl;
    std::cout<<"*****************************************\n";
}