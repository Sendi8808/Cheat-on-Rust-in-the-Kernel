#pragma once

class p_ConVar_Graphics {
public:
	p_ConVar_Graphics* ConVar() {
		return *reinterpret_cast<p_ConVar_Graphics**>((ull)GameAssembly + 52531944);//
	}
	p_ConVar_Graphics* Static() {
		return *reinterpret_cast<p_ConVar_Graphics**>(this + 0xb8);
	}
	float& _fov() {
		return *reinterpret_cast<float*>(this + 0x18);
	}
};