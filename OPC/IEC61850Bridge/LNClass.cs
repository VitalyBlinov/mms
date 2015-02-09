using System.Collections.Generic;

namespace IEC61850Bridge
{
	public class LNClass
	{
		public string Clause { get; set; }
		public string Description { get; set; }
		public string Name { get; set; }
		public string Part { get; set; }
		public string Remark { get; set; }

		private static Dictionary<string, string> LNGroups = LNClass.InitLNGroups();
		private static List<LNClass> LNClasses = LNClass.InitLNClasses();

		public static List<LNClass> InitLNClasses()
		{
			List<LNClass> list = new List<LNClass>();

			LNClass.LNClasses.Add(new LNClass()
			{
				Clause = "",
				Description = "",
				Name = "",
				Part = "",
				Remark = ""
			});

			LNClass.LNClasses.Add(new LNClass()
			{
				Clause = "5.3.2",
				Description = "Physical device information",
				Name = "LPHD",
				Part = "7-4 Ed2",
				Remark = ""
			});

			return list;
		}

		public static LNClass getLNClass(string lnClass)
		{
			return null;
		}

		public static string getLNGroup(string lnClass)
		{
			string key = lnClass.Substring(0, 1);
			
			if (LNClass.LNGroups.ContainsKey(key))
				return LNClass.LNGroups[key];
			
			return string.Empty;
		}

		public static Dictionary<string, string> InitLNGroups()
		{
			return new Dictionary<string, string>()
			{	
				{ "L", "System LNs"	},
				{ "A", "Automatic Control" },
				{ "C", "Control" },
				{ "D", "Decentralized Energy Resources" },
				{ "F", "Functional Blocks"	},
				{ "G", "Generic" },
				{ "H", "Hydro Power" },
				{ "I", "Interfacing and Archiving" },
				{ "K", "Mechanical and non-electric primary equipment" },
				{ "M", "Metering and measurment" },
				{ "P", "Protection Functions" },
				{ "Q", "Power quality events" },
				{ "R", "Protection related functions" },
				{ "S", "Supervision and monitoring" },
				{ "T", "Instrument Transformers and Sensors" },
				{ "W", "Wind Turbines" },
				{ "X", "Switchgear" },
				{ "Y", "Power Transformers" },
				{ "Z", "Further power system equipment"	}
			};
		}
	}
}
