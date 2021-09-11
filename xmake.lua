add_rules("mode.debug", "mode.release");

set_config("plat", "cross")

toolchain("cross-toolchain");
    set_kind("standalone");
    set_sdkdir("/usr/local/x86_64-elf-gcc/");
    set_bindir("/usr/local/x86_64-elf-gcc/bin");

    set_toolset("c", "x86_64-elf-gcc");
    set_toolset("ld", "x86_64-elf-ld");
    set_toolset("as", "nasm");
toolchain_end();

target("LuaOS");
    set_kind("binary");
    set_toolchains("cross-toolchain");

    add_files("kernel/**.c", "kernel/**.asm");
    add_headerfiles("kernel/**.h");
    add_includedirs("kernel/", "kernel/lib/");

    add_asflags("-f elf64", { force = true });
    add_cflags("-ffreestanding -I. -std=gnu11 -fno-stack-protector -fpie -mno-80387 -mno-mmx -mno-3dnow -mno-sse -mno-sse2 -mno-red-zone", { force = true });
                
    add_ldflags("-Tkernel/linker.ld -nostdlib -zmax-page-size=0x1000 -static -pie --no-dynamic-linker -ztext", { force = true });
    
    set_objectdir("build/");
    set_targetdir("build/bin");

    after_link(function (target) 
    
    end);
target_end();