
#ifndef RATUV1_AVLTREE_H
#define RATUV1_AVLTREE_H

#include <iostream>

template<class Key, class Value>
class AvlNode {
public:
    Key key;
    Value value;
    AvlNode<Key, Value> *right_son  ;
    AvlNode<Key, Value> *left_son;
    AvlNode<Key, Value> *parent;
    int height{};

    AvlNode(Key key, Value value)
            : key(key),
              value(value),
              right_son(nullptr),
              left_son(nullptr),
              parent(nullptr),
              height(0) {}

    AvlNode(AvlNode<Key, Value> &other) {
        this->key = other.key;
        this->value = other.value;
        this->right_son = other.right_son;
        this->left_son = other.left_son;
        this->parent = other.parent;
        this->height = other.height;
    }
    ~AvlNode() {
        delete right_son;
        delete left_son;
        delete parent;
    }

};

template <class Key, class Value>
class AvlTree {
    int size;
    AvlNode<Key, Value> *root;

    AvlTree();
    ~AvlTree();
    void DeleteTree(AvlNode<Key, Value> *node);
    int BF(AvlNode<Key, Value> *node) const;
    void RR(AvlNode<Key, Value> *node);
    void LL(AvlNode<Key, Value> *node);
    void RL(AvlNode<Key, Value> *node);
    void LR(AvlNode<Key, Value> *node);
    void Rotate(AvlNode<Key, Value> *node);
    int Insert(Key key, Value value);
    int Delete(Key key);
    AvlNode<Key, Value>* Find(Key key) const;
    void Merge(AvlTree<Key, Value> &second_tree);
};

// Constructor
template<class Key, class Value>
AvlTree<Key, Value>::AvlTree() {
    this->size = 0;
    this->root = nullptr;
}

// Destructor
template<class Key, class Value>
AvlTree<Key, Value>::~AvlTree() {
    if(root != nullptr) {
        DeleteTree(root);
    }

}

template<class Key, class Value>
void AvlTree<Key, Value>::DeleteTree(AvlNode<Key, Value> *node) {
    if(node == nullptr) {
        return;
    }
    DeleteTree(node->right);
    DeleteTree(node->left);
    delete node;
}

// Calculates Balance Factor
template<class Key, class Value>
int AvlTree<Key, Value>::BF(AvlNode<Key, Value> *node) const {
    if(node == nullptr) {
        return 0;
    }
    int Rheight = 0;
    int Lheight = 0;
    if(node->right_son != nullptr) {
        Rheight = node->right_son->height;
    }
    if(node->left_son != nullptr) {
        Lheight = node->left_son->height;
    }
    return Lheight - Rheight;
}

// Preforms Right Right rotation
template<class Key, class Value>
void AvlTree<Key, Value>::RR(AvlNode<Key, Value> *node) {
    AvlNode<Key,Value> *a;
    AvlNode<Key,Value> *b;
    a = node;
    b = a->right_son;
    b->left_son->parent = a;
    a->right_son = b->left_son;

    AvlNode<Key,Value> *a_parent = a->parent;
    if(a_parent != nullptr){
        if (a_parent->right_son == a)
            a_parent->right_son = b;
        else if (a_parent->left_son == a)
            a_parent->left_son = b;
    }
    b->left_son = a;
    a->parent = b;
}

// Preforms Left Left rotation
template<class Key, class Value>
void AvlTree<Key, Value>::LL(AvlNode<Key, Value> *node) {
    AvlNode<Key, Value> *a;
    AvlNode<Key, Value> *b;




}

// Preforms Right Left rotation
template<class Key, class Value>
void AvlTree<Key, Value>::RL(AvlNode<Key, Value> *node) {
    LL(node->right_son);
    RR(node);
}

// Preforms Left Right rotation
template<class Key, class Value>
void AvlTree<Key, Value>::LR(AvlNode<Key, Value> *node) {
    RR(node->left_son);
    LL(node);
}

// Preforms the rotation needed
template<class Key, class Value>
void AvlTree<Key, Value>::Rotate(AvlNode<Key, Value> *node) {
    int bf = BF(node);
    if(bf >= 2) {
        if(node->left_son->BF() >= 0) {
            LL();
        } else {
            LR();
        }
    } else if(bf <= -2) {
        if(node->right_son->BF() >= 0) {
            RL();
        } else {
            RR();
        }
    }
}


#endif //RATUV1_AVLTREE_H
