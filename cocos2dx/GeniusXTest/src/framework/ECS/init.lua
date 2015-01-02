
local _M = {}

_M.gameSystem = gx.GameSystem:getInstance()

_M.createSystem = import(".SystemBase")
_M.createCom = import(".ComBase")
_M.createScene = import(".SceneBase")

return _M
