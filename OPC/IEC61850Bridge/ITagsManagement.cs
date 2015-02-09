using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IEC61850Bridge
{
    /// <summary>
    /// Items management interface
    /// </summary>
    /// <remarks>
    /// Abstracts items addition/removal
    /// </remarks>
    interface ITagsManagement
    {
        void AddItem(
            int refreshRate,
            string accessPath,
            string itemID
            );
    }
}
