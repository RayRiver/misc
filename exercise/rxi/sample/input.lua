local _ = require "lib.lume"

local input = {}

local keymap = {
  left    = { "left",   "a" },
  right   = { "right",  "d" },
  up      = { "up",     "w" },
  down    = { "down",   "s" },
  select  = { "x", "c", "j", "k", "space", "return" },
  jump    = { "x", "k" },
  attack  = { "c", "j" },
  action  = { "down", "up" },
}


function input.isDown(name)
  return _.any(keymap[name], juno.keyboard.isDown)
end


function input.wasPressed(name)
  return _.any(keymap[name], juno.keyboard.wasPressed)
end


return input
