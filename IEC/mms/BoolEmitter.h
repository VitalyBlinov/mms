//-----------------------------------------------------------------------------
// <copyright file="BoolEmitter.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/27 01:46:04</created>
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
	    ///	\brief Boolean type emitter
        template <class Context>
	    Context&& emit(Context&& _ctx, bool _Value)
	    {
           return std::move(emitTag(emitLength(emitOctet(_ctx, _Value?1:0), 1), _Value));
	    };
    }
}

