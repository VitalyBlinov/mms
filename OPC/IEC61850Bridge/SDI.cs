using System;
using System.Collections.Generic;

namespace IEC61850Bridge
{
	public class SDI : IAddDAI
	{
		public const string NODE_NAME = "SDI";

		public string desc { get; set; }
		public string ix { get; set; }
		public string name { get; set; }

		public Dictionary<string, DAI> DAIs = new Dictionary<string, DAI>();

		public void AddDAI(DAI dai)
		{
			DAIs.Add(dai.name, dai);
		}
	}
}
