#pragma once
class p_LocalPlayer {
public:
	p_LocalPlayer* LocalPlayer() {
		return *reinterpret_cast<p_LocalPlayer**>((ull)GameAssembly + 52535504);
	}
	p_LocalPlayer* p_Static() {
		return *reinterpret_cast<p_LocalPlayer**>(this + 0xb8);
	}
	ull p_null() {
		return *reinterpret_cast<ull*>(this);
	}
};