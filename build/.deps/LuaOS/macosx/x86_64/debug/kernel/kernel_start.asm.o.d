{
    files = {
        "kernel/kernel_start.asm"
    },
    values = {
        "/usr/local/bin/nasm",
        {
            "-I",
            "kernel",
            "-I",
            ".",
            "-f",
            "elf32"
        }
    }
}