//-----------------------------------------------------------------------------
// <copyright file="FloatEmitter.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/10 00:50:04</created>
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
             * \brief Emits float (single precision)
             *
             * \details
             *
             ****************************************/
            template <class Context>
            Context&& emitFloat(Context&& _ctx, float _Value)
            {
                auto arr = reinterpret_cast<const unsigned char*>(&_Value);
                for (auto idx = sizeof(float); idx !=0; --idx)
                {
                    _ctx = MMS::Emitters::emitOctet(_ctx, arr[idx-1]);
                }
                return MMS::Emitters::emitOctet(_ctx, 0x80);
            }

        }
        ///	\brief Floating-point type emitter
        /// \details in MMS, floating-point type is represented
        /// according to IEEE 754 single precision with an additional leading
        /// byte or information octet that may carry additional information about
        /// the value. It can indicate whether the format is binary or decimal, special
        /// value (NaN, INF) and may also be used to indicate the base for encoding.
        /// For simplicity's sake, this emitter always emits the float as it is, with
        /// no fuzz. 
        template <class Context>
        Context&& emit(Context&& _ctx, float _Value)
        {
            auto oldContextSize = MMS::getContextSize(_ctx);
            _ctx = Details::emitFloat(_ctx, _Value);
            return std::move(emitTag(emitLength(_ctx, oldContextSize - MMS::getContextSize(_ctx)), _Value));
        };
    }
}

