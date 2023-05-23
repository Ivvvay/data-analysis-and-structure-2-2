#ifndef DATA_ANALYSIS_AND_STRUCTURE_2_2_BINARYTREE_H
#define DATA_ANALYSIS_AND_STRUCTURE_2_2_BINARYTREE_H
#include <iostream>
#include <random>
#include <iomanip>

class BinaryTree {
public:
    class Node {
    protected:
        int _key = 0;
        Node* _leftChild = nullptr;
        Node* _rightChild = nullptr;
    public:
        Node(int key = 0, Node* leftChild = nullptr, Node* rightChild = nullptr, int height = 1); //- конструкторы (по умолчанию и с параметрами);
        ~Node() = default;
        int getKey() const; //- получение ключа узла (целое число);
        void setKey(int key);
        int getNumChildren() const; //- получение количества прямых потомков узла;
        Node* getLeftChild() const;
        Node* getRightChild() const;
        void setLeftChild(Node* leftChild);
        void setRightChild(Node* rightChild);

        int _height = 1;
    };

    BinaryTree(); //- конструктор (по умолчанию);
    BinaryTree(const BinaryTree& other); //- конструктор (копирования);
    BinaryTree(Node* newRoot);
    virtual ~BinaryTree(); //- деструктор;
    const Node* getRoot() const;//- получение корня дерева;
    Node* getRoot();

    void clear(); //- очистка дерева (удаление всех узлов);
    void deleteSubtree(int key);//- удаление поддеревьев узла;
    void deleteSubtree(Node* node);
    bool isEmpty() const; //- isEmpty (возвращает true, если дерево пусто);

    BinaryTree copySubtree(int key); //- копирование поддерева узла (возвращает новый объект класса);
    Node* copySubtree(const Node* node) const;
    virtual Node* rootOfCopySubtree(int key);
    Node* copyTree(Node* node) const;

    int getHeight() const; //- получение высоты дерева;
    int getHeight(const Node* node) const;
    int getSize() const; //- получение количества узлов дерева;
    int getSize(const Node* node) const;

    virtual int getMinKey(); //- получение минимального ключа дерева;
    virtual int getMaxKey(); //- получение максимального ключа дерева;

    virtual Node* addNode(int key); //- добавление узла в дерево (методом случайного выбора поддерева);
    virtual Node* addNode(Node* root, int key);
    virtual bool removeNode(int key); //- удаление узла из дерева по ключу (возвращает true, если узел был удалён);
    void removeNode(Node* node);
    bool removeRoot();
    virtual Node* getSuccessor(Node* node);

    virtual Node* findNodeByKey(int key);//- поиск узла по ключу
    Node* findNodeByKey(int key, Node* currentNode);
    Node* findParent(Node* node, Node* current); //- поиск предков

    bool isBalanced() const; //- проверка дерева на сбалансированность (возвращает true, если дерево является сбалансированным:
    virtual bool isBalanced(const Node* node) const; //высоты правого и левого поддеревьев отличаются не более, чем на единицу, и сами поддеревья также являются сбалансированными);
    int getSum(); //- получение суммы всех ключей дерева;
    int getSum(const Node* node);
    virtual int getNodeLevel(int key);//- получение уровня вершины по ключу (возвращает индекс уровня или -1, если вершина не найдена);
    int getNodeLevel(int key, const Node* node, int level = 0);
    std::vector<int> getKeys() const; //- получение вектора  содержащего все ключи дерева (обход вершин производить любым способом - Л-К-П);
    void inorderTraversal(const Node* node, std::vector<int>& keys) const;

    void printTree() const; //- вывод в консоль дерева в горизонтальном виде;
    void printTree(const Node* node, int indent) const;
    void printLeaves() const; //- вывод в консоль листьев дерева;
    void printLeaves(const Node* node) const;

    BinaryTree& operator=(const BinaryTree& other); //- оператор присваивания;
    void copyNodes(Node* newNode, const Node* otherNode) const;

protected:
    Node* _root = nullptr;
};


#endif //DATA_ANALYSIS_AND_STRUCTURE_2_2_BINARYTREE_H
