matrix World;
matrix View;
matrix Projection;
float3 Direction = float3(-1, -1, 1);

struct VertexInput
{
    float4 Position : Position0;
    float3 Normal : Normal0;
};

struct VertexOutput
{
    float4 Position : SV_Position0;
    float3 Normal : Normal0;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    output.Normal = mul(input.Normal, (float3x3) World);
    
    return output;
}
SamplerState Sampler;

float4 PS(VertexOutput input) : SV_Target0
{
    float4 diffuse = float4(1, 1, 1, 1);
    //float3 Direction = float3(-1, -1, 1);
    float3 normal = normalize(input.Normal);
    float NdotL = saturate(dot(normal, -Direction));
    
    return diffuse * NdotL;
}

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}