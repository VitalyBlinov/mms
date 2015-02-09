//-----------------------------------------------------------------------------
// <copyright file="FetchContext.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 16:56:18</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file MMS extractor context and extractor helper functions
//-----------------------------------------------------------------------------
#pragma once
#include "MMSTags.h"
#include "UniversalClass.h"
#include "ContextTraits.h"
/************************************//**
 * \brief MMS protocol implementation
 ****************************************/
namespace MMS
{
    /************************************//**
     * \brief Protocol extractors namespace
     ****************************************/
    namespace Extractors
    {
        namespace Details
        {
        /************************************//**
         * \brief Fetch context
         *
         * \details Implements the input non-volatile buffer
         * allowing only "walk forward" paradigm.
         * \todo Add context-dependent error 
         *
         ****************************************/
        class FetchContextBase
        {
	        public:
		        ///	\brief FetchContextBase constructor
		        FetchContextBase(
                    const void* _begin,     ///< Pointer to the head of the buffer
                    std::size_t _length     ///< Length of buffer in bytes
                    );
                /************************************//**
                 * \brief Copy constructor
                 ****************************************/
                FetchContextBase(
                    const FetchContextBase& _rhs
                    );
                /// \brief Fetch single octet
                /// \details Does not perform bounds checks!
                unsigned char fetchOctetUnsafe();
                /// \brief Fetch a number of octets
                /// \details Checks if given number of octets can be extracted. If so, returns
                /// a pointer to the beginning of such array, otherwise returns a null pointer.
                /// \returns A pointer to the beginning of the array of _octets. If contexts is
                /// shorted than _octets bytes, nullptr is returned. In such case, context will be
                /// exhausted  and subsequent calls to GetContextSize() will return 0;
                const unsigned char* fetchOctets(
                    std::size_t _octets             ///< Number of octets to fetch
                    );
                /************************************//**
                 * \brief Get context size
                 *
                 * \returns Remaining context buffer size in bytes
                 ****************************************/
                std::size_t GetContextSize() const;
                /************************************//**
                 * \brief Indicates if tag should be emitted in this context
                 *
                 * \returns True
                 *
                 ****************************************/
                virtual bool IsTagEnabled() const = 0;
                /************************************//**
                 * \brief Equal operator
                 *
                 * \returns True if both contexts share the same buffer. False otherwise
                 *
                 ****************************************/
                bool operator == (const FetchContextBase& _rhs) const;
            protected:
                const unsigned char* m_begin;
                const unsigned char* m_end;
	        };

            template <class Traits>
            class FetchContext:
                public FetchContextBase
            {
            public:
                typedef Traits context_traits;
                typedef FetchContext<typename context_traits::ImplicitTraits> tImplicit;
                typedef FetchContext<typename context_traits::ExplicitTraits> tExplicit;
                /************************************//**
                 * \brief Indicates if tag should be emitted in this context
                 *
                 * \returns True
                 *
                 ****************************************/
                bool IsTagEnabled() const
                {
                    return !context_traits().isImplicit();
                }
                /************************************//**
                 * \brief Constructor
                 *
                 * \details This constructor takes two iterators
                 *
                 ****************************************/
                FetchContext(                
                    const void* _begin,     ///< Pointer to the head of the buffer
                    std::size_t _length     ///< Length of buffer in bytes
                    ):
                    FetchContextBase(_begin, _length)
                    {

                    }
                /************************************//**
                 * \brief Constructor uses default emit context as base
                 *
                 * \details Used when a no-tag context needs to be 
                 *  created on top of the buffer that was already
                 *  filled with data. Most common case is when we need
                 *  to emit report header when all reported data has been
                 *  emitted
                 *
                 ****************************************/
                template <class Tr>
                FetchContext(                
                    const FetchContext<Tr>& _rhs          ///< Original instance
                    ):
                    FetchContextBase(_rhs)
                {

                }
            };

        }
        using Details::FetchContextBase;

        typedef Details::FetchContext<ContextTraits<false>> ExplicitFetchContextMMS;
        typedef Details::FetchContext<ContextTraits<true>> ImplicitFetchContextMMS;
        typedef Details::FetchContext<ContextTraits<false, ASN1::Tags::TagDef>> ExplicitFetchContextASN;
        typedef Details::FetchContext<ContextTraits<true, ASN1::Tags::TagDef>> ImplicitFetchContextASN;

        /// \name Emit context create functions
        /// \details Used when MMS data is emitted. Have specializations for pointers and vector/array containers
        /**@{*/
        template <class T>
        inline ExplicitFetchContextMMS createFetchContext(T _begin, T _end)
        {
            return createContext<ExplicitFetchContextMMS>(_begin, _end);
        };

        template <typename T, typename Allocator>
        inline ExplicitFetchContextMMS createFetchContext(std::vector<T, Allocator>& _buffer)
        {
            return createContext<ExplicitFetchContextMMS>(_buffer);
        };

        template <typename T, std::size_t N>
        inline ExplicitFetchContextMMS createFetchContext(std::array<T, N>& _buffer)
        {
            return createContext<ExplicitFetchContextMMS>(_buffer);
        };

        template <typename T, std::size_t N>
        inline ExplicitFetchContextMMS createFetchContext(T (&data)[N])
        {
            return createContext<ExplicitFetchContextMMS>(data);
        };

        /**@}*/
        /// \name No-tag Emit context create functions
        /// \details Used when report headers are emitted or in other places where tags are omitted
        /**@{*/
        template <class T>
        inline ImplicitFetchContextMMS createNoTagFetchContext(T _begin, T _end)
        {
            return createContext<ImplicitFetchContextMMS>(_begin, _end);
        };

        template <typename T, typename Allocator>
        inline ImplicitFetchContextMMS createNoTagFetchContext(std::vector<T, Allocator>& _buffer)
        {
            return createContext<ImplicitFetchContextMMS>(_buffer);
        };

        template <typename T, std::size_t N>
        inline ImplicitFetchContextMMS createNoTagFetchContext(std::array<T, N>& _buffer)
        {
            return createContext<ImplicitFetchContextMMS>(_buffer);
        };

        template <typename T, std::size_t N>
        inline ImplicitFetchContextMMS createNoTagFetchContext(T (&data)[N])
        {
            return createContext<ImplicitFetchContextMMS>(data);
        };

        template <class C>
        inline ImplicitFetchContextMMS createNoTagFetchContext(C& _ctx)
        {
            return ImplicitFetchContextMMS(
                _ctx
                );
        };
        /**@}*/
        /************************************//**
         * \brief Creates a sub-context of given length
         *
         * \details Used when extracting a structure. The intent
         * is to perform initial bounds checking before even
         * attempting to extract the structure
         * \returns New context object starting at current position with
         * length of _length. If original context is shorter than _length,
         * an empty context is returned.
         *
         * \tparam C context type
         *
         ****************************************/
        template <class C>
        inline C getSubContext(
            C& _original,               ///< Original context object
            std::size_t _length        ///< Required length of sub-context
            )
        {
            auto ptr = fetchOctets(_original, _length);
            return C(ptr, _length);
        }
        /************************************//**
         * \brief Fetch entry point
         *
         * \details Fetch function covering all data types. Implements "roll-back" logic - 
         * fetch context _ctx is not modified if extraction fails.
         *
         * \returns True if data was successfully fetched. False otherwise
         *
         * \tparam Context fetch context type
         * \tparam Val value type
         *
         ****************************************/
        template <class Context, class Val>
        inline bool fetch(
            Context& _ctx,              ///< Fetch context
            Val& _Value                 ///< [OUT] value
            )
        {
            Context backup(_ctx);
            if (!Details::extract(_ctx, _Value))
            {
                _ctx = backup;
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}

