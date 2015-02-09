//-----------------------------------------------------------------------------
// <copyright file="TagExtractor.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 22:08:14</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "ContextMisc.h"
#include "FetchOctet.h"
#include "TagEmitter.h"
#include "ASN1Tag.h"
namespace MMS
{
    namespace Extractors
    {
        ///	\brief Check tag helper function
        /// \details Checks if Context class defines NO_TAG enum value.
        /// If such enum exists, no tag is extracted and no validation is performed
        /// \tparam Context context type
        /// \returns False if context enables tags and extracted tag is not valid or cannot be extracted. True otherwise
        template <class Context, typename T>
        inline bool checkTag(Context& _ctx, T& _what)
        {
            if (MMS::tagEnabled(_ctx))
            {
                unsigned char extracted = 0;
                auto _tag = decltype(MMS::Emitters::Details::traits_resolver().get(_ctx))().getTag(_what);
                if (MMS::Extractors::fetchOctet(_ctx, extracted))
                {
                    return _tag == extracted;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return true;
            }
        }
        /************************************//**
         * \brief Skip tag helper function
         *
         * \details Used when the whole TLV is to be skipped. Assumes nothing,
         * supports long version of tag
         *
         ****************************************/
        template <class Context>
        inline bool skipTag(Context& _ctx)
        {
            if (MMS::tagEnabled(_ctx))
            {
                ASN1::TagValue val;

                extract(_ctx, val);

            }
            return true;
        }
    }
}

