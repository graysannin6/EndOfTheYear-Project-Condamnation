#pragma once

#pragma warning(disable: 4251)

#ifdef RENDERING_CONTEXT
#define API_RENDERING __declspec(dllexport)
#else
#define API_RENDERING __declspec(dllimport)
#endif