matrix World;
matrix View;
matrix Projection;

Texture2D Map;

struct VertexInput
{
    float4 Position : Position0;
    float2 Uv : Uv0;
};

struct VertexOutput
{
    float4 Position : SV_Position0;
    float2 Uv : Uv0;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    output.Uv = input.Uv;
    return output;
}
SamplerState Sampler;

float4 PS(VertexOutput input) : SV_Target0
{
    return Map.Sample(Sampler, input.Uv);
}

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}