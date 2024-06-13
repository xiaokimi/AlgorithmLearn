workspace "AlgorithmLearn"
	architecture "x64"
	startproject "SandBox"
	
	configurations 
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "SandBox"