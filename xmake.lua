local compiler = {
    windows = "msvc", -- or clang-cl
    linux = "gcc",
    macosx = "clang",
}
local arch = {
    arch = os.arch()
}

add_rules("mode.debug", "mode.release")

add_requires("toml++")
add_requires("termcolor")

target("juamp")
    set_kind("binary")
    add_files("src/*.cpp")
    set_languages("c++17")
    add_includedirs("include")
    set_optimize("fast")
    add_packages("toml++")
    add_packages("termcolor")

if is_plat("windows") then
    set_toolchains(compiler.windows)
elseif is_plat("linux") then
    set_toolchains(compiler.linux)
elseif is_plat("macosx") then
    set_toolchains(compiler.macosx)
end

if is_arch("x64") then
    set_arch("x64")
elseif is_arch("x86") then
    set_arch("x86")
end