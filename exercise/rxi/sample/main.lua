local _ = require "lib.lume"
local flux = require "lib.flux"
local tick = require "lib.tick"
local Game = require "rxi.game"
local PlayState = require "playstate"
local MenuState = require "menustate"

local function toggleDebug()
  juno.debug.setVisible(not juno.debug.getVisible())
  Game.debugDraw = not Game.debugDraw
end

function juno.onLoad()
  if G.debug then
    --Game.init(MenuState, 2)
    Game.init(PlayState, 2)
  else
    print = function() end
    Game.init(MenuState, 2)
  end
  juno.audio.master:setGain(.8)
  if G.debug then
    --toggleDebug()
    juno.audio.master:setGain(0)
  end
end


function juno.onUpdate(dt)
  flux.update(dt)
  tick.update(dt)
  Game.update(dt)
end


function juno.onKeyDown(k)
  if G.debug then
    if k == "tab" then
      toggleDebug()
    end
    --if k == "r" then
    --  _.clear(package.loaded)
    --  require("main")
    --  juno.onLoad()
    --end
    if k == "m" then
      juno.audio.master:setGain(.8)
    end
    if k == "`" then
      juno.debug.setFocused(not juno.debug.getFocused())
    end
    if k == "escape" then
      os.exit()
    end
  end
end


function juno.onDraw()
  Game.draw()
  if G.debug then
    juno.graphics.drawText("debug mode", juno.graphics.getWidth() - 100, 10)
  end
end
