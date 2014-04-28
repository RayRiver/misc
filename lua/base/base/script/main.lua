log = function(...)
    print(string.format(...))
end

function __G__TRACKBACK__(msg)
    log("----------------------------------------")
    log("LUA ERROR: " .. tostring(msg) .. "\n")
    log(debug.traceback())
    log("----------------------------------------")
end

function test_varlist()
	local args = VarList()
	args:addInt8(123)
	args:addInt16(122)
	args:addInt32(121)
	args:addInt64(120)
	args:addFloat(119.0)
	args:addDouble(118)
	args:addString("abcd")
	args:addFloat(117)

	print(args:toInt32(0))
	print(args:toInt32(1))
	print(args:toInt32(2))
	print(args:toInt32(3))
	print(args:toInt32(4))
	print(args:toInt32(5))
	print(args:toString(6))
	print(args:toFloat(7))
end

function test_net()
	net.connect("127.0.0.1", 60000)
	--sys.sleep(3000)
	--net.disconnect()
end

function test_event()
    event.register("testevent1", function(a, b) print("hey you! " .. tostring(a) .. "," .. tostring(b)); return a+b end)
    local ret = event.call("testevent1", 1, 2)
    print("ret = " .. tostring(ret))
    event.unregister("testevent1")

end

function main()
    package.path = package.path .. ";./script/?.lua"

    require("classlib")
    require("network")
    require("nethandler")

    network.init()
    nethandler.init()

    net.connect("192.168.6.227", 9090)
end

xpcall(main, __G__TRACKBACK__)
