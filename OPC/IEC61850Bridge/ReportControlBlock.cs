using System;

namespace IEC61850Bridge
{
	public class ReportControlBlock
	{
		public const string NODE_NAME = "ReportControl";

		public OptFields OptFields;
		public RptEnabled RptEnabled;
		public TrgOps TrgOps;

		public string buffered { get; set; }
		public string bufTime { get; set; }
		public string confRev { get; set; }
		public string datSet { get; set; }
		public string desc { get; set; }
		public string intgPd { get; set; }
		public string name { get; set; }
		public string rptID { get; set; }
	}

	public class OptFields
	{
		public const string NODE_NAME = "OptFields";

		public string bufOvfl { get; set; }
		public string configRef { get; set; }
		public string dataRef { get; set; }
		public string dataSet { get; set; }
		public string entryID { get; set; }
		public string reasonCode { get; set; }
		public string segmentation { get; set; }
		public string seqNum { get; set; }
		public string timeStamp { get; set; }
	}

	public class TrgOps
	{
		public const string NODE_NAME = "TrgOps";

		public string dchg { get; set; }
		public string dupd { get; set; }
		public string period { get; set; }
		public string qchg { get; set; }
	}

	public class RptEnabled
	{
		public const string NODE_NAME = "RptEnabled";

		public ClientLN ClientLN;

		public string desc { get; set; }
		public string max { get; set; }
	}

	public class ClientLN
	{
		public const string NODE_NAME = "ClientLN";

		public string iedName { get; set; }
		public string ldInst { get; set; }
		public string lnClass { get; set; }
		public string lnInst { get; set; }
		public string prefix { get; set; }
	}
}
