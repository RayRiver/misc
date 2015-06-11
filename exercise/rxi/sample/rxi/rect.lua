local _ = require "lib.lume"
local Object = require "lib.classic"

local Rect = Object:extend()


function Rect:new(x, y, width, height)
  self.x = x or 0
  self.y = y or 0
  self.width = width or 0
  self.height = height or 0
end


function Rect:getPosition()
  return self.x, self.y
end


function Rect:getSize()
  return self.width, self.height
end


function Rect:set(x, y, width, height)
  self.x = x or self.x
  self.y = y or self.y
  self.width = width or self.width
  self.height = height or self.height
  return self
end


function Rect:clone(dest)
  dest = dest or Rect()
  dest.x = self.x
  dest.y = self.y
  dest.width = self.width
  dest.height = self.height
  return dest
end


function Rect:left(val)
  if val then self.x = val end
  return self.x
end


function Rect:right(val)
  if val then self.x = val - self.width end
  return self.x + self.width
end


function Rect:top(val)
  if val then self.y = val end
  return self.y
end


function Rect:bottom(val)
  if val then self.y = val - self.height end
  return self.y + self.height
end


function Rect:middleX(val)
  if val then self.x = val - self.width / 2 end
  return self.x + self.width / 2
end


function Rect:middleY(val)
  if val then self.y = val - self.height / 2 end
  return self.y + self.height / 2
end


function Rect:merge(r)
  local x1 = math.min(self:left(), r:left())
  local y1 = math.min(self:top(), r:top())
  local x2 = math.max(self:right(), r:right())
  local y2 = math.max(self:bottom(), r:bottom())
  self.x, self.y = x1, y1
  self.width =  math.max(0, x2 - x1)
  self.height =  math.max(0, y2 - y1)
  return self
end


function Rect:expand(amount)
  if amount > 0 then
    self.x = self.x - amount
    self.y = self.y - amount
    self.width = self.width + amount * 2
    self.height = self.height + amount * 2
  end
  self.width = math.max(0, self.width)
  self.height = math.max(0, self.height)
  return self
end


function Rect:clamp(r)
  if self.width > r.width then 
    self:middleX(r:middleX())
  else
    if self:left() < r:left() then self:left(r:left()) end
    if self:right() > r:right() then self:right(r:right()) end
  end
  if self.height > r.height then 
    self:middleY(r:middleY())
  else
    if self:top() < r:top() then self:top(r:top()) end
    if self:bottom() > r:bottom() then self:bottom(r:bottom()) end
  end
end


function Rect:clip(r)
  local x1 = math.max(self:left(), r:left())
  local y1 = math.max(self:top(), r:top())
  local x2 = math.min(self:right(), r:right())
  local y2 = math.min(self:bottom(), r:bottom())
  self.x, self.y = x1, y1
  self.width =  math.max(0, x2 - x1)
  self.height =  math.max(0, y2 - y1)
  return self
end


function Rect:reject(r)
  if not self:overlaps(r) then return end
  local diffx = self:middleX() - r:middleX()
  local diffy = self:middleY() - r:middleY()
  if math.abs(diffx) > math.abs(diffy) then
    if diffx > 0 then
      r:left(self:right())
    else
      r:right(self:left())
    end
  else
    if diffy > 0 then
      r:top(self:bottom())
    else
      r:bottom(self:top())
    end
  end
end


function Rect:equals(r)
  return self.x == r.x and self.y == r.y and
         self.width == r.width and self.height == r.height
end


function Rect:contains(r)
  return r.x >= self.x and r.x + r.width <= self.x + self.width and
         r.y >= self.y and r.y + r.height <= self.y + self.height
end


function Rect:overlapsX(r)
  return self.x < r.x + r.width and self.x + self.width > r.x
end


function Rect:overlapsY(r)
  return self.y < r.y + r.height and self.y + self.height > r.y
end


function Rect:overlaps(r)
  return r.x + r.width > self.x and r.x < self.x + self.width and
         r.y + r.height > self.y and r.y < self.y + self.height
end


function Rect:at(r)
  self.x = r.x + (r.width - self.width) / 2
  self.y = r.y + (r.height - self.height) / 2
end


function Rect:overlapsPoint(x, y)
  return x > self.x and x < self.x + self.width and
         y > self.y and y < self.y + self.height
end


function Rect:__tostring()
  return _.format("({x}, {y}, {width}, {height})", self)
end


return Rect
