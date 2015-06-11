local _ = require "lib.lume"
local Object = require "lib.classic"

local Game = Object:extend()


function Game:new()
  error("the Game object constructor should not be used; use Game.init()")
end


function Game.init(stateConstructor, scale)
  local Entity = require "rxi.entity"
  Game.scale = scale or 3
  Game.width  = math.ceil(juno.graphics.getWidth()  / Game.scale)
  Game.height = math.ceil(juno.graphics.getHeight() / Game.scale)
  Game.camera = Entity()
  Game.camera.width, Game.camera.height = Game.width, Game.height
  Game.framebuffer = juno.Buffer.fromBlank(Game.width, Game.height)
  Game.postbuffer = juno.Buffer.fromBlank(Game.width, Game.height)
  Game.shakeAmount = 0
  Game.shakeTimer = 0
  Game.elapsed = 0
  Game.frame = 0
  Game.bgcolor = { 0, 0, 0 }
  Game.debugDraw = false
  Game.minfps = 30
  Game.state = nil
  Game.pendingState = stateConstructor()
  return Game
end


function Game.switchState(state)
  Game.pendingState = state
end


function Game.shake(amount, time)
  Game.shakeAmount = amount or 2
  Game.shakeTimer = math.abs(time or .5)
end


function Game.update(dt)
  -- Pending state? Switch out old state then switch to new state and create..
  if Game.pendingState then
    if Game.state then
      Game.state:destroy()
    end
    Game.camera.x, Game.camera.y = 0, 0
    Game.state = Game.pendingState
    Game.pendingState = nil
    Game.state:create()
    -- Run GC to clear up old state; called twice to assure objects which are
    -- collected in two phases are collected.
    collectgarbage()
    collectgarbage()
  end
  -- Apply minimum fps
  dt = math.min(1 / Game.minfps, dt)
  -- Update counters
  Game.elapsed = Game.elapsed + dt
  Game.frame = Game.frame + 1
  -- Update screen-shake timer
  if Game.shakeTimer ~= 0 then
    Game.shakeTimer = Game.shakeTimer - dt
    if Game.shakeTimer <= 0 then
      Game.shakeTimer = 0
      Game.shakeAmount = 0
    end
  end
  -- Update
  Game.state:update(dt)
end


function Game.draw()
  -- Reset entities buffer state -- This assures the first entity drawn will
  -- correctly set up the state of the buffer for its draw mode
  Game.state.resetBufferState()
  -- Clear to background color
  Game.framebuffer:clear(Game.bgcolor[1], Game.bgcolor[2], Game.bgcolor[3], 1)
  -- Draw
  Game.state:draw()
  -- Debug draw?
  if Game.debugDraw then
    Game.framebuffer:reset()
    Game.framebuffer:setAlpha(.7)
    Game.state:drawDebug()
  end
  -- Apply effects and copy game's pixels
  local fb = Game.framebuffer
  -- Screen is shaking? Copy to shake buffer with an offset
  if Game.shakeAmount >= 1 then
    Game.postbuffer:clear(0, 0, 0)
    Game.postbuffer:copyPixels(
      Game.framebuffer,
      _.random() * Game.shakeAmount,
      _.random() * Game.shakeAmount)
    fb = Game.postbuffer
  end
  -- Copy buffer to screen, scaled
  juno.graphics.copyPixels(fb, 0, 0, nil, Game.scale)
end


return Game
