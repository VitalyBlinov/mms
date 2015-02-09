//-----------------------------------------------------------------------------
// <copyright file="NULLPDU.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/20 06:08:49</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file helper macro to declare NULL PDU
//-----------------------------------------------------------------------------
#pragma once
#include "UniversalClass.h"
#include "TagEmitter.h"
#include "LengthEmitter.h"
#include "TagExtractor.h"
#include "LengthExtractor.h"
namespace MMS
{
    namespace DataTypes
    {
        /************************************//**
         * \brief NULL value placeholder
         *
         * \details This empty structure represents
         * all NULL values in the ASN.1 parts of MMS
         * protocol
         *
         ****************************************/
        struct NULLValue
        {

        };
    }

    namespace Emitters
    {
        /************************************//**
         * \brief NULL Value emitter
         ****************************************/
        template <class Context>
        Context emit(Context _ctx, MMS::DataTypes::NULLValue _Value)
        {
            return emitTag(emitLength(std::forward<Context>(_ctx), 0), _Value);
        };
    }

    namespace Extractors
    {
        namespace Details
        {
            /************************************//**
             * \brief NULL value  extractor
             *
             * \details extracts NULL value from the fetch context.
             *
             * \returns True if value is successfully extracted. False otherwise.
             *
             ****************************************/
            template <class Context>
            bool extract(Context& _ctx, MMS::DataTypes::NULLValue& _Value)
            {
                if (checkTag(_ctx, _Value))
                {
                    unsigned int _length = 0;
                    if (fetchLength(_ctx, _length))
                    {
                        return _length == 0;
                    }
                }
                return false;
            };
        }
    }
}

namespace ASN1
{
    namespace Tags
    {
        ASN_TAG_TYPE_DEF(MMS::DataTypes::NULLValue, EN_UNIVERSAL_CLASS::_NULL);
    }
}