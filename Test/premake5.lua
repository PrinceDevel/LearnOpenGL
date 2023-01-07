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
		"../Engine/src",
		"res",	
        
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
		defines "RB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RB_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RB_DIST"
		runtime "Release"
		optimize "on"

