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
	node* kids[2];
	node(threes* arr, int idx) {
		k = arr[idx].k;
		kids[1] = nullptr;
		kids[0] = nullptr;
	}
};

struct tree {
	node* root;
	vector<node*> nodes;
	tree(threes* arr, int& size) {
		root = new node(arr, 1);
		nodes.reserve(size);
		nodes.push_back( root);
		for (int i = 1; i < size; i++) {
			nodes.push_back(new node(arr, i + 1));
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
	void rotateLeft(node* a) {
		node* b = a->kids[1];
		a->kids[1] = b->kids[0];
		b->kids[0] = a;
		if (a == root) {
			root = b;
		}
		//adjust heights of a and b
	}
	void rotateRight(node* a) {
		node* b = a->kids[0];
		a->kids[0] = b->kids[1];
		b->kids[1] = a;
		//adjust heights of a and b
		if (a == root) {
			root = b;
		}
	}
	void bigRotateLeft(node* a) {
		node* tmp = a;
		node* c = a->kids[1]->kids[0];
		//io << "before right" << "\n";
		//printTree(this);
		rotateRight(a->kids[1]);
		root->kids[1] = c;
		//io << "after right" << "\n";
		//printTree(this);
		rotateLeft(a);
		/*if (tmp == root) {
			root = c;
		}*/
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
		io << "\n";
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
	int l, r, k;
	threes* arr = new threes[n + 1];
	arr[0].l = -11;
	arr[0].r = -11;
	arr[0].h = -11;
	for (int i = 0; i < n; i++) {
		io >> k >> l >> r;
		arr[i + 1].l = l;
		arr[i + 1].r = r;
		arr[i + 1].h = -11;
		arr[i + 1].k = k;
	}
	findHeight(1, n, arr);
	tree* myTree = new tree(arr, n);
	int balance;
	if (arr[arr[1].r].r == 0 && arr[arr[1].r].l == 0) {
		balance = 0;
	}
	else if (arr[arr[1].r].l == 0) {
		balance = arr[arr[arr[1].r].r].h + 1;
	}
	else if (arr[arr[1].r].r == 0) {
		balance = -arr[arr[arr[1].r].l].h - 1;
	}
	else {
		balance = arr[arr[arr[1].r].r].h - arr[arr[arr[1].r].l].h;
	}
	
	//printTree(myTree);
	//io << "\n";

	if (balance == 0 || balance == 1) {
		myTree->rotateLeft(myTree->root);
	}
	if (balance == -1) {
		myTree->bigRotateLeft(myTree->root);
	}
	
	
	//printTree(myTree);
	//io << "Root:" << myTree->root->k << "\n";
	
	std::queue<node *> queue;
	queue.push(myTree->root);
	vector<threes> output_tree;
	output_tree.reserve(n);
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
		output_tree.push_back(th);
	}
	io << n << "\n";
	for (auto it: output_tree) {
	io << it.k << " " << it.l << " " << it.r << "\n";
	}
	//io << myTree->root->k;
	return 0;
}

