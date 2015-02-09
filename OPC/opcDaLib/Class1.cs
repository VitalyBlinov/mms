using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace opcDaLib
{
    /// <summary>
    /// Exception used when name conflict is detected
    /// </summary>
    class NameConflictException: Exception
    {
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="Msg">Message associated with this exception</param>
        NameConflictException(string Msg)
            : base(Msg)
        {

        }
    }
}
