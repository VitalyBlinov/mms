using System;
using System.Collections.Generic;

namespace IEC61850Bridge
{
	public class LDevice : AbstractNode
	{
		public const string NODE_NAME = "LDevice";

		public string desc { get; set; }
		public string inst { get; set; }
		public LN0 LN0 { get; set; }

		public Dictionary<string, DataSet> DataSets = new Dictionary<string, DataSet>();
		public Dictionary<string, LN> LNodes = new Dictionary<string, LN>();
		public Dictionary<string, ReportControlBlock> ReportControlBlocks = new Dictionary<string, ReportControlBlock>();

		public void AddDataset(DataSet dataSet)
		{
			DataSets.Add(dataSet.name, dataSet);
		}

		public void AddLNode(LN lnode)
		{
			LNodes.Add(lnode.prefix + lnode.lnClass + lnode.inst, lnode);
		}

		public void AddReportControlBlock(ReportControlBlock reportControlBlock)
		{
			ReportControlBlocks.Add(reportControlBlock.name, reportControlBlock);
		}
	}
}
