local Game = require "rxi.game"
local State = require "rxi.state"
local Entity = require "rxi.entity"


local StateEx = State:extend()

function StateEx:create()
  StateEx.super.create(self)
  -- Init fx
  self.displaceMap = juno.Buffer.fromBlank(G.width, G.height)
  -- Reset keyboard :3
  juno.keyboard.reset()
end


local fb = juno.Buffer.fromBlank(G.width, G.height)

function StateEx:draw()
  self.displaceMap:clear(.5, .5, .5, 1)
  -- Draw
  StateEx.super.draw(self)
  -- Do effects
  juno.bufferfx.displace(fb, Game.framebuffer, self.displaceMap,
                         "r", "g", 10, 10)
  Game.framebuffer, fb = fb, Game.framebuffer
end




return StateEx

