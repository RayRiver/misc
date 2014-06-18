
require("config")
require("framework.init")

local AppClass = class("AppClass")

function AppClass:ctor()
    app = self
end

function AppClass:run()
    self:enterScene("game_scene")
end

function AppClass:enterScene(sceneName)
    local scenePackageName = "app.scenes." .. sceneName
    local sceneClass = require(scenePackageName)
    local scene = sceneClass.new()
    display.replaceScene(scene)
end

return AppClass
