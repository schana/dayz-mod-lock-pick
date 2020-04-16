static string DIR = "$profile:SchanaModLockPick";
static string PATH = DIR + "\\config.json";

class SchanaModCarLockPickSettings
{
    private static bool initialized = false;
    private static ref SchanaModCarLockPickSettings settings;

    float unlock_time_seconds = 30.0;
    int unlock_tool_damage = 100;
    int unlock_success_rate_percent = 100;

    static ref SchanaModCarLockPickSettings Get()
    {
        if (initialized)
        {
            return settings;
        }

        ref SchanaModCarLockPickSettings data = new ref SchanaModCarLockPickSettings;

        if (FileExist(PATH))
        {
            JsonFileLoader<SchanaModCarLockPickSettings>.JsonLoadFile(PATH, data);
            initialized = true;
        }
        else
        {
            if (GetGame().IsServer() || !GetGame().IsMultiplayer())
            {
                MakeDirectory(DIR);
                JsonFileLoader<SchanaModCarLockPickSettings>.JsonSaveFile(PATH, data);
            }
        }

        settings = data;

        return settings;
    }
}
