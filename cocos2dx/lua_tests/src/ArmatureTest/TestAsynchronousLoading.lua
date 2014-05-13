local TestClass = class("TestAsynchronousLoading", require("src.ArmatureTest.ArmatureTestBase"))

function TestClass:onEnter()
    self:setDesc("0%")
    
    local function onAsyncLoadUpdate(percent)
        self:setDesc(string.format("%d", percent*100) .. "%")
    end

    local function onAsyncLoaded()
        self:setDesc("100% done")
    end
    
    -- 异步加载资源
    self:asyncLoad(onAsyncLoaded, onAsyncLoadUpdate)        
end

return TestClass
