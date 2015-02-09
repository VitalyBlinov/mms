//-----------------------------------------------------------------------------
// <copyright file="IntegerExtractor.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/13 05:33:57</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "LengthExtractor.h"
#include "MMSTags.h"
namespace MMS
{
    namespace Extractors
    {
        namespace Details
        {
            /************************************//**
             * \brief Extracts an integer value
             *
             * \tparam T  -  either char, short, int, long or long long
             *
             * \details This function implements ASN.1 logic when fetching
             * signed integers. It takes care of positive and 
             * negative numbers and caters for an important case when
             * leading bit of the leading octet is set, but the number is positive and 
             * leading bit of the leading octet is not set for negative numbers. See ASN.1
             * description for more details
             * \note This function must not be used to fetch unsigned integers
             *
             ****************************************/
            template <class Context, class T>
            inline bool fetchIntegerValue(Context& _ctx, T& _Value, unsigned int _length)
            {
                auto ptr = fetchOctets(_ctx, _length);
                if (ptr)
                {
                    unsigned int index = 0;
                    if (ptr[index] == 0)            // Positive special case
                    {
                        if (sizeof(T) < _length)
                        {
                            return false;
                        }
                        ++index;
                    }
                    else if (ptr[index] == 0xFF)     // Negative special case
                    {
                        if (sizeof(T) < _length - 1)
                        {
                            return false;
                        }
                        ++index;
                        _Value = ~0;
                    }
                    else if (sizeof(T) < _length)
                    {
                        return false;
                    }
                    else if (ptr[0] & 0x80)
                    {
                        _Value = ~0;
                    }
                    else
                    {
                        _Value = 0;
                    }
                    while (index != _length)
                    {
                        _Value = (_Value << 8) | ptr[index];
                        ++index;
                    }
                    return  true;
                }
                else
                {
                    return false;
                }
            }
            /************************************//**
             * \brief Emits integer
             *
             * \tparam T  -  either char, short, int, long or long long
             *
             ****************************************/
            template <class Context, class T>
            inline bool fetchInteger(Context& _ctx, T& _Value)
            {
                if (checkTag(_ctx, _Value))
                {
                    unsigned int _len = 0;
                    if (fetchLength(_ctx, _len))
                    {
                        return fetchIntegerValue(_ctx, _Value, _len);
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
            bool extract(Context& _ctx, char& _Value)
            {
                return fetchInteger(_ctx, _Value);
            };

            template <class Context>
            bool extract(Context& _ctx, short& _Value)
            {
                return fetchInteger(_ctx, _Value);
            };

            template <class Context>
            bool extract(Context& _ctx, int& _Value)
            {
                return fetchInteger(_ctx, _Value);
            };

            template <class Context>
            bool extract(Context& _ctx, long& _Value)
            {
                return fetchInteger(_ctx, _Value);
            };

            template <class Context>
            bool extract(Context& _ctx, long long& _Value)
            {
                return fetchInteger(_ctx, _Value);
            };
            ///@}
            
        }
    }
}

