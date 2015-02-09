using System;
using System.Collections.Generic;

namespace IEC61850Bridge
{
	public class LNodeType : AbstractNode
	{
		public const string NODE_NAME = "LNodeType";

		public string desc { get; set; }
		public string id { get; set; }
		public string iedType { get; set; }
		public string lnClass { get; set; }

		public List<DO> DOs = new List<DO>();

		public void AddDO(DO doToAdd)
		{
			DOs.Add(doToAdd);
		}
	}
}
