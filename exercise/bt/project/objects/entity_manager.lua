
local lib = require("lib.init")

local function generateEntityId(self)
    self.m_generated_entity_id = self.m_generated_entity_id + 1
    return self.m_generated_entity_id
end

local ObjectClass = lib.Class("EntityManager")

local s_instance
function ObjectClass:instance()
    if not s_instance then
        s_instance = ObjectClass:create()
    end
    return s_instance
end

function ObjectClass:initialize()
    self.m_entities = {}

    self.m_generated_entity_id = 0
end

function ObjectClass:destroy()
    self:destroyAllEntities()

    self.m_generated_entity_id = 0

    self.m_world = nil
    self.m_blackboard = nil
end

function ObjectClass:setWorld(world)
    self.m_world = world
end

function ObjectClass:setBlackboard(blackboard)
    self.m_blackboard = blackboard
end

function ObjectClass:createEntity(config)
    local id = generateEntityId(self)
    local entity_class = require(config.class)
    local entity = entity_class:create(config, id, self.m_world, self.m_blackboard)
    self.m_entities[id] = entity
    return entity
end

function ObjectClass:destroyEntity(entity)
    local id = entity:getId()
    self.m_entities[id] = nil
    entity:destroy()
end

function ObjectClass:destroyEntityById(entity_id)
    local entity = self.m_entities[entity_id]
    if entity then
        self:destroyEntity(entity)
    end
end

function ObjectClass:destroyAllEntities()
    for _, entity in pairs(self.m_entities) do
        self:destroyEntity(entity)
    end
end

return ObjectClass
