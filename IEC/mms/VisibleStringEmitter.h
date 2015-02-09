//-----------------------------------------------------------------------------
// <copyright file="VisibleStringEmitter.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/16 12:56:02</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "LengthEmitter.h"
#include "EmitOctet.h"
#include "MMSTags.h"
#include "TagEmitter.h"
#include "ContextMisc.h"
#include "VisibleString.h"
#include "evaluator.h"
namespace MMS
{
    namespace Emitters
    {
        namespace Details
        {
            /************************************//**
             * \brief Visible string emitter
             *
             * \details Emits visible string
             * \tparam T - either VisibleString or std::string
             *
             ****************************************/
            template <class Context, class T>
            inline Context&& emitVisibleString(Context&& _ctx, const T& _Value)
            {
                auto oldContextSize = MMS::getContextSize(_ctx);
                _ctx = emitOctets(_ctx, _Value.c_str(), _Value.length());
                return std::move(emitTag(emitLength(_ctx, oldContextSize - MMS::getContextSize(_ctx)), _Value));
            };
            /************************************//**
             * \brief Evaluator overload for visible string
             *
             * \details Optimized version of the evaluator. Does not
             *  use context to perform to do test emits.
             * \tparam T - either VisibleString or std::string
             *
             ****************************************/
            template <typename Context, typename T>
            inline std::size_t evaluateVisibleString(const Context& _ctx, const T& _Value)
            {
                return evaluateTag(_ctx, _Value) + evaluateLength(_ctx, _Value.length()) + _Value.length();
            }
        }
        /************************************//**
         * \brief Visible string emitter
         *
         * \details Emits visible string
         *
         ****************************************/
        template <class Context, class T>
        inline Context&& emit(Context&& _ctx, const MMS::DataTypes::VisibleString<T>& _Value)
        {
            return Details::emitVisibleString(std::forward<Context>(_ctx), _Value);
        };
        /************************************//**
         * \brief Evaluator overload for visible string
         *
         * \details Optimized version of the evaluator. Does not
         *  use context to perform to do test emits.
         *
         ****************************************/
        template <typename Context, typename T>
        inline std::size_t evaluate(const Context& _ctx, const MMS::DataTypes::VisibleString<T>& _Value)
        {
            return Details::evaluateVisibleString(_ctx, _Value);
        }
        /************************************//**
         * \brief std::string emitter
         *
         * \details Emits std::string as visible string
         *
         ****************************************/
        template <class Context>
        inline Context&& emit(Context&& _ctx, const std::string& _Value)
        {
            return Details::emitVisibleString(std::forward<Context>(_ctx), _Value);
        };
        /************************************//**
         * \brief Evaluator overload for std::string
         *
         * \details Optimized version of the evaluator. Does not
         *  use context to perform to do test emits.
         *
         ****************************************/
        template <typename Context>
        inline std::size_t evaluate(const Context& _ctx, const std::string& _Value)
        {
            return Details::evaluateVisibleString(_ctx, _Value);
        }
    }
}

