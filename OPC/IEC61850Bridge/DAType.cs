using System;
using System.Collections.Generic;

namespace IEC61850Bridge
{
	public class DAType
	{
		public const string NODE_NAME = "DAType";

		public string id { get; set; }
		public string iedType { get; set; }

		public Dictionary<string, BDA> BDAs = new Dictionary<string, BDA>();

		public void AddBDA(BDA bda)
		{
			BDAs.Add(bda.name, bda);
		}
	}
}
