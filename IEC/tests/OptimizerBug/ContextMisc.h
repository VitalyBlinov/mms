//-----------------------------------------------------------------------------
// <copyright file="ContextMisc.h" company="big foot Software">
//      Copyright (c) 2015 big foot Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 21:14:07</created>
// <author>Vital</author>
// <summary>Project "Something went bad"</summary>
//-----------------------------------------------------------------------------
#pragma once
#include <cstddef>
#include <array>
#include <vector>
namespace MMS
{
        /************************************//**
         * \brief Context size stub
         *
         * \details returns the size of the context
         * \todo This function may later be changed to adapt
         * SFINAE technology if other context types are required
         ****************************************/
        template <class Context>
        inline std::size_t getContextSize(
            const Context& _ctx
            )
        {
            return _ctx.GetContextSize();
        }
        /************************************//**
         * \brief Checks if tag emit is enabled for given context
         *
         * \details In generic case, when exact type
         * of context is not known in compile time,
         * reverts to calling _ctx.IsTagEnabled().
         * Specialization of this function for NoTagEmitContext
         * always returns false
         *
         ****************************************/
        ///@{
        template <class Context>
        inline bool tagEnabled(const Context& _ctx)
        {
            return _ctx.IsTagEnabled();
        }

        template <class C, class T>
        inline C createContext(T _begin, T _end)
        {
            return C(&*_begin, _end - _begin);
        }

        template <class C, typename T, typename Allocator>
        inline C createContext(std::vector<T, Allocator>& _buffer)
        {
            return C(
                _buffer.size()? &_buffer[0]: nullptr,
                _buffer.size()? _buffer.size() * sizeof(T): 0
                );
        };

        template <class C, typename T, std::size_t N>
        inline C createContext(std::array<T, N>& _buffer)
        {
            return C(
                N>0? &_buffer[0]: nullptr,
                N>0? N * sizeof(T): 0
                );
        };

        template <class C, typename T, std::size_t N>
        inline C createContext(T (&data)[N])
        {
            return C(
                data,
                N * sizeof(T)
                );
        };
}

