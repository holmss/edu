#ifndef RBTREE_H
#define RBTREE_H
#include <cstdint>
#include <cstring>
#include <fstream>

const char BLACK = 'b';
const char RED = 'r';

class TRBNode
{
public:
	TRBNode();
	//TRBNode(const TRBNode&);
	TRBNode(const char *, uint64_t);
	char* key;
	uint64_t value;
	TRBNode* left;
	TRBNode* right;
	TRBNode* parent;
	//static TRBNode* nil;
	char colour;
	virtual ~TRBNode();
};

class TRBTree{
public:

    TRBNode* nil;
	TRBNode* root;
	//TRBNode* MakeNode();
	const char MARKER='!';
	void Serialize(TRBNode* node, std::ofstream &fp);
	void DeSerialize(TRBNode* parNode,TRBNode*& node, std::ifstream &file, char * temp);
	TRBTree();
	bool RBInsert(const char*, unsigned long long);
    TRBNode* Search( char*);
	void RBDelete(TRBNode*);
	virtual ~TRBTree();
private:
	TRBNode* Minimum(TRBNode*) const;
	void RBInsertFixup(TRBNode*);
	void LeftRotate(TRBNode*);
	void RightRotate(TRBNode*);
	void RBDeleteFixup(TRBNode*);
	void RBTransplant(TRBNode*, TRBNode*);
    void DistructTree(TRBNode *);
};
#endif //RBTREE_H