//-----------------------------------------------------------------------------
// <copyright file="IntegerEmitter.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/29 00:17:14</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "LengthEmitter.h"
#include "EmitOctet.h"
#include "MMSTags.h"
#include "TagEmitter.h"

namespace MMS
{
    namespace Emitters
    {
        namespace Details
        {
            /************************************//**
             * \brief Emits an integer value
             *
             * \tparam T  -  either char, short, int, long or long long
             *
             * \details This function implements ASN.1 logic for emitting
             * signed integers. It takes care of positive and 
             * negative numbers and caters for an important case when
             * leading bit of the leading octet is set, but the number is positive and 
             * leading bit of the leading octet is not set for negative numbers. See ASN.1
             * description for more details
             * \note This function must not be used to emit unsigned integers
             *
             ****************************************/
            template <class Context, class T>
            inline Context&& emitIntegerValue(Context&& _ctx, T _Value)
            {
                T _positive = _Value<0?~_Value:_Value;
                while (_positive != 0)
                {
                    unsigned char octet = _Value & 0xFF;
                    _ctx = emitOctet(_ctx, octet);
                    _Value = _Value >> 8;
                    _positive = _positive >> 8;
                    if (_positive == 0)
                    {
                        if (_Value != _positive)           // negative number
                        {
                            if ((octet & 0x80) != 0x80)    // need to supplement high bits by adding octet with all bits set
                            {
                                return emitOctet(_ctx, 0xFF);
                            }
                        }
                        else                               // positive number
                        {
                            if ((octet & 0x80) == 0x80)    // need to add trailing zero octet
                            {
                                return emitOctet(_ctx, 0);
                            }
                        }
                    }
                }
                return _ctx;
            }
            /************************************//**
             * \brief Emits integer
             *
             * * \tparam T  -  either char, short, int, long or long long
             *
             ****************************************/
            template <class Context, class T>
            inline Context&& emitInteger(Context&& _ctx, T _Value)
            {
                auto oldSize = MMS::getContextSize(_ctx);
                _ctx = emitIntegerValue(_ctx, _Value);
                return std::move(emitTag(emitLength(_ctx, oldSize - MMS::getContextSize(_ctx)), _Value));
            }
            
        }
        ///	\brief Integer type emitter
        /// \details Emits an integer according to the ASN.1 rules. This means that
        /// it ensures that there is no confusion over most signed/unsigned; leading zero byte
        /// is added if the most significant byte is set.
        ///@{
        template <class Context>
        Context&& emit(Context&& _ctx, int _Value)
        {
            return std::move(Details::emitInteger(_ctx, _Value));
        };

        template <class Context>
        Context&& emit(Context&& _ctx, char _Value)
        {
            return std::move(Details::emitInteger(_ctx, _Value));
        };

        template <class Context>
        Context&& emit(Context&& _ctx, short _Value)
        {
            return std::move(Details::emitInteger(_ctx, _Value));
        };

        template <class Context>
        Context&& emit(Context&& _ctx, long _Value)
        {
            return std::move(Details::emitInteger(_ctx, _Value));
        };

        template <class Context>
        Context&& emit(Context&& _ctx, long long _Value)
        {
            return std::move(Details::emitInteger(_ctx, _Value));
        };

        ///@}
    }
}

