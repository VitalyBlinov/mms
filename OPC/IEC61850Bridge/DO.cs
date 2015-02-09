namespace IEC61850Bridge
{
	public class DO : AbstractNode
	{
		public const string NODE_NAME = "DO";

		public string name { get; set; }
		public string type { get; set; }
		public string accessControl { get; set; }
		public string transient { get; set; }
	}
}