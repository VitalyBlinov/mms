//-----------------------------------------------------------------------------
// <copyright file="VisibleStringEmitter.h" company="big foot Software">
//      Copyright (c) 2015 big foot Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/16 12:56:02</created>
// <author>Vital</author>
// <summary>Project "Something went bad"</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "LengthEmitter.h"
#include "EmitOctet.h"
#include "TagEmitter.h"
#include "ContextMisc.h"
#include "VisibleString.h"

namespace MMS
{
    namespace Emitters
    {
        /************************************//**
         * \brief Visible string emitter
         *
         * \details Emits visible string
         *
         ****************************************/
        template <class Context, class T>
        inline Context&& emit(Context&& _ctx, const MMS::DataTypes::VisibleString<T>& _Value)
        {
            auto oldContextSize = MMS::getContextSize(_ctx);
            _ctx = emitOctets(_ctx, _Value.c_str(), _Value.length());
            return std::move(emitTag(emitLength(_ctx, oldContextSize - MMS::getContextSize(_ctx)), _Value));
        };
    }
}

