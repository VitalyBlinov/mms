//-----------------------------------------------------------------------------
// <copyright file="FixedSizeBitString.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 13:36:24</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include <bitset>
#include "MMSTags.h"
#include "UniversalClass.h"
namespace MMS
{
    /************************************//**
     * \brief Data types definition specific to MMS protocol stack
     ****************************************/
    namespace DataTypes
    {
        /************************************//**
         * \brief Fixed size bit-string
         *
         * \details Fixed size bit string is used 
         * to represent bit strings length of which 
         * is set in the standard, either MMS or IEC61850
         * For example, dbPos or Quality have fixed number
         * of bits.
         *
         * Uses std::bitset under the hood
         *
         ****************************************/
        template <std::size_t N>
        class FixedSizeBitString
        {
        public:
                typedef std::bitset<N> value_type;
                /************************************//**
                 * \brief Cast to bit string operator
                 *
                 * \details Allows to emit this thing
                 *
                 ****************************************/
                operator const value_type& () const
                {
                    return m_flags;
                }
                const value_type& GetBitSet() const
                {
                    return m_flags;
                }
                operator value_type& ()
                {
                    return m_flags;
                }
                value_type& GetBitSet()
                {
                    return m_flags;
                }
                /************************************//**
                 * \brief Equals operator
                 ****************************************/
                bool operator == (const FixedSizeBitString<N>& _rhs) const
                {
                    return m_flags == _rhs.m_flags;
                }
            protected:
                value_type m_flags;
        };
    }

    namespace Tags
    {
        // Defines MMS tag for this type
        template <std::size_t N> struct TagDef<MMS::DataTypes::FixedSizeBitString<N>>{enum {TAG = MMS_TAGS::BITSTRING};};
    }
}

namespace ASN1
{
    namespace Tags
    {
        // Defines ASN.1 tag for this type
        template <std::size_t N> struct TagDef<MMS::DataTypes::FixedSizeBitString<N>>{enum {TAG = EN_UNIVERSAL_CLASS::BITSTRING};};
    }
}