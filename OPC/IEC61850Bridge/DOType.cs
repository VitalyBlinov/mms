using System;
using System.Collections.Generic;

namespace IEC61850Bridge
{
	public class DOType
	{
		public const string NODE_NAME = "DOType";

		public string cdc { get; set; }
		public string id { get; set; }
		public string iedType { get; set; }
		public string lnClass { get; set; }

		public Dictionary<string, DA> DAs = new Dictionary<string, DA>();
		public Dictionary<string, SDO> SDOs = new Dictionary<string, SDO>();

		public void AddDA(DA da)
		{
			DAs.Add(da.name, da);
		}

		public void AddSDO(SDO sdo)
		{
			SDOs.Add(sdo.name, sdo);
		}
	}
}