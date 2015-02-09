//-----------------------------------------------------------------------------
// <copyright file="EmitContext.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/27 01:42:39</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <array>
#include "ContextMisc.h"
#include "MMSTags.h"
#include "UniversalClass.h"
#include "ContextTraits.h"
namespace MMS
{
    /************************************//**
     * \brief MMS protocol elements emitters
     ****************************************/
    namespace Emitters
    {
        namespace Details
        {
            ///	\brief EmitContext class
	        /// \details used to emit MMS data
	        class EmitContextBase
	        {
	        public:
		        ///	\brief EmitContext constructor
		        EmitContextBase(
                    void* _begin,           ///< Pointer to the head of the buffer
                    std::size_t _length     ///< Length of buffer in bytes
                    );
                /************************************//**
                 * \brief Copy constructor
                 ****************************************/
                EmitContextBase(
                    const EmitContextBase& _rhs
                    );
                /// \brief Emits single octet
                /// \details Performs bounds check. If target buffer is full, no data is emitted,
                /// instead, an internal counter is incremented. This can later be used to calculate 
                /// the required size of target buffer.
                /// \returns an indication of success. Normally,  true is returned. False is returned if 
                /// target buffer is already full and octet is not emitted
				inline bool emitOctet(
					unsigned char _octet                ///< Octet to be emitted
					)
				{
					if (m_length != 0)
					{
						--m_length;
						m_begin[m_length] = _octet;
						return true;
					}
					else
					{
						++m_missingOctets;
						return false;
					}
				}
                /************************************//**
                 * \brief Get number of missing octets
                 *
                 * \details Returns the number of octets that
                 * did not fit into the buffer provided
                 *
                 ****************************************/
                std::size_t GetMissingOctetsCount() const;
                /************************************//**
                 * \brief Get context size
                 *
                 * \returns Remaining context buffer size in bytes
                 ****************************************/
				inline std::size_t GetContextSize() const
				{
					return m_length;
				}
                /************************************//**
                 * \brief Emit octets optimization
                 *
                 * \details Copies _size of octets to the buffer. If 
                 * context's buffer is too small, no copy is performed but
                 * buffer size is set to 0
                 *
                 * \returns True if _size of octets have
                 *  been successfully copied to the context's buffer.
                 *  False if buffer is too small.
                 ****************************************/
                bool emitOctets(
                    const void* _pPtr,              ///< Address of an array of octets to be emitted
                    std::size_t _size               ///< Number of octets to be emitted
                    );
                /************************************//**
                 * \brief Indicates if tag should be emitted in this context
                 *
                 * \returns True
                 *
                 ****************************************/
                //virtual bool IsTagEnabled() const = 0;
            protected:
                // Note - these two variables declared volatile.
                // In fact, they aren't. But, as of MS Visual Studio Version 11.0.61030.00 Update 4,
                // there is a bug in optimizer that may lead to wrong code being generated
                // without volatile keywords.
                unsigned char* m_begin;
                std::size_t m_length;
                std::size_t m_missingOctets;
	        };

            template <class Traits>
            class EmitContext:
                public EmitContextBase
            {
            public:
                typedef Traits context_traits;
                typedef EmitContext<typename context_traits::ImplicitTraits> tImplicit;
                typedef EmitContext<typename context_traits::ExplicitTraits> tExplicit;
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
                EmitContext(                
                    void* _begin,           ///< Pointer to the head of the buffer
                    std::size_t _length     ///< Length of buffer in bytes
                    ):
                    EmitContextBase(_begin, _length)
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
                EmitContext(                
                    const EmitContext<Tr>& _rhs          ///< Original instance
                    ):
                    EmitContextBase(_rhs)
                {

                }
            };

        }

        typedef Details::EmitContext<ContextTraits<false>> ExplicitEmitContextMMS;
        typedef Details::EmitContext<ContextTraits<true>> ImplicitEmitContextMMS;
        typedef Details::EmitContext<ContextTraits<false, ASN1::Tags::TagDef>> ExplicitEmitContextASN;
        typedef Details::EmitContext<ContextTraits<true, ASN1::Tags::TagDef>> ImplicitEmitContextASN;

        /// \name Emit context create functions
        /// \details Used when MMS data is emitted. Have specializations for pointers and vector/array containers
        /**@{*/
        template <class T>
        inline ExplicitEmitContextMMS createMMSExplicitContext(T _begin, T _end)
        {
            return createContext<ExplicitEmitContextMMS>(
                _begin,
                _end - _begin
                );
        };

        template <typename T, typename Allocator>
        inline ExplicitEmitContextMMS createMMSExplicitContext(std::vector<T, Allocator>& _buffer)
        {
            return createContext<ExplicitEmitContextMMS>(
                _buffer
                );
        };

        template <typename T, std::size_t N>
        inline ExplicitEmitContextMMS createMMSExplicitContext(std::array<T, N>& _buffer)
        {
            return createContext<ExplicitEmitContextMMS>(
                _buffer
                );
        };

        template <typename T, std::size_t N>
        inline ExplicitEmitContextMMS createMMSExplicitContext(T (&data)[N])
        {
            return createContext<ExplicitEmitContextMMS>(
                data
                );
        };

        /**@}*/
        /// \name No-tag Emit context create functions
        /// \details Used when report headers are emitted or in other places where tags are omitted
        /**@{*/
        template <class T>
        inline ImplicitEmitContextMMS createMMSImplicitContext(T _begin, T _end)
        {
            return createContext<ImplicitEmitContextMMS>(
                _begin, _end
                );
        };

        template <typename T, typename Allocator>
        inline ImplicitEmitContextMMS createMMSImplicitContext(std::vector<T, Allocator>& _buffer)
        {
            return createContext<ImplicitEmitContextMMS>(
                _buffer
                );
        };

        template <typename T, std::size_t N>
        inline ImplicitEmitContextMMS createMMSImplicitContext(std::array<T, N>& _buffer)
        {
            return createContext<ImplicitEmitContextMMS>(
                _buffer
                );
        };

        template <typename T, std::size_t N>
        inline ImplicitEmitContextMMS createMMSImplicitContext(T (&data)[N])
        {
            return createContext<ImplicitEmitContextMMS>(
                data
                );
        };

        template <class Traits>
        inline ImplicitEmitContextMMS createMMSImplicitContext(Details::EmitContext<Traits>& _ctx)
        {
            return ImplicitEmitContextMMS(
                _ctx
                );
        };
        /**@}*/
    }
    /************************************//**
     * \brief Template function specification for NoTagEmitContext
     *
     * \details
     *
     ****************************************/
    template <class Traits>
    inline bool tagEnabled(const Emitters::Details::EmitContext<Traits>& _ctx)
    {
        return !Emitters::Details::EmitContext<Traits>::context_traits().isImplicit();
    }
}

