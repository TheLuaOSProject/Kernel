CC				= /usr/local/i386elfgcc/bin/i386-elf-gcc
CCFLAGS			= -g

LD				= /usr/local/i386elfgcc/bin/i386-elf-ld
GDB				= /usr/local/i386elfgcc/bin/i386-elf-gdb

BUILD_DIR 		= build

KERNEL_OFFSET 	= 0x1000

OS_IMAGE 		= luaos.bin

KERNEL_C 		= $(wildcard kernel/*/*.c kernel/*.c)
KERNEL_H 		= $(wildcard kernel/*/*.h kernel/*.h)
OBJ 			= ${KERNEL_C:.c=.o}

BOOTLOADER = "boot/boot.asm"

build: clean make_dirs ${BUILD_DIR}/bin/${OS_IMAGE}

make_dirs:
	echo ${OBJ}

	mkdir -p ${BUILD_DIR}/bin
	mkdir -p ${BUILD_DIR}/boot
	mkdir -p ${BUILD_DIR}/kernel/drivers

run: build
	qemu-system-i386 -fda ${BUILD_DIR}/bin/${OS_IMAGE}

debug: ${BUILD_DIR}/bin/${OS_IMAGE} ${BUILD_DIR}/bin/kernel.elf
	qemu-system-i386 -s -fda ${BUILD_DIR}/bin/${OS_IMAGE} &
    ${GDB} -ex "target remote localhost:1234" -ex "symbol-file ${BUILD_DIR}/bin/kernel.elf"


${BUILD_DIR}/bin/${OS_IMAGE}: ${BUILD_DIR}/bin/boot.bin ${BUILD_DIR}/bin/kernel.bin
	cat $^ > ${BUILD_DIR}/bin/${OS_IMAGE}

${BUILD_DIR}/bin/kernel.bin: ${BUILD_DIR}/kernel/kernel_start.o ${BUILD_DIR}/${OBJ}
	${LD} -o $@ -Ttext ${KERNEL_OFFSET} $^ --oformat binary

${BUILD_DIR}/bin/kernel.elf: ${BUILD_DIR}/kernel/kernel_start.o ${BUILD_DIR}/${OBJ}
	${LD} -o $@ -Ttext ${KERNEL_OFFSET} $^

${BUILD_DIR}/${OBJ}: ${KERNEL_H} ${KERNEL_C} 
	${CC} ${CCFLAGS} -ffreestanding -c $< -o $@

${BUILD_DIR}/kernel/kernel_start.o: kernel/kernel_start.asm
	nasm $< -f elf -o $@

${BUILD_DIR}/bin/boot.bin: boot/boot.asm
	nasm $< -f bin -o $@

clean:
	rm -rf ${BUILD_DIR}


