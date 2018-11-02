#include <iostream>
#include <sstream>
#include <utility>
#include <string.h>
#include <string>
#include <new>
#include <cstdlib>
#include <exception>
using namespace std;
int Min(int a, int b)
{
	return a > b ? b : a;
}
int Max(int a, int b)
{
	return a > b ? a : b;
}
template <class T>
 class TVector
 {
	 	int Size;
	 	int Capacity;
	 	T* Data;
	 public:
		 	typedef T* Iterator;
		 	TVector() : Size(0), Capacity(0), Data(0) {}
		 	TVector(int size) : Size(size), Capacity(size * 2), Data(new T[Capacity]) {}
		 	TVector(int size, T e) : Size(size), Capacity(Size * 2), Data(new T[Capacity])
			 	{
			 		for (int i = 0; i < Size; i++)
				 			Data[i] = e;
			 	}

			int SizeofSize() const { return Size; }
		 	int isEmpty() const { return Size == 0; }
		 	int SizeofCapacity() const { return Capacity; }
		 	void SizeofResize(int newSize)
			 	{
			 		Capacity = newSize * 2;
					T* newData = new T[Capacity];
			 		int len = Min(Size, newSize);
			 		for (int i = 0; i < len; i++)
				 			newData[i] = Data[i];
			 		delete[] Data;
			 		Size = newSize;
			 		Data = newData;
			 	}
		 	void PushBack(const T& e)
			 	{
			 		if (Size == Capacity)
				 		{
				 			SizeofResize(Size + 1);
				 			Size--;
						}
			 		Data[Size++] = e;
				}
		 	void PopBack()
			 	{
			 		if (Size)
				 			Size--;
			 	}
		 	Iterator Begin() const { return Data; }
		 	Iterator End() const { return Data + Size; }
			const T& Front() const { return Data[0]; }
		 	const T& back() const { return Data[Size - 1]; }
		 	T& operator [] (int idx) { return Data[idx]; }
		 	TVector<T>& operator = (TVector<T>& other)
	 	{
			 		if (Data != other.Data)
				 		{
				 			Size = other.Size;
				 			Capacity = other.Capacity;
				 			delete Data;
				 			Data = new T[Capacity];
							for (int i = 0; i < Size; i++)
									Data[i] = other.Data[i];
				 		}
			 	}
		 	void append(TVector<T>& other)
			 	{
			 		for (int i = 0; i < other.Size; i++)
							PushBack(other[i]);
			 	}

			 };
 template<class K, class V>
 class TAVLTree
 {
	 	struct TNode;
	 	struct TNode
		 	{
				K Key;
		 		V Value;
				TNode* Left;
		 		TNode* Right;
		 		int Height;
		 		TNode(K key, V val) : Key(key),Value(val), Left(0), Right(0),Height(1) {};
		 	};
        TNode* Root;
	 	int SizeofHeight(const TNode* node) {
			return node ? node->Height : 0;
		}
	 	int SizeofBalance(const TNode* node) {
			return SizeofHeight(node->Right) - SizeofHeight(node->Left);
		}
	 	void CorrectSize(TNode* node) {
			node->Height = Max(SizeofHeight(node->Left), SizeofHeight(node->Right)) + 1;
		}
	 	TNode* RotateLeft(TNode* node){
		 		TNode* newRoot = node->Right;
		 		node->Right = newRoot->Left;
				newRoot->Left = node;
		 		CorrectSize(node);
		 		CorrectSize(newRoot);
		 		return newRoot;
		 	}
	 	TNode* RotateRight(TNode* node)
			{
		 		TNode* newRoot = node->Left;
				node->Left = newRoot->Right;
		 		newRoot->Right = node;
		 		CorrectSize(node);
		 		CorrectSize(newRoot);
		 		return newRoot;
		 	}
	 	TNode* ReBalance(TNode* node)
		 	{
				if (!node)
				{
					return 0;
				}
		 		CorrectSize(node);
		 		if (SizeofBalance(node) == 2)
			 		{
			 			if (SizeofBalance(node->Right) < 0)
				 				node->Right = RotateRight(node->Right);
			 			return RotateLeft(node);
			 		}
		 		if (SizeofBalance(node) == -2)
			 		{
			 			if (SizeofBalance(node->Left) > 0)
				 				node->Left = RotateLeft(node->Left);
			 			return RotateRight(node);
			 		}
		 		return node;
		 	}
	 	TNode* Insert(TNode* node, K key, V value)
		 	{
		 		if (!node)
			 		{
			 			try {
							node = new TNode(key, value);
						}
			 			catch (std::bad_alloc&)
				 			{
				 				std::cerr << "Can't insert element in avl tree" << std::endl;
				 				exit(1);
				 			}
			 			return node;
			 		}
				if (key < node->Key)
				{
					node->Left = Insert(node->Left, key, value);
				}
				else if (key > node->Key)
				{
					node->Right = Insert(node->Right, key, value);
				}
				else
				{
				    node->Value=value;
				}
		 		return ReBalance(node);
			}
	 	TNode* DeleteMin(TNode* node, TNode* iter)
		 	{
		 		if (iter->Left)
			 			iter->Left = DeleteMin(node, iter->Left);
		 		else
			 		{

				 		TNode* right = iter->Right;
			 			node->Key = iter->Key;
						node->Value = iter->Value;
			 			delete iter;
						iter = right;
			 		}
		 		return ReBalance(iter);
		 	}
	 	TNode* DeleteNode(TNode* node, K key)
		 	{
				if (!node) {
					return 0;
				}
				if (key < node->Key)
				{
					node->Left = DeleteNode(node->Left, key);
				}
				else if (node->Key < key)
				{
					node->Right = DeleteNode(node->Right, key);
				}
		 		else
			 		{
			 			TNode *left = node->Left, *right = node->Right;
			 			if (!left && !right)
				 			{
				 				delete node;
				 				return 0;
				 			}
						if (!right)
						{
							return left;
						}
			 			node->Right = DeleteMin(node, right);
			 		}
		 		return ReBalance(node);
		 	}
	 	TNode* Search(TNode* node, K key)
		 	{
				if (!node)
				{
					return 0;
				}
		 		TNode* iter;
		 		for (iter = node; iter; )
			 		{
						if (key < iter->Key)
						{
							iter = iter->Left;
						}
						else if (iter->Key < key)
						{
							iter = iter->Right;
						}
						else
						{
							return iter;
						}
			 		}
		 		return 0;
        }
        void AVLDelete(TNode* node)
		 	{
				if (node->Left)
				{
					AVLDelete(node->Left);
				}
				if (node->Right)
				{
					AVLDelete(node->Right);
				}
		 		delete node;
		 	}
    void PrintTree(TNode* node)
                {
                    if(!node)
                    {
                        return;
                    }
                    PrintTree(node->Left);
                    std::cout << node->Key<<std::endl;
                    PrintTree(node->Right);



                }
        	 public:
		 	TAVLTree() : Root(0) {};
		 	void Add(K key, V value) { Root = Insert(Root, key, value); }
		 	void Del(K key) { Root = DeleteNode(Root, key); }
		 	V* Find(K key)
			 	{
                TNode* node = Search(Root, key);
		 		if (node)
			 			return &(node->Value);
		 		else
			 			return 0;
                }
                void Print()
                {
                    PrintTree(Root);
                }

		 	~TAVLTree() {
		 	    if (Root)
                    AVLDelete(Root);
		 	    }
		 };
struct TSuffixNode
{
    TAVLTree<char,TSuffixNode*> Tree;
    TSuffixNode* SuffixLink, *Prev;
    string::iterator Begin,End;
    TSuffixNode(string::iterator begin,string::iterator end):SuffixLink(0),Prev(0),Begin(begin),End(end){}
    int Length(string::iterator current)
    {
        return Min(current+1-Begin,End-Begin);
    }

};
struct TActivePoint
{
    TSuffixNode* Node;
    string::iterator Edge;
    int Length;
    TActivePoint(TSuffixNode *node,string::iterator edge,const int len=0):Node(node),Edge(edge),Length(len){}

};
struct TNeedSuffixLink
{
    TSuffixNode *Root;
    TSuffixNode* NeedSL;
    TNeedSuffixLink(TSuffixNode *root):Root(root),NeedSL(root){};
    TNeedSuffixLink& operator()(TSuffixNode *node)
    {

        if(NeedSL != Root)
        {
            NeedSL->SuffixLink=node;

        }
        NeedSL=node;
        return *this;
    }

};
class TSuffixTree
{

    string String;
    TSuffixNode* Root;
    TActivePoint ActivePoint;
    int Remainder;
    bool WalkDown(string::iterator current,TSuffixNode* node)
    {

        if(ActivePoint.Length>=node->Length(current))
        {

            ActivePoint.Edge+=node->Length(current);
            ActivePoint.Length-=node->Length(current);
            ActivePoint.Node=node;
            return true;
        }
        return false;

    }
    void InsertInSuffixTree(string::iterator add)
    {

        TNeedSuffixLink CreateSuffixLink(Root);
        Remainder++;
        while(Remainder)
        {

            if(!ActivePoint.Length)
            {

                ActivePoint.Edge = add;
            }
            TSuffixNode **answ=ActivePoint.Node->Tree.Find(*ActivePoint.Edge);
            //std::cout<<"Found"<<std::endl<<answ<<std::endl;
            TSuffixNode *next=(!answ)? NULL : *answ;
            if(!next)
            {
                //std::cout <<"1" <<std::endl;
                TSuffixNode*leaf = new TSuffixNode(add,String.end());
                //std::cout <<"leaf" <<leaf<<std::endl;
                ActivePoint.Node->Tree.Add(*ActivePoint.Edge,leaf);
                leaf->Prev=ActivePoint.Node;
                CreateSuffixLink(ActivePoint.Node);
            }
            else
            {
                if(WalkDown(add,next))
                {
                    //std::cout <<"-1"<<std::endl;
                    continue;
                }
                if(*(next->Begin+ActivePoint.Length)==*add)
                {
                  //  std::cout <<"2\n";
                    ActivePoint.Length++;
                   // std::cout <<ActivePoint.Length<<std::endl;
                    CreateSuffixLink(ActivePoint.Node);
                    break;
                }

                //std::cout<<3<<std::endl;
                TSuffixNode *split = new TSuffixNode(next->Begin,next->Begin+ActivePoint.Length);
                TSuffixNode *leaf = new TSuffixNode(add,String.end());
                ActivePoint.Node->Tree.Add(*ActivePoint.Edge,split);
                split->Prev=ActivePoint.Node;
                split->Tree.Add(*add,leaf);
                leaf->Prev=split;
                next->Begin += ActivePoint.Length;
                split->Tree.Add(*next->Begin,next);
                next->Prev = split;
                CreateSuffixLink(split);
            }
            Remainder--;
            if(ActivePoint.Node==Root&& ActivePoint.Length)
            {

                ActivePoint.Length--;
                ActivePoint.Edge=add-Remainder+1;
            }
            else{
                ActivePoint.Node=(ActivePoint.Node->SuffixLink)? ActivePoint.Node->SuffixLink : Root;
            }
        }
    }
    TSuffixNode* GoBySuffixLink(const TSuffixNode* cur) const
    {

        return cur->SuffixLink? cur->SuffixLink :cur->Prev->SuffixLink;
    }
    public:
    TSuffixTree(const string s):String(s),Root(new TSuffixNode(String.end(),String.end())),ActivePoint(Root,String.begin()),Remainder(0)
    {
        Root->SuffixLink=Root->Prev=Root;
        for(string::iterator it =String.begin();it!=String.end();it++)
        {

            InsertInSuffixTree(it);
             //std::cout << *it<<std::endl;
        }
    }
    TVector<int> MatchingStatistic(const string cstring) const
    {
        TVector<int> ms(cstring.size(),0);
        TSuffixNode* cur=Root,*next;
        int jump=0;
        for(int i=0;i<(int)cstring.size();i++)
        {
            int pos=i;
            if(cur!=Root && (cur=GoBySuffixLink(cur))!=Root)
            {

                ms[i]=ms[i-1]-1-jump;
                pos+=ms[i];
                TSuffixNode **answer=cur->Tree.Find(cstring[pos]);
                if(!answer)
                {

                    continue;
                }
                next=*answer;
                cur=next->Prev;

            }
            else
            {
                TSuffixNode **answerTwo = cur->Tree.Find(cstring[i]);
                if(!answerTwo)
                {
                    ms[i]=0;
                    continue;
                }
                next = *answerTwo;
            }
            while(1)
            {
                jump=0;
                string::iterator it;
                for(it=next->Begin;it!=next->End && pos<(int)cstring.size();it++,ms[i]++,pos++,jump++)
                {

                    if(*it!=cstring[pos])
                        break;
                }
                if(it!=next->End)
                {

                    break;
                }
                TSuffixNode** answerThree=next->Tree.Find(cstring[pos]);
                if(answerThree)
                {
                    cur=next;
                    next=*answerThree;
                }
                else
                {
                    cur=next;
                    jump=0;
                    break;

                }
            }
        }
        return ms;
    }

};
int MaxEl(TVector<int> & Vector)
{
    int maxEl=0;
    for(int i=0;i< Vector.SizeofSize();i++)
    {
        if(maxEl<Vector[i])
        {
            maxEl=Vector[i];
        }
    }
    return maxEl;
}
int main()
{
string str;
string str2;
cin>>str>>str2;
if(str.size()>str2.size())
{
    str.swap(str2);
}
TAVLTree<string,int> answer;
 TSuffixTree tree(str+"$");
 TVector<int> ms=tree.MatchingStatistic(str2);
 int max=MaxEl(ms);
 std::cout << max << std::endl;
 if(max)
 {
    for(int i=0;i<ms.SizeofSize();i++)
    {
        if(ms[i]==max)
        {
            answer.Add(str2.substr(i,max),i);
        }
    }
    answer.Print();

 }
 //for(int i=0;i<ms.SizeofSize();i++)
 //{

 //    std::cout <<ms[i]<<std::endl;
 //}
}
