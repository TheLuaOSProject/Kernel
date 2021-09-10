add_rules("mode.debug", "mode.release");



toolchain("cross-toolchain");
    set_kind("standalone");
    set_sdkdir("/usr/local/i386elfgcc/");
    set_bindir("/usr/local/i386elfgcc/bin");

    set_toolset("c", "i386-elf-gcc");
    set_toolset("ld", "i386-elf-ld");
    set_toolset("as", "nasm");

    
toolchain_end();

target("LuaOS-Boot");
    set_plat("cross");
    set_kind("binary");
    set_toolchains("cross-toolchain");

    add_files("boot/boot.asm");

    add_asflags("-f bin", { force = true });

    set_objectdir("build/boot/");
    set_targetdir("build/boot/bin");

    set_strip("none");

    on_link(function (target) end);
    after_link(function (target) 
        os.rm(target:targetdir() .. "/boot.bin");
        os.cp(target:objectdir() .. "/boot/boot.asm.o", target:targetdir() .. "/boot.bin", {rootdir = "build", symlink = false});
    end);
target_end();

target("LuaOS-kernel");
    set_plat("cross");
    set_kind("binary");
    set_toolchains("cross-toolchain");

    add_files("kernel/**.c", "kernel/**.asm");
    add_headerfiles("kernel/**.h");
    add_includedirs("kernel/", "./");

    add_asflags("-f elf32", { force = true });
    add_cflags("-ffreestanding", { force = true });
    add_ldflags("-Ttext 0x1000", { force = true });
    set_objectdir("build/kernel/");
    set_targetdir("build/kernel/bin");

    after_link(function (target) 
        os.mkdir("build/bin");
        os.execv("cat", {"build/boot/bin/boot.bin", target:targetdir() .. "/LuaOS-kernel"}, {stdout = "build/bin/luaos.bin"});
    end);
target_end();