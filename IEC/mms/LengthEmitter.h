//-----------------------------------------------------------------------------
// <copyright file="LengthEmitter.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/27 09:11:40</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "EmitOctet.h"
namespace MMS
{
    namespace Emitters
    {
        ///	\brief Common length emitter
        /// \details Implements definite length value emitting. Supports
        /// short and long forms
        template <class Context>
        inline Context&& emitLength(
            Context&& _ctx,                     ///< Context
            unsigned int _length                ///< Length value to emit
            )
        {
            if (_length < 127)                  // Short form is possible
            {
                return std::move(emitOctet(_ctx, _length));
            }
            else                                // Oops... must use long form.
            {
                unsigned char _count = 0;
                while (_length != 0)
                {
                    _ctx = emitOctet(_ctx, _length);
                    ++_count;
                    _length = _length >> 8;
                }
                return std::move(emitOctet(_ctx, _count | 0x80));
            }
        }
        /************************************//**
         * \brief Evaluates number of octets required to emit length value
         *
         ****************************************/
        template <class Context>
        inline std::size_t evaluateLength(
            const Context& _ctx,                ///< Context
            unsigned int _length                ///< Length value to emit
            )
        {
            if (_length < 127)
            {
                return 1;
            }
            else
            {
                unsigned char _count = 0;
                while (_length != 0)
                {
                    ++_count;
                    _length = _length >> 8;
                }
                return _count + 1;
            }
        }
    }
}

