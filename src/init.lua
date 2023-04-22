---@class Kernel
---@field log { debug: fun(msg: string), info: fun(msg: string), warning: fun(msg: string), error: fun(msg: string), fatal: fun(msg: string) }
kernel = kernel

kernel.log.info "Hello, World from init.lua!"

kernel.log.warning "See how the line number and file is showing!"
