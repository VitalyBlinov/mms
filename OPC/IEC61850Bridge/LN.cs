using System;
using System.Collections.Generic;

namespace IEC61850Bridge
{
	public class LN : AbstractNode
	{
		public const string NODE_NAME = "LN";

		public string desc { get; set; }
		public string inst { get; set; }
		public string lnClass { get; set; }
		public string lnType { get; set; }
		public string prefix { get; set; }

		public Dictionary<string, DOI> DOIs = new Dictionary<string, DOI>();

		public void AddDOI(DOI doi)
		{
			DOIs.Add(doi.name, doi);
		}
	}
}