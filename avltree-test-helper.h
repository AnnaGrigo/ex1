/*
avl-test-helper.h
Copyright (c) Eromid (Olly) 2017

Friend of AvlTree class which contains functions only used in testing.
*/

#ifndef AVL_TEST_HELPER_H
#define AVL_TEST_HELPER_H

#include <algorithm>
#include <cmath>
#include <assert.h>
#include <memory>
#include "AvlTree.h"

using std::max;
using namespace std;

#include <iostream>
using std::cout;
using std::endl;

// A class template to test some of the internals of the AVL tree implementation.
// Is declared friend of AvlTree so has access to these.
template<typename K, typename V>
class test_helper
{
private:  
  test_helper() {} // instantiation not needed (or allowed)
public:

  // Count the total number of nodes in the tree.
  static unsigned int count_nodes(const AvlTree<K, V>& tree)
  {
    if (tree.root)
      return count_descendants(tree.root);
    else
      return 0u;
  }

  // Check the tree is AVL.
  static bool is_avl(const AvlTree<K, V>& tree)
  {
    return is_avl(tree.root);
  }

  // Check the tree's balance factors are correct.
  static bool valid_balance_factors(const AvlTree<K, V>& tree)
  {
    return valid_balance_factors(tree.root);
  }

  // Test the functions in this class.
  static void test_meta_functions()
  {
    {
      // Counting nodes
      AvlTree<int, double> tree;
      assert(count_nodes(tree) == 0);  // Empty tree should have 0 nodes.
      tree.Insert(1, 1.0);
      assert(count_nodes(tree) == 1);  // one node Inserted
      tree.Insert(1, 1.0);
      assert(count_nodes(tree) == 1);  // same node Inserted twice
      tree.Insert(2, 2.0);
      assert(count_nodes(tree) == 2);  // second unique node Inserted
      tree.Delete(3);
      assert(count_nodes(tree) == 2);  // non existent node Deleted
      tree.Delete(1);
      assert(count_nodes(tree) == 1);  // one node Deleted
      tree.Delete(2);
      assert(count_nodes(tree) == 0);
    }
    {
      // subtree height
      AvlTree<int, double> tree;
      assert(subtree_height(tree.root) == 0);  // root is null, height is 0.
      tree.Insert(5, 5.0);
      assert(subtree_height(tree.root) == 1);  // single node height should be 1.
      tree.Insert(8, 8.0);
      assert(subtree_height(tree.root) == 2);  // height should be 2; root has a single right child
      tree.Insert(3, 3.0);
      assert(subtree_height(tree.root) == 2);  // height should be 2; root has a left and right child
      tree.Insert(7, 7.0);
      assert(subtree_height(tree.root) == 3);  // height should be 2; root has a left and right child    
    }
  }

private:
  static bool is_avl(AvlNode<K,V> *root_node)
  {
    if (!root_node) return true;  // Base case; an empty tree is always AVL.
    bool left_is_avl, right_is_avl;
    int left_height, right_height;
    left_is_avl = is_avl(root_node->left_son);
    left_height = subtree_height(root_node->left_son);
    right_is_avl = is_avl(root_node->right_son);
    right_height = subtree_height(root_node->right_son);
    if (root_node->parent == nullptr)
    {
       { cout << "left subtree: " << left_height << " | right subtree: " << right_height << endl; }
       { cout << "left_is_avl: " << left_is_avl << " | right_is_avl: " << right_is_avl << endl; }
    }
    return left_is_avl && right_is_avl && (std::abs(left_height - right_height) <= 1u);
  }

  static bool valid_balance_factors(const AvlNode<K,V> *node)
  {
    if (!node) return true;
     { cout << "left_height: " << subtree_height(node->left_son) << " | right_height: "
         << subtree_height(node->right_son) << " | balance_factor: " << static_cast<int>(node->balance_factor) << endl; }
    return (subtree_height(node->left_son) - subtree_height(node->right_son) == node->balance_factor)
            && valid_balance_factors(node->left_son) && valid_balance_factors(node->right_son);
  }

  static unsigned int count_descendants(AvlNode<K,V> *node)
  {
    unsigned int left_count = node->left_son ? count_descendants(node->left_son) : 0;
    unsigned int right_count = node->right_son ? count_descendants(node->right_son) : 0;
    return 1u + left_count + right_count;
  }

  static unsigned int subtree_height(AvlNode<K,V> *node)
  {
    if (!node) return 0u;  // no subtree root -> height = 0.
    unsigned int left_height, right_height;
    left_height = right_height = 0u;
    left_height = subtree_height(node->left_son);
    right_height = subtree_height(node->right_son);
    return 1 + max(left_height, right_height);
  }
};

#endif
