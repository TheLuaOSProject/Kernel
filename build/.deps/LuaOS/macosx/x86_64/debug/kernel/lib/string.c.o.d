{
    values = {
        "/usr/local/i386elfgcc/bin/i386-elf-gcc",
        {
            "-g",
            "-O0",
            "-Ikernel",
            "-I.",
            "-ffreestanding"
        }
    },
    files = {
        "kernel/lib/string.c"
    },
    depfiles_gcc = "build/kernel/LuaOS/macosx/x86_64/debug/kernel/lib/string.c.o:  kernel/lib/string.c kernel/lib/string.h kernel/lib/types.h\
"
}