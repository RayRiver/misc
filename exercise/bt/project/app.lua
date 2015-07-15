
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

    local factory = bt.Factory

    local root
    if true then
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

    updateBT(root)
end

function love.update(dt)
    if love.keyboard.isDown('escape') then
        love.event.push('quit')
    end
end

function love.draw()

end
