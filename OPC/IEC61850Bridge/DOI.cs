using System.Collections.Generic;

namespace IEC61850Bridge
{
	public class DOI : IAddDAI
	{
		public const string NODE_NAME = "DOI";

		public string name { get; set; }
		public string desc { get; set; }
		public string accessControl { get; set; }
		public string ix { get; set; }

		public Dictionary<string, DAI> DAIs = new Dictionary<string, DAI>();
		public Dictionary<string, SDI> SDIs = new Dictionary<string, SDI>();

		public void AddDAI(DAI dai)
		{
			this.DAIs.Add(dai.name, dai);
		}

		public void AddSDI(SDI sdi)
		{
			this.SDIs.Add(sdi.name, sdi);
		}
	}

	public interface IAddDAI
	{
		void AddDAI(DAI dai);
	}
}