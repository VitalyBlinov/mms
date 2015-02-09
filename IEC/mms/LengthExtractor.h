//-----------------------------------------------------------------------------
// <copyright file="LengthExtractor.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 23:54:39</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "FetchOctet.h"
#include "TagExtractor.h"
namespace MMS
{
    namespace Extractors
    {        
        /************************************//**
         * \brief Length value fetcher
         *
         * \details Extracts length value from the 
         * context; supports both short and long forms
         *
         * \returns True if length was successfully extracted. False otherwise. If false
         * is returned, _length value is not modified. 
         *
         ****************************************/
        template <class Context>
        inline bool fetchLength(
            Context& _ctx,                      ///< Context
            unsigned int& _length               ///< [OUT] Length value
            )
        {
            unsigned char octet = 0;
            Context backup(_ctx);
            if (fetchOctet(_ctx, octet))
            {
                if (octet < 127)        // Short form
                {
                    _length = octet;
                    return  true;
                }
                else                    // Long form
                {
                    auto count = octet & 0x7F;
                    auto octets = fetchOctets(_ctx, count);
                    if (octets != nullptr)
                    {
                        _length = 0;
                        for (auto idx = 0; idx != count; ++idx)
                        {
                            _length = (_length << 8) | octets[idx];
                        }
                        return  true;
                    }
                }
            }
            _ctx = backup;
            return false;
        }
    }
}

