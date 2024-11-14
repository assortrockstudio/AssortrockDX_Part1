#ifndef _STD2D
#define _STD2D

cbuffer TRANSFORM : register(b0)
{
    float4 g_Position;
    float4 g_Scale;
};


struct VS_IN
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    output.vPosition = float4((_in.vPos * g_Scale.xyz) + g_Position.xyz, 1.f);
    output.vColor = _in.vColor;
    
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{    
    return _in.vColor;
}

#endif