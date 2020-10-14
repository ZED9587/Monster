#pragma once
#ifndef AMD_QUAD_D3D12_SAMPLE_H_
#define AMD_QUAD_D3D12_SAMPLE_H_

#include "D3D12Ex.h"

namespace AMD {
	class D3D12Quad : public D3D12Ex
	{
	private:
		void CreateRootSignature();
		void CreatePipelineStateObject();
		void CreateMeshBuffers(ID3D12GraphicsCommandList* uploadCommandList);
		void RenderImpl(ID3D12GraphicsCommandList* commandList) override;
		void InitializeImpl(ID3D12GraphicsCommandList* uploadCommandList) override;

		Microsoft::WRL::ComPtr<ID3D12Resource> uploadBuffer_;

		Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer_;
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;

		Microsoft::WRL::ComPtr<ID3D12Resource> indexBuffer_;
		D3D12_INDEX_BUFFER_VIEW indexBufferView_;
	};
}

#endif

