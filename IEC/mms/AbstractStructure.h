//-----------------------------------------------------------------------------
// <copyright file="AbstractStructure.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/31 02:45:43</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "EmitContext.h"

namespace MMS
{
    namespace Emitters
    {
        namespace Details
        {
            template <class Context, class It>
            Context&& emitStructure(
                Context&& _context,         ///< Emit context
                It _last,                   ///< Last known child member of the structure
                unsigned char _top          ///< Top level of the structure
                )
            {
                auto oldSize = MMS::getContextSize(_context);     // Get previous size of context
                unsigned char oldLevel = MMS::Storage::Tree::GetLevel(*_last);

                while (oldLevel != _top)
                {
                    unsigned char newLevel = MMS::Storage::Tree::GetLevel(*_last);
                    if (newLevel < oldLevel)        // We exited nested structure
                    {
                        _context = MMS::Emitters::emitTag(MMS::Emitters::emitLength(_context, oldSize - MMS::getContextSize(_ctx)), MMS::Tags::STRUCTURE);
                    }
                    else // We either stayed on the same level or went even deeper
                    {
                        _context = MMS::Emitters::emit(_context, *_last); 
                    }
                    --_last;
                    oldLevel = newLevel;
                }
                return std::move(_context);
            }
        }
    }
	///	\brief AbstractStructure class
	/// \details An abstract structure class
    /// is a structure which is defined at runtime.
    template <class It>
    class AbstractStructure
    {
    private: 
        It m_begin;
        It m_end;
    public:
        /************************************//**
         * \brief Constructor
         ****************************************/
        AbstractStructure(
            It _begin,                  ///< Iterator pointing to the root node of the structure
            It _end                     ///< Iterator pointing to the node next to the last that belongs to the structure
            ):
        m_begin(_begin),
        m_end(_end)
        {

        }
        /************************************//**
         * \brief Structure emitter
         ****************************************/
        template <class Context>
        Context&& emit(
            Context&& _context
            )
        {
            // Structure must not be empty, I say...
            if (m_end != m_begin)
            {
                auto last = m_end - 1;
                return MMS::Emitters::Details::emitStructure(_context, last, MMS::Storage::Tree::GetLevel(*m_begin));
//                 auto oldSize = MMS::Emitters::getCo//-----------------------------------------------------------------------------
// <copyright file="AbstractStructure.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/08 04:33:36</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once

namespace IEC
{
	///	\brief AbstractStructure class
	/// 
	class AbstractStructure
	{
	public:
		///	\brief AbstractStructure constructor
		AbstractStructure();
		///	\brief AbstractStructure destructor
		~AbstractStructure();
	};
}

ntextSize(_context);     // Get previous size of context
//                 auto last = m_end - 1;
//                 {
//                     while (last != m_begin)
//                     {
//                         if (MMS::Storage::Tree::GetParent(last) == m_begin)
//                         {
//                             MMS::Emitters::emit(_context, *last);       // Forward it directly to emitter
//                         }
//                         else
//                         {
//                             // we are stepping into the nested structure
//                             _context = AbstractStructure<It>(MMS::Storage::Tree::GetParent(last), last).emit(_context);
//                             last = MMS::Storage::Tree::GetParent(last);
//                         }
//                         --last;
//                     }
//                 }
//                 return MMS::Emitters::emitTag(MMS::Emitters::emitLength(_context, oldSize - MMS::getContextSize(_ctx)), MMS::Tags::STRUCTURE);
            }
            else
            {
                return std::move(_context);
            }
        }
    };
}

