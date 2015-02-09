using System;
using System.Collections.Generic;

namespace IEC61850Bridge
{
	public class DataSet
	{
		public const string NODE_NAME = "DataSet";

		public string desc { get; set; }
		public string name { get; set; }

		public Dictionary<string, FCDA> FCDAs = new Dictionary<string, FCDA>();

		public void AddFCDA(FCDA fcda)
		{
			FCDAs.Add(fcda.prefix + fcda.lnClass + fcda.lnInst + "." + fcda.doName, fcda);
		}
	}
}
