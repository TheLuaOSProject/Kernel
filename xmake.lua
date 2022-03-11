---@module xmake
---@field add_rules         function
---@field add_requires      function
---@field set_kind          function
---@field add_cflags        function
---@field add_ldflags       function
---@field add_files         function
---@field add_headerfiles   function
---@field add_includedirs   function
---@field add_files         function
---@field add_packages      function
---@field target            function
---@field target_end        function
---@field includes          function
---@field set_project       function
---@field set_version       function
---@field set_config        function
---@field add_defines       function
---@field toolchain         function
---@field set_sdkdir        function
---@field set_bindir        function
---@field set_toolset       function
---@field set_toolchains    function
---@field toolchain_end     function
---@field set_objectdir     function
---@field set_targetdir     function
---@field task              task
---@field task_end          function
---@field on_run            function
---@field import            function
---@field before_build      function
---@field package           function
---@field package_end       function
---@field set_url           function
---@field on_install        function
---@field git               git 
---@field os                os
---@field after_link        function
---@field print             function
---@field set_languages     function

---@class git
---@field clone function
---@field pull function

---@class os
---@field isdir function
---@field execv function

---@class task
---@field run       function

--[[
qemu-system-aarch64 -M virt -cpu cortex-a57 -m 4G -serial stdio -smp 4 -device ramfb -drive if=pflash,format=raw,file=[path/to/sabaton/virt.bin.pad],readonly=on -fw_cfg opt/Sabaton/kernel,file=[path/to/my/stivale2/aarch64/kernel.elf]
]]

local SOURCE_DIR<const>     = "src/"
local INCLUDE_DIR<const>    = SOURCE_DIR .. "include/"

local BUILD_DIR<const>  = "build/"
local OBJECT_DIR<const> = BUILD_DIR .. "obj/"
local BINARY_DIR<const> = BUILD_DIR .. "bin/"
local KERNEL_BIN<const> = BINARY_DIR .. "LuaOS"


local PACKAGES<const> = {
    "stivale2", 
    --"sabaton"
}

add_rules("mode.debug", "mode.release")
set_config("plat", "cross")


toolchain("clangtc")
do
    set_kind("standalone")
    --set_toolset("c", "clang")
    set_toolset("cc", "clang")
    set_toolset("c++", "clang++")
    set_toolset("ld", "ld.lld")
    set_toolset("as", "clang")
end
toolchain_end()

includes("packages.lua", "buildlog_task.lua")

add_requires(PACKAGES)

set_languages("c11", "cxx20")

target("LuaOS")
do
    set_kind("binary")
    set_toolchains("clangtc")
    add_cflags (
        "--target=aarch64-none-elf",
        "-std=gnu11",
        "-ffreestanding", "-fpie", "-fno-stack-protector", "-fno-omit-frame-pointer",
        "-mno-80387", "-mno-mmx", "-mno-3dnow", "-mno-sse", "-mno-sse2", "-mno-sse3", "-mno-sse4.1", "-mno-sse4.2", "-mno-sse4", "-mno-sse4a", "-mno-avx",  "-mno-red-zone",
        "-g", "-ggdb",
        "-Wall", "-Wextra", "-Werror",
        { force = true }
    )

    add_ldflags (
        --"-arch", "aarch64-elf-eabi",
        "-T", "cfg/linker.ld",
        "-nostdlib",
        "-zmax-page-size=0x1000",
        "-static",
        "-pie",
        "--no-dynamic-linker",
        "-ztext",
        { force = true }
    )
    
    add_asflags(
        "--target=aarch64-none-elf"
    )

    add_files(SOURCE_DIR .. "**.c", SOURCE_DIR .. "**.S")
    add_headerfiles(SOURCE_DIR .. "**.h")
    add_includedirs(SOURCE_DIR, INCLUDE_DIR)

    set_objectdir(OBJECT_DIR)
    set_targetdir(BINARY_DIR)

    add_packages(PACKAGES)

    if is_mode("debug") then
        add_defines("LUAOS_DEBUG")
    end
    
    on_run(function(target) 
        os.execv("qemu-system-aarch64", {
            "-M",       "virt",
            "-cpu",     "cortex-a72",
            "-m",       "2G", 
            "-serial",  "file:luaos.log", 
            "-smp",     "4", 
            "-device",  "ramfb", 
            "-drive",   "if=pflash,format=raw,file=" .. BINARY_DIR .. "Sabaton_virt_aarch64.elf.bin,readonly=on", 
            "-fw_cfg",  "opt/Sabaton/kernel,file=" .. KERNEL_BIN
        })
    end)
end
target_end()

