local _ = require "lib.lume"
local Game = require "rxi.game"
local Entity = require "rxi.entity"

local Scale9 = Entity:extend()


function Scale9:new(filename)
  Scale9.super.new(self)
  self.solid = false
  self.collidable = false
  self.width = 64
  self.height = 64
  self.tileWidth = 0
  self.tileHeight = 0
  if filename then
    self:loadImage(filename)
  end
end


function Scale9:loadImage(filename)
  local tmp = juno.Buffer.fromFile(filename)
  local w, h = tmp:getSize()
  assert(w % 3 == 0 and h % 3 == 0, "expected width and height divisible by 3")
  Scale9.super.loadImage(self, filename, w / 3, h / 3)
  self.scrollFactor:set(0, 0)
  self.origin:set(0, 0)
  self.tileWidth = w / 3
  self.tileHeight = h / 3
  print(self.width, self.height)
  return self
end


local drawTile = function(self, frame, x, y, sx, sy)
  self.frame = frame
  self.x, self.y = x, y
  self.scale:set(sx, sy)
  Entity.draw(self)
end

function Scale9:draw()
  if not self.image then return end
  local ox, oy = self.x, self.y
  local tw, th = self.tileWidth, self.tileHeight
  local w, h = self.width, self.height
  self.scale:set(1, 1)
  -- Top-left corner
  drawTile(self, 1, ox, oy, 1, 1)
  -- Top-right corner
  drawTile(self, 3, ox + w - tw, oy, 1, 1)
  -- Bottom-left corner
  drawTile(self, 7, ox, oy + h - th, 1, 1)
  -- Bottom-right corner
  drawTile(self, 9, ox + w - tw, oy + h - th, 1, 1)
  -- Top
  drawTile(self, 2, ox + tw, oy, (w - tw * 2) / tw, 1)
  -- Bottom
  drawTile(self, 8, ox + tw, oy + h - th, (w - tw * 2) / tw, 1)
  -- Left
  drawTile(self, 4, ox, oy + th, 1, (h - th * 2) / th)
  -- Right
  drawTile(self, 6, ox + w - tw, oy + th, 1, (h - th * 2) / th)
  -- Middle
  drawTile(self, 5, ox + tw, oy + th, (w - tw * 2) / tw, (h - th * 2) / th)
  -- Reset position
  self.x, self.y = ox, oy
end

return Scale9
