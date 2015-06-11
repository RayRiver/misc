local _ = require "lib.lume"
local Game = require "rxi.game"
local State = require "rxi.state"
local Entity = require "rxi.entity"
local Group = require "rxi.group"
local Tilemap = require "rxi.tilemap"
local Backdrop = require "rxi.backdrop"
local saved = require "saved"
local StateEx = require "stateex"
local Player = require "player"
local Camera = require "camera"
local LeafSpawner = require "leafspawner"
local Crate = require "crate"
local Door = require "door"
local Egg = require "egg"
local Bat = require "bat"
local music = require "music"


local PlayState = StateEx:extend()


function PlayState:loadObject(obj)
  ({
    music = function()
      music.play(obj.type)
    end,
      
    player = function()
      self.player:middleX(obj.x)
      self.player:middleY(obj.y)
    end,

    door = function()
      local e = Door(obj.x, obj.y, obj.width, obj.height, obj.type)
      self.world:add(e)
    end,

    autodoor = function()
      local e = Door(obj.x, obj.y, obj.width, obj.height, obj.type)
      e.auto = true
      self.world:add(e)
    end,

    hiddendoor = function()
      local e = Door(obj.x, obj.y, obj.width, obj.height, obj.type)
      e.hidden = true
      self.world:add(e)
    end,

    egg = function()
      local e = Egg(obj.x, obj.y, self.mapName)
      self.world:add(e)
    end,

    crate = function()
      local e = Crate()
      e:warp(obj.x, obj.y)
      self.world:add(e)
    end,

    bat = function()
      local e = Bat(obj.type)
      e:middleX(obj.x)
      e:middleY(obj.y)
      self.world:add(e)
    end,

    leafspawner = function()
      local e = LeafSpawner(obj.x, obj.y, obj.width, obj.height)
      self.world:add(e)
    end,

  })[obj.name]()
end


function PlayState:create()
  _.trace("PlayState inited")
  saved.runcount = (saved.runcount or 0) + 1
  _.trace("runs:", saved.runcount)

  --Game.bgcolor = { 153 / 0xff, 194 / 0xff, 209 / 0xff }
  -- TODO Remove this:
  --self.mapName = self.mapName or "home"

  -- Save/load current place
  if not self.mapName then
    self.mapName  = saved.mapName or "home"
    self.destDoor = saved.destDoor
  else
    saved.mapName  = self.mapName
    saved.destDoor = self.destDoor
    saved.playerFlip = (Player.lastInstance and Player.lastInstance.flip)
  end

  -- Init root entities
  self.camera = Camera()
  self:add(self.camera)

  self.world = Group()
  self:add(self.world)

  -- Init player
  self.player = Player()
  self.world:add(self.player)

  -- Init tilemap
  self.mapName = self.mapName or "test"
  local mapFilename = "data/map/" .. self.mapName .. ".tmx"

  self.tilemap = Tilemap():loadTmx(
    mapFilename,
    function(o) self:loadObject(o) end,
    "main")
  -- Init tile slopes .. messy messy messy :3
  for i = 1, 31 do self.tilemap.tiles[32 * 16 + i]:setSlope(0, 1) end
  for i = 1, 31 do self.tilemap.tiles[32 * 17 + i]:setSlope(1, 0) end
  -- Top - half slope
  for i = 1, 31 do
    if i % 2 == 1 then
      self.tilemap.tiles[32 * 18 + i]:setSlope(0, .5)
    else
      self.tilemap.tiles[32 * 18 + i]:setSlope(.5, 1)
    end
  end
  for i = 1, 31 do
    if i % 2 == 1 then
      self.tilemap.tiles[32 * 19 + i]:setSlope(1, .5)
    else
      self.tilemap.tiles[32 * 19 + i]:setSlope(.5, 0)
    end
  end
  -- Bottom - half slope
  for i = 1, 31 do
    if i % 2 == 1 then
      self.tilemap.tiles[32 * 20 + i]:setSlope(1, .5, "bottom")
    else
      self.tilemap.tiles[32 * 20 + i]:setSlope(.5, 0, "bottom")
    end
  end
  for i = 1, 31 do
    if i % 2 == 1 then
      self.tilemap.tiles[32 * 21 + i]:setSlope(0, .5, "bottom")
    else
      self.tilemap.tiles[32 * 21 + i]:setSlope(.5, 1, "bottom")
    end
  end
  -- Init death tiles
  for i = 1, 31 do self.tilemap.tiles[32 * 24 + i].death = true end
  -- Init over/under tilemap
  local under = Tilemap():loadTmx(mapFilename, nil, "under")
  under.collidable = false
  self:add(under, 1)
  local over = Tilemap():loadTmx(mapFilename, nil, "over")
  over.collidable = false
  self:add(over)
  -- Add tilemap to world
  self.world:add(self.tilemap)

  -- Init backdrop
  -- Don't know whether to keep these -- perhaps disable parallax?
  local backdrop = Backdrop("data/image/backdrop1.png", .45)
  self:add(backdrop, 1)
  local backdrop = Backdrop("data/image/backdrop2.png", .4)
  self:add(backdrop, 1)

  -- Warp player to destination door if it exists
  if self.destDoor then
    local door = _.match(self.world.members, function(x)
      return x:is(Door) and x.id == self.destDoor
    end)
    assert(door)
    self.player:bottom(door:bottom())
    self.player:middleX(door:middleX())
  end

  -- Init camera
  self.camera:bind(self.tilemap)
  self.camera:follow(self.player)
  self.camera:at(self.player)

  -- Add controls text if this is a new game
  if not saved.donePlayState then
    local e = Entity():loadImage("data/image/controls.png")
    e:middleX(self.camera:middleX())
    e:top(self.camera:top() + 40)
    e.collidable = false
    e.alpha = 0
    e.timer:delay(function()
      e.alpha = 1
      e:flicker(.5)
    end, .5)
    self:add(e)
  end

  saved.donePlayState = true
  PlayState.super.create(self)
end


function PlayState:update(dt)
  -- clear lightmap
  if self.lightmap then
    self.lightmap.image:clear(0, 0, 0, 1)
  end
  -- update
  PlayState.super.update(self, dt)
  -- Clamp player to tilemap
  self.player:clamp(self.tilemap)
end



return PlayState
