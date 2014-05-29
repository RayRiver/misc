
cc.NodeEx = class("cc.NodeEx")

local NodeEx = cc.NodeEx
NodeEx.__index = NodeEx

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
    self.setPosition(x, y)
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
    self.setPosition(display.cx, display.cy)
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
                printInfo("NODE_EVENT: %s %s", self.__cname, event)
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
