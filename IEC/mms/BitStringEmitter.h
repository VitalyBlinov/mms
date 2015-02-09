//-----------------------------------------------------------------------------
// <copyright file="BitStringEmitter.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/09 03:13:51</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <bitset>
#include "LengthEmitter.h"
#include "EmitOctet.h"
#include "MMSTags.h"
#include "TagEmitter.h"
#include "FixedSizeBitString.h"
#include "VarSizeBitString.h"
#include "ContextMisc.h"

namespace MMS
{
    namespace Emitters
    {
        namespace Details
        {
            /************************************//**
             * \brief Emits the context of bit string
             *
             * \tparam S - type of the bitstring. Could be 
             * std::vector<bool> or std::bitset
             *
             ****************************************/
            template <class Context, class S>
            inline Context&& emitBitStringContents(Context&& _ctx, const S& _Value)
            {
                if (_Value.size() == 0)
                {
                    return std::move(_ctx);
                }
                else
                {
                    unsigned char unusedBits = (8 - _Value.size() % 8) %8;
                    unsigned char _byte = 0;
                    auto totalBits = _Value.size() + unusedBits;
                    auto currentBitIndex = totalBits;
                    while (currentBitIndex !=0)
                    {
                        if (currentBitIndex <= _Value.size())
                        {
                            _byte = _byte | (_Value[currentBitIndex-1] << (totalBits - currentBitIndex)%8);
                        }
                        --currentBitIndex;
                        if (currentBitIndex % 8 == 0)
                        {
                            _ctx = MMS::Emitters::emitOctet(_ctx, _byte);
                            _byte = 0;
                        }
                    }
                    // now we have to emit number of unused bits
                    return std::move(MMS::Emitters::emitOctet(_ctx, unusedBits));
                }
            };
        }
        /************************************//**
         * \brief Bit string emitter
         *
         * \details Emits bit string
         *
         ****************************************/
        template <class Context>
        inline Context&& emit(Context&& _ctx, const std::vector<bool>& _Value)
        {
            auto oldContextSize = MMS::getContextSize(_ctx);
            _ctx = Details::emitBitStringContents(_ctx, _Value);
            return std::move(emitTag(std::forward<Context>(emitLength(_ctx, oldContextSize - MMS::getContextSize(_ctx))), _Value));
        };

        /************************************//**
         * \brief Bit string emitter
         *
         * \details Emits bit string
         *
         ****************************************/
        template <class Context, std::size_t S>
        inline Context&& emit(Context&& _ctx, const std::bitset<S>& _Value)
        {
            auto oldContextSize = MMS::getContextSize(_ctx);
            _ctx = Details::emitBitStringContents(_ctx, _Value);
            return std::move(emitTag(emitLength(_ctx, oldContextSize - MMS::getContextSize(_ctx)), _Value));
        };
         /************************************//**
         * \brief Bit string emitter
         *
         * \details Emits bit string defined as Fixed size bit string
         *
         ****************************************/
        template <class Context, std::size_t S>
        inline Context&& emit(Context&& _ctx, const ::MMS::DataTypes::FixedSizeBitString<S>& _Value)
        {
            auto oldContextSize = MMS::getContextSize(_ctx);
            _ctx = Details::emitBitStringContents(_ctx, _Value.GetBitSet());
            return std::move(emitTag(emitLength(_ctx, oldContextSize - MMS::getContextSize(_ctx)), _Value));
        };
        /************************************//**
         * \brief Bit string emitter
         *
         * \details Emits bit string defined as Variables size bit string
         *
         ****************************************/
        template <class Context>
        inline Context&& emit(Context&& _ctx, const ::MMS::DataTypes::VarSizeBitString& _Value)
        {
            auto oldContextSize = MMS::getContextSize(_ctx);
            _ctx = Details::emitBitStringContents(_ctx, _Value);
            return std::move(emitTag(emitLength(_ctx, oldContextSize - MMS::getContextSize(_ctx)), _Value));
        };


    }
}
