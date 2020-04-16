class ActionSchanaUnlockCarDoorCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        float time = SchanaModCarLockPickSettings.Get().unlock_time_seconds;
        m_ActionData.m_ActionComponent = new CAContinuousRepeat(time);
    }
}

class ActionSchanaUnlockCarDoor : ActionContinuousBase
{
    void ActionSchanaUnlockCarDoor()
    {
        m_CallbackClass = ActionSchanaUnlockCarDoorCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINonRuined;
        m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
    }

    override string GetText()
    {
        return "#unlock";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!target)
            return false;

        if (!target.GetObject().IsInherited(CarDoor))
            return false;

        if (isCarDoorHood(target))
            return false;

        CarScript carScript;
        if (Class.CastTo(carScript, target.GetParent()))
        {
            if (carScript.m_Trader_HasKey && carScript.m_Trader_Locked && !player.m_Trader_IsInSafezone && !carDoorIsOpen(target))
                return true;
        }

        return false;
    }

    protected bool carDoorIsOpen(ActionTarget target)
    {
        CarDoor carDoor = CarDoor.Cast(target.GetObject());

        CarScript car;
        if (Class.CastTo(car, target.GetParent()) && carDoor)
        {
            array<string> selections = new array<string>();
            carDoor.GetActionComponentNameList(target.GetComponentIndex(), selections);

            for (int i = 0; i < selections.Count(); i++)
            {
                string m_AnimSource = car.GetAnimSourceFromSelection(selections[i]);
                if (m_AnimSource != "")
                {
                    if (car.GetAnimationPhase(m_AnimSource) > 0.5)
                        return true;
                }
            }
        }

        return false;
    }

    protected bool isCarDoorHood(ActionTarget target)
    {
        CarDoor carDoor = CarDoor.Cast(target.GetObject());

        CarScript car;
        if (Class.CastTo(car, target.GetParent()) && carDoor)
        {
            array<string> selections = new array<string>();
            carDoor.GetActionComponentNameList(target.GetComponentIndex(), selections);

            for (int i = 0; i < selections.Count(); i++)
            {
                string m_AnimSource = car.GetAnimSourceFromSelection(selections[i]);
                if (m_AnimSource == "DoorsHood")
                    return true;
            }
        }

        return false;
    }

    override void OnFinishProgressServer(ActionData action_data)
    {
        int success_rate = SchanaModCarLockPickSettings.Get().unlock_success_rate_percent;
        
        CarScript carScript = CarScript.Cast(action_data.m_Target.GetParent());
        if (carScript)
        {
            string player = action_data.m_Player.GetIdentity().GetId();
            string owner = carScript.m_Trader_LastDriverId;
            string car = action_data.m_Target.GetObject().GetType();
            string position = action_data.m_Player.GetPosition().ToString();
            string format = "SchanaModCarLockPick used by " + player + " on " + car + " at " + position;
            if (Math.RandomInt(0, 100) < success_rate)
            {
                carScript.m_Trader_Locked = false;
                carScript.SynchronizeValues();
                GetGame().AdminLog("SUCCESS " + format);
            }
            else
            {
                GetGame().AdminLog("FAILURE " + format);
            }
        }
        int damage = SchanaModCarLockPickSettings.Get().unlock_tool_damage;
        action_data.m_MainItem.DecreaseHealth(damage, false);
    }
}
