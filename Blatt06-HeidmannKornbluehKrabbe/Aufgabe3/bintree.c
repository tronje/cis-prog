#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "bintree.h"

#define PARENT 0
#define CHILD 1

struct BinTreeNode {
  void *value;
  BinTreeNode *left,
              *right,
              *parent;
};

struct GenBinTree {
  BinTreeNode *t_root; 
  Cmpfunction cmp_node_value; /* pointer to compare function, returns
                                  < 0 if value1 < value2,
                                    0 if value1==value2 * and
                                  > 0 if value1 > value2 */
  Combinefunction combine_node_value; /* pointer to function that handles
                                         duplicate values */
  Freefunction free_node_value; /* pointer to Funktion that frees the contents
                                    of a node pointed to by value */
  unsigned long no_of_elements;
};

GenBinTree *gbt_new(Cmpfunction cmp_node_value,
                Combinefunction combine_node_value,
                Freefunction free_node_value)
{
    GenBinTree* newTree;
    BinTreeNode* newRoot;


    newTree = malloc(sizeof(GenBinTree));
    newRoot = malloc(sizeof(BinTreeNode));
    assert(newTree != NULL);
    assert(newRoot != NULL);
    newRoot -> value = NULL;
    newRoot -> left = NULL;
    newRoot -> right = NULL;
    newRoot -> parent  = NULL;
    newTree -> t_root = newRoot;
    newTree -> cmp_node_value = cmp_node_value;
    newTree -> combine_node_value = combine_node_value;
    newTree -> free_node_value = free_node_value;
    newTree -> no_of_elements = 0;
    return newTree;
}

bool gbt_add(GenBinTree *bintree, void *new_value)
{
  BinTreeNode* currentNode = bintree -> t_root;
  BinTreeNode* parentNode = bintree -> t_root;
  int cmpResult;
  int currentSide = 0;
  printf("newValue = %d\n",*new_value);

  if(bintree -> t_root -> value == NULL)
  {
  	bintree -> t_root -> value = new_value;
  	bintree -> no_of_elements++;
  	return true;
  }

  while(currentNode != NULL)
  {
  	cmpResult = bintree -> cmp_node_value(currentNode -> value,new_value);
    if(cmpResult < 0)
    {
      parentNode = currentNode;
      currentNode = currentNode -> left;
      currentSide = 0;
    }
    else if(cmpResult > 0)
    {
      parentNode = currentNode;
      currentNode = currentNode -> right;
      currentSide  = 1;
    }
    else
    {
      //printf("same value already in tree\n");
      return false;
    }
  }
  if(currentSide == 1)
  {
    parentNode -> right  = malloc(sizeof(BinTreeNode));
    assert(parentNode -> right != NULL);
  	parentNode -> right -> value = (void*)new_value;
  	parentNode -> right -> left = NULL;
  	if(parentNode -> right -> left == NULL) //printf("IS RICHTIG SO\n");
  	parentNode -> right -> right = NULL;
  	parentNode -> right -> parent = parentNode;
  	printf("VALUE of %p: %p\n",parentNode -> right,(int*)parentNode -> right -> value);

  }
  if(currentSide == 0)   
{
    parentNode -> left = malloc(sizeof(BinTreeNode));
    assert(parentNode -> left != NULL);
  	parentNode -> left -> value = new_value;
  	parentNode -> left -> left = NULL;
  	if(parentNode -> left -> left == NULL)// printf("IS RICHTIG SO\n");
  	parentNode -> left -> right = NULL;
  	parentNode -> left -> parent = parentNode;
  	  printf("VALUE: %p .\n",parentNode -> left -> value);

  }
  bintree -> no_of_elements++;

  return true;
}

void gbt_delete(GenBinTree *bintree)
{
  gbt_enumvalues(bintree,(void*)free,NULL);
  free(bintree);
}

void gbt_enumvalues(const GenBinTree *bintree, Applyfunction apply_node_value,
                    void* data)
{
	int runs = 0;
	int came_form = PARENT;
	unsigned elements_done = 0;
	BinTreeNode* currentNode = bintree -> t_root;
	// printf("size: %lu \n",(unsigned long)bintree -> t_root -> left );
			

	while(elements_done  < bintree -> no_of_elements)
	{
		// printf("nof: %lu \n",bintree -> no_of_elements );
		// printf("elements_done: %u \n",elements_done );
		// printf("runs: %d \n",runs );
		// printf("current node value: %p",currentNode -> value);
		
		if(currentNode -> left != NULL && came_form == PARENT)
		{
			//printf("if\n");
			currentNode = currentNode -> left;
			came_form = PARENT;
		}
		else if(currentNode -> right != NULL || came_form != PARENT)
		{
			// printf("elseif\n");
			apply_node_value(currentNode,data);
			elements_done++;
			came_form = PARENT;
			currentNode = currentNode -> right;
		}
		else
		{
			// printf("else\n");
			apply_node_value(currentNode,data);
			elements_done++;
			came_form = CHILD;
			currentNode = currentNode -> parent;
		}
		runs++;
	}

	
}