using System;

namespace IEC61850Bridge
{
	public class SDO : AbstractNode
	{
		public const string NODE_NAME = "SDO";

		public string desc { get; set; }
		public string name { get; set; }
		public string type { get; set; }
	}
}
