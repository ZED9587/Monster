#pragma once
#ifndef ANTERU_D3D12_SAMPLE_D3D12SAMPLE_H_
#define ANTERU_D3D12_SAMPLE_D3D12SAMPLE_H_

#include <d3d12.h>
#include <dxgi.h>
#include <wrl.h>
#include <memory>

class Window;

///////////////////////////////////////////////////////////////////////////////
class D3D12Ex
{
public:
	D3D12Ex(const D3D12Ex&) = delete;
	D3D12Ex& operator= (const D3D12Ex&) = delete;

	D3D12Ex();
	virtual ~D3D12Ex();

	void Run(const int frameCount);

protected:
	int GetQueueSlot() const
	{
		return currentBackBuffer_;
	}

	static const int QUEUE_SLOT_COUNT = 3;

	static constexpr int GetQueueSlotCount()
	{
		return QUEUE_SLOT_COUNT;
	}

	D3D12_VIEWPORT viewport_;
	D3D12_RECT rectScissor_;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain_;
	Microsoft::WRL::ComPtr<ID3D12Device> device_;
	Microsoft::WRL::ComPtr<ID3D12Resource> renderTargets_[QUEUE_SLOT_COUNT];
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_;

	HANDLE frameFenceEvents_[QUEUE_SLOT_COUNT];
	Microsoft::WRL::ComPtr<ID3D12Fence> frameFences_[QUEUE_SLOT_COUNT];
	UINT64 currentFenceValue_;
	UINT64 fenceValues_[QUEUE_SLOT_COUNT];

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> renderTargetDescriptorHeap_;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pso_;

	virtual void InitializeImpl(ID3D12GraphicsCommandList* uploadCommandList);
	virtual void RenderImpl(ID3D12GraphicsCommandList* commandList);

private:
	void Initialize();
	void Shutdown();

	void PrepareRender();
	void FinalizeRender();

	void Render();
	void Present();

	void CreateDeviceAndSwapChain();
	void CreateAllocatorsAndCommandLists();
	void CreateViewportScissor();
	void CreatePipelineStateObject();
	void SetupSwapChain();
	void SetupRenderTargets();

	std::unique_ptr<Window> window_;

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocators_[QUEUE_SLOT_COUNT];
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandLists_[QUEUE_SLOT_COUNT];

	int currentBackBuffer_ = 0;

	std::int32_t renderTargetViewDescriptorSize_;
};

#endif
