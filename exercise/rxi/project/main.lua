-- debug
if arg and arg[#arg] == "-debug" then require("mobdebug").start() end

--require("tango_server")

--package.path = package.path .. ";script/?.lua"
require("app")
