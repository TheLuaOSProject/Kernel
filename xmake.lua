includes("packages")

local packages = {

}

local sanitizers = { }

local cflags = {
    release = {},
    debug = {
        "-Wno-unused-function", "-Wno-unused-parameter", "-Wno-unused-variable"
    },
    regular = {
        "-Wall", "-Wextra", "-Werror",
    }
}

local ldflags = {
    release = {},
    debug = {},
    regular = {}
}

set_languages {
    "gnulatest"
}

set_config("plat", "cross")
set_config("arch", "x86_64")

toolchain("luaos-clang")
do
    set_kind("standalone")
    set_toolset("cc", "clang")
    set_toolset("c++", "clang++")
    set_toolset("ld", "ld.lld")
    set_toolset("as", "nasm")

    on_load(function (toolchain)
        toolchain:add("cflags", "-target", "x86_64-elf", "-mno-sse", "-mno-mmx")
    end)
end
toolchain_end()

add_rules("mode.debug", "mode.release")

add_requires(packages)

target("kernel")
do
    set_kind("binary")
    add_packages(packages)
    set_toolchains("luaos-clang")

    add_files("src/**.c")
    add_headerfiles("src/**.h")

    add_includedirs("src/", "src/include")

    add_cflags(cflags.regular)
    add_ldflags(ldflags.regular)

    if is_mode "debug" then
        add_cflags(cflags.debug)
        add_ldflags(ldflags.debug)

        for _, v in ipairs(sanitizers) do
            add_cflags("-fsanitize=" .. v)
            add_ldflags("-fsanitize=" .. v)
        end

        add_defines("PROJECT_DEBUG")
    elseif is_mode "release" then
        add_cflags(cflags.release)
        add_ldflags(ldflags.release)
    end
end
target_end()
