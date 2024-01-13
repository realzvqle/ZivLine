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
                "$(TargetDir)zivline.exe"                
            }

        filter {}

        

        
        
