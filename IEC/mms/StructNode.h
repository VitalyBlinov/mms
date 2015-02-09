//-----------------------------------------------------------------------------
// <copyright file="StructNode.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/31 03:23:43</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "EndNode.h"

namespace MMS
{
	///	\brief StructNode class
	/// \details Extends EndNode class so it allows for SetRight()
	class StructNode:
            public EndNode
	{
    private:
        ITreeStructure* m_right;
	public:
		///	\brief StructNode constructor
		StructNode();
        /************************************//**
         * \brief Assigns right pointer
         *
         * \details Structure nodes will have children; therefore
         * they allow for "right" pointer to be set
         ****************************************/
        void SetRight(
            ITreeStructure* _right
            );

        virtual ITreeStructure* GetRight();

        virtual const ITreeStructure* GetRight() const;

    };
}

