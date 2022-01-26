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

local BUILD_DIR<const>      = "build/"
local OBJECT_DIR<const>     = BUILD_DIR .. "obj/"
local BINARY_DIR<const>     = BUILD_DIR .. "bin/"

add_rules("mode.debug", "mode.release")
set_config("plat", "cross")

set_toolchains("clang")

includes("packages.lua", "buildlog.lua")

local PACKAGES<const> = {
    "stivale2", 
    "sabaton"
}

add_requires(PACKAGES)

target("LuaOS")
do
    add_cflags (
        "-target aarch64-none-elf",
        "-std=gnu11",
        "-ffreestanding", "-fpie", "-fno-stack-protector", "-fno-omit-frame-pointer",
        "-mno-80387", "-mno-mmx", "-mno-3dnow", "-mno-sse", "-mno-sse2", "-mno-sse3", "-mno-sse4.1", "-mno-sse4.2", "-mno-sse4", "-mno-sse4a", "-mno-avx",  "-mno-red-zone",
        "-g", "-ggdb",
        "-Wall", "-Wextra", "-Werror",
        { force = true }
    )

    add_ldflags (
        "-Tcfg/linker.ld",
        "-nostdlib",
        "-zmax-page-size=0x1000",
        "-static",
        "-pie",
        "--no-dynamic-linker",
        "-ztext",
        { force = true }
    )

    add_files(SOURCE_DIR .. "**.c", SOURCE_DIR .. "**.asm")
    add_headerfiles(SOURCE_DIR .. "**.h")
    add_includedirs(SOURCE_DIR, INCLUDE_DIR)

    set_objectdir(OBJECT_DIR)
    set_targetdir(BINARY_DIR)

    add_packages(PACKAGES)
end
target_end()

