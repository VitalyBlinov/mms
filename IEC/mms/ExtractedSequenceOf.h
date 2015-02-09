//-----------------------------------------------------------------------------
// <copyright file="ExtractedSequenceOf.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/02 03:57:53</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "ContextMisc.h"
#include "FetchContext.h"
#include <vector>
#include "skipTLV.h"
#include "TagExtractor.h"

namespace MMS
{
    namespace DataTypes
    {
        /************************************//**
         * \brief Generic SEQUENCE OF structure
         *
         * \details Represents extracted SEQUENCE OF <T>.
         * Allows to implement a paradigm when a "SEQUENCE OF" can
         * be extracted from the PDU without having to process this 
         * sequence first so the data can be extracted later by whatever
         * is going to process this PDU further. That is to help protocol
         * layer to stay away from any memory management issues.
         * \note Does not own any data, the data must
         * be copied to permanent storage if needed to retain
         * \note Enforces explicit context traits
         *
         ****************************************/
        template <class C, class T>
        class SequenceOf
        {
        private:
            typedef typename C::tExplicit contextType;
            typename contextType m_context;
        public:
            typedef std::false_type implicit;   ///< Needed to use resolve_implicit context trickery
            /************************************//**
             * \brief Iterator type for this container adapter
             ****************************************/
            class const_iterator
            {
            private:
                contextType m_ctx;
                T m_value;
            public:
                typedef typename T value_type;
                typedef typename const T& const_reference;
                typedef typename const T* pointer;
                typedef std::forward_iterator_tag iterator_category;

                const_iterator(
                    contextType _context
                    ):
                    m_ctx(_context)
                {
                    while (getContextSize(_context) != 0 && !fetch(_context, m_value))
                    {
                        skipTLV(_context);
                        m_ctx = _context;
                    }
                };

                bool operator==(const const_iterator& _cmp) const
                {
                    return m_ctx == _cmp.m_ctx;
                };

                bool operator!=(const const_iterator& _cmp) const
                {
                    return ! (*this == _cmp);
                };

                const_iterator& operator++()
                {
                    contextType _copy(m_ctx);
                    skipTLV(_copy);
                    *this = const_iterator(_copy);
                    return *this;
                };

                const_reference operator*() const
                {
                    return m_value;
                };

                pointer operator->() const
                {
                    return &m_value;
                };
            };

            typedef typename T value_type;

            /************************************//**
             * \brief constructor
             ****************************************/
            SequenceOf(
                C _context              ///< Context this sequence is encoded in
                ):
                m_context(_context)
            {

            };
            /************************************//**
             * \brief Default constructor
             ****************************************/
            SequenceOf()
            {

            };

            const_iterator begin() const
            {
                return const_iterator(m_context);
            };

            const_iterator end() const
            {
                contextType _copy(m_context);
                fetchOctets(_copy, getContextSize(_copy));
                return const_iterator(_copy);
            };
        };
        
    }

}

