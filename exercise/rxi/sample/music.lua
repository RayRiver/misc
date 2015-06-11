local _ = require "lib.lume"
local flux = require "lib.flux"

local music = {}

local tracks = {
  ["music1"] = juno.Data.fromFile("data/music/music1.ogg"),
  ["music2"] = juno.Data.fromFile("data/music/music2.ogg"),
}


function music.play(name)
  if not reset and name == music.name then return end
  -- Store old source
  music.lastSource = music.source
  -- Load new music source
  music.name = name
  music.source = juno.Source.fromData(tracks[name])
  music.source:setLoop(1)
  music.source:setGain(0)
  music.source:play()
  -- Fade out old track, fade in new track
  local last = music.lastSource
  local current = music.source
  local t = { old = 1, new = 0 }
  flux.to(t, 1, { old = 0, new = 1 })
    :onupdate(function()
       current:setGain(t.new)
       if last then last:setGain(t.old) end
    end)
    :oncomplete(function()
      if last then last:stop() end
    end)
end


return music
