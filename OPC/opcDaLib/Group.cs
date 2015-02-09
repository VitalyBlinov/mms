using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using OpcRcw.Comn;
using OpcRcw.Da;

namespace opcDaLib
{
    /// <summary>
    /// Implements OPC group
    /// </summary>
    class Group: IOPCGroupStateMgt, IOPCGroupStateMgt2, IOPCItemMgt, IOPCSyncIO, IOPCSyncIO2, IOPCAsyncIO2, IOPCAsyncIO3, IOPCItemDeadbandMgt, IConnectionPointContainer
    {

        void IOPCGroupStateMgt.CloneGroup(string szName, ref Guid riid, out object ppUnk)
        {
            throw new NotImplementedException();
        }

        void IOPCGroupStateMgt.GetState(out int pUpdateRate, out int pActive, out string ppName, out int pTimeBias, out float pPercentDeadband, out int pLCID, out int phClientGroup, out int phServerGroup)
        {
            throw new NotImplementedException();
        }

        void IOPCGroupStateMgt.SetName(string szName)
        {
            name = szName;
        }

        void IOPCGroupStateMgt.SetState(IntPtr pRequestedUpdateRate, out int pRevisedUpdateRate, IntPtr pActive, IntPtr pTimeBias, IntPtr pPercentDeadband, IntPtr pLCID, IntPtr phClientGroup)
        {
            throw new NotImplementedException();
        }

        void IOPCGroupStateMgt2.CloneGroup(string szName, ref Guid riid, out object ppUnk)
        {
            throw new NotImplementedException();
        }

        void IOPCGroupStateMgt2.GetKeepAlive(out int pdwKeepAliveTime)
        {
            throw new NotImplementedException();
        }

        void IOPCGroupStateMgt2.GetState(out int pUpdateRate, out int pActive, out string ppName, out int pTimeBias, out float pPercentDeadband, out int pLCID, out int phClientGroup, out int phServerGroup)
        {
            throw new NotImplementedException();
        }

        void IOPCGroupStateMgt2.SetKeepAlive(int dwKeepAliveTime, out int pdwRevisedKeepAliveTime)
        {
            throw new NotImplementedException();
        }

        void IOPCGroupStateMgt2.SetName(string szName)
        {
            throw new NotImplementedException();
        }

        void IOPCGroupStateMgt2.SetState(IntPtr pRequestedUpdateRate, out int pRevisedUpdateRate, IntPtr pActive, IntPtr pTimeBias, IntPtr pPercentDeadband, IntPtr pLCID, IntPtr phClientGroup)
        {
            throw new NotImplementedException();
        }

        public void AddItems(int dwCount, OPCITEMDEF[] pItemArray, out IntPtr ppAddResults, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        public void CreateEnumerator(ref Guid riid, out object ppUnk)
        {
            throw new NotImplementedException();
        }

        public void RemoveItems(int dwCount, int[] phServer, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        public void SetActiveState(int dwCount, int[] phServer, int bActive, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        public void SetClientHandles(int dwCount, int[] phServer, int[] phClient, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        public void SetDatatypes(int dwCount, int[] phServer, short[] pRequestedDatatypes, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        public void ValidateItems(int dwCount, OPCITEMDEF[] pItemArray, int bBlobUpdate, out IntPtr ppValidationResults, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        void IOPCSyncIO.Read(OPCDATASOURCE dwSource, int dwCount, int[] phServer, out IntPtr ppItemValues, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        void IOPCSyncIO.Write(int dwCount, int[] phServer, object[] pItemValues, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        void IOPCSyncIO2.Read(OPCDATASOURCE dwSource, int dwCount, int[] phServer, out IntPtr ppItemValues, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        void IOPCSyncIO2.ReadMaxAge(int dwCount, int[] phServer, int[] pdwMaxAge, out IntPtr ppvValues, out IntPtr ppwQualities, out IntPtr ppftTimeStamps, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        void IOPCSyncIO2.Write(int dwCount, int[] phServer, object[] pItemValues, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        void IOPCSyncIO2.WriteVQT(int dwCount, int[] phServer, OPCITEMVQT[] pItemVQT, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO2.Cancel2(int dwCancelID)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO2.GetEnable(out int pbEnable)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO2.Read(int dwCount, int[] phServer, int dwTransactionID, out int pdwCancelID, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO2.Refresh2(OPCDATASOURCE dwSource, int dwTransactionID, out int pdwCancelID)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO2.SetEnable(int bEnable)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO2.Write(int dwCount, int[] phServer, object[] pItemValues, int dwTransactionID, out int pdwCancelID, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO3.Cancel2(int dwCancelID)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO3.GetEnable(out int pbEnable)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO3.Read(int dwCount, int[] phServer, int dwTransactionID, out int pdwCancelID, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO3.ReadMaxAge(int dwCount, int[] phServer, int[] pdwMaxAge, int dwTransactionID, out int pdwCancelID, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO3.Refresh2(OPCDATASOURCE dwSource, int dwTransactionID, out int pdwCancelID)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO3.RefreshMaxAge(int dwMaxAge, int dwTransactionID, out int pdwCancelID)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO3.SetEnable(int bEnable)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO3.Write(int dwCount, int[] phServer, object[] pItemValues, int dwTransactionID, out int pdwCancelID, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        void IOPCAsyncIO3.WriteVQT(int dwCount, int[] phServer, OPCITEMVQT[] pItemVQT, int dwTransactionID, out int pdwCancelID, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        public void ClearItemDeadband(int dwCount, int[] phServer, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        public void GetItemDeadband(int dwCount, int[] phServer, out IntPtr ppPercentDeadband, out IntPtr ppErrors)
        {
            throw new NotImplementedException();
        }

        public void SetItemDeadband(int dwCount, int[] phServer, float[] pPercentDeadband, out IntPtr ppErrors)
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
    }
}
