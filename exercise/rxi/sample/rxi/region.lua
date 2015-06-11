local _ = require "lib.lume"
local Entity = require "rxi.entity"

local Region = Entity:extend()

-- A region file loaded with Region:load() should return a table with any or
-- none of the following functions:
--
-- load(self)         Called when the region is loaded
-- update(self, dt)   Called once per frame
-- enter(self, e)     Called when an entity enters the region
-- exit(self, e)      Called when an entity exits the region
--

function Region:new(id, data)
  Region.super.new(self)
  self.id = id
  self.solid = false
  self.moves = false
  self.overlapping = {}
  self.wasOverlapping = {}
  if data then
    Region:load(data)
  else
    self.callbacks = {}
  end
end


function Region:load(data)
  assert(type(data) == "string" or type(data) == "table")
  local t
  if type(data) == "string" then
    if juno.fs.exists(data) then
      t = _.dostring(juno.fs.read(data))
    else
      t = _.dostring(data)
    end
  else
    t = _.clone(data)
  end
  self.callbacks = t
  _.call(self.callbacks.load, self)
end


function Region:update(dt)
  Region.super.update(self, dt)
  -- Do update callbacks
  _.call(self.callbacks.update, self, dt)
  -- Do enter callback
  for e in pairs(self.overlapping) do
    if not self.wasOverlapping[e] then
      _.call(self.callbacks.enter, self, e)
    end
  end
  -- Do exit callback
  for e in pairs(self.wasOverlapping) do
    if not self.overlapping[e] then
      _.call(self.callbacks.exit, self, e)
    end
  end
  -- Reset tables
  local tmp = self.wasOverlapping
  self.wasOverlapping = self.overlapping
  self.overlapping = _.clear(tmp)
end


function Region:onOverlap(e)
  Region.super.onOverlap(self, e)
  self.overlapping[e] = true
end


return Region
