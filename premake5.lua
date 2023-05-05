workspace "LearnOpenGL"
	architecture "x86_64"
	startproject "Test"

	configurations
	{
		"Debug",
		"Release"
	}

int_dir = "%{wks.location}/bin/int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
out_dir = "%{wks.location}/bin/out/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Vendors/Glad"
	include "Vendors/GLFW"
group ""

include "Engine/"
include "Test/"