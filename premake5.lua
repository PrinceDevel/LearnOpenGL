workspace "RageEngine"
	architecture "x86_64"
	startproject "Test"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

binary_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Vendors/Glad"
	include "Vendors/GLFW"
group ""

include "Engine/"
include "Test/"