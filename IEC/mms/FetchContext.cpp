//-----------------------------------------------------------------------------
// <copyright file="FetchContext.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 17:12:03</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include "FetchContext.h"


using namespace MMS::Extractors;


MMS::Extractors::Details::FetchContextBase::FetchContextBase( const void* _begin, /*/< Pointer to the head of the buffer */ std::size_t _length /*/< Length of buffer in bytes */ ):
    m_begin(static_cast<const unsigned char*>(_begin)),
    m_end(static_cast<const unsigned char*>(_begin)+(_begin==nullptr?0:_length))
{

}

MMS::Extractors::Details::FetchContextBase::FetchContextBase(const FetchContextBase& _rhs):
    m_begin(_rhs.m_begin),
    m_end(_rhs.m_end)
{

}

unsigned char MMS::Extractors::Details::FetchContextBase::fetchOctetUnsafe()
{
    return *m_begin++;
}

std::size_t MMS::Extractors::Details::FetchContextBase::GetContextSize() const
{
    return m_end - m_begin;
}

bool FetchContextBase::operator==(const FetchContextBase& _rhs) const
{
    return m_begin == _rhs.m_begin && m_end == _rhs.m_end;
}


const unsigned char* MMS::Extractors::Details::FetchContextBase::fetchOctets( std::size_t _octets /*/< Number of octets to fetch */ )
{
    if (m_begin + _octets > m_end)
    {
        m_begin = m_end;    // Context is exhausted 
        return nullptr;
    }
    else
    {
        auto result = m_begin;
        m_begin += _octets;
        return result;
    }
}
