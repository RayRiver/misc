local _ = require "lib.lume"
local Game = require "rxi.game"
local Thing = require "thing"
local Player = require "player"


local Mob = Thing:extend()

function Mob:new()
  Mob.super.new(self)
  self.visible = false
end

local dieSound = juno.Source.fromData(
  juno.Data.fromFile("data/sound/mob_die.ogg"))
dieSound:setGain(.8)

function Mob:kill()
  Mob.super.kill(self)
  dieSound:play(true)
end


function Mob:update(dt)
  Mob.super.update(self, dt)
  if not self.visible and self:overlaps(Game.camera) then
    self.visible = true
    _.call(self.onVisible, self)
  end
  if self.visible and not self:overlaps(Game.camera) then
    self.visible = false
    _.call(self.onNotVisible, self)
  end
end


function Mob:onOverlap(e)
  if e:is(Player) then
    e:kill()
  end
  Mob.super.onOverlap(self, e)
end


return Mob
