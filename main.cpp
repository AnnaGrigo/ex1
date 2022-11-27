#include <iostream>


#include "AvlTree.h"




int main() {

    returnMessage message = returnMessage::SUCCESS;
    AvlTree<int,int> avl1;
    AvlTree<int,int> avl2;
    avl1.Insert(6,6);
    avl1.Insert(3,3);
    avl1.Insert(7,7);
    avl1.Insert(5,5);
    avl1.Insert(4,4);
    message = avl1.Delete(8);





    return 0;
}
