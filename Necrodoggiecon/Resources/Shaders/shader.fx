//--------------------------------------------------------------------------------------
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// the lighting equations in this code have been taken from https://www.3dgep.com/texturing-lighting-directx-11/
// with some modifications by David White

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
	float4 vOutputColor;
}

Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

struct _Material
{
	bool    UseTexture;     // 4 bytes
	float3  padding1;       // 12 bytes
							//----------------------------------- (16 byte boundary)

	uint2	textureSize;	// 8 bytes
	uint2	textureRect;	// 8 bytes
							//----------------------------------- (16 byte boundary)

	float2	textureOffset;	// 8 bytes
	float2	padding2;		// 8 bytes
							//----------------------------------- (16 byte boundary)
	
	float4	tint;			// 16 bytes
							//----------------------------------- (16 byte boundary)

};

cbuffer MaterialProperties : register(b1)
{
	_Material Material;
};

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
	float4 worldPos : POSITION;
	float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul( input.Pos, World );
	output.worldPos = output.Pos;
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );

	output.Tex = input.Tex;
    
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT IN) : SV_TARGET
{
	float4 texColor = { 1, 1, 1, 1 };

	float2 texSampleOffset = float2(Material.textureRect) / float2(Material.textureSize);
	float2 texOffset = Material.textureOffset / float2(Material.textureRect);

	if (Material.UseTexture)
	{
		texColor = txDiffuse.Sample(samLinear, (IN.Tex + texOffset) * texSampleOffset);
        if (texColor.a <= 0.0f) discard;
    }
	
	float4 finalColor = saturate(texColor + Material.tint);

	return finalColor;
}

//--------------------------------------------------------------------------------------
// PSSolid - render a solid color
//--------------------------------------------------------------------------------------
float4 PSSolid(PS_INPUT IN) : SV_TARGET
{
	return vOutputColor;
}
