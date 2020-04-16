class CfgPatches
{
	class SchanaModLockPick
	{
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Gear_Tools",
			"Trader"
		};
	};
};

class CfgMods
{
	class SchanaModLockPick
	{
		type = "mod";

		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {
					"SchanaModLockPick/World"
				};
			};
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class SchanaModCarLockPick : Inventory_Base
	{
		scope = 2;
		displayName = "CarLockPick";
		descriptionShort = "A specialized tool to pick vehicle locks";
		model = "\dz\gear\tools\Lockpick.p3d";
		itemSize[] = {1, 2};
		rotationFlags = 17;
		weight = 200;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] =
					{
						{
							1.0,
							{
								"DZ\gear\tools\data\Lockpick.rvmat"
							}
						},
						{
							0.69999999,
							{
								"DZ\gear\tools\data\Lockpick.rvmat"
							}
						},
						{
							0.5,
							{
								"DZ\gear\tools\data\Lockpick_damage.rvmat"
							}
						},
						{
							0.30000001,
							{
								"DZ\gear\tools\data\Lockpick_damage.rvmat"
							}
						},
						{
							0.0,
							{
								"DZ\gear\tools\data\Lockpick_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class lockpicker_move_in
				{
					soundSet = "lockpicker_move_in_SoundSet";
					id = 110202;
				};
				class lockpicker_move_out
				{
					soundSet = "lockpicker_move_out_SoundSet";
					id = 110203;
				};
				class lockpicker_loop
				{
					soundSet = "lockpicker_loop_SoundSet";
					id = 203;
				};
				class lockpicker_end
				{
					soundSet = "lockpicker_end_SoundSet";
					id = 110204;
				};
			};
		};
	};
};
