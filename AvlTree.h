#ifndef RATUV1_AVLTREE_H
#define RATUV1_AVLTREE_H

#include <iostream>
#include "Pair.h"
#include "wet1util.h"
#include "Score.h"

template<class Key, class Value>
class AvlNode {
public:
    Key key;
    Value value;
    AvlNode *right_son;
    AvlNode *left_son;
    AvlNode *parent;
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

    ~AvlNode() = default;
};


template<class Key, class Value>
class AvlTree {
public:
    int size;
    AvlNode<Key, Value> *root;
public:
    AvlTree();

    ~AvlTree();

    AvlTree(AvlTree<Key, Value> &other);

    void DeleteTree(AvlNode<Key, Value> *node);

    int BF(AvlNode<Key, Value> *node) const;

    AvlNode<Key, Value> *RR(AvlNode<Key, Value> *node);

    AvlNode<Key, Value> *LL(AvlNode<Key, Value> *node);

    AvlNode<Key, Value> *RL(AvlNode<Key, Value> *node);

    AvlNode<Key, Value> *LR(AvlNode<Key, Value> *node);

    AvlNode<Key, Value> *Rotate(AvlNode<Key, Value> *node);

    StatusType Insert(Key key, Value value);

    StatusType InsertNode(AvlNode<Key, Value> *root, AvlNode<Key, Value> *parent, AvlNode<Key, Value> *toInsert);

    AvlNode<Key, Value> *deleteNode(AvlNode<Key, Value> *node, AvlNode<Key, Value> *nodeParent);

    void UpdateTreeBalance(AvlNode<Key, Value> *node);

    StatusType Delete(Key key);

    AvlNode<Key, Value> *Find(Key key);

    StatusType Merge(AvlTree<Key, Value> &second_tree);

    void InOrder(AvlNode<Key, Value> *root, Pair<Key, Value> arr[]);

    void ArrayToAvlTree(Pair<Key, Value> *arr, int arr_len);

    AvlNode<Key, Value> *ArrayToAvlTreeFunc(Pair<Key, Value> arr[], int begin, int end);

    AvlNode<Key, Value> *Next_InOrder(AvlNode<Key, Value> *node);

    AvlNode<Key, Value> *Prev_InOrder(AvlNode<Key, Value> *node);
};


// Constructor
template<class Key, class Value>
AvlTree<Key, Value>::AvlTree() : size(0), root(nullptr) {}

// Destructor
template<class Key, class Value>
AvlTree<Key, Value>::~AvlTree() {
    if (root != nullptr) {
        DeleteTree(root);
    }
}

template<class Key, class Value>
AvlTree<Key, Value>::AvlTree(AvlTree<Key, Value> &other) {
    root = other.root;
    size = other.size;
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
void updateHeight(AvlNode<Key, Value> *node) {
    int Rheight = 0;
    int Lheight = 0;
    if (node->right_son != nullptr) {
        Rheight = node->right_son->height;
    }
    if (node->left_son != nullptr) {
        Lheight = node->left_son->height;
    }
    if (!node->left_son && !node->right_son) {
        node->height = 0;
    } else {
        node->height = 1 + (std::max(Rheight, Lheight));
    }
}


// Calculates Balance Factor
template<class Key, class Value>
int AvlTree<Key, Value>::BF(AvlNode<Key, Value> *node) const {
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

// Preforms Right Right rotation
template<class Key, class Value>
AvlNode<Key, Value> *AvlTree<Key, Value>::RR(AvlNode<Key, Value> *node) {
    AvlNode<Key, Value> *a;
    AvlNode<Key, Value> *b;
    a = node;
    b = a->right_son;
    a->right_son = b->left_son;
    if (b->left_son) {
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
    if (root == node) {
        root = b;
    }
    return b;
}

// Preforms Left Left rotation
template<class Key, class Value>
AvlNode<Key, Value> *AvlTree<Key, Value>::LL(AvlNode<Key, Value> *node) {
    AvlNode<Key, Value> *a;
    AvlNode<Key, Value> *b;
    a = node;
    b = a->left_son;
    a->left_son = b->right_son;
    if (b->right_son) {
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
    if (root == node) {
        root = b;
    }
    return b;
}

// Preforms Right Left rotation
template<class Key, class Value>
AvlNode<Key, Value> *AvlTree<Key, Value>::RL(AvlNode<Key, Value> *node) {
    node->right_son = LL(node->right_son);
    return RR(node);
}

// Preforms Left Right rotation
template<class Key, class Value>
AvlNode<Key, Value> *AvlTree<Key, Value>::LR(AvlNode<Key, Value> *node) {
    node->left_son = RR(node->left_son);
    return LL(node);
}

// Preforms the rotation needed
template<class Key, class Value>
AvlNode<Key, Value> *AvlTree<Key, Value>::Rotate(AvlNode<Key, Value> *node) {
    int bf = BF(node);
    if (bf >= 2) {
        if (BF(node->left_son) >= 0) {
            return LL(node);
        } else {
            return LR(node);
        }
    } else if (bf <= -2) {
        if (BF(node->right_son) > 0) {
            return RL(node);
        } else {
            return RR(node);
        }
    } else return node;
}

template<class Key, class Value>
StatusType AvlTree<Key, Value>::Insert(Key key, Value value) {
    AvlNode<Key, Value> *node;
    try {
        node = new AvlNode<Key, Value>(key, value);
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!root) {
        root = node;
        size++;
        return StatusType::SUCCESS;
    } else {
        return InsertNode(root, nullptr, node);
    }
}

template<class Key, class Value>
StatusType
AvlTree<Key, Value>::InsertNode(AvlNode<Key, Value> *rootNode, AvlNode<Key, Value> *newParent,
                                AvlNode<Key, Value> *toInsert) {
    if (!rootNode) {
        rootNode = toInsert;
        rootNode->parent = newParent;
        if (newParent) {
            if (newParent->key > toInsert->key) {
                newParent->left_son = rootNode;
            } else newParent->right_son = rootNode;
        }
        size++;
    } else if (rootNode->key == toInsert->key) {
        return StatusType::FAILURE;

    } else if (rootNode->key > toInsert->key) {
        InsertNode(rootNode->left_son, rootNode, toInsert);
    } else if (rootNode->key < toInsert->key) {
        InsertNode(rootNode->right_son, rootNode, toInsert);
    }
    int rHeight = 0, lHeight = 0;
    if (newParent) {
        if (newParent->right_son)
            rHeight = newParent->right_son->height;
        if (newParent->left_son)
            lHeight = newParent->left_son->height;
        if (newParent->left_son || newParent->right_son)
            newParent->height = 1 + std::max(rHeight, lHeight);
        else
            newParent->height = 0;
        this->Rotate(newParent);
    }
    return StatusType::SUCCESS;
}

template<class Key, class Value>
AvlNode<Key, Value> *findMinNode(AvlNode<Key, Value> *root) {
    AvlNode<Key, Value> *node = root;
    while (node->left_son != nullptr) {
        node = node->left_son;
    }
    return node;
}

template<class Key, class Value>
AvlNode<Key, Value> *findMaxNode(AvlNode<Key, Value> *root) {
    AvlNode<Key, Value> *node = root;
    while (node->right_son != nullptr) {
        node = node->right_son;
    }
    return node;
}

template<class Key, class Value>
StatusType AvlTree<Key, Value>::Delete(Key key) {
    AvlNode<Key, Value> *node = Find(key);
    if (!node)
        return StatusType::FAILURE;
    AvlNode<Key, Value> *new_node = deleteNode(node, node->parent);
    UpdateTreeBalance(new_node);
    return StatusType::SUCCESS;
}

template<class Key, class Value>
AvlNode<Key, Value> *AvlTree<Key, Value>::deleteNode(AvlNode<Key, Value> *node, AvlNode<Key, Value> *nodeParent) {
    //if node is a leaf
    if (!node->left_son && !node->right_son) {
        if (nodeParent) {
            if (nodeParent->left_son == node) {
                nodeParent->left_son = nullptr;
            } else {
                nodeParent->right_son = nullptr;
            }
        }
        if(node == root)
            root = nullptr;
        delete node;
        size--;
        return nodeParent;
    }
        // if node has only right son
    else if (!node->left_son && node->right_son) {
        if (nodeParent) {
            if (nodeParent->left_son == node) {
                nodeParent->left_son = node->right_son;
            } else {
                nodeParent->right_son = node->right_son;
            }
        }
        node->right_son->parent = nodeParent;
        if(node == root)
            root = node->right_son;
        delete node;
        size--;
        return nodeParent;
    }
        // if node has only left son
    else if (node->left_son && !node->right_son) {
        if (nodeParent) {
            if (nodeParent->left_son == node) {
                nodeParent->left_son = node->left_son;
            } else {
                nodeParent->right_son = node->left_son;
            }
        }
        node->left_son->parent = nodeParent;
        if(node == root)
            root = node->left_son;
        delete node;
        size--;
        return nodeParent;
    }
        // if node has both sons
    else {
        AvlNode<Key, Value> *maxNode = findMaxNode(node->left_son);
        AvlNode<Key, Value> *maxNodeParent = maxNode->parent;
        //if maxNode is a direct son of node
        if (node->left_son == maxNode) {
            node->right_son->parent = maxNode;
            maxNode->right_son = node->right_son;
            maxNode->parent = nodeParent;
            if (nodeParent) {
                if (nodeParent->left_son == node) {
                    nodeParent->left_son = maxNode;
                } else {
                    nodeParent->right_son = maxNode;
                }
            }
            if(node == root)
                root = maxNode;
            delete node;
            size--;
            return maxNode;
            //if maxNode isn't a direct son of node
        } else {
            node->right_son->parent = maxNode;
            node->left_son->parent = maxNode;
            //if maxNode has a left son
            if (maxNode->left_son) {
                if (maxNodeParent->left_son == maxNode) {
                    maxNodeParent->left_son = maxNode->left_son;
                } else {
                    maxNodeParent->right_son = maxNode->left_son;
                }
                maxNode->left_son->parent = maxNodeParent;
                //if maxNode is a leaf
            } else {
                if (maxNodeParent->left_son == maxNode) {
                    maxNodeParent->left_son = nullptr;
                } else {
                    maxNodeParent->right_son = nullptr;
                }
            }
            maxNode->parent = nodeParent;
            maxNode->right_son = node->right_son;
            maxNode->left_son = node->left_son;
            if (nodeParent) {
                if (nodeParent->left_son == node) {
                    nodeParent->left_son = maxNode;
                } else {
                    nodeParent->right_son = maxNode;
                }
            }
            if(node == root)
                root = maxNode;
            delete node;
            size--;
            return maxNodeParent;
        }
    }
}

template<class Key, class Value>
void AvlTree<Key, Value>::UpdateTreeBalance(AvlNode<Key, Value> *node) {
    if (!node)
        return;
    int rHeight = 0, lHeight = 0;
    if (node->right_son)
        rHeight = node->right_son->height;
    if (node->left_son)
        lHeight = node->left_son->height;
    if (node->left_son || node->right_son)
        node->height = 1 + std::max(rHeight, lHeight);
    else
        node->height = 0;
    this->Rotate(node);
    UpdateTreeBalance(node->parent);
}


template<class Key, class Value>
AvlNode<Key, Value> *AvlTree<Key, Value>::Find(Key key) {
    return findNode(root, key);
}

template<class Key, class Value>
AvlNode<Key, Value> *findNode(AvlNode<Key, Value> *rootNode, Key key) {
    if (!rootNode) {
        return nullptr;
    } else if (rootNode->key == key) {
        return rootNode;
    } else if (rootNode->key > key)
        return findNode(rootNode->left_son, key);
    else {
        return findNode(rootNode->right_son, key);
    }
}

// A uniting function to find the previous node inorder
template<class Key, class Value>
AvlNode<Key, Value> *AvlTree<Key, Value>::Prev_InOrder(AvlNode<Key, Value> *node) {
    if (!node) {
        return nullptr;
    }
    if (node->left_son) {
        return findMaxNode(node->left_son);
    } else {
        AvlNode<Key, Value> *parent = node->parent;
        while (parent && node == parent->left_son) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }
}

// A uniting function to find the next node inorder
template<class Key, class Value>
AvlNode<Key, Value> *AvlTree<Key, Value>::Next_InOrder(AvlNode<Key, Value> *node) {
    if (!node) {
        return nullptr;
    }
    if (node->right_son) {
        return findMinNode(node->right_son);
    }
    AvlNode<Key, Value> *parent = node->parent;
    while (parent != nullptr && node == parent->right_son) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}


template<class Key, class Value>
StatusType AvlTree<Key, Value>::Merge(AvlTree<Key, Value> &second_tree) {
    if (!(this->root) && !(second_tree.root)) {
        return StatusType::SUCCESS;
    }
    int first_tree_size = this->size;
    int second_tree_size = second_tree.size;
    Pair<Key, Value> *array1, *array2;
    try {
        array1 = new Pair<Key, Value>[first_tree_size];
    }
    catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }
    InOrder(this->root, array1);
    try {
        array2 = new Pair<Key, Value>[second_tree_size];
    }
    catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }
    InOrder(second_tree.root, array2);
    Pair<Key, Value> *mergedArray = MergeTwoSortedArrays(array1, array2, first_tree_size, second_tree_size);
    if ((this->root)) {
        DeleteTree(this->root);
    }
    this->ArrayToAvlTree(mergedArray, first_tree_size + second_tree_size);
    this->size = first_tree_size + second_tree_size;
    DeleteTree(second_tree.root);
    second_tree.root = nullptr;
    delete[] array1;
    delete[] array2;
    delete[] mergedArray;
    return StatusType::SUCCESS;
}

// A utility function that merges 2 sorted arrays into 1 sorted array
template<class Key, class Value>
Pair<Key, Value> *MergeTwoSortedArrays(Pair<Key, Value> arr1[], Pair<Key, Value> arr2[], int arr1_len, int arr2_len) {
    auto *mergedArr = new Pair<Key, Value>[arr1_len + arr2_len];
    int arr1_index = 0, arr2_index = 0, new_arr_index = 0;

    while (arr1_index < arr1_len && arr2_index < arr2_len) {
        if (arr1[arr1_index] < arr2[arr2_index]) {
            mergedArr[new_arr_index] = arr1[arr1_index];
            arr1_index++;
        } else {
            mergedArr[new_arr_index] = arr2[arr2_index];
            arr2_index++;
        }
        new_arr_index++;
    }
    while (arr1_index < arr1_len) {
        mergedArr[new_arr_index] = arr1[arr1_index];
        arr1_index++;
        new_arr_index++;
    }
    while (arr2_index < arr2_len) {
        mergedArr[new_arr_index] = arr2[arr2_index];
        arr2_index++;
        new_arr_index++;
    }
    return mergedArr;
}


// A utility function to make a sorted array into an AVL tree
template<class Key, class Value>
void AvlTree<Key, Value>::ArrayToAvlTree(Pair<Key, Value> *arr, int arr_len) {
    AvlNode<Key, Value> *tree_root = ArrayToAvlTreeFunc(arr, 0, arr_len - 1);
    ArrayToAvlTreeParentFunc(tree_root);
    this->root = tree_root;
    this->size = arr_len;
}

// A utility function for ArrayToAvlTree
template<class Key, class Value>
AvlNode<Key, Value> *AvlTree<Key, Value>::ArrayToAvlTreeFunc(Pair<Key, Value> arr[], int begin, int end) {
    if (begin > end) {
        return NULL;
    }
    int mid = (begin + end) / 2;
    auto *new_node = new AvlNode<Key, Value>(arr[mid].key, arr[mid].value);
    new_node->left_son = ArrayToAvlTreeFunc(arr, begin, mid - 1);
    new_node->right_son = ArrayToAvlTreeFunc(arr, mid + 1, end);
    updateHeight(new_node);
    return new_node;
}

// A utility function for ArrayToAvlTree
template<class Key, class Value>
void ArrayToAvlTreeParentFunc(AvlNode<Key, Value> *root) {
    if (root->left_son) {
        root->left_son->parent = root;
        ArrayToAvlTreeParentFunc(root->left_son);
    }
    if (root->right_son) {
        root->right_son->parent = root;
        ArrayToAvlTreeParentFunc(root->right_son);
    }
}

// A utility function that recieves an AVL tree and an empty array and sorts inorder trans into the array
template<class Key, class Value>
void AvlTree<Key, Value>::InOrder(AvlNode<Key, Value> *tree_root, Pair<Key, Value> arr[]) {
    int i = 0;
    InOrderFunc(tree_root, arr, i);
}


// A utility function for InOrder
template<class Key, class Value>
void InOrderFunc(AvlNode<Key, Value> *root, Pair<Key, Value> arr[], int &index) {
    if (!root) {
        return;
    }
    InOrderFunc(root->left_son, arr, index);
    arr[index].key = root->key;
    arr[index].value = root->value;
    index++;
    InOrderFunc(root->right_son, arr, index);
}

template<class Key, class Value>
void limitedInorder(AvlNode<Key, Value> *root, Pair<Key, Value> arr[], Key minKey, Key maxKey) {
    if (!root) {
        return;
    }
    int i = 0;
    if (root->key <= maxKey && root->key >= minKey) {
        limitedInorderHelper(root, arr, minKey, maxKey, i);
    } else if (root->key > maxKey) {
        limitedInorder(root->left_son, arr, minKey, maxKey);
    } else if (root->key < minKey) {
        limitedInorder(root->right_son, arr, minKey, maxKey);
    }
}


template<class Key, class Value>
void limitedInorderHelper(AvlNode<Key, Value> *root, Pair<Key, Value> arr[], Key minKey, Key maxKey, int &index) {
    if (!root) {
        return;
    }
    if ((root->key < minKey || root->key > maxKey) && (!findNodeInRange(root->left_son, minKey, maxKey)) &&
        (!findNodeInRange(root->right_son, minKey, maxKey))) {
        return;
    }
    if (findNodeInRange(root->left_son, minKey, maxKey)) {
        limitedInorderHelper(root->left_son, arr, minKey, maxKey, index);
    }

    if (root->key <= maxKey && minKey <= root->key) {
        arr[index].key = root->key;
        arr[index].value = root->value;
        index++;

    }
    if (findNodeInRange(root->right_son, minKey, maxKey)) {
        limitedInorderHelper(root->right_son, arr, minKey, maxKey, index);
    }

}

template<class Key, class Value>
bool findNodeInRange(AvlNode<Key, Value> *root, Key minKey, Key maxKey) {
    if (!root) {
        return false;
    }
    if (root->key <= maxKey && root->key >= minKey) {
        return true;
    } else if (root->key > maxKey) {
        return findNodeInRange(root->left_son, minKey, maxKey);
    } else if (root->key < minKey) {
        return findNodeInRange(root->right_son, minKey, maxKey);
    }
    return false;
}


template<class Key, class Value>
int rangeCount(AvlNode<Key, Value> *root, Key minKey, Key maxKey) {
    if (!root) {
        return 0;
    }
    int i = 0;
    if (root->key <= maxKey && root->key >= minKey) {
        return rangeCountHelper(root, minKey, maxKey, i);
    } else if (root->key > maxKey) {
        return rangeCountHelper(root->left_son, minKey, maxKey, i);
    } else {
        return rangeCountHelper(root->right_son, minKey, maxKey, i);
    }
}

template<class Key, class Value>
int rangeCountHelper(AvlNode<Key, Value> *root, Key minKey, Key maxKey, int &i) {
    if (!root) {
        return i;
    }
    if ((root->key < minKey || root->key > maxKey) && (((root->left_son && findMinNode(root)->key > maxKey) ||
                                                        (root->right_son && findMaxNode(root)->key < minKey)))) {
        return i;
    }
    rangeCountHelper(root->left_son, minKey, maxKey, i);
    rangeCountHelper(root->right_son, minKey, maxKey, i);
    if (root->key <= maxKey && minKey <= root->key) {
        ++i;
    }
    return i;
}


template<class Key, class Value>
bool is_tree_valid(AvlNode<Key, Value> *root) {
    if (!root) {
        return true;
    }
    if (root->height != 1 + std::max(getHeight(root->left_son), getHeight(root->right_son))) {
        return false;
    }
    if (!root->left_son && !root->right_son && root->height != 0) {
        return false;
    }
    if (root->left_son && root->left_son->key >= root->key) {
        return false;
    }
    if (root->right_son && root->right_son->key <= root->key) {
        return false;
    }
    if (std::abs(BalanceFactor(root)) > 1) {
        return false;
    }
    if (root->parent) {
        if (root->parent->left_son != root && root->parent->right_son != root) {
            return false;
        }
    }
    if (root->left_son) {
        if (root->left_son->parent != root) {
            return false;
        }
    }
    if (root->right_son) {
        if (root->right_son->parent != root) {
            return false;
        }
    }
    return is_tree_valid(root->left_son) && is_tree_valid(root->right_son);
}

template<class Key, class Value>
int getHeight(AvlNode<Key, Value> *root) {
    if (!root) {
        return -1;
    }
    return root->height;
}

template<class Key, class Value>
int is_tree_size_valid(AvlNode<Key, Value> *root) {
    if (!root) {
        return 0;
    } else {
        return is_tree_size_valid(root->left_son) + is_tree_size_valid(root->right_son) + 1;
    }
}

template<class Key, class Value>
int BalanceFactor(AvlNode<Key, Value> *node) {
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


#endif //RATUV1_AVLTREE_H