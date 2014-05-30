
local SCENE_NAME = "SubListScene"

local SceneClass = class(SCENE_NAME, function() 
    return display.newScene(SCENE_NAME)
end)

function SceneClass:ctor(testName)
    local list = require("app.scenes." .. tostring(testName) .. ".list")
    
    local items = {}
    for _, name in pairs(list) do
        local label = cc.Label:createWithSystemFont(name, "Arial", 32)
        
        local menuItem = cc.MenuItemLabel:create(label)
        table.insert(items, menuItem)
        
        menuItem:registerScriptTapHandler(function(tag) 
            app:enterScene(testName .. "." .. name)
        end)
    end
    
    local menu = cc.Menu:create(unpack(items))
    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(display.cx, display.cy)
    self:addChild(menu)
end

return SceneClass