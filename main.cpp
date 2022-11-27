#include <iostream>


#include "AvlTree.h"




int main() {

    AvlTree<int,int> avl1;
    AvlTree<int,int> avl2;
    avl1.Insert(6,6);
    avl1.Insert(3,3);
    avl1.Insert(7,7);
    avl1.Insert(5,5);
    avl1.Insert(4,4);
    avl2.Insert(2,2);
    avl2.Insert(10,10);
    avl2.Insert(8,8);
    avl2.Merge(avl1);
    avl2.Insert(1,1);




    return 0;
}
