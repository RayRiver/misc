local _ = require "lib.lume"
local Game = require "rxi.game"
local Thing = require "thing"


local Crate = Thing:extend()


local dieSound = juno.Source.fromData(
  juno.Data.fromFile("data/sound/crate_die.ogg"))

function Crate:new()
  Crate.super.new(self)
  self:loadImage("data/image/crate.png")
  self.destructable = true
  self.accel.y = 300
end


function Crate:kill()
  Crate.super.kill(self)
  dieSound:play(true)
end


return Crate
