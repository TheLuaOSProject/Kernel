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
        "kernel/kernel.c"
    },
    depfiles_gcc = "build/kernel/LuaOS/macosx/x86_64/debug/kernel/kernel.c.o: kernel/kernel.c  kernel/lib/types.h kernel/drivers/drivers.h kernel/drivers/ports.h  kernel/drivers/../lib/types.h\
"
}