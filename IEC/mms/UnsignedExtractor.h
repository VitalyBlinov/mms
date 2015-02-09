//-----------------------------------------------------------------------------
// <copyright file="UnsignedExtractor.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/13 06:34:32</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// unsigned integer extractor
//-----------------------------------------------------------------------------
#pragma once
#include "FetchOctet.h"
#include "TagExtractor.h"
#include "LengthExtractor.h"
#include "MMSTags.h"
namespace MMS
{
    namespace Extractors
    {
        namespace Details
        {
            /************************************//**
             * \brief Extracts unsigned integer value
             *
             * \tparam T  -  either unsigned char, unsigned short, unsigned int, unsigned long or unsigned long long
             *
             * \details This function implements MMS-specific extension to
             * ASN.1. Latter does not define special rules for unsigned integers,
             * while MMS makes a special case for such numbers
             *
             * \note This function must not be used to fetch signed integers
             *
             ****************************************/
            template <class Context, class T>
            inline bool fetchUnsignedValue(Context& _ctx, T& _Value, unsigned int _length)
            {
                auto ptr = fetchOctets(_ctx, _length);
                if (ptr)
                {
                    _Value = 0;
                    for (auto idx = 0; idx != _length; ++idx)
                    {
                        _Value = (_Value << 8) | ptr[idx];
                    }
                    return true;
                }
                else
                {
                    return false;
                }
            }
            /************************************//**
             * \brief Extracts unsigned integers
             *
             * \tparam T  -  either unsigned char, unsigned short, unsigned int, unsigned long or unsigned long long
             *
             ****************************************/
            template <class Context, class T>
            inline bool fetchUnsigned(Context& _ctx, T& _Value)
            {
                if (checkTag(_ctx, _Value))
                {
                    unsigned int _len = 0;
                    if (fetchLength(_ctx, _len))
                    {
                        if (sizeof(T) >= _len)
                        {
                            return fetchUnsignedValue(_ctx, _Value, _len);
                        }
                    }
                }

                return false;
            }

           /************************************//**
            * \brief Integer type extractors
            *
            * \details extracts signed Integer value from the fetch context.
            *
            * \returns True if value is successfully extracted. False otherwise.
            *
            ****************************************/
            ///@{
            template <class Context>
            bool extract(Context& _ctx, unsigned char& _Value)
            {
                return fetchUnsigned(_ctx, _Value);
            };

            template <class Context>
            bool extract(Context& _ctx, unsigned short& _Value)
            {
                return fetchUnsigned(_ctx, _Value);
            };

            template <class Context>
            bool extract(Context& _ctx, unsigned int& _Value)
            {
                return fetchUnsigned(_ctx, _Value);
            };

            template <class Context>
            bool extract(Context& _ctx, unsigned long& _Value)
            {
                return fetchUnsigned(_ctx, _Value);
            };

            template <class Context>
            bool extract(Context& _ctx, unsigned long long& _Value)
            {
                return fetchUnsigned(_ctx, _Value);
            };
            ///@}
        }
    }
}

