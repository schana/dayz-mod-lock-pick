class SchanaModCarLockPick extends Inventory_Base
{
    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionSchanaUnlockCarDoor);
    }
}
