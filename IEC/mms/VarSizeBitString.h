//-----------------------------------------------------------------------------
// <copyright file="VarSizeBitString.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/24 04:47:07</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include <bitset>
#include "MMSTags.h"
#include "UniversalClass.h"
#include "FixedSizeBitString.h"
namespace MMS
{
    namespace DataTypes
    {
        /************************************//**
         * \brief Variable size bitset
         *
         * \details Fixed-length storage for bit strings
         *  of application-defined length. Allocates reasonable
         *  amount for the data and allows for length of 
         *  the bit set to be specified at run-time within
         *  the limits of storage.
         *
         ****************************************/
        class VarSizeBitString
        {
        public:
            typedef std::bitset<128> value_type;
            /************************************//**
             * \brief Default c'tor
             *
             * \details default constructor assumes empty string
             ****************************************/
            VarSizeBitString(
                size_t _length  = 0
                );

            operator const value_type& () const;
            const value_type& GetBitSet() const;
            operator value_type& ();
            value_type& GetBitSet();
            /************************************//**
             * \brief Get number of bits in the set
             *
             * \note Normally, the bitset is much larger than it
             * needs to be. This function returns number of significant bits in
             * a set.
             *
             * \returns Number of used bits in the bitset. 
             *
             ****************************************/
            std::size_t size() const;
            /************************************//**
            * \brief Equals operators
            * \note template operator taking FixedSizeBitString isn't exactly efficient
            *   as it has to perform bit-to-bit comparison of two arrays
            ****************************************/
            ///@{
            bool operator == (const VarSizeBitString& _rhs) const;

            template <int N>
            bool operator == (const FixedSizeBitString<N>& _rhs) const
            {
                if (m_length == N)
                {
                    for (std::size_t i = 0; i !=m_length; ++i)
                    {
                        if (m_flags[i]!=_rhs.GetBitSet()[i])
                        {
                            return false;
                        }
                    }
                    return true;
                }
                else
                {
                    return false;
                }
            }
            ///@}
            /************************************//**
             * \brief Subscript mutable access
             ****************************************/
            value_type::reference operator [](std::size_t _pos);
            /************************************//**
             * \brief Subscript const access
             ****************************************/
            bool operator [](std::size_t _pos) const;
        private:
            std::bitset<128> m_flags;
            std::size_t m_length;
        };
    }

    namespace Tags
    {
        MMS_TAG_TYPE_DEF(MMS::DataTypes::VarSizeBitString, MMS_TAGS::BITSTRING);
    }
}

namespace ASN1
{
    namespace Tags
    {
        ASN_TAG_TYPE_DEF(MMS::DataTypes::VarSizeBitString, EN_UNIVERSAL_CLASS::BITSTRING);
    }
}