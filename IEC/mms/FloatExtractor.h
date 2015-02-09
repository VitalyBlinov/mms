//-----------------------------------------------------------------------------
// <copyright file="FloatExtractor.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/13 08:48:03</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// Float type extractor
//-----------------------------------------------------------------------------
#pragma once
#include <limits>
#include "MMSTags.h"
#include "FetchContext.h"
#include "LengthExtractor.h"
namespace MMS
{
    namespace Extractors
    {
        namespace Details
        {
            /************************************//**
             * \brief Extracts float value
             *
             * \details This function implements MMS-specific extension to
             * ASN.1. Latter does not define special rules for unsigned integers,
             * while MMS makes a special case for such numbers
             *
             * \note This function must not be used to fetch signed integers
             *
             ****************************************/
            template <class Context>
            inline bool fetchFloatValue(Context& _ctx, float& _Value)
            {
                if (!checkTag(_ctx, _Value))
                {
                    return false;
                }
                unsigned int _length = 0;
                if (!fetchLength(_ctx, _length))
                {
                    return false;
                }
                if (_length !=0)
                {
                    auto ptr = fetchOctets(_ctx, _length);
                    if (ptr[0] == 0x80)     // No fuzz, just four octets following
                    {
                        if (_length == sizeof(float)+1)
                        {
                            memcpy(&_Value, ptr+1, sizeof(float));
                            return true;
                        }
                    }
                    else if (ptr[0] == 0x40)    // Special values (NAN, INF). WE only support NAN
                    {
                        _Value = std::numeric_limits<float>::quiet_NaN();
                        return true;
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
            bool extract(Context& _ctx, float& _Value)
            {
                return fetchFloatValue(_ctx, _Value);
            };
        }
    }
}

