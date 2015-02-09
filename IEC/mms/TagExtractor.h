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
        /************************************//**
         * \brief Check Tag helper functions
         *
         * \details Use compile time template magic to 
         *  detect whether the context is implicit or explicit. Tag
         *  is extracted and compared to its expected value only if 
         *  context is explicit. Implicit context has no runtime overhead
         *
         ****************************************/
        ///@{
        template <class Context, typename T>
        inline typename std::enable_if<Context::context_traits::tImplicit::value, bool>::type checkTag(Context& _ctx, T& _what)
        {
            return true;    // Implicit context, no need to do anything
        }

        template <class Context, typename T>
        inline typename std::enable_if<!Context::context_traits::tImplicit::value, bool>::type checkTag(Context& _ctx, T& _what)
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
        ///@}
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

