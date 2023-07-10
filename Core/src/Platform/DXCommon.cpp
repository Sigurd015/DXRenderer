#include "pch.h"

namespace DXC
{
	void CheckD3DError(HRESULT result)
	{
		if (result == S_OK)
			return;

		switch (result)
		{
		case D3D11_ERROR_FILE_NOT_FOUND:
			DXC_ASSERT(false);
			break;
		case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS:
			DXC_ASSERT(false);
			break;
		case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS:
			DXC_ASSERT(false);
			break;
		case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD:
			DXC_ASSERT(false);
			break;
		case DXGI_ERROR_INVALID_CALL:
			DXC_ASSERT(false);
			break;
		case DXGI_ERROR_WAS_STILL_DRAWING:
			DXC_ASSERT(false);
			break;
		case E_FAIL:
			DXC_ASSERT(false);
			break;
		case E_INVALIDARG:
			DXC_ASSERT(false);
			break;
		case E_OUTOFMEMORY:
			DXC_ASSERT(false);
			break;
		case E_NOTIMPL:
			DXC_ASSERT(false);
			break;
		case S_FALSE:
			DXC_ASSERT(false);
			break;
		}
	}
}