

-- data manager implement
local data = {}

data.tables = {}

local function _set_table_read_only(dataTable)
	assert(dataTable, "table not exist")

	local proxy = {}
	local mt = {
		__index = dataTable,
		__newindex = function(t, k, v)
			assert(false, "error: attemp to update a read only table")
		end,
	}
	setmetatable(proxy, mt)

	return proxy
end

function data.load(tableName, datafile)
	if not datafile then datafile = tableName end
	data.tables[tableName] = require(datafile)

	-- 设置表格数据只读属性
	for i, t in ipairs(data.tables[tableName]._data) do
		data.tables[tableName]._data[i] = _set_table_read_only(t)
	end

end

function data.get(tableName, ...)
	local t = data.tables[tableName]
	assert(#arg > 0 and #arg == #t._keys)

	if type(t) ~= "table" then
		return nil
	end

	local map = t._map
	for i = 1, #arg do
		if i~=#arg and type(map) ~= "table" then
			return nil
		end

		map = map[tostring(arg[i])]
		if i == #arg then
			return t._data[map]
		end
	end
end

local function _iter(list, i)
	i = i + 1
	local v = list[i]
	if v then
		return i, v
	else
		return nil, nil
	end
end

function data.ipairs(tableName)
	local t = data.tables[tableName]
	return _iter, t._data, 0
end


--return data


-- test code bellow --------------------------------------------------------

data.load("testnokey")
data.load("test1keys")
data.load("test2keys")
data.load("test3keys")

-- test find by key(s)
local t1 = data.get("test1keys", 3)
print( t1["普通列1"] )

local t2 = data.get("test2keys", 3, 2)
print( t2["普通列2"] )

local t3 = data.get("test3keys", 3, "测试值1", "a")
print( t3["键列3"] )

-- test ipairs
for i, v in data.ipairs("test2keys") do
	print(i, v["键列2"])
end


-- test read only
t1["普通列1"] = "123"
