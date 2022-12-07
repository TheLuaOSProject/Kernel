package("limine")
do
    set_urls("https://github.com/limine-bootloader/limine/releases/download/$(version)/limine-$(version).tar.gz")

    add_deps {
        "make",
        "grep",
        "sed",
        "find",
        "awk",
        "gzip",
        "nasm",
        "mtools",
        "clang"
    }

    add_versions("v4.20221119.0")
    
    add_includedirs("")
    
    on_install(function (package)
        package:addenv("CROSS_TOOLCHAIN", "llvm") --Fuck your GCC
        import("package.tools.autoconf").install(package)
    end)
end
package_end()
