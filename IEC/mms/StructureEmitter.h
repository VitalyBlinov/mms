//-----------------------------------------------------------------------------
// <copyright file="StructureEmitter.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/29 03:53:43</created>
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
            template <typename Context, typename T>
            auto callEmitContents(Context& _ctx, T& t) -> decltype(t.emitContents(_ctx))
            {
                return t.emitContents(_ctx);
            };

            template <typename T>
            bool callEmitContents(...)
            {
                static_assert(false, "Structure type does not define emitContents method");
                return false;
            };
        }
        /************************************//**
         * \brief Emit structure contents catch-all
         *
         * \details Used when structure has no free function 
         * that emits the contents. Normally, this will assume that
         * structure implements emitContents method
         *
         ****************************************/
        template <class Context, class T>
        Context&& emitStructureContents(Context&& _ctx, const T& _value)
        {
            return MMS::Emitters::Details::callEmitContents(_ctx, _value);
        }
        /************************************//**
         * \brief Default emit method for structures and user types
         *
         * \details implements emitting of structures. Can be used
         * with any type, provided it implements emitContents method
         * or has emitContents function specification.
         *
         ****************************************/
        template <class Context, class T>
        Context&& emit(Context&& _ctx, const T& _value)
        {
            auto oldSize = MMS::getContextSize(_ctx);
            _ctx = emitStructureContents(_ctx, _value);
            return emitTag(emitLength(_ctx, oldSize - MMS::getContextSize(_ctx)), MMS::Tags::STRUCTURE);
        }
    }
}

