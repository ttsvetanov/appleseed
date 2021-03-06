
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2016-2017 Luis Barrancos, The appleseedhq Organization
// Copyright (c) 2016-2017 Esteban Tovagliari, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef AS_OSL_EXTENSIONS_H
#define AS_OSL_EXTENSIONS_H

///////////////////////////////////////////////////////////////////////////////

// appleseed version
#define APPLESEED_VERSION_MAJOR     1
#define APPLESEED_VERSION_MINOR     6
#define APPLESEED_VERSION_PATCH     0

#define APPLESEED_VERSION               \
    APPLESEED_VERSION_MAJOR * 10000 +   \
    APPLESEED_VERSION_MINOR * 100 +     \
    APPLESEED_VERSION_PATCH

#ifndef M_1_PI
#define M_1_PI      0.3183098861837907      // 1/pi
#endif

matrix inverse(matrix m) { return 1 / m; }

closure color mix(closure color A, closure color B, float w)
{
    return (1.0 - w) * A + w * B;
}

closure color mix(closure color A, closure color B, color w)
{
    return (1.0 - w) * A + w * B;
}


/*************************************************************/
// Custom appleseed closures
/*************************************************************/


/***************************************/
// diffuse

closure color as_sheen(normal N) BUILTIN;


/***************************************/
// glossy

closure color as_glossy(
    string  distribution,
    normal  N,
    vector  T,
    float   roughness,
    float   anisotropic,
    float   ior) BUILTIN;

closure color as_glossy(
    string  distribution,
    normal  N,
    float   roughness,
    float   ior)
{
    return as_glossy(distribution, N, vector(0), roughness, 0.0, ior);
}


/***************************************/
// metal

closure color as_metal(
    string  distribution,
    normal  N,
    vector  T,
    color   normal_reflectance,
    color   edge_tint,
    float   roughness,
    float   anisotropic) BUILTIN;

closure color as_metal(
    string  distribution,
    normal  N,
    color   normal_reflectance,
    color   edge_tint,
    float   roughness)
{
    return as_metal(
        distribution,
        N,
        vector(0),
        normal_reflectance,
        edge_tint,
        roughness,
        0.0);
}


/***************************************/
// glass

closure color as_glass(
    string  distribution,
    normal  N,
    vector  T,
    color   surface_transmittance,
    color   reflection_tint,
    color   refraction_tint,
    float   roughness,
    float   anisotropic,
    float   ior,
    color   volume_transmittance,
    float   volume_transmittance_distance) BUILTIN;

closure color as_glass(
    string  distribution,
    normal  N,
    color   surface_transmittance,
    color   reflection_tint,
    color   refraction_tint,
    float   roughness,
    float   ior,
    color   volume_transmittance,
    float   volume_transmittance_distance)
{
    return as_glass(
        distribution,
        N,
        vector(0),
        surface_transmittance,
        reflection_tint,
        refraction_tint,
        roughness,
        0.0,
        ior,
        volume_transmittance,
        volume_transmittance_distance);
}


/***************************************/
// subsurface

closure color as_subsurface(
    string  profile,
    normal  N,
    color   reflectance,
    color   mean_free_path,
    float   ior) BUILTIN;


/***************************************/
// composite closures

closure color as_ashikhmin_shirley(
    normal  N,
    vector  T,
    color   diffuse_reflectance,
    color   glossy_reflectance,
    float   exponent_u,                     // Phong-like exponent in first tangent direction
    float   exponent_v,                     // Phong-like exponent in second tangent direction
    float   fresnel_multiplier) BUILTIN;    // Fresnel multiplier

closure color as_disney(
    normal  N,
    vector  T,
    color   base_color,
    float   subsurface,
    float   metallic,
    float   specular,
    float   specular_tint,
    float   anisotropic,
    float   roughness,
    float   sheen,
    float   sheen_tint,
    float   clearcoat,
    float   clearcoat_gloss) BUILTIN;

#endif // AS_OSL_EXTENSIONS_H
