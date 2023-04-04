require "export-compile-commands"

workspace("cp-boii")
	configurations({ "Debug", "Release" })
	filter("configurations:Debug")
		defines({ "DEBUG" })
		symbols("On")
	filter("configurations:Release")
		defines({ "NDEBUG", "O3" })
		optimize("On")
	filter({})
	targetdir("bin/%{cfg.buildcfg}/")

	-- CP Boii
	project("cp-boii")
		kind("ConsoleApp")
		language("C++")
		includedirs({
			"include",
			"memsafe-boii",
			"log-boii",
			"SDL2/include",
			"SDL2_ttf/include",
			"tinyfiledialogs",
			"C:/msys64/mingw64/include",
			"C:/msys64/mingw32/include",
		})
		files({
			"src/*.cpp",
			"memsafe-boii/memsafe_boii.c",
			"log-boii/log_boii.c",
			"tinyfiledialogs/tinyfiledialogs.c",
		})
		removefiles { "src/main.cpp" }
		filter({ "system:windows" })
			links({
				"SDL2main",
				"SDL2",
				"SDL2_ttf",
				"comdlg32",
				"ole32",
			})
			libdirs({ "SDL2/lib", "SDL2_ttf/lib" })
		filter({ "system:linux" })
			links({ "SDL2main", "SDL2", "SDL2_ttf" })
		filter({ "system:macos" })
			links({ "SDL2main", "SDL2", "SDL2_ttf" })
