
local lib = {}

-- override assert
assert = assert

lib.debug = function(...)
    print(...)
end
lib.debugFormat = function(fmt, ...)
    lib.debug(string.format(fmt, ...))
end

lib.inspect = import(".inspect")
lib.Class = import(".middleclass")
lib.Bump = import(".bump")
lib.BumpDebug = import(".bump_debug")
lib.Cron = import(".cron")
lib.Gamera = import(".gamera")
lib.ShakyCam = import(".shakycam")

return lib
