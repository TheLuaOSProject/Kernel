---@class Kernel.Canvas
---@field create fun(): Kernel.Canvas
---@field fill fun(self: Kernel.Canvas, color: integer)
---@field set_pixel fun(self: Kernel.Canvas, x: integer, y: integer, color: integer)
---@field get_pixel fun(self: Kernel.Canvas, x: integer, y: integer): integer
---@field draw_line fun(self: Kernel.Canvas, x1: integer, y1: integer, x2: integer, y2: integer, color: integer)
---@field draw_rect fun(self: Kernel.Canvas, x: integer, y: integer, width: integer, height: integer, color: integer)
---@field draw_circle fun(self: Kernel.Canvas, x: integer, y: integer, radius: integer, color: integer)
---@field draw_text fun(self: Kernel.Canvas, x: integer, y: integer, text: string, size: integer, color: integer)
---@field test_pitch fun(self: Kernel.Canvas)
---@field set_pitch fun(self: Kernel.Canvas, pitch: integer)
---@field get_dimensions fun(self: Kernel.Canvas): integer, integer
kernel.framebuffer = kernel.framebuffer

--0xAARRGGBB

local colours = {
    black       = 0xFF000000,
    white       = 0xFFFFFFFF,
    red         = 0xFFFF0000,
    green       = 0xFF00FF00,
    blue        = 0xFF0000FF,
    yellow      = 0xFFFFFF00,
    cyan        = 0xFF00FFFF,
    magenta     = 0xFFFF00FF,
    orange      = 0xFFFFA500,
    purple      = 0xFF800080,
    brown       = 0xFFA52A2A,
    pink        = 0xFFFFC0CB,
    grey        = 0xFF808080,
    light_grey  = 0xFFD3D3D3,
    dark_grey   = 0xFFA9A9A9,
    lime        = 0xFF00FF00,
    maroon      = 0xFF800000,
    navy        = 0xFF000080,
    olive       = 0xFF808000,
    teal        = 0xFF008080,
    transparent = 0x00000000
}

---@class Kernel
---@field log { debug: fun(msg: string), info: fun(msg: string), warning: fun(msg: string), error: fun(msg: string), fatal: fun(msg: string) }
---@field write fun(msg: string)
---@field read fun(): string
kernel = kernel

function error(msg, lvl) kernel.log.error("Error ("..lvl.."): "..msg) end

kernel.log.info "Hello, World from init.lua!"
kernel.log.warning "See how the line integer and file is showing!"
kernel.log.error "This is an error!"
kernel.log.info "Showing the canvas"

local canvas = kernel.framebuffer.create()
local x, y = canvas:get_dimensions()
canvas:set_pitch(x)

-- Boxes of every colour
local i = 0
for k, v in pairs(colours) do
    canvas:draw_rect(x - 64, i * 64, 64, 64, v)
    i = i + 1
end

kernel.log.debug("Canvas dimensions: ("..x..", "..y..")")

while true do
    kernel.write "> "
    local line = kernel.read()
    if line:sub(1, 1) == '=' then
        line = "kernel.log.info(tostring("..line:sub(2).."))"
    end
    local fn, err = loadstring(line, "REPL")
    if not fn then kernel.log.error(err); goto continue end
    local ok, err = pcall(fn)
    if ok then
        kernel.log.debug "\x1b[32mOk\x1b[0m"
    else
        kernel.log.error("\x1b[31m"..err.."\x1b[0m")
    end

    ::continue::
end

