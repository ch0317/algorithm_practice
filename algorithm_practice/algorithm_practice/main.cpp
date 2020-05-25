
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
    if(pNode == NULL)
        return NULL;
    if (pNode == pList->prear)
        pList->prear = pList->pHead;
    pList->pHead->next = pNode->next;
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
        if(p->data)
            printf("%d",p->data->data);
        p = p->next;
    }
    printf("\n");
}

void TreePrint(BiTree T)
{
    if(T == NULL){
        return;
    }

    TreePrint(T->plchild);
    TreePrint(T->prchild);
    printf("%d",T->data);
}

//6.设一颗二叉树中各节点的值互不相同，其先序遍历序列和中序遍历序列分别存于两个一维数组A[1...n]和B[1...n]中，
//实现建立该二叉树的二叉链表
int A[] = {1,2,3,4,5,6};
int B[] = {3,2,1,5,4,6};

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
    while(!IsQueueEmpty(pListQueue)){
        PrintQueue(pListQueue);
        p = DelQueue(pListQueue);
        if(p){
            EnQueue(pListQueue, p->plchild);
            EnQueue(pListQueue, p->prchild);
        }
        else{
            while(!IsQueueEmpty(pListQueue)){
                if(DelQueue(pListQueue))
                    return 0;
            }
        }

    }
    return 1;
}

//8. 计算一棵给定二叉树的所有双分支节点数
int CountDoubleBranchNode(BiTree T)
{
    if(T == NULL)
        return 0;

    QueueList *pListQueue = InitQueue();
    BiTree p = T;
    EnQueue(pListQueue, p);
    int count = 0;
    
    while(!IsQueueEmpty(pListQueue)){
        p = DelQueue(pListQueue);
        if(p->plchild)
            EnQueue(pListQueue, p->plchild);
        if(p->prchild)
            EnQueue(pListQueue, p->prchild);
        if(p->plchild && p->prchild)
            count++;
    }
    
    return count;
}

//9. 编写一个把树B所有结点的左右子树进行交换的函数
void SwitchTreeNode(BiTree T)
{
    if(T == NULL)
        return;
    
    SwitchTreeNode(T->plchild);
    SwitchTreeNode(T->prchild);
    BiTree p = T->plchild;
    T->plchild = T->prchild;
    T->prchild = p;
}

//10.求先序遍历序列中第k（1<=k<=二叉树结点个数）个结点的值
int count = 0;
int value = 0;
void GetPreOrderValue(BiTree T, int num)
{
    if(T == NULL)
        return;
    count++;
    if(count == num)
        value = T->data;
    GetPreOrderValue(T->plchild,num);
    GetPreOrderValue(T->prchild,num);
    printf("value:%d\n", value);
}

//11.对于树中每个元素值为x的结点，删去以它为根的子树，并释放相应的空间
void FreeTree(BiTree T)
{
    if(T == NULL)
        return;
    FreeTree(T->plchild);
    FreeTree(T->prchild);
    free(T);
}
void FreeValueX(BiTree T, int x)
{
    if(T == NULL)
        return;

    QueueList *pListQueue = InitQueue();
    BiTree p = T;
    EnQueue(pListQueue, p);
    
    while(!IsQueueEmpty(pListQueue)){
        p = DelQueue(pListQueue);
        if(p->plchild){
            if(p->plchild->data == x){
                printf("free:");
                TreePrint(p);
                printf("\n");
                FreeTree(p->plchild);
                p->plchild = NULL;
            }
            else
                EnQueue(pListQueue, p->plchild);
        }
        if(p->prchild){
            if(p->prchild->data == x){
                printf("free:");
                TreePrint(p);
                printf("\n");
                FreeTree(p->prchild);
                p->prchild = NULL;
            }
            else
                EnQueue(pListQueue, p->prchild);
        }
    }
    
}

//12.打印二叉树中值为x的结点的所有祖先，假设值为x的结点不止一个



int main()
{
    //6
    BiTree p = CreateTree(A, B, 0, 5, 0, 5);
    //TreePrint(p);

    //7
    int ret = IsTreeComplete(p);
    printf("ret:%d\n",ret);
    
    //8
    ret = CountDoubleBranchNode(p);
    printf("double branch nodes num:%d\n",ret);
    
    //9
    //TreePrint(p);
    //SwitchTreeNode(p);
    //TreePrint(p);

    //10
    GetPreOrderValue(p,6);
    
    //11
    TreePrint(p);
    printf("\n");
    FreeValueX(p, 4);
    TreePrint(p);
    
    return 0;
}
