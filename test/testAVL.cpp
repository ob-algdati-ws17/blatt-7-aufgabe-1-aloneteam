#include "testAVL.h"
#include <memory>

using namespace std;

TEST(AVLTest, Test_Nothing) {
    EXPECT_TRUE(true);
}

TEST(AVLTest, Test_OneElement) {
    AVL avl;

    avl += 21;
    avl += 26;
    avl += 30;
    avl += 9;
    avl += 4;
    avl += 14;
    avl += 28;
    avl += 18;
    avl += 15;
    avl += 10;
    avl += 2;
    avl += 3;
    avl += 7;
    avl.print();
    EXPECT_TRUE(true);
}