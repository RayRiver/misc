logic = logic or {}

logic.login = function(username, password)
    local p = Packet()
    p:addId(0xA007)
    p:addInt32(19245)
    p:addString(username)
    p:addString("dc483e80a7a0bd9ef71d8cf973673924")
    p:addInt32(0)
    p:addString("")
    p:addString("")
    p:addString("")
    p:addInt32(1)
    p:addString("")
    p:addString(username)
    p:addString("")
    p:addInt32(0)
    p:addString("")
    p:addString("")
    p:addString("")
    p:send()
end

return logic
