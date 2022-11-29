
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
    avl1.Insert(5,5);
    avl1.Insert(4,4);

    Pair<int,int>* arr = new Pair<int,int>[4];

    arr = limitedInorder(avl1.root,arr,5,2);
    for (int i = 0; i < 4; ++i) {
        std::cout << arr[i].key <<' ';
    }



    return 0;
}
