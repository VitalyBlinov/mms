//-----------------------------------------------------------------------------
// <copyright file="VisibleString.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/02 03:49:34</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include "VisibleString.h"


using namespace MMS::DataTypes;

VisibleStringBuffer::VisibleStringBuffer():
    std::pair<const char*, std::size_t>(nullptr, 0)
{
}
        

MMS::DataTypes::VisibleStringBuffer::VisibleStringBuffer( const char* _pszString, std::size_t _length ):
        std::pair<const char*, std::size_t>(_pszString, _length)
{

}

const char* MMS::DataTypes::VisibleStringBuffer::getPtr() const
{
    return first;
}

std::size_t VisibleStringBuffer::getLength() const
{
    return second;
}
