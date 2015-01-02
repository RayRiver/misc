
local _M = {}

_M.gameSystem = gx.GameSystem:getInstance()

_M.createSystem = import(".SystemBase")
_M.createCom = import(".ComBase")

_M.createScene = function(scene_name)
    return _M.gameSystem:getECS():createEntity("ECS/Scenes/" .. scene_name .. ".json")
end

return _M
