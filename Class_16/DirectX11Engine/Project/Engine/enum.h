#pragma once


enum class ASSET_TYPE
{
	PREFAB,
	MESH,
	MESH_DATA,
	MATERIAL,
	TEXTURE,
	SOUND,
	GRAPHICS_SHADER,
	COMPUTE_SHADER,

	END,
};

enum class CB_TYPE
{
	TRANSFORM,
	MATERIAL,
	ANIMATION,
	GLOBAL,
	END,
};