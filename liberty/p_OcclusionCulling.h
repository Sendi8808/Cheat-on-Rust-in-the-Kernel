#pragma once


class OcclusionCulling_c {
public:
	OcclusionCulling_c* OcclusionCulling() {
		return *reinterpret_cast<OcclusionCulling_c**>((ull)GameAssembly + 52530664);// 
	}
	OcclusionCulling_c* Static() {
		return *reinterpret_cast<OcclusionCulling_c**>(this + 0xb8);
	}
	OcclusionCulling_c* debugSettings() {
		return *reinterpret_cast<OcclusionCulling_c**>(this + 0x18);
	}
	OcclusionCulling_c* jumpSettings() {
		return *reinterpret_cast<OcclusionCulling_c**>(this + 0x80);
	}

	
	int& layerFilter() {
		return *reinterpret_cast<int*>(this + 0x20);
	}

	int& _debugShow() {
		return *reinterpret_cast<int*>(this + 0x94);
	}
};