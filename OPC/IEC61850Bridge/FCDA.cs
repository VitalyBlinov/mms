using System;

namespace IEC61850Bridge
{
	public class FCDA
	{
		public const string NODE_NAME = "FCDA";

		public string daName { get; set; }
		public string doName { get; set; }
		public string fc { get; set; }
		public string ldInst { get; set; }
		public string lnClass { get; set; }
		public string lnInst { get; set; }
		public string prefix { get; set; }
	}
}
