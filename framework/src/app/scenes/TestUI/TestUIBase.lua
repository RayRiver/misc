
local SCENE_NAME = "TestUIBase"

local SceneClass = class(SCENE_NAME, function() 
    return display.newScene(SCENE_NAME)
end)

function SceneClass:ctor()
    self:createGrid()
    self:createBackButton()
    
    self:setNodeDrawEnabled(true)
    self:setNodeDrawDebugEnabled(true)
    
    --printInfo("scene pos: %d %d", self:getPositionX(), self:getPositionY())
    --printInfo("scene anc: %d %d", self:getAnchorPoint().x, self:getAnchorPoint().y)
    --printInfo("scene siz: %d %d", self:getContentSize().width, self:getContentSize().height)
end

function SceneClass:onEnter()

end

function SceneClass:createGrid()
    local step = 40

    display.newColorLayer(cc.c4b(230,230,230,255)):addTo(self)

    for y = display.bottom, display.top, 40 do
        display.newSegment(
            cc.p(display.left, y),
            cc.p(display.right, y),
            1,
            cc.c4b(200, 200, 200, 100)
        ):addTo(self)
    end

    for x = display.left, display.right, 40 do
        display.newSegment(
            cc.p(x, display.bottom),
            cc.p(x, display.top),
            1,
            cc.c4b(200, 200, 200, 100)
        ):addTo(self)
    end

    display.newSegment(
        cc.p(display.left, display.cy),
        cc.p(display.right, display.cy),
        1,
        cc.c4b(250, 100, 100, 100)
    ):addTo(self)

    display.newSegment(
        cc.p(display.cx, display.bottom),
        cc.p(display.cx, display.top),
        1,
        cc.c4b(250, 100, 100, 100)
    ):addTo(self)


    --[[
    display.newPolygon(
    {
    cc.p(display.left, display.bottom),
    cc.p(display.left, display.top),
    cc.p(display.right, display.top),
    cc.p(display.right, display.bottom),
    },
    cc.c4b(230, 0, 0, 123)
    )--:addTo(self)

    display.newTriangle(
    cc.p(100, 100),
    cc.p(200, 200),
    cc.p(300, 150),
    cc.c4f(1, 0, 0, 1)
    )--:addTo(self)
    --]]
end

function SceneClass:createBackButton()
    local button = ccui.Button:create("textures/ui/NextButton.png")
    ccui.WidgetEx.extend(button)
        :align(display.RIGHT_BOTTOM, display.right, display.bottom)
        :addTo(self)
        
    button:addTouchEventListener(function(ref, type) 
        if type == ccui.TouchEventType.ended then
            app:enterScene("EntryScene")
        end
    end)
end

return SceneClass
