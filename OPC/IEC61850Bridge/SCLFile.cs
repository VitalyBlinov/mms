using System;
using System.Collections.Generic;

namespace IEC61850Bridge
{
	public class SCLFile
	{
		public Dictionary<string, DAType> DATypes = new Dictionary<string, DAType>();
		public Dictionary<string, DOType> DOTypes = new Dictionary<string, DOType>();
		public Dictionary<string, EnumType> EnumTypes = new Dictionary<string, EnumType>();
		public Dictionary<string, IEDDescription> IEDs = new Dictionary<string, IEDDescription>();
		public Dictionary<string, LNodeType> LNodeTypes = new Dictionary<string, LNodeType>();

		public void AddDAType(DAType daType)
		{
			DATypes.Add(daType.id, daType);
		}

		public void AddDOType(DOType doType)
		{
			DOTypes.Add(doType.id, doType);
		}

		public void AddEnumType(EnumType enumType)
		{
			EnumTypes.Add(enumType.id, enumType);
		}

		public void AddIEDDescription(IEDDescription ied)
		{
			IEDs.Add(ied.name, ied);
		}

		public void AddLNodeType(LNodeType lnodeType)
		{
			LNodeTypes.Add(lnodeType.id, lnodeType);
		}
	}
}