# LuaOS
## About

LuaOS is a custom kernel running on the Limine bootloader. It aims to allow for parts of the OS to be written in lua, a scripting language.
## Building

To build LuaOS, clone the repository and make sure you have the following packages installed:

``zig xmake clang``

After these packages are installed, navigate into the Kernal directory and run:

``xmake config --mode=debug --toolchain=clang --cc=$CC --cxx=$CXX --ld=ld.lld --as=$CC``

with ``$CC`` being your c complier, and ``$CXX`` being your c++ compiler.

Once this is ran, you can then just run ``xmake``, which will build the the kernal.
