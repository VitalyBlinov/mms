//-----------------------------------------------------------------------------
// <copyright file="EmitContext.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/28 01:11:23</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#include "EmitContext.h"
#include <cstring>

using namespace MMS::Emitters;

//#pragma optimize( "g", off )
bool MMS::Emitters::Details::EmitContextBase::emitOctet( unsigned char _octet /*/< Octet to be emitted */ )
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
//#pragma optimize( "", on )
MMS::Emitters::Details::EmitContextBase::EmitContextBase( void* _begin, /*/< Pointer to the head of the buffer */ std::size_t _length /*/< Length of buffer in bytes */ ) :
    m_begin(static_cast<unsigned char*>(_begin)),
    m_length(_length),
    m_missingOctets(0)
{

}

MMS::Emitters::Details::EmitContextBase::EmitContextBase(const EmitContextBase& _rhs) :
    m_begin(_rhs.m_begin),
    m_length(_rhs.m_length),
    m_missingOctets(_rhs.m_missingOctets)
{

}

std::size_t MMS::Emitters::Details::EmitContextBase::GetMissingOctetsCount() const
{
    return m_missingOctets;
}

std::size_t MMS::Emitters::Details::EmitContextBase::GetContextSize() const
{
    return m_length;
}

bool MMS::Emitters::Details::EmitContextBase::emitOctets( const void* _pPtr, /*/< Address of an array of octets to be emitted */ std::size_t _size /*/< Number of octets to be emitted */ )
{
    if (_size > m_length)
    {
        m_length = 0;
        return false;
    }
    else
    {
        m_length -= _size;
        std::memcpy((void*)(m_begin + m_length), _pPtr, _size);
        return true;
    }
}

