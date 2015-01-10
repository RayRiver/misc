
local SystemClass = class("GameSceneSystem", function(system_name, com_name)
    return ECS.createSystem(system_name, com_name)
end)

function SystemClass:onAttached()
    local node = self:getComByType("NodeCom")
    if node then

    end
    
    -- 创建小象
    local elephant = ECS.createObject("Elephant")
    elephant:getNode():setPosition(display.cx, display.cy)
    self:getNode():addChild(elephant:getNode())
    
    -- 创建怪物工厂
    local monster_factory = ECS.createObject("Manager/MonsterFactory")
    local com = monster_factory:getComByType("Manager/MonsterFactoryCom")
    if com then
        com.target = elephant
    else
        assert(false)
    end
    
    -- 注册事件
    self:registerEvent("onMonsterCreated", handler(self, self.onMonsterCreated))
    self:registerEvent("onMonsterDestroyed", handler(self, self.onMonsterDestroyed))
end

function SystemClass:onMonsterCreated(event)
    self:getNode():addChild(event.args.node)
end

function SystemClass:onMonsterDestroyed(event)
    self:getNode():removeChild(event.args.node)
end

return SystemClass
