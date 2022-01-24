---@module xmake
---@field add_rules         function
---@field add_requires      function
---@field set_kind          function
---@field add_cflags        function
---@field add_ldflags       function
---@field add_files         function
---@field add_headerfiles   function
---@field add_includedirs   function
---@field add_files         function
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
---@field set_urls          function
---@field on_install        function
---@field git               git 
---@field os                os

---@class git
---@field clone function
---@field pull function

---@class os
---@field isdir

---@class task
---@field run       function

package("stivale2")
do
    set_urls("https://github.com/stivale/stivale.git")
    
end
package_end()

package("sabaton")
do
    set_urls("https://github.com/FlorenceOS/Sabaton.git")
    
    --on_install(function (package) 
    --
    --end)
end
package_end()
