---
--- Created by Frityet.
--- DateTime: 2021-09-15 4:20 p.m.
---
--comment if Luarocks path setup properly
require("luarocks.loader");
package.cpath = package.cpath .. ";/usr/local/lib/lua/5.2/?.so";
local JSON = require("rapidjson");

if arg[1] == "buildnum" then
    local logs = JSON.load("buildlog.json")
    io.write(logs[#logs].build_number)
    return
end

---@class Log
local log = {
    date         = "",
    build_number = 0,
    action       = "",
    runtime      = ""
};


---@type Log[]
local logs = JSON.load("buildlog.json");

if logs == nil then
    logs = {
        [0] = {
            build_number = 0,
            date = "nil",
            action = "nil"
        }
    }
end
logs[#logs + 1] = {
    build_number = logs[#logs].build_number + 1;
    date = os.date("%Y/%m/%d at %H:%M"),
    action = arg[1]
};

JSON.dump(logs, "buildlog.json")

local bn = logs[#logs].build_number;
local bd = logs[#logs].date;
print("Build " .. bn);
print("Date: " .. bd);
print("Action: " .. logs[#logs].action);
