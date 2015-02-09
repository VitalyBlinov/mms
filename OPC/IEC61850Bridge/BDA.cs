using System;

namespace IEC61850Bridge
{
	public class BDA : AbstractNode
	{
		public const string NODE_NAME = "BDA";

		public string bType { get; set; }
		public string count { get; set; }
		public string desc { get; set; }
		public string name { get; set; }
		public string sAddr { get; set; }
		public string type { get; set; }
		public string valKind { get; set; }
	}
}
