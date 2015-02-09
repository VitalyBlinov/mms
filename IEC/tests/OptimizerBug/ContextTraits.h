//-----------------------------------------------------------------------------
// <copyright file="ContextTraits.h" company="big foot Software">
//      Copyright (c) 2015 big foot Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/17 04:37:48</created>
// <author>Vital</author>
// <summary>Project "Something went bad"</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "UniversalClass.h"
namespace MMS
{
    /************************************//**
     * \brief Defines context traits class
     *
     * \details There are several context that
     * are in use when MMS protocol is considered.
     * The first important difference between contexts
     * is whether is it implicit or explicit. In implicit 
     * context no tags are used.<br>
     * Another big difference is that inside headers of
     * MMS protocol messages ASN.1 tags system is used, while
     * their payload use MMS-specific tags, that have
     * different values.
     *
     ****************************************/
    template <bool Implicit, template <typename> class Traits = ASN1::Tags::TagDef>
	struct ContextTraits
	{
	public:
        typedef ContextTraits<true, Traits> ImplicitTraits;
        typedef ContextTraits<false, Traits> ExplicitTraits;
        typedef std::integral_constant<bool, Implicit> tImplicit;
   
        /************************************//**
         * \brief Runtime implicit check
         ****************************************/
        inline bool isImplicit() const
        {
            return tImplicit::value;
        };
        /************************************//**
         * \brief Resolves a tag value for given type
         *
         * \details
         *
         ****************************************/
        template <typename T>
        inline typename std::enable_if<Traits<T>::TAG != -1, unsigned char>::type getTag(const T&) const
        {
            return Traits<T>::TAG;
        }

        template <typename T>
        inline typename std::enable_if<Traits<T>::TAG == -1 && std::is_void<typename Traits<T>::constructed>::value, unsigned char>::type getTag(const T&) const
        {
            // Must be a constructed tag, but it does not exist in MMS payload context
            static_assert(false, "Type has no matching tag for given context");
        }

        template <typename T>
        inline typename std::enable_if<Traits<T>::TAG == -1 && !std::is_void<typename Traits<T>::constructed>::value, unsigned char>::type getTag(const T&) const
        {
            return Traits<T>::constructed::TAG;
        }

	};
}

