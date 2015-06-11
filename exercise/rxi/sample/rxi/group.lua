local _ = require "lib.lume"
local Entity = require "rxi.entity"

local Group = Entity:extend()


function Group:new()
  Group.super.new(self)
  self.members = {}
  self.collidables = {}
  self.solid = false
  self.collidable = false
  self.collision = true
end


function Group:add(e, idx)
  assert(e, "expected entity")
  e.parent = self
  if idx then
    table.insert(self.members, idx, e)
  else
    table.insert(self.members, e)
  end
  if e.collidable then
    table.insert(self.collidables, e)
  end
end


function Group:remove(e)
  assert(e, "expected entity")
  if type(e) == "number" then
    _.remove(self.collidables, self.members[e])
    return table.remove(self.members, e)
  end
  local idx = _.find(self.members, e)
  if idx then
    return self:remove(idx) 
  end   
end


local compareX = function(a, b)
  return a.x < b.x
end


function Group:collide()
  local t = self.collidables
  table.sort(t, compareX)
  for i, a in ipairs(t) do
    for j = i + 1, #t do
      local b = t[j]
      if a.x + a.width < b.x then
        break
      end
      if a.y < b.y + b.height and a.y + a.height > b.y then
        a:onOverlap(b)
        b:onOverlap(a)
      end
    end
  end
end


function Group:update(dt)
  -- Update as entity (updates timers, tweens etc.)
  Group.super.update(self, dt)
  -- Update
  _.each(self.members, "update", dt)
  -- Purge dead members
  for i, e in _.ripairs(self.members) do
    if e.dead then
      self:remove(i)
    end
  end
  -- Collision
  if self.collision then
    self:collide()
  end
end


function Group:drawDebug()
  _.each(self.members, "drawDebug")
end


function Group:draw()
  _.each(self.members, "draw")
end


return Group
