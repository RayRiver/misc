
require("config")
require("framework.init")

local AppClass = class("AppClass")

function AppClass:ctor()
    app = self
    
    -- 初始化game system
    local ecs = ECS.gameSystem:getECS()
    
    local content = cc.FileUtils:getInstance():getStringFromFile("ECS/Coms.json")
    local ECS_COMS = json.decode(content)
    for _, com in ipairs(ECS_COMS) do
        ecs:registerCom(ECS.comFactory(com.name))
    end
    
    local content = cc.FileUtils:getInstance():getStringFromFile("ECS/Systems.json")
    local ECS_SYSTEMS = json.decode(content)
    for _, system in ipairs(ECS_SYSTEMS) do
        local s = ECS.systemFactory(system.name, system.com)
        ecs:registerSystem(s)
        print("register system: ", tostring(system.name), tostring(s))
    end
end

function AppClass:run()
    app:enterScene("EntryScene")
end

function AppClass:enterScene(scene_name)
    local scene = ECS.createScene(scene_name)
    if cc.Director:getInstance():getRunningScene() then
        cc.Director:getInstance():replaceScene(scene)
    else
        cc.Director:getInstance():runWithScene(scene)
    end
end

return AppClass
