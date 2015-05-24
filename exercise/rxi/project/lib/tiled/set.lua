
local Set = {}
Set.__index = Set

local function new(class, config)
    local quads = {}

    local w = config.imagewidth / config.tilewidth
    local h = config.imageheight / config.tileheight
    for i = 0, w*h do
        local col = i % w
        local row = (i - col) / w
        quads[i] = love.graphics.newQuad(
            col * config.tilewidth, row * config.tileheight,
            config.tilewidth, config.tileheight,
            config.imagewidth, config.imageheight
        )
    end

    return setmetatable({
        name = config.name,
        firstgid = config.firstgid,
        tilewidth = config.tilewidth,
        tileheight = config.tileheight,
        image = love.graphics.newImage(config.image),
        quads = quads,
    }, Set)
end

-- the module
return setmetatable({new = new},
    {__call = function(_, ...) return new(...) end})
