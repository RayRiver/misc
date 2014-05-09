local TestClass = class("ArmatureTestBase", require("src.TestBase"))

function TestClass:asyncLoad(callback)
    local mgr = ccs.ArmatureDataManager:getInstance()
    mgr:addArmatureFileInfoAsync("res/armature/Cowboy.ExportJson", callback or function() end)
end

return TestClass