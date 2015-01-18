
local n = 1

local SystemClass = class("MonsterFactorySystem", function(system_name, com_name)
    return ECS.createSystemBase(system_name, com_name)
end)

function SystemClass:onAttached()
    self.m_monsters = {}
    self.m_monster_num = 0

    self:registerEvent("onDestroyMonster", handler(self, self.onDestroyMonster))

    self:registerScheduler(handler(self, self.createMonster), 1)
end

function SystemClass:onDestroyMonster(event)
    local monster = event.args.monster
    
    if monster and self.m_monsters[monster] then
        ECS.destroyObject(monster)
        
        self.m_monsters[monster] = nil
        self.m_monster_num = self.m_monster_num - 1
        
        -- 通知怪物已经销毁
        self:dispatchEvent("onMonsterDestroyed", {node=monster:getNode()})
    end
end

function SystemClass:createMonster()
    if self.m_monster_num > 2 then
        return
    end

    -- 随机怪物
    local n = math.random(1,2)
    local monster_name 
    if n == 1 then
        monster_name = "Monster/MonsterDinosaur"
    else
        monster_name = "Monster/MonsterMushroom"
    end
    
    -- 随机怪物位置
    local pos_x, pos_y
    local n = math.random(1,4)
    local offset = -100
    if n == 1 then
        pos_y = display.top + offset
        pos_x = math.random(display.left - offset, display.right + offset)
    elseif n == 2 then
        pos_x = display.right + offset
        pos_y = math.random(display.bottom - offset, display.top + offset)
    elseif n == 3 then
        pos_y = display.bottom - offset
        pos_x = math.random(display.left - offset, display.right + offset)
    else
        pos_x = display.left - offset
        pos_y = math.random(display.bottom - offset, display.top + offset)
    end
    
    -- 创建怪物
    local monster = ECS.createObject(monster_name)
    monster:getNode():setPosition(pos_x, pos_y)
    
    self.m_monsters[monster] = true
    self.m_monster_num = self.m_monster_num + 1
    
    -- 设置怪物AI
    local com_factory = self:getComByType("Manager/MonsterFactoryCom")
    local com_ai = monster:getComByType("AI/MoveToTargetCom")
    if com_factory and com_ai then
        com_ai.target = com_factory.target
    else
        assert(false)
    end

    -- 通知怪物已经创建好
    self:dispatchEvent("onMonsterCreated", {node=monster:getNode()})
end

return SystemClass
