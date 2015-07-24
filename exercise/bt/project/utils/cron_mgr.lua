
local lib = require("lib.init")

local ObjectClass = {
    m_cron_table = {},
}

function ObjectClass:every(time, callback, ...)
    local clock = lib.Cron.every(time, callback, ...)
    self.m_cron_table[clock] = true
    return clock
end

function ObjectClass:after(time, callback, ...)
    local clock = lib.Cron.after(time, callback, ...)
    self.m_cron_table[clock] = true
    return clock
end

function ObjectClass:remove(clock)
    self.m_cron_table[clock] = nil
end

function ObjectClass:update(dt)
    for clock, _ in pairs(self.m_cron_table) do
        local is_expired = clock:update(dt)
        if is_expired then
            self.m_cron_table[clock] = nil
        end
    end
end

return ObjectClass
