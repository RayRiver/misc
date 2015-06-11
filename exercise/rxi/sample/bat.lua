local _ = require "lib.lume"
local Game = require "rxi.game"
local Tilemap = require "rxi.tilemap"
local Mob = require "mob"


local Bat = Mob:extend()

function Bat:new(facing)
  Bat.super.new(self)
  self:loadImage("data/image/bat.png", 14, 15)
  self:addAnimation("fly", { 1, 2, 3, 4, 5 }, 10)
  self:play("fly")
  if facing then
    self.flip = (facing == "left")
  end
  self.destructable = true
end


function Bat:onVisible()
  self.velocity.x = (self.flip and -1 or 1) * 30
  -- Is the player on the wrong side? Just die right away
  if _.sign(self.velocity.x) ~= _.sign(Game.state.player.x - self.x) then
    self.dead = true
  end
end


function Bat:onOverlap(e)
  if e.solid and e:is(Tilemap.Tile) then
    self.dead = true
  end
  Bat.super.onOverlap(self, e)
end


function Bat:onNotVisible()
  self.dead = true
end


return Bat
