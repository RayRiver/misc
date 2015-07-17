
local BT = bt

local Common = BT.import(".common")

local ObjectClass = Common.Class("Factory")

local s_instance
function ObjectClass:instance()
    if not s_instance then
        s_instance = ObjectClass:create()
    end
    return s_instance
end

function ObjectClass:initialize()
    self.m_node_class_map = {}
    self.m_cond_class_map = {}
end

function ObjectClass:registerNodeClass(node_type, node_class)
    assert(node_type)
    assert(node_class)
    assert(not self.m_node_class_map[node_type])
    self.m_node_class_map[node_type] = node_class
end

function ObjectClass:createNode(node_type, ...)
    local node_class = self.m_node_class_map[node_type]
    if node_class then
        return node_class:create(...)
    else
        local node_class = require(node_type)
        if node_class then
            self:registerNodeClass(node_type, node_class)
            return node_class:create(...)
        else
            return nil
        end
    end
end

function ObjectClass:registerCondClass(cond_type, cond_class)
    assert(cond_type)
    assert(cond_class)
    assert(not self.m_cond_class_map[cond_type])
    self.m_cond_class_map[cond_type] = cond_class
end

function ObjectClass:createCond(cond_type, ...)
    local cond_class = self.m_cond_class_map[cond_type]
    if cond_class then
        return cond_class:create(...)
    else
        return nil
    end
end

return ObjectClass
