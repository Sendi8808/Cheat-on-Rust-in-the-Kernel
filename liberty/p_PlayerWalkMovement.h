#pragma once
class PlayerWalkMovement {
public:
	float& capsule() {
		return *reinterpret_cast<float*>(this + 0xB0);
	}
	float& jumpTime() {
		return *reinterpret_cast<float*>(this + 0xD0);
	}
	float& landTime() {
		return *reinterpret_cast<float*>(this + 0xD4);
	}
	float& groundTime() {
		return *reinterpret_cast<float*>(this + 0xCC);
	}

};
