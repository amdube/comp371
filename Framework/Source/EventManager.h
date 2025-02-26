//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#pragma once
struct GLFWwindow;
#include <vector>;
#include <cstring>;

class EventManager
{
public:
	static void Initialize();
	static void Shutdown();

	static void Update();

	static float GetFrameTime();
	static bool ExitRequested();

	static GLFWwindow* GetWindow();

	static float GetMouseMotionX();
	static float GetMouseMotionY();
	static float GetCurrentVolume();
	static float* GetCurrentSpec();

	static void EnableMouseCursor();
	static void DisableMouseCursor();

	static float GetRandomFloat(float min, float max);
	static void LoadMusicFileNames();
	static void PlayNextSong();

private:
	static std::vector<std::string> filenames;

	// Time
	static double sLastFrameTime;
	static float sFrameTime;

	// Mouse
	static double sLastMousePositionX;
	static float  sMouseDeltaX;
	static double sLastMousePositionY;
	static float  sMouseDeltaY;

	// Window
	static GLFWwindow* spWindow;
};

