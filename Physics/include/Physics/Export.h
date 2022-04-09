#pragma once

#pragma warning(disable: 4251)

#ifdef PHYSICS_CONTEXT
#define API_PHYSICS __declspec(dllexport)
#else
#define API_PHYSICS __declspec(dllimport)
#endif