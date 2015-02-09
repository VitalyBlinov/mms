using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Reflection;

namespace IEC61850Bridge
{
	public static class Btype
	{
		public const string BOOLEAN = "BOOLEAN";
		public const string INT8 = "INT8";
		public const string INT16 = "INT16";
		public const string INT24 = "INT24";
		public const string INT32 = "INT32";
		public const string INT128 = "INT128";
		public const string INT8U = "INT8U";
		public const string INT16U = "INT16U";
		public const string INT24U = "INT24U";
		public const string INT32U = "INT32U";
		public const string FLOAT32 = "FLOAT32";
		public const string FLOAT64 = "FLOAT64";
		public const string Enum = "Enum";
		public const string Dbpos = "Dbpos";
		public const string Tcmd = "Tcmd";
		public const string Quality = "Quality";
		public const string Timestamp = "Timestamp";
		public const string VisString32 = "VisString32";
		public const string VisString64 = "VisString64";
		public const string VisString255 = "VisString255";
		public const string Octet64 = "Octet64";
		public const string Struct = "Struct";
		public const string EntryTime = "EntryTime";
		public const string Unicode255 = "Unicode255";

		public static string GetDescription<T>(this T enumerationValue) where T : struct
		{
			Type type = enumerationValue.GetType();
			
			if (!type.IsEnum)
				throw new ArgumentException("EnumerationValue must be of Enum type", "enumerationValue");
			
			string name = enumerationValue.ToString();
			MemberInfo[] member = type.GetMember(name);
			
			if (member != null && member.Length > 0)
			{
				object[] customAttributes = member[0].GetCustomAttributes(typeof(DescriptionAttribute), false);
			
				if (customAttributes != null && customAttributes.Length > 0)
					return ((DescriptionAttribute)customAttributes[0]).Description;
			}

			return name;
		}
	}

	public class Quality : AbstractNode
	{
		public OperatorBlocked operatorBlocked { get; set; }
		public SourceType source { get; set; }
		public Test test { get; set; }
		public ValidityType validity { get; set; }
		public List<QualityDetail> qualityDetails;

		public Quality()
		{
			this.InitQualityDetails();
			this.validity = new ValidityType();
			this.source = new SourceType();
			this.test = new Test();
			this.operatorBlocked = new OperatorBlocked();
		}

		private void InitQualityDetails()
		{
			this.qualityDetails = new List<QualityDetail>()
			{
				new QualityDetail { VisibleText = "Overflow", name = "overflow", value = false },
				new QualityDetail { VisibleText = "OutOfRange", name = "outOfRange", value = false },
				new QualityDetail { VisibleText = "BadReference", name = "badReference", value = false },
				new QualityDetail { VisibleText = "Oscillatory", name = "oscillatory", value = false },
				new QualityDetail { VisibleText = "Failure", name = "failure", value = false },
				new QualityDetail { VisibleText = "OldData", name = "oldData", value = false },
				new QualityDetail { VisibleText = "Inconsistent", name = "inconsistent", value = false },
				new QualityDetail { VisibleText = "Inaccurate", name = "inaccurate", value = false }
			};
		}
	}

	public class QualityDetail : AbstractNode
	{
		public string name { get; set; }
		public bool value { get; set; }
	}

	public class QualityDetails : AbstractNode
	{
		public QualityDetails()
		{
			this.VisibleText = "Quality Details";
		}
	}

	public class ValidityType : AbstractNode
	{
		public ValidityType()
		{
			this.VisibleText = "Validity";
		}

		public ValidityType.ValidityTypeEnum value { get; set; }

		public enum ValidityTypeEnum
		{
			[Description("good")]
			Good,
			[Description("invalid")]
			Invalid,
			[Description("reserved")]
			Reseved,
			[Description("questionable")]
			Questionable
		}
	}

	public class SourceType : AbstractNode
	{
		public SourceType()
		{
			this.VisibleText = "Source";
		}

		public SourceType.SourceTypeEnum value { get; set; }

		public enum SourceTypeEnum
		{
			[Description("process")]
			Process,
			[Description("substituted")]
			Substituted
		}
	}

	public class OperatorBlocked : AbstractNode
	{
		public bool value { get; set; }

		public OperatorBlocked()
		{
			this.VisibleText = "OperatorBlocked";
		}
	}

	public class Test : AbstractNode
	{
		public bool value { get; set; }

		public Test()
		{
			this.VisibleText = "Test";
		}
	}

	public class Struct : AbstractNode
	{
	}
}
