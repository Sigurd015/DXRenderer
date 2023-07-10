#pragma once
#include <Windows.h>
#include <comdef.h>
#include <d3d11.h>
#include <d3dcompiler.h>

namespace DXC
{
	void CheckD3DError(HRESULT result);
}

#ifdef DXR_DEBUG
#define DX_CHECK_RESULT(x) { HRESULT __hr = x;CheckD3DError(__hr);}
#else
#define DX_CHECK_RESULT(x) x
#endif