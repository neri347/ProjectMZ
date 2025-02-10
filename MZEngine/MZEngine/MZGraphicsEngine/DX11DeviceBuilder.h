#pragma once
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <wrl.h>

namespace MZGraphics
{
	class DX11DeviceBuilder
	{
	public:
		DX11DeviceBuilder(HWND hWnd, UINT screenWidth, UINT screenHeight);
		~DX11DeviceBuilder();

		ID3D11Device* GetDevice() const;
		ID3D11DeviceContext* GetDeviceContext() const;
		IDXGISwapChain* GetSwapChain() const;
		ID3D11RenderTargetView* GetRTV() const;

		void ResizeBackbuffer(UINT width, UINT height);
		void ClearBackbuffer(const float color[4]);

	private:
		HWND _hWnd;
		UINT _screenWidth;
		UINT _screenHeight;

	private:
		// DX 초기화 관련
		Microsoft::WRL::ComPtr<ID3D11Device> _device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _deviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _backbuffer;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView;
	};
}