static const uint8_t DepthId_PlaneHelpers_fs_essl[2542] =
{
	0x46, 0x53, 0x48, 0x0b, 0x6f, 0x1e, 0x3e, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x09, 0x76, // FSH.o.><.......v
	0x69, 0x65, 0x77, 0x49, 0x6e, 0x66, 0x6f, 0x73, 0x02, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // iewInfos........
	0xcc, 0xcc, 0x0a, 0x63, 0x61, 0x6d, 0x65, 0x72, 0x61, 0x56, 0x69, 0x65, 0x77, 0x04, 0x01, 0x00, // ...cameraView...
	0x00, 0x01, 0x00, 0x00, 0x00, 0xcc, 0xcc, 0x0e, 0x64, 0x65, 0x70, 0x74, 0x68, 0x49, 0x64, 0x53, // ........depthIdS
	0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xcc, 0xcc, // ampler..........
	0x99, 0x09, 0x00, 0x00, 0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, 0x69, 0x67, 0x68, // ....varying high
	0x70, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, // p vec2 v_texcoor
	0x64, 0x30, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x68, 0x69, 0x67, 0x68, // d0;.uniform high
	0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x69, 0x65, 0x77, 0x49, 0x6e, 0x66, 0x6f, 0x73, // p vec4 viewInfos
	0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, // ;.uniform highp 
	0x6d, 0x61, 0x74, 0x34, 0x20, 0x63, 0x61, 0x6d, 0x65, 0x72, 0x61, 0x56, 0x69, 0x65, 0x77, 0x3b, // mat4 cameraView;
	0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, // .uniform sampler
	0x32, 0x44, 0x20, 0x64, 0x65, 0x70, 0x74, 0x68, 0x49, 0x64, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, // 2D depthIdSample
	0x72, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, // r;.void main ().
	0x7b, 0x0a, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, // {.  highp float 
	0x73, 0x75, 0x6d, 0x5f, 0x32, 0x3b, 0x0a, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, // sum_2;.  highp v
	0x65, 0x63, 0x34, 0x20, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5f, 0x33, 0x3b, 0x0a, 0x20, 0x20, 0x68, // ec4 color_3;.  h
	0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x72, 0x6f, 0x5f, 0x34, 0x3b, 0x0a, // ighp vec3 ro_4;.
	0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x72, 0x61, //   highp float ra
	0x74, 0x69, 0x6f, 0x5f, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x6c, 0x6f, 0x77, 0x70, 0x20, 0x66, 0x6c, // tio_5;.  lowp fl
	0x6f, 0x61, 0x74, 0x20, 0x64, 0x65, 0x70, 0x74, 0x68, 0x5f, 0x36, 0x3b, 0x0a, 0x20, 0x20, 0x68, // oat depth_6;.  h
	0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x75, 0x76, 0x5f, 0x37, 0x3b, 0x0a, // ighp vec2 uv_7;.
	0x20, 0x20, 0x75, 0x76, 0x5f, 0x37, 0x20, 0x3d, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, //   uv_7 = v_texco
	0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x64, 0x65, 0x70, 0x74, 0x68, 0x5f, 0x36, 0x20, // ord0;.  depth_6 
	0x3d, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44, 0x20, 0x28, 0x64, 0x65, 0x70, // = texture2D (dep
	0x74, 0x68, 0x49, 0x64, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x2c, 0x20, 0x76, 0x5f, 0x74, // thIdSampler, v_t
	0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x2e, 0x78, 0x3b, 0x0a, 0x20, 0x20, 0x72, // excoord0).x;.  r
	0x61, 0x74, 0x69, 0x6f, 0x5f, 0x35, 0x20, 0x3d, 0x20, 0x76, 0x69, 0x65, 0x77, 0x49, 0x6e, 0x66, // atio_5 = viewInf
	0x6f, 0x73, 0x2e, 0x78, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x6f, 0x5f, 0x34, 0x20, 0x3d, 0x20, 0x28, // os.x;.  ro_4 = (
	0x63, 0x61, 0x6d, 0x65, 0x72, 0x61, 0x56, 0x69, 0x65, 0x77, 0x20, 0x2a, 0x20, 0x76, 0x65, 0x63, // cameraView * vec
	0x34, 0x28, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, // 4(0.0, 0.0, 0.0,
	0x20, 0x31, 0x2e, 0x30, 0x29, 0x29, 0x2e, 0x78, 0x79, 0x7a, 0x3b, 0x0a, 0x20, 0x20, 0x63, 0x6f, //  1.0)).xyz;.  co
	0x6c, 0x6f, 0x72, 0x5f, 0x33, 0x20, 0x3d, 0x20, 0x76, 0x65, 0x63, 0x34, 0x28, 0x30, 0x2e, 0x30, // lor_3 = vec4(0.0
	0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x29, // , 0.0, 0.0, 0.0)
	0x3b, 0x0a, 0x20, 0x20, 0x73, 0x75, 0x6d, 0x5f, 0x32, 0x20, 0x3d, 0x20, 0x30, 0x2e, 0x30, 0x3b, // ;.  sum_2 = 0.0;
	0x0a, 0x20, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x28, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x69, 0x6e, // .  for (highp in
	0x74, 0x20, 0x79, 0x5f, 0x31, 0x20, 0x3d, 0x20, 0x2d, 0x32, 0x3b, 0x20, 0x79, 0x5f, 0x31, 0x20, // t y_1 = -2; y_1 
	0x3c, 0x20, 0x33, 0x3b, 0x20, 0x79, 0x5f, 0x31, 0x2b, 0x2b, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, // < 3; y_1++) {.  
	0x20, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x28, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x69, 0x6e, 0x74, //   for (highp int
	0x20, 0x78, 0x5f, 0x38, 0x20, 0x3d, 0x20, 0x2d, 0x32, 0x3b, 0x20, 0x78, 0x5f, 0x38, 0x20, 0x3c, //  x_8 = -2; x_8 <
	0x20, 0x33, 0x3b, 0x20, 0x78, 0x5f, 0x38, 0x2b, 0x2b, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, //  3; x_8++) {.   
	0x20, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x67, //    highp float g
	0x5f, 0x39, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x75, 0x76, 0x5f, 0x37, 0x2e, 0x79, // _9;.      uv_7.y
	0x20, 0x3d, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x2e, 0x79, //  = v_texcoord0.y
	0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x75, 0x76, 0x5f, 0x37, 0x2e, 0x78, 0x20, 0x3d, // ;.      uv_7.x =
	0x20, 0x28, 0x31, 0x2e, 0x30, 0x20, 0x2d, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, //  (1.0 - v_texcoo
	0x72, 0x64, 0x30, 0x2e, 0x78, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x68, 0x69, // rd0.x);.      hi
	0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // ghp vec2 tmpvar_
	0x31, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, // 10;.      tmpvar
	0x5f, 0x31, 0x30, 0x2e, 0x78, 0x20, 0x3d, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x28, 0x78, 0x5f, // _10.x = float(x_
	0x38, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, // 8);.      tmpvar
	0x5f, 0x31, 0x30, 0x2e, 0x79, 0x20, 0x3d, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x28, 0x79, 0x5f, // _10.y = float(y_
	0x31, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, // 1);.      highp 
	0x76, 0x65, 0x63, 0x32, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x31, 0x3b, 0x0a, // vec2 tmpvar_11;.
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x31, 0x2e, //       tmpvar_11.
	0x78, 0x20, 0x3d, 0x20, 0x31, 0x2e, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, // x = 1.0;.      t
	0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x31, 0x2e, 0x79, 0x20, 0x3d, 0x20, 0x72, 0x61, 0x74, // mpvar_11.y = rat
	0x69, 0x6f, 0x5f, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x75, 0x76, 0x5f, 0x37, // io_5;.      uv_7
	0x20, 0x3d, 0x20, 0x28, 0x75, 0x76, 0x5f, 0x37, 0x20, 0x2b, 0x20, 0x28, 0x28, 0x74, 0x6d, 0x70, //  = (uv_7 + ((tmp
	0x76, 0x61, 0x72, 0x5f, 0x31, 0x30, 0x20, 0x2a, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // var_10 * tmpvar_
	0x31, 0x31, 0x29, 0x20, 0x2a, 0x20, 0x30, 0x2e, 0x30, 0x30, 0x30, 0x35, 0x29, 0x29, 0x3b, 0x0a, // 11) * 0.0005));.
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x33, //       highp vec3
	0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x32, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, //  tmpvar_12;.    
	0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x32, 0x2e, 0x7a, 0x20, 0x3d, 0x20, //   tmpvar_12.z = 
	0x31, 0x2e, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // 1.0;.      tmpva
	0x72, 0x5f, 0x31, 0x32, 0x2e, 0x78, 0x20, 0x3d, 0x20, 0x28, 0x28, 0x75, 0x76, 0x5f, 0x37, 0x2e, // r_12.x = ((uv_7.
	0x78, 0x20, 0x2a, 0x20, 0x32, 0x2e, 0x30, 0x29, 0x20, 0x2d, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x3b, // x * 2.0) - 1.0);
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x32, // .      tmpvar_12
	0x2e, 0x79, 0x20, 0x3d, 0x20, 0x28, 0x28, 0x75, 0x76, 0x5f, 0x37, 0x2e, 0x79, 0x20, 0x2d, 0x20, // .y = ((uv_7.y - 
	0x30, 0x2e, 0x35, 0x29, 0x20, 0x2a, 0x20, 0x28, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x5f, 0x35, 0x20, // 0.5) * (ratio_5 
	0x2a, 0x20, 0x32, 0x2e, 0x30, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x68, // * 2.0));.      h
	0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, // ighp vec4 tmpvar
	0x5f, 0x31, 0x33, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // _13;.      tmpva
	0x72, 0x5f, 0x31, 0x33, 0x2e, 0x77, 0x20, 0x3d, 0x20, 0x30, 0x2e, 0x30, 0x3b, 0x0a, 0x20, 0x20, // r_13.w = 0.0;.  
	0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x33, 0x2e, 0x78, 0x79, //     tmpvar_13.xy
	0x7a, 0x20, 0x3d, 0x20, 0x6e, 0x6f, 0x72, 0x6d, 0x61, 0x6c, 0x69, 0x7a, 0x65, 0x28, 0x74, 0x6d, // z = normalize(tm
	0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x32, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // pvar_12);.      
	0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // highp vec3 tmpva
	0x72, 0x5f, 0x31, 0x34, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, // r_14;.      tmpv
	0x61, 0x72, 0x5f, 0x31, 0x34, 0x20, 0x3d, 0x20, 0x28, 0x63, 0x61, 0x6d, 0x65, 0x72, 0x61, 0x56, // ar_14 = (cameraV
	0x69, 0x65, 0x77, 0x20, 0x2a, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x33, 0x29, // iew * tmpvar_13)
	0x2e, 0x78, 0x79, 0x7a, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, // .xyz;.      high
	0x70, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, // p float tmpvar_1
	0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x66, // 5;.      highp f
	0x6c, 0x6f, 0x61, 0x74, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x36, 0x3b, 0x0a, // loat tmpvar_16;.
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x36, 0x20, //       tmpvar_16 
	0x3d, 0x20, 0x28, 0x72, 0x6f, 0x5f, 0x34, 0x2e, 0x79, 0x20, 0x2d, 0x20, 0x2d, 0x31, 0x2e, 0x30, // = (ro_4.y - -1.0
	0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x28, 0x28, 0x74, // );.      if (((t
	0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x34, 0x2e, 0x79, 0x20, 0x3e, 0x3d, 0x20, 0x30, 0x2e, // mpvar_14.y >= 0.
	0x30, 0x29, 0x20, 0x7c, 0x7c, 0x20, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x36, // 0) || (tmpvar_16
	0x20, 0x3c, 0x3d, 0x20, 0x30, 0x2e, 0x30, 0x29, 0x29, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, //  <= 0.0))) {.   
	0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x35, 0x20, 0x3d, //      tmpvar_15 =
	0x20, 0x39, 0x39, 0x39, 0x39, 0x39, 0x2e, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //  99999.0;.      
	0x7d, 0x20, 0x65, 0x6c, 0x73, 0x65, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // } else {.       
	0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x35, 0x20, 0x3d, 0x20, 0x28, 0x74, 0x6d, //  tmpvar_15 = (tm
	0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x36, 0x20, 0x2f, 0x20, 0x61, 0x62, 0x73, 0x28, 0x74, 0x6d, // pvar_16 / abs(tm
	0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x34, 0x2e, 0x79, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, // pvar_14.y));.   
	0x20, 0x20, 0x20, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, //    };.      high
	0x70, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x37, // p vec3 tmpvar_17
	0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, // ;.      tmpvar_1
	0x37, 0x20, 0x3d, 0x20, 0x28, 0x72, 0x6f, 0x5f, 0x34, 0x20, 0x2b, 0x20, 0x28, 0x74, 0x6d, 0x70, // 7 = (ro_4 + (tmp
	0x76, 0x61, 0x72, 0x5f, 0x31, 0x34, 0x20, 0x2a, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // var_14 * tmpvar_
	0x31, 0x35, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, // 15));.      high
	0x70, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x38, // p vec2 tmpvar_18
	0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, // ;.      tmpvar_1
	0x38, 0x20, 0x3d, 0x20, 0x66, 0x72, 0x61, 0x63, 0x74, 0x28, 0x28, 0x30, 0x2e, 0x34, 0x20, 0x2a, // 8 = fract((0.4 *
	0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x37, 0x2e, 0x78, 0x7a, 0x29, 0x29, 0x3b, //  tmpvar_17.xz));
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, // .      highp vec
	0x32, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x39, 0x3b, 0x0a, 0x20, 0x20, 0x20, // 2 tmpvar_19;.   
	0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x39, 0x20, 0x3d, 0x20, 0x66, //    tmpvar_19 = f
	0x72, 0x61, 0x63, 0x74, 0x28, 0x28, 0x28, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // ract(((.        
	0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x37, 0x2e, 0x78, 0x7a, 0x20, 0x2a, 0x20, // (tmpvar_17.xz * 
	0x34, 0x30, 0x2e, 0x30, 0x29, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x20, 0x30, // 40.0).       + 0
	0x2e, 0x35, 0x29, 0x20, 0x2a, 0x20, 0x30, 0x2e, 0x31, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, // .5) * 0.1));.   
	0x20, 0x20, 0x20, 0x67, 0x5f, 0x39, 0x20, 0x3d, 0x20, 0x28, 0x6d, 0x69, 0x6e, 0x20, 0x28, 0x28, //    g_9 = (min ((
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, // .        ((float
	0x28, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x38, 0x2e, 0x78, 0x20, 0x3e, 0x3d, // ((tmpvar_18.x >=
	0x20, 0x30, 0x2e, 0x31, 0x29, 0x29, 0x20, 0x2a, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x28, 0x28, //  0.1)) * float((
	0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x38, 0x2e, 0x79, 0x20, 0x3e, 0x3d, 0x20, 0x30, // tmpvar_18.y >= 0
	0x2e, 0x31, 0x29, 0x29, 0x29, 0x20, 0x2a, 0x20, 0x30, 0x2e, 0x34, 0x29, 0x0a, 0x20, 0x20, 0x20, // .1))) * 0.4).   
	0x20, 0x20, 0x20, 0x20, 0x2b, 0x20, 0x30, 0x2e, 0x36, 0x29, 0x2c, 0x20, 0x28, 0x0a, 0x20, 0x20, //     + 0.6), (.  
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x28, 0x28, 0x74, //       ((float((t
	0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x39, 0x2e, 0x78, 0x20, 0x3e, 0x3d, 0x20, 0x30, 0x2e, // mpvar_19.x >= 0.
	0x31, 0x29, 0x29, 0x20, 0x2a, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x28, 0x28, 0x74, 0x6d, 0x70, // 1)) * float((tmp
	0x76, 0x61, 0x72, 0x5f, 0x31, 0x39, 0x2e, 0x79, 0x20, 0x3e, 0x3d, 0x20, 0x30, 0x2e, 0x31, 0x29, // var_19.y >= 0.1)
	0x29, 0x29, 0x20, 0x2a, 0x20, 0x30, 0x2e, 0x32, 0x29, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // )) * 0.2).      
	0x20, 0x2b, 0x20, 0x30, 0x2e, 0x38, 0x29, 0x29, 0x20, 0x2a, 0x20, 0x30, 0x2e, 0x33, 0x29, 0x3b, //  + 0.8)) * 0.3);
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x67, 0x5f, 0x39, 0x20, 0x3d, 0x20, 0x28, 0x67, 0x5f, // .      g_9 = (g_
	0x39, 0x20, 0x2d, 0x20, 0x30, 0x2e, 0x30, 0x35, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, // 9 - 0.05);.     
	0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, //  highp vec4 tmpv
	0x61, 0x72, 0x5f, 0x32, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, // ar_20;.      tmp
	0x76, 0x61, 0x72, 0x5f, 0x32, 0x30, 0x2e, 0x77, 0x20, 0x3d, 0x20, 0x31, 0x2e, 0x30, 0x3b, 0x0a, // var_20.w = 1.0;.
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x30, 0x2e, //       tmpvar_20.
	0x78, 0x20, 0x3d, 0x20, 0x67, 0x5f, 0x39, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, // x = g_9;.      t
	0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x30, 0x2e, 0x79, 0x20, 0x3d, 0x20, 0x67, 0x5f, 0x39, // mpvar_20.y = g_9
	0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, // ;.      tmpvar_2
	0x30, 0x2e, 0x7a, 0x20, 0x3d, 0x20, 0x67, 0x5f, 0x39, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, // 0.z = g_9;.     
	0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, //  highp vec4 tmpv
	0x61, 0x72, 0x5f, 0x32, 0x31, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x6d, 0x70, // ar_21;.      tmp
	0x76, 0x61, 0x72, 0x5f, 0x32, 0x31, 0x20, 0x3d, 0x20, 0x6d, 0x69, 0x78, 0x20, 0x28, 0x76, 0x65, // var_21 = mix (ve
	0x63, 0x34, 0x28, 0x30, 0x2e, 0x32, 0x2c, 0x20, 0x30, 0x2e, 0x32, 0x2c, 0x20, 0x30, 0x2e, 0x32, // c4(0.2, 0.2, 0.2
	0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x2c, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, // , 1.0), tmpvar_2
	0x30, 0x2c, 0x20, 0x6d, 0x61, 0x78, 0x20, 0x28, 0x28, 0x31, 0x2e, 0x30, 0x20, 0x2d, 0x20, 0x0a, // 0, max ((1.0 - .
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x73, 0x71, 0x72, 0x74, 0x28, 0x64, 0x6f, //         (sqrt(do
	0x74, 0x20, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x37, 0x2e, 0x78, 0x7a, 0x2c, // t (tmpvar_17.xz,
	0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x37, 0x2e, 0x78, 0x7a, 0x29, 0x29, 0x20, //  tmpvar_17.xz)) 
	0x2a, 0x20, 0x30, 0x2e, 0x30, 0x32, 0x29, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x29, 0x2c, // * 0.02).      ),
	0x20, 0x30, 0x2e, 0x30, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, //  0.0));.      if
	0x20, 0x28, 0x28, 0x28, 0x64, 0x65, 0x70, 0x74, 0x68, 0x5f, 0x36, 0x20, 0x3e, 0x20, 0x38, 0x30, //  (((depth_6 > 80
	0x30, 0x30, 0x2e, 0x30, 0x29, 0x20, 0x26, 0x26, 0x20, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, // 00.0) && (tmpvar
	0x5f, 0x31, 0x35, 0x20, 0x3c, 0x20, 0x38, 0x30, 0x30, 0x30, 0x2e, 0x30, 0x29, 0x29, 0x29, 0x20, // _15 < 8000.0))) 
	0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x73, 0x75, 0x6d, 0x5f, 0x32, 0x20, // {.        sum_2 
	0x2b, 0x3d, 0x20, 0x31, 0x2e, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // += 1.0;.        
	0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5f, 0x33, 0x20, 0x3d, 0x20, 0x28, 0x63, 0x6f, 0x6c, 0x6f, 0x72, // color_3 = (color
	0x5f, 0x33, 0x20, 0x2b, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x31, 0x29, 0x3b, // _3 + tmpvar_21);
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x3b, // .      };.    };
	0x0a, 0x20, 0x20, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, // .  };.  gl_FragC
	0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x28, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5f, 0x33, 0x20, // olor = (color_3 
	0x2f, 0x20, 0x73, 0x75, 0x6d, 0x5f, 0x32, 0x29, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,             // / sum_2);.}...
};
