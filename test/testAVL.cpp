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

//    int c[13] = {14, 4, 21, 3, 9 ,15, 28, 2, /*nullptr,*/ 7, 10, /*nullptr,*/ 18, 26, 30};
//    int i = 0;

    EXPECT_EQ(avl.getElement(0,0)->key, 14);
    EXPECT_EQ(avl.getElement(1,0)->key, 4);
    EXPECT_EQ(avl.getElement(1,1)->key, 21);
    EXPECT_EQ(avl.getElement(2,0)->key, 3);
    EXPECT_EQ(avl.getElement(2,1)->key, 9);
    EXPECT_EQ(avl.getElement(2,2)->key, 15);
//    EXPECT_EQ(avl.getElement(2,3)->key, 28);
//    EXPECT_EQ(avl.getElement(3,0)->key, 2);
//    EXPECT_EQ(avl.getElement(3,1)->key, nullptr);
//    EXPECT_EQ(avl.getElement(3,2)->key, 7);
//    EXPECT_EQ(avl.getElement(3,3)->key, 10);
//    EXPECT_EQ(avl.getElement(3,4)->key, nullptr);
//    EXPECT_EQ(avl.getElement(3,5)->key, 18);
//    EXPECT_EQ(avl.getElement(3,6)->key, 26);
//    EXPECT_EQ(avl.getElement(3,7)->key, 30);


//    avl -= 30;
//    avl -= 7;
//    avl -= 2;
//    avl -= 10;
//    avl -= 26;
//    avl -= 3;
//    avl -= 9;
//    avl -= 15;
    EXPECT_TRUE(avl.checkBalance());
    avl.print();
    EXPECT_TRUE(true);
}