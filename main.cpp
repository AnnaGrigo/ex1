#include <iostream>


#include "AvlTree.h"




int main() {

    AvlTree<int,int> avl;
    avl.Insert(6,6);
    avl.Insert(3,3);
    avl.Insert(7,7);
    avl.Insert(5,5);
    avl.Insert(4,4);
    avl.Insert(2,2);
    avl.Insert(10,10);
    avl.Insert(8,8);
    avl.Delete(5);
    avl.Insert(5,5);




    return 0;
}
