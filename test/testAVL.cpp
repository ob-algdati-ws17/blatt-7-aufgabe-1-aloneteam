#include "testAVL.h"

using namespace std;

TEST(AVLTest, Test_Nothing) {
    EXPECT_TRUE(true);
}

TEST(AVLTest, Test_Empty) {
    AVL avl;
    EXPECT_TRUE(avl.isEmpty());
    avl += 0;
    EXPECT_FALSE(avl.isEmpty());
    avl -= 0;
    EXPECT_TRUE(avl.isEmpty());
}

#define COMPARE(X, Y, Z) EXPECT_EQ(avl.getElement((X), (Y))->key, Z)

TEST(AVLTest, Test_Insert) {
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

    COMPARE(0, 0, 14);
    COMPARE(1, 0 , 4);
    COMPARE(1, 1, 21);
    COMPARE(2, 0, 3);
    COMPARE(2, 1, 9);
    COMPARE(2, 2, 15);
    COMPARE(2, 3, 28);
    COMPARE(3, 0, 2);
    COMPARE(3, 2, 7);
    COMPARE(3, 3, 10);
    COMPARE(3, 5, 18);
    COMPARE(3, 6, 26);
    COMPARE(3, 7, 30);

    EXPECT_TRUE(avl.checkBalance());
}

TEST(AVLTest, Test_remove) {
    AVL avl;
    avl += 21;
    avl += 26;
    avl += 30;
    avl += 9;
    avl += 4;
    avl += 14;
    avl += 28;

    avl -= 26;
    avl -= 21;
    avl -= 9;

    COMPARE(0, 0, 28);
    COMPARE(1, 0, 14);
    COMPARE(1, 1, 30);
    COMPARE(2, 0, 4);
    EXPECT_TRUE(avl.checkBalance());
}

TEST(AVLTest, Test_duplicate) {
    AVL avl;
    avl += 21;
    avl += 26;
    avl += 30;
    avl += 9;
    avl += 4;

    COMPARE(0, 0, 26);
    COMPARE(1, 0, 9);
    COMPARE(1, 1, 30);
    COMPARE(2, 0, 4);
    COMPARE(2, 1, 21);
    EXPECT_TRUE(avl.checkBalance());

    avl += 21;
    avl += 26;
    avl += 30;
    avl += 9;
    avl += 4;

    COMPARE(0, 0, 26);
    COMPARE(1, 0, 9);
    COMPARE(1, 1, 30);
    COMPARE(2, 0, 4);
    COMPARE(2, 1, 21);
    EXPECT_TRUE(avl.checkBalance());
}

TEST(AVLTest, Test_checkBalance) {
    AVL avl;
    avl += 21;
    avl += 26;
    avl += 30;
    avl += 9;
    avl += 4;
    EXPECT_TRUE(avl.checkBalance());

    avl.getElement(1, 1)->bal = 1;
    EXPECT_FALSE(avl.checkBalance());
    avl.getElement(1, 1)->bal = 0;
}

TEST(AVLTest, Test_removeNotFound) {
    AVL avl;
    avl += 21;
    avl += 26;
    avl += 30;
    avl += 9;
    avl += 4;

    COMPARE(0, 0, 26);
    COMPARE(1, 0, 9);
    COMPARE(1, 1, 30);
    COMPARE(2, 0, 4);
    COMPARE(2, 1, 21);
    EXPECT_TRUE(avl.checkBalance());

    avl -= 15;
    avl -= 0;
    avl -= 8;

    COMPARE(0, 0, 26);
    COMPARE(1, 0, 9);
    COMPARE(1, 1, 30);
    COMPARE(2, 0, 4);
    COMPARE(2, 1, 21);
    EXPECT_TRUE(avl.checkBalance());
}