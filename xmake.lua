require("luarocks.loader");
package.cpath = package.cpath .. ";/usr/local/lib/lua/5.2/?.so";
local JSON = require("rapidjson");

add_rules("mode.debug", "mode.release");

set_config("plat", "cross")

local function tablelen(table)
    local len = 0;
    for k, v in pairs(table) do
        len = len + 1;
    end
    return len;
end

local function strcat(base, ext)
    base = base .. ext;
    return base;
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
        "-I.", 
        "-std=gnu11", 
        "-fno-stack-protector", 
        "-fno-omit-frame-pointer", 
        "-fpie", 
        "-mno-80387", 
        "-mno-mmx", 
        "-mno-3dnow", 
        "-mno-sse", 
        "-mno-sse2", 
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
    
    set_objectdir("build/");
    set_targetdir("build/bin");

    add_defines("QEMU");

    on_build(function (target)
        ---@class Log
        local log = {
           date = "",
           build_number = 0,
           action = "",
           runtime = ""
        };

        ---@type Log[]
        local logs = JSON.load("buildlog.json");

        if logs == nil then
            logs = {
                [0] = {
                    build_number = 0,
                    date = "nil",
                    action = "nil"
                }
            }
        end

        logs[#logs + 1] = {
            build_number = logs[#logs].build_number + 1;
            date = os.date("%Y/%m/%d at %H:%M"),
            action = arg[1]
        };

        JSON.dump(logs, "buildlog.json");

        local bn = logs[#logs].build_number;
        local bd = logs[#logs].date;
        print("Build " .. bn);
        print("Date: " .. bd);
        print("Action: " .. logs[#logs].action);

        local commonfile_read = io.open("kernel/lib/common.h", "r");

        ---@type string[]
        local content = {};

        for line in commonfile_read:lines() do
            table.insert(content, line);
        end

        commonfile_read:close();

        content[23] = "#define LUAOS_VERSION       \"1.0." .. tostring(bn) .. "\"";
        content[24] = "#define LUAOS_BUILD_DATE    \"" .. bd .. "\"";

        local commonfile_write = io.open("kernel/lib/common.h", "w");

        for i, v in pairs(content) do
            commonfile_write:write(v .. "\n");
        end

        commonfile_write:close();
    end);

    after_link(function (target)
        local liminepath = target:objectdir() .. "/limine/";
        local kernelimg = target:targetdir() .. "/LuaOS";

        local limine_exists = os.isdir(liminepath);

        if limine_exists == false then
            print("Cloning limine...")
            local gitcmd = "git clone https://github.com/limine-bootloader/limine.git " .. liminepath .. " --branch=v2.0-branch-binary --depth=1";
            os.run(gitcmd);
        end
        print("Making limine")
        os.run("make -C " .. liminepath);

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

        local xorrisoargs = "-as mkisofs -b ";

        xorrisoargs = strcat(xorrisoargs, xorrisofiles.cdbin .. " -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot ");
        xorrisoargs = strcat(xorrisoargs, xorrisofiles.efibin .. " -efi-boot-part --efi-boot-image --protective-msdos-label ");
        xorrisoargs = strcat(xorrisoargs, target:targetdir() .. " -o " .. xorrisofiles.export);
        
        print("Creating bootable media");
        os.run("xorriso " .. xorrisoargs);

        local exec = "./" .. liminepath .. "limine-install " .. xorrisofiles.export;
        print("Executing limine")
        os.run(exec);
    end);

    on_run (
        function(target)
            import("core.base.process");

            local files = {
                img = target:targetdir() .. "/LuaOS-x86_64.iso";
                elf = target:targetdir() .. "/LuaOS";
            };
            
            local qemucmd = "qemu-system-x86_64 -M q35 -m 1G -cdrom " .. files.img .. " -s -machine smm=off -d int -no-reboot -serial file:luaos.log -monitor stdio";
            print(qemucmd);
            
            local qemu = process.open(qemucmd, { stderr = "qemulog.txt" });
            
            os.run("sleep 1");
            

            --local gdb = process.openv (
            --    "/usr/local/x86_64-elf-gcc/bin/x86_64-elf-gdb",
            --    {
            --        "-ex", "target remote localhost:1234",
            --        "-ex", "file " .. files.elf
            --    }
            --);

            qemu:wait();
            --gdb:wait();
        end
    );
target_end();