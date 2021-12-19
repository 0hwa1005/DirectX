struct LightDesc
{
    float4 Ambient;
    float4 Specular;
    float3 Direction;
    float padding;
    float3 Position;
};

cbuffer CB_Light
{
    LightDesc GlobalLight;
};

struct MaterialDesc
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
};

cbuffer CB_Material
{
    MaterialDesc Material;
};