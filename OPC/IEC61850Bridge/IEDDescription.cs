using System;
using System.Collections.Generic;

namespace IEC61850Bridge
{
	public class IEDDescription
	{
		public const string NODE_NAME = "IED";

		public string configVersion { get; set; }
		public string desc { get; set; }
		public string manufacturer { get; set; }
		public string name { get; set; }
		public string type { get; set; }

		public List<LDevice> LDevices = new List<LDevice>();

		public void AddLDevice(LDevice ldevice)
		{
			LDevices.Add(ldevice);
		}
	}
}
