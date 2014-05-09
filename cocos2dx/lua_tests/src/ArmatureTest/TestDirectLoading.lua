local TestClass = class("TestDirectLoading", require("src.TestBase"))

function TestClass:onEnter()
    self:setDesc("")

    local mgr = ccs.ArmatureDataManager:getInstance()
    mgr:addArmatureFileInfo("res/armature/bear.ExportJson")
    
    local armature = ccs.Armature:create("bear");
    armature:getAnimation():playWithIndex(0)
    armature:setAnchorPoint(0.5, 0.5)
    armature:setPosition(display.cx, display.cy)
    self:addChild(armature)
end

return TestClass