local _ = require "lib.lume"
local Game = require "rxi.game"
local Entity = require "rxi.entity"


local Dialog = Entity:extend()


function Dialog:new(str)
  Dialog.super.new(self)
  _.trace("init dialog")
  -- Init text
  str = _.wordwrap(str, 30)
  self:setText("")
  local i = 0
  local str = str
  local function textLoop()
    i = i + 1
    self:setText(str:sub(1, i))
    if i < #str then
      self.timer:delay(textLoop, .03)     
    else
      self.timer
        :delay(function() self:flicker(10) end, 3)
        :after(function() self:kill() end, .2)
    end
    self.width = 0
    self:centerOffset()
  end
  textLoop()
end


function Dialog:draw()
  if self.flickerTimer > 0 and Game.frame % 2 == 0 then return end
  local x, y = self:getScreenPosition()
  local buf = self:getDrawDest()
  buf:drawRect(x - 2 + self.offset.x, y - 2, self.image:getWidth() + 4,
               self.image:getHeight() + 4, 0, 0, 0)
  Dialog.super.draw(self)
end


return Dialog

