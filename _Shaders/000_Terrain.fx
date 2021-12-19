Texture2D BaseMap;
Texture2D LayerMap;
Texture2D AlphaMap;

struct BrushDesc
{
    float4 Color;
    float3 Location;
    uint Type;
    uint Range;
};

cbuffer CB_TerrainBrush
{
    BrushDesc TerrainBrush;
};

float3 GetBrushColor(float3 wPosition)
{
    [flatten]
    if(TerrainBrush.Type==0)
        return float3(0, 0, 0);
    
    [flatten]
    if(TerrainBrush.Type==1)
    {
        if ((wPosition.x >= (TerrainBrush.Location.x - TerrainBrush.Range)) &&
            (wPosition.x <= (TerrainBrush.Location.x + TerrainBrush.Range)) &&
            (wPosition.z >= (TerrainBrush.Location.z - TerrainBrush.Range)) &&
            (wPosition.z <= (TerrainBrush.Location.z + TerrainBrush.Range)))
        {
            return TerrainBrush.Color;
        }
    }
    
    [flatten]
    if (TerrainBrush.Type == 2)
    {
        float dx = wPosition.x - TerrainBrush.Location.x;
        float dz = wPosition.z - TerrainBrush.Location.z;
        
        float dist = sqrt(dx * dx + dz * dz);
        
        [flatten]
        if(dist<=TerrainBrush.Range)
            return TerrainBrush.Color;
    }
    return float3(0, 0, 0);
}

cbuffer CB_GridLine
{
    float4 GridLineColor;
    uint VisibleGridLine;
    float GridLineThickness;
    float GridLineSize;
};

float3 GetLineColor(float3 wPosition)
{
    [flatten]
    if (VisibleGridLine < 1)
        return float3(0, 0, 0);
    
    float2 grid = wPosition.xz / GridLineSize;
    float2 range = abs(frac(grid - 0.5) - 0.5);
    float2 speed = fwidth(grid);
    
    float2 pixel = range / speed;
    float thick = saturate(min(pixel.x, pixel.y)) - GridLineThickness;
    return lerp(GridLineColor.rgb, float3(0, 0, 0), thick);
    
    return float3(0, 0, 0);
};

float4 GetTerrainColor(float2 uv)
{
    float4 base = BaseMap.Sample(LinearSampler, uv);
    float4 layer = LayerMap.Sample(LinearSampler, uv);
    float4 alpha = AlphaMap.Sample(LinearSampler, uv).r;
    return lerp(base, layer, alpha);//선형보간
}