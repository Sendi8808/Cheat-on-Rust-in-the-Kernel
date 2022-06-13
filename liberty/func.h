#pragma once
void OprionsFunc() {
	auto Movement = BasePlayer_c->movement();
	if (true) { // admin esp
		Oclusion->OcclusionCulling()->Static()->_debugShow() = (int)DebugFilter::Dynamic;
		Oclusion->OcclusionCulling()->Static()->jumpSettings()->debugSettings()->layerFilter() = 131072;
	}
	if (true) { // Sky
		auto p_TOD_Sky = TOD->TodSyTypeInfo()->static_fields()->instances()->List()->p_TOD_Sky();
		p_TOD_Sky->Cycle()->Hour() = 14;
		//p_TOD_Sky->night()->AmbientMultiplier() = 4;
		//p_TOD_Sky->night()->ReflectionMultiplier() = 1.5;
	}
	if (true) { //spider man
		Movement->capsule() = 0;
	}
	if (true) {//infinitihump
		Movement->jumpTime() = 0;
		Movement->landTime() = 0;
		Movement->groundTime() = 1000;
	}
	if (true) {//Fov
		Graphics->ConVar()->Static()->_fov() = 120;
	}
}
void Func() {
	while (true) {
		pointers.p_Player = P_player->LocalPlayer()->p_Static()->p_null();
		OprionsFunc();
	}
}