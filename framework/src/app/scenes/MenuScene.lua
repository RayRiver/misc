
local MENU_ITEMS =
{
    {
        text = "TestUIButtonScene",
        listener = "onChooseTestUIButton",
    },
    {
        text = "TestUIImageScene",
        listener = "onChooseTestUIImage",
    },
    {
        text = "TestUISliderScene",
        listener = "onChooseTestUISlider",
    },
}

local SCENE_NAME = "MenuScene"

local SceneClass = class(SCENE_NAME, function() 
    return display.newScene(SCENE_NAME)
end)

function SceneClass:ctor()
    local function getMenuItemParams(index)
        local params = MENU_ITEMS[index]
        if not params then return end
        params.listener = handler(self, self[params.listener])
        return params
    end

    local labels = {}
    for i = 1, #MENU_ITEMS do
        labels[#labels+1] = ui.newTTFLabelMenuItem(getMenuItemParams(i))
    end
    local menu = ui.newMenu(labels)
    menu:alignItemsVertically()
    menu:setPosition(display.cx, display.cy)
    self:addChild(menu)
end

function SceneClass:onEnter()

end

function SceneClass:onChooseTestUIButton()
    app:enterScene("ui.TestUIButtonScene")
end

function SceneClass:onChooseTestUIImage()

end

function SceneClass:onChooseTestUISlider()

end

return SceneClass
