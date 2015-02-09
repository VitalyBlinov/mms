//-----------------------------------------------------------------------------
// <copyright file="GetNameListResponse.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/12 17:13:26</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Emitter and extractor for GetNameList-Response
//-----------------------------------------------------------------------------
#pragma once
#include "serialization.h"
#include "ExtractedSequenceOf.h"
#include "sequence.h"
namespace MMS
{
    namespace PDU
    {
        namespace Confirmed
        {
            namespace Details
            {
                /************************************//**
                 * \brief Used to emit GetNameList
                 *
                 * \details used to emit portions GetNameList response,
                 * where boolean member needs to indicate whether more will follow
                 *
                 ****************************************/
                template <class It>
                struct EmittedNameList
                {
                    typedef std::false_type implicit;               ///< Needed to use resolve_implicit context trickery
                    typedef MMS::DataTypes::sequence<It> sequence;  ///< Pre-adjusted sequence to be emitted or extracted sequence type
                    sequence nameList;                              ///< Ze sequence
                    bool moreFollows;                               ///< Will be set to false.
                };
            }
            /************************************//**
             * \brief GetNameList-response structure ready to emit
             *
             * \details Used by the server when GetNameList response
             *  needs to be emitted
             *
             ****************************************/
            template <class C, class T=std::string>
            struct GetNameListExtracted
            {
                typedef MMS::DataTypes::SequenceOf<C, T> typeExtractedSequence;
                /************************************//**
                 * \brief Extracted sequence of names
                 *
                 * \details It's not exactly extracted, user need to iterate
                 * through extractedSequence to get names.
                 *
                 ****************************************/
                typeExtractedSequence extractedSequence;
                bool moreFollows;       ///< If true, subsequent GetNameList-Request is required to retrieve the remainder
            };
        }
    }

    namespace serialization
    {
        using MMS::PDU::Confirmed::Details::EmittedNameList;
        using MMS::PDU::Confirmed::GetNameListExtracted;

        template <class It>
        T_PDU_IMPLICIT_FIELD(EmittedNameList<It>, 0, EmittedNameList<It>::nameList);
        template <class It>
        T_PDU_IMPLICIT_FIELD(EmittedNameList<It>, 1, EmittedNameList<It>::moreFollows);
        template <class It>
        T_FIELD_DEFAULT(EmittedNameList<It>, 1, true);

        template <class C, class T>
        T_PDU_IMPLICIT_FIELD(GetNameListExtracted<C COMMA T>, 0, GetNameListExtracted<C COMMA T>::extractedSequence);
        template <class C, class T>
        T_OPT_IMPLICIT_FIELD(GetNameListExtracted<C COMMA T>, 1, GetNameListExtracted<C COMMA T>::moreFollows);
        template <class C, class T>
        T_FIELD_DEFAULT(GetNameListExtracted<C COMMA T>, 1, true);

    }


    namespace Emitters
    {
        /************************************//**
         * \brief Emits the name list completely according to rules
         *
         * \details GetNameList response defined as following:
         * \code
                 GetNameList-Response ::= SEQUENCE
                 {
                 listOfIdentifier	[0] IMPLICIT SEQUENCE OF Identifier,
                 moreFollows		[1] IMPLICIT BOOLEAN DEFAULT TRUE
                 }
         * \endcode
         *
         * \returns Pair consisting of resulting context and 
         * one iterator past the last one emitted
         ****************************************/
        template <class C, class It>
        inline std::pair<typename std::remove_reference<C>::type, It> emitNameList(C&& _ctx, It _begin, It _end)
        {
            // How much can we afford to spend?
            auto afford = getContextSize(_ctx) - evaluateLength(_ctx, getContextSize(_ctx)) - evaluateTag(_ctx, 0) - evaluate(_ctx, (bool)false);
            // Now we know how much we've got
            It emitEnd = _begin;
            auto testExplicit = forceExplicit(_ctx);
            while (emitEnd != _end)
            {
                auto required = evaluate(testExplicit, *emitEnd);
                if (required > afford)
                {
                    break;
                }
                else
                {
                    afford -= required;
                    ++emitEnd;
                }
            }
            MMS::PDU::Confirmed::Details::EmittedNameList<It> List = {MMS::DataTypes::sequence<It>(_begin, emitEnd), emitEnd != _end};
            _ctx = emit(std::forward<C>(_ctx), List);

            return std::make_pair(std::move(_ctx), emitEnd);
        }
    }
}

