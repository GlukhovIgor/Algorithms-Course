// ALGOS.cpp: определяет точку входа для консольного приложения.
//

#include<iostream>
#include<fstream>
#include <queue>
#include<vector>
#include<algorithm>
#include<queue>
#include "edx-io.hpp"
using namespace std;

struct tree;
void printTree(tree*);

struct threes {
	int l;
	int r;
	int h;
	int k;
};
struct node {
	int k;
	int h;
	node* kids[2];
	node(threes* arr, int idx, int hgt) {
		k = arr[idx].k;
		kids[1] = nullptr;
		kids[0] = nullptr;
		h = hgt;
	}
	node(int key) {
		k = key;
		kids[1] = nullptr;
		kids[0] = nullptr;
		h = 0;
	}
};
int height(node* n) {
	return n ? n->h : -1;
}
int balancefact(node* n) {
	if (!n) {
		return 0;
	}
	return height(n->kids[1]) - height(n->kids[0]);
}
void fixheight(node* n) {
	int hl = height(n->kids[0]);
	int hr = height(n->kids[1]);
	n->h =(hl > hr ? hl : hr) + 1;
}
struct tree {
	node* root;
	vector<node*> nodes;
	tree() {
		root = nullptr;
	}
	tree(threes* arr, int& size) {
		root = new node(arr, 1, arr[1].h);
		nodes.reserve(size+1);
		nodes.push_back( root);
		for (int i = 1; i < size; i++) {
			nodes.push_back(new node(arr, i + 1, arr[i+1].h));
		}
		for (int i = 0; i < size; i++) {
			if (arr[i + 1].l != 0) {
				nodes[i]->kids[0] = nodes[arr[i + 1].l - 1];
			}
			if (arr[i + 1].r != 0) {
				nodes[i]->kids[1] = nodes[arr[i + 1].r - 1];
			}
		}
	}
	void makeOutTree(node* n, vector<threes>& outTree) {
		std::queue<node *> queue;
		queue.push(n);
		int num = 1;
		while (!queue.empty())
		{
			node *v = queue.front();
			queue.pop();
			int children_num[2] = { 0, 0 };
			for (int i = 0; i < 2; i++)
			{
				if (v->kids[i] != nullptr)
				{
					queue.push(v->kids[i]);
					children_num[i] = ++num;
				}
			}
			threes th;
			th.k = v->k;
			th.l = children_num[0];
			th.r = children_num[1];
			outTree.push_back(th);
		}
	}
	node* rotateLeft(node* a) {
		node* b = a->kids[1];
		a->kids[1] = b->kids[0];
		b->kids[0] = a;
		if (a == root) {
			root = b;
		}
		fixheight(a);
		fixheight(b);
		return b;
	}
	node* rotateRight(node* a) {
		node* b = a->kids[0];
		a->kids[0] = b->kids[1];
		b->kids[1] = a;
		fixheight(a);
		fixheight(b);
		if (a == root) {
			root = b;
		}
		return b;
	}
	/* void bigRotateLeft(node* a) {
		node* tmp = a;
		node* c = a->kids[1]->kids[0];
		//io << "before right" << "\n";
		//printTree(this);
		rotateRight(a->kids[1]);
		root->kids[1] = c;
		//io << "after right" << "\n";
		//printTree(this);
		rotateLeft(a);
		if (tmp == root) {
			root = c;
		}
	} */
	node* balance(node* n) {
		//io << "before balancing: \n";
		//printTree(this);
		fixheight(n);
		if (balancefact(n) == 2) {
			//io << "balance of " << n->k << " is 2" << "\n";
			if (balancefact(n->kids[1]) < 0) {
				//io << "balance of " << n->kids[1]->k << " is < 0" << "\n";
				n->kids[1] = rotateRight(n->kids[1]);
			}
			return rotateLeft(n);
		}
		if (balancefact(n) == -2) {
			//io << "balance of " << n->k << " is -2" << "\n";
			if (balancefact(n->kids[0]) > 0) {
				//io << "balance of " << n->kids[0]->k << " is > 0" << "\n";
				n->kids[0] = rotateLeft(n->kids[0]);
			}
			return rotateRight(n);
		}
		return n;
	}
	void addToNodes(int k) {
		nodes.push_back(new node(k));
	}
	node* insert(node* n, node* added) {
		if (!this->root) {
			this->root = added;
			return added;
		}
		//printTree(this);
		if (!n) {
			fixheight(added);
			return added;
		}
		if (added->k < n->k) {
			//io << "added as a left kid of" << n->k << "\n";
			n->kids[0] = insert(n->kids[0], added);
		}
		else {
			//io << "added as a right kid of" << n->k << "\n";
			n->kids[1] = insert(n->kids[1], added);
		}
		//printTree(this);
		//return n;
		return balance(n);
	}
	node* findmax(node* n) {
		return n->kids[1] == nullptr ? (n) : findmax(n->kids[1]);
	}

	node* remove(node* root, int key) {
		if (!root) {
			return nullptr;
		}
		if (key != root->k)
		{
			root->kids[key < root->k ? 0 : 1] = remove(root->kids[key < root->k ? 0 : 1], key);
		}
		else
		{
			if (root->kids[0] == nullptr && root->kids[1] == nullptr)
			{
				return nullptr;
			}
			if (root->kids[0] == nullptr)
			{
				root = root->kids[1];
				return balance(root);
			}
			node * r = findmax(root->kids[0]);
			root->k = r->k;
			root->kids[0] = remove(root->kids[0], r->k);
		}
		return balance(root);
	}
	node* search(node* root, int key) {
		if (!root) {
			return nullptr;
		}
		if (root->k == key) {
			return root;
		}
		if (root->k < key) {
			return search(root->kids[1], key);
		}
		return search(root->kids[0], key);
	}
};

void printTree(tree* myTree) {
	for (auto it : myTree->nodes) {
		io << it->k << " ";
		if (it->kids[0] == nullptr) {
			io << "NULL ";
		}
		else {
			io << it->kids[0]->k << " ";
		}
		if (it->kids[1] == nullptr) {
			io << "NULL ";
		}
		else {
			io << it->kids[1]->k << " ";
		}
		io << it->h << "\n";
	}
	io << "\n";
}
void printBalances(tree* myTree) {
	io << "Balances: \n";
	for (auto it : myTree->nodes) {
		io << it->k << " ";
		io << balancefact(it) << "\n" ;
	}
}
void findHeight(int j, int& n, threes* arr) {
	if (j == 0) {
		return;
	}
	if (arr[j].l == 0 && arr[j].r == 0) {
		arr[j].h = 0;
		return;
	}
	if (arr[j].l == 0) {
		findHeight(arr[j].r, n, arr);
		arr[j].h = arr[arr[j].r].h + 1;
		return;
	}
	if (arr[j].r == 0) {
		findHeight(arr[j].l, n, arr);
		arr[j].h = arr[arr[j].l].h + 1;
		return;
	}
	findHeight(arr[j].l, n, arr);
	findHeight(arr[j].r, n, arr);
	arr[j].h = max(arr[arr[j].l].h, arr[arr[j].r].h) + 1;
	return;
}
int main()
{
	int n;
	io >> n;
	tree* myTree = new tree();
	char c;
	int k;
	//threes* arr = new threes[n + 1];
	for (int i = 0; i < n; i++) {
		io >> c >> k;
		switch (c) {
		case 'A':
			if (!myTree->search(myTree->root, k)) {
				myTree->root = myTree->insert(myTree->root, new node(k));
			}
			io << balancefact(myTree->root) << "\n";
			break;
		case 'C':
			myTree->search(myTree->root, k)? io << "Y\n": io << "N\n";
			break;
		case 'D':
			if (myTree->search(myTree->root, k)) {
				myTree->root = myTree->remove(myTree->root, k);
			}
			io << balancefact(myTree->root) << "\n";
			break;
		}
	}
	return 0;
}

