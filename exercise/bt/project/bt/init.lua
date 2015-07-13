
local package = ...
print(package)

local _M = {}

function _M.import(file)

end

_M.Node = require("bt/node")

bt = _M
return _M
