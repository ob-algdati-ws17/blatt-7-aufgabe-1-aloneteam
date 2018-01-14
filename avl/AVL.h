#ifndef INJECTOR_CLASS
#define INJECTOR_CLASS

#define calcBal(X) (X)->bal = static_cast<short>((X)->right == nullptr ? (X)->left == nullptr ? 0 : -1 : (X)->left == nullptr ? 1 : 0);
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))

class AVL {

private:
    struct element {
        const int key;
        element* left;
        element* right;
        element* parent;
        short bal;

        element(int k, element* l, element* r, element* p, short b) : key(k), left(l), right(r), parent(p), bal(b) {};
        element(int k, element* p) : key(k), left(nullptr), right(nullptr), parent(p), bal(0) {}; // konstruktor neues Blatt
        explicit element(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr), bal(0){}; // konstruktor, wenn erstes Element
    };

    element* root = nullptr;

    void upin(element *p);

    void upout(element *p);

    void L(element *e);

    void R(element *e);

    void add(element* e, int key);

    element *getMin(element* e);

    void remove(element *e);

    int countHeight(element* e);

    bool checkBalance(element* e);


public:
    ~AVL();

    element* getElement(const int line, int elem);

    void print();

    bool isEmpty();

    bool checkBalance();

    element* search(const int key);

    friend AVL &operator+=(AVL &a, int input);

    friend AVL &operator-=(AVL &a, int input);
};

#endif