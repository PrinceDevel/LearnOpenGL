project "Engine"

	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir   ("%{wks.location}/bin/out/" .. binary_dir .. "/%{prj.name}")
	objdir      ("%{wks.location}/bin/int/" .. binary_dir .. "/%{prj.name}")

	pchheader "rbpch.hpp"
	pchsource "src/rbpch.cpp"

	files {
        "src/**.h",
        "src/**.c",
		"src/**.hpp",
		"src/**.cpp",
	
        "../Vendors/glm/glm/**.hpp",
		"../Vendors/glm/glm/**.inl"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs {
		"src",
        
		"../Vendors/GLFW/include",
		"../Vendors/Glad/include",
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

	filter "configurations:Dist"
		defines "_CONFIG_DIST"
		runtime "Release"
		optimize "on"


