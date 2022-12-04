
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
    avl2.Insert(5,5);
    avl2.Insert(4,4);
    avl2.Insert(20,20);
    avl2.Insert(10,10);
    avl2.Insert(8,8);
    avl2.Insert(9,9);
    avl1.Merge(avl2);
    int x =1;


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
