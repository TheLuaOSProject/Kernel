# Luck - The LuaOS kernel

Luck is the kernel for LuaOS, it is a microkernel.

## Building

Get the source with:

`git clone --recursive https://github.com/TheLuaOSProject/Kernel.git`

### Dependencies

#### General

- `clang`
- `nasm`
- `curl`
- `ld.lld`
- `xorriso`

#### arch

- 'lld' (`ld.lld`)
- 'libisoburn' (`xorriso`)

```sh
make
```

## Testing

### Dependencies

- `qemu-system-x86_64`

```sh
make uefi
```
