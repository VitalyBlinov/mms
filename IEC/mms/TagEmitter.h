//-----------------------------------------------------------------------------
// <copyright file="TagEmitter.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/28 02:07:27</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "EmitOctet.h"
#include "ContextTraits.h"
#include "ASN1Tag.h"
namespace MMS
{
    namespace Emitters
    {
        namespace Details
        {
            struct traits_resolver
            {
                template <class T>
                inline typename std::enable_if<!std::is_same<typename std::remove_reference<T>::type, MMS::Emitters::Details::EmitContextBase>::value, typename std::remove_reference<T>::type::context_traits>::type get( const T& _val) { return T::context_traits();};

                template <class T>
                inline typename std::enable_if<std::is_same<typename std::remove_reference<T>::type, MMS::Emitters::Details::EmitContextBase>::value, MMS::ContextTraits<false>>::type get( const T& _val) { return MMS::ContextTraits<false>();};
                
            };
        }
        /************************************//**
         * \brief Template tag emitter
         *
         * \details Uses context traits to resolve correct
         * tag for given  type. This is preferred method for 
         * emitting the tags
         *
         ****************************************/
        template <class Context, typename T>
        inline Context&& emitTag(Context&& _ctx, const T& _val)
        {
            if (MMS::tagEnabled(_ctx))
            {
                return std::move(MMS::Emitters::emitOctet(std::forward<Context>(_ctx), decltype(Details::traits_resolver().get(_ctx))().getTag(_val)));
            }
            else
            {
                return std::move(_ctx);
            }
        }
        /************************************//**
         * \brief Evaluates number of octets required to emit tag in given context
         * \note Assumes tag value is less than 31.
         ****************************************/
        template <class Context, typename T>
        inline std::size_t evaluateTag(const Context& _ctx, const T& _val)
        {
            //static_assert(decltype(Details::traits_resolver().get(_ctx))().getTag(_val) < 31, "Evaluate tag function does not work for tag values greater than 31");
            if (MMS::tagEnabled(_ctx))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        /************************************//**
         * \brief Emits context-specific tag
         *
         * \details used when emitting MMS PDUs and PDU details.
         *
         ****************************************/
        template <class Context>
        Context&& emitContextSpecificTag(Context&& _ctx, unsigned char _tag)
        {
            return MMS::Emitters::emitOctet(_ctx, _tag | 0x80);
        }
    }
}

