/// Name: Generator.h
/// Version: 0.0.3-alpha
/// Description: The header file for all of my question generation scripts
/// Author: Nicolas Martens

#define _CRT_SECURE_NO_WARNINGS 1
#define _USE_MATH_DEFINES 1

#include <random>
#include <cmath>
#include <string>
#include <vector>
#include <queue>

#include <iostream>

#define DLL_EXPORT __declspec(dllexport)

#pragma execution_character_set("utf-8")

extern "C" {
	struct DLL_EXPORT question {
		const wchar_t* question;
		int answer[6];
		int optionA[6];
		int optionB[6];
		int optionC[6];
		int type;
	};

	DLL_EXPORT question create(int difficulty);
	DLL_EXPORT int clean(int buffer);
}