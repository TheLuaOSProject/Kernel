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
    add_cflags("-ffreestanding -I. -std=gnu11 -fno-stack-protector -fpie -mno-80387 -mno-mmx -mno-3dnow -mno-sse -mno-sse2 -mno-red-zone -g", { force = true });
                
    add_ldflags("-Tkernel/linker.ld -nostdlib -zmax-page-size=0x1000 -static -pie --no-dynamic-linker -ztext", { force = true });
    
    set_objectdir("build/");
    set_targetdir("build/bin");

    after_link(function (target)
        local liminepath = target:objectdir() .. "/limine/";
        local kernelimg = target:targetdir() .. "/LuaOS";

        if os.isdir(liminepath) then
            os.rm(liminepath);
        end

        local gitcmd = "git clone https://github.com/limine-bootloader/limine.git " .. liminepath .. " --branch=v2.0-branch-binary --depth=1";
        os.run(gitcmd);

        os.run("make -C " .. liminepath);

        local liminefiles = { 
            cfg     = "kernel/limine.cfg",
            sys     = liminepath .. "limine.sys",
            cdbin   = liminepath .. "limine-cd.bin",
            efibin  = liminepath .. "limine-eltorito-efi.bin"
        };
        
        for _, v in pairs(liminefiles) do
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
        os.run("xorriso " .. xorrisoargs);

        local exec = "./" .. liminepath .. "limine-install " .. xorrisofiles.export;
        os.run(exec);
    end);

    on_run (
        function(target)
            import("core.base.process");

            local files = {
                img = target:targetdir() .. "/LuaOS-x86_64.iso";
                elf = target:targetdir() .. "/LuaOS";
            };
            
            local qemucmd = "qemu-system-x86_64 -M q35 -m 1G -cdrom " .. files.img .. " -s";
            print(qemucmd);
            local qemu = process.open(qemucmd, { stderr = "qemulog.txt" });
            
            os.run("sleep 1");
            
            local gdb = process.openv (
                "/usr/local/x86_64-elf-gcc/bin/x86_64-elf-gdb",
                { 
                    "-ex", "target remote localhost:1234", 
                    "-ex", "file " .. files.elf
                }
            );
            
            qemu:wait();
            gdb:wait();
        end
    );
target_end();