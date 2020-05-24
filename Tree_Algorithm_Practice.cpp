
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct BiTreeNODE{
	ElemType data;
	struct BiTreeNODE *plchild, *prchild;
}BiTreeNode, *BiTree;

typedef struct QUEUE_NODE{
	BiTree data;
	struct QUEUE_NODE *next;
}QueueNode;

typedef struct QUEUE_LIST{
	QueueNode *pHead;
	QueueNode *prear;
}QueueList;

QueueList *InitQueue()
{
	//创建链表头
	QueueNode *pListHead = (QueueNode *)malloc(sizeof(QueueNode));
	pListHead->data = NULL;
	pListHead->next = NULL;
	QueueList *pList = (QueueList *)malloc(sizeof(QueueList));
	pList->pHead = pListHead;
	pList->prear = pListHead;
	return pList;
}

void EnQueue(QueueList *pList, BiTree T)
{
	QueueNode *pNode = (QueueNode *)malloc(sizeof(QueueNode));
	pNode->data = T;
	pNode->next = NULL;
	pList->prear->next = pNode;
	pList->prear = pNode;
}

BiTree DelQueue(QueueList *pList)
{
	QueueNode *pNode = pList->pHead->next;
	pList->pHead = pNode->next;
	BiTree p = pNode->data;
	free(pNode);
	return p;
}

bool IsQueueEmpty(QueueList *pList)
{
	if(pList->pHead == pList->prear)
		return true;
	else
		return false;
}

void PrintQueue(QueueList *pList)
{
	QueueNode *p = pList->pHead->next;
	printf("queue:");
	while(p != NULL){
		printf("%d",p->data->data);
		p = p->next;
	}
	printf("\n");
}

//6.设一颗二叉树中各节点的值互不相同，其先序遍历序列和中序遍历序列分别存于两个一维数组A[1...n]和B[1...n]中，
//实现建立该二叉树的二叉链表
int A[] = {1,2,3,4,5};
int B[] = {3,2,1,5,4};

BiTree CreateTree(int A[], int B[], int f1, int r1, int f2, int r2)
{
	//printf("f1=%d,r1=%d,f2=%d,r2=%d",f1,r1,f2,r2);
	BiTree root = (BiTree)malloc(sizeof(BiTreeNode));
	root->data = A[f1];
	//printf("root:%d\n",root->data);
	int i = 0;
	for(i = f2; B[i] != root->data; i++);
	//printf("i:%d",i);

	int llen = i - f2;
	int rlen = r2 - i;

	//递归构造二叉树
	if(llen)
		root->plchild = CreateTree(A, B, f1 + 1, f1 + llen, f2, f2 + llen - 1);
	else
		root->plchild = NULL;

	if(rlen)
		root->prchild = CreateTree(A, B, r1 - rlen + 1, r1, r2 - rlen + 1, r2);
	else
		root->prchild = NULL;

	return root;
}

//7.判断二叉树是否是完全二叉树
bool IsTreeComplete(BiTree T)
{
	if(T == NULL)
		return 1;

	QueueList *pListQueue = InitQueue();
	BiTree p = T;
	EnQueue(pListQueue, p);
	int count = 0;
	while(!IsQueueEmpty(pListQueue)){
		PrintQueue(pListQueue);
		p = DelQueue(pListQueue);
		printf("count:%d\n",count);
		if(p){
			printf("data:%d\n",p->data);
			EnQueue(pListQueue, p->plchild);
			printf("plchild:%d\n",p->plchild->data);
			EnQueue(pListQueue, p->prchild);
			printf("prchild:%d\n",p->prchild->data);
		}
		else{
			printf("data:null");
			while(!IsQueueEmpty(pListQueue)){
				if(DelQueue(pListQueue))
					return 0;
			}
		}

	}
	return 1;
}

void TreePrint(BiTree T)
{
	if(T == NULL)
		return;

	TreePrint(T->plchild);
	TreePrint(T->prchild);
	printf("node%d\n",T->data);
}

int main()
{
	//6
	BiTree p = CreateTree(A, B, 0, 4, 0, 4);
	//TreePrint(p);

	//7
	int ret = IsTreeComplete(p);
	printf("ret:%d\n",ret);

	return 0;
}