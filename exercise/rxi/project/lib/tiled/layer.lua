
local Tile = require("lib.tiled.tile")

local Layer = {}
Layer.__index = Layer

local function new(class, config, sets)
    local w, h = config.width, config.height

    -- tile id界限解析
    local firstgids = {}
    for _, set in ipairs(sets) do
        table.insert(firstgids, set.firstgid)
    end
    table.sort(firstgids)

    local current_set
    local tiles = {}
    for y = 0, h-1 do
        for x = 0, w-1 do
            local index = config.data[y * w + x + 1]

            -- 找到属于哪个set
            local set_id = 0
            for i, firstgid in ipairs(firstgids) do
                if index >= firstgid then
                    set_id = i
                else
                    break
                end
            end

            -- 创建tile
            local set
            local id
            local offset_x
            local offset_y
            if set_id > 0 then
                set = sets[set_id]
                id = index - set.firstgid
                offset_x = set.tilewidth * (x-1)
                offset_y = set.tileheight * (y-1)
                current_set = set
            else
                id = 0
            end
            local tile = Tile:new(set, id, offset_x, offset_y)
            table.insert(tiles, tile)
        end
    end

    local canvas = love.graphics.newCanvas(current_set.tilewidth * w, current_set.tileheight * h)
    love.graphics.setCanvas(canvas)
    canvas:clear()
    for _, tile in ipairs(tiles) do
        tile:draw()
    end
    love.graphics.setCanvas()

    return setmetatable({
        x = 0,
        y = 0,
        name = config.name,
        width = config.width,
        height = config.height,
        visible = config.visible,
        opacity = config.opacity,
        tiles = tiles,
        canvas = canvas,
    }, Layer)
end

function Layer:move(dx, dy)
    self.x = self.x + dx
    self.y = self.y + dy
    for _, tile in ipairs(self.tiles) do
        tile:move(dx, dy)
    end
end

function Layer:draw()
    if self.visible then
        love.graphics.draw(self.canvas, self.x, self.y)
    end
end

-- the module
return setmetatable({new = new},
    {__call = function(_, ...) return new(...) end})
