local _ = require "lib.lume"
local Thing = require "thing"
local Player = require "player"


local LeafSpawner = Thing:extend()
local Leaf = Thing:extend()


function LeafSpawner:new(x, y, width, height)
  LeafSpawner.super.new(self)
  self.x, self.y = x, y
  self.width, self.height = width, height
  self.collidable = false
  -- Init leaf spawn timer
  local function spawnLoop()
    local leaf = Leaf(self.x + _.random(self.width),
                      self.y + _.random(self.height))
    self.parent:add(leaf)
    self.timer:delay(spawnLoop, _.random(.2, 3))
  end
  self.timer:delay(spawnLoop, .5)
end

function Leaf:new(x, y)
  Leaf.super.new(self)
  self:loadImage(_.weightedchoice({
    ["data/image/leaf.png"] = 90,
    ["data/image/petal.png"] = 10,
  }))
  self:middleX(x)
  self:middleY(y)
  self.angularVelocity = _.random(-1, 1) * 180
  self.angle = _.random(360)
  self.velocity.x = _.random(-1) * 10
  self.velocity.y = _.random(20)
  self.accel.y = _.random(20, 60)
  self.maxVelocity:set(20, 20)
  self.solid = false
end


function Leaf:onOverlap(e)
  if e.solid and not e:is(Player) then
    self:kill()
  end
end



return LeafSpawner
