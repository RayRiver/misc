
local Utils = {}

Utils.Class = require('lib.middleclass')
Utils.Camera = require('lib.camera')
Utils.Timer = require('lib.timer')
Utils.Vector = require('lib.vector')
Utils.Tiled = require('lib.tiled')

Utils.handler = function(obj, method, ...)
    return function(...)
        return method(obj, ...)
    end
end

Utils.rectIntersect = function(a, b)
    if a.x + a.w < b.x or b.x + b.w < a.x or a.y + a.h < b.y or b.y + b.h < a.y then
        return false
    else
        return true
    end
end

return Utils

