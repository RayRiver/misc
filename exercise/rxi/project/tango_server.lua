
local Utils = require("utils")

require("tango.server.copas_socket")

greet = function(...)
    print(...)
end

Utils.print("tango:", tango)

tango_sock, tango_request_loop = tango.server.copas_socket.loop{
    port = 12345,
}
