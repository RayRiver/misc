
local bump_debug = {}

local function getCellRect(world, cx,cy)
    local cellSize = world.cellSize
    local l,t = world:toWorld(cx,cy)
    return l,t,cellSize,cellSize
end

local s_world
function bump_debug.setWorld(world)
    s_world = world
end

function bump_debug.draw()
    local world = s_world
    if not world then
        return
    end

    for cy, row in pairs(world.rows) do
        for cx, cell in pairs(row) do
            local l,t,w,h = getCellRect(world, cx,cy)
            local intensity = cell.itemCount * 16 + 16
            love.graphics.setColor(255,255,255,intensity)
            love.graphics.rectangle('fill', l,t,w,h)
            love.graphics.setColor(255,255,255,10)
            love.graphics.rectangle('line', l,t,w,h)
        end
    end
end

return bump_debug
