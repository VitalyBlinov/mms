//-----------------------------------------------------------------------------
// <copyright file="MMSFlatTree.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/03 04:07:40</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include <vector>

namespace Storage
{
    /************************************//**
     * \brief Flat or compressed MMS contents tree
     *
     * \details Uses bad-ass trickery to flatten the MMS
     * tree so it can be kept in a vector with minimal
     * overhead. In fact, the tree is organized in such way
     * when each node needs only one pointer to point
     * to its parent. Other pointers are not needed as the 
     * structure is taking continuous memory area
     *
     ****************************************/
    template <class T>
    class MMSFlatTree
    {
    public:
        /************************************//**
         * \brief Tree node type
         *
         * \details Surprisingly, tree node is a very simple
         *  structure that comprises a value and a level counter. 
         *  This is essentially
         *  sufficient to traverse flat tree correctly
         *
         ****************************************/
        struct Node
        {
            T _value;
            unsigned char _level;
            Node():
                _level(0)
            {

            }
        };
        /************************************//**
         * \brief Storage type
         ****************************************/
        typedef std::vector<Node> storage_type;
        /************************************//**
         * \brief Constructor
         *
         * \details Length of the tree (number of nodes) must be known
         * prior to construction!
         *
         ****************************************/
        MMSFlatTree( 
            std::size_t _size           ///< Number of nodes the tree must accommodate
            )
        {
            m_storage.resize(_size+1);  
        }
       
        //MMSFlatTree(const MMSFlatTree& other) = delete;
        //MMSFlatTree& operator = (const MMSFlatTree& other) = delete;

        /************************************//**
         * \brief Adds a child to a given node
         *
         * \details Attempts to insert a node in the tree. Newly inserted
         * node must belong to the same branch as the previously added node,
         * and the storage must not be full.
         *
         * \returns Pointer to inserted node. If node cannot be inserted,
         *  nullptr is returned.
         *
         ****************************************/
        Node* Insert(
            T&& _value,                     ///< Value of the node
            Node* _parent,                  ///< Parent of this node. If nullptr is supplied, added at top level (child of a root node)
            Node* _hint = nullptr           ///< hint node pointer; must be the pointer to the last inserted node
            )
        {
            if (_parent == nullptr)
            {
                _parent = &m_storage[0];    // Fist element of the storage is the root!
            }
            _hint = findSlot(_hint);        // Finds the first free slot
            if (_hint != nullptr)           // Free slot exists
            {
                // Now, we need to make sure that we are not inserting
                // a node that will break the tree. Newly inserted node's parent
                // must be a parent of current branch
                if (_parent == &m_storage[0] || checkAncestry(_hint - 1, _parent))
                {
                    _hint->_level = _parent->_level + 1;
                    _hint->_value = std::move(_value);
                    return _hint;
                }
                else
                {
                    return nullptr;         // Oh boy. The tree is screwed
                }
            }
            else
            {
                return nullptr;             // Not enough room. The number of nodes is incorrect, perhaps.
            }
        };
        /************************************//**
         * \brief Returns the beginning of the tree
         ****************************************/
        typename storage_type::iterator begin()
        {
            return m_storage.begin();
        }
        /************************************//**
         * \brief Returns one element past the end of the tree
         ****************************************/
        typename storage_type::iterator end()
        {
            return m_storage.end();
        }
    private:
        storage_type m_storage;
        /************************************//**
         * \brief Finds the first free slot in the tree
         ****************************************/
        Node* findSlot(
            Node* _hint = nullptr
            )
        {
            if (_hint == nullptr)
            {
                _hint = &m_storage[0] + 1;
            }
            while (_hint != &m_storage[0] + m_storage.size())
            {
                if (_hint->_level == 0)  // Free slot found
                {
                    return _hint;
                }
                ++_hint;
            }
            return nullptr;         //  Tree is full. Bugger off!
        }
        /************************************//**
         * \brief Checks that given parent exists in node's hierarchy
         * \returns True if nodes are related, i.e. _pParent is an ancestor of _pNode. False otherwise
         ****************************************/
        bool checkAncestry(
            Node* _pNode,
            Node* _pParent
            ) const
        {
            while (_pNode != nullptr)
            {
                if (_pNode == _pParent)
                {
                    return true;
                }
                else if (_pNode->_level == _pParent->_level)
                {
                    return false;
                }
                else
                {
                    --_pNode;
                }
            }
            return false;
        }

    };
    
}

