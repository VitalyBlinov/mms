using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IEC61850Bridge
{
    /// <summary>
    /// Connection factory
    /// </summary>
    public class ConnectionFactory
    {
        /// <summary>
        /// Creates a new connection
        /// </summary>
        /// <param name="?">Connection parameters</param>
        /// <returns>new IED connection object</returns>
		IConnection Create(ConnectionParameters parameters)
		{
			return null;
		}
    }
}
