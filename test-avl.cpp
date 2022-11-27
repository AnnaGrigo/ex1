/*
optional.h
Copyright (c) Eromid (Olly) 2017

Unit tests for AVL tree implementation in AvlTree.h.
*/

#include <assert.h>
#include "AvlTree.h"
#include "avltree-test-helper.h"

#include <iostream>
using std::cout;
using std::endl;
using std::left;
using std::right;

#include <iomanip>
using std::setw;
using std::setfill;

using tests = test_helper<int, double>;

#define TEST_CASE(fn)\
cout << "================================================================================" << endl;\
cout << "    Running " << #fn << "...";                                                            \
fn();                                                                                              \
cout << " Complete. " << endl;                                                                     \
cout << "================================================================================" << endl;


// Run the tests inside the test-helper class template
void test_meta_functions()
{
  tests::test_meta_functions();
}

// Test empty tree behaves correctly
void test_empty_tree()
{
  AvlTree<int, double> tree;
  assert(tests::is_avl(tree));            // Tree should be an AVL tree
  assert(tests::count_nodes(tree) == 0);  // Empty tree should have 0 nodes.
  tree.Delete(123);                       // Removing non-existing key should have no effect.
  assert(tests::count_nodes(tree) == 0);  // Empty tree should still have 0 nodes.
  assert(tests::is_avl(tree));            // Tree should be an AVL tree still
  assert(is_tree_valid(tree.root)); // Are all balance factors correct (none)
}

// Test tree with only one node behaves correctly
void test_single_node()
{
  const double value = 42.0;
  const int key = 1;
  AvlTree<int, double> tree;
  tree.Insert(key, value);

  // After Insertion of single node:
  assert(tests::count_nodes(tree) == 1);      // Empty tree should have 0 nodes.
  assert(tests::is_avl(tree));                // Tree should be an AVL tree still
  tree.Delete(123);                           // Removing non-existing key should have no effect.
  assert(tests::count_nodes(tree) == 1);      // Tree should now have one node
  assert(tests::is_avl(tree));                // Tree should be an AVL tree still
  //assert(tree.Find(key).has_value() == true);  // query should return a value
  assert(tree.Find(key)->value == value);     // value should be what we put in
  assert(is_tree_valid(tree.root)); // Are all balance factors correct

  // after removing single node:
  tree.Delete(key);
  assert(tests::count_nodes(tree) == 0);      // Empty tree should still have 0 nodes.
  assert(tests::is_avl(tree));    
 // assert(tree.Find(key).has_value() == false);      // query should return a value
  assert(is_tree_valid(tree.root)); // Are all balance factors correct

}

// Test repeated right Insertions don't imbalance the tree
void test_multiple_right_Insertions()
{
  AvlTree<int, double> tree;
  const static int n_Insertions = 100;
  for (unsigned int i = 1; i <= n_Insertions; ++i)
  {
    tree.Insert(i, static_cast<double>(i));   // Insert increasing numbers
    assert(tests::is_avl(tree));              // check tree remains AVL
    assert(tests::count_nodes(tree) == i);          // Check the node made is in
    assert(is_tree_valid(tree.root)); // Are all balance factors correct
  }
  for (int i = 1; i < n_Insertions; ++i)
  {
   // assert(tree.Find(i).has_value() == true);  // query should return a value
    assert(tree.Find(i)->value == static_cast<double>(i));     // value should be what we put in
  }
}

// Test repeated left Insertions don't imbalance the tree
void test_multiple_left_Insertions()
{
  AvlTree<int, double> tree;
  const static int n_Insertions = 100;
  for (unsigned int i = n_Insertions; i >= 1; --i)
  {
    tree.Insert(i, static_cast<double>(i));   // Insert increasing numbers
    assert(tests::is_avl(tree));              // check tree remains AVL
    assert(tests::count_nodes(tree) == n_Insertions - (i -1));          // Check the node made is in
    assert(is_tree_valid(tree.root)); // Are all balance factors correct
  }
  for (int i = 1; i < n_Insertions; ++i)
  {
    //assert(tree.Find(i).has_value() == true);  // query should return a value
    assert(tree.Find(i)->value == static_cast<double>(i));     // value should be what we put in
  }
}

// Test that a right-left rotation correctly balances the tree
void test_right_left_rotation()
{
  AvlTree<int, double> tree;
  tree.Insert(10, 10.0);      // Root
  tree.Insert(20, 20.0);      // Right child of root
  tree.Insert(15, 15.0);      // left child of right child of root -> triggers RL rotation
  assert(tests::is_avl(tree));
  assert(is_tree_valid(tree.root));

}

// Test that a left-right rotation correctly balances the tree
void test_left_right_rotation()
{
  AvlTree<int, double> tree;
  tree.Insert(20, 20.0);        // Root node
  tree.Insert(10, 10.0);        // Left child
  tree.Insert(15, 15.0);        // Right child of left child -> triggers LR rotation
  assert(tests::is_avl(tree));
  assert(is_tree_valid(tree.root));
}

// Call all the above cases
int main()
{
  TEST_CASE(test_meta_functions);
  TEST_CASE(test_empty_tree);
  TEST_CASE(test_single_node);
  TEST_CASE(test_multiple_right_Insertions);
  TEST_CASE(test_multiple_left_Insertions);
  TEST_CASE(test_right_left_rotation);
  TEST_CASE(test_left_right_rotation);
  return 0;
}
