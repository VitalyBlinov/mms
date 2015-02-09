//-----------------------------------------------------------------------------
// <copyright file="ASN1Tag.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/23 14:46:59</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file ASN1 tag specific functions. 
//-----------------------------------------------------------------------------
#pragma once
#include "EmitOctet.h"
#include "FetchOctet.h"
namespace ASN1
{
    namespace Details
    {
        class TagBase
        {
        public:
            enum FLAGS : unsigned char {UNIVERSAL = 0x0, CONSTRUCTED = 0x20, APPLICATION = 0x40, CONTEXT = 0x80};
        };
    }
    /************************************//**
     * \brief ASN1 tag representation
     *
     * \details useful representation for ASN.1 tag
     *  allowing catering for all types of tags and
     *  supporting tag values greater than 31
     *
     ****************************************/
    class TagValue: public Details::TagBase
    {
        unsigned char m_flag;
        unsigned int m_value;
    public:
        /************************************//**
         * \brief Constructor
         ****************************************/
        TagValue(
            unsigned int _value,                                ///< Tag value
            unsigned char _flag = TagBase::UNIVERSAL            ///< Tag flag
            );
        TagValue();
        /************************************//**
         * \brief Comparison operator
         ****************************************/
        bool operator == (const TagValue& _rhs) const;
        /************************************//**
         * \brief Get value method
         ****************************************/
        unsigned int getValue() const;
        /************************************//**
         * \brief Get flags method
         ****************************************/
        unsigned char getFlags() const;
    };
}

namespace MMS
{
    namespace Emitters
    {
        namespace Details
        {
            /************************************//**
             * \brief Emits the tag according to ASN.1 rules using short form
             *
             * \details Most tags' values fit in lower 5 bits of the octet.
             *  For tag values greater than 31, long tag encoding should be used
             *
             ****************************************/
            template <class Context>
            inline Context&& emitTagValueShortForm(Context&& _ctx, const ASN1::TagValue& _value)
            {
                return std::move(MMS::Emitters::emitOctet(std::forward<Context>(_ctx), _value.getFlags() | (unsigned char)_value.getValue()));
            }
            /************************************//**
             * \brief Emits the tag according to ASN.1 rules using short form
             *
             * \details Most tags' values fit in lower 5 bits of the octet.
             *  For tag values greater than 31, long tag encoding should be used
             *
             ****************************************/
            template <class Context>
            inline Context&& emitTagValueLongForm(Context&& _ctx, const ASN1::TagValue& _value)
            {
                auto tagVal = _value.getValue();
                
                _ctx = MMS::Emitters::emitOctet(std::forward<Context>(_ctx), (unsigned char)tagVal & 0x7F);
                tagVal = tagVal >> 7;
                while (tagVal != 0)
                {
                    _ctx = MMS::Emitters::emitOctet(std::forward<Context>(_ctx), (unsigned char)tagVal | 0x80);
                    tagVal = tagVal >> 7;
                }
                return std::move(MMS::Emitters::emitOctet(std::forward<Context>(_ctx), _value.getFlags() | 0x1F));
            }
        }
        /************************************//**
         * \brief Template tag emitter
         *
         * \details Runtime-specific tag emitter. Used for
         * context- and application-specific tags, where
         * tag value cannot be fully resolved at compile time based on a type only.
         * In most cases, however, it is possible to resolve
         * whether a short of a long form must be used.
         *
         ****************************************/
        template <class Context>
        inline Context&& emitTag(
            Context&& _ctx, 
            const ASN1::TagValue& _value, 
            std::true_type                  ///< Short form is used
            )
        {
            return std::move(Details::emitTagValueShortForm(std::forward<Context>(_ctx), _value));
        }

        template <class Context>
        inline Context&& emitTag(
            Context&& _ctx, 
            const ASN1::TagValue& _value, 
            std::false_type                  ///< Long form is used
            )
        {
            return std::move(Details::emitTagValueLongForm(std::forward<Context>(_ctx), _value));
        }

        template <class Context>
        inline Context&& emit(
            Context&& _ctx, 
            const ASN1::TagValue& _value
            )
        {
            if (_value.getValue() < 31)
            {
                return emitTag(std::forward<Context>(_ctx), _value, std::true_type());
            }
            else
            {
                return emitTag(std::forward<Context>(_ctx), _value, std::false_type());
            }
        }
    }
    namespace Extractors
    {
        namespace Details
        {
            /************************************//**
             * \brief Extracts tag value 
             ****************************************/
            template <class Context>
            inline bool extract(Context& _ctx, ASN1::TagValue& _out)
            {
                unsigned char octet = 0;
                if (fetchOctet(_ctx, octet))
                {
                    if ((octet & 0x1F) != 0x1F) // short form
                    {
                        _out = ASN1::TagValue(octet & 0x1F, (ASN1::Details::TagBase::FLAGS)octet & 0xE0);
                        return true;
                    }
                    else
                    {
                        int flag = (ASN1::Details::TagBase::FLAGS)(octet & 0xE0);
                        unsigned int value = 0;

                        do
                        {
                            if (!fetchOctet(_ctx, octet))
                            {
                                return false;
                            }
                            value = (value << 7) | (octet & 0x7F);
                        } 
                        while ((octet & 0x80) != 0);

                        _out = ASN1::TagValue(value, flag);
                        return true;
                    }
                }
                return false;
            }
        }
        /************************************//**
         * \brief Extracts the tag value from the context and checks it against 
         *  provided value
         *
         * \returns true if tag value extracted matches value provided. False otherwise
         *
         ****************************************/
        template <class Context, typename T>
        inline bool checkTag(Context& _ctx, const ASN1::TagValue& _value)
        {
            ASN1::TagValue _extracted;
            if (Details::extract(_ctx, _value))
            {
                return _extracted == _value;
            }
            else 
            {
                return false;
            }
        }
    }
}
