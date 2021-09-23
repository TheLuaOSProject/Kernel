---
--- Created by Frityet.
--- DateTime: 2021-09-15 4:20 p.m.
---

---@class task
---@field name          string
---@field dependencies  table[] | nil
---@field action        function
local task = {
    ---@type    string
    name;

    ---@type    table[] | nil
    dependencies;
    
    ---@type    function
    action;
}

---@param name          string
---@param dependencies  task[] | nil
---@param action        function
---@return task
function task:create(name, dependencies, action)
    ---@type task
    local t = {};
    
    t.name = name;
    t.dependencies = dependencies;
    t.action = action;
    
    return t;
end

function build_luaos()
    os.execute("xmake -rvD");
end

function run_luaos()
    os.execute("xmake run");
end

function debug_luaos()
    
end

---@type task
local build = {
     name           = "build",
     dependencies   = nil,
     action         = build_luaos
}

---@type task
local run = {
    name            = "run",
    dependencies    = { build },
    action          = run_luaos
}

---@type task
local debug = {
    name            = "debug",
    dependencies    = { build },
    action          = debug_luaos 
}

---@type task[]
local tasks = {
    build,
    run,
    debug
}

for _, v in pairs(tasks) do
    if v.name == arg[1] then
        if v.dependencies ~= nil then
            for _, p in pairs(v.dependencies) do
                p.action();
            end
        end
        v.action();
    end
end 
