
local Utils = require("utils")

local ObjectClass = Utils.Class("Rect")

function ObjectClass:initialize(x, y, width, height)
    self.x = x or 0
    self.y = y or 0
    self.width = width or 0
    self.height = width or 0
end

function ObjectClass:getPosition()
    return self.x, self.y
end

function ObjectClass:getSize()
    return self.width, self.height
end

function ObjectClass:left(val)
    if val then self.x = val end
    return self.x
end

function ObjectClass:right(val)

end

return ObjectClass
