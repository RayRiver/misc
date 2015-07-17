
local lib = import("..init")

local ObjectClass = lib.Class("Node")

function ObjectClass:__tostring()
    return string.format("{%s:%s}", self.class.name, self.m_name)
end

function ObjectClass:initialize(name, precondition)
    self.m_children = {}
    self.m_name = name or ""

    if precondition then
        self:setPrecondition(precondition)
    end

    lib.debugFormat("node %s initialize", tostring(self))
end

function ObjectClass:setName(name)
    self.m_name = name or ""
end

function ObjectClass:getName(name)
    return self.m_name
end

function ObjectClass:addChild(child, name)
    table.insert(self.m_children, child)
    if name then
        child:setName(name)
    end
    return self
end

function ObjectClass:setPrecondition(precondition)
    self.m_precondition = precondition
end

function ObjectClass:evaluate(input)
    lib.debugFormat("node %s evaluate", tostring(self))
    return (self.m_precondition == nil or self.m_precondition:onEvaluate(input)) and self:onInternalEvaluate(input)
end

function ObjectClass:transition(input)
    lib.debugFormat("node %s transition", tostring(self))
    return self:onTransition(input)
end

function ObjectClass:update(owner, input, output)
    lib.debugFormat("node %s update", tostring(self))
    return self:onUpdate(owner, input, output)
end

-- override me
function ObjectClass:onInternalEvaluate(input)
    return true
end

-- override me
function ObjectClass:onTransition(input)

end

-- override me
function ObjectClass:onUpdate(owner, input, output)

end

return ObjectClass
