local TestBase = class("TestBase", function()
    local scene = cc.Scene:create()
    local layer = cc.Layer:create()
    scene:addChild(layer)
    layer.scene = scene
    return layer
end)

function TestBase:init()
    local visibleRect = cc.Director:getInstance():getOpenGLView():getVisibleRect()
    
    -- add title label
    local label = cc.Label:createWithTTF({
            fontFilePath="res/fonts/arial.ttf", 
            fontSize=32
        }, 
        self.title or "")
    label:setPosition(visibleRect.x+visibleRect.width/2, visibleRect.y+visibleRect.height-30)
    self:addChild(label)
    
    -- add sub title label
    local label = cc.Label:createWithTTF({
            fontFilePath="res/fonts/Thonburi.ttf", 
            fontSize=16
        }, 
        self.subtitle or "")
    label:setPosition(visibleRect.x+visibleRect.width/2, visibleRect.y+visibleRect.height-60)
    self:addChild(label)
    
    -- add desc label
    local label = cc.Label:createWithTTF({
            fontFilePath="res/fonts/Thonburi.ttf", 
            fontSize=16
        }, 
        tostring(""))
    label:setPosition(display.cx, display.top-75)
    self:addChild(label)
    self.desc = label
    
    -- add menu items
    local item1 = cc.MenuItemImage:create("res/Images/b1.png", "res/Images/b2.png", "res/Images/b1.png")
    local item2 = cc.MenuItemImage:create("res/Images/r1.png", "res/Images/r2.png", "res/Images/r1.png")
    local item3 = cc.MenuItemImage:create("res/Images/f1.png", "res/Images/f2.png", "res/Images/f1.png")
    local menu = cc.Menu:create(item1, item2, item3)
    
    local menu_x = visibleRect.x+visibleRect.width/2
    local menu_y = visibleRect.y+item2:getContentSize().height/2
    local distance = item2:getContentSize().width*2
    menu:setPosition(0, 0)
    item1:setPosition(menu_x-distance, menu_y)
    item2:setPosition(menu_x, menu_y)
    item3:setPosition(menu_x+distance, menu_y)
    self:addChild(menu, 100)
    
    -- menu items callback
    item1:registerScriptTapHandler(function() 
        if self.callbacks.prev then
           self.callbacks.prev.fn(self.callbacks.prev.obj) 
        end
    end)
    item2:registerScriptTapHandler(function() 
        if self.callbacks.restart then
           self.callbacks.restart.fn(self.callbacks.restart.obj) 
        end
    end)
    item3:registerScriptTapHandler(function() 
        if self.callbacks.next then
           self.callbacks.next.fn(self.callbacks.next.obj) 
        end
    end)
    
    -- add return menu button
    local label = cc.Label:createWithTTF({
        fontFilePath="res/fonts/arial.ttf", 
        fontSize=32
    }, "BACK")
    local menuItem = cc.MenuItemLabel:create(label)
    menuItem:registerScriptTapHandler(function()
        require("src.TestList")
        runTestList()
    end)
    menuItem:setAnchorPoint(1,0)
    menuItem:setPosition(display.right, display.bottom)
    local menu = cc.Menu:create(menuItem)
    menu:setPosition(0, 0)
    self:addChild(menu,100)

    -- onEnter call
    if type(self.onEnter) == "function" then
        self:onEnter()
    end
end

function TestBase:registerOnDraw()
    self.glNode = cc.GLNode:create()
    self.glNode:setContentSize(cc.size(display.width, display.height))
    self.glNode:setAnchorPoint(cc.p(0.5, 0.5))
    self.glNode:setPosition(display.width/2, display.height/2)
    self.glNode:registerScriptDrawHandler(function()
        if self.onDraw then
            self:onDraw()
        end
    end)
    self:addChild(self.glNode, -10)
end

function TestBase:setTitle(s)
    self.title = tostring(s)
end

function TestBase:setSubTitle(s)
    self.subtitle = tostring(s)
end

function TestBase:setDesc(s)
    self.desc:setString(s)
end

function TestBase:setPrevCallback(obj, fn)
    assert(obj, "prev callback obj is not valid")
    assert(type(fn) == "function", "prev callback is not a function")
    self.callbacks = self.callbacks or {}
    self.callbacks.prev = { obj=obj, fn=fn }
end

function TestBase:setNextCallback(obj, fn)
    assert(obj, "prev callback obj is not valid")
    assert(type(fn) == "function", "next callback is not a function")
    self.callbacks = self.callbacks or {}
    self.callbacks.next = { obj=obj, fn=fn }
end

function TestBase:setRestartCallback(obj, fn)
    assert(obj, "prev callback obj is not valid")
    assert(type(fn) == "function", "restart callback is not a function")
    self.callbacks = self.callbacks or {}
    self.callbacks.restart = { obj=obj, fn=fn }
end

function TestBase:run()
    if not self.scene then
        assert(false, "TestBase:scene is nil")
    end

    if cc.Director:getInstance():getRunningScene() then
        cc.Director:getInstance():replaceScene(self.scene)
    else
        cc.Director:getInstance():runWithScene(self.scene)
    end
end

return TestBase
