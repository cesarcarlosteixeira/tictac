add_rules("mode.debug", "mode.release")
set_warnings("all", "error")
set_languages("c23")
set_optimize("fastest")
add_includedirs("src/include/")
add_files("src/*.c")

target("tic")
    if (is_mode("debug")) then
        add_defines("DEBUG")
        set_optimize("none")
    end
        
    set_kind("binary")
    add_files("src/exe/main.c")
    add_files("src/*.c")


target("tictac")
   set_kind("shared")
