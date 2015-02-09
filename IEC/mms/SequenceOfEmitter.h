//-----------------------------------------------------------------------------
// <copyright file="SequenceOfEmitter.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/30 04:52:17</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once

namespace MMS
{
    namespace Emitters
    {
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
            auto remaining = getContextSize(_ctx);
            It emitEnd = _begin;
            while (emitEnd != _end)
            {
                auto required = evaluate(_ctx, *emitEnd);
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
            for (auto itr = std::reverse_iterator<It>(emitEnd); itr != std::reverse_iterator<It>(_begin); ++itr)
            {
                _ctx = emit(std::forward<Context>(_ctx), *itr);
            }
            return std::make_pair(std::move(_ctx), emitEnd);
        }
    }
}

