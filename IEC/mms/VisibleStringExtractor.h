//-----------------------------------------------------------------------------
// <copyright file="VisibleStringExtractor.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/16 13:34:37</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once

namespace MMS
{
	namespace Extractors
    {
        namespace Details
        {
            /************************************//**
             * \brief Visible string extractor
             *
             * \details extracts Visible string from the context
             * \note If the capacity of target variable is not enough to
             * store the full value of the string, the string is truncated!
             *
             * \returns True if value is successfully extracted. False otherwise.
             *
             ****************************************/
            ///@{
            template <class Context>
            inline bool extract(Context& _ctx, MMS::DataTypes::VisibleStringBuffer& _Value)
            {
                if (checkTag(_ctx, _Value))
                {
                    unsigned int length = 0;
                    if (fetchLength(_ctx, length))
                    {
                        auto ptr = fetchOctets(_ctx, length);
                        if (ptr != nullptr)
                        {
                            std::swap(_Value,MMS::DataTypes::VisibleStringBuffer(reinterpret_cast<const char*>(ptr), length));
                            return true;
                        }
                    }
                }
                return false;
            };

            template <class Context, class T>
            inline bool extract(Context& _ctx, MMS::DataTypes::VisibleString<T>& _Value)
            {
                MMS::DataTypes::VisibleStringBuffer _buf;
                bool ret = extract(_ctx, _buf);
                if (ret)
                {
                    std::swap(_Value, MMS::DataTypes::VisibleString<T>(_buf));
                    return true;
                }
                else
                {
                    return false;
                }
            };
            ///@}
        }
    }
}

