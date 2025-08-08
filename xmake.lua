add_rules("mode.debug", "mode.release")
set_warnings("all", "error")
set_languages("c23")

target("tic")
    if (is_mode("debug")) then
        add_defines("DEBUG")
        set_optimize("none")
    end
      
    set_kind("binary")
    add_files("src/exe/main.c")


target("tictac")
   set_optimize("fastest")
   set_kind("shared")
   add_files("src/*.c")
   add_includedirs("src/include", { public = true})
