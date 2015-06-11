local _ = require "lib.lume"
local Game = require "rxi.game"
local Entity = require "rxi.entity"
local saved = require "saved"
local Thing = require "thing"
local Player = require "player"
local Dialog = require "dialog"


local Egg = Thing:extend()

local maxEgg = 13

function Egg:new(x, y, map)
  Egg.super.new(self)
  self:loadImage("data/image/egg.png")
  self.accel.y = 300
  self.solid = false
  self.tileSolid = true
  self.usable = true
  self:warp(x, y)
  -- Make uid -- if we've been collected kill ourselves *immediately* -- unless
  -- we're in debug mode
  self.uid = _.format("egg:{x}-{y}-{map}", { x = x, y = y, map = map })
  if saved[self.uid] then
    if not G.debug then
      self.dead = true
    end
  end
end


local collectSound = juno.Source.fromData(
  juno.Data.fromFile("data/sound/egg.ogg"))


function Egg:use()
  self.dead = true
  saved[self.uid] = true
  saved.eggcount = (saved.eggcount or 0) + 1
  -- do dialog
  local d = Dialog("You found an egg ("
                   .. saved.eggcount .. " of " .. maxEgg .. ")")
  d:at(self)
  d.y = d.y - 30
  Game.state:add(d)
  -- Do sound
  collectSound:play(true)
  -- Last egg -- end game!
  if saved.eggcount == maxEgg then
    saved:clear()
    -- White out screen
    local blank = Entity():makeImage(G.width, G.height, 1, 1, 1, 1)
    blank.scrollFactor:set(0, 0)
    blank.collidable = false
    Game.state:add(blank)
    -- Make dummy player
    local player = Game.state.player
    local dummy = Entity():loadImage("data/image/player.png",
                                     player.frameSize:getSize())
    dummy.frame = player.frame
    dummy.flip = player.flip
    dummy.offset = player.offset
    dummy:at(player)
    Game.state:add(dummy)
    player.dead = true
    -- Init timer to go back to menu
    Game.state.timer:delay(function()
      local MenuState = require "menustate"
      Game.switchState(MenuState())
    end, 5)
  end
end




return Egg
