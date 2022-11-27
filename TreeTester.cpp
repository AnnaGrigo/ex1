#include <iostream>
#include "AvlTree.h"
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <memory>
int BalanceFactor(AvlNode<int, int> *node){
    if (node == nullptr) {
        return 0;
    }
    int Rheight = -1;
    int Lheight = -1;
    if (node->right_son != nullptr) {
        Rheight = node->right_son->height;
    }
    if (node->left_son != nullptr) {
        Lheight = node->left_son->height;
    }
    return Lheight - Rheight;
}

void printTree(AvlNode<int,int> * root) {
    std::cout.flush();
    if(root== nullptr)
        return;
    
    printTree(root->left_son);
    std::cout<<root->key;
    std::cout<<" BF: "<< BalanceFactor(root) <<" Height: "<<root->height-1<<std::endl;
    printTree(root->right_son);
}
void print2DUtil(AvlNode<int,int> *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right_son child first
    print2DUtil(root->right_son, space);

    // Print current node after space
    // count
    std::cout<<std::endl;
    for (int i = 10; i < space; i++)
        std::cout<<" ";
    std::cout<<root->value<<"\n";

    // Process left_son child
    print2DUtil(root->left_son, space);
}

// Wrapper over print2DUtil()
void print2D(AvlNode<int,int> *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

}
int main1(){
    AvlTree<int,int> tree;

    //Specific Cases

    /*correct output for the four next cases
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0 */

    //basic LL root change
    tree.Insert(3,3);
    tree.Insert(2,2);
    tree.Insert(1,1);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;
    //basic LR root change
    tree.Insert(3,3);
    tree.Insert(1,1);
    tree.Insert(2,2);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //basic RR root change
    tree.Insert(1,1);
    tree.Insert(2,2);
    tree.Insert(3,3);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //basic RL root change
    tree.Insert(1,1);
    tree.Insert(3,3);
    tree.Insert(2,2);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //basic LR not root change
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    4 BF: 1 Height: 2
    5 BF: 0 Height: 0
    6 BF: 1 Height: 3
    7 BF: 0 Height: 0
    8 BF: 1 Height: 1 */
    tree.Insert(6,6);
    tree.Insert(4,4);
    tree.Insert(8,8);
    tree.Insert(3,3);
    tree.Insert(5,5);
    tree.Insert(7,7);
    tree.Insert(1,1);
    tree.Insert(2,2);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //basic LL not root change
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    4 BF: 1 Height: 2
    5 BF: 0 Height: 0
    6 BF: 1 Height: 3
    7 BF: 0 Height: 0
    8 BF: 1 Height: 1 */
    tree.Insert(6,6);
    tree.Insert(4,4);
    tree.Insert(8,8);
    tree.Insert(3,3);
    tree.Insert(5,5);
    tree.Insert(7,7);
    tree.Insert(2,2);
    tree.Insert(1,1);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //basic RR not root change
    /*correct output
     * 1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    5 BF: 1 Height: 2
    7 BF: 0 Height: 0*/
    tree.Insert(5,5);
    tree.Insert(7,7);
    tree.Insert(1,1);
    tree.Insert(2,2);
    tree.Insert(3,3);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //basic RL not root change
    /*correct output
     * 1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    5 BF: 1 Height: 2
    7 BF: 0 Height: 0*/
    tree.Insert(5,5);
    tree.Insert(7,7);
    tree.Insert(1,1);
    tree.Insert(3,3);
    tree.Insert(2,2);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //root deletion no roll successor is a neighbour
    /*correct output
    2 BF: 0 Height: 0
    3 BF: 1 Height: 1
    5 BF: 1 Height: 2
    6 BF: 0 Height: 0*/
    tree.Insert(4,4);
    tree.Insert(5,5);
    tree.Insert(3,3);
    tree.Insert(2,2);
    tree.Insert(6,6);
    tree.Delete(4);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //root deletion no roll successor is not a neighbour
    /*correct output
    2 BF: 0 Height: 0
    3 BF: 1 Height: 1
    5 BF: 0 Height: 2
    6 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0 */
    tree.Insert(4,4);
    tree.Insert(3,3);
    tree.Insert(7,7);
    tree.Insert(2,2);
    tree.Insert(5,5);
    tree.Insert(8,8);
    tree.Insert(6,6);
    tree.Delete(4);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //node deletion no roll successor is a neighbour case7
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 1 Height: 1
    4 BF: 1 Height: 2
    5 BF: 0 Height: 0
    7 BF: 1 Height: 3
    8 BF: -1 Height: 1
    9 BF: 0 Height: 0*/
    tree.Insert(7,7);
    tree.Insert(3,3);
    tree.Insert(8,8);
    tree.Insert(2,2);
    tree.Insert(4,4);
    tree.Insert(9,9);
    tree.Insert(5,5);
    tree.Insert(1,1);
    tree.Delete(3);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //node deletion no roll successor is not a neighbour case8
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 1 Height: 1
    5 BF: 0 Height: 2
    6 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0
    9 BF: 0 Height: 3
    10 BF: 0 Height: 0
    12 BF: -1 Height: 2
    13 BF: -1 Height: 1
    14 BF: 0 Height: 0*/
    tree.Insert(9,9);
    tree.Insert(3,3);
    tree.Insert(12,12);
    tree.Insert(2,2);
    tree.Insert(7,7);
    tree.Insert(10,10);
    tree.Insert(13,13);
    tree.Insert(1,1);
    tree.Insert(5,5);
    tree.Insert(8,8);
    tree.Insert(14,14);
    tree.Insert(6,6);
    tree.Delete(3);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //node deletion causing LR case9
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    4 BF: 0 Height: 2
    7 BF: -1 Height: 1
    8 BF: 0 Height: 0*/
    tree.Insert(7,7);
    tree.Insert(2,2);
    tree.Insert(8,8);
    tree.Insert(1,1);
    tree.Insert(4,4);
    tree.Insert(9,9);
    tree.Insert(3,3);
    tree.Delete(9);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //node deletion causing LL case10
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 1 Height: 1
    3 BF: 0 Height: 2
    4 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0*/
    tree.Insert(7,7);
    tree.Insert(3,3);
    tree.Insert(8,8);
    tree.Insert(2,2);
    tree.Insert(4,4);
    tree.Insert(9,9);
    tree.Insert(1,1);
    tree.Delete(9);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //node deletion causing RR case11
    /*correct output
    2 BF: 0 Height: 0
    3 BF: 0 Height: 1
    7 BF: 0 Height: 0
    8 BF: 0 Height: 2
    9 BF: -1 Height: 1
    10 BF: 0 Height: 0*/
    tree.Insert(3,3);
    tree.Insert(2,2);
    tree.Insert(8,8);
    tree.Insert(7,7);
    tree.Insert(1,1);
    tree.Insert(9,9);
    tree.Insert(10,10);
    tree.Delete(1);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //node deletion causing RL case12
    /*correct output
    * 2 BF: 0 Height: 0
    3 BF: 1 Height: 1
    7 BF: 0 Height: 2
    10 BF: 0 Height: 0
    13 BF: 0 Height: 1
    14 BF: 0 Height: 0*/
    tree.Insert(3,3);
    tree.Insert(2,2);
    tree.Insert(13,13);
    tree.Insert(7,7);
    tree.Insert(1,1);
    tree.Insert(14,14);
    tree.Insert(10,10);
    tree.Delete(1);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //double rotations RL and RR case 13
    /*correct output
    3 BF: 0 Height: 0
    5 BF: 0 Height: 1
    7 BF: 0 Height: 0
    9 BF: 0 Height: 2
    11 BF: 0 Height: 0
    13 BF: 1 Height: 1
    15 BF: 0 Height: 3
    17 BF: 0 Height: 0
    19 BF: -1 Height: 2
    21 BF: -1 Height: 1
    23 BF: 0 Height: 0*/
    tree.Insert(9,9);
    tree.Insert(3,3);
    tree.Insert(15,15);
    tree.Insert(1,1);
    tree.Insert(7,7);
    tree.Insert(13,13);
    tree.Insert(19,19);
    tree.Insert(5,5);
    tree.Insert(11,11);
    tree.Insert(17,17);
    tree.Insert(21,21);
    tree.Insert(23,23);
    tree.Delete(1);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //double rotations RR and RR case 14
    /*correct output
    3 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0
    9 BF: 0 Height: 2
    11 BF: 0 Height: 0
    13 BF: 1 Height: 1
    15 BF: 0 Height: 3
    17 BF: 0 Height: 0
    19 BF: -1 Height: 2
    21 BF: -1 Height: 1
    23 BF: 0 Height: 0*/
    tree.Insert(9,9);
    tree.Insert(3,3);
    tree.Insert(15,15);
    tree.Insert(1,1);
    tree.Insert(7,7);
    tree.Insert(13,13);
    tree.Insert(19,19);
    tree.Insert(8,8);
    tree.Insert(11,11);
    tree.Insert(17,17);
    tree.Insert(21,21);
    tree.Insert(23,23);
    tree.Delete(1);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //double rotations RL and LL case 15
    /*correct output
    6 BF: 0 Height: 0
    7 BF: 1 Height: 1
    8 BF: 1 Height: 2
    9 BF: 0 Height: 0
    10 BF: 0 Height: 3
    11 BF: -1 Height: 1
    12 BF: 0 Height: 0
    15 BF: 0 Height: 2
    17 BF: 0 Height: 0
    18 BF: 0 Height: 1
    20 BF: 0 Height: 0
     */
    tree.Insert(15,15);
    tree.Insert(10,10);
    tree.Insert(20,20);
    tree.Insert(8,8);
    tree.Insert(11,11);
    tree.Insert(17,17);
    tree.Insert(21,21);
    tree.Insert(7,7);
    tree.Insert(9,9);
    tree.Insert(12,12);
    tree.Insert(18,18);
    tree.Insert(6,6);
    tree.Delete(21);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //double rotations LR and LL case 16
    /*correct output
    6 BF: 0 Height: 0
    7 BF: 1 Height: 1
    8 BF: 1 Height: 2
    9 BF: 0 Height: 0
    10 BF: 0 Height: 3
    11 BF: -1 Height: 1
    12 BF: 0 Height: 0
    15 BF: 0 Height: 2
    20 BF: 0 Height: 0
    21 BF: 0 Height: 1
    22 BF: 0 Height: 0 */
    tree.Insert(15,15);
    tree.Insert(10,10);
    tree.Insert(20,20);
    tree.Insert(8,8);
    tree.Insert(11,11);
    tree.Insert(17,17);
    tree.Insert(22,22);
    tree.Insert(7,7);
    tree.Insert(9,9);
    tree.Insert(12,12);
    tree.Insert(21,21);
    tree.Insert(6,6);
    tree.Delete(17);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //delete node cause LR
    /*correct output
     * 2 BF: 0 Height: 0
    3 BF: -1 Height: 2
    4 BF: 0 Height: 0
    6 BF: 1 Height: 1*/

    tree.Insert(5,5);
    tree.Insert(3,3);
    tree.Insert(6,6);
    tree.Insert(2,2);
    tree.Insert(4,4);
    tree.Delete(5);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    //delete node cause LR
    /*correct output
     * 2 BF: 0 Height: 0
    3 BF: 0 Height: 1
    6 BF: 0 Height: 0*/
    tree.Insert(5,5);
    tree.Insert(3,3);
    tree.Insert(6,6);
    tree.Insert(2,2);
    tree.Delete(5);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.DeleteTree(tree.root);
    tree.root= nullptr;

    tree.Insert(3,3);
    tree.Insert(6,6);
    print2D(tree.root);
    tree.Insert(2,2);
    print2D(tree.root);
    tree.Insert(5,5);
    print2D(tree.root);
    tree.Insert(7,7);
    print2D(tree.root);
    tree.Insert(4,4);
    print2D(tree.root);
    tree.Insert(9,9);
    print2D(tree.root);
    tree.Insert(1,1);
    print2D(tree.root);
    tree.Insert(8,8);
    print2D(tree.root);
    tree.Delete(3);
    print2D(tree.root);
    tree.Delete(6);
    print2D(tree.root);
    tree.Delete(2);
    print2D(tree.root);
    tree.Delete(5);
    print2D(tree.root);
    tree.Delete(7);
    print2D(tree.root);
    tree.Delete(4);
    print2D(tree.root);
    std::vector<int> vector;
    for (int i=1; i<100; i++) vector.push_back(i);


    for (int k = 0; k <= 0; ++k) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); it++){
            tree.Insert(*it,*it);

        }
        //shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            print2D(tree.root);
            tree.Delete(*it);

        }
        std::cout<<std::endl;
        tree.DeleteTree(tree.root);
        tree.root= nullptr;
        std::cout<<std::endl;
        std::cout << '\n';
    }

    return 0;
}