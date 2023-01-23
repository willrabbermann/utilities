#ifndef _GMATH_H_
#define _GMATH_H_

#ifndef M_PI
# define M_E 2.7182818284590452354
# define M_LOG2E 1.4426950408889634074
# define M_LN2 0.69314718055994530942
# define M_LN10 2.30258509299404568402
# define M_PI 3.14159265358979323846
# define M_SQRT2 1.41421356237309504880
# define M_SQRT1_2 0.70710678118654752440
#endif
#define M_TAU (2 * M_PI)
#define M_SQRT3 1.73205080756887729352
#define M_SQRT5 2.23606797749978969640
#define M_PHI 1.61803398874989484820
#define M_SQRTPHI 1.27201964951406896425
#define M_SQRTE 1.64872127070012814684
#define M_SQRTPI 1.77245385090551602729

#define deg2rad(x) ((x)*M_PI / 180)
#define rad2deg(x) ((x)*180 / M_PI)

#define abs(a) ((a < 0) ? (-a) : (a)) 
#define aprox(a, b, c) ((abs((a - b)) <= c) ? (1) : (0))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define clamp(a, b, c) min(c, max(b, a))

typedef float float2x2[2][2];
typedef float float3x3[3][3];
typedef float float4x4[4][4];

typedef struct {
	float x, y;
} vec2f, vert2f;

typedef struct {
	float x, y, z;
} vec3f, vert3f;

typedef struct {
	float x, y, z, w;
} vec4f, vert4f;

vec2f *newvec2f(float x, float y);
float distancevec2f(vec2f *a, vec2f *b);
void printvec2f(vec2f *v);
void opvec2f(vec2f *a, vec2f *b, vec2f *result, char op);
void scalar_op_vec2f(vec2f *a, float scalar, vec2f *result, char op);
void rotatevec2f(vec2f *origin, vec2f *vec, float degrees);

vec3f *newvec3f(float x, float y, float z);
float distancevec3f(vec3f *a, vec3f *b);
void printvec3f(vec3f *v);
void opvec3f(vec3f *a, vec3f *b, vec3f *result, char op);
void scalar_op_vec3f(vec3f *a, float scalar, vec3f *result, char op);
void rotatevec3f(vec3f *origin, vec3f *vec, float degrees, char axis);

vec4f *newvec4f(float x, float y, float z, float w);
float distancevec4f(vec4f *a, vec4f *b);
void printvec4f(vec4f *v);
void opvec4f(vec4f *a, vec4f *b, vec4f *result, char op);
void scalar_op_vec4f(vec4f *a, float scalar, vec4f *result, char op);

void eyefloat2x2(float2x2 a);
void eyefloat3x3(float3x3 a);
void eyefloat4x4(float4x4 a);
void printfloat2x2(float2x2 a);
void printfloat3x3(float3x3 a);
void printfloat4x4(float4x4 a);
void opfloat3x3(float3x3 a, float3x3 b, float3x3 result, char op);

void dotproduct_2x2_vec2f(float2x2 *a, vec2f *b, vec2f *result);
void dotproduct_3x3_vec3f(float3x3 *a, vec3f *b, vec3f *result);
void dotproduct_4x4_vec4f(float4x4 *a, vec4f *b, vec4f *result);

#endif
