set -ex

cd extern/luajit/src

DASM=../dynasn/dynasm.lua
ALL_LIB="lib_base.c lib_math.c lib_bit.c lib_string.c lib_table.c lib_io.c lib_os.c lib_package.c lib_debug.c lib_jit.c lib_ffi.c lib_buffer.c"

gcc host/minilua.c -o minilua.exe

./minilua.exe ../dynasm/dynasm.lua -LN -D P64 -D NO_UNWIND -o host/buildvm_arch.h vm_x64.dasc

gcc host/buildvm*.c -o buildvm.exe -DLUAJIT_TARGET=LUAJIT_ARCH_X64 -DLUAJIT_OS=LUAJIT_OS_OTHER -DLUAJIT_DISABLE_JIT -DLUAJIT_DISABLE_FFI -DLUAJIT_NO_UNWIND -I. -DTARGET_OS_IPHONE=0

./buildvm.exe -m elfasm -o lj_vm.s
./buildvm.exe -m bcdef -o lj_bcdef.h $ALL_LIB
./buildvm.exe -m ffdef -o lj_ffdef.h $ALL_LIB
./buildvm.exe -m libdef -o lj_libdef.h $ALL_LIB
./buildvm.exe -m recdef -o lj_recdef.h $ALL_LIB
./buildvm.exe -m vmdef -o jit/vmdef.lua $ALL_LIB
./buildvm.exe -m folddef -o lj_folddef.h lj_opt_fold.c

LJCOMPILE="clang -target x86_64-elf -nostdinc -Wno-duplicate-decl-specifier -Wno-unused-command-line-argument -Wno-unknown-attributes -I../../../inc -I../../../inc/lj-libc -DLUAJIT_DISABLE_FFI -DLUAJIT_USE_SYSMALLOC -DLUAJIT_TARGET=LUAJIT_ARCH_X64 -DLUAJIT_OS=LUAJIT_OS_OTHER -DLUAJIT_DISABLE_JIT -DLUAJIT_DISABLE_FFI -DLUAJIT_NO_UNWIND -I. -DTARGET_OS_IPHONE=0 -DLUAJIT_SECURITY_PRNG=0 -g -mcmodel=kernel -fno-omit-frame-pointer"

rm -f lj_*.o lib_*.o

$LJCOMPILE -c -o lj_vm.o lj_vm.s

for f in lj_*.c lib_aux.c lib_base.c lib_bit.c lib_buffer.c lib_debug.c lib_math.c lib_string.c lib_table.c; do
    $LJCOMPILE -c $f
done

ld.lld -r -o libluajit_luck.o lj_*.o lib_*.o
