local _ = require "lib.lume"
local Game = require "rxi.game"
local Entity = require "rxi.entity"

local Backdrop = Entity:extend()


function Backdrop:new(filename, sfx, sfy)
  Backdrop.super.new(self)
  self.solid = false
  self.collidable = false
  sfx = sfx or 1
  sfy = sfy or sfx
  self.scrollFactor:set(sfx, sfy)
  if filename then
    self:loadImage(filename)
  end
end


function Backdrop:update(dt)
  Backdrop.super.update(self, dt)
  self.tile:update(dt)
end


function Backdrop:loadImage(...)
  self.tile = Entity():loadImage(...)
  self.tile.scrollFactor:set(0, 0)
  return self
end


function Backdrop:draw()
  if not self.tile then
    return
  end
  local t = self.tile
  local x, y = self:getScreenX(), self:getScreenY()
  local w, h = t.width, t.height
  x = (x % w + w) % w - w
  y = (y % h + h) % h - h
  for j = y, Game.height, h do
    for i = x, Game.width, w do
      t.x, t.y = i, j
      t:draw()
    end
  end
end

return Backdrop
