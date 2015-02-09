//-----------------------------------------------------------------------------
// <copyright file="OctetStringEmitter.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/13 23:47:28</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Octet string emitter
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <list>
#include <array>
#include "OctetStringExt.h"
namespace MMS
{
    namespace Emitters
    {
        namespace Details
        {
            /************************************//**
             * \brief Generic octet string emitter
             *
             * \details Emits octet string defined by the pair of iterators
             *
             ****************************************/
            template <class Context, class It>
            inline Context&& emitOctetString(Context&& _ctx, It _begin, It _end)
            {
                for (auto itr = std::reverse_iterator<It>(_end); itr != std::reverse_iterator<It>(_begin); ++itr)
                {
                    _ctx = emitOctet(std::forward<Context>(_ctx), *itr);
                }
                return _ctx;
            }
            /************************************//**
             * \brief Octet string emitter specialization
             *
             * \details Used when octet string is defined as continuous block of memory
             *
             ****************************************/
            template <class Context>
            inline Context&& emitOctetString(Context&& _ctx, const unsigned char* pPtr, std::size_t length)
            {
                return emitOctets(std::forward<Context>(_ctx), pPtr, length);
            }
            /************************************//**
             * \brief Emit octet string overload
             *
             * \details Overload for std::vector
             *
             ****************************************/
            template <class Context, class Ch> 
            inline Context&& emitOctetStringOverload(Context&& _ctx, const std::vector<Ch>& _value)
            {
                return emitOctetString(std::forward<Context>(_ctx), _value.data(), _value.size() * sizeof(Ch));
            }
            /************************************//**
             * \brief Emit octet string overload
             *
             * \details Overload for std::array
             *
             ****************************************/
            template <class Context, class Ch, int S> 
            inline Context&& emitOctetStringOverload(Context&& _ctx, const std::array<Ch, S>& _value)
            {
                return emitOctetString(std::forward<Context>(_ctx), _value.data(), _value.size() * sizeof(Ch));
            }
            /************************************//**
             * \brief Emit octet string overload
             *
             * \details Overload for std::list
             *
             ****************************************/
            template <class Context, class Ch> 
            inline Context&& emitOctetStringOverload(Context&& _ctx, const std::list<Ch>& _value)
            {
                return emitOctetString(std::forward<Context>(_ctx), _value.begin(), _value.end());
            }
            /************************************//**
             * \brief Emit octet string overload
             *
             * \details Overload for OctetStringExt
             *
             ****************************************/
            template <class Context> 
            inline Context&& emitOctetStringOverload(Context&& _ctx, const MMS::DataTypes::OctetStringBuffer& _value)
            {
                return emitOctetString(std::forward<Context>(_ctx), _value.pPtr, _value.length);
            }
        }
        /************************************//**
         * \brief Octet string emitter
         *
         * \details Takes an octet string and emits it.
         *  Uses specializations.
         * \note This function is only enabled for types that
         * have an ASN1 or MMS octetString tag associated with
         *
         ****************************************/
        template <class Context, class T> 
        inline typename std::enable_if<(MMS::Tags::TagDef<T>::TAG == MMS::Tags::OCTET_STRING || ASN1::Tags::TagDef<T>::TAG == ASN1::Tags::OCTETSTRING), 
            typename std::remove_reference<Context>::type>::type&& 
            emit(Context&& _ctx, const T& _value)
        {
            auto oldSize = MMS::getContextSize(_ctx);
            _ctx = Details::emitOctetStringOverload(_ctx, _value);
            return std::move(emitTag(emitLength(_ctx, oldSize - MMS::getContextSize(_ctx)), _value));
        }
    }

}

