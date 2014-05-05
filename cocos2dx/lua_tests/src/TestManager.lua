local TestManager = class("TestManager")

function TestManager:ctor(testName)
    self.testName = tostring(testName)
    self.tests = {}
    self.index = 0
end

function TestManager:add(subTestName)
    table.insert(self.tests, subTestName)
end

function TestManager:next()
    if #self.tests > 0 then
        if self.index == 0 then
            self.index = 1
        else
            self.index = self.index + 1
            if self.index > #self.tests then
                self.index = 1
            end
        end
        self:run()
    end
end

function TestManager:prev()
    if #self.tests > 0 then
        if self.index == 0 then
            self.index = #self.tests
        else
            self.index = self.index - 1
            if self.index <= 0 then
                self.index = #self.tests
            end
        end
        self:run()
    end
end

function TestManager:run()
    if #self.tests <= 0 then
        return
    end
    if self.index == 0 then
        self.index = 1
    end

    local subTestName = self.tests[self.index]
    local testImpName = "src." .. tostring(self.testName) .. "." .. tostring(subTestName)
    local test = nil
    if testImpName then
        local testClass = require(testImpName)
        test = testClass.new()
    end

    if test then
        test:setTitle(self.testName)
        test:setSubTitle(subTestName)  
        test:setNextCallback(self, self.next)
        test:setPrevCallback(self, self.prev)
        test:setRestartCallback(self, self.run)
        test:init()

        test:run()
    end
end

function runTest(testName)
    local list = require("src." .. tostring(testName) .. ".list")
    local testManager = TestManager.new(testName)
    for _, s in pairs(list) do
        testManager:add(s)
    end
    testManager:run()
end

