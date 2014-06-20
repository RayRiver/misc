
local SCENE_NAME = "EntryScene"

local SceneClass = class(SCENE_NAME, function() 
    local scene = display.newScene()
    return scene
end)

function SceneClass:ctor()

    local label = cc.Label:createWithSystemFont("start", "Arial", 32)
    local menuItem = cc.MenuItemLabel:create(label)
    menuItem:registerScriptTapHandler(function(tag) 
        app:enterScene("game_scene")
    end)

    local menu = cc.Menu:create(menuItem)
    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(display.cx, display.cy)
    self:addChild(menu)
end

return SceneClass
