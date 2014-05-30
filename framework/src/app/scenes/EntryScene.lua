
local SCENE_NAME = "EntryScene"

local SceneClass = class(SCENE_NAME, function() 
    return display.newScene(SCENE_NAME)
end)

function SceneClass:ctor()
    
end

function SceneClass:onEnter()
    self:enterTest("TestUI")
end

function SceneClass:enterTest(testName)
    local SubListScene = require("app.scenes.SubListScene")
    local scene = SubListScene.new(testName)
    display.replaceScene(scene)
end

return SceneClass
