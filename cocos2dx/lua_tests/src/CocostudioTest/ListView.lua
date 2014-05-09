local TestClass = class("ListView", require("src.TestBase"))

function TestClass:onEnter()
    self:setDesc("")

    --local widget = ccs.GUIReader:getInstance():widgetFromJsonFile("res/ccs/BaseUI/Export/ListView/ListView.json")
    --self:addChild(widget)
    
    local layout = ccui.Layout:create()
    layout:setSize(cc.size(250,160))
    layout:setPosition(display.cx-layout:getSize().width/2, display.cy-layout:getSize().height/2)
    layout:setBackGroundImageScale9Enabled(true)
    layout:setBackGroundImage("res/Images/CyanSquare.png")
    self:addChild(layout)

    local listview = ccui.ListView:create()
    listview:setTouchEnabled(true)
    listview:setBounceEnabled(true)
    listview:setSize(cc.size(250,160))
    listview:setDirection(ccui.ScrollViewDir.vertical)
    listview:setGravity(ccui.ListViewGravity.centerHorizontal)
    listview:setItemsMargin(2)
    --listview:setBackGroundImage("res/Images/stars2-grayscale.png")
    layout:addChild(listview)
    

    local default_widget = ccui.Button:create("res/cocosui/animationbuttonnormal.png", "res/cocosui/animationbuttonpressed.png")
    default_widget:setName("default_widget")
    
    local default_item = ccui.Layout:create()
    default_item:setTouchEnabled(true)
    default_item:setSize(default_widget:getSize())
    default_widget:setPosition(default_item:getSize().width/2, default_item:getSize().height/2)
    default_item:addChild(default_widget)
    
    listview:setItemModel(default_item)
    
    listview:pushBackDefaultItem()
    listview:pushBackDefaultItem()
    listview:pushBackDefaultItem()
    listview:pushBackDefaultItem()
    listview:pushBackDefaultItem()
    listview:pushBackDefaultItem()
    listview:pushBackDefaultItem()
    listview:pushBackDefaultItem()
    listview:pushBackDefaultItem()
    
    -- set item data
    for i = 0, 8 do
        local item = listview:getItem(i)
        local widget = item:getChildByName("default_widget")
        local index = listview:getIndex(item)
        widget:setTitleText("default " .. tostring(index))
    end
    

end

return TestClass