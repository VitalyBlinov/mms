//-----------------------------------------------------------------------------
// <copyright file="MMSTags.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/27 01:01:56</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <bitset>
namespace MMS
{
    namespace Tags
    {
        /************************************//**
         * \brief MMS-specific subset of types
         *
         ****************************************/
        enum MMS_TAGS
        {
            TYPE_NAME       =   0x80,
            ARRAY           =   0x81,       // does anyone need them?
            STRUCTURE       =   0x82,       // In fact, structures' encoding is rather straightforward
            BOOLEAN         =   0x83,       // If only everything was that simple...
            BITSTRING       =   0x84,       // Oh, lovely bit strings.
            INTEGER         =   0x85,       // Special encoding rules due to leading bit ambiguity
            UNSIGNED        =   0x86,       // Much simpler than INTEGER
            FLOAT           =   0x87,       // IEEE format
            OCTET_STRING    =   0x89,       // An array of bytes. Pretty much.
            VISIBLE_STRING  =   0x8A,       // A string of visible characters
            BINARY_TIME     =   0x8C,       // Also called "timeofday"
            BCD             =   0x8D,       // They say it's integers
            BOOLEAN_ARRAY   =   0x8E,       // Haven't seen it being used
            OBJECT_ID       =   0x8F,       
            MMS_STRING      =   0x90,       // Something must be watched for. isn't it an UTF string?
            UTC_TIME        =   0x91        // UTC time.
        };

        template <typename T>
        struct TagDef { enum {TAG = -1}; typedef void constructed;};

#define MMS_TAG_TYPE_DEF(type, tag) \
            template <> struct TagDef<type> {enum {TAG = tag};};

        MMS_TAG_TYPE_DEF(char, MMS_TAGS::INTEGER);
        MMS_TAG_TYPE_DEF(short, MMS_TAGS::INTEGER);
        MMS_TAG_TYPE_DEF(int, MMS_TAGS::INTEGER);
        MMS_TAG_TYPE_DEF(long, MMS_TAGS::INTEGER);
        MMS_TAG_TYPE_DEF(long long, MMS_TAGS::INTEGER);

        MMS_TAG_TYPE_DEF(unsigned char, MMS_TAGS::UNSIGNED);
        MMS_TAG_TYPE_DEF(unsigned short, MMS_TAGS::UNSIGNED);
        MMS_TAG_TYPE_DEF(unsigned int, MMS_TAGS::UNSIGNED);
        MMS_TAG_TYPE_DEF(unsigned long, MMS_TAGS::UNSIGNED);
        MMS_TAG_TYPE_DEF(unsigned long long, MMS_TAGS::UNSIGNED);

        MMS_TAG_TYPE_DEF(float, MMS_TAGS::FLOAT);

        MMS_TAG_TYPE_DEF(bool, MMS_TAGS::BOOLEAN);

        MMS_TAG_TYPE_DEF(std::vector<bool>, MMS_TAGS::BITSTRING);
        template <std::size_t L> struct TagDef<std::bitset<L>>{enum tagDef {TAG = MMS_TAGS::BITSTRING};};

    }
}

