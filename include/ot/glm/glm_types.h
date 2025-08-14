
#ifndef _OT_GLM_TYPES_H_
#define _OT_GLM_TYPES_H_

import glm;

#include <comm/commtypes.h>

//vectors

typedef glm::vec2 float2;
typedef glm::vec3 float3;
typedef glm::vec4 float4;

typedef glm::dvec2 double2;
typedef glm::dvec3 double3;
typedef glm::dvec4 double4;

typedef glm::ivec2 int2;
typedef glm::ivec3 int3;
typedef glm::ivec4 int4;

typedef glm::uvec2 uint2;
typedef glm::uvec3 uint3;
typedef glm::uvec4 uint4;

typedef glm::bvec2 bool2;
typedef glm::bvec3 bool3;
typedef glm::bvec4 bool4;

typedef glm::i64vec4 i64vec4;
typedef glm::i64vec3 i64vec3;
typedef glm::i64vec2 i64vec2;

typedef glm::u64vec4 u64vec4;
typedef glm::u64vec3 u64vec3;
typedef glm::u64vec2 u64vec2;

typedef glm::i16vec4 short4;
typedef glm::i16vec3 short3;
typedef glm::i16vec2 short2;

typedef glm::u16vec4 ushort4;
typedef glm::u16vec3 ushort3;
typedef glm::u16vec2 ushort2;

typedef glm::i16vec4 i16vec4;
typedef glm::i16vec3 i16vec3;
typedef glm::i16vec2 i16vec2;

typedef glm::u16vec4 u16vec4;
typedef glm::u16vec3 u16vec3;
typedef glm::u16vec2 u16vec2;

typedef glm::i8vec4 i8vec4;
typedef glm::i8vec3 i8vec3;
typedef glm::i8vec2 i8vec2;

typedef glm::u8vec4 u8vec4;
typedef glm::u8vec3 u8vec3;
typedef glm::u8vec2 u8vec2;


template <int N> struct hvec {
    static_assert(N <= 4, "hvec only supports N <= 4 with this implementation");
    short data[4] = {0};

    glm::vec<N, float> to_float_vec() const {
        glm::vec<N, float> v;
        __m128 half_floats = _mm_cvtph_ps(*(__m128i *)data);
        _mm_store_ps(glm::gtc::value_ptr(v), half_floats);
        return v;
    }

    void from_float_vec(const glm::vec<N, float> &v) {
        __m128 values = _mm_set_ps(N >= 4 ? v[3] : 0.f, N >= 3 ? v[2] : 0.f,
                                   N >= 2 ? v[1] : 0.f, v[0]);
        __m128i half_values = _mm_cvtps_ph(values, _MM_FROUND_TO_NEAREST_INT);
        _mm_storeu_si64((__m64 *)&data[0], half_values);
    }
};


using half2 = hvec<2>;
using half3 = hvec<3>;
using half4 = hvec<4>;

//matrices

typedef glm::mat2x2 float2x2;
typedef glm::mat2x3 float3x2;
typedef glm::mat2x4 float4x2;

typedef glm::mat3x2 float2x3;
typedef glm::mat3x3 float3x3;
typedef glm::mat3x4 float4x3;

typedef glm::mat4x2 float2x4;
typedef glm::mat4x3 float3x4;
typedef glm::mat4x4 float4x4;


typedef glm::dmat2x2 double2x2;
typedef glm::dmat2x3 double3x2;
typedef glm::dmat2x4 double4x2;

typedef glm::dmat3x2 double2x3;
typedef glm::dmat3x3 double3x3;
typedef glm::dmat3x4 double4x3;

typedef glm::dmat4x2 double2x4;
typedef glm::dmat4x3 double3x4;
typedef glm::dmat4x4 double4x4;

// quaternions

using glm::quat;
using glm::dquat;

#endif //_OT_GLM_TYPES_H_
