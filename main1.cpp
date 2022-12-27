#include <iostream>
#include "AvlTree.h"
#include <ostream>
#include <assert.h>

int main1() {
    AvlTree<int,int> avl1;
    avl1.Insert(9  ,9);
    avl1.Insert(2  ,2);
    avl1.Insert(6,6);
    avl1.Insert(1,1);
    avl1.Insert(3,3);
    avl1.Insert(5,5);
    avl1.Insert(7,7);
    avl1.Insert(8,8);
    avl1.Insert(4,4);
    assert(is_tree_valid(avl1.root) == true);
    avl1.Delete(9);
    assert(is_tree_valid(avl1.root) == true);
    avl1.Delete(2);
    assert(is_tree_valid(avl1.root) == true);
    avl1.Delete(6);
    assert(is_tree_valid(avl1.root) == true);
    avl1.Delete(1);
    assert(is_tree_valid(avl1.root) == true);
    avl1.Delete(3);
    assert(is_tree_valid(avl1.root) == true);
    avl1.Delete(5);
    assert(is_tree_valid(avl1.root) == true);
    avl1.Delete(7);
    assert(is_tree_valid(avl1.root) == true);
    avl1.Delete(8);
    assert(is_tree_valid(avl1.root) == true);
    avl1.Delete(4);
    assert(is_tree_valid(avl1.root) == true);
    return 0;
}


/*
 * if(node->left_son){
            AvlNode<Key,Value>* maxLeftNode = findMaxNode(node->left_son);
            AvlNode<Key,Value>* maxLeftNodeParent = maxLeftNode->parent;
            if(maxLeftNode != node->left_son){
                if (maxLeftNode->left_son){
                    maxLeftNodeParent->parent->right_son = maxLeftNode->left_son;
                    maxLeftNode->left_son->parent = maxLeftNodeParent;
                }
                else maxLeftNodeParent->right_son = nullptr;
                maxLeftNode->left_son = node->left_son;
                node->left_son->parent = maxLeftNode;
            }
            if(node->right_son){
                maxLeftNode->right_son = node->right_son;
                node->right_son->parent = maxLeftNode;
            }
            maxLeftNode->parent = nodeParent;
            if(nodeParent){
                if (nodeParent->right_son == node){
                    nodeParent->right_son = maxLeftNode;
                }
                else
                    nodeParent->left_son = maxLeftNode;
            }
            maxLeftNode->parent = nodeParent;
            if(node == root){
                root = maxLeftNode;
                updateHeight(maxLeftNode);
            }
            delete node;
            --size;
        }
        else if(node->right_son){
            node->right_son->parent = nodeParent;
            if(nodeParent){
                if(nodeParent->left_son == node){
                    nodeParent->left_son = node->right_son;
                } else nodeParent->right_son = node->right_son;
            }
            if(node == root){
                root = node->right_son;
                updateHeight(node->right_son);
            }
            delete node;
            --size;
        }
        else{
            if(nodeParent){
                if(nodeParent->left_son == node){
                    nodeParent->left_son = nullptr;
                } else nodeParent->right_son = nullptr;
            }
            else(root = nullptr);
            delete node;
            --size;
        }
 */