local _ = require "lib.lume"
local Game = require "rxi.game"
local Thing = require "thing"


local Pulse = Thing:extend()


function Pulse:new(time, size)
  Pulse.super.new(self)
  self:loadImage("data/image/pulse.png")
  self.solid = false
  self.drawDest = Game.state.displaceMap
  time = time or 2
  size = size or 1.3
  self.scale:set(0, 0)
  self.tween:to(self.scale, time, { x = size, y = size })
    :ease("expoout")
  self.tween:to(self, time, { alpha = 0 })
    :ease("expoout")
    :oncomplete(function() self:kill() end)
  -- Defer *destroy stuff close to me* timer
  self.timer:delay(function()
    _(self.parent.members)
      :filter("destructable")
      :filter(function(e) return self:distanceTo(e) < 42 end)
      :each(function(e) e:kill() end)
  end, .05)
end

return Pulse
