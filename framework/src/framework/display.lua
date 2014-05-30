
local display = {}

local sharedDirector = cc.Director:getInstance()

local glview = sharedDirector:getOpenGLView()
local size = glview:getFrameSize()
display.sizeInPixels = { width = size.width, height = size.height }
local w = display.sizeInPixels.width
local h = display.sizeInPixels.height

if CONFIG_SCREEN_WIDTH == nil or CONFIG_SCREEN_HEIGHT == nil then
    CONFIG_SCREEN_WIDTH = w
    CONFIG_SCREEN_HEIGHT = h
end

if not CONFIG_SCREEN_AUTOSCALE then
    if w > h then
        CONFIG_SCREEN_AUTOSCALE = "FIXED_HEIGHT"
    else
        CONFIG_SCREEN_AUTOSCALE = "FIXED_WIDTH"
    end
else
    CONFIG_SCREEN_AUTOSCALE = string.upper(CONFIG_SCREEN_AUTOSCALE)
end

local scale, scaleX, scaleY

if CONFIG_SCREEN_AUTOSCALE then
    if type(CONFIG_SCREEN_AUTOSCALE_CALLBACK) == "function" then
        scaleX, scaleY = CONFIG_SCREEN_AUTOSCALE_CALLBACK(w, h, device.model)
    end

    if not scaleX or not scaleY then
        scaleX, scaleY = w / CONFIG_SCREEN_WIDTH, h / CONFIG_SCREEN_HEIGHT
    end

    if CONFIG_SCREEN_AUTOSCALE == "FIXED_WIDTH" then
        scale = scaleX
        CONFIG_SCREEN_HEIGHT = h / scale
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT" then
        scale = scaleY
        CONFIG_SCREEN_WIDTH = w / scale
    else
        scale = 1.0
        printError(string.format("display - invalid CONFIG_SCREEN_AUTOSCALE \"%s\"", CONFIG_SCREEN_AUTOSCALE))
    end

    glview:setDesignResolutionSize(CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT, cc.ResolutionPolicy.NO_BORDER)
end

local winSize = sharedDirector:getWinSize()
display.contentScaleFactor = scale
display.size               = {width = winSize.width, height = winSize.height}
display.width              = display.size.width
display.height             = display.size.height
display.cx                 = display.width / 2
display.cy                 = display.height / 2
display.c_left             = -display.width / 2
display.c_right            = display.width / 2
display.c_top              = display.height / 2
display.c_bottom           = -display.height / 2
display.left               = 0
display.right              = display.width
display.top                = display.height
display.bottom             = 0
display.widthInPixels      = display.sizeInPixels.width
display.heightInPixels     = display.sizeInPixels.height

printInfo(string.format("# CONFIG_SCREEN_AUTOSCALE      = %s", CONFIG_SCREEN_AUTOSCALE))
printInfo(string.format("# CONFIG_SCREEN_WIDTH          = %0.2f", CONFIG_SCREEN_WIDTH))
printInfo(string.format("# CONFIG_SCREEN_HEIGHT         = %0.2f", CONFIG_SCREEN_HEIGHT))
printInfo(string.format("# display.widthInPixels        = %0.2f", display.widthInPixels))
printInfo(string.format("# display.heightInPixels       = %0.2f", display.heightInPixels))
printInfo(string.format("# display.contentScaleFactor   = %0.2f", display.contentScaleFactor))
printInfo(string.format("# display.width                = %0.2f", display.width))
printInfo(string.format("# display.height               = %0.2f", display.height))
printInfo(string.format("# display.cx                   = %0.2f", display.cx))
printInfo(string.format("# display.cy                   = %0.2f", display.cy))
printInfo(string.format("# display.left                 = %0.2f", display.left))
printInfo(string.format("# display.right                = %0.2f", display.right))
printInfo(string.format("# display.top                  = %0.2f", display.top))
printInfo(string.format("# display.bottom               = %0.2f", display.bottom))
printInfo(string.format("# display.c_left               = %0.2f", display.c_left))
printInfo(string.format("# display.c_right              = %0.2f", display.c_right))
printInfo(string.format("# display.c_top                = %0.2f", display.c_top))
printInfo(string.format("# display.c_bottom             = %0.2f", display.c_bottom))
printInfo("#")

display.COLOR_WHITE = {r=255, g=255, b=255}
display.COLOR_BLACK = {r=0, g=0, b=0}
display.COLOR_RED   = {r=255, g=0, b=0}
display.COLOR_GREEN = {r=0, g=255, b=0}
display.COLOR_BLUE  = {r=0, g=0, b=255}

display.AUTO_SIZE      = 0
display.FIXED_SIZE     = 1
display.LEFT_TO_RIGHT  = 0
display.RIGHT_TO_LEFT  = 1
display.TOP_TO_BOTTOM  = 2
display.BOTTOM_TO_TOP  = 3

display.CENTER        = 1
display.LEFT_TOP      = 2; display.TOP_LEFT      = 2
display.CENTER_TOP    = 3; display.TOP_CENTER    = 3
display.RIGHT_TOP     = 4; display.TOP_RIGHT     = 4
display.CENTER_LEFT   = 5; display.LEFT_CENTER   = 5
display.CENTER_RIGHT  = 6; display.RIGHT_CENTER  = 6
display.BOTTOM_LEFT   = 7; display.LEFT_BOTTOM   = 7
display.BOTTOM_RIGHT  = 8; display.RIGHT_BOTTOM  = 8
display.BOTTOM_CENTER = 9; display.CENTER_BOTTOM = 9

display.ANCHOR_POINTS = {
    cc.p(0.5, 0.5),  -- CENTER
    cc.p(0, 1),      -- TOP_LEFT
    cc.p(0.5, 1),    -- TOP_CENTER
    cc.p(1, 1),      -- TOP_RIGHT
    cc.p(0, 0.5),    -- CENTER_LEFT
    cc.p(1, 0.5),    -- CENTER_RIGHT
    cc.p(0, 0),      -- BOTTOM_LEFT
    cc.p(1, 0),      -- BOTTOM_RIGHT
    cc.p(0.5, 0),    -- BOTTOM_CENTER
}

-- add for short codes
display.ANCHOR_CENTER = display.ANCHOR_POINTS[display.CENTER]
display.ANCHOR_TOP_LEFT = display.ANCHOR_POINTS[display.TOP_LEFT]
display.ANCHOR_TOP_CENTER = display.ANCHOR_POINTS[display.TOP_CENTER]
display.ANCHOR_TOP_RIGHT = display.ANCHOR_POINTS[display.TOP_RIGHT]
display.ANCHOR_CENTER_LEFT = display.ANCHOR_POINTS[display.CENTER_LEFT]
display.ANCHOR_CENTER_RIGHT = display.ANCHOR_POINTS[display.CENTER_RIGHT]
display.ANCHOR_BOTTOM_LEFT = display.ANCHOR_POINTS[display.BOTTOM_LEFT]
display.ANCHOR_BOTTOM_RIGHT = display.ANCHOR_POINTS[display.BOTTOM_RIGHT]
display.ANCHOR_BOTTOM_CENTER = display.ANCHOR_POINTS[display.BOTTOM_CENTER]

function display.newNode()
    return cc.NodeEx.extend(cc.Node:create())
end

--[[--

创建一个新场景，并返回 CCScene 场景对象。

指定场景名称方便调试。

@param string 场景名称

@return CCScene 场景对象

@see CCScene

]]
function display.newScene(name)
    local scene = cc.SceneEx.extend(cc.Scene:create())
    scene.name = name or "<unknown-scene>"
    return scene
end

--[[--

切换到新场景

~~~ lua

-- 使用红色做过渡色
display.replaceScene(nextScene, "fade", 0.5, ccc3(255, 0, 0))

~~~

@param CCScene newScene 场景对象
@param string transitionType 过渡效果名
@param number time 过渡时间
@param mixed more 过渡效果附加参数

]]
function display.replaceScene(newScene)
    if sharedDirector:getRunningScene() then
        sharedDirector:replaceScene(newScene)
    else
        sharedDirector:runWithScene(newScene)
    end
end

function display.newLayer()
    return cc.LayerEx.extend(cc.Layer:create())
end

function display.newColorLayer(color)
    return cc.LayerEx.extend(cc.LayerColor:create(color or cc.c4b(0,0,0,255)))
end

function display.newDrawNode()
    return cc.DrawNodeEx.extend(cc.DrawNode:create())
end

function display.newPolygon(points, fillColor_4b, borderWidth, borderColor_4b)
    local node = display.newDrawNode()
    
    local fillColor_4f
    if not fillColor_4b then
        fillColor_4f = cc.c4f(1,1,1,1)
    else
        fillColor_4f = cc.c4f(
            fillColor_4b.r/255,
            fillColor_4b.g/255,
            fillColor_4b.b/255,
            fillColor_4b.a/255
        )
    end
    
    local borderColor_4f
    if not borderColor_4b then
        borderColor_4f = fillColor_4f
    else
        borderColor_4f = cc.c4f(
            borderColor_4b.r/255,
            borderColor_4b.g/255,
            borderColor_4b.b/255,
            borderColor_4b.a/255
        )
    end
    
    node:drawPolygon(
        points, #points,
        fillColor_4f,
        borderWidth or 0,
        borderColor_4f
    )
    return node
end

function display.newTriangle(point1, point2, point3, fillColor_4b)
    local node = display.newDrawNode()
    
    local fillColor_4f
    if not fillColor_4b then
        fillColor_4f = cc.c4f(1,1,1,1)
    else
        fillColor_4f = cc.c4f(
            fillColor_4b.r/255,
            fillColor_4b.g/255,
            fillColor_4b.b/255,
            fillColor_4b.a/255
        )
    end
    
    node:drawTriangle(point1, point2, point3, fillColor_4f)
    return node
end

function display.newSegment(point1, point2, radius, color_4b)
    local node = display.newDrawNode()

    local color_4f
    if not color_4b then
        color_4f = cc.c4f(1,1,1,1)
    else
        color_4f = cc.c4f(
            color_4b.r/255,
            color_4b.g/255,
            color_4b.b/255,
            color_4b.a/255
        )
    end
    
    node:drawSegment(point1, point2, radius or 1, color_4f)
    return node
end

--[[--

将指定的显示对象按照特定锚点对齐。

格式：

display.align(显示对象, 锚点位置, [x, y])

显示对象锚点位置：

-   display.CENTER 图像中央
-   display.LEFT_TOP,
-   display.TOP_LEFT 图像左上角
-   display.CENTER_TOP,
-   display.TOP_CENTER 图像顶部的中间
-   display.RIGHT_TOP,
-   display.TOP_RIGHT 图像顶部的中间
-   display.CENTER_LEFT,
-   display.LEFT_CENTER 图像左边的中间
-   display.CENTER_RIGHT,
-   display.RIGHT_CENTER 图像右边的中间
-   display.BOTTOM_LEFT,
-   display.LEFT_BOTTOM 图像左边的底部
-   display.BOTTOM_RIGHT,
-   display.RIGHT_BOTTOM 图像右边的底部
-   display.BOTTOM_CENTER,
-   display.CENTER_BOTTOM 图像中间的底部

~~~ lua

-- 将图像按左上角对齐，并放置在屏幕左上角
display.align(sprite, display.LEFT_TOP, 0, 0)

~~~

@param CCSprite target 显示对象
@param integer anchorPoint 锚点位置
@param integer x
@param integer y

]]
function display.align(target, anchorPoint, x, y)
    target:setAnchorPoint(display.ANCHOR_POINTS[anchorPoint])
    if x and y then target:setPosition(x, y) end
end

return display


