static const uint8_t Circle_fs_glsl[80] =
{
	0x46, 0x53, 0x48, 0x0b, 0x31, 0xe7, 0x8b, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3d, 0x00, // FSH.1..-......=.
	0x00, 0x00, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, // ..void main ().{
	0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, // .  gl_FragColor 
	0x3d, 0x20, 0x76, 0x65, 0x63, 0x34, 0x28, 0x31, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, // = vec4(1.0, 0.0,
	0x20, 0x31, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00, //  1.0, 1.0);.}...
};
