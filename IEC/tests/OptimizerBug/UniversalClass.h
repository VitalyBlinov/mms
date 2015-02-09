
#pragma once
#include <vector>
#include <bitset>
namespace ASN1
{
    namespace Tags
    {
	    ///	\brief Universal class tags definition
        enum EN_UNIVERSAL_CLASS
        {
            EOC             =   0x0,
            BOOLEAN         =   0x1,
            INTEGER         =   0x2,
            BITSTRING       =   0x3,
            OCTETSTRING     =   0x4,
            _NULL           =   0x5,
            OID             =   0x6,
            O_DESRIPTOR     =   0x7,
            EXTERNAL        =   0x8,
            REAL            =   0x9,
            ENUMERATED      =   0xA,
            EMB_PDV         =   0xB,
            UTF8STRING      =   0xC,
            REL_OID         =   0xD,
            SEQUENCE        =   0x10,
            SET             =   0x11,
            NUMERIC_STR     =   0x12,
            PRINTABLE_STR   =   0x13,
            T61STR          =   0x14,
            VIDEOTEX_STR    =   0x15,
            IA5STR          =   0x16,
            UTCTIME         =   0x17,
            GEN_TIME        =   0x18,
            GRAPHIC_STR     =   0x19,
            VISIBLE_STR     =   0x1A,
            GENERAL_STR     =   0x1B,
            UNIVERSAL_STR   =   0x1C,           // How many strings can there be?
            CHARACTER_STR   =   0x1D,
            BMP_STR         =   0x1E

        };

        template <typename T>
        struct constructedTag { enum {TAG = 0x20}; };

        template <typename T>
        struct TagDef { enum {TAG = -1}; typedef constructedTag<T> constructed;};

#define ASN_TAG_TYPE_DEF(type, tag) \
        template <> struct TagDef<type> {enum {TAG = tag};};
#define T_ASN_TAG_TYPE_DEF(type, tag) \
        struct TagDef<type> {enum {TAG = tag};};

        ASN_TAG_TYPE_DEF(char, EN_UNIVERSAL_CLASS::INTEGER);
        ASN_TAG_TYPE_DEF(short, EN_UNIVERSAL_CLASS::INTEGER);
        ASN_TAG_TYPE_DEF(int, EN_UNIVERSAL_CLASS::INTEGER);
        ASN_TAG_TYPE_DEF(long, EN_UNIVERSAL_CLASS::INTEGER);
        ASN_TAG_TYPE_DEF(long long, EN_UNIVERSAL_CLASS::INTEGER);

        ASN_TAG_TYPE_DEF(float, EN_UNIVERSAL_CLASS::REAL);

        ASN_TAG_TYPE_DEF(bool, EN_UNIVERSAL_CLASS::BOOLEAN);

        ASN_TAG_TYPE_DEF(std::vector<bool>, EN_UNIVERSAL_CLASS::BITSTRING);
        template <std::size_t L> struct TagDef<std::bitset<L>>{enum tagDef {TAG = EN_UNIVERSAL_CLASS::BITSTRING};};

    }
}

