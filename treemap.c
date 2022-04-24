#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    void* key;
    void* value;
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
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap* map=(TreeMap*)malloc(sizeof(TreeMap*));
    map->lower_than = lower_than;
    return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode *current = tree->root;
  TreeNode *nodo = createTreeNode(key, value);
  while(current != NULL){
    if(is_equal(tree, current->key, key) == 1) break;

    if(current->left == NULL && current->right == NULL){
      if(tree->lower_than(key,current->key) == 1){
        current->left = nodo;
        current->left->parent = current;
      }
      if(tree->lower_than(current->key,key) == 1){
        current->right = nodo;
        current->right->parent = current;
      }
    }
    if(tree->lower_than(key, current->key) == 1){
      current = current->left;
      tree->current=current;
    }
    if(tree->lower_than(current->key, key) == 1){
      current=current->right;
      tree->current=current;
    }
  }
}

TreeNode * minimum(TreeNode * x){
  while(x->left != NULL){
    x=x->left;
  }
    return x;                                                                      
}

void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode*aux = tree->root;
  while(aux != NULL){
    if(tree->lower_than(key,aux->pair->key)==1){
      aux = aux->left;
      }else if(tree->lower_than(aux->pair->key,key)==1){
      aux=aux->right;
      }else{
      tree->current=aux;
        return aux->pair;
      }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
  TreeNode *auxi = tree->root;
   if(auxi == NULL){
     return NULL;
     }
  while(auxi != NULL){
      if(tree->lower_than(key, auxi->key) == 1){
        auxi = auxi->left;
      }
      if(tree->lower_than(auxi->key, key) == 1){
        auxi=auxi->right;
      }else break;
  }
    return auxi->value;
  }

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode*aux1=minimum(tree->root);
    return aux1->value;
  }
 

Pair * nextTreeMap(TreeMap * tree) {
  if(tree==NULL){
    return NULL;
  }
  TreeNode*rama;
  if(tree->current->right != NULL){
    rama=tree->current->right;
    tree->current = minimum(rama);
    return tree->current->value;
  }
  TreeNode* aux;
  aux=tree->current->parent;
  while(aux != NULL && tree->current == aux->right){
    tree->current=aux;
    aux=aux->parent;
  }
  tree->current=aux;
  if(tree->current == NULL){
    return NULL;
  }
  return tree->current->value;
  }
