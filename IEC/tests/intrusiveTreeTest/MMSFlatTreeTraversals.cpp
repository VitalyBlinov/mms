//-----------------------------------------------------------------------------
// <copyright file="MMSFlatTreeTraversals.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/06 09:29:38</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <algorithm>
#include "MMSFlatTree.h"
#include "IElementID.h"

/************************************//**
 * \brief Test fixture class
 * \details Check how easy it is to traverse the tree
 ****************************************/
class MMSFlatTreeTraversals: public testing::Test
{

public:
    typedef Storage::MMSFlatTree<std::string> TestFlatTree;
    TestFlatTree m_CUT;
    MMSFlatTreeTraversals():
            m_CUT(1024)
    {
        auto where = m_CUT.Insert(std::string("First"), nullptr);
        auto first = where;
        where = m_CUT.Insert(std::string("Second"), where);
        where = m_CUT.Insert(std::string("Third"), where);
        where = m_CUT.Insert(std::string("Second 2"), first, where);
        auto second2 = where;
        where = m_CUT.Insert(std::string("Third 2"), where, where);
        where = m_CUT.Insert(std::string("Third 3"), second2, where);
        where = m_CUT.Insert(std::string("First 2"), nullptr, where);
    }

};
/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(MMSFlatTreeTraversals, TestFindOne)
{
    auto iter = std::find_if(m_CUT.begin(), m_CUT.end(), [](const TestFlatTree::Node& _node) -> bool {
        return _node._value == "First";
    });

    ASSERT_EQ(m_CUT.begin() + 1, iter);
}

TEST_F(MMSFlatTreeTraversals, TestFindStructureEnd)
{
    auto _begin = std::find_if(m_CUT.begin(), m_CUT.end(), [](const TestFlatTree::Node& _node) -> bool {
        return _node._value == "First";
    });

    auto _end = std::find_if(_begin + 1, m_CUT.end(), [_begin](const TestFlatTree::Node& _node) -> bool {
        return _begin->_level == _node._level;
    });

    ASSERT_EQ(m_CUT.begin() + 1, _begin);
    ASSERT_EQ("First 2", _end->_value);
}


// As a matter of fact, hierarchical traversal is not needed at all...
TEST_F(MMSFlatTreeTraversals, TestTraverse)
{
    auto _begin = std::find_if(m_CUT.begin(), m_CUT.end(), [](const TestFlatTree::Node& _node) -> bool {
        return _node._value == "First";
    });

    auto _end = std::find_if(_begin + 1, m_CUT.end(), [_begin](const TestFlatTree::Node& _node) -> bool {
        return _begin->_level == _node._level;
    });

    EXPECT_EQ(m_CUT.begin() + 1, _begin);
    EXPECT_EQ("First 2", _end->_value);

    for (auto itr = _begin; itr != _end; ++itr)
    {

    }
}

namespace
{
    /************************************//**
     * \brief Element ID class
     ****************************************/
    class ID: public Storage::IElementID
    {
        std::string m_name;
    public:
        ID(std::string&& _name):
                m_name(std::move(_name))
        {

        }


        virtual const char* GetName() const
        {
            return m_name.c_str();
        }

    };
}