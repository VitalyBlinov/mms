using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using OpcRcw.Comn;
using OpcRcw.Da;
using System.Windows.Forms;

namespace opcDaLib
{
    /// <summary>
    /// Server class implementation
    /// </summary>
    /// <remarks>
    /// This Server implements all interfaces it requires to support by the OPC standard.
    /// </remarks>
    [ComVisible(true), GuidAttribute("B275A865-E07D-4F0C-8570-3E633C7AFD2C")]
    public class Server: IOPCServer, IOPCCommon , IConnectionPointContainer, IOPCBrowse, IOPCItemIO
    {
        private FileTimeAdapter m_startTime;

        public Server()
        {
            m_startTime = new FileTimeAdapter(DateTime.Now);
        }
        
        public void AddGroup(string szName, int bActive, int dwRequestedUpdateRate, int hClientGroup, IntPtr pTimeBias, IntPtr pPercentDeadband, int dwLCID, out int phServerGroup, out int pRevisedUpdateRate, ref Guid riid, out object ppUnk)
        {
            throw new NotImplementedException();
        }

        public void CreateGroupEnumerator(OPCENUMSCOPE dwScope, ref Guid riid, out object ppUnk)
        {
            throw new NotImplementedException();
        }

        public void GetErrorString(int dwError, int dwLocale, out string ppString)
        {
            ppString = "GetErrorString with locale invoked";
        }

        public void GetGroupByName(string szName, ref Guid riid, out object ppUnk)
        {
            throw new NotImplementedException();
        }
        /// <summary>
        /// Returns server status
        /// </summary>
        /// <remarks>
        /// This method is implemented to become a first example of
        /// how these exposed COM interfaces are going to be implemented.
        /// As per COM calling agreement, anything that needs to be allocated
        /// in the heap and then passed to other participant, must be deallocated
        /// by that other participant. Here, a structure is allocated in the unmanaged heap
        /// and then returned via pointer to the caller. It is then caller's responsibility
        /// to free that memory. It also has to free the szVendorInfo string, but that is hopefully
        /// taken care of in one of RCWs
        /// </remarks>
        /// <param name="ppServerStatus"></param>
        public void GetStatus(out IntPtr ppServerStatus)
        {
            OPCSERVERSTATUS status = new OPCSERVERSTATUS();
            status.dwServerState = OPCSERVERSTATE.OPC_STATUS_NOCONFIG;
            status.szVendorInfo = "This vendor rocks";
            ppServerStatus = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(OPCSERVERSTATUS)));
            status.ftStartTime = m_startTime.FileTime;
            status.ftCurrentTime = FileTimeAdapter.Convert(DateTime.Now);
            // TODO: handle last update time... when there is anything to update
            Marshal.StructureToPtr(status, ppServerStatus, false);
        }

        public void RemoveGroup(int hServerGroup, int bForce)
        {
            throw new NotImplementedException();
        }

        public void GetErrorString(int dwError, out string ppString)
        {
            ppString = "GetErrorString w/o locale invoked";
        }

        public void GetLocaleID(out int pdwLcid)
        {
            throw new NotImplementedException();
        }

        public void QueryAvailableLocaleIDs(out int pdwCount, out IntPtr pdwLcid)
        {
            throw new NotImplementedException();
        }

        public void SetClientName(string szName)
        {
            throw new NotImplementedException();
        }

        public void SetLocaleID(int dwLcid)
        {
            throw new NotImplementedException();
        }

        public void EnumConnectionPoints(out IEnumConnectionPoints ppenum)
        {
            throw new NotImplementedException();
        }

        public void FindConnectionPoint(ref Guid riid, out IConnectionPoint ppCP)
        {
            throw new NotImplementedException();
        }

        public void Browse(string szItemID, ref IntPtr pszContinuationPoint, int dwMaxElementsReturned, OPCBROWSEFILTER dwBrowseFilter, string szElementNameFilter, string szVendorFilter, int bReturnAllProperties, int bReturnPropertyValues, int dwPropertyCount, int[] pdwPropertyIDs, out int pbMoreElements, out int pdwCount, out IntPtr ppBrowseElements)
        {
            throw new NotImplementedException();
        }

        public void GetProperties(int dwItemCount, string[] pszItemIDs, int bReturnPropertyValues, int dwPropertyCount, int[] pdwPropertyIDs, out IntPtr ppItemProperties)
        {
            throw new NotImplementedException();
        }

        public void Read(int dwCount, string[] pszItemIDs, int[] pdwMaxAge, out IntPtr ppvValues, out IntPtr ppwQualities, out IntPtr ppftTimeStamps, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        public void WriteVQT(int dwCount, string[] pszItemIDs, OPCITEMVQT[] pItemVQT, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }
    }
}
