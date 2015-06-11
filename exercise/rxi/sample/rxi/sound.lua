local _ = require "lib.lume"
local Game = require "rxi.game"
local Entity = require "rxi.entity"

-- A placeable sound source in the world -- Sounds specifically react to the
-- camera position relative to themselves, adjusting their gain and panning
-- accordingly

local Sound = Entity:extend()


function Sound:new(data, loop)
  Sound.super.new(self)
  -- Init entity parameters
  self.width, self.height = 4, 4
  self.solid = false
  self.collidable = false
  -- Init
  self.gain = 1
  self.pan = .5
  self.size = Game.camera.width * 1.1
  self:loadSound(data, loop)
end


function Sound:loadSound(data, loop)
  if type(data) == "string" then
    return self:loadSound(juno.Data.fromFile(data), loop)
  end
  self.source = juno.Source.fromData(data)
  self.source:setLoop(loop)
  self.source:setGain(0)
  self.source:play()
end


function Sound:update(dt)
  -- Alter sound source based on position relative to camera
  if self.source then
    local e = Game.camera
    -- Do gain
    local d = self:distanceTo(e)
    local a = _.clamp(1 - (d / self.size), 0, 1) * self.gain
    self.source:setGain(a)
    -- Do pan
    local x = (self:middleX() - e:middleX()) / self.size
    local p = _.clamp(x, -1, 1) * self.pan
    self.source:setPan(p)
  end
  -- Update
  Sound.super.update(self, dt)
end


return Sound

