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
        "kernel/drivers/ports.c"
    },
    depfiles_gcc = "build/kernel/LuaOS/macosx/x86_64/debug/kernel/drivers/ports.c.o:  kernel/drivers/ports.c kernel/drivers/ports.h  kernel/drivers/../lib/types.h\
"
}