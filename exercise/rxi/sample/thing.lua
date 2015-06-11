local _ = require "lib.lume"
local Game = require "rxi.game"
local Entity = require "rxi.entity"
local Tilemap = require "rxi.tilemap"


local Thing = Entity:extend()

function Thing:new()
  Thing.super.new(self)
end


function Thing:kill()
  if self.destructable then
    -- Break into particles
    for i = 1, 14 do
      local n = 2
      local e = Thing():makeImage(self.width / n, self.height / n)
      e.image:copyPixels(self.image,
                         -(math.random(n) - 1) * self.frameSize.width / n,
                         -(math.random(n) - 1) * self.frameSize.height / n)
      e.solid = false
      e.tileSolid = true
      e:at(self)
      local r = _.random(math.pi * 2)
      e.bounce = .8
      e.velocity.x = _.random(-1, 1) * 200
      e.velocity.y = _.random(-1, .5) * 200
      e.angle = _.random(360)
      e.angularVelocity = _.random(-1, 1) * 200
      e.drag:set(100, 100)
      e.accel.y = 300
      e.timer
        :delay(function() e:flicker(10) end, _.random(1, 2))
        :after(function() e:kill() end, .2)
      self.parent:add(e)
    end
    -- Nuh nuh nuh nuh SCREEN SHAKE
    Game.shake(4, .1)
  end

  Thing.super.kill(self)
end


function Thing:onOverlap(e)
  if not self.solid and self.tileSolid and e:is(Tilemap.Tile) then
    self.solid = true
    e:onOverlap(self)
    self:onOverlap(e)
    self.solid = false
    return  
  end 
  Thing.super.onOverlap(self, e)
end


return Thing
