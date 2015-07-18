
local monster
local blackboard = {}

function love.load()
    print("load...")

    local config = {
        eyeshot = 50,
        components = {
            {
                class = "components.behavior_tree",
                config = {
                    bt = "ai.bt_test_config",
                    interval = 1,
                },
            },
        },
    }
    monster = require("objects.monster"):create(config, blackboard)
    monster:setPosition(300, 200)
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
