
local COM_NAME = "EntrySceneCom"

local ComClass
ComClass = class(COM_NAME, function() 
    return ECS.createCom(ComClass, COM_NAME)
end)

function ComClass:ctor()

end

return ComClass
