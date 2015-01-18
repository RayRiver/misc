
local ComClass = class("GameSceneCom", function(com_name) 
    return ECS.createComBase(com_name)
end)

function ComClass:ctor()

end

return ComClass