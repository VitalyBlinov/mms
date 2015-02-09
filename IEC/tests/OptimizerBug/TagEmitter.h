//-----------------------------------------------------------------------------
// <copyright file="TagEmitter.h" company="big foot Software">
//      Copyright (c) 2014 big foot Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/28 02:07:27</created>
// <author>Vital</author>
// <summary>Project "Something went bad"</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "EmitOctet.h"
#include "ContextTraits.h"

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

            /************************************//**
             * \brief Emits the tag according to ASN.1 rules
             *
             * \details Most tags' values fit in lower 5 bits of the octet.
             *  For tag values greater than 31, long tag encoding should be used
             *
             ****************************************/
            template <class Context>
            inline Context&& emitTagValue(Context&& _ctx, unsigned int _tag)
            {
                if (_tag < 32)
                {
                    return std::move(MMS::Emitters::emitOctet(std::forward<Context>(_ctx), _tag));
                }
                else
                {
                    
                }
            }
        }
        /************************************//**
         * \brief Template tag emitter
         *
         * \details Users context traits to resolve correct
         * tag for given  type
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

