
#ifndef RATUV1_AVLTREE_H
#define RATUV1_AVLTREE_H

#include <iostream>

enum class returnMessage{
    ALLOCATION_ERROR, INVALID_INPUT, FAILURE, SUCCESS
};

template<class Key, class Value>
class AvlNode {
public:
    Key key;
    Value value;
    AvlNode* right_son;
    AvlNode* left_son;
    AvlNode* parent;
    int height;

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

    ~AvlNode() = default;


};


template<class Key, class Value>
class AvlTree {
public:
    int size;
    AvlNode<Key, Value>* root;
public:
    AvlTree();
    ~AvlTree();
    void DeleteTree(AvlNode<Key, Value> *node);
    int BF(AvlNode<Key, Value> *node) const;
    AvlNode<Key, Value>* RR(AvlNode<Key, Value> *node);
    AvlNode<Key, Value>* LL(AvlNode<Key, Value> *node);
    AvlNode<Key, Value>* RL(AvlNode<Key, Value> *node);
    AvlNode<Key, Value>* LR(AvlNode<Key, Value> *node);
    AvlNode<Key, Value>* Rotate(AvlNode<Key, Value> *node);
    returnMessage Insert(Key key, Value value);
    returnMessage InsertNode(AvlNode<Key, Value> *root, AvlNode<Key, Value> *parent, AvlNode<Key, Value> *toInsert);
    returnMessage deleteNode(AvlNode<Key, Value>* node,AvlNode<Key, Value>* nodeParent, Key id);
    returnMessage Delete(Key key);
        AvlNode<Key, Value> *Find(Key key) const;
    void Merge(AvlTree<Key, Value> &second_tree);


};

// Constructor
template<class Key, class Value>
AvlTree<Key, Value>::AvlTree() : size(0),root(nullptr){}

// Destructor
template<class Key, class Value>
AvlTree<Key, Value>::~AvlTree() {
    if (root != nullptr) {
        DeleteTree(root);
    }

}

template<class Key, class Value>
void AvlTree<Key, Value>::DeleteTree(AvlNode<Key, Value> *node) {
    if (node == nullptr) {
        return;
    }
    DeleteTree(node->right_son);
    DeleteTree(node->left_son);
    delete node;
}

//updates a nodes height
template<class Key, class Value>
void updateHeight(AvlNode<Key, Value> *node){
    int Rheight = 0;
    int Lheight = 0;
    if (node->right_son != nullptr) {
        Rheight = node->right_son->height;
    }
    if (node->left_son != nullptr) {
            Lheight = node->left_son->height;
    }
    if(!node->left_son && !node->right_son)
    {
        node->height = 0;
    } else{
        node->height = 1 + (std::max(Rheight,Lheight));
    }
}


// Calculates Balance Factor
template<class Key, class Value>
int AvlTree<Key, Value>::BF(AvlNode<Key, Value> *node) const {
    if (node == nullptr) {
        return 0;
    }
    int Rheight = 0;
    int Lheight = 0;
    if (node->right_son != nullptr) {
        Rheight = node->right_son->height;
    } else
        Rheight = -1;
    if (node->left_son != nullptr) {
        Lheight = node->left_son->height;
    } else
        Lheight = -1;
    return Lheight - Rheight;
}

// Preforms Right Right rotation
template<class Key, class Value>
AvlNode<Key, Value>* AvlTree<Key, Value>::RR(AvlNode<Key, Value> *node) {
    AvlNode<Key, Value> *a;
    AvlNode<Key, Value> *b;
    a = node;
    b = a->right_son;
    a->right_son = b->left_son;
    if(b->left_son){
        b->left_son->parent = a;
    }
    AvlNode<Key, Value> *a_parent = a->parent;
    if (a_parent) {
        if (a_parent->right_son == a)
            a_parent->right_son = b;
        else if (a_parent->left_son == a)
            a_parent->left_son = b;
    }
    b->parent = a_parent;
    b->left_son = a;
    a->parent = b;
    updateHeight(a);
    updateHeight(b);
    if(root == node){
        root = b;
    }
    return b;
}

// Preforms Left Left rotation
template<class Key, class Value>
AvlNode<Key, Value>* AvlTree<Key, Value>::LL(AvlNode<Key, Value> *node) {
    AvlNode<Key, Value> *a;
    AvlNode<Key, Value> *b;
    a = node;
    b = a->left_son;
    a->left_son = b->right_son;
    if(b->right_son){
        b->right_son->parent = a;
    }
    AvlNode<Key, Value> *a_parent = a->parent;
    if (a_parent) {
        if (a_parent->right_son == a)
            a_parent->right_son = b;
        else if (a_parent->left_son == a)
            a_parent->left_son = b;
    }
    b->parent = a_parent;
    b->right_son = a;
    a->parent = b;
    updateHeight(a);
    updateHeight(b);
    if(root == node){
        root = b;
    }
    return b;
}

// Preforms Right Left rotation
template<class Key, class Value>
AvlNode<Key, Value>* AvlTree<Key, Value>::RL(AvlNode<Key, Value> *node) {
    node->right_son = LL(node->right_son);
    return RR(node);
}

// Preforms Left Right rotation
template<class Key, class Value>
AvlNode<Key, Value>* AvlTree<Key, Value>::LR(AvlNode<Key, Value> *node) {
    node->left_son = RR(node->left_son);
    return LL(node);
}

// Preforms the rotation needed
template<class Key, class Value>
AvlNode<Key, Value>* AvlTree<Key, Value>::Rotate(AvlNode<Key, Value> *node) {
    int bf = BF(node);
    if (bf >= 2) {
        if (BF(node->left_son) >= 0) {
           return LL(node);
        } else {
           return LR(node);
        }
    }
    else if (bf <= -2) {
        if (BF(node->right_son) > 0) {
           return RL(node);
        } else {
           return RR(node);
        }
    }
    else return node;
}

template<class Key, class Value>
returnMessage AvlTree<Key, Value>::Insert(Key key, Value value) {
    auto* node =  new AvlNode<Key, Value>(key,value);
    if(!root){
        root = node;
        size++;
        return returnMessage::SUCCESS;
    } else{
        return InsertNode(root, nullptr,node);
    }
}

template<class Key, class Value>
returnMessage
AvlTree<Key, Value>::InsertNode(AvlNode<Key, Value> *rootNode, AvlNode<Key, Value> *newParent, AvlNode<Key, Value> *toInsert) {
    if (!rootNode){
        rootNode = toInsert;
        rootNode->parent = newParent;
        if (newParent){
            if(newParent->key > toInsert->key){
                newParent->left_son = rootNode;
            } else newParent->right_son = rootNode;
        }
        size++;
    }
    else if(rootNode->key == toInsert->key){
        return returnMessage::FAILURE;

    }
    else if(rootNode->key > toInsert->key){
        InsertNode(rootNode->left_son,rootNode,toInsert);
    }
    else if(rootNode->key < toInsert->key){
        InsertNode(rootNode->right_son,rootNode,toInsert);
    }
    int rHeight = 0, lHeight = 0;
    if(newParent){
        if(newParent->right_son)
            rHeight = newParent->right_son->height;
        if(newParent->left_son)
            lHeight = newParent->left_son->height;
        newParent->height = (1 + std::max(rHeight, lHeight));
        this->Rotate(newParent);
    }
    return returnMessage::SUCCESS;
}

template<class Key, class Value>
AvlNode<Key, Value>* findMinNode (AvlNode<Key,Value>* root) {
    AvlNode<Key, Value> *node = root;
    while (node->left_son != nullptr)
    {
        node = node->left_son;
    }
    return node;
}

template<class Key, class Value>
AvlNode<Key, Value>* findMaxNode (AvlNode<Key,Value>* root) {
    AvlNode<Key, Value> *node = root;
    while (node->right_son != nullptr)
    {
        node = node->right_son;
    }
    return node;
}

template<class Key, class Value>
returnMessage AvlTree<Key, Value>::Delete(Key key) {
    return deleteNode(root, nullptr, key);
}

template<class Key, class Value>
returnMessage AvlTree<Key, Value>::deleteNode(AvlNode<Key, Value>* node ,AvlNode<Key, Value>* nodeParent, Key id){
    if(!node){
        return returnMessage::FAILURE;
    }
    if (node->key > id){
        deleteNode(node->left_son, node,id);
    }
    else if (node->key < id){
        deleteNode(node->right_son, node, id);
    }
    if(node->key == id){
        if(node->left_son){
            AvlNode<Key,Value>* maxLeftNode = findMaxNode(node->left_son);
            AvlNode<Key,Value>* maxLeftNodeParent = maxLeftNode->parent;
            if(maxLeftNode != node->left_son){
                if (maxLeftNode->left_son){
                    maxLeftNodeParent->parent->right_son = maxLeftNode->left_son;
                    maxLeftNode->left_son->parent = maxLeftNodeParent;
                }
                else maxLeftNodeParent->right_son = nullptr;
                maxLeftNode->left_son = node->left_son;
                node->left_son->parent = maxLeftNode;
            }
            if(node->right_son){
                maxLeftNode->right_son = node->right_son;
                node->right_son->parent = maxLeftNode;
            }
            maxLeftNode->parent = nodeParent;
            if(nodeParent){
                if (nodeParent->right_son == node){
                    nodeParent->right_son = maxLeftNode;
                }
                else
                    nodeParent->left_son = maxLeftNode;
            }
            maxLeftNode->parent = nodeParent;
            if(node == root){
                root = maxLeftNode;
            }
            delete node;
            --size;
        }
        else if(node->right_son){
            node->right_son->parent = nodeParent;
            if(nodeParent){
                if(nodeParent->left_son == node){
                    nodeParent->left_son = node->right_son;
                } else nodeParent->right_son = node->right_son;
            }
            if(node == root){
                root = node->right_son;
            }
            delete node;
            --size;
        }
        else{
            if(nodeParent){
                if(nodeParent->left_son == node){
                    nodeParent->left_son = nullptr;
                } else nodeParent->right_son = nullptr;
            }
            else(root = nullptr);
            delete node;
            --size;
        }
    }
    int rHeight = 0, lHeight = 0;
    if(nodeParent){
        if(nodeParent->right_son)
            rHeight = nodeParent->right_son->height;
        if(nodeParent->left_son)
            lHeight = nodeParent->left_son->height;
        nodeParent->height = (1 + std::max(rHeight, lHeight));
        this->Rotate(nodeParent);
    }
    return returnMessage::SUCCESS;
}



template<class Key, class Value>
AvlNode<Key, Value> *AvlTree<Key, Value>::Find(Key key) const {
    return findNode(root,key);
}

template<class Key, class Value>
AvlNode<Key, Value> *findNode(AvlNode<Key, Value> * rootNode,int key){
    if(!rootNode){
        return nullptr;
    }
    if(rootNode->key == key){
        return rootNode;
    } else if (rootNode->key > key)
        findNode(rootNode->left_son,key);
    else if(rootNode->key < key){
        findNode(rootNode->right_son,key);
    }
}


#endif //RATUV1_AVLTREE_H
