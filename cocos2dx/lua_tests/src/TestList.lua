local TESTLIST = 
{
    "FrameworkTest",
    "ActionsTest",
    
    "UserExtTest",
    "ArmatureTest",
    "ActionManagerTest",
    
    "CocostudioTest",
    "SchedulerTest",

}

local LINE_SPACE = 40

local TestList = class("TestList", function()
    local scene = cc.Scene:create()
    local layer = cc.Layer:create()
    scene:addChild(layer)
    layer.scene = scene
    return layer
end)

function TestList:init()
    local layout = ccs.GUIReader:getInstance():widgetFromJsonFile("res/ccs/BaseUI/Export/TestList/TestList.json")
    self:addChild(layout)
    local listview = layout:getChildByName("ListView1")
    --listview:setItemsMargin(2)
    
    -- 默认控件
    local item_widget = ccs.GUIReader:getInstance():widgetFromJsonFile("res/ccs/BaseUI/Export/TestListItem/TestListItem.json")
    listview:setItemModel(item_widget)
    for i = 1, #TESTLIST do
        local index = #listview:getItems()
        listview:insertDefaultItem(index)
        
        local item = listview:getItem(index)
        
        local button = item:getChildByName("Button1")
        local name = TESTLIST[i]
        button:setTitleText(name)
        button:addTouchEventListener(function(sender, type)
            if type == ccui.TouchEventType.ended then
                require("src.TestManager")
                runTest(name)
            end
        end)
    end
end

function TestList:run()
    if not self.scene then
        assert(false, "TestList:scene is nil")
    end

    if cc.Director:getInstance():getRunningScene() then
        cc.Director:getInstance():replaceScene(self.scene)
    else
        cc.Director:getInstance():runWithScene(self.scene)
    end
end

function runTestList()
    local testList = TestList.new()
    testList:init()
    testList:run()
end

