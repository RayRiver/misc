
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

return Utils

