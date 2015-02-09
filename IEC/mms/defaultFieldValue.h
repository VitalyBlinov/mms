//-----------------------------------------------------------------------------
// <copyright file="defaultFieldValue.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/13 18:26:01</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Default field value helpders
//-----------------------------------------------------------------------------
#pragma once
#define COMMA ,
namespace MMS
{
    namespace serialization
    {
        namespace Details
        {
            template <class T, class U, int ID>
            struct default_field_value
            {
                static U def() { return U(); }
            };
        }
#define FIELD_DEFAULT(type, id, value) \
    template <> struct Details::default_field_value<type, decltype(value), id> { static decltype(value) def() { return value; }};

#define T_FIELD_DEFAULT(type, id, value) \
    struct Details::default_field_value<type, decltype(value), id> { static decltype(value) def() { return value; }};

    }
}

