local _ = require "lib.lume"

local saved = {}
local filename = "saved.dat"

-- Try to load from disk

if juno.fs.exists(filename) then
  saved = _.deserialize(juno.fs.read(filename))
end

-- Init proxy table and return

local proxy = {}
  
function proxy.flush()
  juno.fs.write(filename, _.serialize(saved))
end

function proxy.clear()
  saved = {}
  proxy.flush()
end
  

setmetatable(proxy, {

  __index = function(t, k)
    return saved[k]
  end,

  __newindex = function(t, k, v)
    if type(v) == "table" then
      error("`saved` table does not support nested table")
    end
    saved[k] = v
    t:flush()
  end,

})


return proxy
