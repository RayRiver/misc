
cc.NodeEx = class("cc.NodeEx")

local NodeEx = cc.NodeEx
NodeEx.__index = NodeEx
NodeEx.isNode = true

function NodeEx.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, NodeEx)
    return target
end

function NodeEx:align(anchorPoint, x, y)
    self:setAnchorPoint(display.ANCHOR_POINTS[anchorPoint])
    if x and y then self:setPosition(x, y) end
    return self
end

function NodeEx:schedule(callback, interval)
    local action = cc.RepeatForever:create(cc.Sequence:create(
        cc.DelayTime:create(interval),
        cc.CallFunc:create(callback)
    ))
    self:runAction(action)
    return action
end

function NodeEx:performWithDelay(callback, delay)
    local action = cc.Sequence:create(
        cc.DelayTime:create(delay),
        cc.CallFunc:create(callback)
    )
    self:runAction(action)
    return action
end

function NodeEx:add(child, zorder, tag)
    self:addChild(child, zorder or 0, tag or 0)
    return self
end

function NodeEx:addTo(target, zorder, tag)
    target:addChild(self, zorder or 0, tag or 0)
    return self
end

function NodeEx:show()
    self:setVisible(true)
    return self
end

function NodeEx:hide()
    self:setVisible(false)
    return self
end

function NodeEx:pos(x, y)
    self:setPosition(x, y)
    return self
end

function NodeEx:scale(scale)
    self:setScale(scale)
    return self
end

function NodeEx:rotation(scale)
    self:setRotation(scale)
    return self
end

function NodeEx:size(w, h)
    if type(w) == "userdata" then
        self:setContentSize(w)
    else
        self:setContentSize(cc.Size(w, h))
    end
    return self
end

function NodeEx:center()
    self:setPosition(display.cx, display.cy)
    return self
end

function NodeEx:opacity(opacity)
    self:setOpacity(opacity)
    return self
end

function NodeEx:zorder(z)
    self:setZOrder(z)
    return self
end

function NodeEx:setNodeDrawDebugEnabled(enabled)
    self.isDrawDebug = enabled
end

function NodeEx:setNodeDrawEnabled(enabled, listener, debug_listener)
    if enabled then
        if not self.glNode then
            self.glNode = cc.GLNode:create()
            self.glNode:setContentSize(self:getContentSize())
            self.glNode:setAnchorPoint(self:getAnchorPoint())
            self.glNode:setPosition(0, 0)
        else
            self.glNode:unregisterScriptDrawHandler()
        end
        
        local fn = function()
            if listener then
                listener()
            elseif self.onDraw then
                self:onDraw()
            end
            
            if self.isDrawDebug then 
                if debug_listener then
                    debug_listener()
                else
                    self:onDrawDebug() 
                end
            end
        end

        self.glNode:registerScriptDrawHandler(fn)
        
        self:addChild(self.glNode, 10000)
    else
        self.glNode:unregisterScriptDrawHandler()
    end
end

function NodeEx:onDrawDebug()
    cc.DrawPrimitives.drawColor4F(255, 0, 0, 255)
    
    local function _drawNode(node)
        if not node:isVisible() then return end
        if node.isScene or node.isLayer then return end

        local x, y = node:getPosition()
        local size = node:getContentSize()
        local anchor = node:getAnchorPoint()
        local scale_x = node:getScaleX()
        local scale_y = node:getScaleY()
        local origin = cc.p(x-(size.width*anchor.x)*scale_x, y-(size.height*anchor.y)*scale_y)
        local destination = cc.p(x+(size.width*(1-anchor.x))*scale_x, y+(size.height*(1-anchor.y))*scale_y)

        cc.DrawPrimitives.drawRect(origin, destination)
    end

    local function _drawNodes(node)
        _drawNode(node)
        local children = node:getChildren()
        for _, n in pairs(children) do
            _drawNodes(n)
        end
    end
    
    _drawNodes(self)
end

function NodeEx:setNodeEventEnabled(enabled, handler)
    if enabled then
        if not handler then
            handler = function(event)
                if event == "enter" then
                    self:onEnter()
                elseif event == "exit" then
                    self:onExit()
                elseif event == "enterTransitionFinish" then
                    self:onEnterTransitionFinish()
                elseif event == "exitTransitionStart" then
                    self:onExitTransitionStart()
                elseif event == "cleanup" then
                    self:onCleanup()
                end
                --printInfo("NODE_EVENT: %s %s", self.__cname, event)
            end
        end
        self:registerScriptHandler(handler)
    else
        self:unregisterScriptHandler()
    end
    return self
end

function NodeEx:onEnter()
    -- override
end

function NodeEx:onExit()
    -- override
end

function NodeEx:onEnterTransitionFinish()
    -- override
end

function NodeEx:onExitTransitionStart()
    -- override
end

function NodeEx:onCleanup()
    -- override
end
