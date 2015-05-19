-- debug
if arg and arg[#arg] == "-debug" then require("mobdebug").start() end

package.path = package.path .. ";script/?.lua"
require("App")
