project "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++11"

	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"src",
	}

	filter "system:windows"
		systemversion "latest"

	filter {"configurations:Debug"}
		defines {"DEBUG"}
		symbols "On"

	filter {"configurations:Release"}
		defines {"NDEBUG"}
		optimize "On"