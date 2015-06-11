local _ = require "lib.lume"
local Entity = require "rxi.entity"
local Game = require "rxi.game"
local Tilemap = require "rxi.tilemap"
local Thing = require "thing"
local Pulse = require "pulse"
local input = require "input"
local saved = require "saved"


local Player = Thing:extend()


function Player:new()
  Player.super.new(self)
  _.trace("player init")
  -- Init graphics
  self:loadImage("data/image/player.png", 12, 17)
  self:addAnimation("idle", { 1, 2, 3, 4 }, 8)
  self:addAnimation("walk", { 5, 6, 7, 8 }, 12)
  self:addAnimation("fall", { 8 }, 12)
  self.autoFlip = true
  -- Init blink & blink timer
  self.blink = Entity():loadImage("data/image/player_blink.png")
  self.blinking = true
  local function blinkLoop()
    self.blinking = true
    self.timer
      :delay(function() self.blinking = false end, .2)
      :after(blinkLoop, _.random(.5, 5))
  end
  blinkLoop()
  -- Init self
  self.height = self.height - 2
  self.offset.y = -2
  self.x, self.y = 30, 30
  self.accel.y = 250
  self.maxVelocity:set(100, 200)
  self.drag.x = 900
  self.canAttack = true
  -- Init sounds
  self.sounds = _.map({
    attack  = { name = "player_attack", gain = .85  },
    jump    = { name = "player_jump",   gain = 1    },
    land    = { name = "player_land",   gain = 1.1  },
    walk    = { name = "player_walk",   gain = .6   },
    die     = { name = "player_die",    gain = .7   },
  }, function(x)
    local source = 
      juno.Source.fromData(
        juno.Data.fromFile("data/sound/" .. x.name .. ".ogg"))
    source:setGain(x.gain)
    return source
  end)
  -- Init use icon
  self.useIcon = Entity():loadImage("data/image/useicon.png")
  self.useIcon.collidable = false
  Game.state:add(self.useIcon)
  -- Set this as our last self
  Player.lastInstance = self
  -- Load persistant stuff
  self.flip = saved.playerFlip
end


function Player:kill()
  if self.dying then return end
  local PlayState = require "playstate"
  -- Add blank screen and dummy player
  local blank = Entity():makeImage(G.width, G.height, 0, 0, 0, 1)
  blank.scrollFactor:set(0, 0)
  blank.collidable = false
  --blank.alpha = 0
  --blank.tween:to(blank, .1, { alpha = 1 })
  Game.state:add(blank)
  local dummy = Entity():loadImage("data/image/player.png",
                                   self.frameSize:getSize())
  dummy.frame = self.frame
  dummy.flip = self.flip
  dummy.offset = self.offset
  dummy:at(self)
  Game.state:add(dummy)
  -- SHAKE IT
  Game.shake(4, .2)
  -- Do sound
  self.sounds.die:play(true)
  -- Stop camera
  Game.state.camera:follow()
  -- Do fadeout on dummy
  Game.state.timer:delay(function() Game.switchState(PlayState()) end, 1.2)
  -- Kill self
  self.super.kill(self)
end


function Player:jump()
  -- Abort if not touching the ground
  if not self.touching.bottom then return end
  self.velocity.y = -160
  -- Throw some dust up
  local e = Entity():loadImage("data/image/player_jump.png", 27)
  local time = .4
  e.collidable = false
  e:addAnimation("main", { 1, 2, 3, 4, 5, 6, 7 }, 7 / time)
  e:play("main")
  e:middleX(self:middleX())
  e:bottom(self:bottom())
  e.velocity.x = self.velocity.x / 2
  e.drag.x = 200
  e.timer:delay(function() e:kill() end, time)
  self.parent:add(e)
  -- Do sound
  self.sounds.jump:play(true)
end


function Player:land()
  --Throw some dust up
  local e = Entity():loadImage("data/image/player_land.png", 27)
  local time = .3
  e.collidable = false
  e:addAnimation("main", { 1, 2, 3, 4, 5 }, 5 / time)
  e:play("main")
  e:middleX(self:middleX())
  e:bottom(self:bottom())
  e.timer:delay(function() e:kill() end, time)
  self.parent:add(e)
  -- Do sound
  self.sounds.land:play(true)
end


function Player:attack()
  if not self.canAttack then return end
  local e = Pulse()
  e:at(self)
  self.parent:add(e)
  -- Do sound
  self.sounds.attack:play(true)
  -- Init attack state/timer
  self.canAttack = false
  self.timer:delay(function() self.canAttack = true end, 1)
end


function Player:onOverlap(e)
  if e:is(Tilemap.Tile) and e.death then
    self:kill()
  end
  if e.usable then
    self.showUseIcon = true
    if self.performingAction then
      e:use()
    end
  end
  Player.super.onOverlap(self, e)
end


function Player:update(dt)
  self.performingAction = false
  -- Handle debug free-move
  if G.debug and juno.keyboard.isDown("1") then
    local step = 300
    if input.isDown("left")   then self.x = self.x - step * dt end
    if input.isDown("right")  then self.x = self.x + step * dt end
    if input.isDown("up")     then self.y = self.y - step * dt end
    if input.isDown("down")   then self.y = self.y + step * dt end
    return
  end
  -- Do input
  local s = 600
  if input.isDown("left") then
    self.accel.x = -s
  elseif input.isDown("right") then
    self.accel.x = s
  else
    self.accel.x = 0
  end
  -- Jump / dejump
  if input.isDown("jump") then
    self:jump()
  end
  if not input.isDown("jump") then
    self.velocity.y = math.max(self.velocity.y, -90)
  end
  -- Action
  if input.wasPressed("action") then
    self.performingAction = true
  end
  -- attack
  if input.wasPressed("attack") then
    self:attack()
  end
  -- Landing
  if self.touching.bottom and not self.wasGrounded then
    self:land()
  end
  -- Animation
  if self.touching.bottom then
    self:play(self.velocity.x == 0 and "idle" or "walk")
  else
    self:play("fall")
  end
  -- walking sound
  if self.accel.x ~= 0 and self.touching.bottom then
    self.sounds.walk:setLoop(true)
    self.sounds.walk:play()
  else
    self.sounds.walk:stop()
  end
  -- Update
  self.wasGrounded = self.touching.bottom
  Player.super.update(self, dt)
  -- Debug stuff
  if G.debug then
    if juno.keyboard.wasPressed("q") then
      self:kill()
    end
  end
  -- Handle `use` icon
  if self.showUseIcon then
    self.useIcon.alpha = 1
  else
    self.useIcon.alpha = 0
  end
  self.useIcon:middleX(self:middleX())
  self.useIcon:bottom(self:top() - 6)
  self.showUseIcon = false
end


function Player:draw()
  -- Draw self
  Player.super.draw(self)
  -- Draw blink mask
  if self.blinking then
    self.blink.flip = self.flip
    self.blink:at(self)
    self.blink:draw()
  end
end


return Player
