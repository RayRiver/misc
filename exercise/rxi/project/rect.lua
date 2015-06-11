
local Utils = require("utils")

local ObjectClass = Utils.Class("Rect")

function ObjectClass:initialize(x, y, width, height)
    self.x = x or 0
    self.y = y or 0
    self.width = width or 0
    self.height = height or 0
end

function ObjectClass:set(x, y, width, height)
    self.x = x or self.x
    self.y = y or self.y
    self.width = width or self.width
    self.height = height or self.height
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
    if val then self.x = val - self.width end
    return self.x + self.width
end

function ObjectClass:top(val)
    if val then self.y = val end
    return self.y
end

function ObjectClass:bottom(val)
    if val then self.y = val - self.height end
    return self.y + self.height
end

function ObjectClass:middleX(val)
    if val then self.x = val - self.width / 2 end
    return self.x + self.width / 2
end

function ObjectClass:middleY(val)
    if val then self.y = val - self.height / 2 end
    return self.y + self.height / 2
end

function ObjectClass:equals(other)
    return self.x == other.x and
            self.y == other.y and
            self.width == other.width and
            self.height == other.height
end

function ObjectClass:contains(other)
    return other.x >= self.x and
            other.x + other.width <= self.x + self.width and
            other.y >= self.y and
            other.y + other.height <= self.y + self.height
end

function ObjectClass:overlapsPoint(x, y)
    return x > self.x and
            x < self.x + self.width and
            y > self.y and
            y < self.y + self.height
end

function ObjectClass:overlapsX(other)
    return self.x < other.x + other.width and
            other.x < self.x + self.width
end

function ObjectClass:overlapsY(other)
    return self.y < other.y + other.height and
            other.y < self.y + self.height
end

function ObjectClass:overlaps(other)
    return self.x < other.x + other.width and
            other.x < self.x + self.width and
            self.y < other.y + other.height and
            other.y < self.y + self.height
end

function ObjectClass:__tostring()
    return string.format("x, y, width, height = " ..
            tostring(self.x) .. ", " ..
            tostring(self.y) .. ", " ..
            tostring(self.width) .. ", " ..
            tostring(self.height)
    )
end

return ObjectClass
