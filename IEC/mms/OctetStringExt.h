//-----------------------------------------------------------------------------
// <copyright file="OctetStringExt.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/13 20:51:46</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "MMSTags.h"
#include "UniversalClass.h"
namespace MMS
{
    namespace DataTypes
    {
        /************************************//**
         * \brief Extracted octet string type
         *
         * \details This type is a lightweight wrapper
         * for buffer/context. The idea is that protocol level
         * should not manage memory, but whatever uses extracted
         * data should be able to process it and create whatever
         * type they like
         *
         ****************************************/
        struct OctetStringBuffer
        {
            const unsigned char* pPtr;
            std::size_t length;
        };
    }
    namespace Tags
    {
        // Defines MMS tag for this type
        MMS_TAG_TYPE_DEF(MMS::DataTypes::OctetStringBuffer, MMS_TAGS::OCTET_STRING);
    }
}

namespace ASN1
{
    namespace Tags
    {
        // Defines ASN.1 tag for this type
        ASN_TAG_TYPE_DEF(MMS::DataTypes::OctetStringBuffer, EN_UNIVERSAL_CLASS::OCTETSTRING);
    }
}