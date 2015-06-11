
local Sets = {}
Sets.__index = Sets

local function new(class)
    return setmetatable({
        tiles = {},
    }, Sets)
end

function Sets:addSet(set_config)
    local config = set_config

    local image = love.graphics.newImage(config.image)

    local w = config.imagewidth / config.tilewidth
    local h = config.imageheight / config.tileheight
    for i = 0, w*h do
        local col = i % w
        local row = (i - col) / w

        local gid = row * w + col + config.firstgid
        local quad = love.graphics.newQuad(
            col * config.tilewidth, row * config.tileheight,
            config.tilewidth, config.tileheight,
            config.imagewidth, config.imageheight
        )

        assert(self.tiles[gid] == nil, "gid already exists: " .. tostring(gid))
        self.tiles[gid] = {
            image = image,
            quad = quad,
            set_config = set_config,
        }
    end
end

function Sets:getTileConfigByGID(gid)
    return self.tiles[gid]
end

-- the module
return setmetatable({new = new},
    {__call = function(_, ...) return new(...) end})
