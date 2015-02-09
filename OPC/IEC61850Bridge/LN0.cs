using System;

namespace IEC61850Bridge
{
	public class LN0 : AbstractNode
	{
		public const string NODE_NAME = "LN0";

		public string desc { get; set; }
		public string inst { get; set; }
		public string lnClass { get; set; }
		public string lnType { get; set; }
	}
}
