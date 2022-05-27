--[[
qemu-system-aarch64 -M virt -cpu cortex-a57 -m 4G -serial stdio -smp 4 -device ramfb -drive if=pflash,format=raw,file=[path/to/sabaton/virt.bin.pad],readonly=on -fw_cfg opt/Sabaton/kernel,file=[path/to/my/stivale2/aarch64/kernel.elf]
]]

includes("packages.lua")

local PACKAGES<const> = {
    "stivale2", 
    "sabaton"
}

local SABATON_PATH<const> = "sabaton.elf.bin"

add_rules("mode.debug", "mode.release")

set_config("plat", "cross")
set_config("arch", "aarch64")
local TARGET<const> = "aarch64-none-elf"

set_languages("gnulatest", "gnuxxlatest")

add_requires(PACKAGES)

target("LuaOS")
do
    set_kind("binary")
    
    add_packages(PACKAGES)
    
    add_files("src/**.c", "src/**.asm")
    add_includedirs("src/", "src/include/")
 
    
    add_cflags {
        "--target=" .. TARGET, "-ffreestanding",
        "-fpie", "-fno-stack-protector", "-fno-omit-frame-pointer",
        "-mno-80387", "-mno-mmx", "-mno-3dnow", "-mno-sse", "-mno-sse2", "-mno-sse3", "-mno-sse4.1", "-mno-sse4.2", "-mno-sse4", "-mno-sse4a", "-mno-avx",  "-mno-red-zone",
        "-Wall", "-Wextra", "-Werror", "-Wno-unused-function", "-Wno-unused-parameter", "-Wno-unused-variable", 
        "-fms-extensions", "-Wno-microsoft"
    }
    
    add_asflags {
        "--target=" .. TARGET, "-ffreestanding"
    }
   
    add_ldflags (
        "--script", "config/linker.ld",
        "-nostdlib",
        { force = true }
    )
   
   on_run(function(target)
        import("lib.detect.find_tool")
        local qemu = find_tool("qemu-system-aarch64")
        os.runv(qemu.program, { 
                "-M",       "virt",
                "-cpu",     "cortex-a72",
                "-m",       "2G", 
                "-serial",  "file:luaos.log", 
                "-smp",     "4", 
                "-device",  "ramfb", 
                "-drive",   "if=pflash,format=raw,file=" .. SABATON_PATH .. ",readonly=on", 
                "-fw_cfg",  "opt/Sabaton/kernel,file=" .. target:targetfile(),
                "-S", "-d", "int",
                "-s"
        }) 
   end)
end
target_end()
