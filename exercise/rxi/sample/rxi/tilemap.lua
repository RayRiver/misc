local _ = require "lib.lume"
local Entity = require "rxi.entity"
local Game = require "rxi.game"

local Tile = Entity:extend()

function Tile:new(filename, tilesize, index, cache)
  Tile.super.new(self)
  if cache then
    self.image = cache.image
    self.frames = cache.frames
    self.width, self.height = tilesize, tilesize
  else
    self:loadImage(filename, tilesize, tilesize)
  end
  self.frame = index
  self.last = self
  self.moves = false
  self.immovable = true
  self.moves = false
end


function Tile:setSlope(left, right, side)
  side = side or "top"
  assert(side == "top" or side == "bottom",
         "expected 'top' or 'bottom' as side")
  self.solid = false
  self.slope = { left = left, right = right, side = side }
end


function Tile:onOverlap(e)
  -- Seperation is handled in e's :onOverlap() -- Only slope seperation is
  -- handled here
  if not e.solid then return end
  local s = self.slope
  if s then
    local h = self.height
    local x = (s.left > s.right) and e:left() or e:right()
    local p = (x - self.x) / self.width
    if s.side == "bottom" then
      -- Bottom-facing slope
      local y = self.y + _.lerp(s.left, s.right, p) * h
      if e:top() < y and e.last:top() >= self:top() then
        e:top(y)
        if e.velocity.y < 0 then
          e.velocity.y = e.velocity.y * -e.bounce
        end
        e.touching.top = true
      end
    elseif s.side == "top" then
      -- Top-facing slope
      local y = self.y + (1 - _.lerp(s.left, s.right, p)) * h
      if e:bottom() > y and e.last:bottom() <= self:bottom() then
        e:bottom(y)
        if e.velocity.y > 0 then
          e.velocity.y = e.velocity.y * -e.bounce
        end
        e.touching.bottom = true
      end
    end
  end
end


local Tilemap = Entity:extend()

Tilemap.Tile = Tile

function Tilemap:new()
  Tilemap.super.new(self)
  self.solid = false
end


function Tilemap:loadArray(array, width, imageFile, tileSize)
  if #array % width ~= 0 then
    error("expected array to be divisible by width")
  end
  -- Init fields
  self.data = _.clone(array)
  self.widthInTiles = width
  self.heightInTiles = #array / width
  self.tileSize = tileSize
  self.tiles = {}
  -- Load tile entities
  local cache = Tile(imageFile, tileSize, 1)
  for i = 1, math.huge do
    local tile = Tile(imageFile, tileSize, i, cache)
    table.insert(self.tiles, tile)
    if i == #tile.frames then
      break
    end
  end
  -- Init size
  self.width = self.widthInTiles * self.tileSize
  self.height = self.heightInTiles * self.tileSize
end


function Tilemap:loadTmx(filename, objHandler, tileLayer, imageFile)
  local text = juno.fs.read(filename)
  -- Get map data
  local ptn = '"csv">(.-)<'
  if tileLayer then  
    ptn = 'name="' .. tileLayer .. '".-' .. ptn
  end
  local s = text:match(ptn)
  assert(s, "tile layer does not exist")
  local data = _.map(_.split(s, ","), tonumber)
  local width = tonumber(text:match('width="(.-)"'))
  local tileSize = tonumber(text:match('tilewidth="(.-)"'))
  -- Load tile entities
  if not imageFile then
    imageFile = text:match('image source="(.-)"'):gsub("%.%.", "data")
  end
  -- Load map
  self:loadArray(data, width, imageFile, tileSize)
  -- Load objects
  if objHandler then
    for objStr in text:gmatch("<object (.-)/>") do
      local o = {}
      for k, v in objStr:gmatch('(%w-)="(.-)"') do
        o[k] = v
      end
      o.x = tonumber(o.x)
      o.y = tonumber(o.y)
      o.width = tonumber(o.width)
      o.height = tonumber(o.height)
      objHandler(o)
    end
  end
  return self
end


function Tilemap:getTile(x, y)
  local t = self.tiles[self.data[x + y * self.widthInTiles + 1]]
  if t then
    t.x, t.y = x * self.tileSize + self.x, y * self.tileSize + self.y
    return t
  end
end


local overlapsState
local overlapsSolid = function(t, e)
  if t.solid and e:overlaps(t) then
    overlapsState = true
  end
end

function Tilemap:overlapsSolid(e)
  overlapsState = false
  self:eachOverlappingTile(e, overlapsSolid, nil, nil, e)
  return overlapsState
end


function Tilemap:eachOverlappingTile(r, fn, revx, revy, ...)
  local sx = math.floor((r:left()    - self.x) / self.tileSize)
  local sy = math.floor((r:top()     - self.y) / self.tileSize)
  local ex = math.floor((r:right()   - self.x) / self.tileSize)
  local ey = math.floor((r:bottom()  - self.y) / self.tileSize)
  sx, sy = math.max(sx, 0), math.max(sy, 0)
  ex = math.min(ex, self.widthInTiles - 1)
  ey = math.min(ey, self.heightInTiles - 1)
  if revx then sx, ex = ex, sx end
  if revy then sy, ey = ey, sy end
  for y = sy, ey, (revy and -1 or 1) do
    for x = sx, ex, (revx and -1 or 1) do
      local t = self:getTile(x, y) 
      if t then fn(t, ...) end
    end
  end
end


local onOverlap = function(t, e)
  e:onOverlap(t)
  t:onOverlap(e)
end

function Tilemap:onOverlap(e)
  self:eachOverlappingTile(e, onOverlap, e.velocity.x < 0, e.velocity.y < 0, e)
end


function Tilemap:update(dt)
  Tilemap.super.update(self, dt)
  _.each(self.tiles, "update", dt)
end


function Tilemap:draw()
  self:eachOverlappingTile(Game.camera, Tile.draw)
end



return Tilemap
