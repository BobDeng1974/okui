/**
* Copyright 2017 BitTorrent Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include "RenderOnce.h"
#include "TestFramebuffer.h"

#include <okui/blending.h>
#include <okui/shapes/Rectangle.h>

#include <gtest/gtest.h>

#if ONAIR_OKUI_HAS_NATIVE_APPLICATION && !OPENGL_ES // TODO: fix for OpenGL ES

using namespace okui;

TEST(Blending, erasure) {
    RenderOnce([&](View* view) {
        auto width = view->bounds().width;
        auto height = view->bounds().height;

        TestFramebuffer framebuffer(width, height);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        auto shader = view->colorShader();

        shader->setColor(RGBF(1.0, 1.0, 0.0));
        shapes::Rectangle((width - height * 0.5) * 0.5, height * 0.25, height * 0.5, height * 0.5).round(height * 0.25).draw(shader);
        shader->flush();

        {
            Blending blending{BlendFunction::kErasure};
            shader->setColor(RGBAF(1.0, 0.0, 0.0, 0.0));
            shapes::Rectangle((width - height * 0.25) * 0.5, height * 0.375, height * 0.25, height * 0.25).round(height * 0.125).draw(shader);
            shader->flush();
        }

        framebuffer.finish();

        EXPECT_EQ(framebuffer.getPixel(width * 0.1, height * 0.5), RGBAF(0.0, 0.0, 0.0, 0.0));
        EXPECT_EQ(framebuffer.getPixel(width * 0.5, height * 0.1), RGBAF(0.0, 0.0, 0.0, 0.0));
        EXPECT_EQ(framebuffer.getPixel(width * 0.5, height * 0.5), RGBF(0.0, 1.0, 0.0));
        EXPECT_EQ(framebuffer.getPixel(width * 0.5, height * 0.30), RGBF(1.0, 1.0, 0.0));
    });
}

TEST(Blending, alphaLock) {
    RenderOnce([&](View* view) {
        auto width = view->bounds().width;
        auto height = view->bounds().height;

        TestFramebuffer framebuffer(width, height);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        auto shader = view->colorShader();

        shader->setColor(RGBF(1.0, 0.0, 0.0));
        shapes::Rectangle((width - height * 0.5) * 0.5, height * 0.25, height * 0.5, height * 0.5).round(height * 0.25).draw(shader);
        shader->flush();

        {
            Blending blending{BlendFunction::kAlphaLock};
            shader->setColor(RGBF(0.0, 1.0, 0.0));
            shapes::Rectangle(0.0, height * 0.4, width, height * 0.2).draw(shader);
            shader->flush();
        }

        framebuffer.finish();

        EXPECT_EQ(framebuffer.getPixel(width * 0.1, height * 0.5), RGBAF(0.0, 0.0, 0.0, 0.0));
        EXPECT_EQ(framebuffer.getPixel(width * 0.5, height * 0.1), RGBAF(0.0, 0.0, 0.0, 0.0));
        EXPECT_EQ(framebuffer.getPixel(width * 0.5, height * 0.5), RGBF(0.0, 1.0, 0.0));
    });
}

#endif // ONAIR_OKUI_HAS_NATIVE_APPLICATION
