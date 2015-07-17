
local monster
local blackboard = {}

function love.load()
    print("load...")

    --[[
    local bt = require("bt.init")
    local factory = bt.Factory

    if false then
        root = factory:createNode("PrioritySelectorNode", "root", factory:createCond("PreconditionTRUE"))
        root:addChild(
            factory:createNode("LoopNode", "loop", 3):addChild(
                factory:createNode("ActionNode", "action")
            )
        )
    else
        root = bt.Reader.loadFile("bt_test_config")
        print("root: ", tostring(root))
    end
    --]]

    monster = require("monster"):create({ai="ai.bt_test_config"}, blackboard)
end

function love.update(dt)
    if love.keyboard.isDown('escape') then
        love.event.push('quit')
    end

    monster:update(dt)
end

function love.draw()
    monster:draw()
end
