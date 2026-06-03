
struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
};


float4 mainPS(PS_INPUT input) : SV_TARGET
{
    return input.col;
}