
#include <iostream>

#include "AvlTree.h"
#include <assert.h>


using namespace std;

int main() {

    AvlTree<int,int> avl1;
    AvlTree<int,int> avl2;
    avl1.Insert(10,10);
    avl1.Insert(6,6);
    avl1.Insert(13,13);
    avl1.Insert(11,11);
    avl1.Insert(15,15);
    avl1.Insert(4,4);

    avl1.Insert(7,7);
    avl1.Insert(12,12);
  //  assert(is_tree_size_valid(avl1.root) == avl1.size);

    avl1.Insert(14,14);
    int range = rangeCount(avl1.root, 8, 16);
    auto *arr = new Pair<int,int>[range];
    limitedInorder(avl1.root, arr, 8, 16);
    for (int i = 0; i < range; ++i) {
        cout << "range: " << i <<"key:"<<arr[i].key << endl;

    }

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
