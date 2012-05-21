-- check if basic type
function isbasic (type)
 local t = gsub(type,'const ','')
 local m,t = applytypedef('', t)
 local b = _basic[t]
 if b then
  return b,_basic_ctype[b]
 end
 return nil
end

function get_property_methods(ptype, name)

	if get_property_methods_hook and get_property_methods_hook(ptype,name) then
		return get_property_methods_hook(ptype, name)
	end

	if ptype == "default" then -- get_name, set_name
		return "get_"..name, "set_"..name
	end

	if ptype == "qt" then -- name, setName
		return name, "set"..string.upper(string.sub(name, 1, 1))..string.sub(name, 2, -1)
	end

	if ptype == "overload" then -- name, name
		return name,name
	end
	
	if ptype == "loop2d" then -- name, name
		return "get"..string.upper(string.sub(name, 1, 1))..string.sub(name, 2, -1), "set"..string.upper(string.sub(name, 1, 1))..string.sub(name, 2, -1)
	end

	return nil
end
