
local _M = {}

_M.gameSystem = gx.GameSystem:getInstance()

_M.createSystem = import(".SystemBase")
_M.createCom = import(".ComBase")

return _M
