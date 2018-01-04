//
// Created by sahar on 29/12/2017.
//
#ifndef COLOSSEUM2_AVLTREE_H
#define COLOSSEUM2_AVLTREE_H

#include <iostream>
#include "Exceptions.h"

template<typename T>
//Forward declaration of the tree class
class AVLTree;

template<typename T>
class NodeAVL {
    friend class AVLTree<T>; //Allow the tree class to access the nodes' fields

    T data; //The node's data. Assumption: overloads comparision operators.
    int BF; //The node's balance factor.
    NodeAVL<T> *left; //Pointer to the node's left son.
    NodeAVL<T> *right; //Pointer to the node's right son.
    int rank;
    T sum;

    NodeAVL(T &data = NULL, int BF = 0, int rank = 1, NodeAVL<T> *left = NULL,
            NodeAVL<T> *right = NULL) : data(data), BF(BF), left(left),
                                        right(right), rank(rank),
                                        sum(data) {}
};


/*
 * The AVLTree class - a generic AVL tree that supports the rank feature (rank tree).
 * We make an ASSUMPTION on the type of values stored in the tree, T: this type overloaded the following operations:
 * - Comparision (==, <, >, ...).
 * - Sum (+).
 */
template<typename T>
class AVLTree {
private:
    NodeAVL<T> *root; //The tree contains only one field: a pointer to its root node.

    void Delete(NodeAVL<T> *&curr) {
        //De-allocates all of the tree's nodes, starting from the given node (root)
        if (curr) {
            Delete(curr->left);
            Delete(curr->right);
            delete curr;
            curr = NULL;
        }
    }

    void RotateL(NodeAVL<T> *&curr) {
        NodeAVL<T> *temp1 = curr;
        NodeAVL<T> *temp2 = curr->right;
        temp1->right = temp2->left;
        temp2->left = temp1;
        curr = temp2;
        temp1->BF -= 1;
        if (temp2->BF > 0) {
            temp1->BF -= temp2->BF;
        }
        temp2->BF -= 1;
        if (temp1->BF < 0) {
            temp2->BF += temp1->BF;
        }
        int rank1 = (temp1->left) ? temp1->left->rank : 0;
        int rank2 = (temp1->right) ? temp2->right->rank : 0;
        int rank3 = (temp2->right) ? temp2->right->rank : 0;
        temp1->rank = rank1 + rank2 + 1;
        int rank4 = (temp2->left) ? temp2->left->rank : 0;
        temp2->rank = rank3 + rank4 + 1;

        int sum1 = (temp1->left) ? temp1->left->sum : 0;
        int sum2 = (temp1->right) ? temp2->right->sum : 0;
        temp1->sum = sum1 + sum2 + temp1->data;
        int sum3 = (temp2->right) ? temp2->right->sum : 0;
        int sum4 = (temp2->left) ? temp2->left->sum : 0;
        temp2->sum = sum3 + sum4 + temp2->sum;
    }

    void RotateR(NodeAVL<T> *&curr) {
        NodeAVL<T> *B = curr;
        NodeAVL<T> *A = curr->left;
        B->left = A->right;
        A->right = B;
        curr = A;
        ++(B->BF);
        if (A->BF < 0) {
            B->BF -= A->BF;
        }
        ++(A->BF);
        if (B->BF > 0) {
            A->BF += B->BF;
        }
        int rank1 = (B->left) ? (B->left->rank) : 0;
        int rank2 = (B->right) ? (B->right->rank) : 0;
        B->rank = rank1 + rank2 + 1;
        int rank3 = (A->left) ? (A->left->rank) : 0;
        int rank4 = (A->right) ? (A->right->rank) : 0;
        A->rank = rank3 + rank4 + 1;

        int sum1 = (B->left) ? (B->left->sum) : 0;
        int sum2 = (B->right) ? (B->right->sum) : 0;
        B->sum = sum1 + sum2 + B->data;
        int sum3 = (A->left) ? (A->left->sum) : 0;
        int sum4 = (A->right) ? (A->right->sum) : 0;
        A->sum = sum3 + sum4 + A->data;
    }

    bool IncBF(NodeAVL<T> *&curr) {
        curr->BF++;
        if (curr->BF == 0)
            return false;
        if (curr->BF == 1)
            return true;
        if (curr->BF == 2) {
            if (curr->right->BF == -1) {
                RotateR(curr->right);
            }
            RotateL(curr);
            return false;
        }
        return true;
    }

    bool DecBF(NodeAVL<T> *&curr) {
        curr->BF--;
        if (curr->BF == 0)
            return false;
        if (curr->BF == -1)
            return true;
        if (curr->BF == -2) {
            if (curr->left->BF == 1) {
                RotateL(curr->left);
            }
            RotateR(curr);
            return false;
        }
        return true;
    }

    void FixRanks(T data, NodeAVL<T> *&curr) {
        if (!curr) {
            return;
        } else if (curr->data > data) {
            curr->rank--;
            curr->sum -= data;
            FixRanks(data, curr->left);
        } else {
            curr->rank--;
            curr->sum -= data;
            FixRanks(data, curr->right);
        }
    }

    bool Insert(T data, NodeAVL<T> *&curr) {
        if(!root){
            root = new NodeAVL<T>(data);
            return true;
        }
        if (!curr) {
            curr = new NodeAVL<T>(data);
            return true;
        } else if (!(curr->data)) {
            curr->data = data;
            curr->sum = data;
            return true;
        } else if (data > curr->data) {
            //We use this cool trick to traverse back upwards after insertion!!
            curr->rank++;
            curr->sum += data;
            return Insert(data, curr->right) && IncBF(curr);
        } else if (data < curr->data) {
            curr->rank++;
            curr->sum += data;
            return Insert(data, curr->left) && DecBF(curr);
        } else {
            FixRanks(data, root);
            throw ElementAlreadyExists();
        }
    }

    T &Find(T data, NodeAVL<T> *&curr) const {
        if (!curr || !curr->data) {
            throw ElementDoesntExist();
        } else if (data > curr->data) {
            return Find(data, curr->right);
        } else if (data < curr->data) {
            return Find(data, curr->left);
        } else {
            return curr->data;
        }
    }

    bool Remove(T data, NodeAVL<T> *&curr) {
        if (!curr || !curr->data || !data) {
            throw ElementDoesntExist();
        } else if (curr->data > data) {
            return Remove(data, curr->left) && IncBF(curr);
        } else if (curr->data < data) {
            return Remove(data, curr->right) && DecBF(curr);
        } else {
            if (!curr->left && !curr->right) {
                Delete(curr);
            } else if (curr->left && curr->right) {
                NodeAVL<T> *current_node = curr;
                T min_node_value = Min(curr->right);
                bool isDiffHeight = Remove(min_node_value, curr);
                current_node->data = min_node_value;
                return isDiffHeight;
            } else {
                NodeAVL<T> *node_to_remove = curr;

                if (!curr->left) {
                    curr = node_to_remove->right;
                    node_to_remove->right = NULL;
                } else {
                    curr = node_to_remove->left;
                    node_to_remove->left = NULL;
                }
                Delete(node_to_remove);
            }
            return true;
        }
    }

    T SmallerSumByRank(int desired_rank, NodeAVL<T> *&curr) const {
        if (!curr) {
            throw ElementDoesntExist();
        }
        int left_rank = curr->left->rank;
        if (desired_rank == curr->rank) {
            return curr->sum;
        } else if (desired_rank < left_rank) {
            return SmallerSumByRank(desired_rank, curr->left);
        } else {
            return SmallerSumByRank(desired_rank, curr->right);
        }
    }

    T Max(const NodeAVL<T> *const curr) const {
        return (!curr->right) ? curr->data : Max(curr->right);
    }

    T Min(const NodeAVL<T> *const curr) const {
        return (!curr->left) ? curr->data : Min(curr->left);
    }

    void InOrder(NodeAVL<T> *&curr) const {
        if (!this || !curr) {
            return;
        }
        InOrder(curr->left);
        std::cout << curr->data << std::endl;
        InOrder(curr->right);
    }

    void PreOrder(NodeAVL<T> *&curr) const {
        if (!this || !curr) {
            return;
        }
        std::cout << curr->data << std::endl;
        PreOrder(curr->left);
        PreOrder(curr->right);
    }

    void InorderRanks(NodeAVL<T> *&curr) const {
        if (!this || !curr) {
            return;
        }
        InorderRanks(curr->left);
        std::cout << curr->data << ": " << curr->rank << std::endl;
        InorderRanks(curr->right);
    }

    void PreorderRanks(NodeAVL<T> *&curr) const {
        if (!curr) {
            return;
        }
        std::cout << curr->data << ": " << curr->rank << ", " << curr->sum
                  << std::endl;
        PreorderRanks(curr->left);
        PreorderRanks(curr->right);
    }

public:
    AVLTree() : root(NULL) {}
    AVLTree(T data_root) : root(new NodeAVL<T>(data_root)) {}

    ~AVLTree() {
        //Wrapper for "Delete" function
        Delete(root);
    }

    void Insert(T data) {
        //Wrapper for "Insert" function
        Insert(data, root);
    }

    T &Find(T data) const {
        //Wrapper for "Find" function
        return Find(data, root);
    }

    void Remove(T data) {
        //Wrapper for "Remove" function
        Remove(data, root);
    }

    T SmallerSumByRank(int desired_rank) const {
        //Wrapper for "SmallerSumByRank" function
        int sum = root ? root->sum - desired_rank : -desired_rank;
        if (sum <= 0) {
            throw notEnoughElements();
        }
        return SmallerSumByRank(sum, root);
    }

    void InOrder() const {
        //Wrapper for "InOrder" function (kept for debugging purposes)
        InOrder(root);
    }

    void PreOrder() const {
        //Wrapper for "PreOrder" function (kept for debugging purposes)
        PreOrder(root);
    }

    void InorderRanks() const {
        InorderRanks(root);
    }

    void PreorderRanks() {
        PreorderRanks(root);
    }
};

#endif //COLOSSEUM2_AVLTREE_H