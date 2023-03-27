#ifndef DATA_ANALYSIS_AND_STRUCTURE_2_2_BINARYTREE_H
#define DATA_ANALYSIS_AND_STRUCTURE_2_2_BINARYTREE_H
#include <iostream>

class BinaryTree {
public:
    class Node {
    private:
        int _key = 0;
        Node* _leftChild = nullptr;
        Node* _rightChild = nullptr;
    public:
        Node(int key = 0, Node* leftChild = nullptr, Node* rightChild = nullptr); //- конструкторы (по умолчанию и с параметрами);
        ~Node() = default;
        int getKey() const; //- получение ключа узла (целое число);
        void setKey(int key);
        int getNumChildren() const; //- получение количества прямых потомков узла;
        Node* getLeftChild() const;
        Node* getRightChild() const;
        void setLeftChild(Node* leftChild);
        void setRightChild(Node* rightChild);
    };
    BinaryTree(); //- конструктор (по умолчанию);
    BinaryTree(const BinaryTree& other); //- конструктор (копирования);
    ~BinaryTree(); //- деструктор;
    const Node* getRoot() const;//- получение корня дерева;
    Node* getRoot();
    void clear(); //- очистка дерева (удаление всех узлов);
    void deleteSubtree(Node* node);
    bool isEmpty() const; //- isEmpty (возвращает true, если дерево пусто);
    Node* copySubtree(const Node* node) const; //- копирование поддерева узла (возвращает новый объект класса);
    Node* copyTree(Node* node) const;
    int getHeight() const; //- получение высоты дерева;
    int getHeight(const Node* node) const;
    int getSize() const; //- получение количества узлов дерева;
    int getSize(const Node* node) const;


private:
    Node* _root = nullptr;
};


#endif //DATA_ANALYSIS_AND_STRUCTURE_2_2_BINARYTREE_H
