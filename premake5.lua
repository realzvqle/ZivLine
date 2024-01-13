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
                "$(TargetDir)zivline.exe"                -- Replace with the actual name of your executable
            }

        filter {}

        

        
        
