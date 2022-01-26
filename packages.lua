---@module xmakepackage
---@field package           function
---@field set_urls          function
---@field on_load           function
---@field on_install        function
---@field package_end       function
---@field add_includedirs   function
---@field import            function
---@field os os

---@class os
---@field cp function
---@field vcp function
---@field mkdir function

package("stivale2")
do
    set_urls("https://github.com/stivale/stivale.git")
    
    add_includedirs("")
    
    on_install(function (package)
        os.mkdir(package:installdir())
        os.cp("stivale2.h", package:installdir())
    end)
end
package_end()

package("sabaton")
do
    set_urls("https://github.com/FlorenceOS/Sabaton.git")
    
    on_install(function (package)
        os.execv("zig", "build", "virt")
        os.cp("zig-out/bin/Sabaton_virt_aarch64.elf.bin", package:installdir() .. "/sabaton.bin")
    end)
end
package_end()
