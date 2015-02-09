//-----------------------------------------------------------------------------
// <copyright file="VisibleString.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/16 03:13:45</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include <string>
#include <array>
#include "MMSTags.h"
#include "UniversalClass.h"
namespace MMS
{
    namespace DataTypes
    {
        /************************************//**
         * \brief Encoded visible string buffer representation
         *
         * \details Used to represent visible string without
         * actually extracting it from the context, i.e. when
         * the data is still on the buffer. This means
         * that 
         *
         ****************************************/
        class VisibleStringBuffer: public std::pair<const char*, std::size_t>
        {
        public:
            VisibleStringBuffer();

            VisibleStringBuffer(
                const char* _pszString,
                std::size_t _length
                );
            /************************************//**
             * \brief Returns string pointer.
             *
             * \note this is not a c_str() - string will not be null-terminated
             *
             ****************************************/
            const char* getPtr() const;
            /************************************//**
             * \returns Length of the string
             *
             ****************************************/
            std::size_t getLength() const;
        };
        namespace Details
        {
            /************************************//**
             * \brief GetLength template check
             ****************************************/
            template <class T>
            inline std::size_t getLength(const T& _what)
            {
                return _what.size();
            }

            /************************************//**
             * \brief GetLength template check
             ****************************************/
            template <std::size_t L>
            inline std::size_t getLength(const std::array<char, L>& _what)
            {
                auto where = std::find(_what.begin(), _what.end(), 0);
                return where - _what.begin();
            }

            /************************************//**
             * \brief Check capacity - generic
             ****************************************/
            template <class T>
            inline bool checkCapacity(const T& _what, std::size_t _required)
            {
                return true;
            }

            /************************************//**
             * \brief Check capacity - std::array
             ****************************************/
            template <std::size_t L>
            inline bool checkCapacity(const std::array<char, L>& _what, std::size_t _required)
            {
                return _required < L;
            }
            /************************************//**
             * \brief  assign method for std::array
             ****************************************/
            template <std::size_t L>
            inline void assign(std::array<char, L>& _what, const char* _begin, std::size_t _length)
            {
                auto len = (_length<L-1?_length:L-1);
                std::copy(_begin, _begin + len, _what.begin());
                _what[len] = 0;
            }
            /************************************//**
             * \brief Generic assign method
             ****************************************/
            template <class T>
            inline void assign(T& _what, const char* _begin, std::size_t _length)
            {
                std::swap(_what, T(_begin, _begin + _length));
            }
            /************************************//**
             * \brief Generic to string function
             ****************************************/
            ///@{
            template <std::size_t L>
            inline std::string convert_to_string(const std::array<char, L>& _what)
            {
                return std::string(_what.begin(), _what.begin() + getLength(_what));
            }
            inline std::string convert_to_string(const std::string& _what)
            {
                return _what;
            }
            ///@}
        }
        /************************************//**
         * \brief Template Visible String representation
         *
         * \details This class abstracts visible string from
         * storage
         *
         * \tparam T - storage for the string. Only std::string and std::array<char, N>
         * have practical meaning. Other types cannot be specified.
         *
         ****************************************/
        template <class T>
        class VisibleString
        {
        private: 
            T m_storage;
        public:
            typedef T value_type;
            VisibleString()
            {

            }
            /************************************//**
             * \brief Constructor taking T
             ****************************************/
            VisibleString(
                const T& _original
                ):
            m_storage(_original)
            {
            };
            /************************************//**
             * \brief Constructor taking T
             ****************************************/
            VisibleString(
                T&& _original
                ):
            m_storage(_original)
            {
            };
			/************************************//**
			* \brief Constructor taking string on the buffer
			****************************************/
			VisibleString(
				const VisibleString& _rhs
				):
				m_storage(_rhs.m_storage)
			{
			};
            /************************************//**
             * \brief Constructor taking string on the buffer
             ****************************************/
            VisibleString(
                const VisibleStringBuffer& _buf
                )
            {
                Details::assign(m_storage, _buf.getPtr(), _buf.getLength());
            };
			/************************************//**
			* \brief Constructor taking string on the buffer
			****************************************/
			VisibleString(
				VisibleStringBuffer&& _buf
				)
			{
				Details::assign(m_storage, _buf.getPtr(), _buf.getLength());
			};
             /************************************//**
             * \brief Constructor taking literal and length
             ****************************************/
            VisibleString(
                const char* _begin,
                std::size_t _length
                )
            {
                Details::assign(m_storage, _begin, _length);
            };
            /************************************//**
             * \brief Constructor taking literal 
             ****************************************/
            VisibleString(
                const char* _pszStr
                )
            {
                Details::assign(m_storage, _pszStr, strlen(_pszStr));
            };

            /************************************//**
             * \brief Assignment operator
             *
             ****************************************/
            ///@{
            VisibleString& operator = (const char* _ptr)
            {
                Details::assign(m_storage, _ptr, strlen(_ptr));
                return *this;
            }
            VisibleString& operator = (const std::string& _str)
            {
                Details::assign(m_storage, _str.c_str(), _str.length());
                return *this;
            }
            VisibleString& operator = (const VisibleString<T>& _str)
            {
                m_storage = _str.m_storage;
                return *this;
            }
            VisibleString& operator = (VisibleString<T>&& _str)
            {
                m_storage = _str.m_storage;
                return *this;
            }
            template <class St>
            VisibleString& operator = (const VisibleString<St>&& _str)
            {
                *this = _str.c_str();
                return *this;
            }
            ///@}
             /************************************//**
             * \brief c-string access method
             ****************************************/
            const char* c_str() const
            {
                if (length() != 0)
                {
                    return &*m_storage.begin();
                }
                else
                {
                    static const char* empty = "";
                    return empty;
                }
            }
            /************************************//**
             * \brief Cast to std::string operator
             ****************************************/
            inline operator std::string () const
            {
                return Details::convert_to_string(m_storage);
            }
            /************************************//**
             * \brief Returns length of the string
             *
             * \returns length of the string irrespectively to
             * the m_storage capacity
             *
             ****************************************/
            std::size_t length() const
            {
                return Details::getLength(m_storage);
            }
            /************************************//**
             * \brief Checks if storage capacity is enough to store the string
             *
             * \details Important only in case when std::array is used as
             * storage. std::string or std::vector have virtually unlimited storage capacity
             *
             * \returns true if storage is capable of storing required
             * amount of characters
             *
             ****************************************/
            bool checkCapacity(
                std::size_t _characters         ///< number of characters required to store
                ) const
            {
                return Details::checkCapacity(m_storage, _characters);
            }
            /************************************//**
             * \brief Equal operator
             *
             * \details Compares two visible strings. Case sensitive
             *
             * \todo Room for optimization.
             *
             ****************************************/
            template <typename St>
            bool operator == (const VisibleString<St>& _rhs) const
            {
                return static_cast<std::string>(*this) == static_cast<std::string>(_rhs);
            }
        };
    }

    namespace Tags
    {
        // Defines MMS tag for this type
        template <class T> struct TagDef<MMS::DataTypes::VisibleString<T>>{enum {TAG = MMS_TAGS::VISIBLE_STRING};};
        MMS_TAG_TYPE_DEF(MMS::DataTypes::VisibleStringBuffer, MMS_TAGS::VISIBLE_STRING);
        MMS_TAG_TYPE_DEF(std::string, MMS_TAGS::VISIBLE_STRING);
    }
}

namespace ASN1
{
    namespace Tags
    {
        // Defines ASN.1 tag for this type
        template <class T> struct TagDef<MMS::DataTypes::VisibleString<T>>{enum {TAG = EN_UNIVERSAL_CLASS::VISIBLE_STR};};
        ASN_TAG_TYPE_DEF(MMS::DataTypes::VisibleStringBuffer, EN_UNIVERSAL_CLASS::VISIBLE_STR);
        ASN_TAG_TYPE_DEF(std::string, EN_UNIVERSAL_CLASS::VISIBLE_STR);
    }
}
