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
    int (*lower_than) (void* key1, void* key2);
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

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap* new = (TreeMap*)malloc(sizeof(TreeMap));
    if (!new) return NULL;
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode* aux = tree->root;

    if (!aux)
    {
      TreeNode* new = createTreeNode(key, value);
      tree->root = new;
    }

    while(aux)
    {
      if(is_equal(tree, aux->key, key) == 1) return;
      
      else if(tree->lower_than(key, aux->key) == 1)
      {
        if(aux->left != NULL) 
          aux = aux->left;
        else
        {
          TreeNode* new = createTreeNode(key, value);
          aux->left = new;
          new->parent = aux;
          tree->current = new;
          return;
        }
      } 
      else
      {
        if(aux->right != NULL)
          aux = aux->right;
        else
        {
          TreeNode* new = createTreeNode(key, value);
          aux->right = new;
          new->parent = aux;
          tree->current = new;
          return;
        }
      }
    }
  
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
    TreeNode* primero = minimum(tree->root);
    return primero->value;
}

void * nextTreeMap(TreeMap * tree) {
  if(tree->current->right)
    tree->current = minimum(tree->current->right);
  else
  {
    TreeNode* aux = tree->current;
    while(tree->current)
    {
      if (!tree->current->parent) return NULL;

      tree->current = tree->current->parent;
      if(tree->lower_than(aux->key, tree->current->key) == 1) break;
    }
  }

  return tree->current->value;
}
