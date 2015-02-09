using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IEC61850Bridge
{
    /// <summary>
    /// IED connection
    /// </summary>
    public interface IConnection
    {
	    /// <summary>
        /// Opens this connection
        /// </summary>
        /// <param name="connectCallback"></param>
		void Open(onConnect connectCallback);

		/// <summary>
		/// Closes the connection
		/// </summary>
		/// <param name="connectCallback">Callback invoked when conneciton is succesfully closed</param>
		void Close(onConnect connectCallback);

	    void Discover();
	}

    /// <summary>
    /// Connection callback interface
    /// </summary>
    public interface onConnect
    {
        void onConnect(bool status);
    };
    
	/// <summary>
    /// Scan callback interface
    /// </summary>
    public interface onScanStatus
    {
        /// <summary>
        /// called when progress is updated
        /// </summary>
        /// <param name="scanned">number of items already scanned</param>
        /// <param name="total">total number of items</param>
        void progressUpdate(int scanned, int total);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="description"></param>
        void onScanComplete(IEDDescription description);
    }
}
