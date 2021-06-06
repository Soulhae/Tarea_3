#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;

struct TreeNode {
    void* key;
    void * value;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    double (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}

TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->key = key;
    new->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(double (*lower_than) (void* key1, void* key2)) {
    TreeMap* new = (TreeMap*)malloc(sizeof(TreeMap));
    if (!new) return NULL;
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
	TreeNode* node;
	node = createTreeNode(key, value);
	if(!tree->root){
		tree->root = node;
		return;
	}
	TreeNode* aux = tree->root;
	while(aux){
		TreeNode* parent = aux;
		if(is_equal(tree, aux->key, key)==1)return;
		if(tree->lower_than(key,aux->key)==1)aux = aux->left;
		else aux = aux->right;
		if(!aux){
			node->parent = parent;
			if(tree->lower_than(key,parent->key)==1)parent->left = node;
			else parent->right = node;
		}
	}
	tree->current = node;
	aux = node;
}

TreeNode * minimum(TreeNode * x){
    while(x)
    {
      if(x->left)
        x = x->left;
      else break;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(!(node->left) && !(node->right)) // si no tiene hijos
  {
    if(node == node->parent->left)
      node->parent->left = NULL;
    else 
      node->parent->right = NULL;

    free(node);
  }
  else if (node->left && node->right) // si tiene 2 hijos
  {
    TreeNode* minimo = minimum(node->right);
    node->key = minimo->key;
    node->value = minimo->value;
    removeNode(tree, minimo);
  }
  else // si tiene 1 solo
  {
    if(node->left)
    {
      if(node == node->parent->left)
      {
        node->parent->left = node->left;
        node->left->parent = node->parent;
      }
      else
      {
        node->parent->right = node->left;
        node->left->parent = node->parent;
      }
    }
    else
    {
      if(node == node->parent->left)
      {
        node->parent->left = node->right;
        node->right->parent = node->parent;
      }
      else
      {
        node->parent->right = node->right;
        node->right->parent = node->parent;
      }
    }

    free(node);
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}


void * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode* aux = tree->root;

    while(aux)
    {
      if(is_equal(tree, aux->key, key) == 1)
      {
        tree->current = aux;
        return aux->value;
      }
      else if(tree->lower_than(key, aux->key) == 1) aux = aux->left;
      else aux = aux->right;
    }

    return NULL;
}
    


void * upperBound(TreeMap * tree, void* key) {
    TreeNode* aux = tree->root;
    TreeNode* ub_node = aux->right;

    while(aux)
    {
      if(is_equal(tree, aux->key, key) == 1)
      {
        ub_node = aux;
        break;
      }
      else
      {
        if(tree->lower_than(key, aux->key) == 1)
        {
          if(tree->lower_than(aux->key, ub_node->key) == 1) 
            ub_node = aux;
        }
        
        if(tree->lower_than(key, aux->key) == 1)
          aux = aux->left;
        else
          aux = aux->right;
      }
    }
    
    if(tree->lower_than(ub_node->key, key) == 1) return NULL;
    else return ub_node->value;
}

void * firstTreeMap(TreeMap * tree) {
  TreeNode* aux;
  aux = minimum(tree->root);
  tree->current = aux;
  return aux->value;
}

void * nextTreeMap(TreeMap * tree) {

  TreeNode *current = tree->current;
  if (current->right != NULL){
    current = current->right;
    current = minimum(current);
    tree->current = current;
    return tree->current->value;
  }

  TreeNode *parent = current->parent;
  while (parent != NULL){
    if( tree->lower_than(current->key,parent->key) != 1 )parent = parent->parent;
    else break;
  }

  if (current == NULL || parent == NULL) return NULL;
  tree->current = parent;
  return parent->value;

}