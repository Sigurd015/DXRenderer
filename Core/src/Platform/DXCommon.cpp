#include "pch.h"

namespace DXR
{
	void CheckD3DError(HRESULT result)
	{
		if (result == S_OK)
			return;

		switch (result)
		{
		case D3D11_ERROR_FILE_NOT_FOUND:
			DXR_ASSERT(false);
			break;
		case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS:
			DXR_ASSERT(false);
			break;
		case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS:
			DXR_ASSERT(false);
			break;
		case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD:
			DXR_ASSERT(false);
			break;
		case DXGI_ERROR_INVALID_CALL:
			DXR_ASSERT(false);
			break;
		case DXGI_ERROR_WAS_STILL_DRAWING:
			DXR_ASSERT(false);
			break;
		case E_FAIL:
			DXR_ASSERT(false);
			break;
		case E_INVALIDARG:
			DXR_ASSERT(false);
			break;
		case E_OUTOFMEMORY:
			DXR_ASSERT(false);
			break;
		case E_NOTIMPL:
			DXR_ASSERT(false);
			break;
		case S_FALSE:
			DXR_ASSERT(false);
			break;
		}
	}
}