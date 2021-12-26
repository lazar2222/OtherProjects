#ifndef _AVLTree_H_
#define _AVLTree_H_

struct TreeNode
{
	int value;
	int count;
	int STD;
	TreeNode* left;
	TreeNode* right;
};

class AVLTree
{
	public:;

	  int find(int target);
	  int findSilent(int target);
	  void insert(int target);
	  void clear();
	  void print(int color);
	  int tmin();
	  int tmax();

	private:;

	   TreeNode* root = nullptr;
	   TreeNode* newNode(int val = 0, int cnt = 0, int t = 0, TreeNode* l = nullptr, TreeNode* r = nullptr);
	   void delNode(TreeNode* n);
	   void updateSTD(TreeNode* n);
	   int balance(TreeNode* n);
	   bool isCritical(TreeNode* n);
	   void fixTree(TreeNode* n,int t);
	   int balanceDir(int b);
	   void rotl(TreeNode* n);
	   void rotr(TreeNode* n);
};

#endif // !_AVLTree_H_