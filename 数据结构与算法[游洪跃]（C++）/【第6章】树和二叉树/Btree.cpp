#include<iostream>
using namespace std;
// 二叉树结点类
struct BinTreeNode
{
// 数据成员:
 double data;  // 数据域
 BinTreeNode *leftChild; // 左孩子指针域
 BinTreeNode *rightChild; // 右孩子指针域
 BinTreeNode(){ leftChild = rightChild = NULL;};  // 无参数的构造函数 
 BinTreeNode(double &val,BinTreeNode *lChild = NULL, BinTreeNode *rChild = NULL);
};

BinTreeNode::BinTreeNode(double &val, BinTreeNode *lChild,BinTreeNode *rChild)
{ 
 data = val;     // 数据元素值
 leftChild = lChild;   // 左孩子
 rightChild = rChild;  // 右孩子
}
//节点类，其数据成员为二叉节点类型的指针
struct Node 
{
BinTreeNode *data;  // 数据域
Node *next;  // 指针域
Node(){ next = NULL;};   
Node( BinTreeNode *item, Node *link = NULL){  data = item;   next = link;};
};
//队列类，作为层次遍历的辅助数据结构用
class LinkQueue 
{
protected:
 Node *front, *rear;    
public:
 LinkQueue(){rear = front = new Node; };  
 void OutQueue(BinTreeNode * &e);  // 出队操作
    void InQueue(BinTreeNode * &e);   // 入队操作
 bool Empty(){return front==rear;};
};

void LinkQueue::OutQueue(BinTreeNode * &e)
{  Node *tmpPtr = front->next; 
  e = tmpPtr->data;      
  front->next = tmpPtr->next;   
  if (rear == tmpPtr)
  { 
   rear = front;
  }
  delete tmpPtr;      
}

void LinkQueue::InQueue(BinTreeNode * &e)
{
 Node *tmpPtr = new Node(e); 
 rear->next = tmpPtr;       
 rear = tmpPtr;         
}
// 二叉树类
class BinaryTree
{
protected:
 BinTreeNode *root;
// 辅助函数:
 void DestroyHelp(BinTreeNode  * &r);     
 void PreOrderHelp(BinTreeNode  *r) const ; 
 void InOrderHelp(BinTreeNode  *r) const ; 
 void PostOrderHelp(BinTreeNode  *r) const ;
    int HeightHelp(const BinTreeNode  *r) const; 
 int NodeCountHelp(const BinTreeNode  *r) const;
 int leafNodeCountHelp(const BinTreeNode  *r) const;

public:
 BinaryTree();          
 virtual ~BinaryTree();        
 BinTreeNode  *GetRoot() const;     
 void InOrder() const; 
 void PreOrder() const;
 void PostOrder() const; 
 void LevelOrder() const; 
 int NodeCount() const;        
 int leafNodeCount() const;
 void InsertLeftChild(BinTreeNode  *cur,  double &e);
 void InsertRightChild(BinTreeNode  *cur,  double &e);
 int Height() const;          
 BinaryTree( double &e); 
 BinTreeNode *Maketree(double &e,BinTreeNode  *left,BinTreeNode  *right)
 {root=new BinTreeNode(e,left,right);
 return root;
 }
};
 
BinaryTree ::BinaryTree()
{
 root = NULL;
}
 
BinaryTree ::~BinaryTree()
{
 DestroyHelp(root);
}

 
BinTreeNode  *BinaryTree ::GetRoot() const
{
 return root;
}

void BinaryTree ::PreOrderHelp(BinTreeNode  *r) const

{
 if (r != NULL) 
 {
  cout<<(r->data)<<"  ";    
  PreOrderHelp(r->leftChild); 
  PreOrderHelp(r->rightChild); 
 }
}
 
void BinaryTree ::PreOrder() const
{
 PreOrderHelp(root); 
} 

void BinaryTree ::InOrderHelp(BinTreeNode  *r) const
{
 if (r != NULL) 
 {
  InOrderHelp(r->leftChild); 
  cout<<(r->data)<<"  "; 
  InOrderHelp(r->rightChild); 
 }
}
 
void BinaryTree ::InOrder() const
{
 InOrderHelp(root); 
} 
 
void BinaryTree ::PostOrderHelp(BinTreeNode  *r) const
{
 if (r != NULL) 
 {
  PostOrderHelp(r->leftChild); 
  PostOrderHelp(r->rightChild);
  cout<<(r->data)<<"  ";    
 }
}
 
void BinaryTree ::PostOrder() const
{
 PostOrderHelp(root); 
} 

void BinaryTree ::LevelOrder() const
{
 LinkQueue q; // 队列
 BinTreeNode  *t = root;  // 从根结点开始进行层次遍历
 
 if (t != NULL) q.InQueue(t);  
 while (!q.Empty())
 { q.OutQueue(t);     
  cout<<(t->data)<<"  ";
  if (t->leftChild != NULL)  
   q.InQueue(t->leftChild); 
  if (t->rightChild != NULL)   
   q.InQueue(t->rightChild);  
 }
}
 
int BinaryTree ::HeightHelp(const BinTreeNode  *r) const
{
 if(r == NULL)
 { return 0;
 }
 else
 { int lHeight, rHeight;
  lHeight = HeightHelp(r->leftChild);  // 左子树的高
  rHeight = HeightHelp(r->rightChild); // 右子树的高
  return (lHeight > rHeight ? lHeight : rHeight) + 1;
 }
}
 
int BinaryTree ::Height() const
{
 return HeightHelp(root);
}

 
BinaryTree ::BinaryTree( double &e)
{
 root = new BinTreeNode (e);
}
 
int BinaryTree ::NodeCountHelp(const BinTreeNode  *r) const
{
 if (r ==NULL) return 0;  
 else return NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild) + 1;
}
 
int BinaryTree ::NodeCount() const
{
 return NodeCountHelp(root);
}
int BinaryTree ::leafNodeCountHelp(const BinTreeNode  *r) const
{ int lt,rt;
 if (r==NULL) return 0;  
 else if(r->leftChild==NULL &&r->rightChild==NULL)
  return 1;
 else 
 {lt=leafNodeCountHelp(r->leftChild);
 rt=leafNodeCountHelp(r->leftChild);
 return lt+rt;}
}
 
int BinaryTree ::leafNodeCount() const
{
 return leafNodeCountHelp(root);
}

 
void BinaryTree ::InsertLeftChild(BinTreeNode  *cur,  double &e)
{
 if (cur == NULL)
 {
  return;
 }
 else 
 { // 插入左孩子
  BinTreeNode  *child =  new BinTreeNode (e);
  if (cur->leftChild != NULL)
  {child->leftChild = cur->leftChild;
  }
  cur->leftChild = child;    
  return;
 }
}

 
void BinaryTree ::InsertRightChild(BinTreeNode  *cur,  double &e)
{
 if (cur == NULL)
 { return;
 }
 else
 { // 插入右孩子
  BinTreeNode  *child =  new BinTreeNode (e);
  if (cur->rightChild != NULL)
  { child->rightChild = cur->rightChild;
  }
  cur->rightChild = child;     
  return;
 }
}
 
void BinaryTree ::DestroyHelp(BinTreeNode  *&r)
{
 if(r != NULL)
 { DestroyHelp(r->leftChild);  // 销毁左子树
  DestroyHelp(r->rightChild);  // 销毁右子树
  delete r;      // 销毁根结点
  r = NULL;
 }
}

int main(void)
{       double e;
  //BinTreeNode *cur;
  BinTreeNode*a,*b,*c,*d,*f;
  BinaryTree bt;
  cout<<"请输入a结点的数值";
  cin>>e;
  a=bt.Maketree(e,NULL,NULL);
  cout<<"请输入b结点的数值";
  cin>>e;
  b=bt.Maketree(e,NULL,NULL);
  cout<<"请输入b结点的数值";
  cin>>e;
  c=bt.Maketree(e,NULL,NULL);
  cout<<"请输入d结点的数值";
  cin>>e;
  d=bt.Maketree(e,a,b);
  cout<<"请输入f结点的数值";
  cin>>e;
  f=bt.Maketree(e,c,d);
  /*cout<<"请输入根节点的数值:";
  cin>>e;
  cur = new BinTreeNode(e);
  BinaryTree bt(e);  // 建立二叉树
  cur = bt.GetRoot();
  cout<<"请输入根节点左孩子的数值:";
   cin>>e;
  bt.InsertLeftChild(cur, e);
  cout<<"请输入根节点右孩子的数值:";
  cin>>e;
  bt.InsertRightChild(cur, e);
  cout<<"请输入根节点左孩子的左孩子的数值:";
   cin>>e;
  bt.InsertLeftChild(cur->leftChild, e);
  cout<<"请输入根节点右孩子的左孩子的数值:";
  cin>>e;
  bt.InsertLeftChild(cur->rightChild, e);
  cout<<"请输入根节点右孩子的右孩子的数值:"; 
  cin>>e;
  bt.InsertRightChild(cur->rightChild,e);*/
  cout << "先序遍历:" << endl;
  bt.PreOrder();
  cout<<endl;
  system("PAUSE");   

  cout << "中序遍历:" << endl;
  bt.InOrder();
  cout<<endl;
  system("PAUSE");   

  cout << "后序遍历:" << endl;
  bt.PostOrder();
  cout<<endl;
  system("PAUSE");   

  cout << "层次遍历:" << endl;
  bt.LevelOrder();
  cout<<endl;
 /* system("PAUSE");   
  cout<<"树的高度为"<<bt.Height()<<endl;
  cout<<"树中节点数为"<<bt.NodeCount()<<endl;
  cout<<"树中叶子节点数为"<<bt.leafNodeCount()<<endl;
  */
 return 0;      
}

