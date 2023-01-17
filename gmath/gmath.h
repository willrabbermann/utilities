#ifndef _GMATH_H_
#define _GMATH_H_

#ifndef M_PI
#define M_E 2.7182818284590452354
#define M_LOG2E 1.4426950408889634074
#define M_LN2 0.69314718055994530942
#define M_LN10 2.30258509299404568402
#define M_PI 3.14159265358979323846
#define M_SQRT2 1.41421356237309504880
#define M_SQRT1_2 0.70710678118654752440
#endif

#define M_TAU (2 * M_PI)
#define M_SQRT3 1.73205080756887729352
#define M_SQRT5 2.23606797749978969640
#define M_PHI 1.61803398874989484820
#define M_SQRTPHI 1.27201964951406896425
#define M_SQRTE 1.64872127070012814684
#define M_SQRTPI 1.77245385090551602729

typedef float float2x2[2][2];
typedef float float3x3[3][3];
typedef float float4x4[4][4];

#define deg2rad(x) ((x)*M_PI / 180)
#define rad2deg(x) ((x)*180 / M_PI)

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct {
	float x, y;
} vec2f;

typedef struct {
	float x, y, z;
} vec3f;

typedef struct {
	float x, y, z, w;
} vec4f;

int iclamp(int target, int min, int max);
float fclamp(float target, float min, float max);

vec4f *newvec4f(float x, float y, float z, float w);
void transform(vec4f *left, vec4f *right);
void scale(vec4f *left, float right);

void printvec4f(vec4f *v);

#endif
