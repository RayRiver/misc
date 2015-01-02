
local COM_NAME = "EntryCom"
local SYSTEM_NAME = "EntrySystem"

local SystemClass
SystemClass = class(SYSTEM_NAME, function()
    return ECS.createSystem(SystemClass, SYSTEM_NAME, COM_NAME)
end)

function SystemClass:ctor()

end

return SystemClass

