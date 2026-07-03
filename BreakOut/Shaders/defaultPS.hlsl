
struct PS_INPUT
{
    float4 posProj : SV_POSITION;
    float4 posWord : POSITION;
    float4 col : COLOR;
};


float4 mainPS(PS_INPUT input) : SV_TARGET
{
    return float4(1.0f, 1.0f, 0.0f, 1.0f);
}