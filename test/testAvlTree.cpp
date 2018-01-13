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

TEST(AvlTreeTest, TestSubTreeHeight) {
    AvlTree a;
    a.add(2);
    a.add(1);
    a.add(5);
    a.add(4);

    auto test = a.search(2)->rightSuccessor;
    EXPECT_EQ(height(test), 2);
}

TEST(AvlTreeTest, RemoveNode_OneSuccessor) {
    AvlTree a;
    a.add(3);
    a.add(4);
    a.add(2);
    a.add(1);

    EXPECT_EQ(a.search(2), a.search(3)->leftSuccessor);

    a.remove(2);
    EXPECT_EQ(nullptr, a.search(2));
    EXPECT_EQ(a.search(1), a.search(3)->leftSuccessor);
    EXPECT_EQ(a.search(3), a.search(1)->predecessor);
}

TEST(AvlTreeTest, RemoveNode_OneSuccessor_Root) {
    AvlTree a;
    a.add(1);
    a.add(2);

    EXPECT_EQ(a.search(2), a.search(1)->rightSuccessor);

    a.remove(1);
    EXPECT_EQ(nullptr, a.search(1));
    EXPECT_EQ(nullptr, a.search(2)->predecessor);
}

TEST(AvlTreeTest, RemoveNode_TwoLeafsAndHeightOfQ0_LS_Simple) {
    AvlTree a;
    a.add(10);
    a.add(9);

    a.remove(9);
    EXPECT_TRUE(a.search(9) == nullptr);
    EXPECT_TRUE(a.search(10)->balanceFactor == 0);
    EXPECT_TRUE(a.search(10)->leftSuccessor == nullptr && a.search(10)->rightSuccessor == nullptr);
}

TEST(AvlTreeTest, RemoveNode_TwoLeafsAndHeightOfQ1_LS_Simple) {
    AvlTree a;
    a.add(10);
    a.add(9);
    a.add(11);

    a.remove(9);
    EXPECT_TRUE(a.search(9) == nullptr);
    EXPECT_TRUE(a.search(10)->leftSuccessor == nullptr);
    EXPECT_TRUE(a.search(10)->balanceFactor == 1);
}

TEST(AvlTreeTest, RemoveNode_TwoLeafsAndHeightOfQ2_LS_Rotate) {
    AvlTree a;
    a.add(10);
    a.add(9);
    a.add(11);
    a.add(12);

    a.remove(9);
    EXPECT_TRUE(a.search(9) == nullptr);
    EXPECT_TRUE(a.search(11)->leftSuccessor->key == 10);
    EXPECT_TRUE(a.search(11)->rightSuccessor->key == 12);
    EXPECT_TRUE(a.search(11)->balanceFactor == 0);
}

TEST(AvlTreeTest, RemoveNode_TwoLeafsAndHeightOfQ2_LS_DoubleRotate) {
    AvlTree a;
    a.add(10);
    a.add(9);
    a.add(12);
    a.add(11);

    a.remove(9);
    EXPECT_TRUE(a.search(9) == nullptr);
    EXPECT_EQ(a.search(11)->leftSuccessor, a.search(10));
    EXPECT_EQ(a.search(11)->rightSuccessor, a.search(12));
    EXPECT_TRUE(a.search(11)->balanceFactor == 0);
}

TEST(AvlTreeTest, RemoveNode_TwoLeafsAndHeightQ0_RS_Simple) {
    AvlTree a;
    a.add(10);
    a.add(11);

    EXPECT_TRUE(a.search(10)->balanceFactor == 1);
    a.remove(11);
    EXPECT_TRUE(a.search(11) == nullptr);
    EXPECT_TRUE(a.search(10)->balanceFactor == 0);
    EXPECT_TRUE(a.search(10)->leftSuccessor == nullptr && a.search(10)->rightSuccessor == nullptr);
}

TEST(AvlTreeTest, RemoveNode_TwoLeafsAndHeightQ1_RS_Simple) {
    AvlTree a;
    a.add(10);
    a.add(11);
    a.add(9);

    EXPECT_TRUE(a.search(10)->balanceFactor == 0);
    a.remove(11);
    EXPECT_TRUE(a.search(10)->balanceFactor == -1);
    EXPECT_TRUE(a.search(11) == nullptr);
}

TEST(AvlTreeTest, RemoveNode_TwoLeafsAndHeightQ2_RS_Rotate) {
    AvlTree a;
    a.add(10);
    a.add(11);
    a.add(9);
    a.add(8);

    EXPECT_TRUE(a.search(10)->balanceFactor == -1);
    a.remove(11);
    EXPECT_TRUE(a.search(10)->balanceFactor == 0);
    EXPECT_TRUE(a.search(8) == a.search(9)->leftSuccessor);
    EXPECT_TRUE(a.search(10) == a.search(9)->rightSuccessor);
}

TEST(AvlTreeTest, RemoveNode_TwoSuccessors_Root) {
    AvlTree a;
    a.add(2);
    a.add(1);
    a.add(3);
    a.add(4);

    EXPECT_EQ(nullptr, a.search(2)->predecessor);

    a.remove(2);
    EXPECT_EQ(nullptr, a.search(2));
    EXPECT_EQ(nullptr, a.search(3)->predecessor);
    EXPECT_EQ(a.search(1), a.search(3)->leftSuccessor);
    EXPECT_EQ(a.search(4), a.search(3)->rightSuccessor);
}

TEST(AvlTreeTest, RemoveNode_TwoSuccessors) {
    AvlTree a;
    a.add(3);
    a.add(2);
    a.add(5);
    a.add(1);
    a.add(4);
    a.add(6);

    EXPECT_EQ(a.search(3), a.search(5)->predecessor);

    a.remove(5);
    EXPECT_EQ(nullptr, a.search(5));
    EXPECT_EQ(a.search(3), a.search(6)->predecessor);
    EXPECT_EQ(a.search(4), a.search(6)->leftSuccessor);
}


//TEST(AvlTreeTest, UpOut_TwoSuccessors) {
//    AvlTree a;
//    a.add(3);
//    a.add(2);
//    a.add(5);
//    a.add(1);
//    a.add(4);
//    a.add(6);
//
//    EXPECT_EQ(a.search(3), a.search(5)->predecessor);
//
//    a.remove(5);
//    EXPECT_EQ(nullptr, a.search(5));
//
//    EXPECT_EQ(-1, a.search(6)->balanceFactor);
//}
