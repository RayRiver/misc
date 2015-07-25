
local lib = require("lib.init")

local ObjectClass = lib.Class("Component")

function ObjectClass:initialize(config)
    self.m_config = config
end

function ObjectClass:getConfig()
    return self.m_config
end

function ObjectClass:getOwner()
    return self.m_owner
end

function ObjectClass:attach(owner)
    self.m_owner = owner
    self:onAttached()
end

function ObjectClass:detach()
    self:onDetached()
end

function ObjectClass:update(dt)
    self:onUpdate(dt)
end

function ObjectClass:draw()
    self:onDraw()
end

-- override me
function ObjectClass:onAttached()

end

-- override me
function ObjectClass:onDetached()

end

-- override me
function ObjectClass:onUpdate(dt)

end

-- override me
function ObjectClass:onDraw()

end

return ObjectClass
