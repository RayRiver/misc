
local Layer = {}
Layer.__index = Layer

local function new(class, config, sets, tilewidth, tileheight)
    local w, h = config.width, config.height

    -- 解析tiles
    local tiles = {}
    for y = 0, h-1 do
        for x = 0, w-1 do
            local index = y * w + x
            local gid = config.data[index + 1]

            if gid ~= 0 then
                local tile_config = sets:getTileConfigByGID(gid)
                local image = tile_config.image
                local quad = tile_config.quad

                local offset_x = tilewidth * (x-1)
                local offset_y = tileheight * (y-1)

                tiles[index] = {
                    x = offset_x,
                    y = offset_y,
                    w = tilewidth,
                    h = tileheight,
                    col = x,
                    row = y,
                    index = index,
                    gid = gid,
                    image = image,
                    quad = quad,
                    offset_x = offset_x,
                    offset_y = offset_y,
                }
            end
        end
    end

    -- 所有tile先绘制在canvas中
    local canvas = love.graphics.newCanvas(tilewidth * w, tileheight * h)
    love.graphics.setCanvas(canvas)
    canvas:clear()
    for index, tile in pairs(tiles) do
        love.graphics.draw(tile.image, tile.quad, tile.offset_x, tile.offset_y)
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

    return t
end

function Layer:move(dx, dy)
    self.x = self.x + dx
    self.y = self.y + dy
    for index, tile in pairs(self.tiles) do
        tile.x = tile.x + dx
        tile.y = tile.y + dy
    end
end

function Layer:draw()
    if self.visible then
        love.graphics.draw(self.canvas, self.x, self.y)
    end
end

function Layer:getTile(col_or_index, row)
    if row == nil then
        local index = col_or_index
        return self.tiles[index]
    else
        local index = row * self.width + col_or_index
        return self.tiles[index]
    end
end

function Layer:foreachTile(func)
    if type(func) == "function" then
        for index, tile_config in pairs(self.tiles) do
            local is_stop = func(tile_config)
            if is_stop then
                break
            end
        end
    end
end

-- the module
return setmetatable({new = new},
    {__call = function(_, ...) return new(...) end})
