
#include <iostream>

#include "AvlTree.h"

#include <assert.h>


int main() {

    AvlTree<int,int> avl1;
    AvlTree<int,int> avl2;
    avl1.Insert(6,6);
    avl1.Insert(2,2);
    avl1.Insert(1,1);
    avl2.Insert(3,3);
    avl2.Insert(7,7);
    avl2.Insert(5,5);
    avl2.Insert(4,4);
    avl1.Merge(avl2);
    assert(is_tree_valid(avl1.root)==1);
    int x = 5;
    //avl1.root->key = 6;
    //x = is_tree_valid(avl1.root);
    //assert(x==1);
    //message = avl1.Delete(8);





    return 0;
}
