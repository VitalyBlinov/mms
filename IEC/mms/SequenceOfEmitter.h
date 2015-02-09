//-----------------------------------------------------------------------------
// <copyright file="SequenceOfEmitter.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/30 04:52:17</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Emitters for "sequence of"
//-----------------------------------------------------------------------------
#pragma once
#include "sequence.h"
#include "TagEmitter.h"
#include "LengthEmitter.h"
#include "ASN1Tag.h"
namespace MMS
{
    namespace Emitters
    {
        /************************************//**
         * \brief Emit sequence that definitely fits in the context
         *
         * \details
         *
         ****************************************/
        template <class Context, class It>
        inline Context emit(Context&& _ctx, const MMS::DataTypes::sequence<It>& _value)
        {
            auto oldSize = getContextSize(_ctx);
            auto expContext = forceExplicit(_ctx);
            for (auto itr = std::reverse_iterator<It>(_value.end()); itr != std::reverse_iterator<It>(_value.begin()); ++itr)
            {
                expContext = emit(std::forward<decltype(expContext)>(expContext), *itr);
            }
            _ctx = std::remove_reference<Context>::type(expContext);
            return emitTag(emitLength(std::forward<Context>(_ctx), oldSize - getContextSize(_ctx)), _value);
        }
        /************************************//**
         * \brief Emits the "sequence of"
         *
         * \details emits the sequence of values. Using evaluate
         * functionality, calculates the range which can be emitted
         * in the context without overflowing it and then emits that
         * range. Order is preserved.
         *
         * \returns A pair containing new context and 
         * an iterator to the first element that did
         * not fit in the context
         *
         * \tparam Context Emit context
         * \tparam It Bi-directional iterator defining the sequence.
         *
         ****************************************/
        template <class Context, class It>
        inline std::pair<typename std::remove_reference<Context>::type, It> emitSequence(
            Context&& _ctx,                             ///< Context to emit sequence to
            It _begin,                                  ///< start of the sequence
            It _end                                     ///< end of the sequence
            )
        {
            auto overhead = evaluateLength(_ctx, getContextSize(_ctx)) + evaluateTag(_ctx, 0);
            auto expContext = forceExplicit(_ctx);
            auto remaining = getContextSize(expContext) - overhead;
            It emitEnd = _begin;
            while (emitEnd != _end)
            {
                auto required = evaluate(expContext, *emitEnd);
                if (required > remaining)
                {
                    break;
                }
                else
                {
                    remaining -= required;
                    ++emitEnd;
                }
            }
            expContext = emit(std::forward<decltype(expContext)>(expContext), MMS::DataTypes::sequence<It>(_begin, emitEnd));
            return std::make_pair(std::move(std::remove_reference<Context>::type(expContext)), emitEnd);
        }
    }
}

