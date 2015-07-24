
local lib = require("lib.init")
local Entity = import(".entity")
local utils = require("utils.init")

local ObjectClass = lib.Class("Monster", Entity)

function ObjectClass:initialize(...)
    Entity.initialize(self, ...)
end

function ObjectClass:attack(target)
    if self.m_attack_cool_down then
        return
    end

    print("attack")

    self.m_attack_cool_down = true
    utils.CronMgr:after(2, function()
        self.m_attack_cool_down = false
    end)
end

return ObjectClass
