//-----------------------------------------------------------------------------
// <copyright file="MMSFlatTreeTest.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/06 08:07:49</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "MMSFlatTree.h"

/************************************//**
 * \brief Test fixture class
 ****************************************/
class MMSFlatTreeTest: public testing::Test
{

public:
    typedef Storage::MMSFlatTree<std::string> TestFlatTree;
    TestFlatTree m_CUT;
    MMSFlatTreeTest():
            m_CUT(1024)
    {
        
    }

};
/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(MMSFlatTreeTest, TestInsertAtRoot)
{
	auto where = m_CUT.Insert(std::string("First"), nullptr);
    auto first = where;
}
TEST_F(MMSFlatTreeTest, TestAddSecond)
{
    auto where = m_CUT.Insert(std::string("First"), nullptr);
    auto first = where;
    ASSERT_NE(nullptr, where);
    where = m_CUT.Insert(std::string("Second"), where);
}

TEST_F(MMSFlatTreeTest, TestAddThird)
{
    auto where = m_CUT.Insert(std::string("First"), nullptr);
    auto first = where;
    ASSERT_NE(nullptr, where);
    where = m_CUT.Insert(std::string("Second"), where);
    ASSERT_NE(nullptr, where);
    where = m_CUT.Insert(std::string("Third"), where);
    ASSERT_NE(nullptr, where);
}

TEST_F(MMSFlatTreeTest, TestAddSecond2)
{
    auto where = m_CUT.Insert(std::string("First"), nullptr);
    auto first = where;
    ASSERT_NE(nullptr, where);
    where = m_CUT.Insert(std::string("Second"), where);
    ASSERT_NE(nullptr, where);
    where = m_CUT.Insert(std::string("Third"), where);
    ASSERT_NE(nullptr, where);
    where = m_CUT.Insert(std::string("Second 2"), first, where);
    ASSERT_NE(nullptr, where);
}

TEST_F(MMSFlatTreeTest, TestNegative)
{
    auto where = m_CUT.Insert(std::string("First"), nullptr);
    auto first = where;
    ASSERT_NE(nullptr, where);
    where = m_CUT.Insert(std::string("Second"), where);
    ASSERT_NE(nullptr, where);
    where = m_CUT.Insert(std::string("Third"), where);
    ASSERT_NE(nullptr, where);
    where = m_CUT.Insert(std::string("Second 2"), first, where);
    ASSERT_NE(nullptr, where);
    where = m_CUT.Insert(std::string("First"), nullptr);
    ASSERT_NE(nullptr, where);
    where = m_CUT.Insert(std::string("Second 3"), first, where);    // This would break the tree
    ASSERT_EQ(nullptr, where);
}
