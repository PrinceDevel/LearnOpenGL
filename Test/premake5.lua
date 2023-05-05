project "Test"

	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	systemversion "latest"

	targetdir   (out_dir .. "/%{prj.name}")
	objdir      (int_dir .. "/%{prj.name}")

	files {
        "source/**.h",
		"source/**.c",
		"source/**.hpp",
		"source/**.cpp",

		"resource/**.*"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs {
		"source",
		"resource",
		"../Engine/source",
        
		"../Vendors/GLFW/include",
		"../Vendors/Glad/include",
		"../Vendors/glm"
	}

    links {
		"Glad",
		"GLFW",
        "Engine"
    }

	filter "system:windows"
        links {
            "gdi32",
            "user32",
            "opengl32"
        }
    
    filter "system:linux" 
        links {
            "OpenGL",
            "dl",
            "pthread"
        }

	filter "configurations:Debug"
		defines "_CONFIG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "_CONFIG_RELEASE"
		runtime "Release"
		optimize "on"

