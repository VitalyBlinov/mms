using System;

namespace IEC61850Bridge
{
	public class DA : AbstractNode
	{
		public const string NODE_NAME = "DA";
		public const string VAL_NODE_NAME = "Val";

		public string bType { get; set; }
		public string count { get; set; }
		public string dchg { get; set; }
		public string desc { get; set; }
		public string dupd { get; set; }
		public string fc { get; set; }
		public string name { get; set; }
		public string qchg { get; set; }
		public string sAddr { get; set; }
		public string type { get; set; }
		public string Val { get; set; }
		public string valKind { get; set; }
	}
}
