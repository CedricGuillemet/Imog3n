static const uint8_t SDF_DepthId_fs_mtl[2990] =
{
	0x46, 0x53, 0x48, 0x0b, 0x6f, 0x1e, 0x3e, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x08, 0x62, // FSH.o.><.......b
	0x6f, 0x75, 0x6e, 0x64, 0x4d, 0x69, 0x6e, 0x12, 0x01, 0x50, 0x00, 0x01, 0x00, 0x00, 0x00, 0xcc, // oundMin..P......
	0xcc, 0x0a, 0x62, 0x6f, 0x75, 0x6e, 0x64, 0x52, 0x61, 0x74, 0x69, 0x6f, 0x12, 0x01, 0x60, 0x00, // ..boundRatio..`.
	0x01, 0x00, 0x00, 0x00, 0xcc, 0xcc, 0x11, 0x53, 0x44, 0x46, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, // .......SDFSample
	0x72, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x11, 0x01, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, // rSampler........
	0xcc, 0xcc, 0x11, 0x53, 0x44, 0x46, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x54, 0x65, 0x78, // ...SDFSamplerTex
	0x74, 0x75, 0x72, 0x65, 0x11, 0x01, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0xcc, 0xcc, 0x09, 0x76, // ture...........v
	0x69, 0x65, 0x77, 0x49, 0x6e, 0x66, 0x6f, 0x73, 0x12, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // iewInfos........
	0xcc, 0xcc, 0x0a, 0x63, 0x61, 0x6d, 0x65, 0x72, 0x61, 0x56, 0x69, 0x65, 0x77, 0x14, 0x01, 0x10, // ...cameraView...
	0x00, 0x04, 0x00, 0x00, 0x00, 0xcc, 0xcc, 0x0a, 0x53, 0x44, 0x46, 0x53, 0x61, 0x6d, 0x70, 0x6c, // ........SDFSampl
	0x65, 0x72, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcc, 0xcc, 0xfa, 0x0a, 0x00, 0x00, // er..............
	0x23, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64, 0x65, 0x20, 0x3c, 0x6d, 0x65, 0x74, 0x61, 0x6c, 0x5f, // #include <metal_
	0x73, 0x74, 0x64, 0x6c, 0x69, 0x62, 0x3e, 0x0a, 0x23, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64, 0x65, // stdlib>.#include
	0x20, 0x3c, 0x73, 0x69, 0x6d, 0x64, 0x2f, 0x73, 0x69, 0x6d, 0x64, 0x2e, 0x68, 0x3e, 0x0a, 0x0a, //  <simd/simd.h>..
	0x75, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, 0x65, 0x20, // using namespace 
	0x6d, 0x65, 0x74, 0x61, 0x6c, 0x3b, 0x0a, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x5f, // metal;..struct _
	0x47, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, // Global.{.    flo
	0x61, 0x74, 0x34, 0x20, 0x76, 0x69, 0x65, 0x77, 0x49, 0x6e, 0x66, 0x6f, 0x73, 0x3b, 0x0a, 0x20, // at4 viewInfos;. 
	0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x78, 0x34, 0x20, 0x63, 0x61, 0x6d, 0x65, //    float4x4 came
	0x72, 0x61, 0x56, 0x69, 0x65, 0x77, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, // raView;.    floa
	0x74, 0x34, 0x20, 0x62, 0x6f, 0x75, 0x6e, 0x64, 0x4d, 0x69, 0x6e, 0x3b, 0x0a, 0x20, 0x20, 0x20, // t4 boundMin;.   
	0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x62, 0x6f, 0x75, 0x6e, 0x64, 0x52, 0x61, 0x74, //  float4 boundRat
	0x69, 0x6f, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x0a, 0x63, 0x6f, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x74, // io;.};..constant
	0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x32, 0x20, 0x5f, 0x37, 0x32, 0x36, 0x20, 0x3d, 0x20, 0x7b, //  float2 _726 = {
	0x7d, 0x3b, 0x0a, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, // };..struct xlatM
	0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, // tlMain_out.{.   
	0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, //  float4 bgfx_Fra
	0x67, 0x44, 0x61, 0x74, 0x61, 0x30, 0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x30, // gData0 [[color(0
	0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, // )]];.};..struct 
	0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x69, 0x6e, 0x0a, 0x7b, // xlatMtlMain_in.{
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x32, 0x20, 0x76, 0x5f, 0x74, 0x65, // .    float2 v_te
	0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x20, 0x5b, 0x5b, 0x75, 0x73, 0x65, 0x72, 0x28, 0x6c, // xcoord0 [[user(l
	0x6f, 0x63, 0x6e, 0x30, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x0a, 0x66, 0x72, 0x61, // ocn0)]];.};..fra
	0x67, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, // gment xlatMtlMai
	0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, // n_out xlatMtlMai
	0x6e, 0x28, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x69, 0x6e, // n(xlatMtlMain_in
	0x20, 0x69, 0x6e, 0x20, 0x5b, 0x5b, 0x73, 0x74, 0x61, 0x67, 0x65, 0x5f, 0x69, 0x6e, 0x5d, 0x5d, //  in [[stage_in]]
	0x2c, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x74, 0x20, 0x5f, 0x47, 0x6c, 0x6f, 0x62, // , constant _Glob
	0x61, 0x6c, 0x26, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x20, 0x5b, 0x5b, 0x62, 0x75, 0x66, // al& _mtl_u [[buf
	0x66, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x2c, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, // fer(0)]], textur
	0x65, 0x33, 0x64, 0x3c, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x3e, 0x20, 0x53, 0x44, 0x46, 0x53, 0x61, // e3d<float> SDFSa
	0x6d, 0x70, 0x6c, 0x65, 0x72, 0x20, 0x5b, 0x5b, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x28, // mpler [[texture(
	0x30, 0x29, 0x5d, 0x5d, 0x2c, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x20, 0x53, 0x44, // 0)]], sampler SD
	0x46, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x20, // FSamplerSampler 
	0x5b, 0x5b, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x29, 0x0a, // [[sampler(0)]]).
	0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, // {.    xlatMtlMai
	0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x20, 0x6f, 0x75, 0x74, 0x20, 0x3d, 0x20, 0x7b, 0x7d, 0x3b, 0x0a, // n_out out = {};.
	0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x33, 0x20, 0x5f, 0x33, 0x37, 0x32, 0x20, //     float3 _372 
	0x3d, 0x20, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x63, 0x61, 0x6d, 0x65, 0x72, 0x61, // = (_mtl_u.camera
	0x56, 0x69, 0x65, 0x77, 0x20, 0x2a, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x28, 0x30, 0x2e, // View * float4(0.
	0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, // 0, 0.0, 0.0, 1.0
	0x29, 0x29, 0x2e, 0x78, 0x79, 0x7a, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, // )).xyz;.    floa
	0x74, 0x33, 0x20, 0x5f, 0x33, 0x39, 0x32, 0x20, 0x3d, 0x20, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, // t3 _392 = (_mtl_
	0x75, 0x2e, 0x63, 0x61, 0x6d, 0x65, 0x72, 0x61, 0x56, 0x69, 0x65, 0x77, 0x20, 0x2a, 0x20, 0x66, // u.cameraView * f
	0x6c, 0x6f, 0x61, 0x74, 0x34, 0x28, 0x6e, 0x6f, 0x72, 0x6d, 0x61, 0x6c, 0x69, 0x7a, 0x65, 0x28, // loat4(normalize(
	0x66, 0x6c, 0x6f, 0x61, 0x74, 0x33, 0x28, 0x28, 0x28, 0x31, 0x2e, 0x30, 0x20, 0x2d, 0x20, 0x69, // float3(((1.0 - i
	0x6e, 0x2e, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x2e, 0x78, 0x29, // n.v_texcoord0.x)
	0x20, 0x2a, 0x20, 0x32, 0x2e, 0x30, 0x29, 0x20, 0x2d, 0x20, 0x31, 0x2e, 0x30, 0x2c, 0x20, 0x28, //  * 2.0) - 1.0, (
	0x30, 0x2e, 0x35, 0x20, 0x2d, 0x20, 0x69, 0x6e, 0x2e, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, // 0.5 - in.v_texco
	0x6f, 0x72, 0x64, 0x30, 0x2e, 0x79, 0x29, 0x20, 0x2a, 0x20, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, // ord0.y) * (_mtl_
	0x75, 0x2e, 0x76, 0x69, 0x65, 0x77, 0x49, 0x6e, 0x66, 0x6f, 0x73, 0x2e, 0x78, 0x20, 0x2a, 0x20, // u.viewInfos.x * 
	0x32, 0x2e, 0x30, 0x29, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x29, 0x2c, 0x20, 0x30, 0x2e, 0x30, // 2.0), 1.0)), 0.0
	0x29, 0x29, 0x2e, 0x78, 0x79, 0x7a, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, // )).xyz;.    floa
	0x74, 0x32, 0x20, 0x5f, 0x37, 0x32, 0x33, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x64, 0x6f, 0x0a, // t2 _723;.    do.
	0x20, 0x20, 0x20, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, //     {.        fl
	0x6f, 0x61, 0x74, 0x33, 0x20, 0x5f, 0x34, 0x38, 0x36, 0x20, 0x3d, 0x20, 0x61, 0x62, 0x73, 0x28, // oat3 _486 = abs(
	0x28, 0x28, 0x5f, 0x33, 0x37, 0x32, 0x20, 0x2d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, // ((_372 - _mtl_u.
	0x62, 0x6f, 0x75, 0x6e, 0x64, 0x4d, 0x69, 0x6e, 0x2e, 0x78, 0x79, 0x7a, 0x29, 0x20, 0x2a, 0x20, // boundMin.xyz) * 
	0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x6f, 0x75, 0x6e, 0x64, 0x52, 0x61, 0x74, 0x69, // _mtl_u.boundRati
	0x6f, 0x2e, 0x78, 0x79, 0x7a, 0x29, 0x20, 0x2d, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x33, 0x28, // o.xyz) - float3(
	0x30, 0x2e, 0x35, 0x29, 0x29, 0x20, 0x2d, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x33, 0x28, 0x30, // 0.5)) - float3(0
	0x2e, 0x35, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, // .5);.        flo
	0x61, 0x74, 0x20, 0x5f, 0x34, 0x39, 0x39, 0x20, 0x3d, 0x20, 0x6c, 0x65, 0x6e, 0x67, 0x74, 0x68, // at _499 = length
	0x28, 0x66, 0x61, 0x73, 0x74, 0x3a, 0x3a, 0x6d, 0x61, 0x78, 0x28, 0x5f, 0x34, 0x38, 0x36, 0x2c, // (fast::max(_486,
	0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x33, 0x28, 0x30, 0x2e, 0x30, 0x29, 0x29, 0x29, 0x20, 0x2b, //  float3(0.0))) +
	0x20, 0x66, 0x61, 0x73, 0x74, 0x3a, 0x3a, 0x6d, 0x69, 0x6e, 0x28, 0x66, 0x61, 0x73, 0x74, 0x3a, //  fast::min(fast:
	0x3a, 0x6d, 0x61, 0x78, 0x28, 0x5f, 0x34, 0x38, 0x36, 0x2e, 0x78, 0x2c, 0x20, 0x66, 0x61, 0x73, // :max(_486.x, fas
	0x74, 0x3a, 0x3a, 0x6d, 0x61, 0x78, 0x28, 0x5f, 0x34, 0x38, 0x36, 0x2e, 0x79, 0x2c, 0x20, 0x5f, // t::max(_486.y, _
	0x34, 0x38, 0x36, 0x2e, 0x7a, 0x29, 0x29, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x29, 0x3b, 0x0a, 0x20, // 486.z)), 0.0);. 
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x5f, 0x34, 0x35, //        float _45
	0x34, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x62, 0x6f, 0x6f, 0x6c, 0x20, // 4;.        bool 
	0x5f, 0x37, 0x32, 0x31, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, // _721;.        fl
	0x6f, 0x61, 0x74, 0x32, 0x20, 0x5f, 0x37, 0x32, 0x34, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, // oat2 _724;.     
	0x20, 0x20, 0x20, 0x69, 0x6e, 0x74, 0x20, 0x5f, 0x37, 0x31, 0x39, 0x20, 0x3d, 0x20, 0x30, 0x3b, //    int _719 = 0;
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x5f, // .        float _
	0x37, 0x32, 0x30, 0x20, 0x3d, 0x20, 0x5f, 0x34, 0x39, 0x39, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, // 720 = _499;.    
	0x20, 0x20, 0x20, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x28, 0x3b, 0x3b, 0x29, 0x0a, 0x20, 0x20, 0x20, //     for (;;).   
	0x20, 0x20, 0x20, 0x20, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //      {.         
	0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x5f, 0x37, 0x31, 0x39, 0x20, 0x3c, 0x20, 0x31, 0x30, //    if (_719 < 10
	0x30, 0x29, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7b, // 0).            {
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // .               
	0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x5f, 0x35, 0x33, 0x31, 0x20, 0x3d, 0x20, 0x53, //  float4 _531 = S
	0x44, 0x46, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x2e, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, // DFSampler.sample
	0x28, 0x53, 0x44, 0x46, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x53, 0x61, 0x6d, 0x70, 0x6c, // (SDFSamplerSampl
	0x65, 0x72, 0x2c, 0x20, 0x28, 0x28, 0x28, 0x5f, 0x33, 0x37, 0x32, 0x20, 0x2b, 0x20, 0x28, 0x5f, // er, (((_372 + (_
	0x33, 0x39, 0x32, 0x20, 0x2a, 0x20, 0x5f, 0x37, 0x32, 0x30, 0x29, 0x29, 0x20, 0x2d, 0x20, 0x5f, // 392 * _720)) - _
	0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x6f, 0x75, 0x6e, 0x64, 0x4d, 0x69, 0x6e, 0x2e, 0x78, // mtl_u.boundMin.x
	0x79, 0x7a, 0x29, 0x20, 0x2a, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x6f, 0x75, // yz) * _mtl_u.bou
	0x6e, 0x64, 0x52, 0x61, 0x74, 0x69, 0x6f, 0x2e, 0x78, 0x79, 0x7a, 0x29, 0x29, 0x3b, 0x0a, 0x20, // ndRatio.xyz));. 
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x66, //                f
	0x6c, 0x6f, 0x61, 0x74, 0x20, 0x5f, 0x35, 0x31, 0x30, 0x20, 0x3d, 0x20, 0x5f, 0x35, 0x33, 0x31, // loat _510 = _531
	0x2e, 0x78, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // .x;.            
	0x20, 0x20, 0x20, 0x20, 0x5f, 0x34, 0x35, 0x34, 0x20, 0x3d, 0x20, 0x5f, 0x37, 0x32, 0x30, 0x20, //     _454 = _720 
	0x2b, 0x20, 0x5f, 0x35, 0x31, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // + _510;.        
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x5f, 0x35, 0x31, 0x30, //         if (_510
	0x20, 0x3c, 0x3d, 0x20, 0x30, 0x2e, 0x30, 0x30, 0x31, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, //  <= 0.0010000000
	0x34, 0x37, 0x34, 0x39, 0x37, 0x34, 0x35, 0x31, 0x33, 0x30, 0x35, 0x33, 0x38, 0x39, 0x34, 0x30, // 4749745130538940
	0x34, 0x32, 0x39, 0x36, 0x38, 0x37, 0x35, 0x29, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // 4296875).       
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, //          {.     
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, //                _
	0x37, 0x32, 0x34, 0x20, 0x3d, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x32, 0x28, 0x5f, 0x34, 0x35, // 724 = float2(_45
	0x34, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // 4, 1.0);.       
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x37, 0x32, //              _72
	0x31, 0x20, 0x3d, 0x20, 0x74, 0x72, 0x75, 0x65, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // 1 = true;.      
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x62, 0x72, //               br
	0x65, 0x61, 0x6b, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // eak;.           
	0x20, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //      }.         
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x37, 0x32, 0x30, 0x20, 0x3d, 0x20, 0x5f, 0x34, //        _720 = _4
	0x35, 0x34, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // 54;.            
	0x20, 0x20, 0x20, 0x20, 0x5f, 0x37, 0x31, 0x39, 0x2b, 0x2b, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, //     _719++;.    
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x63, 0x6f, 0x6e, 0x74, //             cont
	0x69, 0x6e, 0x75, 0x65, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // inue;.          
	0x20, 0x20, 0x7d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //   }.            
	0x65, 0x6c, 0x73, 0x65, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // else.           
	0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //  {.             
	0x20, 0x20, 0x20, 0x5f, 0x37, 0x32, 0x34, 0x20, 0x3d, 0x20, 0x5f, 0x37, 0x32, 0x36, 0x3b, 0x0a, //    _724 = _726;.
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //                 
	0x5f, 0x37, 0x32, 0x31, 0x20, 0x3d, 0x20, 0x66, 0x61, 0x6c, 0x73, 0x65, 0x3b, 0x0a, 0x20, 0x20, // _721 = false;.  
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x62, 0x72, //               br
	0x65, 0x61, 0x6b, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // eak;.           
	0x20, 0x7d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x0a, 0x20, 0x20, 0x20, //  }.        }.   
	0x20, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x5f, 0x37, 0x32, 0x31, 0x29, 0x0a, 0x20, //      if (_721). 
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //        {.       
	0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x37, 0x32, 0x33, 0x20, 0x3d, 0x20, 0x5f, 0x37, 0x32, 0x34, //      _723 = _724
	0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x62, 0x72, // ;.            br
	0x65, 0x61, 0x6b, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x0a, 0x20, // eak;.        }. 
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x37, 0x32, 0x33, 0x20, 0x3d, 0x20, 0x66, 0x6c, //        _723 = fl
	0x6f, 0x61, 0x74, 0x32, 0x28, 0x39, 0x39, 0x39, 0x39, 0x39, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, // oat2(99999.0, 0.
	0x30, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x62, 0x72, 0x65, 0x61, // 0);.        brea
	0x6b, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x20, 0x77, 0x68, 0x69, 0x6c, 0x65, 0x28, 0x66, // k;.    } while(f
	0x61, 0x6c, 0x73, 0x65, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, // alse);.    float
	0x34, 0x20, 0x5f, 0x37, 0x32, 0x37, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, // 4 _727;.    if (
	0x5f, 0x37, 0x32, 0x33, 0x2e, 0x78, 0x20, 0x3c, 0x20, 0x31, 0x30, 0x30, 0x30, 0x2e, 0x30, 0x29, // _723.x < 1000.0)
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x66, // .    {.        f
	0x6c, 0x6f, 0x61, 0x74, 0x33, 0x20, 0x5f, 0x34, 0x30, 0x35, 0x20, 0x3d, 0x20, 0x5f, 0x33, 0x37, // loat3 _405 = _37
	0x32, 0x20, 0x2b, 0x20, 0x28, 0x5f, 0x33, 0x39, 0x32, 0x20, 0x2a, 0x20, 0x5f, 0x37, 0x32, 0x33, // 2 + (_392 * _723
	0x2e, 0x78, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x37, 0x32, // .x);.        _72
	0x37, 0x20, 0x3d, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x28, 0x5f, 0x37, 0x32, 0x33, 0x2c, // 7 = float4(_723,
	0x20, 0x6e, 0x6f, 0x72, 0x6d, 0x61, 0x6c, 0x69, 0x7a, 0x65, 0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, //  normalize(float
	0x33, 0x28, 0x53, 0x44, 0x46, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x2e, 0x73, 0x61, 0x6d, // 3(SDFSampler.sam
	0x70, 0x6c, 0x65, 0x28, 0x53, 0x44, 0x46, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x53, 0x61, // ple(SDFSamplerSa
	0x6d, 0x70, 0x6c, 0x65, 0x72, 0x2c, 0x20, 0x28, 0x28, 0x5f, 0x34, 0x30, 0x35, 0x20, 0x2d, 0x20, // mpler, ((_405 - 
	0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x6f, 0x75, 0x6e, 0x64, 0x4d, 0x69, 0x6e, 0x2e, // _mtl_u.boundMin.
	0x78, 0x79, 0x7a, 0x29, 0x20, 0x2a, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x6f, // xyz) * _mtl_u.bo
	0x75, 0x6e, 0x64, 0x52, 0x61, 0x74, 0x69, 0x6f, 0x2e, 0x78, 0x79, 0x7a, 0x29, 0x29, 0x2e, 0x78, // undRatio.xyz)).x
	0x29, 0x20, 0x2d, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x33, 0x28, 0x53, 0x44, 0x46, 0x53, 0x61, // ) - float3(SDFSa
	0x6d, 0x70, 0x6c, 0x65, 0x72, 0x2e, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x28, 0x53, 0x44, 0x46, // mpler.sample(SDF
	0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x2c, 0x20, // SamplerSampler, 
	0x28, 0x28, 0x28, 0x5f, 0x34, 0x30, 0x35, 0x20, 0x2d, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x33, // (((_405 - float3
	0x28, 0x30, 0x2e, 0x35, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x29, 0x29, // (0.5, 0.0, 0.0))
	0x20, 0x2d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x6f, 0x75, 0x6e, 0x64, 0x4d, //  - _mtl_u.boundM
	0x69, 0x6e, 0x2e, 0x78, 0x79, 0x7a, 0x29, 0x20, 0x2a, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, // in.xyz) * _mtl_u
	0x2e, 0x62, 0x6f, 0x75, 0x6e, 0x64, 0x52, 0x61, 0x74, 0x69, 0x6f, 0x2e, 0x78, 0x79, 0x7a, 0x29, // .boundRatio.xyz)
	0x29, 0x2e, 0x78, 0x2c, 0x20, 0x53, 0x44, 0x46, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x2e, // ).x, SDFSampler.
	0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x28, 0x53, 0x44, 0x46, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, // sample(SDFSample
	0x72, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x2c, 0x20, 0x28, 0x28, 0x28, 0x5f, 0x34, 0x30, // rSampler, (((_40
	0x35, 0x20, 0x2d, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x33, 0x28, 0x30, 0x2e, 0x30, 0x2c, 0x20, // 5 - float3(0.0, 
	0x30, 0x2e, 0x35, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x29, 0x29, 0x20, 0x2d, 0x20, 0x5f, 0x6d, 0x74, // 0.5, 0.0)) - _mt
	0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x6f, 0x75, 0x6e, 0x64, 0x4d, 0x69, 0x6e, 0x2e, 0x78, 0x79, 0x7a, // l_u.boundMin.xyz
	0x29, 0x20, 0x2a, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x6f, 0x75, 0x6e, 0x64, // ) * _mtl_u.bound
	0x52, 0x61, 0x74, 0x69, 0x6f, 0x2e, 0x78, 0x79, 0x7a, 0x29, 0x29, 0x2e, 0x78, 0x2c, 0x20, 0x53, // Ratio.xyz)).x, S
	0x44, 0x46, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x2e, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, // DFSampler.sample
	0x28, 0x53, 0x44, 0x46, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x53, 0x61, 0x6d, 0x70, 0x6c, // (SDFSamplerSampl
	0x65, 0x72, 0x2c, 0x20, 0x28, 0x28, 0x28, 0x5f, 0x34, 0x30, 0x35, 0x20, 0x2d, 0x20, 0x66, 0x6c, // er, (((_405 - fl
	0x6f, 0x61, 0x74, 0x33, 0x28, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x30, // oat3(0.0, 0.0, 0
	0x2e, 0x35, 0x29, 0x29, 0x20, 0x2d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x6f, // .5)) - _mtl_u.bo
	0x75, 0x6e, 0x64, 0x4d, 0x69, 0x6e, 0x2e, 0x78, 0x79, 0x7a, 0x29, 0x20, 0x2a, 0x20, 0x5f, 0x6d, // undMin.xyz) * _m
	0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x6f, 0x75, 0x6e, 0x64, 0x52, 0x61, 0x74, 0x69, 0x6f, 0x2e, // tl_u.boundRatio.
	0x78, 0x79, 0x7a, 0x29, 0x29, 0x2e, 0x78, 0x29, 0x29, 0x2e, 0x78, 0x79, 0x29, 0x3b, 0x0a, 0x20, // xyz)).x)).xy);. 
	0x20, 0x20, 0x20, 0x7d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x65, 0x6c, 0x73, 0x65, 0x0a, 0x20, 0x20, //    }.    else.  
	0x20, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x37, 0x32, 0x37, //   {.        _727
	0x20, 0x3d, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x28, 0x39, 0x39, 0x39, 0x39, 0x2e, 0x30, //  = float4(9999.0
	0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x29, // , 0.0, 0.0, 0.0)
	0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x75, 0x74, 0x2e, // ;.    }.    out.
	0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x30, 0x20, 0x3d, // bgfx_FragData0 =
	0x20, 0x5f, 0x37, 0x32, 0x37, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, //  _727;.    retur
	0x6e, 0x20, 0x6f, 0x75, 0x74, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00, 0x00, 0x90, 0x00,             // n out;.}......
};
