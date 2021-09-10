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
    set_kind("binary");
    set_toolchains("cross-toolchain");

    add_files("boot/boot.asm");

    add_asflags("-f bin", { force = true });

    set_objectdir("build/boot/");
    set_targetdir("build/boot/bin");
target_end();

target("LuaOS-kernel");
    set_kind("binary");
    set_toolchains("cross-toolchain");

    add_files("kernel/**.c", "kernel/**.asm");
    add_headerfiles("kernel/**.h");
    add_includedirs("kernel/", "./");

    add_asflags("-f elf32", { force = true });
    add_cflags("-ffreestanding", { force = true });
    add_ldflags("-Ttext 0x1000", "--oformat binary");
    set_objectdir("build/kernel/");
    set_targetdir("build/kernel/bin");
target_end();