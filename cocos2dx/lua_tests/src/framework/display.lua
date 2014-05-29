local display = {}

local DIRECTOR = cc.Director:getInstance()
local sharedSpriteFrameCache = cc.SpriteFrameCache:getInstance()
--local sharedTextureCache = cc.TextureCache.new()

display.TEXTURES_PIXEL_FORMAT = {}

local glView = DIRECTOR:getOpenGLView()
local size = glView:getFrameSize()
display.sizeInPixels = { width = size.width, height = size.height }
local w = display.sizeInPixels.width
local h = display.sizeInPixels.height

if CONFIG_SCREEN_WIDTH == nil or CONFIG_SCREEN_HEIGHT == nil then
    CONFIG_SCREEN_WIDTH = w
    CONFIG_SCREEN_HEIGHT = h
end

local function checkScale(w, h)
    local scale = 1
    local wscale, hscale = w/CONFIG_SCREEN_WIDTH, h/CONFIG_SCREEN_HEIGHT
    if CONFIG_SCREEN_AUTOSCALE == "FIXED_WIDTH" then
        scale = wscale
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT" then
        scale = hscale
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_WIDTH_PRIOR" then
        if wscale > hscale then
            scale = wscale
        else
            scale = hscale
        end
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT_PRIOR" then
        if wscale < hscale then
            scale = wscale
        else
            scale = hscale
        end
    end
    return scale, wscale, hscale
end

local scale, wscale, hscale = 1, 1, 1
if type(CONFIG_SCREEN_AUTOSCALE) == "function" then
    CONFIG_SCREEN_AUTOSCALE(w, h)
    glview:setDesignResolutionSize(CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT, cc.ResolutionPolicy.NO_BORDER)
elseif CONFIG_SCREEN_AUTOSCALE then
    CONFIG_SCREEN_AUTOSCALE = string.upper(CONFIG_SCREEN_AUTOSCALE)
    scale, wscale, hscale = checkScale(w, h)
    
    if CONFIG_SCREEN_AUTOSCALE == "FIXED_WIDTH" then
        CONFIG_SCREEN_HEIGHT = h / scale
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_WIDTH_PRIOR" then
        if wscale > hscale then
            CONFIG_SCREEN_HEIGHT = h / scale
        else
            CONFIG_SCREEN_WIDTH = w / scale
        end
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT" then
        CONFIG_SCREEN_WIDTH = w / scale
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT_PRIOR" then
        if wscale < hscale then
            CONFIG_SCREEN_HEIGHT = h / scale
        else
            CONFIG_SCREEN_WIDTH = w / scale
        end
    else
        echoError(string.format("display - invalid CONFIG_SCREEN_AUTOSCALE \"%s\"", CONFIG_SCREEN_AUTOSCALE))
    end
    
    glView:setDesignResolutionSize(CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT, cc.ResolutionPolicy.NO_BORDER)
end


local winSize = DIRECTOR:getWinSize()
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

echoInfo(string.format("# CONFIG_SCREEN_AUTOSCALE      = %s", CONFIG_SCREEN_AUTOSCALE))
echoInfo(string.format("# CONFIG_SCREEN_WIDTH          = %0.2f", CONFIG_SCREEN_WIDTH))
echoInfo(string.format("# CONFIG_SCREEN_HEIGHT         = %0.2f", CONFIG_SCREEN_HEIGHT))
echoInfo(string.format("# display.widthInPixels        = %0.2f", display.widthInPixels))
echoInfo(string.format("# display.heightInPixels       = %0.2f", display.heightInPixels))
echoInfo(string.format("# display.contentScaleFactor   = %0.2f", display.contentScaleFactor))
echoInfo(string.format("# display.width                = %0.2f", display.width))
echoInfo(string.format("# display.height               = %0.2f", display.height))
echoInfo(string.format("# display.cx                   = %0.2f", display.cx))
echoInfo(string.format("# display.cy                   = %0.2f", display.cy))
echoInfo(string.format("# display.left                 = %0.2f", display.left))
echoInfo(string.format("# display.right                = %0.2f", display.right))
echoInfo(string.format("# display.top                  = %0.2f", display.top))
echoInfo(string.format("# display.bottom               = %0.2f", display.bottom))
echoInfo(string.format("# display.c_left               = %0.2f", display.c_left))
echoInfo(string.format("# display.c_right              = %0.2f", display.c_right))
echoInfo(string.format("# display.c_top                = %0.2f", display.c_top))
echoInfo(string.format("# display.c_bottom             = %0.2f", display.c_bottom))
echoInfo("#")

display.COLOR_WHITE = {r=255, g=255, b=255}
display.COLOR_BLACK = {r=0, g=0, b=0}
display.COLOR_RED   = {r=255, g=0, b=0}
display.COLOR_GREEN = {r=0, g=255, b=0}
display.COLOR_BLUE  = {r=0, g=0, b=255}

display.ANCHOR_CENTER = cc.p(0.5, 0.5)
display.ANCHOR_TOP_LEFT = cc.p(0, 1)
display.ANCHOR_TOP_CENTER = cc.p(0.5, 1)
display.ANCHOR_TOP_RIGHT = cc.p(1, 1)
display.ANCHOR_CENTER_LEFT = cc.p(0, 0.5)
display.ANCHOR_CENTER_RIGHT = cc.p(1, 0.5)
display.ANCHOR_BOTTOM_LEFT = cc.p(0, 0)
display.ANCHOR_BOTTOM_CENTER = cc.p(0.5, 0)
display.ANCHOR_BOTTOM_RIGHT = cc.p(1, 0)

display.SCENE_TRANSITIONS = 
{
    CROSSFADE       = {cc.TransitionCrossFade, 2},
    FADE            = {cc.TransitionFade, 3, cc.c3b(0, 0, 0)},
    FADEBL          = {cc.TransitionFadeBL, 2},
    FADEDOWN        = {cc.TransitionFadeDown, 2},
    FADETR          = {cc.TransitionFadeTR, 2},
    FADEUP          = {cc.TransitionFadeUp, 2},
    FLIPANGULAR     = {cc.TransitionFlipAngular, 3, cc.TRANSITION_ORIENTATION_LEFT_OVER},
    FLIPX           = {cc.TransitionFlipX, 3, cc.TRANSITION_ORIENTATION_LEFT_OVER},
    FLIPY           = {cc.TransitionFlipY, 3, cc.TRANSITION_ORIENTATION_UP_OVER},
    JUMPZOOM        = {cc.TransitionJumpZoom, 2},
    MOVEINB         = {cc.TransitionMoveInB, 2},
    MOVEINL         = {cc.TransitionMoveInL, 2},
    MOVEINR         = {cc.TransitionMoveInR, 2},
    MOVEINT         = {cc.TransitionMoveInT, 2},
    PAGETURN        = {cc.TransitionPageTurn, 3, false},
    ROTOZOOM        = {cc.TransitionRotoZoom, 2},
    SHRINKGROW      = {cc.TransitionShrinkGrow, 2},
    SLIDEINB        = {cc.TransitionSlideInB, 2},
    SLIDEINL        = {cc.TransitionSlideInL, 2},
    SLIDEINR        = {cc.TransitionSlideInR, 2},
    SLIDEINT        = {cc.TransitionSlideInT, 2},
    SPLITCOLS       = {cc.TransitionSplitCols, 2},
    SPLITROWS       = {cc.TransitionSplitRows, 2},
    TURNOFFTILES    = {cc.TransitionTurnOffTiles, 2},
    ZOOMFLIPANGULAR = {cc.TransitionZoomFlipAngular, 2},
    ZOOMFLIPX       = {cc.TransitionZoomFlipX, 3, cc.TRANSITION_ORIENTATION_LEFT_OVER},
    ZOOMFLIPY       = {cc.TransitionZoomFlipY, 3, cc.TRANSITION_ORIENTATION_UP_OVER},
}

function display.setDesignResolutionSize(width, height, resolutionPolicy)
    cc.Director:getInstance():getOpenGLView():setDesignResolutionSize(
        width, height, resolutionPolicy
    )
end

function display.wrapSceneWithTransition(scene, transitionType, time, more)
    local key = string.upper(tostring(transitionType))
    if key == "RANDOM" then
        local keys = table.keys(display.SCENE_TRANSITIONS)
        key = keys[math.random(1, #keys)]
    end
    
    if display.SCENE_TRANSITIONS[key] then
        local cls, count, default = unpack(display.SCENE_TRANSITIONS[key])
        time = time or 0.2
        if count == 3 then
            scene = cls:create(time, scene, more or default)
        else
            scene = cls:create(time, scene)
        end    
    else
        echoError("display.wrapSceneWithTransition() - invalid transitionType %s", tostring(transitionType))
    end
    
    return scene
end

function display.newScene(name)
    local scene = CCSceneExtend.extend(cc.Scene:create())
    scene.name = name or "<unknown-scene>"
    return scene
end

function display.replaceScene(newScene, transitionType, time, more)
    if DIRECTOR:getRunningScene() then
        if transitionType then
            newScene = display.wrapSceneWithTransition(newScene, transitionType, time, more)
        end
        DIRECTOR:replaceScene(newScene)
    else
        DIRECTOR:runWithScene(newScene)
    end
end

function display.getRunningScene()
    return DIRECTOR:getRunningScene()
end

function display.pause()
    DIRECTOR:pause()
end

function display.resume()
    DIRECTOR:resume()
end

function display.newLayer()
    return CCLayerExtend.extend(cc.Layer:create())
end

function display.newColorLayer(color) -- { r=255, g=255, b=255, a=255 }
    return CCLayerExtend.extend(cc.LayerColor:create(color))
end

function display.newNode()
    return CCNodeExtend.extend(cc.Node:create())
end

function display.setTexturePixelFormat(filename, format)
    display.TEXTURES_PIXEL_FORMAT[filename] = format
end

function display.addSpriteFramesWithFile(plistFilename, image)
    if display.TEXTURES_PIXEL_FORMAT[image] then
        cc.Texture2D:setDefaultAlphaPixelFormat(display.TEXTURES_PIXEL_FORMAT[image])
        sharedSpriteFrameCache:addSpriteFramesWithFile(plistFilename, image)
        cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
    else
        sharedSpriteFrameCache:addSpriteFramesWithFile(plistFilename, image)
    end
end

function display.removeSpriteFrameByImageName(imageName)
    cc.SpriteFrameCache:getInstance():removeSpriteFrameByName(imageName)
    --sharedTextureCache:removeTextureForKey(imageName)
end

function display.newBatchNode(image, capacity)
    return CCNodeExtend.extend(cc.SpriteBatchNode:create(image, capacity or 100))
end

function display.newSpriteFrame(frameName)
    local frame = cc.SpriteFrameCache:getInstance():getSpriteFrameByName(frameName)
    if not frame then
        echoError("display.newSpriteFrame() - invalid frameName %s", tostring(frameName))
    end
    return frame
end

function display.newSprite(filename, x, y)
    local t = type(filename)
    if t == "userdata" then t = tolua.type(filename) end

    local sprite
    
    if not filename then
        sprite = cc.Sprite:create()
    elseif t == "string" then
        if string.byte(filename) == 35 then -- first char is #
            local frame = display.newSpriteFrame(string.sub(filename, 2))
            if frame then
                sprite = cc.Sprite:createWithSpriteFrame(frame)
            end
        else
            if display.TEXTURES_PIXEL_FORMAT[filename] then
                -- TODO: TEXTURES_PIXEL_FORMAT do what?
                --[[
                _G.kCCTexture2DPixelFormat_RGBA8888  = cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888
                _G.kCCTexture2DPixelFormat_RGB888    = cc.TEXTURE2_D_PIXEL_FORMAT_RG_B888
                _G.kCCTexture2DPixelFormat_RGB565    = cc.TEXTURE2_D_PIXEL_FORMAT_RG_B565
                _G.kCCTexture2DPixelFormat_A8        = cc.TEXTURE2_D_PIXEL_FORMAT_A8
                _G.kCCTexture2DPixelFormat_I8        = cc.TEXTURE2_D_PIXEL_FORMAT_I8 
                _G.kCCTexture2DPixelFormat_AI88      = cc.TEXTURE2_D_PIXEL_FORMAT_A_I88
                _G.kCCTexture2DPixelFormat_RGBA4444  = cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A4444 
                _G.kCCTexture2DPixelFormat_RGB5A1    = cc.TEXTURE2_D_PIXEL_FORMAT_RGB5_A1 
                _G.kCCTexture2DPixelFormat_PVRTC4    = cc.TEXTURE2_D_PIXEL_FORMAT_PVRTC4
                _G.kCCTexture2DPixelFormat_PVRTC2    = cc.TEXTURE2_D_PIXEL_FORMAT_PVRTC2
                _G.kCCTexture2DPixelFormat_Default   = cc.TEXTURE2_D_PIXEL_FORMAT_DEFAULT
                --]]
                cc.Texture2D:setDefaultAlphaPixelFormat(display.TEXTURES_PIXEL_FORMAT[filename])
                sprite = cc.Sprite:create(filename)
                cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
            else
                sprite = cc.Sprite:create(filename)
            end
        end
    elseif t == "cc.SpriteFrame" then
        sprite = cc.Sprite:createWithSpriteFrame(filename)
    else
        echoError("display.newSprite() - invalid filename value type")
        sprite = cc.Sprite:create()
    end
   
    if sprite then
        CCSpriteExtend.extend(sprite)
        if x and y then sprite:setPosition(x, y) end
    else
        echoError("display.newSprite() - create sprite failure, filename %s", tostring(filename))
        sprite = cc.Sprite:create()
    end
    
    return sprite     
end

function display.newFrames(pattern, begin, count, isReversed)
    local frames = {}
    local step = 1
    local last = begin + count - 1
    if isReversed then
        last, begin = begin, last
        step = -1
    end
    
    for index = begin, last, step do
        local frameName = string.format(pattern, index)
        local frame = sharedSpriteFrameCache:spriteFrameByName(frameName)
        if not frame then
            echoError("display.newFrames() - invalid frame, name %s", tostring(frameName))
            return
        end
        frames[#frames+1] = frame
    end
    
    return frames
end

function display.newAnimation(frames, time)
    time = time or (1.0/#frames)
    return cc.Animation:createWithSpriteFrames(frames, time)
end

return display

