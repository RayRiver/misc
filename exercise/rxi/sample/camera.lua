local _ = require "lib.lume"
local Entity = require "rxi.entity"
local Game = require "rxi.game"
local Thing = require "thing"

local Camera = Thing:extend()

function Camera:new()
  Camera.super.new(self)
  self.collidable = false
  self.width, self.height = Game.camera.width, Game.camera.height
  self.speed = 2
  _.trace(self.width, self.height)
end 


function Camera:update(dt)
  Camera.super.update(self, dt)
  -- Move towards following
  if self.following then
    local dstx = self.following:middleX() - self.width / 2
    local dsty = self.following:middleY() - self.height / 2
    self.x = _.lerp(self.x, dstx, self.speed * dt)
    self.y = _.lerp(self.y, dsty, self.speed * dt)
  end
  -- Bind to bound entity
  if self.bound then
    self:clamp(self.bound)
  end
  -- Set core camera
  Game.camera:at(self)
end


function Camera:bind(e)
  self.bound = e
end


function Camera:follow(e)
  self.following = e
  return e
end 


return Camera

