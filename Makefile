# Copyright (C) 2023 Amrit Bhogal
#
# This file is part of LuaOS.
#
# LuaOS is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# LuaOS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with LuaOS.  If not, see <http://www.gnu.org/licenses/>.

CC = clang
LD = ld.lld

GDB := x86_64-elf-gdb

CFLAGS = -g -Og -pipe -Wall -Wextra -Werror -Wno-unused -fms-extensions -Wno-microsoft
NASMFLAGS = -F dwarf -g -f elf64

CFLAGS +=       						\
    -std=gnu2x           				\
    -ffreestanding       				\
    -fno-stack-protector 				\
    -fno-stack-check     				\
    -fno-lto             				\
    -fno-pie             				\
    -fno-pic             				\
    -m64                 				\
    -march=x86-64        				\
    -mabi=sysv           				\
    -mno-80387           				\
    -mno-mmx             				\
    -mno-sse             				\
    -mno-sse2            				\
    -mno-red-zone        				\
    -mcmodel=kernel      				\
    -MMD                 				\
	-target x86_64-elf	 				\
	-isystem extern/limine				\
	-isystem extern/terminal			\
	-Iinc               				\
	-Wno-unused-command-line-argument	\
	-Wanon-enum-enum-conversion			\
	-Wassign-enum						\
	-Wenum-conversion					\
	-Wenum-enum-conversion				\
	-Wno-unused-function    			\
	-Wno-unused-parameter   			\
	-Wnull-dereference      			\
	-Wnull-conversion       			\
	-Wnullability-completeness			\
	-Wnullable-to-nonnull-conversion	\
	-fno-omit-frame-pointer 			\
	-Wno-deprecated-attributes			\
	-fblocks

LDFLAGS +=         			\
    -nostdlib               \
    -static                 \
    -m elf_x86_64           \
    -z max-page-size=0x1000 \
    -T res/linker.ld		\
	-no-pie

ASFLAGS = -f elf64

CFILES := $(shell find ./src -type f -name '*.c') extern/terminal/term.c extern/terminal/backends/framebuffer.c
ASFILES := $(shell find ./src -type f -name '*.asm')

COBJS := $(addprefix build/obj/,$(CFILES:.c=.c.o))
ASOBJS := $(addprefix build/obj/,$(ASFILES:.asm=.asm.o))

override QEMUFLAGS := -smp 2 -m 2G -monitor stdio -serial file:luaos.log
QDF ?= -s

.PHONY: all
all: build/bin/luaos.iso extern/ovmf-x64

.PHONY: uefi
uefi: extern/ovmf-x64 build/bin/luaos.iso
	qemu-system-x86_64 -M q35 $(QEMUFLAGS) -bios extern/ovmf-x64/OVMF.fd -cdrom build/bin/luaos.iso -boot d $(QDF)

.PHONY: bios
bios: build/bin/luaos.iso
	qemu-system-x86_64 -M q35 $(QEMUFLAGS) -cdrom build/bin/luaos.iso -boot d $(QDF)

extern/luajit/libluajit_luck.o:
	$(MAKE) -C extern/luajit CC="$(CC) -Wno-implicit-function-declaration"

extern/ovmf-x64:
	mkdir -p $@
	cd $@ && curl -o OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip && 7z x OVMF-X64.zip

extern/limine/limine-deploy:
	$(MAKE) -C extern/limine

extern/terminal/../luajit/src/lua.h: extern/luajit

build/bin/luaos.iso: extern/limine extern/limine/limine-deploy build/bin/luck.elf res/limine.cfg src/init.lua
	mkdir -p $(dir $@)/iso
	cp \
		build/bin/luck.elf res/powered-by-lua.bmp res/limine.cfg \
		res/font.bin extern/limine/limine-cd.bin extern/limine/limine.sys \
		extern/limine/limine-cd-efi.bin src/init.lua \
		$(dir $@)/iso
	xorriso -as mkisofs\
			-b limine-cd.bin\
			-no-emul-boot\
			-boot-load-size 4\
			-boot-info-table\
			--efi-boot limine-cd-efi.bin\
			-efi-boot-part\
			--efi-boot-image\
			--protective-msdos-label\
			$(dir $@)/iso -o $@
	rm -rf $(dir $@)/iso

	extern/limine/limine-deploy $@

build/bin/luck.elf: $(COBJS) $(ASOBJS) extern/luajit/libluajit_luck.o
	@/usr/bin/printf "\033[35mLinking $@\n\033[0m"
	@mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -o $@ $^

build/obj/extern/%.c.o: extern/limine extern/terminal extern/luajit
	@/usr/bin/printf "\033[32mCompiling $<\n\033[0m"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(shell echo "$@" | sed 's/build\/obj\///g' | sed 's/\.o//g') -o $@

build/obj/./src/%.c.o: src/%.c extern/limine extern/terminal extern/luajit
	@/usr/bin/printf "\033[32mCompiling $<\n\033[0m"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/obj/%.asm.o: %.asm
	@/usr/bin/printf "\033[32mAssembling $^\n\033[0m"
	@mkdir -p $(dir $@)
	nasm $(NASMFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf build
	find . -type f -name '*.o' -delete
	$(MAKE) -C extern/limine clean

-include $(CFILES:%.c=build/obj/%.c.d)
