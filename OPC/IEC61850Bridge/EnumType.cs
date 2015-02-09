using System;
using System.Collections.Generic;

namespace IEC61850Bridge
{
	public class EnumType : AbstractNode
	{
		public const string NODE_NAME = "EnumType";

		public string desc { get; set; }
		public string id { get; set; }

		public Dictionary<string, EnumVal> EnumVals = new Dictionary<string, EnumVal>();

		public void AddEnumVal(EnumVal enumVal)
		{
			EnumVals.Add(enumVal.value, enumVal);
		}
	}
}