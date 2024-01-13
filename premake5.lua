-- premake5.lua

workspace "zivline"
    configurations { "Release" }

    SRCDIR = "src"
    RESDIR = "resources"
    BUILD_DIR = "build"

    project "zivline"
        kind "ConsoleApp"
        language "C"
        targetdir (BUILD_DIR)
        files {SRCDIR .. "/*.c", RESDIR .. "/*.rc"}

        filter "configurations:Release"
            links { "dbghelp" }
            optimize "On"
            postbuildcommands {
                'echo Compiling resources...',
                'windres ' .. RESDIR .. '/res.rc -O coff -o ' .. BUILD_DIR .. '/res.res',
                BUILD_DIR .. '\\zivline.exe'
            }

        filter {}


        

        
        
