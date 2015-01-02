
require("config")
require("framework.init")

local AppClass = class("AppClass")

function AppClass:ctor()
    app = self
    
    -- 初始化game system
    local ecs = ECS.gameSystem:getECS()
    
    local content = cc.FileUtils:getInstance():getStringFromFile("ECS/Coms.json")
    local ECS_COMS = json.decode(content)
    for _, com_name in ipairs(ECS_COMS) do
        ecs:registerCom(require("Coms." .. com_name).new())
    end
    
    local content = cc.FileUtils:getInstance():getStringFromFile("ECS/Systems.json")
    local ECS_SYSTEMS = json.decode(content)
    for _, system_name in ipairs(ECS_SYSTEMS) do
        ecs:registerSystem(require("Systems." .. system_name).new())
    end
end

function AppClass:run()
    app:enterScene("EntryScene")
end

function AppClass:enterScene(scene_name)
    local scene = require("Scenes." .. scene_name).new()
    if cc.Director:getInstance():getRunningScene() then
        cc.Director:getInstance():replaceScene(scene)
    else
        cc.Director:getInstance():runWithScene(scene)
    end
end

return AppClass
