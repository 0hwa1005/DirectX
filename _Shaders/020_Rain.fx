#include "000_Header.fx"
#include "000_Light.fx"

cbuffer CB_Rain
{
    float4 Color;
    float3 Velocity;
    float  DrawInstance;
    float3 Origin;
    float  CB_Rain_Padding;
    float3 Extent;
};

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : Uv0;
    float2 Scale : Scale0;
};

struct VertexOutput
{
    float4 Position : SV_Position0;
    float2 Uv : Uv0;
    float Alpha : Alpha0;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    
    float3 velocity = Velocity;
    velocity.xz /= input.Scale.y * 0.1f;
    
    float3 displace = Time * velocity;
    
    input.Position.xyz = Origin + (Extent + (input.Position.xyz + displace) % Extent) % Extent - (Extent * 0.5f);
    
    float4 position = WorldPosition(input.Position);
    float3 up = normalize(-velocity);
    float3 forward = position.xyz - ViewPosition();
    float3 right = normalize(cross(up, forward));
    
    position.xyz += (input.Uv.x - 0.5f) * right * input.Scale.x;
    position.xyz += (1.5f - input.Uv.y * 1.5f) * up * input.Scale.y;
    position.w = 1.0f;
    
    output.Position = ViewProjection(position);
    output.Uv = input.Uv;
    output.Alpha = 0.5f;
    
    return output;
}

float4 PS(VertexOutput input) : SV_Target0
{
    return DiffuseMap.Sample(LinearSampler, input.Uv) * Color;
}

BlendState AlphaBlend
{
    BlendEnable[0] = true;
    DestBlend[0] = INV_SRC_ALPHA;
    SrcBlend[0] = SRC_ALPHA;
    BlendOp[0] = Add;

    SrcBlendAlpha[0] = One;
    DestBlendAlpha[0] = One;
    RenderTargetWriteMask[0] = 0x0F;
};

technique11 T0
{
    P_BS_VP(P0, AlphaBlend, VS, PS)
}