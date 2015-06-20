
local Utils = require("utils")
local Player = require("entities.player")
local Block = require("entities.block")
local Guardian = require("entities.guardian")

local sortByUpdateOrder = function(a,b)
    if a:getClassUpdateOrder() < b:getClassUpdateOrder() then
        return true
    else
        if a:getUpdateOrder() < b:getUpdateOrder() then
            return true
        end
    end

    return false
end

local Map = Utils.Class("Map")

function Map:initialize(width, height, camera)
    self.width = width
    self.height = height
    self.camera = camera

    self:reset()
end

function Map:reset()
    local width, height = self.width, self.height

    self.world = Utils.Bump.newWorld()
    self.player = Player:new(self, self.world, { x=60, y=60 })

    -- edges
    Block:new(self.world, { x=0, y=0, w=width, h=32 })
    Block:new(self.world, { x=0, y=32, w=32, h=height-64 })
    Block:new(self.world, { x=width-32, y=32, w=32, h=height-64 })

    -- tiled floor
    local tilesOnFloor = 40
    for i=0,tilesOnFloor - 1 do
        Block:new(self.world, { x=i*width/tilesOnFloor, y=height-32, w=width/tilesOnFloor, h=32 })
    end

    -- blocks
    local x, y, w, h
    for i = 1, 60 do
        w = math.random(100, 400)
        h = math.random(100, 400)
        x = math.random(100, width - w - 100)
        y = math.random(100, height - h - 100)
        local area = w * h

        for i=1, math.floor(area/7000) do
            Block:new(self.world, {
                x = math.random(x, x+w),
                y = math.random(y, y+h),
                w = math.random(32, 128),
                h = math.random(32, 128),
            })
        end

        --Block:new(self.world, {x=x, y=y, w=w, h=h})
    end

    -- guardians
    for i = 1, 10 do
        Guardian:new(self.world, {
            x = math.random(100, width - 100),
            y = math.random(100, height - 100),
            target = self.player,
        })
    end
end

function Map:update(dt, x, y, w, h)
    local x, y, w, h = x or 0, y or 0, w or self.width, h or self.height
    local visibleThings, len = self.world:queryRect(x, y, w, h)

    table.sort(visibleThings, sortByUpdateOrder)

    for i = 1, len do
        visibleThings[i]:update(dt)
    end
end

function Map:draw(drawDebug, x, y, w, h)
    if drawDebug then
        Utils.BumpDebug.draw(self.world, x, y, w, h)
    end

    local visibleThings, len = self.world:queryRect(x, y, w, h)

    table.sort(visibleThings, sortByUpdateOrder)

    for i = 1, len do
        visibleThings[i]:draw(drawDebug)
    end
end

return Map
