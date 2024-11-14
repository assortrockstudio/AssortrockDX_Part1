#pragma once

// 정점
// 3D 공간의 좌표를 나타내는 단위 
struct Vtx
{	
	Vec3	vPos;
	Vec4	vColor;		
};


// 상수버퍼 관련 구조체
struct tTransform
{
	Vec4 Position;
	Vec4 Scale;
};