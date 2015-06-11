
local _ = require "lib.lume"
local Game = require "rxi.game"
local Region = require "rxi.region"
local Thing = require "thing"
local Player = require "player"


local Door = Region:extend()


function Door:new(x, y, width, height, dest)
  Door.super.new(self, dest)
  self.x, self.y = x, y
  self.width, self.height = width, height
  self.dest = dest
  assert(self.width)
  assert(self.height)
  assert(self.dest)
  self.elapsed = 0
  self:load({

    enter = function(self, e)
      -- Waiting for small elapsed time prevents player from triggering a door
      -- they just sparned at from another map, meaning they'd have to first
      -- *leave* the door and then re-enter it to trigger it
      if e:is(Player) and self.auto and self.elapsed > .2 then
        self:use()
      end
    end,

    update = function(self, dt)
      self.elapsed = self.elapsed + dt
    end,

  })
end


function Door:use()
  local PlayState = require "playstate"
  local s = PlayState()
  s.mapName = self.dest
  s.destDoor = Game.state.mapName
  juno.keyboard.reset()
  Game.switchState(s)
end


function Door:update(dt)
  Door.super.update(self, dt)
  self.usable = (not self.auto and not self.hidden)
end


return Door
