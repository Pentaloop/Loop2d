local newIndex = function(self, key, value)
	print("newIndex "..key.."="..value.."\n")
end

local index = function(self, key, value)
    print("index "..key.."="..value.."\n")
end

local proxy_mt = {
    __newindex = newIndex,
    __index = index,
}

Settings = setmetatable({}, proxy_mt)
--Settings = { __index = index, __newindex = newIndex};