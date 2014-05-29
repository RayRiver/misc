
local SCENE_NAME = "TestUIButtonScene"

local SceneClass = class(SCENE_NAME, function() 
    return display.newScene(SCENE_NAME)
end)

function SceneClass:ctor()

end

function SceneClass:onEnter()
    display.newPolygon(
        {
            cc.p(display.left, display.bottom),
            cc.p(display.left, display.top),
            cc.p(display.right, display.top),
            cc.p(display.right, display.bottom),
        },
        cc.c4b(255, 255, 255, 255),
        1,
        cc.c4b(255, 0, 0, 155)
    ):addTo(self)
end

return SceneClass
