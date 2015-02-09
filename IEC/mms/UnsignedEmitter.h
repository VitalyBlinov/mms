//-----------------------------------------------------------------------------
// <copyright file="UnsignedEmitter.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/29 18:17:52</created>
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
             * \brief Emits an unsigned integer value
             *
             * \tparam T  -  either unsigned char, unsigned short, unsigned int, unsigned long or unsigned long long
             *
             * \details Unlike ASN.1, MMS defines special case for unsigned integers.
             *  because there is no sign, the encoding rules are much simpler and
             * there is no need to check the value of the most significant bit as
             * this will not cause misinterpretation of positive number as negative and vice versa
             *
             ****************************************/
            template <class Context, class T>
            inline Context&& emitUnsignedValue(Context&& _ctx, T _Value)
            {
                while (_Value != 0)
                {
                    _ctx = emitOctet(_ctx, _Value & 0xFF);
                    _Value = _Value >> 8;
                }
                return _ctx;
            }
            template <class Context>
            inline Context&& emitUnsignedValue(Context&& _ctx, unsigned char _Value)
            {
                if (_Value != 0)
                {
                    return emitOctet(_ctx, _Value);
                }
                else
                {
                    return _ctx;
                }
            }
            /************************************//**
             * \brief Emits unsigned integer
             *
             * * \tparam T - either unsigned char, unsigned short, unsigned int, unsigned long or unsigned long long
             *
             ****************************************/
            template <class Context, class T>
            inline Context&& emitUnsignedInteger(Context&& _ctx, T _Value)
            {
                auto oldSize = MMS::getContextSize(_ctx);
                _ctx = emitUnsignedValue(_ctx, _Value);
                return std::move(emitTag(emitLength(_ctx, oldSize - MMS::getContextSize(_ctx)), _Value));
            }
            
        }
        ///	\brief Unsigned Integer type emitter
        /// \details Simply emits an unsigned integer number
        ///@{
        template <class Context>
        Context&& emit(Context&& _ctx, unsigned int _Value)
        {
            return std::move(Details::emitUnsignedInteger(_ctx, _Value));
        };

        template <class Context>
        Context&& emit(Context&& _ctx, unsigned char _Value)
        {
            return std::move(Details::emitUnsignedInteger(_ctx, _Value));
        };

        template <class Context>
        Context&& emit(Context&& _ctx, unsigned short _Value)
        {
            return std::move(Details::emitUnsignedInteger(_ctx, _Value));
        };

        template <class Context>
        Context&& emit(Context&& _ctx, unsigned long _Value)
        {
            return std::move(Details::emitUnsignedInteger(_ctx, _Value));
        };

        template <class Context>
        Context&& emit(Context&& _ctx, unsigned long long _Value)
        {
            return std::move(Details::emitUnsignedInteger(_ctx, _Value));
        };
        ///@}
    }

}

