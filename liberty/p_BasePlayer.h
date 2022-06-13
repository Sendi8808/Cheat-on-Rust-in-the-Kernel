#pragma once
class BasePlayer {
public:
	PlayerWalkMovement* movement() {
		return *reinterpret_cast<PlayerWalkMovement**>(pointers.p_Player + 0x4F0);
	}
};