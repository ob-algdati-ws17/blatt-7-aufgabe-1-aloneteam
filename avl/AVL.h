class AVL {
#define calcBal(X) (X)->bal = static_cast<short>((X)->right == nullptr ? (X)->left == nullptr ? 0 : -1 : (X)->left == nullptr ? 1 : 0);

private:
    struct element {
        const int key;
        element* left;
        element* right;
        element* parent;
        short bal;

        element(int k, element* p) : key(k), left(nullptr), right(nullptr), parent(p), bal(0) {}; // konstruktor neues Blatt
        element(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr), bal(0) {}; // konstruktor, wenn erstes Element
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

    void L(element *e) {
        std::cout << "Rotate L around " << e->key << std::endl;
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
            if(isLeft) e->left = new typename AVL::element(key, e);
            else e->right = new typename AVL::element(key, e);
            if(e->bal == 0) {
                e->bal = isLeft ? -1 : 1;
                upin(e);
                return;
            }
            e->bal = 0;
            return;
        }
        add(target, key);
        return;
    };


public:
    ~AVL() {

    }

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

    element* search(const int key) {
        if(root == nullptr) {
            return nullptr;
        }
        element* next = root;

        while(true) {
            if(next == nullptr || next->key == key) {
                return nullptr;
            }
            next = (next->key == key) ? next->left : next-> right;
        }
    }

    friend AVL &operator+=(AVL &a, int input) {
//        std::cout << "Adding ... " << input << std::endl;
        if(a.root == nullptr) {
            a.root = new typename AVL::element(input);
            return a;
        }
        a.add(a.root, input);
    };

    friend AVL &operator-=(AVL &a, int input) {

    };

};