
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
// Copyright (c) 2014-2017 Francois Beaune, The appleseedhq Organization
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

#ifndef APPLESEED_RENDERER_KERNEL_LIGHTING_LIGHTTRACING_LIGHTTRACINGSAMPLEGENERATOR_H
#define APPLESEED_RENDERER_KERNEL_LIGHTING_LIGHTTRACING_LIGHTTRACINGSAMPLEGENERATOR_H

// appleseed.renderer headers.
#include "renderer/kernel/rendering/isamplegenerator.h"
#include "renderer/utility/paramarray.h"

// appleseed.foundation headers.
#include "foundation/platform/compiler.h"

// OSL headers.
#include "foundation/platform/oslheaderguards.h"
BEGIN_OSL_INCLUDES
#include "OSL/oslexec.h"
END_OSL_INCLUDES

// OpenImageIO headers.
#include "foundation/platform/oiioheaderguards.h"
BEGIN_OIIO_INCLUDES
#include "OpenImageIO/texture.h"
END_OIIO_INCLUDES

// Standard headers.
#include <cstddef>

// Forward declarations.
namespace renderer  { class Frame; }
namespace renderer  { class LightSampler; }
namespace renderer  { class Project; }
namespace renderer  { class SampleAccumulationBuffer; }
namespace renderer  { class TextureStore; }
namespace renderer  { class TraceContext; }

namespace renderer
{

class LightTracingSampleGeneratorFactory
  : public ISampleGeneratorFactory
{
  public:
    // Constructor.
    LightTracingSampleGeneratorFactory(
        const Project&          project,
        const Frame&            frame,
        const TraceContext&     trace_context,
        TextureStore&           texture_store,
        const LightSampler&     light_sampler,
        OIIO::TextureSystem&    oiio_texture_system,
        OSL::ShadingSystem&     shading_system,
        const ParamArray&       params);

    // Delete this instance.
    virtual void release() APPLESEED_OVERRIDE;

    // Return a new sample generator instance.
    virtual ISampleGenerator* create(
        const size_t            generator_index,
        const size_t            generator_count) APPLESEED_OVERRIDE;

    // Create an accumulation buffer for this sample generator.
    virtual SampleAccumulationBuffer* create_sample_accumulation_buffer() APPLESEED_OVERRIDE;

  private:
    const Project&              m_project;
    const Frame&                m_frame;
    const TraceContext&         m_trace_context;
    TextureStore&               m_texture_store;
    const LightSampler&         m_light_sampler;
    OIIO::TextureSystem&        m_oiio_texture_system;
    OSL::ShadingSystem&         m_shading_system;
    const ParamArray            m_params;
};

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_KERNEL_LIGHTING_LIGHTTRACING_LIGHTTRACINGSAMPLEGENERATOR_H
