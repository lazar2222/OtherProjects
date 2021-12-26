#include <iostream>
#include <stack>
#include <cmath>
#include <queue>
#include "AVLTree.h"
#include "FunkySortedMatrix.h"
#include "TerminalStuff.h"
#include <chrono>
#include <thread>

using namespace std;

int AVLTree::find(int target)
{
    TreeNode* cur = root;
    int cnt = 0;
    while (cur != nullptr) 
    {
        cnt++;
        if (cur->value == target) 
        {
            cout << target << " pronadjen, postoji " <<cur->count << " identicnih kljuceva" << endl;
            return cnt;
        }
        else if (cur->value > target) 
        {
            cur = cur->left;
        }
        else 
        {
            cur = cur->right;
        }
    }
    cout << target << " nije pronadjen" << endl;
    return cnt;
}

int AVLTree::findSilent(int target)
{
    TreeNode* cur = root;
    int cnt = 0;
    while (cur != nullptr)
    {
        cnt++;
        if (cur->value == target)
        {
            return cnt;
        }
        else if (cur->value > target)
        {
            cur = cur->left;
        }
        else
        {
            cur = cur->right;
        }
    }
    return cnt;
}

void AVLTree::insert(int target)
{
    if (root == nullptr) 
    {
        root = newNode(target, 1,1);
        return;
    }
    TreeNode* cur = root;
    stack<TreeNode*> S;
    while (cur != nullptr)
    {
        S.push(cur);
        if (cur->value == target)
        {
            cur->count++;
            S.empty();
            return;
        }
        else if (cur->value > target)
        {
            cur = cur->left;
        }
        else
        {
            cur = cur->right;
        }
    }
    if (S.top()->value > target) 
    {
        S.top()->left = newNode(target, 1, 1);
    }
    else 
    {
        S.top()->right = newNode(target, 1, 1);
    }
    while (!S.empty())
    {
        cur = S.top();
        S.pop();
        updateSTD(cur);
        fixTree(cur,target);
    }
}

void AVLTree::clear()
{
    TreeNode* c = root;
    stack<TreeNode*> S;
    while (c != NULL)
    {
        if (c->right != nullptr)
        {
            S.push(c->right);
        }
        S.push(c);
        c = c->left;
    }
    while (!S.empty())
    {
        c = S.top(); S.pop();
        if (!S.empty() && c->right == S.top())
        {
            TreeNode* t = S.top(); S.pop();
            S.push(c);
            c = t;
        }
        else
        {
            delNode(c);
            c = NULL;
        }
        while (c != NULL)
        {
            if (c->right != NULL)
            {
                S.push(c->right);
            }
            S.push(c);
            c = c->left;
        }
    }
    root = nullptr;
}

void AVLTree::print(int color)
{
    if (root == nullptr) { return; }
    int ds = mmax(mmax(dataSize(tmin()), dataSize(tmax()))+1,4);
    int bh = (root->STD * 3);
    int bw = pow(2, root->STD - 1)*ds;
    ScreenBuffer SB(bw, bh);

    queue<TreeNode*> NQ;
    queue<int> LQ;
    NQ.push(root);
    LQ.push(1);

    int fieldcount = 0;
    int llevel = 0;

    while (LQ.front() <= root->STD) 
    {
        TreeNode* cn = NQ.front(); NQ.pop();
        int lvl = LQ.front(); LQ.pop();
        if (lvl != llevel) { fieldcount = 0; }
        else { fieldcount++; }
        llevel = lvl;
        int fieldsize = bw/pow(2,lvl-1);
        int currline = (lvl-1)*3;
        if (cn != nullptr) 
        {
            SB.printCenteredInField(cn->value, fieldcount * fieldsize, currline, fieldsize);
            SB.printCenteredInFieldPh(cn->count, fieldcount * fieldsize, currline+1, fieldsize);
            SB.printBranch(cn->left != nullptr,cn->right!=nullptr, fieldcount * fieldsize, currline + 2, fieldsize);

            NQ.push(cn->left); NQ.push(cn->right);
            LQ.push(lvl + 1); LQ.push(lvl + 1);
        }
        else 
        {
            NQ.push(nullptr); NQ.push(nullptr);
            LQ.push(lvl + 1); LQ.push(lvl + 1);
        }
    }

    
    if (color==1) { SB.enableColor(); SB.rainbowBarf(); }
    if (color == 2) 
    {
        SB.clearScreen();
        cout << "\033[0;0H";
        SB.enableColor(); SB.rainbowBarf();
        for (int i = 0; i < 10; i++)
        {
            SB.printBuffer();
            SB.rainbowBarf();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            cout << "\033[0;0H";
        }
    }
    SB.printBuffer();
    SB.disableColor();
    if (ds > 4) 
    {
        cout <<endl<< "U stablu postoje podatci koji se ispisuju na sirini od vise od 4 karaktera, koristi se eksperimentalni ispis stabla" << endl;
    }
    if (bw > 80)
    {
        cout <<endl<< "Stablo je sire od 80 karakter-a, stablo ce takodje biti ispisano u fajl stablo.txt" << endl;
        SB.printToFile("stablo.txt");
    }
    SB.deleteBuffer();
}

int AVLTree::tmin()
{
    if (root == nullptr) { return 0; }
    TreeNode* c = root;
    int min;
    while (c != nullptr) 
    {
        min = c->value;
        c = c->left;
    }
    return min;
}

int AVLTree::tmax()
{
    if (root == nullptr) { return 0; }
    TreeNode* c = root;
    int max;
    while (c != nullptr)
    {
        max = c->value;
        c = c->right;
    }
    return max;
}

TreeNode* AVLTree::newNode(int val, int cnt, int t, TreeNode* l, TreeNode* r)
{
    TreeNode* p = new TreeNode;
    p->value = val;
    p->count = cnt;
    p->STD = t;
    p->left = l;
    p->right = r;
    return p;
}

void AVLTree::delNode(TreeNode* n)
{
    delete n;
}

void AVLTree::updateSTD(TreeNode* n)
{
    int lstd = n->left == nullptr ? 0 : n->left->STD;
    int rstd = n->right == nullptr ? 0 : n->right->STD;
    n->STD = 1 + mmax(lstd, rstd);
}

int AVLTree::balance(TreeNode* n)
{
    int lstd = n->left == nullptr ? 0 : n->left->STD;
    int rstd = n->right == nullptr ? 0 : n->right->STD;

    return lstd - rstd;
}

bool AVLTree::isCritical(TreeNode* n)
{
    return balance(n) > 1 || balance(n) < -1;
}

void AVLTree::fixTree(TreeNode* n,int t)
{
    if (isCritical(n)) 
    {
        int tbal = balance(n);
        int cbal = n->value > t ? balance(n->left) : balance(n->right);
        cbal = cbal == 0 ? balanceDir(tbal) : cbal;
        if (balanceDir(tbal) == balanceDir(cbal)) 
        {
            if (balanceDir(tbal) == 1) 
            {
                //rotr
                rotr(n);
            }
            else 
            {
                //rotl
                rotl(n);
            }
        }
        else
        {
            if (balanceDir(tbal) == 1)
            {
                //rotl
                rotl(n->left);
                //rotr
                rotr(n);
            }
            else
            {
                //rotr
                rotr(n->right);
                //rotl
                rotl(n);
            }
        }
    }
}

int AVLTree::balanceDir(int b)
{
    return b>=0?b==0?0:1:-1;
}

void AVLTree::rotl(TreeNode* n)
{
    int tv = n->value;
    int tc = n->count;
    n->value = n->right->value;
    n->count = n->right->count;
    n->right->value = tv;
    n->right->count = tc;

    TreeNode* A = n->right;
    TreeNode* C = A->right;
    A->right = A->left;
    A->left = n->left;
    n->left = A;
    n->right = C;
    updateSTD(A);
    updateSTD(n);
}

void AVLTree::rotr(TreeNode* n)
{
    int tv = n->value;
    int tc = n->count;
    n->value = n->left->value;
    n->count = n->left->count;
    n->left->value = tv;
    n->left->count = tc;

    TreeNode* A = n->left;
    TreeNode* C = A->left;
    A->left = A->right;
    A->right = n->right;
    n->right = A;
    n->left = C;
    updateSTD(A);
    updateSTD(n);
}
