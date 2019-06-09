/*
 * b-search-tree 构建二叉搜索树
 *
 * tree-search(Tree, key)
 * tree-minimum(Tree)
 * tree-maximum(Tree)
 * tree-successor(Tree, Node)
 * tree-prodecessor(Tree, Node)
 * tree-insert(Tree, Node)
 * tree-delete(Tree, Node) 
 * transplant(Tree, Node, Node) //移动一个子树
 *
 * tree-free(Node)
 */


#pragma region include_header_files

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

#pragma endregion


#pragma region btree-func


typedef struct NodeList {
	struct NodeList* left;
	struct NodeList* right;
	struct NodeList* p;
	int val;
}*pNodeList;


typedef struct Tree {
	pNodeList root;
}*pTree;


//tree-search(Tree, key)
pNodeList tree_search(pTree tree, pNodeList node) {
	pNodeList tmp = tree->root;
	while (tmp) {
		if (tmp->val == node->val) {
			return tmp;
		}
		tmp = node->val < tmp->val ? tmp->left : tmp->right;
	}
	return NULL;
}


//tree_free(Tree, Node)

void tree_free(pTree tree, pNodeList node) {
	if (tree->root == node) {
		tree->root = NULL;
	}
	if (node->left)
		tree_free(tree, node->left);
	if (node->right)
		tree_free(tree, node->right);
	free(node);
}




// tree-minimum(Tree)

pNodeList tree_minimum(pTree tree) {
	pNodeList tmp = tree->root;
	if (tmp == NULL) return NULL;
	while (tmp->left)
		tmp = tmp->left;
	return tmp;
}

// tree-maximum(Tree)
pNodeList tree_maximum(pTree tree) {
	pNodeList tmp = tree->root;
	if (tmp == NULL) return NULL;
	while (tmp->right) {
		tmp = tmp->right;
	}
	return tmp;
}

// tree-successor(Tree, Node)
pNodeList tree_successor(pTree tree, pNodeList node) {
	pNodeList search_res = tree_search(tree, node);
	if(search_res == tree_maximum(tree)) return NULL;
	pNodeList ret_node;
	if(search_res->right == NULL){
		while(search_res->p && search_res->p->right == search_res){
			search_res = search_res->p;
		}
		ret_node = search_res->p;
	}
	else{
		ret_node = search_res->right;
		while(ret_node->left){
			ret_node = ret_node->left;
		}
	}
	return ret_node;
}

// tree-prodecessor(Tree, Node)
pNodeList tree_prodecessor(pTree tree, pNodeList node) {
	pNodeList search_res = tree_search(tree, node);
	pNodeList ret_node;
	if(search_res->left == NULL){
		while(search_res->p && search_res->p->left == search_res){
			search_res = search_res->p;
		}
		ret_node = search_res->p;
	}
	else{
		ret_node = search_res->left;
		while(ret_node->right){
			ret_node = ret_node->right;
		}
	}
	return ret_node;
}

// tree-insert(Tree, Node)

pNodeList tree_insert(pTree tree, pNodeList node) {
	if (tree->root == NULL) {
		tree->root = node;
		node->left = NULL;
		node->right = NULL;
		node->p = NULL;
		return node;
	}
	pNodeList tmp = tree->root;
	pNodeList p = NULL;
	while (tmp) {
		p = tmp;
		tmp = node->val < tmp->val ? tmp->left : tmp->right;
	}
	if (node->val < p->val) {
		p->left = node;
		node->p = p;
		node->left = NULL;
		node->right = NULL;
	}
	else {
		p->right = node;
		node->p = p;
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}

// tree-delete(Tree, Node)

pNodeList tree_delete(pTree tree, pNodeList node) {
	pNodeList search_res = tree_search(tree, node);
	if (search_res == NULL) return NULL;
	pNodeList successor = search_res;
	if (search_res->left == NULL && search_res->right == NULL) {
		if (tree->root == search_res) {
			tree->root = NULL;
		}
		else if (search_res->p->left == search_res) {
			search_res->p->left = NULL;
		}
		else if (search_res->p->right == search_res) {
			search_res->p->right = NULL;
		}
	}
	else if (search_res->left == NULL) {
		if (tree->root == search_res) {
			tree->root = search_res->right;
		}
		else if (search_res->p->left == search_res) {
			search_res->p->left = search_res->right;
			search_res->right->p = search_res->p;
		}
		else {
			search_res->p->right = search_res->right;
			search_res->right->p = search_res->p;
		}
	}
	else if (search_res->right == NULL) {
		if (tree->root == search_res) {
			tree->root = search_res->left;
		}
		else if (search_res->p->left == search_res) {
			search_res->p->left = search_res->left;
			search_res->left->p = search_res->p;
		}
		else {
			search_res->p->right = search_res->left;
			search_res->left->p = search_res->p;
		}
	}
	else {
		successor = tree_successor(tree, search_res);
		if (successor->p == search_res) {
			search_res->left = successor->left;
			search_res->val = successor->val;
			successor->left->p = search_res;
		}
		else {
			successor->p->right = successor->left;
			successor->left->p = successor->p;
			search_res->val = successor->val;
		}
		search_res = successor;
	}
	
	if (successor) {
		free(successor);
	}
	return search_res;
}


// transplant(Tree, Node, Node) //移动一个子树

pNodeList transplant(pTree tree, pNodeList remove_node, pNodeList insert_node) {
	pNodeList search_res = tree_search(tree, remove_node);
	if (search_res == NULL) return NULL;
	if (tree->root == search_res) {
		tree->root = insert_node;
		insert_node->p = NULL;
	}
	else if (search_res->p->left == search_res) {
		insert_node->p = search_res->p;
		search_res->p->left = insert_node;
	}
	else {
		insert_node->p = search_res->p;
		search_res->p->right = insert_node;
	}
	tree_free(tree, remove_node);
	return insert_node;
}


void in_order_travel(pNodeList node) {
	if (node == NULL) return;
	in_order_travel(node->left);
	printf("%d,", node->val);
	in_order_travel(node->right);
}

void print(int* arr, char* s) {
	printf("%s\n", s);
	for (int i = 0; i < 10; ++i) {
		printf("%d,", arr[i]);
	}
	printf("\n");
}

#pragma endregion


#pragma region test


int main(void) {
	int array[10] = { 0 };
	//srand(time(0));
	for (int i = 0; i < 10; ++i) {
		array[i] = rand() / (RAND_MAX / 100);
	}
	print(array, "before build btree is:");
	pTree tree = (pTree)malloc(sizeof(struct Tree));
	tree->root = NULL;
	for (int i = 0; i < 10; ++i) {
		pNodeList node = (pNodeList)malloc(sizeof(struct NodeList));
		node->left = NULL;
		node->p = NULL;
		node->right = NULL;
		node->val = array[i];
		tree_insert(tree, node);
	}
	printf("the root is:%d\n", tree->root->val);
	printf("after build the b-tree is(in order travel):\n");
	in_order_travel(tree->root);
	printf("\n");
	printf("tree-maximum is:%d\n", tree_maximum(tree)->val);
	printf("tree-minimum is:%d\n", tree_minimum(tree)->val);
	pNodeList remove_node = (pNodeList)malloc(sizeof(struct NodeList));
	memset(remove_node, 0, sizeof(struct NodeList));
	remove_node->val = 58;
	printf("the search remove_node(val:58) is:%d\n", tree_search(tree, remove_node)->val);
	printf("the remove_node(val:58) prodecessor is:%d\n", tree_prodecessor(tree, remove_node)->val);
	printf("the remove_node(val:58) successor is:%d\n", tree_successor(tree, remove_node)->val);
	tree_delete(tree, remove_node);
	printf("after remove the node->val = 58 is(in order travel):\n");
	in_order_travel(tree->root);
	printf("\n");

	for (int i = 0; i < 10; ++i) {
		array[i] = rand() / (RAND_MAX / 100) + 100;
	}
	print(array, "before build btree is:");
	pTree new_tree = (pTree)malloc(sizeof(struct Tree));
	new_tree->root = NULL;
	for (int i = 0; i < 10; ++i) {
		pNodeList node = (pNodeList)malloc(sizeof(struct NodeList));
		node->left = NULL;
		node->p = NULL;
		node->right = NULL;
		node->val = array[i];
		tree_insert(new_tree, node);
	}
	printf("the new_tree build is:\n");
	in_order_travel(new_tree->root);
	printf("\n");
	printf("after transplant is:\n");
	transplant(tree, tree->root->right, new_tree->root);
	in_order_travel(tree->root);
	printf("\n");
	tree_free(tree, tree->root);
	if (tree->root == NULL) {
		printf("tree-free success");
	}
	else {
		printf("tree-free failure");
	}
	return 0;
}


#pragma endregion
