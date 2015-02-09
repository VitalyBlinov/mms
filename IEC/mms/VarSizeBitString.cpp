//-----------------------------------------------------------------------------
// <copyright file="VarSizeBitString.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/24 07:15:26</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include "VarSizeBitString.h"


using namespace MMS::DataTypes;


VarSizeBitString::value_type& MMS::DataTypes::VarSizeBitString::GetBitSet()
{
    return m_flags;
}

const VarSizeBitString::value_type& MMS::DataTypes::VarSizeBitString::GetBitSet() const
{
    return m_flags;
}

MMS::DataTypes::VarSizeBitString::operator MMS::DataTypes::VarSizeBitString::value_type&()
{
    return m_flags;
}

MMS::DataTypes::VarSizeBitString::operator const MMS::DataTypes::VarSizeBitString::value_type&() const
{
    return m_flags;
}

MMS::DataTypes::VarSizeBitString::VarSizeBitString( size_t _length /*= value_type().size() */ ):
        m_length(_length)
{
    m_flags.reset();
}

std::size_t MMS::DataTypes::VarSizeBitString::size() const
{
    return m_length;
}

VarSizeBitString::value_type::reference MMS::DataTypes::VarSizeBitString::operator[]( std::size_t _pos )
{
    return m_flags[_pos];
}

bool MMS::DataTypes::VarSizeBitString::operator[]( std::size_t _pos ) const
{
    return m_flags[_pos];
}


bool VarSizeBitString::operator== (const VarSizeBitString& _rhs) const
{
    return m_flags == _rhs.m_flags && m_length == _rhs.m_length;
}