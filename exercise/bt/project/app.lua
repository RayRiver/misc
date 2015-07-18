
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

    local config = require("data.objects.test_monster")
    local entity_manager = require("objects.entity_manager"):instance()
    entity_manager:setWorld(nil)
    entity_manager:setBlackboard(blackboard)

    monster = entity_manager:createEntity(config)
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
