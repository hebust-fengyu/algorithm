/*
 *
 * rb_tree 红黑树
 * 
 * rb-init(Tree)
 * rb-left-rotate(Tree, Node)
 * rb-right-rotate(Tree, Node)
 * rb-insert(Tree, Node)
 * rb-insert-fixup(Tree, Node)
 * rb-delete(Tree, Node)
 * rb-delete-fixup(Tree, Node)
 * rb-maximum(Tree) 
 * rb-minimum(Tree)
 * rb-successor(Tree, Node)
 * rb-predecessor(Tree, Node)
 * rb-transplant(Tree, Node, Node)
 * rb-search(Tree, Node)
 * rb-free(Tree, Node)
 * 
 * 
 */



#pragma region include_header_file

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#pragma endregion


#pragma region data_struct

typedef enum tag_color{
    red, black
}Color;

typedef struct NodeList{
    struct NodeList* p;
    struct NodeList* left;
    struct NodeList* right;
    int val;
    Color color;
}*pNodeList;


typedef struct Tree{
    pNodeList root;
    pNodeList nil;
}*pTree;


#pragma endregion



#pragma region declare_func

void rb_init(pTree);
void rb_left_rotate(pTree tree, pNodeList node);
void rb_right_rotate(pTree tree, pNodeList node);
void rb_insert_fixup(pTree tree, pNodeList node);
pNodeList rb_insert(pTree tree, pNodeList node);
void rb_delete_fixup(pTree tree, pNodeList node);
pNodeList rb_delete(pTree tree, pNodeList node);
pNodeList rb_maximum(pTree tree, pNodeList node);
pNodeList rb_minimum(pTree tree, pNodeList node);
pNodeList rb_successor(pTree tree, pNodeList node);
pNodeList rb_predecessor(pTree tree, pNodeList node);
pNodeList rb_transplant(pTree tree, pNodeList node);
pNodeList rb_search(pTree tree, pNodeList node);

#pragma endregion



#pragma region rb_tree_func



// * rb-free(Tree, Node)

void rb_free(pTree tree, pNodeList node){
    rb_free(tree, node->left);
    rb_free(tree, node->right);
    if(node != tree->nil){
        free(node);
    }
    if(tree->root == node){
        tree->root = tree->nil;
    }
}


// * rb-init(Tree)

void rb_init(pTree tree){
    tree->nil->val = 0;
    tree->nil->left = tree->nil->right = tree->nil;
    tree->root = tree->nil;
    tree->nil->color = black;
}


// * rb-left-rotate(Tree, Node)

void left_rotate(pTree tree, pNodeList node){
    pNodeList search_res = rb_search(tree, node);
    if(search_res == tree->nil) return;
    if(search_res->left == tree->nil && search_res->right == tree->nil){
        return;
    }
    else if(search_res->right == tree->nil){
        return;
    }
    else{
        if(search_res->p->left == search_res){
            search_res->right->p = search_res->p;
            search_res->p->left = search_res->right;
    
        }
        else{
            search_res->right->p = search_res->p;
            search_res->p->right = search_res->right;
        }
        search_res->p = search_res->right;
        search_res->right = search_res->p->left;
        search_res->right->p = search_res;
        search_res->p->left = search_res;        
    }
}



//* rb-right-rotate(Tree, Node)

void rb_right_rotate(pTree tree, pNodeList node){
    pNodeList search_res = rb_search(tree, node);
    if(search_res == tree->nil) return;
    if(search_res->left == tree->nil && search_res->right == tree->nil){
        return;
    }
    else if(search_res->left == tree->nil){
        return;
    }
    else{
        if(search_res->p->left == search_res){
            search_res->left->p = search_res->p;
            search_res->p->left = search_res->left;
    
        }
        else{
            search_res->left->p = search_res->p;
            search_res->p->right = search_res->left;
        }
        search_res->p = search_res->left;
        search_res->left = search_res->p->right;
        search_res->left->p = search_res;
        search_res->p->right = search_res;        
    }
}


// * rb-insert(Tree, Node)

pNodeList rb_insert(pTree tree, pNodeList node){
    node->color = red;
    node->left = node->right = tree->nil;
    if(tree->root == tree->nil){
        tree->root = node;
        node->p = tree->nil;
        node->color = black;
        return node;
    }
    pNodeList insert_node = tree->root;
    pNodeList parent_node;
    while(insert_node){
        parent_node = insert_node;
        insert_node = node->val < insert_node ? insert_node->left : insert_node->right;
    }
    node->val < parent_node->val ? parent_node->left = node : parent_node->right = node;
    node->p = parent_node;
    if(parent_node->color = red)
        rb_insert_fixup(tree, node);
} 

// * rb-insert-fixup(Tree, Node)

void rb_insert_fixup(pTree tree, pNodeList node){
    while(node->p->color == red){
        if(node->p->p->left == node->p){
            pNodeList ppr_node = node->p->p->right;
            if(ppr_node->color == red){
                ppr_node->color = black;
                node->p->color = black;
                node->p->p->color = red;
                node = node->p->p;
            }
            else if(node->p->right == node){
                rb_left_rotate(tree, node->p);
                node->color = black;
                node->p->color = red;
                rb_right_rotate(tree, node->p);
            }
            else{
                rb_right_rotate(tree, node->p->p);
            }
            
        }
        else{
            pNodeList ppl_node = node->p->p->left;
            if(ppl_node->color == red){
                ppl_node->color = black;
                node->p->color = black;
                node->p->p->color = red;
            }
            else if(node->p->left == node){
                rb_right_rotate(tree, node->p);
                node->color = black;
                node->p->color = red;
                rb_left_rotate(tree, node->p);
            }
            else{
                rb_left_rotate(tree, node->p);
            }
        }
    }
    T->root->color = black;
}

// * rb-delete(Tree, Node)

void rb_delte(pTree tree, pNodeList node){
    pNodeList search_res = rb_search(tree, node);
    pNodeList transplant, fixup_node;
    Color transplant_old_color;
    if(search_res->left == tree->nil && search_res->right == tree->nil){
        rb_free(tree, search_res);
    }
    else if(search_res->left == tree->nil){
        transplant = rb_successor(tree, search_res);
        transplant_old_color = transplant->color;
        if(transplant->p == search_res){
            rb_transplant(tree, search_res, transplant);
            fixup_node = transplant;
        }
        else{
            fixup_node = transplant->right;
            rb_transplant(tree, transplant, transplant->right);
            search_res->val = transplant->val;
        }
        rb_free(tree, transplant);
    }
    else{
        transplant = rb_predecessor(tree, search_res);
        transplant_old_color = transplant->color;
        if(transplant->p == search_res){
            rb_transplant(tree, search_res, transplant);
            fixup_node = transplant;
        }
        else{
            fixup_node = transplant->left;
            rb_transplant(tree, transplant, transplant->left);
            search_res->val = transplant->val;
        }
        rb_free(tree, transplant);
    }
    if(transplant_old_color == black)
        rb-delete-fixup(tree, fixup_node);
}


// * rb-delete-fixup(Tree, Node)

void rb_delte_fixup(pTree tree, pNodeList node){
            
}


// * rb-maximum(Tree) 

pNodeList rb_maximum(pTree tree){
    pNodeList max_ret = tree->root;
    while(max_ret->right != tree->nil){
        max_ret = max_ret->right;
    }
    return max_ret;
}


// * rb-minimum(Tree)

pNodeList rb_minimum(pTree tree){
    pNodeList min_ret = tree->root;
    while(min_ret->left != tree->nil){
        min_ret = min_ret->left;
    }    
    return min_ret;
}


// * rb-successor(Tree, Node)

pNodeList rb_successor(pTree tree, pNodeList node){
    pNodeList search_res = rb_search(tree, node);
    pNodeList max_ret = rb_maximum(tree);
    if(search_res->left == max_ret){
        search_res = search_res->right;
    }
    else if(search_res->right != tree->nil){
        search_res = search_res->right;
        while(search_res->left != tree->nil){
            search_res = search_res->left;
        }
    }
    else{
        while(search_res->p->right == search_res){
            search_res = search_res->p;
        }
        search_res = search_res->p;
    }
    return search_res;
}


// * rb-predecessor(Tree, Node)

pNodeList rb_predecessor(pTree tree, pNodeList node){
    pNodeList search_res = rb_search(tree, node);
    pNodeList min_node = rb_minimum(tree);
    if(search_res->val == min_node->val){
        search_res = search_res->left;
    }
    else if(search_res->left != tree->nil){
        search_res = search_res->left;
        while(search_res->right != tree->nil){
            search_res = search_res->right;
        }
    }
    else{
        while(search_res->p->left == search_res){
            search_res = search_res->p;
        }
        search_res = search_res->p;
    }
    return search_res;
}


// * rb-transplant(Tree, Node, Node)

pNodeList rb_transplant(pTree tree, pNodeList remove_node, pNodeList insert_node){

}

// * rb-search(Tree, Node)
pNodeList rb_search(pTree tree, pNodeList node){
    pNodeList ret_node = tree->root;
    while(ret_node != tree->nil){
        if(ret_node->val == node->val){
            return ret_node;
        }
        ret_node = node->val < ret_node->val ? ret_node->left : ret_node->right;
    }    
    return ret_node;
}


#pragma endregion



#pragma region test


int main(void){
    return 0;
}


#pragma endregion
