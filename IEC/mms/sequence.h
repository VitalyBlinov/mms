//-----------------------------------------------------------------------------
// <copyright file="sequence.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/24 15:48:06</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include <utility>
namespace MMS
{
    namespace DataTypes
    {
        /************************************//**
        * \brief Sequence OF X
        *
        * \details used to represent certain sequences when 
        * emitting and extracting
        *
        ****************************************/
        template <class It>
        struct sequence: public std::pair<It, It>
        {
            typedef typename std::pair<It, It> base;
            /************************************//**
            * \brief Constructor
            ****************************************/
            sequence(It _begin, It _end):
                    base(_begin, _end)
            {

            }
            /************************************//**
            * \brief return begin of the sequence
            ****************************************/
            It begin() const
            {
                return first;
            }
            /************************************//**
            * \brief returns end of the sequence
            ****************************************/
            It end() const
            {
                return second;
            }
        };
    }
}

