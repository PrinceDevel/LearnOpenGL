project "Engine"

	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir   (out_dir .. "/%{prj.name}")
	objdir      (int_dir .. "/%{prj.name}")

	pchheader "precompiled.hpp"
	pchsource "source/precompiled.cpp"

	files {
        "source/**.h",
        "source/**.c",
		"source/**.hpp",
		"source/**.cpp",
	
        "../Vendors/glm/glm/**.hpp",
		"../Vendors/glm/glm/**.inl"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs {
		"source",
        
		"../Vendors/GLFW/include",
		"../Vendors/Glad/include",
		"../Vendors/FileSystem/FileSystem/include",
		"../Vendors/glm"
	}

	filter "configurations:Debug"
		defines "_CONFIG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "_CONFIG_RELEASE"
		runtime "Release"
		optimize "on"


