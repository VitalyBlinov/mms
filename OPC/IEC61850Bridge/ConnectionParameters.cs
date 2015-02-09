using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IEC61850Bridge
{
    /// <summary>
    /// IED connection parameters
    /// </summary>
    class ConnectionParameters
    {
        public String IPAddress { get; set; }
        public int Port { get; set; }

        ConnectionParameters(String address)
        {
            this.IPAddress = address;
            this.Port = 102;
        }
    }
}
