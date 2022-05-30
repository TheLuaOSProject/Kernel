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
        import("lib.detect.find_tool")
        
        local comperr
        
        local zig = find_tool("zig")
        try {
            function ()
                os.runv(zig.program, { "build", "virt" }, { envs = { AARCH64_EDK_PATH = "" } })
            end,
            catch { function (err) comperr = err  end }
        }
        
        try {
            function() os.cp("zig-out/bin/Sabaton_virt_aarch64.elf.bin", package:installdir()) end,
            catch { function (err) raise("\x1b[31mCould not build!\nError: \x1b[0m" .. comperr .. "\n\x1b[31mTry installing Zig 0.9!") end }
        }
    end)
end
package_end()
