-- require("luarocks.loader");
-- package.cpath = package.cpath .. ";/usr/local/lib/lua/5.2/?.so";
-- local JSON = require("rapidjson");

add_rules("mode.debug", "mode.release");

set_config("plat", "cross")

local function startswith(str, pattern)
    return string.sub(str, 1, string.len(pattern)) == pattern;
end

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
    add_cflags (
        "-ffreestanding",
        "-std=gnu11",
        "-fpie",
        "-fno-stack-protector",
        "-fno-omit-frame-pointer",
        "-mno-80387",
        "-mno-mmx",
        "-mno-3dnow",
        "-mno-sse",
        "-mno-sse2",
        "-mno-sse3",
        "-mno-sse4.1",
        "-mno-sse4.2",
        "-mno-sse4",
        "-mno-sse4a",
        "-mno-avx",
        "-mno-red-zone",
        "-g",
        "-ggdb",
        "-Wall",
        "-Wextra",
        "-Werror",
        { force = true }
    );
                
    add_ldflags (
        "-Tkernel/linker.ld",
        "-nostdlib",
        "-zmax-page-size=0x1000",
        "-static",
        "-pie",
        "--no-dynamic-linker",
        "-ztext",
        { force = true }
    );
    
    set_objectdir("build/obj/");
    set_targetdir("build/bin/");

    add_defines("QEMU");

    before_build(function (target)
        -- os.run("xmake project -k compile_commands .vscode/")

        print("Updating common.h")

        os.runv("lua", { "buildlog.lua", "build" })

        local commonfile_read = io.open("kernel/lib/common.h", "r");

        ---@type string[]
        local content = {};

        for line in commonfile_read:lines() do
            table.insert(content, line);
        end

        commonfile_read:close();

        local version_ln, build_ln = 0, 0;

        for key, value in pairs(content) do
            if startswith(value, "#define LUAOS_VERSION") then
                version_ln = key;
            else
                if startswith(value, "#define LUAOS_BUILD_DATE") then
                    build_ln = key;
                end
            end
        end
 
        local buildnum, _ = os.iorunv("lua", { "buildlog.lua", "buildnum" });


        content[version_ln] = "#define LUAOS_VERSION       \"1.0." .. buildnum .. "\"";
        content[build_ln] = "#define LUAOS_BUILD_DATE    \"" .. os.date("%Y/%m/%d at %H:%M") .. "\"";

        local commonfile_write = io.open("kernel/lib/common.h", "w");

        for _, v in pairs(content) do
            commonfile_write:write(v .. "\n");
        end

        commonfile_write:close();

        print("Setting up Limine")

        local liminepath = target:objectdir() .. "/limine/";

        local has_wifi = true;

        if os.isdir(liminepath) then
            local out, err = os.iorunv("ping", { "-c1", "github.com" })
            if err ~= "" then has_wifi = false goto NO_WIFI end
            os.rm(liminepath)
            ::NO_WIFI::
        end

        if has_wifi then
            print(os.iorunv("git", { "clone", "https://github.com/limine-bootloader/limine.git", liminepath, "--branch=v2.0-branch-binary", "--depth=1" }))
            print("Making limine...")
            os.iorunv("make", { "-C", liminepath });
        end

        local liminefiles = { 
            cfg     = "kernel/limine.cfg",
            sys     = liminepath .. "limine.sys",
            cdbin   = liminepath .. "limine-cd.bin",
            efibin  = liminepath .. "limine-eltorito-efi.bin"
        };
        
        print("Copying files")
        for _, v in pairs(liminefiles) do
            print("Copying file " .. v)
            os.cp(v, target:targetdir());
        end
        
    end);

    after_link(function (target)
        local liminepath = target:objectdir() .. "/limine/";
 
        local xorrisofiles = {
            cfg     = "limine.cfg",
            sys     = "limine-cd.bin",
            cdbin   = "limine-cd.bin",
            efibin  = "limine-eltorito-efi.bin",
            export  = target:targetdir() .. "/LuaOS-x86_64.iso"
        };
        
        if os.isfile(xorrisofiles.export) then
            os.rm(xorrisofiles.export);
        end
        
        print("Creating bootable media");
        os.iorunv("xorriso", {
            "-as",                      "mkisofs",
            "-b",                       xorrisofiles.cdbin,
            "-no-emul-boot",
            "-boot-load-size",          "4",
            "-boot-info-table",
            "--efi-boot",               xorrisofiles.efibin,
            "-efi-boot-part",
            "--efi-boot-image",
            "--protective-msdos-label",
            target:targetdir(),
            "-o",                       xorrisofiles.export
        })

        print("Executing limine")
        print(os.iorunv(liminepath .. "limine-install", { xorrisofiles.export }));
    end);

    on_run(function (target)
        os.iorunv("qemu-system-x86_64", { 
            "-M",           "q35",
            "-m",           "1G",
            "-cdrom",       target:targetdir() .. "/LuaOS-x86_64.iso",
            "-s",
            "-machine",     "smm=off",
            "-d",           "int",
            "-no-reboot",
            "-serial",      "file:luaos.log",
            "-monitor",     "stdio"
        });
    end);
target_end();