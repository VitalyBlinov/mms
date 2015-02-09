//-----------------------------------------------------------------------------
// <copyright file="BitStringExtractor.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/13 23:01:15</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "FetchContext.h"
#include "LengthExtractor.h"
#include "FetchOctet.h"
#include "FixedSizeBitString.h"
#include "VarSizeBitString.h"
#include "MMSTags.h"
namespace MMS
{
    namespace Extractors
    {
        namespace Details
        {
            /************************************//**
             * \brief Adjusts the bit string length to it can accept the extracted value
             *
             * \returns True if target bit string can be adjusted. This generic version always returns true
             *
             ****************************************/
            template <typename T>
            inline bool setBitStringLength(
                T& _what, 
                std::size_t _length
                )
            {
                std::swap(_what, T(_length));
                return true;
            }
            /************************************//**
             * \brief setBitStringLength specialization for std::bitset
             *
             * \returns True if target bit string can accept all the bits.
             * False otherwise
             *
             ****************************************/
            template <std::size_t S>
            inline bool setBitStringLength(
                std::bitset<S>& _what, 
                std::size_t _length
                )
            {
                if (_length <= S)
                {
                     _what.reset();
                     return true;
                }
                return false;
            }
            /************************************//**
             * \brief Fetches the contents of the bit string
             *
             * \tparam T - type of the bitstring. Could be 
             * std::vector<bool> or std::bitset
             *
             ****************************************/
            template <class Context, class T>
            inline bool fetchBitString(
                Context& _ctx, 
                T& _Value, 
                unsigned int _octets, 
                unsigned char _padding
                )
            {
                auto ptr = MMS::Extractors::fetchOctets(_ctx, _octets);
                if (ptr != nullptr)
                {
                    if (setBitStringLength(_Value, _octets*8 - _padding))
                    {
                        for (auto idx = 0; idx != _octets*8 - _padding; ++idx)
                        {
                            _Value[idx] = (ptr[idx/8] & (0x80 >> (idx % 8))) != 0;
                        }
                        return true;
                    }
                }
                return false;
            };
            /************************************//**
             * \brief Extracts length and padding value and forwards the call to fetchBitString
             ****************************************/
            template <class Context, class T>
            inline bool doExtractBitString(Context& _ctx, T& _Value)
            {
                if (checkTag(_ctx, _Value))
                {
                    unsigned int _length = 0;
                    if (fetchLength(_ctx, _length))
                    {
                        unsigned char _padding = 0;
                        if (fetchOctet(_ctx, _padding))
                        {
                            return fetchBitString(_ctx, _Value, _length-1, _padding);
                        }
                    }
                }
                return false;
            };

            /************************************//**
             * \brief Bit string extractor
             *
             * \details Extracts the bit string
             *
             ****************************************/
            ///@{
            template <class Context>
            inline bool extract(Context& _ctx, std::vector<bool>& _Value)
            {
                return doExtractBitString(_ctx, _Value);
            };

            template <class Context, std::size_t S>
            inline bool extract(Context& _ctx, std::bitset<S>& _Value)
            {
                return doExtractBitString(_ctx, _Value);
            };

            template <class Context, std::size_t S>
            inline bool extract(Context& _ctx, ::MMS::DataTypes::FixedSizeBitString<S>& _Value)
            {
                return doExtractBitString(_ctx, _Value.GetBitSet());
            };

            template <class Context>
            inline bool extract(Context& _ctx, ::MMS::DataTypes::VarSizeBitString& _Value)
            {
                return doExtractBitString(_ctx, _Value);
            };
            ///@}
        }
    }
}

