#ifndef _ttfTree_H_
#define _ttfTree_H_

#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include "TerminalStuff.h"

using namespace std;

const int kn = 3;
const int stn = 4;

template <class K, class V>
struct TreeNode
{
	K* keys[3] = {};
	V* values[3] = {};
	TreeNode* st[4] = {};
};

template <class K, class V>
class ttfTree
{
public:;

	  void init();
	  void init(istream& stream);
	  void deleteTree();
	  bool containsKey(K t);
	  V findKey(K t);
	  void insert(K k, V v);
	  void deleteKey(K tk, V tv);
	  void deleteTop();
	  template <class K, class V>
	  friend ostream& operator<<(ostream& os, const ttfTree <K, V> tree);
	  void modifyKey(K ok, V ov, K nk);
	  int keyCount(K t);
	  void print(ostream& os);
	  template <class K, class V>
	  friend class binaryttfTree;
	  template <class K, class V>
	  friend class binaryttfTreeNode;

private:;
	   TreeNode<K, V>* root = nullptr;
	   TreeNode<K, V>* newNode();
	   void delNode(TreeNode<K, V>* n);
	   K* keyProxy(K k);
	   V* valueProxy(V v);
	   void setKV(TreeNode<K, V>* n, int pos, K k, V v);
	   void clearKV(TreeNode<K, V>* n, int pos);
	   void moveKV(TreeNode<K, V>* dn, int dpos, TreeNode<K, V>* sn, int spos);
	   void swapKV(TreeNode<K, V>* dn, int dpos, TreeNode<K, V>* sn, int spos);
	   bool r(K ka, V va, K kb, V vb);
	   bool e(K ka, V va, K kb, V vb);
	   bool r(K ka, V va, TreeNode<K, V>* n, int pos);
	   bool e(K ka, V va, TreeNode<K, V>* n, int pos);
	   bool r(TreeNode<K, V>* dn, int dpos, TreeNode<K, V>* sn, int spos);
	   int nodeCount(TreeNode<K, V>* n);
	   void nodeInsert(TreeNode<K, V>* n, K k, V v, TreeNode<K, V>* pre);
	   bool isLefa(TreeNode<K, V>* n);
	   int parrentIndex(TreeNode<K, V>* n, TreeNode<K, V>* p);
	   int realBrother(TreeNode<K, V>* n, TreeNode<K, V>* p);
	   int divK(TreeNode<K, V>* n, TreeNode<K, V>* p);
	   TreeNode<K, V>* maxKey(int& pos);
	   TreeNode<K, V>* minKey(int& pos);
	   int treeLevel();
};

template <class K, class V>
class binaryttfTree {
public:;

	  binaryttfTree<K, V>(ttfTree<K, V>& base);
	  template <class K, class V>
	  friend ostream& operator<<(ostream& os, const binaryttfTree<K, V> tree);
	  void print(ostream& os);
private:;
	   ttfTree<K, V>& baseTree;
};

template <class K, class V>
class binaryttfTreeNode {
public:;

	  static binaryttfTreeNode<K, V> rootNode(ttfTree<K, V>& base);
	  bool black();
	  K key();
	  V value();
	  binaryttfTreeNode<K, V> left();
	  binaryttfTreeNode<K, V> right();
	  bool isNull();
	  template <class K, class V>
	  friend class binaryttfTree;
private:;
	   binaryttfTreeNode<K, V>(TreeNode<K, V>* n, int p);
	   TreeNode<K, V>* node;
	   int pos;
};

template<class K, class V>
void ttfTree<K, V>::init()
{
	deleteTree();
}

void ttfTree<int, string>::init(istream& stream)
{
	string line;
	while (getline(stream, line)) {
		for (int i = line.length(); i >= 0; i--)
		{
			if (line[i] == ' ')
			{
				string action = line.substr(0, i);
				string sp = line.substr(i);
				int prio = stoi(sp);
				insert(prio, action);
				break;
			}
		}
	};
}

template<class K, class V>
void ttfTree<K, V>::deleteTree()
{
	if (root == nullptr) { return; }
	TreeNode<K, V>* c;
	stack<TreeNode<K, V>*> S;
	queue<TreeNode<K, V>*> Q;

	Q.push(root);
	S.push(root);
	while (!Q.empty())
	{
		c = Q.front();
		Q.pop();
		for (int i = 0; i < stn; i++)
		{
			if (c->st[i] != nullptr)
			{
				Q.push(c->st[i]);
				S.push(c->st[i]);
			}
		}
	}
	while (!S.empty())
	{
		c = S.top();
		S.pop();
		delNode(c);
	}

	root = nullptr;
}

template<class K, class V>
bool ttfTree<K, V>::containsKey(K t)
{
	TreeNode<K, V>* cur = root;
	TreeNode<K, V>* tmp;
	while (cur != nullptr)
	{
		for (int i = 0; i < kn; i++)
		{
			if (cur->keys[i] != nullptr)
			{
				if (t == *(cur->keys[i])) { return true; }
				else if (t < *(cur->keys[i])) { tmp = cur->st[i]; break; }
				else { tmp = cur->st[i + 1]; }
			}
		}
		cur = tmp;
	}
	return false;
}

template<class K, class V>
V ttfTree<K, V>::findKey(K t)
{
	TreeNode<K, V>* cur = root;
	TreeNode<K, V>* tmp = nullptr;
	V* res = nullptr;
	while (cur != nullptr)
	{
		for (int i = 0; i < kn; i++)
		{
			if (cur->keys[i] != nullptr)
			{
				if (t == *(cur->keys[i])) { res = cur->values[i]; tmp = cur->st[i + 1]; }
				else if (t < *(cur->keys[i])) { tmp = cur->st[i]; break; }
				else { tmp = cur->st[i + 1]; }
			}
		}
		cur = tmp;
	}
	if (res != nullptr) { return *res; }
	throw 404;
}

template<class K, class V>
void ttfTree<K, V>::insert(K k, V v)
{
	if (root == nullptr)
	{
		root = newNode();
		setKV(root, 1, k, v);
		return;
	}

	stack<TreeNode<K, V>*> S;
	TreeNode<K, V>* cur = root;
	TreeNode<K, V>* tmp = nullptr;
	while (cur != nullptr)
	{
		S.push(cur);
		for (int i = 0; i < kn; i++)
		{
			if (cur->keys[i] != nullptr)
			{
				if (e(k, v, cur, i)) { throw 202; }
				else if (!r(k, v, cur, i)) { tmp = cur->st[i]; break; }
				else { tmp = cur->st[i + 1]; }
			}
		}
		cur = tmp;
	}
	TreeNode<K, V>* pre = nullptr;
	while (true)
	{
		cur = S.top();
		S.pop();
		if (nodeCount(cur) == 3)
		{
			TreeNode<K, V>* nn = newNode();
			K tk = *(cur->keys[1]);
			V tv = *(cur->values[1]);
			moveKV(cur, 1, cur, 0);
			moveKV(nn, 1, cur, 2);
			nn->st[2] = cur->st[3];
			nn->st[1] = cur->st[2];
			cur->st[2] = cur->st[1];
			cur->st[1] = cur->st[0];
			cur->st[0] = nullptr;
			cur->st[3] = nullptr;



			if (r(k, v, tk, tv))
			{
				nodeInsert(nn, k, v, pre);
			}
			else
			{
				nodeInsert(cur, k, v, pre);
			}

			k = tk;
			v = tv;
			pre = nn;
			if (S.empty())
			{
				nn = newNode();
				setKV(nn, 1, k, v);
				nn->st[1] = cur;
				nn->st[2] = pre;
				root = nn;
				break;
			}
		}
		else
		{
			nodeInsert(cur, k, v, pre);
			break;
		}
	}

}

template<class K, class V>
void ttfTree<K, V>::deleteKey(K tk, V tv)
{
	if (root == nullptr) { throw 404; }
	stack<TreeNode<K, V>*> S;
	TreeNode<K, V>* cur = root;
	TreeNode<K, V>* tmp = nullptr;
	int pos = -1;
	while (cur != nullptr)
	{
		S.push(cur);
		for (int i = 0; i < kn; i++)
		{
			if (cur->keys[i] != nullptr)
			{
				if (e(tk, tv, cur, i)) { tmp = nullptr; pos = i; break; }
				else if (!r(tk, tv, cur, i)) { tmp = cur->st[i]; break; }
				else { tmp = cur->st[i + 1]; }
			}
		}
		cur = tmp;
	}

	if (pos == -1) { throw 404; }

	cur = S.top();
	S.pop();
	if (!isLefa(cur))
	{
		TreeNode<K, V>* rc = cur;
		S.push(cur);
		cur = cur->st[pos + 1];
		while (true)
		{
			S.push(cur);
			if (isLefa(cur))
			{
				if (cur->keys[0] == nullptr) { swapKV(rc, pos, cur, 1); pos = 1; }
				else { swapKV(rc, pos, cur, 0); pos = 0; }
				break;
			}
			else
			{
				if (cur->keys[0] == nullptr) { cur = cur->st[1]; }
				else { cur = cur->st[0]; }
			}
		}
	}
	else
	{
		S.push(cur);
	}
	bool prop = true;
	TreeNode<K, V>* pre = nullptr;
	while (prop) {
		prop = false;
		cur = S.top();
		S.pop();
		if (S.empty() && nodeCount(cur) == 1)
		{
			delNode(cur);
			root = pre;
			return;
		}
		if (pos != 1) { clearKV(cur, pos); }
		else
		{
			if (nodeCount(cur) == 3) { moveKV(cur, 1, cur, 2); }
			else if (nodeCount(cur) == 2)
			{
				if (cur->keys[0] == nullptr) { moveKV(cur, 1, cur, 2); }
				else { moveKV(cur, 1, cur, 0); }
			}
			else
			{
				//PROPAGACIJA
				int rbi = realBrother(cur, S.top());
				int rk = divK(cur, S.top());
				pos = parrentIndex(cur, S.top());
				if (rbi != -1)
				{
					TreeNode<K, V>* rb = S.top()->st[rbi];
					if (nodeCount(rb) == 3)
					{
						moveKV(cur, 1, S.top(), rk);
						moveKV(S.top(), rk, rb, 1);
						if (rbi > rk)
						{
							cur->st[1] = pre;
							moveKV(cur, 2, rb, 0);
							moveKV(rb, 1, rb, 2);
							cur->st[2] = rb->st[0];
							cur->st[3] = rb->st[1];
							rb->st[0] = nullptr;
							rb->st[1] = rb->st[2];
							rb->st[2] = rb->st[3];
							rb->st[3] = nullptr;
						}
						else
						{
							cur->st[2] = pre;
							moveKV(cur, 0, rb, 2);
							moveKV(rb, 1, rb, 0);
							cur->st[1] = rb->st[3];
							cur->st[0] = rb->st[2];
							rb->st[3] = nullptr;
							rb->st[2] = rb->st[1];
							rb->st[1] = rb->st[0];
							rb->st[0] = nullptr;
						}
					}
					else if (nodeCount(rb) == 2)
					{
						moveKV(cur, 1, S.top(), rk);
						if (rk == pos)
						{
							cur->st[1] = pre;
							if (rb->keys[0] == nullptr)
							{
								moveKV(S.top(), rk, rb, 1);
								moveKV(rb, 1, rb, 2);
								cur->st[2] = rb->st[1];
								rb->st[1] = rb->st[2];
								rb->st[2] = rb->st[3];
								rb->st[3] = nullptr;
							}
							else {
								moveKV(S.top(), rk, rb, 0);
								cur->st[2] = rb->st[0];
								rb->st[0] = nullptr;
							}

						}
						else
						{
							cur->st[2] = pre;
							if (rb->keys[2] == nullptr)
							{
								moveKV(S.top(), rk, rb, 1);
								moveKV(rb, 1, rb, 0);
								cur->st[1] = rb->st[2];
								rb->st[2] = rb->st[1];
								rb->st[1] = rb->st[0];
								rb->st[0] = nullptr;
							}
							else {
								moveKV(S.top(), rk, rb, 2);
								cur->st[1] = rb->st[3];
								rb->st[3] = nullptr;
							}
							cur->st[1] = pre;
						}
					}
					else
					{
						if (r(rb, 1, S.top(), rk))
						{
							moveKV(rb, 2, rb, 1);
							rb->st[3] = rb->st[2];
							rb->st[2] = rb->st[1];
							rb->st[1] = pre;
						}
						else
						{
							moveKV(rb, 0, rb, 1);
							rb->st[0] = rb->st[1];
							rb->st[1] = rb->st[2];
							rb->st[2] = pre;
						}
						moveKV(rb, 1, S.top(), rk);
						if (rk == 0)
						{
							S.top()->st[1] = S.top()->st[rbi];
							S.top()->st[0] = nullptr;
						}
						else if (rk == 1)
						{
							pre = S.top()->st[rbi];
							pos = 1;
							setKV(S.top(), rk, *(rb->keys[1]), *(rb->values[1]));
							prop = true;
						}
						else
						{
							S.top()->st[2] = S.top()->st[rbi];
							S.top()->st[3] = nullptr;
						}
						delNode(cur);
					}
				}
				else
				{
					int bi;
					if (rk == pos) { bi = pos + 1; }
					else { bi = rk; }
					TreeNode<K, V>* rs = S.top()->st[bi];

					if (nodeCount(rs) == 2)
					{
						moveKV(cur, 1, S.top(), 1);
						if (S.top()->keys[0] == nullptr)
						{
							cur->st[1] = pre;
							moveKV(S.top(), 1, S.top(), 2);
							if (rs->keys[0] == nullptr)
							{
								moveKV(S.top(), 0, rs, 1);
								moveKV(rs, 1, rs, 2);
								cur->st[2] = rs->st[1];
								rs->st[1] = rs->st[2];
								rs->st[2] = rs->st[3];
								rs->st[3] = nullptr;
							}
							else {
								moveKV(S.top(), 0, rs, 0);
								cur->st[2] = rs->st[0];
								rs->st[0] = nullptr;
							}
							S.top()->st[0] = S.top()->st[1];
							S.top()->st[1] = S.top()->st[2];
							S.top()->st[2] = S.top()->st[3];
							S.top()->st[3] = nullptr;
						}
						else {
							cur->st[2] = pre;
							moveKV(S.top(), 1, S.top(), 0);
							if (rs->keys[2] == nullptr)
							{
								moveKV(S.top(), 2, rs, 1);
								moveKV(rs, 1, rs, 0);
								cur->st[1] = rs->st[2];
								rs->st[2] = rs->st[1];
								rs->st[1] = rs->st[0];
								rs->st[0] = nullptr;
							}
							else {
								moveKV(S.top(), 2, rs, 2);
								cur->st[1] = rs->st[3];
								rs->st[3] = nullptr;
							}
							S.top()->st[3] = S.top()->st[2];
							S.top()->st[2] = S.top()->st[1];
							S.top()->st[1] = S.top()->st[0];
							S.top()->st[0] = nullptr;
						}
					}
					else if (nodeCount(rs) == 3)
					{
						moveKV(cur, 1, S.top(), 1);
						if (S.top()->keys[0] == nullptr)
						{
							cur->st[1] = pre;
							moveKV(S.top(), 1, S.top(), 2);
							moveKV(S.top(), 0, rs, 1);

							moveKV(rs, 1, rs, 2);
							moveKV(cur, 2, rs, 0);

							cur->st[2] = rs->st[0];
							cur->st[3] = rs->st[1];
							rs->st[0] = nullptr;
							rs->st[1] = rs->st[2];
							rs->st[2] = rs->st[3];
							rs->st[3] = nullptr;

							S.top()->st[0] = S.top()->st[1];
							S.top()->st[1] = S.top()->st[2];
							S.top()->st[2] = S.top()->st[3];
							S.top()->st[3] = nullptr;
						}
						else {
							cur->st[2] = pre;
							moveKV(S.top(), 1, S.top(), 0);
							moveKV(S.top(), 2, rs, 1);

							moveKV(rs, 1, rs, 0);
							moveKV(cur, 0, rs, 2);

							cur->st[1] = rs->st[3];
							cur->st[0] = rs->st[2];
							rs->st[3] = nullptr;
							rs->st[2] = rs->st[1];
							rs->st[1] = rs->st[0];
							rs->st[0] = nullptr;

							S.top()->st[3] = S.top()->st[2];
							S.top()->st[2] = S.top()->st[1];
							S.top()->st[1] = S.top()->st[0];
							S.top()->st[0] = nullptr;
						}
					}
					else
					{
						if (r(rs, 1, S.top(), rk))
						{
							moveKV(rs, 2, rs, 1);
							rs->st[3] = rs->st[2];
							rs->st[2] = rs->st[1];
							rs->st[1] = pre;
						}
						else
						{
							moveKV(rs, 0, rs, 1);
							rs->st[0] = rs->st[1];
							rs->st[1] = rs->st[2];
							rs->st[2] = pre;
						}
						moveKV(rs, 1, S.top(), rk);
						if (S.top()->keys[0] == nullptr)
						{
							moveKV(S.top(), 1, S.top(), 2);
							S.top()->st[1] = S.top()->st[2];
							S.top()->st[2] = S.top()->st[3];
							S.top()->st[3] = nullptr;
						}
						else
						{
							moveKV(S.top(), 1, S.top(), 0);
							S.top()->st[2] = S.top()->st[1];
							S.top()->st[1] = S.top()->st[0];
							S.top()->st[0] = nullptr;
						}
						delNode(cur);
					}
				}
			}

		}
	}
}

template<class K, class V>
void ttfTree<K, V>::deleteTop()
{
	int rpos;
	TreeNode<K, V>* maxn = maxKey(rpos);
	deleteKey(*(maxn->keys[rpos]), *(maxn->values[rpos]));
}

template<class K, class V>
void ttfTree<K, V>::modifyKey(K ok, V ov, K nk)
{
	if (root == nullptr) { throw 404; }
	stack<TreeNode<K, V>*> S;
	TreeNode<K, V>* cur = root;
	TreeNode<K, V>* tmp = nullptr;
	int pos = -1;
	while (cur != nullptr)
	{
		S.push(cur);
		for (int i = 0; i < kn; i++)
		{
			if (cur->keys[i] != nullptr)
			{
				if (e(ok, ov, cur, i)) { tmp = nullptr; pos = i; break; }
				else if (!r(ok, ov, cur, i)) { tmp = cur->st[i]; break; }
				else { tmp = cur->st[i + 1]; }
			}
		}
		cur = tmp;
	}

	if (pos == -1) { throw 404; }

	cur = S.top();
	S.pop();
	if (isLefa(cur))
	{
		int rk = divK(cur, S.top());
		if (pos == rk)
		{
			if (r(nk, ov, S.top(), rk))
			{
				deleteKey(ok, ov);
				insert(nk, ov);
				return;
			}
		}
		else
		{
			if (!r(nk, ov, S.top(), rk))
			{
				deleteKey(ok, ov);
				insert(nk, ov);
				return;
			}
		}
	}
	else
	{
		deleteKey(ok, ov);
		insert(nk, ov);
		return;
	}
	//shuffle
	clearKV(cur, pos);
	if (pos == 1)
	{
		if (cur->keys[0] != nullptr) { moveKV(cur, 1, cur, 0); }
		else if (cur->keys[2] != nullptr) { moveKV(cur, 1, cur, 2); }
	}
	nodeInsert(cur, nk, ov, nullptr);
}

template<class K, class V>
int ttfTree<K, V>::keyCount(K t)
{
	int cnt = 0;
	stack<TreeNode<K, V>*> S;
	TreeNode<K, V>* cur;
	TreeNode<K, V>* tmp;
	S.push(root);
	while (!S.empty())
	{
		cur = S.top();
		S.pop();
		if (cur != nullptr) {
			for (int i = 0; i < kn; i++)
			{
				if (cur->keys[i] != nullptr)
				{
					if (t == *(cur->keys[i])) { S.push(cur->st[i]); tmp = cur->st[i + 1]; cnt++; }
					else if (t < *(cur->keys[i])) { tmp = cur->st[i]; break; }
					else { tmp = cur->st[i + 1]; }
				}
			}
			S.push(tmp);
		}
	}
	return cnt;
}

void ttfTree<int, string>::print(ostream& os)
{
	if (root == nullptr) { return; }
	int minpos, maxpos;
	int ds = mmax(mmax(dataSize(*(minKey(minpos)->keys[minpos])), dataSize(*(maxKey(maxpos)->keys[maxpos]))), 3);
	int fs = (ds * 3) + 5;
	int treelvl = treeLevel();
	int bh = (treelvl * 4);
	int bw = pow(4, treelvl - 1) * fs;
	ScreenBuffer SB(bw, bh, os);

	queue<TreeNode<int, string>*> NQ;
	queue<int> LQ;
	NQ.push(root);
	LQ.push(1);

	int fieldcount = 0;
	int llevel = 0;

	while (LQ.front() <= treelvl)
	{
		TreeNode<int, string>* cn = NQ.front(); NQ.pop();
		int lvl = LQ.front(); LQ.pop();
		if (lvl != llevel) { fieldcount = 0; }
		else { fieldcount++; }
		llevel = lvl;
		int fieldsize = bw / pow(4, lvl - 1);
		int currline = (lvl - 1) * 4;
		if (cn != nullptr)
		{
			int fieldstart = (fieldcount * fieldsize) + ((fieldsize - fs) / 2);
			SB[currline][fieldstart] = '[';
			SB[currline + 1][fieldstart] = '[';
			SB[currline][fieldstart + 1 + ds] = '|';
			SB[currline + 1][fieldstart + 1 + ds] = '|';
			SB[currline][fieldstart + 2 + 2 * ds] = '|';
			SB[currline + 1][fieldstart + 2 + 2 * ds] = '|';
			SB[currline][fieldstart + 3 + 3 * ds] = ']';
			SB[currline + 1][fieldstart + 3 + 3 * ds] = ']';
			if (cn->keys[0] != nullptr) { SB.printCenteredInField(*(cn->keys[0]), fieldstart + 1, currline, ds); }
			if (cn->keys[1] != nullptr) { SB.printCenteredInField(*(cn->keys[1]), fieldstart + 2 + ds, currline, ds); }
			if (cn->keys[2] != nullptr) { SB.printCenteredInField(*(cn->keys[2]), fieldstart + 3 + 2 * ds, currline, ds); }
			if (cn->values[0] != nullptr) { SB.printCenteredInField(*(cn->values[0]), fieldstart + 1, currline + 1, ds); }
			if (cn->values[1] != nullptr) { SB.printCenteredInField(*(cn->values[1]), fieldstart + 2 + ds, currline + 1, ds); }
			if (cn->values[2] != nullptr) { SB.printCenteredInField(*(cn->values[2]), fieldstart + 3 + 2 * ds, currline + 1, ds); }
			SB.printMultiBranch(cn->st[0] != nullptr, cn->st[1] != nullptr, cn->st[2] != nullptr, cn->st[3] != nullptr, fieldcount * fieldsize, currline + 2, fieldsize, ds);
			for (int i = 0; i < ds; i++)
			{
				SB.characterColor(fieldstart + 1 + i, currline, 91);
				SB.characterColor(fieldstart + 1 + i, currline + 1, 91);
				SB.characterColor(fieldstart + 2 + ds + i, currline, 90);
				SB.characterColor(fieldstart + 2 + ds + i, currline + 1, 90);
				SB.characterColor(fieldstart + 3 + 2 * ds + i, currline, 91);
				SB.characterColor(fieldstart + 3 + 2 * ds + i, currline + 1, 91);
			}
		}
		if (cn == nullptr)
		{
			if (lvl < treelvl)
			{
				NQ.push(nullptr);
				LQ.push(lvl + 1);
				NQ.push(nullptr);
				LQ.push(lvl + 1);
				NQ.push(nullptr);
				LQ.push(lvl + 1);
				NQ.push(nullptr);
				LQ.push(lvl + 1);
			}
		}
		else
		{
			for (int i = 0; i < stn; i++)
			{
				NQ.push(cn->st[i]);
				LQ.push(lvl + 1);
			}
		}
	}

	SB.enableColor();
	SB.printBuffer();
	SB.disableColor();
	if (ds >= 4)
	{
		cout << endl << "U stablu postoje podatci koji se ispisuju na sirini od vise od 4 karaktera, koristi se eksperimentalni ispis stabla" << endl;
	}
	if (bw > 80)
	{
		cout << endl << "Stablo je sire od 80 karaktera, stablo ce takodje biti ispisano u fajl stablo.txt" << endl;
		SB.printToFile("stablo.txt");
	}
	SB.deleteBuffer();
}

template<class K, class V>
TreeNode<K, V>* ttfTree<K, V>::maxKey(int& pos)
{
	TreeNode<K, V>* cur = root;
	TreeNode<K, V>* maxk = nullptr;
	while (cur != nullptr)
	{
		for (int i = kn - 1; i >= 0; i--)
		{
			if (cur->keys[i] != nullptr)
			{
				maxk = cur;
				pos = i;
				cur = cur->st[i + 1];
				break;
			}
		}
	}

	if (maxk == nullptr) { throw 404; }
	return maxk;
}

template<class K, class V>
TreeNode<K, V>* ttfTree<K, V>::minKey(int& pos)
{
	TreeNode<K, V>* cur = root;
	TreeNode<K, V>* mink = nullptr;
	while (cur != nullptr)
	{
		for (int i = 0; i < kn; i++)
		{
			if (cur->keys[i] != nullptr)
			{
				mink = cur;
				pos = i;
				cur = cur->st[i];
				break;
			}
		}
	}

	if (mink == nullptr) { throw 404; }
	return mink;
}
template<class K, class V>
int ttfTree<K, V>::treeLevel()
{
	TreeNode<K, V>* cur = root;
	int lvl = 0;
	while (cur != nullptr)
	{
		lvl++;
		for (int i = 0; i < kn; i++)
		{
			if (cur->keys[i] != nullptr)
			{
				cur = cur->st[i];
				break;
			}
		}
	}
	return lvl;
}
template<class K, class V>
TreeNode<K, V>* ttfTree<K, V>::newNode()
{
	return new TreeNode<K, V>;
}

template<class K, class V>
void ttfTree<K, V>::delNode(TreeNode<K, V>* n)
{
	for (int i = 0; i < kn; i++)
	{
		delete n->keys[i];
		delete n->values[i];
	}
	delete n;
}

template<class K, class V>
K* ttfTree<K, V>::keyProxy(K k)
{
	K* kp = new K;
	*kp = k;
	return kp;
}

template<class K, class V>
V* ttfTree<K, V>::valueProxy(V v)
{
	V* vp = new V;
	*vp = v;
	return vp;
}

template<class K, class V>
void ttfTree<K, V>::setKV(TreeNode<K, V>* n, int pos, K k, V v)
{
	clearKV(n, pos);
	n->keys[pos] = keyProxy(k);
	n->values[pos] = valueProxy(v);
}

template<class K, class V>
void ttfTree<K, V>::clearKV(TreeNode<K, V>* n, int pos)
{
	delete n->keys[pos];
	delete n->values[pos];
	n->keys[pos] = nullptr;
	n->values[pos] = nullptr;
}

template<class K, class V>
void ttfTree<K, V>::moveKV(TreeNode<K, V>* dn, int dpos, TreeNode<K, V>* sn, int spos)
{
	clearKV(dn, dpos);
	dn->keys[dpos] = sn->keys[spos];
	sn->keys[spos] = nullptr;
	dn->values[dpos] = sn->values[spos];
	sn->values[spos] = nullptr;
}

template<class K, class V>
void ttfTree<K, V>::swapKV(TreeNode<K, V>* dn, int dpos, TreeNode<K, V>* sn, int spos)
{
	K* tk = sn->keys[spos];
	V* tv = sn->values[spos];
	sn->keys[spos] = dn->keys[dpos];
	sn->values[spos] = dn->values[dpos];
	dn->keys[dpos] = tk;
	dn->values[dpos] = tv;
}

template<class K, class V>
bool ttfTree<K, V>::r(K ka, V va, K kb, V vb)
{
	return (ka > kb) || (ka == kb && va <= vb);
}

template<class K, class V>
bool ttfTree<K, V>::e(K ka, V va, K kb, V vb)
{
	return ka == kb && va == vb;
}

template<class K, class V>
bool ttfTree<K, V>::r(K ka, V va, TreeNode<K, V>* n, int pos)
{
	return (ka > * (n->keys[pos])) || (ka == *(n->keys[pos]) && va <= *(n->values[pos]));
}

template<class K, class V>
bool ttfTree<K, V>::e(K ka, V va, TreeNode<K, V>* n, int pos)
{
	return ka == *(n->keys[pos]) && va == *(n->values[pos]);
}

template<class K, class V>
bool ttfTree<K, V>::r(TreeNode<K, V>* dn, int dpos, TreeNode<K, V>* sn, int spos)
{
	return (*(dn->keys[dpos]) > * (sn->keys[spos])) || (*(dn->keys[dpos]) == *(sn->keys[spos]) && *(dn->values[dpos]) <= *(sn->values[spos]));
}

template<class K, class V>
int ttfTree<K, V>::nodeCount(TreeNode<K, V>* n)
{
	int cnt = 0;
	for (int i = 0; i < kn; i++)
	{
		if (n->keys[i] != nullptr)
		{
			cnt++;
		}
	}
	return cnt;
}

template<class K, class V>
void ttfTree<K, V>::nodeInsert(TreeNode<K, V>* n, K k, V v, TreeNode<K, V>* pre)
{
	if (nodeCount(n) == 0)
	{
		setKV(n, 1, k, v);
	}
	else if (nodeCount(n) == 1)
	{
		if (r(k, v, n, 1))
		{
			setKV(n, 2, k, v);
			n->st[3] = pre;
		}
		else
		{
			setKV(n, 0, k, v);
			n->st[0] = n->st[1];
			n->st[1] = pre;
		}
	}
	else
	{
		if (r(k, v, n, 1))
		{
			if (n->keys[2] == nullptr) { setKV(n, 2, k, v); n->st[3] = pre; }
			else if (r(k, v, n, 2)) { moveKV(n, 0, n, 1); moveKV(n, 1, n, 2); setKV(n, 2, k, v); n->st[0] = n->st[1]; n->st[1] = n->st[2]; n->st[2] = n->st[3]; n->st[3] = pre; }
			else { moveKV(n, 0, n, 1); setKV(n, 1, k, v); n->st[0] = n->st[1]; n->st[1] = n->st[2]; n->st[2] = pre; }
		}
		else
		{
			if (n->keys[0] == nullptr) { setKV(n, 0, k, v); n->st[0] = n->st[1]; n->st[1] = pre; }
			else if (r(k, v, n, 0)) { moveKV(n, 2, n, 1); setKV(n, 1, k, v); n->st[3] = n->st[2]; n->st[2] = pre; }
			else { moveKV(n, 2, n, 1); moveKV(n, 1, n, 0); setKV(n, 0, k, v); n->st[3] = n->st[2]; n->st[2] = n->st[1]; n->st[1] = pre; }
		}
	}

}

template<class K, class V>
bool ttfTree<K, V>::isLefa(TreeNode<K, V>* n)
{
	return n->st[1] == nullptr;
}

template<class K, class V>
int ttfTree<K, V>::parrentIndex(TreeNode<K, V>* n, TreeNode<K, V>* p)
{
	int pos = 0;
	for (int i = 0; i < stn; i++)
	{
		if (p->st[i] == n) { pos = i; break; }
	}
	return pos;
}

template<class K, class V>
int ttfTree<K, V>::realBrother(TreeNode<K, V>* n, TreeNode<K, V>* p)
{
	int pos = parrentIndex(n, p);

	if (nodeCount(p) == 3)
	{
		switch (pos)
		{
		case 0: {return 1; }
		case 1: {return 0; }
		case 2: {return 3; }
		case 3: {return 2; }
		}
	}
	else if (nodeCount(p) == 2)
	{
		if (p->keys[0] == nullptr)
		{
			switch (pos)
			{
			case 1: {return -1; }
			case 2: {return 3; }
			case 3: {return 2; }
			}
		}
		else
		{
			switch (pos)
			{
			case 0: {return 1; }
			case 1: {return 0; }
			case 2: {return -1; }
			}
		}
	}
	else
	{
		switch (pos)
		{
		case 1: {return 2; }
		case 2: {return 1; }
		}
	}

}

template<class K, class V>
int ttfTree<K, V>::divK(TreeNode<K, V>* n, TreeNode<K, V>* p)
{
	int pos = parrentIndex(n, p);

	if (nodeCount(p) == 3)
	{
		switch (pos)
		{
		case 0: {return 0; }
		case 1: {return 0; }
		case 2: {return 2; }
		case 3: {return 2; }
		}
	}
	else if (nodeCount(p) == 2)
	{
		if (p->keys[0] == nullptr)
		{
			switch (pos)
			{
			case 1: {return 1; }
			case 2: {return 2; }
			case 3: {return 2; }
			}
		}
		else
		{
			switch (pos)
			{
			case 0: {return 0; }
			case 1: {return 0; }
			case 2: {return 1; }
			}
		}
	}
	else
	{
		switch (pos)
		{
		case 1: {return 1; }
		case 2: {return 1; }
		}
	}
}

template<class K, class V>
ostream& operator<<(ostream& os, ttfTree<K, V> tree)
{
	tree.print(os);
	return os;
}

template<class K, class V>
ostream& operator<<(ostream& os, binaryttfTree<K, V> tree)
{
	tree.print(os);
	return os;
}

template<class K, class V>
binaryttfTreeNode<K, V> binaryttfTreeNode<K, V>::rootNode(ttfTree<K, V>& base)
{
	return binaryttfTreeNode<K, V>(base.root, 1);
}

template<class K, class V>
bool binaryttfTreeNode<K, V>::black()
{
	if (isNull()) { throw 400; }
	return pos == 1;
}

template<class K, class V>
K binaryttfTreeNode<K, V>::key()
{
	if (isNull()) { throw 400; }
	return *(node->keys[pos]);
}

template<class K, class V>
V binaryttfTreeNode<K, V>::value()
{
	if (isNull()) { throw 400; }
	return *(node->values[pos]);
}

template<class K, class V>
binaryttfTreeNode<K, V> binaryttfTreeNode<K, V>::left()
{
	if (isNull()) { throw 400; }
	if (pos == 1)
	{
		return node->keys[0] == nullptr ? (binaryttfTreeNode<K, V>(node->st[1], 1)) : (binaryttfTreeNode<K, V>(node, 0));
	}
	else if (pos == 0)
	{
		return binaryttfTreeNode<K, V>(node->st[0], 1);
	}
	else
	{
		return binaryttfTreeNode<K, V>(node->st[2], 1);
	}
}

template<class K, class V>
binaryttfTreeNode<K, V> binaryttfTreeNode<K, V>::right()
{
	if (isNull()) { throw 400; }
	if (pos == 1)
	{
		return node->keys[2] == nullptr ? binaryttfTreeNode<K, V>(node->st[2], 1) : binaryttfTreeNode<K, V>(node, 2);
	}
	else if (pos == 0)
	{
		return binaryttfTreeNode<K, V>(node->st[1], 1);
	}
	else
	{
		return binaryttfTreeNode<K, V>(node->st[3], 1);
	}
}

template<class K, class V>
bool binaryttfTreeNode<K, V>::isNull()
{
	return node == nullptr || node->keys[pos] == nullptr;
}

void binaryttfTree<int, string>::print(ostream& os)
{
	if (baseTree.root == NULL) { return; }
	int minpos, maxpos;
	int ds = mmax(mmax(dataSize(*(baseTree.minKey(minpos)->keys[minpos])), dataSize(*(baseTree.maxKey(maxpos)->keys[maxpos]))) + 1, 3 + 1);
	int treelvl = baseTree.treeLevel() * 2;
	int bh = (treelvl * 3);
	int bw = pow(2, treelvl - 1) * ds;
	ScreenBuffer SB(bw, bh, os);

	queue<binaryttfTreeNode<int, string>> NQ;
	queue<int> LQ;
	NQ.push(binaryttfTreeNode<int, string>::rootNode(baseTree));
	LQ.push(1);

	int fieldcount = 0;
	int llevel = 0;

	while (LQ.front() <= treelvl)
	{
		binaryttfTreeNode<int, string> cn = NQ.front(); NQ.pop();
		int lvl = LQ.front(); LQ.pop();
		if (lvl != llevel) { fieldcount = 0; }
		else { fieldcount++; }
		llevel = lvl;
		int fieldsize = bw / pow(2, lvl - 1);
		int currline = (lvl - 1) * 3;
		if (!cn.isNull())
		{
			SB.printCenteredInField(cn.key(), fieldcount * fieldsize, currline, fieldsize);
			SB.printCenteredInField(cn.value().substr(0, ds - 1), fieldcount * fieldsize, currline + 1, fieldsize);
			SB.printBranch(!cn.left().isNull(), !cn.right().isNull(), fieldcount * fieldsize, currline + 2, fieldsize);

			for (int i = 0; i < fieldsize; i++)
			{
				SB.characterColor(fieldcount * fieldsize + i, currline, cn.black() ? 90 : 91);
				SB.characterColor(fieldcount * fieldsize + i, currline + 1, cn.black() ? 90 : 91);
			}

			NQ.push(cn.left()); NQ.push(cn.right());
			LQ.push(lvl + 1); LQ.push(lvl + 1);
		}
		else
		{
			NQ.push(binaryttfTreeNode<int, string>(nullptr, 1)); NQ.push(binaryttfTreeNode<int, string>(nullptr, 1));
			LQ.push(lvl + 1); LQ.push(lvl + 1);
		}
	}

	SB.enableColor();
	SB.printBuffer();
	SB.disableColor();
	if (ds > 4)
	{
		cout << endl << "U stablu postoje podatci koji se ispisuju na sirini od vise od 4 karaktera, koristi se eksperimentalni ispis stabla" << endl;
	}
	if (bw > 80)
	{
		cout << endl << "Stablo je sire od 80 karakter-a, stablo ce takodje biti ispisano u fajl stablo.txt" << endl;
		SB.printToFile("stablo.txt");
	}
	SB.deleteBuffer();
}

template<class K, class V>
binaryttfTreeNode<K, V>::binaryttfTreeNode(TreeNode<K, V>* n, int p)
{
	node = n;
	pos = p;
}

template<class K, class V>
binaryttfTree<K, V>::binaryttfTree(ttfTree<K, V>& base) : baseTree(base)
{

}

#endif // !_ttfTree_H_
