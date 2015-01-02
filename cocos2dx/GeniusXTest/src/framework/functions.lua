

--------------------------------
-- 用指定字符或字符串分割输入字符串，返回包含分割结果的数组
-- @function [parent=#string] split
-- @param string input 输入字符串
-- @param string delimiter 分割标记字符或字符串
-- @return array#array  包含分割结果的数组

--[[--

用指定字符或字符串分割输入字符串，返回包含分割结果的数组

~~~ lua

local input = "Hello,World"
local res = string.split(input, ",")
-- res = {"Hello", "World"}

local input = "Hello-+-World-+-Quick"
local res = string.split(input, "-+-")
-- res = {"Hello", "World", "Quick"}

~~~

]]

-- end --

function string.split(input, delimiter)
    input = tostring(input)
    delimiter = tostring(delimiter)
    if (delimiter=='') then return false end
    local pos,arr = 0, {}
    -- for each divider found
    for st,sp in function() return string.find(input, delimiter, pos, true) end do
        table.insert(arr, string.sub(input, pos, st - 1))
        pos = sp + 1
    end
    table.insert(arr, string.sub(input, pos))
    return arr
end

--[[--

载入一个模块

import() 与 require() 功能相同，但具有一定程度的自动化特性。

假设我们有如下的目录结构：

~~~

app/
app/classes/
app/classes/MyClass.lua
app/classes/MyClassBase.lua
app/classes/data/Data1.lua
app/classes/data/Data2.lua

~~~

MyClass 中需要载入 MyClassBase 和 MyClassData。如果用 require()，MyClass 内的代码如下：

~~~ lua

local MyClassBase = require("app.classes.MyClassBase")
local MyClass = class("MyClass", MyClassBase)

local Data1 = require("app.classes.data.Data1")
local Data2 = require("app.classes.data.Data2")

~~~

假如我们将 MyClass 及其相关文件换一个目录存放，那么就必须修改 MyClass 中的 require() 命令，否则将找不到模块文件。

而使用 import()，我们只需要如下写：

~~~ lua

local MyClassBase = import(".MyClassBase")
local MyClass = class("MyClass", MyClassBase)

local Data1 = import(".data.Data1")
local Data2 = import(".data.Data2")

~~~

当在模块名前面有一个"." 时，import() 会从当前模块所在目录中查找其他模块。因此 MyClass 及其相关文件不管存放到什么目录里，我们都不再需要修改 MyClass 中的 import() 命令。这在开发一些重复使用的功能组件时，会非常方便。

我们可以在模块名前添加多个"." ，这样 import() 会从更上层的目录开始查找模块。

~

不过 import() 只有在模块级别调用（也就是没有将 import() 写在任何函数中）时，才能够自动得到当前模块名。如果需要在函数中调用 import()，那么就需要指定当前模块名：

~~~ lua

# MyClass.lua

# 这里的 ... 是隐藏参数，包含了当前模块的名字，所以最好将这行代码写在模块的第一行
local CURRENT_MODULE_NAME = ...

local function testLoad()
local MyClassBase = import(".MyClassBase", CURRENT_MODULE_NAME)
# 更多代码
end

~~~

@param string moduleName 要载入的模块的名字
@param [string currentModuleName] 当前模块名

@return module

]]
function import(moduleName, currentModuleName)
    local currentModuleNameParts
    local moduleFullName = moduleName
    local offset = 1

    while true do
        if string.byte(moduleName, offset) ~= 46 then -- .
            moduleFullName = string.sub(moduleName, offset)
            if currentModuleNameParts and #currentModuleNameParts > 0 then
                moduleFullName = table.concat(currentModuleNameParts, ".") .. "." .. moduleFullName
            end
            break
        end
        offset = offset + 1

        if not currentModuleNameParts then
            if not currentModuleName then
                local n,v = debug.getlocal(3, 1)
                currentModuleName = v
            end

            currentModuleNameParts = string.split(currentModuleName, ".")
        end
        table.remove(currentModuleNameParts, #currentModuleNameParts)
    end

    return require(moduleFullName)
end

--[[--

将 Lua 对象及其方法包装为一个匿名函数

在 quick-cocos2d-x 中，许多功能需要传入一个 Lua 函数做参数，然后在特定事件发生时就会调用传入的函数。例如触摸事件、帧事件等等。

~~~ lua

local MyScene = class("MyScene", function()
return display.newScene("MyScene")
end)

function MyScene:ctor()
self.frameTimeCount = 0
-- 注册帧事件
self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, self.onEnterFrame)
self:scheduleUpdate()
end

function MyScene:onEnterFrame(dt)
self.frameTimeCount = self.frameTimeCount + dt
end

~~~

上述代码执行时将出错，报告"Invalid self" ，这就是因为 C++ 无法识别 Lua 对象方法。因此在调用我们传入的 self.onEnterFrame 方法时没有提供正确的参数。

要让上述的代码正常工作，就需要使用 handler() 进行一下包装：

~~~ lua

function MyScene:ctor()
self.frameTimeCount = 0
-- 注册帧事件
self:addNodeEventListener(cc.ENTER_FRAME_EVENT, handler(self, self.onEnterFrame))
self:scheduleUpdate()
end

~~~

实际上，除了 C++ 回调 Lua 函数之外，在其他所有需要回调的地方都可以使用 handler()。

@param mixed obj Lua 对象
@param function method 对象方法

@return function

]]
function handler(obj, method)
    return function(...)
        return method(obj, ...)
    end
end
