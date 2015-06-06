
local Tile = require("lib.tiled.tile")

local Layer = {}
Layer.__index = Layer

local function new(class, config, sets, tilewidth, tileheight)
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
                offset_x = tilewidth * (x-1)
                offset_y = tileheight * (y-1)
            end
            local tile = Tile:new(set, id, offset_x, offset_y, tilewidth, tileheight)
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

    local t = setmetatable({
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

    t.tiles_map = {}
    for _, tile in ipairs(tiles) do
        t.tiles_map[tile.id] = tile
    end

    return t
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

function Layer:getTile(col, row)
    if row == nil then
        local id = col
        return self.tiles_map[id]
    else

    end
end

function Layer:foreachTile(func)
    if type(func) == "function" then
        for _, tile in ipairs(self.tiles) do
            local is_stop = func(tile)
            if is_stop then
                break
            end
        end
    end
end

-- the module
return setmetatable({new = new},
    {__call = function(_, ...) return new(...) end})
