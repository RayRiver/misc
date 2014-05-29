

-- ResolutionPolicy
cc.ResolutionPolicy = {}
cc.ResolutionPolicy.EXACT_FIT = 0
cc.ResolutionPolicy.NO_BORDER = 1
cc.ResolutionPolicy.SHOW_ALL = 2
cc.ResolutionPolicy.FIXED_HEIGHT = 3
cc.ResolutionPolicy.FIXED_WIDTH = 4
cc.ResolutionPolicy.UNKNOWN = 5

-- custom event
local EVENT_CUSTOM_BEGAN = 10000
cc.Handler = cc.Handler or {}
cc.Handler.EVENT_USEREXT_CUSTOM = cc.Handler.EVENT_USEREXT_CUSTOM or {}
cc.Handler.EVENT_USEREXT_CUSTOM.onNetConnected = EVENT_CUSTOM_BEGAN+1
cc.Handler.EVENT_USEREXT_CUSTOM.onNetDisconnect = EVENT_CUSTOM_BEGAN+2
cc.Handler.EVENT_USEREXT_CUSTOM.onNetReceive = EVENT_CUSTOM_BEGAN+3

cc.distance = function(p1, p2)
    return math.sqrt( (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) )
end

cc.distance2 = function(p1, p2)
    return ( (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) )
end

-- extend from cocos2dx class
require(cc.PACKAGE_NAME .. ".cocos2dx.CCNodeExtend")
require(cc.PACKAGE_NAME .. ".cocos2dx.CCSceneExtend")
require(cc.PACKAGE_NAME .. ".cocos2dx.CCLayerExtend")
require(cc.PACKAGE_NAME .. ".cocos2dx.CCSpriteExtend")

