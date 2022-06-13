#pragma once


class weapon {
public:
	BaseProjectile* get_base_projetile() {
		return *reinterpret_cast<BaseProjectile**>((uintptr_t)this + 0x98);
	}

	bool is_weapon() {
		const auto     item_definition = *reinterpret_cast<ull*>((uintptr_t)this + 0x20);
		if (!item_definition)
			return false;

		return *reinterpret_cast<ull*>(item_definition + 0x40) == 0;
	}
	int get_item_definition_id()
	{
		const auto     item_definition = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x20);
		if (!item_definition)
			return 0;

		return *reinterpret_cast<int*>(item_definition + 0x18);
	}

};