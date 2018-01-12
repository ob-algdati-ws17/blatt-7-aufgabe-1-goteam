#include "testAvlTree.h"

using namespace std;


TEST(AvlTreeTest, Empty_Tree) {
    AvlTree a;
    EXPECT_EQ(nullptr, a.search(1));
}

TEST(AvlTreeTest, One_Node) {
    AvlTree a;
    a.add(1);
    EXPECT_EQ(1, a.search(1)->key);
    EXPECT_EQ(0, a.search(1)->balanceFactor);
    EXPECT_EQ(nullptr, a.search(1)->predecessor);
    EXPECT_EQ(nullptr, a.search(1)->leftSuccessor);
    EXPECT_EQ(nullptr, a.search(1)->rightSuccessor);
}

TEST(AvlTreeTest, Two_Node) {
    AvlTree a;
    a.add(1);
    a.add(2);
    EXPECT_EQ(nullptr, a.search(1)->leftSuccessor);
    EXPECT_EQ(a.search(1)->rightSuccessor, a.search(2));
    EXPECT_EQ(a.search(1), a.search(2)->predecessor);
}

TEST(AvlTreeTest, UpIn_Balance_Right) {
    AvlTree a;
    a.add(1);
    EXPECT_EQ(0, a.search(1)->balanceFactor);
    a.add(2);
    EXPECT_EQ(0, a.search(2)->balanceFactor);
    EXPECT_EQ(1, a.search(1)->balanceFactor);
}

TEST(AvlTreeTest, UpIn_Balance_Left) {
    AvlTree a;
    a.add(2);
    EXPECT_EQ(0, a.search(2)->balanceFactor);
    a.add(1);
    EXPECT_EQ(0, a.search(1)->balanceFactor);
    EXPECT_EQ(-1, a.search(2)->balanceFactor);
}

TEST(AvlTreeTest, UpIn_Balance) {
    AvlTree a;
    a.add(2);
    EXPECT_EQ(0, a.search(2)->balanceFactor);
    a.add(1);
    EXPECT_EQ(0, a.search(1)->balanceFactor);
    EXPECT_EQ(-1, a.search(2)->balanceFactor);
    a.add(3);
    EXPECT_EQ(0, a.search(1)->balanceFactor);
    EXPECT_EQ(0, a.search(2)->balanceFactor);
    EXPECT_EQ(0, a.search(3)->balanceFactor);
}

TEST(AvlTreeTest, UpIn_Rotate_Right) {
    AvlTree a;
    a.add(3);
    a.add(2);
    a.add(1);
    EXPECT_EQ(0, a.search(1)->balanceFactor);
    EXPECT_EQ(0, a.search(2)->balanceFactor);
    EXPECT_EQ(0, a.search(3)->balanceFactor);

    EXPECT_EQ(nullptr, a.search(2)->predecessor);
    EXPECT_EQ(a.search(2)->rightSuccessor, a.search(3));
    EXPECT_EQ(a.search(3)->predecessor, a.search(2));
    EXPECT_EQ(a.search(2)->leftSuccessor, a.search(1));
    EXPECT_EQ(a.search(1)->predecessor, a.search(2));

    EXPECT_EQ(nullptr, a.search(3)->leftSuccessor);
}

TEST(AvlTreeTest, UpIn_Rotate_Left) {
    AvlTree a;
    a.add(1);
    a.add(2);
    a.add(3);
    EXPECT_EQ(0, a.search(1)->balanceFactor);
    EXPECT_EQ(0, a.search(2)->balanceFactor);
    EXPECT_EQ(0, a.search(3)->balanceFactor);

    EXPECT_EQ(nullptr, a.search(2)->predecessor);
    EXPECT_EQ(a.search(2)->rightSuccessor, a.search(3));
    EXPECT_EQ(a.search(3)->predecessor, a.search(2));
    EXPECT_EQ(a.search(2)->leftSuccessor, a.search(1));
    EXPECT_EQ(a.search(1)->predecessor, a.search(2));

    EXPECT_EQ(nullptr, a.search(1)->rightSuccessor);
}

TEST(AvlTreeTest, UpIn_Rotate_LeftRight) {
    AvlTree a;
    a.add(3);
    a.add(1);
    a.add(2);
    EXPECT_EQ(0, a.search(1)->balanceFactor);
    EXPECT_EQ(0, a.search(2)->balanceFactor);
    EXPECT_EQ(0, a.search(3)->balanceFactor);

    EXPECT_EQ(nullptr, a.search(1)->leftSuccessor);
    EXPECT_EQ(nullptr, a.search(1)->rightSuccessor);
    EXPECT_EQ(a.search(2), a.search(1)->predecessor);

    EXPECT_EQ(nullptr, a.search(3)->leftSuccessor);
    EXPECT_EQ(nullptr, a.search(3)->rightSuccessor);
    EXPECT_EQ(a.search(2), a.search(3)->predecessor);

    EXPECT_EQ(nullptr, a.search(2)->predecessor);
    EXPECT_EQ(a.search(1), a.search(2)->leftSuccessor);
    EXPECT_EQ(a.search(3), a.search(2)->rightSuccessor);
}

TEST(AvlTreeTest, UpIn_Rotate_RightLeft) {
    AvlTree a;
    a.add(1);
    a.add(3);
    a.add(2);
    EXPECT_EQ(0, a.search(1)->balanceFactor);
    EXPECT_EQ(0, a.search(2)->balanceFactor);
    EXPECT_EQ(0, a.search(3)->balanceFactor);

    EXPECT_EQ(nullptr, a.search(1)->leftSuccessor);
    EXPECT_EQ(nullptr, a.search(1)->rightSuccessor);
    EXPECT_EQ(a.search(2), a.search(1)->predecessor);

    EXPECT_EQ(nullptr, a.search(3)->leftSuccessor);
    EXPECT_EQ(nullptr, a.search(3)->rightSuccessor);
    EXPECT_EQ(a.search(2), a.search(3)->predecessor);

    EXPECT_EQ(nullptr, a.search(2)->predecessor);
    EXPECT_EQ(a.search(1), a.search(2)->leftSuccessor);
    EXPECT_EQ(a.search(3), a.search(2)->rightSuccessor);
}

TEST(AvlTreeTest, UpIn_Rotate_LeftRight_Big) {
    AvlTree a;
    a.add(4);
    a.add(5);
    a.add(3);
    a.add(1);
    a.add(2);
    EXPECT_EQ(a.search(4), a.search(2)->predecessor);
    EXPECT_EQ(nullptr, a.search(4)->predecessor);
    EXPECT_EQ(-1, a.search(4)->balanceFactor);
    EXPECT_EQ(0, a.search(1)->balanceFactor);
    EXPECT_EQ(0, a.search(2)->balanceFactor);
    EXPECT_EQ(0, a.search(3)->balanceFactor);
}

TEST(AvlTreeTest, UpIn_Rotate_RightLeft_Big) {
    AvlTree a;
    a.add(2);
    a.add(1);
    a.add(5);
    a.add(4);
    a.add(3);
    EXPECT_EQ(a.search(2), a.search(4)->predecessor);
    EXPECT_EQ(nullptr, a.search(2)->predecessor);
    EXPECT_EQ(1, a.search(2)->balanceFactor);
    EXPECT_EQ(0, a.search(3)->balanceFactor);
    EXPECT_EQ(0, a.search(4)->balanceFactor);
    EXPECT_EQ(0, a.search(5)->balanceFactor);
}

TEST(AvlTreeTest, Test_Height) {
    AvlTree a;
    a.add(2);
    a.add(1);
    a.add(5);
    a.add(4);

    auto test = a.search(5);
    EXPECT_EQ(height(test), 1);
}