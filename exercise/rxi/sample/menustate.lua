local _ = require "lib.lume"
local Game = require "rxi.game"
local Entity = require "rxi.entity"
local StateEx = require "stateex"
local PlayState = require "playstate"
--local IntroState = require "introstate"
local saved = require "saved"
local input = require "input"

local MenuState = StateEx:extend()


function MenuState:create()

  self.options = {

    {
      name = "New Game",
      fn =  function() 
        saved.clear()
        saved.notFirstRun = true
        --Game.switchState(IntroState())
        Game.switchState(PlayState())
      end
    },

    {
      name = "Exit",
      fn = function() os.exit() end
    },

  }

  if saved.notFirstRun then
    table.insert(self.options, 1, {
      name = "Continue game",
      fn = function() Game.switchState(PlayState()) end
    })
  end

  local padding = 20

  self.menuText = Entity()
  self.menuText:warp(padding, padding)
  self:add(self.menuText)
  self.idx = 1
  self:refresh()

  local author = Entity():setText("@x_rxi")
  author:right(G.width - padding)
  author:top(padding)
  self:add(author)
  
  saved.notFirstRun = true


  MenuState.super.create(self)
end


function MenuState:refresh()
  local i = 0
  local txt = _(self.options)
    :map(function(x)
      i = i + 1
      return ((i == self.idx) and "> " or "") .. x.name
    end)
    :reduce(function(a, b) return a .. "\n" .. b end)
    :result()
  self.menuText:setText(txt)
end


function MenuState:update(dt)
  MenuState.super.update(self, dt)

  if input.wasPressed("down") then
    self.idx = math.min(self.idx + 1, #self.options)
    self:refresh()
  elseif input.wasPressed("up") then
    self.idx = math.max(self.idx - 1, 1)
    self:refresh()
  elseif input.wasPressed("select") then
    self.options[self.idx].fn()
    self:refresh()
  end

end


return MenuState
