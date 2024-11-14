#ifndef _STD2D
#define _STD2D


struct VS_IN
{
    float3 vPos : POSITION;    
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    output.vPosition = float4(_in.vPos, 1.f);   
    
    return output;
}







#endif