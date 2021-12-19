#include "000_Header.fx"
#include "000_Light.fx"
#include "000_Terrain.fx"

Texture2D BaseMap;

struct VertexOutput
{
    float4 Position : SV_Position0;
    float4 wPosition : Position1;
    float3 Normal : Normal0;
    float2 Uv : Uv0;
    //float3 Color : Color0;
};

VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
    output.Position = WorldPosition(input.Position);
    //output.Color = GetBrushColor(output.Position.xyz);
    output.wPosition = output.Position;
    output.Position = ViewProjection(output.Position);
    output.Normal = WorldNormal(input.Normal);
    output.Uv = input.Uv;
    
    return output;
}

float4 PS(VertexOutput input) : SV_Target0
{
    //return float4(input.Normal * 0.5f + 0.5f, 1);//RGBºû
    float4 diffuse = BaseMap.Sample(LinearSampler, input.Uv);
    float3 normal = normalize(input.Normal);
    float NdotL = saturate(dot(normal, -GlobalLight.Direction));
    float3 brushColor = GetBrushColor(input.wPosition.xyz);
    return diffuse * NdotL + float4(brushColor, 1);
}

RasterizerState RS
{
    FillMode = Wireframe;
};

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P1
    {
        SetRasterizerState(RS);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}