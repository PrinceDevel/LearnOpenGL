project "Test"

	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	systemversion "latest"

	targetdir   ("%{wks.location}/bin/out/" .. binary_dir .. "/%{prj.name}")
	objdir      ("%{wks.location}/bin/int/" .. binary_dir .. "/%{prj.name}")

	files {
        "src/**.h",
		"src/**.c",
		"src/**.hpp",
		"src/**.cpp",

		"res/**.*"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs {
		"src",
		"res",
		"../Engine/src",
        
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

	filter "configurations:Dist"
		defines "_CONFIG_DIST"
		runtime "Release"
		optimize "on"

