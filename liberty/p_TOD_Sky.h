#pragma once
class TOD_SunParameters {
public:
	float& MeshSize() {
		return *reinterpret_cast<float*>(this + 0x10) ;
	}
	float& MeshBrightness() {
		return *reinterpret_cast<float*>(this + 0x14) ;
	}
	float& MeshContrast() {
		return *reinterpret_cast<float*>(this + 0x18) ;
	}
};
class TOD_CycleParameters {
public:
	float& Hour() {
		return *reinterpret_cast<float*>(this + 0x10) ;
	}
	float& Day() {
		return *reinterpret_cast<float*>(this + 0x14) ;
	}
	float& Month() {
		return *reinterpret_cast<float*>(this + 0x18) ;
	}
	float& Year() {
		return *reinterpret_cast<float*>(this + 0x1C) ;
	}
};
class TOD_NightParameters {
public:
	float& MoonColor() {
		return *reinterpret_cast<float*>(this + 0x10);
	}
	float& LightColor() {
		return *reinterpret_cast<float*>(this + 0x18) ;
	}
	float& RayColor() {
		return *reinterpret_cast<float*>(this + 0x20) ;
	}
	float& SkyColor() {
		return *reinterpret_cast<float*>(this + 0x28) ;
	}
	float& CloudColor() {
		return *reinterpret_cast<float*>(this + 0x30) ;
	}
	float& FogColor() {
		return *reinterpret_cast<float*>(this + 0x38) ;
	}
	float& AmbientColor() {
		return *reinterpret_cast<float*>(this + 0x40) ;
	}
	float& LightIntensity() {
		return *reinterpret_cast<float*>(this + 0x48) ;
	}
	float& ShadowStrength() {
		return *reinterpret_cast<float*>(this + 0x4C) ;
	}
	float& AmbientMultiplier() {
		return *reinterpret_cast<float*>(this + 0x50) ;
	}
	float& ReflectionMultiplier() {
		return *reinterpret_cast<float*>(this + 0x54) ;
	}
};
class TOD_AmbientParameters {
public:
	float& TOD_AmbientType() {
		return *reinterpret_cast<float*>(this + 0x10) ;
	}
	float& Saturation() {
		return *reinterpret_cast<float*>(this + 0x14) ;
	}
	float& UpdateInterval() {
		return *reinterpret_cast<float*>(this + 0x18) ;
	}
};
class TOD_MoonParameters {
	float& MeshSize() {
		return *reinterpret_cast<float*>(this + 0x10) ;
	}
	float& MeshBrightness() {
		return *reinterpret_cast<float*>(this + 0x14) ;
	}
	float& MeshContrast() {
		return *reinterpret_cast<float*>(this + 0x18) ;
	}
	float& HaloSize() {
		return  *reinterpret_cast<float*>(this + 0x1C) ;
	}
	float& HaloBrightness() {
		return *reinterpret_cast<float*>(this + 0x20) ;
	}
};
class TOD_StarParameters {
public:
	float& Size() {
		return *reinterpret_cast<float*>(this + 0x10) ;
	}
	float& Brightness() {
		return *reinterpret_cast<float*>(this + 0x14) ;
	}
};
class TOD_CloudParameters {
public:
	float& Size() {
		return *reinterpret_cast<float*>(this + 0x10) ;
	}
	float& Opacity() {
		return *reinterpret_cast<float*>(this + 0x14) ;
	}
	float& Coverage() {
		return *reinterpret_cast<float*>(this + 0x18) ;
	}
	float& Sharpness() {
		return *reinterpret_cast<float*>(this + 0x1C) ;
	}
	float& Coloring() {
		return *reinterpret_cast<float*>(this + 0x20) ;
	}
	float& Attenuation() {
		return *reinterpret_cast<float*>(this + 0x24) ;
	}
	float& Saturation() {
		return *reinterpret_cast<float*>(this + 0x28) ;
	}
	float& Scattering() {
		return *reinterpret_cast<float*>(this + 0x2C) ;
	}
	float& Brightness() {
		return *reinterpret_cast<float*>(this + 0x30) ;
	}
};
class TOD_Sky {
public:
	TOD_Sky* TodSyTypeInfo() {
		return *reinterpret_cast<TOD_Sky**>((ull)GameAssembly + 52540200);// TOD_Sky_TypeInfo
	}
	TOD_Sky* static_fields() {
		return  *reinterpret_cast<TOD_Sky**>(this + 0xB8);
	}
	TOD_Sky* instances() {
		return	 *reinterpret_cast<TOD_Sky**>(this);
	}
	TOD_Sky* List() {
		return *reinterpret_cast<TOD_Sky**>(this + 0x10);
	}
	TOD_Sky* p_TOD_Sky() {
		return *reinterpret_cast<TOD_Sky**>(this + 0x20);
	}
	TOD_CycleParameters* Cycle() {
		return *reinterpret_cast<TOD_CycleParameters**>(this + 0x38);
	}
	TOD_NightParameters* night() {
		return *reinterpret_cast<TOD_NightParameters**>(this + 0x58);
	}
	TOD_AmbientParameters* ambient() {
		return  *reinterpret_cast<TOD_AmbientParameters**>(this + 0x90);
	}
	TOD_SunParameters* Sun() {
		return  *reinterpret_cast<TOD_SunParameters**>(this + 0x60);
	}
	TOD_MoonParameters* Moon() {
		return  *reinterpret_cast<TOD_MoonParameters**>(this + 0x68);
	}
	TOD_StarParameters* Star() {
		return  *reinterpret_cast<TOD_StarParameters**>(this + 0x70);
	}
};