//-----------------------------------------------------------------------------
// <copyright file="ASN1Tag.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/23 23:02:51</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include "ASN1Tag.h"


using namespace ASN1;


ASN1::TagValue::TagValue( unsigned int _value,  unsigned char _flag  ):
        m_value(_value),
        m_flag(_flag)
{

}

ASN1::TagValue::TagValue():
    m_value(0),
    m_flag(FLAGS::UNIVERSAL)
{

}

bool ASN1::TagValue::operator==( const TagValue& _rhs ) const
{
    return m_flag == _rhs.m_flag && m_value == _rhs.m_value;
}

unsigned int ASN1::TagValue::getValue() const
{
    return m_value;
}

unsigned char ASN1::TagValue::getFlags() const
{
    return m_flag;
}
