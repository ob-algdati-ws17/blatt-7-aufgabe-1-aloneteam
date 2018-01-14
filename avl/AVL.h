class AVL {

#define calcBal(X) (X)->bal = static_cast<short>((X)->right == nullptr ? (X)->left == nullptr ? 0 : -1 : (X)->left == nullptr ? 1 : 0);
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))

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

    void upin(element* p) {
        if(p == root) return;
        if(p->bal != -1 && p->bal != 1) {
            std::cout << "Element (bal) ist nicht 1 oder -1. " << p->bal << "," << p->key << std::endl;
            return;
        }
        element *pp = p->parent;
        if(pp->left == p) {
            if(pp->bal == 1) {
                pp->bal = 0;
                return;
            }
            if(pp->bal == 0) {
                pp->bal = -1;
                upin(pp);
                return;
            }
            if(p->bal == -1) {
                R(pp);
                pp->bal = 0;
                p->bal = 0;
                return;
            }
            if(p->bal == 1) {
                L(p);
                R(pp);
                calcBal(pp);
                calcBal(p);
                pp->parent->bal = 0;
                return;
            }
        }
        else {
            if(pp->bal == -1) {
                pp->bal = 0;
                return;
            }
            if(pp->bal == 0) {
                pp->bal = 1;
                upin(pp);
                return;
            }
            if(p->bal == 1) {
                L(pp);
                pp->bal = 0;
                p->bal = 0;
                return;
            }
            if(p->bal == -1) {
                R(p);
                L(pp);
                calcBal(pp);
                calcBal(p);
                pp->parent->bal = 0;
            }
        }
    };

    void upout(element *p) {
        if(p == root) return;
        element *pp = p->parent;
        if(p->bal != 0) {
            std::cout << "Element (bal) ist nicht 0. " << p->bal << "," << p->key << std::endl;
            return;
        }

        bool isLeft = pp->left == p;
        element *q = isLeft ? pp->right : pp->left;
        if(isLeft) {
            if(pp->bal == -1) {
                pp->bal = 0;
                upout(pp);
                return;
            }
            if(pp->bal == 0) {
                pp->bal = 1;
                return;
            }
            //pp->bal = 1
            if(q->bal == 0) {
                L(pp);
                pp->parent->bal = -1;
                return;
            }
            if(q->bal == 1) {
                L(pp);
                pp->bal = 0;
                pp->parent->bal = 0;
                upout(pp->parent);
                return;
            }
            //q->bal = -1
            R(q);
            L(pp);
            element *ppp = pp->parent;
            calcBal(pp);
            ppp->bal = 0;
            calcBal(ppp->right);
            upout(ppp);
            return;
        }
        else {
            if(pp->bal == 1) {
                pp->bal = 0;
                upout(pp);
                return;
            }
            if(pp->bal == 0) {
                pp->bal = -1;
                return;
            }
            //pp->bal = -1
            if(q->bal == 0) {
                R(pp);
                pp->parent->bal = 1;
                return;
            }
            if(q->bal == -1) {
                R(pp);
                pp->bal = 0;
                pp->parent->bal = 0;
                upout(pp->parent);
                return;
            }
            L(q);
            R(pp);
            element *ppp = pp->parent;
            calcBal(pp);
            ppp->bal = 0;
            calcBal(ppp->left);
            upout(ppp);
            return;
        }
    }

    void L(element *e) {
        element *o = e->right;
        if(e == root) {
            root = o;
            o->parent = root;
        }
        else {
            if(e->parent->left == e) e->parent->left = o;
            else e->parent->right = o;
            o->parent = e->parent;
        }
        element *tmp = o->left;
        o->left = e;
        e->parent = o;
        e->right = tmp;
        if(tmp != nullptr) tmp->parent = e;
    };

    void R(element *e) {
        element *o = e->left;
        if(e == root) {
            root = o;
            o->parent = root;
        }
        else {
            if(e->parent->left == e) e->parent->left = o;
            else e->parent->right = o;
            o->parent = e->parent;
        }

        element *tmp = o->right;
        o->right = e;
        e->parent = o;

        e->left = tmp;
        if(tmp != nullptr) tmp->parent = e;
    };

    void add(element* e, int key) {
        if(e->key == key) return; // duplicate entry
        element *target = key < e->key ? e->left : e->right;
        if(target == nullptr) { // BLatt gefunden
            bool isLeft = key < e->key;
            if(isLeft) e->left = new AVL::element(key, e);
            else e->right = new AVL::element(key, e);
            if(e->bal == 0) {
                e->bal = static_cast<short>(isLeft ? -1 : 1);
                upin(e);
                return;
            }
            e->bal = 0;
            return;
        }
        add(target, key);
    };

    element* getMin(element* e) {
        return e->left == nullptr ? e : getMin(e->left);
    };

    void remove(element *e) {
        if(e->left != nullptr && e->right != nullptr) { // 2 Knoten
            element *q = getMin(e->right);
            auto *n = new AVL::element(q->key, e->left, e->right, e->parent, e->bal);
            if(e != root)  {
                if(e->parent->left == e) e->parent->left = n;
                else e->parent->right = n;
            }
            else root = n;
            e->right->parent = n;
            e->left->parent = n;

            remove(q);
            free(e);
            return;
        }
        else if(e->left == nullptr && e->right == nullptr) { // 2 Blätter
            if(e == root) {
                root = nullptr;
                free(e);
                return;
            }
            element *p = e->parent;
            bool isLeft = p->left == e;
            if(isLeft) p->left = nullptr;
            else p->right = nullptr;
            free(e);
            switch(countHeight(p)) {
                case 1: {
                    calcBal(p); // bal = [-1, 1]
                    return;
                }
                case 0: {
                    p->bal = 0;
                    upout(p);
                    return;
                }
                default: { // case 2
                    if (isLeft) { // links wurde entfernt
                        element *q = p->right;
                        if (q->right == nullptr) { // case 2
                            R(q);
                            L(p);
                            p->bal = 0;
                            q->bal = 0;
                            upout(p->parent);
                            return;
                        }
                        if (q->left == nullptr) {
                            L(p);
                            q->bal = 0;
                            p->bal = 0;
                            upout(q);
                            return;
                        }
                        L(p);
                        p->bal = 1;
                        q->bal = -1;
                        return;
                    }
                    element *q = p->left;
                    if (q->left == nullptr) { // case 2
                        L(q);
                        R(p);
                        p->bal = 0;
                        q->bal = 0;
                        upout(p->parent);
                        return;
                    }
                    if (q->right == nullptr) {
                        R(p);
                        q->bal = 0;
                        p->bal = 0;
                        upout(q);
                        return;
                    }
                    R(p);
                    p->bal = -1;
                    q->bal = 1;
                    return;
                }
            }
        }
        else {
            if(e == root) {
                root = root->left == nullptr ? root->right : root->left;
                free(root->parent);
                root->parent = nullptr;
                return;
            }
            element *p = e->parent;
            bool isLeftParent = p->left == e;
            bool isLeftFollower = e->left != nullptr;
            if(isLeftParent) p->left = isLeftFollower ? e->left : e->right;
            else p->right = isLeftFollower ? e->left : e->right;
            if(isLeftFollower) e->left->parent = p;
            else e->right->parent = p;
            free(e);
            upout(isLeftParent ? p->left : p->right);
        }
    };

    int countHeight(element* e) {
        return max(e->left == nullptr ? 0 : countHeight(e->left) + 1, e->right == nullptr ? 0 : countHeight(e->right) + 1);
    };

    bool checkBalance(element* e) {
        return (e->bal == static_cast<short>((e->right == nullptr ? 0 : countHeight(e->right) + 1) - (e->left == nullptr ? 0 : countHeight(e->left) + 1)))
               && (e->right == nullptr ? true : checkBalance(e->right)) && (e->left == nullptr ? true : checkBalance(e->left));
    }


public:
    ~AVL() {
        while(!isEmpty()) remove(root);
    };

    element* getElement(const int line, int elem) {
        element *current = root;
        for(int num = 1 << line - 1; num >= 1; current = elem < num ? current->left : current->right, elem &= num - 1, num >>= 1) {}
        return current;
    };

    void print() {
        using namespace std;
        element *c[500];
        c[0] = root;
        int count = 1;
        while(true) {
            element *tmpc[500];
            int counttmpc = 0;
            int countnptr = 0;
            for (int i = 0; i < count; i++) {
                if (c[i] == nullptr) {
                    cout << " -";
                    tmpc[counttmpc++] = nullptr;
                    tmpc[counttmpc++] = nullptr;
                    countnptr += 2;
                } else {
                    cout << " " << c[i]->key << "'" << c[i]->bal;
                    tmpc[counttmpc++] = c[i]->left;
                    tmpc[counttmpc++] = c[i]->right;
                }
            }
            if (counttmpc == countnptr) {
                cout << endl;
                break;
            }
            for (int i = 0; i < counttmpc; i++) {
                c[i] = tmpc[i];
            }
            count = counttmpc;
            cout << endl;
        }
    };

    bool isEmpty() {
        return root == nullptr;
    }

    bool checkBalance() {
        if(root == nullptr) return true;
        bool x = checkBalance(root);
        return x;
    }

    element* search(const int key) {
        if(root == nullptr) return nullptr;
        element *next = root;
        for(element *current = next; next != nullptr && next->key != key; next = (next->key > key) ? next->left : next-> right) {}
        return next;
    };

    friend AVL &operator+=(AVL &a, int input) {
        if(a.root == nullptr) {
            a.root = new AVL::element(input);
            return a;
        }
        a.add(a.root, input);
    };

    friend AVL &operator-=(AVL &a, int input) {
        element *e = a.search(input);
        if(e == nullptr) return a;
        a.remove(e);
    };
};