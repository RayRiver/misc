local display = {}

local visibleRect = cc.Director:getInstance():getOpenGLView():getVisibleRect()
display.width = visibleRect.width
display.height = visibleRect.height
display.left = visibleRect.x
display.right = visibleRect.x + visibleRect.width
display.top = visibleRect.y + visibleRect.height
display.bottom = visibleRect.y
display.cx = visibleRect.x + visibleRect.width/2
display.cy = visibleRect.y + visibleRect.height/2

return display
