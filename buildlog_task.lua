---@module xmake
---@class cmake
---@field add_rules         function
---@field add_requires      function
---@field set_kind          function
---@field add_cflags        function
---@field add_ldflags       function
---@field add_files         function
---@field add_headerfiles   function
---@field add_includedirs   function
---@field add_packages      function
---@field target            function
---@field target_end        function
---@field includes          function
---@field set_project       function
---@field set_version       function
---@field set_config        function
---@field add_defines       function
---@field toolchain         function
---@field set_sdkdir        function
---@field set_bindir        function
---@field set_toolset       function
---@field set_toolchains    function
---@field toolchain_end     function
---@field set_objectdir     function
---@field set_targetdir     function
---@field task              task
---@field task_end          function
---@field on_run            function
---@field import            function
---@field before_build      function
---@field package           function
---@field package_end       function
---@field set_url           function
---@field on_install        function
---@field git               git 
---@field os                os
---@field json              json

---@class git
---@field clone function
---@field pull function

---@class os
---@field isdir

---@class task
---@field run       function

---@class json
---@field deserialise function

---@class BuildLog
---@field date string
---@field buildnumber number
---@field action string


function table:__tostring()
    local result = "{"
    for k, v in pairs(self) do
        -- Check the key type (ignore any numerical keys - assume its an array)
        if type(k) == "string" then
            result = result.."[\""..k.."\"]".."="
        end

        -- Check the value type
        if type(v) == "table" then
            result = result..table_to_string(v)
        elseif type(v) == "boolean" then
            result = result..tostring(v)
        else
            result = result.."\""..v.."\""
        end
        result = result..","
    end
    -- Remove leading commas from the result
    if result ~= "" then
        result = result:sub(1, result:len()-1)
    end
    return result.."}"
end

task("update_buildlog-build")
do
    --local bl = local_buildlog()
    --local old = bl[#bl]
    --bl[#bl + 1] = {
    --    date = os.time(nil),
    --    buildnumber = old.buildnumber + 1,
    --    action = "build"
    --}
    --local f = io.open("buildlog.lua", "w")
    --f:write("return ")
    --f:write(bl)
end
task_end()

task("update_buildlog-run")
do
    --local bl = local_buildlog()
    
end
task_end()
