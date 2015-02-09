using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using OpcRcw.Da;
using System.Runtime.InteropServices;

namespace opcDaLib
{
    /// <summary>
    /// FILETIME adapter class
    /// </summary>
    [ComVisible(false)]
    public class FileTimeAdapter
    {
        private OpcRcw.Da.FILETIME m_ft;
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="dt">DateTime type which is converted to FILETIME</param>
        public FileTimeAdapter(
            DateTime dt
            )
        {
            m_ft = Convert(dt);
        }
        /// <summary>
        /// Public FILETIME property
        /// </summary>
        public OpcRcw.Da.FILETIME FileTime
        {
            get { return m_ft; }
        }
        /// <summary>
        /// Static converter function
        /// </summary>
        /// <param name="dt">DateTime value</param>
        /// <returns>FILETIME structure</returns>
        public static OpcRcw.Da.FILETIME Convert(DateTime dt)
        {
            OpcRcw.Da.FILETIME ret = new OpcRcw.Da.FILETIME();
            ret.dwHighDateTime = (int)(dt.ToFileTime() >> 32);
            ret.dwLowDateTime = (int)(dt.ToFileTime() & 0xFFFFFFFF);
            return ret;
        }
    }
}
