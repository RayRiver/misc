local _ = require "lib.lume"
local flux = require "lib.flux"
local tick = require "lib.tick"
local Object = require "lib.classic"
local Game = require "rxi.game"
local Rect = require "rxi.rect"

local Entity = Rect:extend()

function Entity:new()
  Entity.super.new(self)
  self.last = Rect(0, 0)
  self.velocity = Rect(0, 0)
  self.accel = Rect(0, 0)
  self.drag = Rect(0, 0)
  self.maxVelocity = Rect(math.huge, math.huge)
  self.origin = Rect(0, 0)
  self.offset = Rect(0, 0)
  self.scale = Rect(1, 1)
  self.scrollFactor = Rect(1, 1)
  self.frameSize = Rect(0, 0)
  self.frames = {}
  self.animations = {}
  self.animation = nil
  self.animationTimer = 0
  self.animationFrame = 1
  self.frame = 1
  self.angle = 0
  self.bounce = 0
  self.angularVelocity = 0
  self.autoFlip = false
  self.dead = false
  self.flip = false
  self.immovable = false
  self.moves = true
  self.solid = true
  self.collidable = true
  self.color = nil
  self.flashColor = { 1, 1, 1 }
  self.flashTimer = 0
  self.flickerTimer = 0
  self.blend = nil
  self.alpha = 1
  self.drawDest = nil
  self.touching = {}
  self.health = 0
  self.tween = flux.group()
  self.timer = tick.group()
end


local allSides = { top = true, bottom = true, left = true, right = true }

function Entity:separate(e, axis)
  -- Separating against ourself?
  if self == e then return end
  -- Do the entities overlap?
  if not self:overlaps(e) then return end
  -- Work out overlapping axis or use the axis if we were passed one
  local separateX = false
  if axis then
    separateX = (axis == "x")
  else
    if self.last:overlapsY(e.last) then
      if self.last:overlapsX(e.last) then
        -- Overlapped on both axes last frame? Assume the least-overlapping
        -- axis is the one we want to separate on
        local distX = self:middleX() < e:middleX() and
                      e:left() - self:left() or
                      self:right() - e:right()
        local distY = self:middleY() < e:middleY() and
                      e:top() - self:top() or
                      self:bottom() - e:bottom()
        separateX = distX > distY
      else
        separateX = true
      end
    end
  end
  -- Check the sides that we're colliding on are collidable.
  local selfSides = self.collidable == true and allSides or self.collidable
  local eSides    = e.collidable    == true and allSides or e.collidable
  if separateX then
    if self.last.x < e.last.x then
      if not selfSides.right or not eSides.left then return end
    else
      if not selfSides.left or not eSides.right then return end
    end
  else
    if self.last.y < e.last.y then
      if not selfSides.bottom or not eSides.top then return end
    else
      if not selfSides.top or not eSides.bottom then return end
    end
  end
  -- Handle immovable entity
  if self.immovable or e.immovable then
    -- Both immovable? Nothing we can do...
    if self.immovable and e.immovable then
      return
    end
    -- The bits below assumes `e` is the immovable object, thus if `self` is
    -- the immovable object we call the function with the arguments switched 
    if self.immovable then
      return e:separate(self)
    end
    -- Separate
    if separateX then
      local z = self.last.x < e.last.x
      if z then
        self:right(e:left())
        self.touching.right = true
        e.touching.left = true
      else
        self:left(e:right())
        self.touching.left = true
        e.touching.right = true
      end
      if z == (self.velocity.x > 0) then
        self.velocity.x = -self.velocity.x * self.bounce
      end
    else
      local z = self.last.y < e.last.y
      if z then
        self:bottom(e:top())
        self.touching.bottom = true
        e.touching.top = true
      else
        self:top(e:bottom())
        self.touching.top = true
        e.touching.bottom = true
      end
      if z == (self.velocity.y > 0) then
        self.velocity.y = -self.velocity.y * self.bounce
      end
    end
    return
  end
  -- Handle both entities being movable
  if separateX then
    -- Overlaps on X axis
    local z = self.last.x < e.last.x
    local mid = self:middleX() < e:middleX() and
                (self:right() + e:left()) / 2 or
                (self:left() + e:right()) / 2
    if z then
      self:right(mid)
      e:left(mid)
      self.touching.right = true
      e.touching.left = true
    else
      self:left(mid)
      e:right(mid)
      self.touching.left = true
      e.touching.right = true
    end
    if z == (self.velocity.x > 0) then
      self.velocity.x = -self.velocity.x * self.bounce
    end
    if z == (e.velocity.x < 0) then
      e.velocity.x = -e.velocity.x * e.bounce
    end
  else
    -- Overlaps on Y axis
    local z = self.last.y < e.last.y
    local mid = self:middleY() < e:middleY() and
                (self:bottom() + e:top()) / 2 or
                (self:top() + e:bottom()) / 2
    if z then
      self:bottom(mid)
      e:top(mid)
      self.touching.bottom = true
      e.touching.top = true
    else
      self:top(mid)
      e:bottom(mid)
      e.touching.bottom = true
      self.touching.top = true
    end
    if z == (self.velocity.y > 0) then
      self.velocity.y = -self.velocity.y * self.bounce
    end
    if z == (e.velocity.y < 0) then
      e.velocity.y = -e.velocity.y * e.bounce
    end
  end
end


function Entity:onOverlap(e)
  if self.solid and e.solid then
    self:separate(e)
  end
end


function Entity:hurt(points)
  points = points or 1
  self.health = self.health - points
  if self.health <= 0 then
    self:kill()
  end
end


function Entity:kill()
  self.dead = true
end


function Entity:flicker(n)
  self.flickerTimer = n
end


function Entity:flash(n, r, g, b)
  self.flashTimer = n
  self.flashColor[1], self.flashColor[2], self.flashColor[3] = r, g, b
end


function Entity:randomFrame()
  self.frame = math.random(#self.frames)
end


function Entity:warp(x, y)
  assert(type(x) == "number" and type(y) == "number", "expected two numbers")
  self.x, self.y = x, y
  Rect.clone(self, self.last)
end


function Entity:followPath(points, speed, loop)
  points = _.map(points, tonumber)
  -- Error check points
  assert(#points % 2 == 0, "expected number of points divisible by 2") 
  assert(#points > 0, "expected number of points greater than zero") 
  -- Warp to first point
  self:warp(points[1], points[2])
  -- Only two points given? We're finished!
  if #points == 2 then
    return
  end
  -- Make path object
  self.path = {
    points  = points,
    speed   = math.abs(speed),
    loop    = (loop == nil) and true or loop,
    idx     = -1, -- `-1` so the next idx will be 1, idx is incremented by 2
    timer   = 0,
    tween   = nil
  }
end


function Entity:clearPath()
  if self.path and self.path.tween then
    self.path.tween:stop()
  end
  self.path = nil
end


function Entity:to(...)
  if type(select(1, ...)) == "table" then
    return self.tween:to(...)
  else
    return self.tween:to(self, ...)
  end
end


function Entity:centerOffset()
  self.offset.x = math.floor((self.width - self.frameSize.width) / 2)
  self.offset.y = math.floor((self.height - self.frameSize.height) / 2)
end


function Entity:centerOrigin()
  self.origin.x = _.round(self.frameSize.width / 2)
  self.origin.y = _.round(self.frameSize.height / 2)
end


function Entity:distanceTo(e)
  return _.distance(self:middleX(), self:middleY(),
                    e:middleX(), e:middleY())
end


function Entity:angleTo(e)
  return _.angle(self:middleX(), self:middleY(),
                 e:middleX(), e:middleY())
end


function Entity:getScreenX()
  return math.floor(self.x - _.round(Game.camera.x * self.scrollFactor.x))
end


function Entity:getScreenY()
  return math.floor(self.y - _.round(Game.camera.y * self.scrollFactor.y))
end


function Entity:getScreenPosition()
  return self:getScreenX(), self:getScreenY()
end


function Entity:getDrawDest()
  return self.drawDest or Game.framebuffer
end


function Entity:play(name, reset)
  local last = self.animation
  self.animation = self.animations[name]
  if reset or self.animation ~= last then
    self.animationTimer = self.animation.period
    self.animationFrame = 1
    self.frame = _.first(self.animation.frames)
  end
end


function Entity:stop()
  self.animation = nil
end


function Entity:addAnimation(name, frames, fps, loop)
  self.animations[name] = {
    frames = _.clone(frames),
    period = (fps ~= 0) and (1 / math.abs(fps)) or 1,
    loop   = (loop == nil) and true or loop,
  }
end


local loadImage = _.memoize(function(...)
  return juno.Buffer.fromFile(...)
end)

function Entity:loadImage(filename, width, height)
  self.image = loadImage(filename)
  width = width or self.image:getWidth()
  height = height or self.image:getHeight()
  self.frames = {}
  self.frameSize:set(0, 0, width, height)
  for y = 0, self.image:getHeight() / height - 1 do
    for x = 0, self.image:getWidth() / width - 1 do
      local r = { x = x * width, y = y * height, w = width, h = height }
      table.insert(self.frames, r)
    end
  end
  self.width = self.width ~= 0 and self.width or width
  self.height = self.height ~= 0 and self.height or height
  self:centerOrigin()
  return self
end


function Entity:makeImage(width, height, r, g, b, a)
  self.image = juno.Buffer.fromBlank(width, height)
  if r then
    self.image:clear(r, g, b, a)
  else
    self.image:clear(0, 0, 0, 0)
  end
  self.width, self.height = width, height
  self.frameSize:set(0, 0, width, height)
  self.frames = {{ x = 0, y = 0, w = width, h = height }}
  self:centerOrigin()
  return self
end


local loadFont = _.memoize(function(...)
  return juno.Font.fromFile(...)
end)

function Entity:loadFont(filename, size)
  filename = filename or "data/font/default.ttf"
  size = size or 8
  self.font = loadFont(filename, size)
  local textOld = self.text
  self.text = ""
  self:setText(textOld)
  return self
end


function Entity:setText(str)
  str = str and tostring(str) or nil
  if str == self.text then return end
  if not self.font then self:loadFont() end
  self.text = str
  if not self.text or self.text == "" then
    self.image = nil
    return self
  end
  local lines = _.split(self.text, "\n")
  local height = self.font:getHeight(self.text)
  local width = 0
  for i, line in ipairs(lines) do
    width = math.max(width, self.font:getWidth(line))
  end
  self:makeImage(width, height * #lines)
  for i, line in ipairs(lines) do
    self.image:draw(self.font:render(line), 0, height * (i - 1))
  end
  return self
end


local loadSound = _.memoize(function(...)
  local data = juno.Data.fromFile(...)
  return juno.Source.fromData(data)
end)

function Entity:playSound(filename, gain, pan, always)
  -- Not on screen?
  if not Game.camera:overlaps(self) and not always then
    return
  end
  -- Load and do sound
  local sound = loadSound(filename)
  sound:setGain(gain or 1)
  sound:setPan(pan or 0)
  sound:play()
  return sound
end


function Entity:updateMovement(dt)
  -- No time passed? Return as nothing below would do anything
  if dt == 0 then return end
  -- Store current position as last position
  Rect.clone(self, self.last)
  -- Update velocity
  self.velocity.x = self.velocity.x + self.accel.x * dt
  self.velocity.y = self.velocity.y + self.accel.y * dt
  -- Update max velocity
  if math.abs(self.velocity.x) > self.maxVelocity.x then
    self.velocity.x = self.maxVelocity.x * _.sign(self.velocity.x)
  end
  if math.abs(self.velocity.y) > self.maxVelocity.y then
    self.velocity.y = self.maxVelocity.y * _.sign(self.velocity.y)
  end
  -- Update position
  self.x = self.x + self.velocity.x * dt
  self.y = self.y + self.velocity.y * dt
  -- Update drag
  if self.accel.x == 0 and self.drag.x > 0 then
    local sign = _.sign(self.velocity.x)
    self.velocity.x = self.velocity.x - self.drag.x * dt * sign
    if (self.velocity.x < 0) ~= (sign < 0) then
      self.velocity.x = 0
    end
  end
  if self.accel.y == 0 and self.drag.y > 0 then
    local sign = _.sign(self.velocity.y)
    self.velocity.y = self.velocity.y - self.drag.y * dt * sign
    if (self.velocity.y < 0) ~= (sign < 0) then
      self.velocity.y = 0
    end
  end
  -- Update angle
  self.angle = self.angle + self.angularVelocity * dt
end


function Entity:updateAutoFlip()
  if self.accel.x ~= 0 then
    self.flip = (self.accel.x < 0)
  end
end


function Entity:updateAnimation(dt)
  local a = self.animation
  if not a then return end
  self.animationTimer = self.animationTimer - dt
  if self.animationTimer <= 0 then
    self.animationFrame = self.animationFrame + 1
    if self.animationFrame > #a.frames then
      if a.loop then
        self.animationFrame = 1
      else
        return self:stop()
      end
    end
    self.animationTimer = self.animationTimer + a.period
    self.frame = a.frames[self.animationFrame]
  end
end


function Entity:updatePathFollow(dt)
  local p = self.path
  if not p then return end
  if p.timer <= 0 then
    p.idx = p.idx + 2
    -- Reached last point? Loop or cancel
    if p.idx >= #p.points - 2 then
      if p.loop then
        p.idx = 1
      else
        self.path = nil
        return
      end
    end
    -- Get time
    local a = p.points
    local d = _.distance(a[p.idx], a[p.idx + 1], a[p.idx + 2], a[p.idx + 3])
    local t = d / p.speed
    -- Tween to next point
    p.tween = self.tween:to(self, t, { x = a[p.idx + 2], y = a[p.idx + 3] })
      :ease("linear")
    -- Set up timer
    p.timer = t
  else
    p.timer = p.timer - dt
  end
end


function Entity:updateTouching(dt)
  -- If no time has passed we leave our `touching` state unchanged. This
  -- assures, for example, that we maintain our touching-the-floor state even
  -- if gravity was not applied this frame which would cause us not to collide
  -- with the floor
  if dt == 0 then return end
  -- Clear `touching` state
  _.clear(self.touching)
end


function Entity:updateTimers(dt)
  self.flashTimer = self.flashTimer - dt
  self.flickerTimer = self.flickerTimer - dt
end


function Entity:update(dt)
  if self.moves then
    self:updateMovement(dt)
  end
  if self.path then
    self:updatePathFollow(dt)
  end
  if self.autoFlip then
    self:updateAutoFlip(dt)
  end
  if self.animation then
    self:updateAnimation(dt)
  end
  self:updateTouching(dt)
  self:updateTimers(dt)
  self.tween:update(dt)
  self.timer:update(dt)
end


local dbgColorBase      = { 1, 1, 0 }
local dbgColorMoves     = { 0, 1, 1 }
local dbgColorSolid     = { 0, 1, 0 }
local dbgColorImmovable = { 1, 0, 1 }

function Entity:drawDebug()
  local color = self.immovable and dbgColorImmovable or
                self.solid     and dbgColorSolid     or
                self.moves     and dbgColorMoves     or
                                   dbgColorBase
  local x, y = self:getScreenX(), self:getScreenY()
  Game.framebuffer:drawBox(x, y, self.width, self.height, unpack(color))
end


local lastDrawDest = ""
local lastColor    = ""
local lastBlend    = ""
local lastAlpha    = ""

function Entity.resetBufferState()
  lastDrawDest = ""
  lastColor    = ""
  lastBlend    = ""
  lastAlpha    = ""
end

function Entity:draw()
  -- No image? Nothing to draw..
  if not self.image then return end
  -- Flickering and on an even frame? Don't draw
  if self.flickerTimer > 0 and Game.frame % 2 == 0 then
    return 
  end  
  -- Get buffer according to our draw dest -- use the game's buffer if this is
  -- nil
  local buffer = self.drawDest or Game.framebuffer
  -- Different buffer to the last buffer? Reset draw state
  if buffer ~= lastDrawDest then
    lastDrawDest = buffer
    lastColor = ""
    lastBlend = ""
    lastAlpha = ""
  end
  -- Init buffer state. Tries to reduce the amount of C function calls we need
  -- to do by keeping track of the last buffer and its state.
  local flashing = (self.flashTimer > 0)
  local color = flashing and self.flashColor or self.color
  local blend = flashing and "color" or self.blend
  local alpha = self.alpha
  if color ~= lastColor then 
    lastColor = color
    local r, g, b
    if color then
      r, g, b = unpack(color)
    end
    buffer:setColor(r, g, b)
  end
  if blend ~= lastBlend then
    lastBlend = blend
    buffer:setBlend(blend)
  end
  if alpha ~= lastAlpha then
    lastAlpha = alpha
    buffer:setAlpha(alpha)
  end
  -- Draw
  buffer:draw(self.image,
              self:getScreenX() + self.offset.x + self.origin.x,
              self:getScreenY() + self.offset.y + self.origin.y,
              self.frames[self.frame],
              math.rad(self.angle),
              self.flip and -self.scale.x or self.scale.x,
              self.scale.y,
              self.origin.x, self.origin.y)
end


return Entity
