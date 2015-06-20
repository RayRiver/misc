
local Utils = {}

Utils.Class = require('lib.middleclass')
Utils.Camera = require('lib.camera')
Utils.Timer = require('lib.timer')
Utils.Vector = require('lib.vector')
Utils.Tiled = require('lib.tiled')

Utils.Bump = require("lib.bump")
Utils.BumpDebug = require("lib.bump_debug")
Utils.Gamera = require("lib.gamera")
Utils.ShakyCam = require("lib.shakycam")
Utils.Stateful = require("lib.stateful")

Utils.handler = function(obj, method, ...)
    return function(...)
        return method(obj, ...)
    end
end

Utils.sign = function(x)
    return x > 0 and 1 or -1
end

Utils.rectIntersect = function(a, b)
    if a.x + a.w < b.x or b.x + b.w < a.x or a.y + a.h < b.y or b.y + b.h < a.y then
        return false
    else
        return true
    end
end

function Utils.print(info, ...)
    local args = {...}
    local lookup_table = {}

    local function _make_spaces(level)
        local content = {}
        for i = 1, level do
            table.insert(content, "    ")
        end
        return table.concat(content)
    end

    local function _val2str(val, level)
        level = level or 0
        if type(val) == "string" then
            return "\"" .. tostring(val) .. "\""
        elseif type(val) ~= "table" then
            return tostring(val)
        elseif lookup_table[val] then
            return tostring(val)
        else
            lookup_table[val] = true
            local content = {}
            table.insert(content, tostring(val) .. ": \n" .. _make_spaces(level) .. "{\n")
            table.insert(content, _make_spaces(level+1) .. "metatable: " .. _val2str(getmetatable(val), level+1) .. "\n")

            local key_table = {}
            for k, v in pairs(val) do
                table.insert(key_table, k)
            end
            table.sort(key_table, function(a, b)
                local function _getPri(value_type)
                    local pri
                    if value_type == "number" then pri = 1
                    elseif value_type == "string" then pri = 2
                    elseif value_type == "table" then pri = 3
                    elseif value_type == "function" then pri = 4
                    else pri = 5 end
                    return pri
                end

                local type_a = type(a)
                local type_b = type(b)
                local pri_a = _getPri(type_a)
                local pri_b = _getPri(type_b)

                if pri_a == pri_b then
                    if type_a == "number" then
                        return a < b
                    else
                        return tostring(a) < tostring(b)
                    end
                else
                    return pri_a < pri_b
                end
            end)

            for _, k in ipairs(key_table) do
                local v = val[k]

                local key
                if type(k) == "string" then
                    key = "[\"" .. tostring(k) .. "\"]"
                else
                    key = "[" .. tostring(k) .. "]"
                end
                table.insert(content, _make_spaces(level+1) .. key .. " = ")
                table.insert(content, _val2str(v, level+1) .. "\n")
            end
            table.insert(content, _make_spaces(level) .. "}")
            return table.concat(content)
        end
    end

    print(info or "")
    for i, arg in ipairs(args) do
        print("param " .. tostring(i) .. " => ", _val2str(arg))
    end
    print("\n")
end

return Utils

