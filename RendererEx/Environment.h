#pragma once

#include <dxgi1_4.h>
#include "d3dx12.h"
#include <wrl.h>
#include <iostream>
#include <d3d12.h>
#include <dxgi.h>

using namespace Microsoft::WRL;

class Envionment
{
public:
	Envionment();
	~Envionment();

private:

};

Envionment::Envionment()
{
}

Envionment::~Envionment()
{
}

struct RenderEnvironment
{
	ComPtr<ID3D12Device> device;
	ComPtr<ID3D12CommandQueue> queue;
	ComPtr<IDXGISwapChain> swapChain;
};

///////////////////////////////////////////////////////////////////////////////
/**
Create everything we need for rendering, this includes a device, a command queue,
and a swap chain.
*/
RenderEnvironment CreateDeviceAndSwapChainHelper(
	_In_opt_ IDXGIAdapter* adapter,
	D3D_FEATURE_LEVEL minimumFeatureLevel,
	_In_ const DXGI_SWAP_CHAIN_DESC* swapChainDesc)
{
	RenderEnvironment result;

	auto hr = D3D12CreateDevice(adapter, minimumFeatureLevel,
		IID_PPV_ARGS(&result.device));

	if (FAILED(hr)) {
		throw std::runtime_error("Device creation failed.");
	}

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	hr = result.device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&result.queue));

	if (FAILED(hr)) {
		throw std::runtime_error("Command queue creation failed.");
	}

	ComPtr<IDXGIFactory4> dxgiFactory;
	hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));

	if (FAILED(hr)) {
		throw std::runtime_error("DXGI factory creation failed.");
	}

	// Must copy into non-const space
	DXGI_SWAP_CHAIN_DESC swapChainDescCopy = *swapChainDesc;
	hr = dxgiFactory->CreateSwapChain(
		result.queue.Get(),
		&swapChainDescCopy,
		&result.swapChain
	);

	if (FAILED(hr)) {
		throw std::runtime_error("Swap chain creation failed.");
	}

	return result;
}
