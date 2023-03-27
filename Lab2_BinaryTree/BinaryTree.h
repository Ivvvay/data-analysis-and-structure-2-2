#ifndef DATA_ANALYSIS_AND_STRUCTURE_2_2_BINARYTREE_H
#define DATA_ANALYSIS_AND_STRUCTURE_2_2_BINARYTREE_H


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
    Node* copyTree(Node* node) const;


private:
    Node* _root = nullptr;
};


#endif //DATA_ANALYSIS_AND_STRUCTURE_2_2_BINARYTREE_H
