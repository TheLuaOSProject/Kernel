local QEMU  = "qemu-system-x86_64";
local GDB   = "/usr/local/x86_64-elf-gcc/bin/x86_64-elf-gdb";

local function buildproject()
    local cmd = "xmake -rvD";
    os.execute(cmd);
    
    return { img = "build/bin/LuaOS-x86_64.iso", kernel_obj = "build/LuaOS/cross/none/release/kernel/kernel.c.o" };
end

local files = buildproject();

local cmd   = QEMU .. " -s -M q35 -m 2G -cdrom " .. files.img .. " & " .. GDB .. " -ex \"target remote localhost:1234\" -ex \"symbol-file " .. files.kernel_obj .. "\"";

os.execute(cmd);
os.execute(gdbcmd);

io.read();
