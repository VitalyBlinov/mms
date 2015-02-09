//-----------------------------------------------------------------------------
// <copyright file="skipTLV.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/03 02:10:42</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "TagExtractor.h"
#include "LengthExtractor.h"

namespace MMS
{
    namespace Extractors
    {
        /************************************//**
         * \brief Skips the TLV
         *
         * \details Skips the tag, extracts the length
         * and skips all octets of the value. If tag or length
         * cannot be extracted, skips the rest of the context, data
         * is damaged anyway
         *
         ****************************************/
        template <class Context>
        inline void skipTLV(Context& _ctx)
        {
            skipTag(_ctx);
            unsigned int _length = 0;
            if (fetchLength(_ctx, _length))
            {
                fetchOctets(_ctx, _length);
            }
            else
            {
                fetchOctets(_ctx, getContextSize(_ctx));
            }
        }
    }
}

