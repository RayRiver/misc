
local BT = bt

local Common = {}

function Common.createTable()
    return {}
end

Common.Class = BT.import(".class")

Common.RunningStatus = {
    Executing = "Executing",
    Finish = "Finish",
    Terminal = "Terminal",
}

return Common
