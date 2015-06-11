local _ = require "lib.lume"
local Group = require "rxi.group"

local State = Group:extend()

function State:new()
  State.super.new(self)
  if self.new ~= State.new then
    error("State's constructor overridden. override State:create() instead")
  end
end


function State:create()

end


function State:destroy()

end

return State
