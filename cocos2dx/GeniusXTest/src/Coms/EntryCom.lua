
local COM_NAME = "EntryCom"

local ComClass
ComClass = class(COM_NAME, function() 
    return ECS.createCom(ComClass, COM_NAME)
end)

function ComClass:ctor()

end

return ComClass
