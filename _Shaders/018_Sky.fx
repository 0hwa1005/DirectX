#include "000_Header.fx"
#include "000_Light.fx"
#include "000_Model.fx"

cbuffer CB_Sky
{
    float4 Center;
    float4 Apex;
    float Height;
};

float4 PS(MeshOutput input) : SV_Target0
{
    return lerp(Center, Apex, input.oPosition.y * Height);
    
    float4 diffuse = DiffuseMap.Sample(LinearSampler, input.Uv);
    float3 normal = normalize(input.Normal);
    float NdotL = saturate(dot(normal, -GlobalLight.Direction));
    //return diffuse * NdotL;
    return float4(0.3f, 0.4f, 0.8f, 1.0f);
}

RasterizerState RS
{
    //FillMode = Wireframe;
    FrontCounterClockWise = true;
};

RasterizerState RS2
{
    FillMode = Wireframe;
    FrontCounterClockWise = true;
};

DepthStencilState DS
{
    DepthEnable = false;
};

technique11 T0
{
    //P_VP(P0, VS_Mesh, PS)
    P_RS_DSS_VP(P0, RS, DS, VS_Mesh, PS)
    P_RS_DSS_VP(P1, RS2, DS, VS_Mesh, PS)
}