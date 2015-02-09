using System;

namespace IEC61850Bridge
{
	public class DAI
	{
		public const string NODE_NAME = "DAI";

		public string desc { get; set; }
		public string ix { get; set; }
		public string name { get; set; }
		public string sAddr { get; set; }
		public string Val { get; set; }
		public string valKind { get; set; }

		public string CreateValNode()
		{
			return "<Val>" + Val + "</Val>";
		}
	}
}
