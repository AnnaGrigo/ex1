
#include <iostream>

#include "AvlTree.h"
#include <assert.h>




int main() {

    AvlTree<int,int> avl1;
    AvlTree<int,int> avl2;
    avl1.Insert(6,6);
    avl1.Insert(2,2);
    avl1.Insert(1,1);
    avl1.Insert(3,3);
    avl1.Insert(7,7);
    avl1.Insert(4,4);
    assert(is_tree_size_valid(avl1.root) == avl1.size);

    avl1.Insert(9,9);
    avl1.Insert(5,5);
    avl1.Insert(20,20);
    avl1.Insert(10,10);
    avl1.Insert(8,8);
    avl1.Insert(11,11);
    avl1.Insert(12,12);
    avl1.Insert(13,13);
    avl1.Insert(14,14);
    avl1.Insert(15,15);
    avl1.Insert(16,16);
    avl1.Insert(17,17);
    avl1.Insert(18,18);
    avl1.Insert(19,19);
    avl1.Delete(1);
    assert((is_tree_valid(avl1.root)) == true);
    assert(is_tree_size_valid(avl1.root) == avl1.size);
    int x = 5;


    /*int minkey = 3, maxkey = 8;
    Pair<int,int>* arr = new Pair<int,int>[maxkey-minkey +1];
    limitedInorder(avl1.root,arr,minkey,maxkey);
    for (int i = 0; i < maxkey - minkey +1; ++i) {
        std::cout << arr[i].key <<' ';
    }*/

    //int i = rangeCount(avl1.root,3,8);

    //std::cout<< i <<' ';


    return 0;
}
