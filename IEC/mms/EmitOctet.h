//-----------------------------------------------------------------------------
// <copyright file="EmitOctet.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/27 16:10:53</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once


namespace MMS
{
    namespace Emitters
    {
        namespace Details
        {
            template <typename T>
            inline auto callEmitOctet(T& t, unsigned char _what) -> decltype(t.emitOctet(0), bool())
            {
                return t.emitOctet(_what);
            };

            template <typename T>
            bool callEmitOctet(...)
            {
                static_assert(false, "Context type does not define emitOctet method");
                return false;
            };


        }
        ///	\brief emitOctet helper function
        /// \details Checks if Context class defines emitOctet function and uses it.
        /// otherwise the compilation will be failed unless there is an overload of emitOctet
        /// for given Context type
        /// \tparam Context context type
        template <class Context>
        inline Context&& emitOctet(Context&& _ctx, unsigned char _octet)
        {
            Details::callEmitOctet(std::forward<Context>(_ctx), _octet);
            return std::move(_ctx);
        }

        namespace Details
        {
            /************************************//**
             * \brief A little trick to detect if context supports emitOctets method
             *
             * \details http://rsdn.ru/forum/cpp/2720363
             *
             ****************************************/
            template <typename T>
            class has_emitOctets
            {
                struct BaseFake
                {
                    void emitOctets(){};
                };

                struct Base: public T, public BaseFake {};

                template <typename Type, Type t> class Helper{};

                template <typename U>
                static std::false_type deduce(U*, Helper<void (BaseFake::*)(), &U::emitOctets>* = 0);
                static std::true_type deduce(...);
            public:
                typedef decltype(deduce((Base*)(0))) hasIt;
            };

            template <typename T, typename It>
            inline T&& callEmitOctets(T&& t, It _begin, It _end, std::true_type)
            {
                t.emitOctets(_begin, _end);
                return std::move(t);
            };


            template <typename T>
            inline T&& callEmitOctets(T&& t, const void* _pPtr, std::size_t _size, std::true_type)
            {
                t.emitOctets(_pPtr, _size);
                return std::move(t);
            };

            template <typename T, typename It>
            inline T&& callEmitOctets(T&& t, It _begin, It _end, std::false_type)
            {
                for (auto iter = std::reverse_iterator<It>(_end); iter != std::reverse_iterator<It>(_begin); ++iter)
                {
                    t = emitOctet(std::forward<T>(t), *iter);
                }
                return std::move(t);
            };

            template <typename T>
            inline T&& callEmitOctets(T&& t, const void* _pPtr, std::size_t _size, std::false_type)
            {
                return std::move(callEmitOctets(std::forward<T>(t), static_cast<const unsigned char*>(_pPtr), static_cast<const unsigned char*>(_pPtr) + _size));
            };
        }
        /************************************//**
         * \brief Emits range of octets defined by the pair of iterators
         *
         * \details This function overload is used when emitting
         * continuous memory range
         ****************************************/
        template <class Context>
        inline Context&& emitOctets(Context&& _ctx, const void* _pPtr, std::size_t _size)
        {
            return std::move(Details::callEmitOctets(std::forward<Context>(_ctx), _pPtr, _size, Details::has_emitOctets<std::remove_reference<Context>::type>::hasIt()));
        }
    }
}

