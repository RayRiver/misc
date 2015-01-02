
local ComClass = class("GameSceneCom", function(com_name) 
    return ECS.createCom(com_name)
end)

function ComClass:ctor()

end

return ComClass