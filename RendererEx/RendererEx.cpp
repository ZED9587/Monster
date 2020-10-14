// RendererEx.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "RendererEx.h"
#include <iostream>
#include "D3D12Quad.h"

int WinMain(
	_In_ HINSTANCE /* hInstance */,
	_In_opt_ HINSTANCE /* hPrevInstance */,
	_In_ PSTR     /* lpCmdLine */,
	_In_ int       /* nCmdShow */
)
{
	D3D12Ex* sample = new AMD::D3D12Quad;

	if (sample == nullptr) {
		return 1;
	}

	sample->Run(512);
	delete sample;

	return 0;
}

