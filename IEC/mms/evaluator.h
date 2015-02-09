//-----------------------------------------------------------------------------
// <copyright file="evaluator.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/29 03:50:54</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "ContextMisc.h"
namespace MMS
{
    namespace Emitters
    {
        /************************************//**
         * \brief Common evaluator
         *
         * \details Used to calculate number of octets
         *  that emitted value will require in target
         *  context.
         * \note Most data types need to provide
         *  specializations to make sure evaluation
         *  is done it most optimal way
         *
         * \returns number of octets emitted value will take
         *  in emit context
         *
         ****************************************/
        template <typename Context, typename T>
        inline std::size_t evaluate(const Context& _ctx, const T& _value)
        {
            Context copy(_ctx);
            auto oldSize = getContextSize(copy) - getNotEnoughOctetsCount(copy);
            copy = emit(copy, _value);
            return oldSize - getContextSize(copy) + getNotEnoughOctetsCount(copy);
        }
    }
}

