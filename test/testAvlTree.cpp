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