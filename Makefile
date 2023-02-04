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

override CC := clang
override LD := ld.lld

CFLAGS ?= -g -O2 -pipe -Wall -Wextra
NASMFLAGS ?= -F dwarf -g

override CFLAGS +=       	\
    -std=gnu2x           	\
    -ffreestanding       	\
    -fno-stack-protector 	\
    -fno-stack-check     	\
    -fno-lto             	\
    -fno-pie             	\
    -fno-pic             	\
    -m64                 	\
    -march=x86-64        	\
    -mabi=sysv           	\
    -mno-80387           	\
    -mno-mmx             	\
    -mno-sse             	\
    -mno-sse2            	\
    -mno-red-zone        	\
    -mcmodel=kernel      	\
    -MMD                 	\
	-target x86_64-elf	 	\
	-isystem extern/include	\
	-Isrc/					\
	-Isrc/include/			\

override LDFLAGS +=         \
    -nostdlib               \
    -static                 \
    -m elf_x86_64           \
    -z max-page-size=0x1000 \
    -T res/linker.ld		\
	-no-pie

override ASFLAGS += -f elf64

override CFILES := $(shell find ./src -type f -name '*.c')
override ASFILES := $(shell find . -type f -name 'src/*.asm')

override COBJS := $(addprefix build/obj/,$(CFILES:.c=.o))
override ASOBJS := $(addprefix build/obj/,$(ASFILES:.asm=.o))

.PHONY: all
all: build/bin/luaos.iso

.PHONY: run
run: extern/ovmf-x64 build/bin/luaos.iso
	qemu-system-x86_64 -M q35 -m 2G -bios extern/ovmf-x64/OVMF.fd -cdrom build/bin/luaos.iso -boot d

extern/ovmf-x64:
	mkdir -p $@
	cd $@ && curl -o OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip && 7z x OVMF-X64.zip

extern/limine:
	mkdir -p $@
	git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1 $@
	$(MAKE) -C $@

build/bin/luaos.iso: extern/limine build/bin/luck.elf
	mkdir -p $(dir $@)
	cp res/limine.cfg extern/limine/limine-cd.bin extern/limine/limine.sys extern/limine/limine-cd-efi.bin $(dir $@)
	xorriso -as mkisofs\
			-b limine-cd.bin\
			-no-emul-boot\
			-boot-load-size 4\
			-boot-info-table\
			--efi-boot limine-cd-efi.bin\
			-efi-boot-part\
			--efi-boot-image\
			--protective-msdos-label\
			$(dir $@) -o $@

	extern/limine/limine-deploy $@

build/bin/luck.elf: $(COBJS) $(ASOBJS)
	mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -o $@ $^

$(COBJS): $(CFILES) extern/include/limine.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(ASOBJS): $(ASFILES)
	mkdir -p $(dir $@)
	nasm $(NASMFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf build

extern/include/limine.h:
	mkdir -p extern/include/
	curl https://raw.githubusercontent.com/limine-bootloader/limine/trunk/limine.h -o $@
