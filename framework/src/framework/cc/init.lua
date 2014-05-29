
-- init base classes
cc.Registry   = import(".Registry")
cc.GameObject = import(".GameObject")

-- init components
local components = {
    "components.behavior.StateMachine",
    "components.behavior.EventProtocol",
    "components.ui.BasicLayoutProtocol",
    "components.ui.LayoutProtocol",
}
for _, packageName in ipairs(components) do
    cc.Registry.add(import("." .. packageName), packageName)
end

-- gameobject extend
local GameObject = cc.GameObject
local ccmt = {}
ccmt.__call = function(self, target)
    if target then
        return GameObject.extend(target)
    end
    printError("cc() - invalid target")
end
setmetatable(cc, ccmt)


-- load more library
cc.ui = import(".ui.init")

-- load extensions
