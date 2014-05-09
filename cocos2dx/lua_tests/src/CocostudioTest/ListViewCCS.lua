local TestClass = class("ListViewCCS", require("src.TestBase"))

function TestClass:onEnter()
    self:setDesc("")

    local widget = ccs.GUIReader:getInstance():widgetFromJsonFile("res/ccs/BaseUI/Export/ListView/ListView.json")
    self:addChild(widget)
    
    local listview = widget:getChildByName("ListView1")
    listview:setItemsMargin(2)
    
    local default_widget = ccui.Button:create("res/cocosui/animationbuttonnormal.png", "res/cocosui/animationbuttonpressed.png")
    default_widget:setName("default_widget")
    
    local default_layout = ccui.Layout:create()
    default_layout:setTouchEnabled(true)
    default_layout:setSize(default_widget:getSize())
    default_widget:setPosition(default_layout:getSize().width/2, default_layout:getSize().height/2)
    default_layout:addChild(default_widget)
    
    -- 默认控件
    local item_widget = ccs.GUIReader:getInstance():widgetFromJsonFile("res/ccs/BaseUI/Export/ListViewItem/ListViewItem.json")
    listview:setItemModel(item_widget)
    for i = 1, 8 do
        local index = #listview:getItems()
        --listview:pushBackDefaultItem()
        listview:insertDefaultItem(index)
        
        local item = listview:getItem(index)
        
        local label = item:getChildByName("Label1")
        label:setText("默认按钮: ")
        
        local button = item:getChildByName("Button1")
        button:addTouchEventListener(function(sender, type)
            if type == ccui.TouchEventType.began then
                label:setText("按下按钮 " .. tostring(index) .. ": ")
            elseif type == ccui.TouchEventType.ended then
                label:setText("弹起按钮 " .. tostring(index) .. ": ")
            elseif type == ccui.TouchEventType.canceled then
                label:setText("取消按钮 " .. tostring(index) .. ": ")
            end
        end)
    end
    
    -- 自定义控件
    local item_widget = ccs.GUIReader:getInstance():widgetFromJsonFile("res/ccs/BaseUI/Export/ListViewItem2/ListViewItem2.json")
    for i = 1, 8 do
        local _item_widget = item_widget:clone()
        
        local index = #listview:getItems()
        --listview:pushBackCustomItem(_item_widget)
        listview:insertCustomItem(_item_widget, index)
        
        local item = listview:getItem(index)
        
        local label = item:getChildByName("Label1")
        label:setText("自定按钮: ")
        
        local button = item:getChildByName("Button1")
        button:addTouchEventListener(function(sender, type)
            if type == ccui.TouchEventType.began then
                label:setText("按下按钮 " .. tostring(index) .. ": ")
            elseif type == ccui.TouchEventType.ended then
                label:setText("弹起按钮 " .. tostring(index) .. ": ")
            elseif type == ccui.TouchEventType.canceled then
                label:setText("取消按钮 " .. tostring(index) .. ": ")
            end
        end)

    end
end

return TestClass