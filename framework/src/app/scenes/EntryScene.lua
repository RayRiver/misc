
local SCENE_NAME = "EntryScene"

local SceneClass = class(SCENE_NAME, function() 
    return display.newScene(SCENE_NAME)
end)

function SceneClass:ctor()
    
end

function SceneClass:onEnter()
    app:enterScene("MenuScene")
end

return SceneClass
