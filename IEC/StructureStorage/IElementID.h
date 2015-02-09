//-----------------------------------------------------------------------------
// <copyright file="IElementID.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/08 04:35:21</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once

namespace Storage
{
	/************************************//**
	 * \brief Defines an interface for tree element
	 *
	 * \details Common methods like getLocalName etc...
	 *
	 ****************************************/
	class IElementID
	{
	public:
		/************************************//**
		 * \brief Returns element name
		 *
		 * \returns Local tree node name. For example, if the
         * full path of this node is "MMXU1.MX.phV.phsAB.mag, then
         * this function will return "mag" only
         * \note This interface does not provide a method to return 
         * the full name of the node - each node is considered an isolated entity here
		 *
		 ****************************************/
        virtual 
        const char* GetName() const = 0;

		///	\brief ITreeElement destructor
		virtual ~IElementID() = 0;
	};
}

