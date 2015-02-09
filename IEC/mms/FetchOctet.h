//-----------------------------------------------------------------------------
// <copyright file="FetchOctet.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 22:20:08</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once

namespace MMS
{
    namespace Extractors
    {
        namespace Details
        {
            template <typename T>
            inline auto callFetchOctet(T& t, unsigned char& _what) -> decltype(t.fetchOctetUnsafe(), bool())
            {
                if (MMS::getContextSize(t) != 0)
                {
                    _what = t.fetchOctetUnsafe();
                    return true;
                }
                else
                {
                    return false;
                }
            };

            template <typename T>
            inline bool callFetchOctet(...)
            {
                static_assert(false, "Context type does not define fetchOctet method");
                return false;
            };

            template <typename T>
            inline auto callFetchOctets(T& t, std::size_t _octets) -> decltype(t.fetchOctets(0))
            {
                return t.fetchOctets(_octets);
            };

            template <typename T>
            inline const unsigned char* callFetchOctets(...)
            {
                static_assert(false, "Context type does not define fetchOctets method");
                return nullptr;
            };
        }
        ///	\brief fetchOctet helper function
        /// \details Checks if Context class defines fetchOctet function and uses it.
        /// otherwise the compilation will be failed unless there is an overload of fetchOctet
        /// for given Context type
        /// \tparam Context context type
        template <class Context>
        inline bool fetchOctet(Context& _ctx, unsigned char& _octet)
        {
            return Details::callFetchOctet(_ctx, _octet);
        }
        ///	\brief fetchOctets helper function
        /// \details Checks if Context class defines fetchOctets function and uses it.
        /// otherwise the compilation will be failed unless there is an overload of fetchOctet
        /// for given Context type
        /// \tparam Context context type
        template <class Context>
        inline const unsigned char* fetchOctets(Context& _ctx, std::size_t _octets)
        {
            return Details::callFetchOctets(_ctx, _octets);
        }
    }
}

