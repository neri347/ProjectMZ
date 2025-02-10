#include "DX11DeviceBuilder.h"

namespace MZGraphics
{

	DX11DeviceBuilder::DX11DeviceBuilder(HWND hWnd, UINT screenWidth, UINT screenHeight)
		: _hWnd(hWnd), _screenWidth(screenWidth), _screenHeight(screenHeight)
	{
		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		// ���� ü�� ����
		DXGI_SWAP_CHAIN_DESC swapchainDesc;
		ZeroMemory(&swapchainDesc, sizeof(swapchainDesc));
		swapchainDesc.BufferDesc.Width = screenWidth;
		swapchainDesc.BufferDesc.Height = screenHeight;
		swapchainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapchainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapchainDesc.BufferDesc.RefreshRate.Denominator = 0;
		swapchainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapchainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapchainDesc.SampleDesc.Count = 1;
		swapchainDesc.SampleDesc.Quality = 0;
		swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapchainDesc.BufferCount = 1;
		swapchainDesc.OutputWindow = hWnd;
		swapchainDesc.Windowed = TRUE;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapchainDesc.Flags = 0;

		// ��ġ, ����ü�� ����
		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr, // �⺻ ����� ���
			D3D_DRIVER_TYPE_HARDWARE, // �ϵ���� ����
			nullptr,	// ����Ʈ���� ����̹� ����
			createDeviceFlags,
			nullptr, // �⺻ ��ó����
			0,
			D3D11_SDK_VERSION,
			&swapchainDesc,
			_swapChain.GetAddressOf(),
			_device.GetAddressOf(),
			nullptr,
			_deviceContext.GetAddressOf()
			);

		// �� ���۸� ���� Ÿ������ ����
		ID3D11Texture2D* pBackBuffer = nullptr;
		hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
		hr = _device->CreateRenderTargetView(pBackBuffer, nullptr, _renderTargetView.GetAddressOf());
		pBackBuffer->Release();

		// ���� Ÿ�� ����
		_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);

		// ����Ʈ ����
		D3D11_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = static_cast<float>(screenWidth);
		viewport.Height = static_cast<float>(screenHeight);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		_deviceContext->RSSetViewports(1, &viewport);
	}

	DX11DeviceBuilder::~DX11DeviceBuilder()
	{

	}

	ID3D11Device* DX11DeviceBuilder::GetDevice() const
	{
		return _device.Get();
	}

	ID3D11DeviceContext* DX11DeviceBuilder::GetDeviceContext() const
	{
		return _deviceContext.Get();
	}

	IDXGISwapChain* DX11DeviceBuilder::GetSwapChain() const
	{
		return _swapChain.Get();
	}

	ID3D11RenderTargetView* DX11DeviceBuilder::GetRTV() const
	{
		return _renderTargetView.Get();
	}

	void DX11DeviceBuilder::ResizeBackbuffer(UINT width, UINT height)
	{

	}

	void DX11DeviceBuilder::ClearBackbuffer(const float color[4])
	{

	}

}