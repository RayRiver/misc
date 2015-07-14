
local function updateBT(root)
    local input = {}
    local output = {}

    if root and root:evaluate(input) then
        root:update(input, output)
    end
end

function love.load()
    print("load...")
    local bt = require("bt.init")

    local factory = bt.Factory:instance()

    local root = factory:createNode("PrioritySelectorNode", "root", factory:createCond("ConditionTRUE"))
    root:addChild(
        factory:createNode("LoopNode", "loop", 3):addChild(
            factory:createNode("ActionNode", "action")
        )
    )

    updateBT(root)
end

function love.update(dt)
    if love.keyboard.isDown('escape') then
        love.event.push('quit')
    end
end

function love.draw()

end
