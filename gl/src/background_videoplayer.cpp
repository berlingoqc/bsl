//
// Created by wq on 19-04-09.
//

#include <shaders.h>
#include "background_videoplayer.h"
#include "shaders_file.h"

namespace bsl::gl {
    RGBGL_Player::RGBGL_Player(int winW,int winH) {
        resize(winW, winH);

        if (!setupShader()) {
        }

        glGenVertexArrays(1, &vao);
    }



    void RGBGL_Player::setPixels(int i, int storesize, const void *data) {
        if(videos.size() > i) {
            //cv::flip(m, m, 0);
            glBindTexture(GL_TEXTURE_2D, i_tex);
            //use fast 4-byte alignment (default anyway) if possible
            //glPixelStorei(GL_UNPACK_ALIGNMENT, (m.step & 3) ? 1 : 4);

            //set length of one complete row in data (doesn't need to equal image.cols)
            //glPixelStorei(GL_UNPACK_ROW_LENGTH, m.step / m.elemSize());
            glPixelStorei(GL_UNPACK_ROW_LENGTH, storesize);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, videos[i]->w, videos[i]->h, GL_BGR, GL_UNSIGNED_BYTE, data);
            videos[i]->loaded = true;
        }

    }


    void RGBGL_Player::draw() {
        glBindVertexArray(vao);
        glUseProgram(prog);

        for(const auto& v : videos) {
            if(v->loaded) {
                glUniform4f(u_pos, v->x, v->y, v->w, v->h);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, i_tex);
                glUniform1i(glGetUniformLocation(prog, "texture"), 0);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            }

        }
    }

    void RGBGL_Player::remove(int i) {
    }

    void RGBGL_Player::add(PlayerStreamInfo info) {
        videos.push_back(std::make_unique<PlayerStreamInfo>(info));
        glGenTextures(1, &i_tex);
        glBindTexture(GL_TEXTURE_2D, i_tex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexImage2D(GL_TEXTURE_2D,     // Type of texture
                     0,                 // Pyramid level (for mip-mapping) - 0 is the top level
                     GL_RGB,            // Internal colour format to convert to
                     info.w,          // Image width  i.e. 640 for Kinect in standard mode
                     info.h,          // Image height i.e. 480 for Kinect in standard mode
                     0,                 // Border width in pixels (can either be 1 or 0)
                     GL_BGR, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                     GL_UNSIGNED_BYTE,  // Image data type
                     nullptr);        // The actual image data itself

    }

    void RGBGL_Player::resize(int winW, int winH) {
        assert(winW > 0 && winH > 0);

        win_w = winW;
        win_h = winH;

        pm = glm::mat4(1.0);
        pm = glm::ortho(0.0f, (float) win_w, (float) win_h, 0.0f, 0.0f, 100.0f);

        glUseProgram(prog);
        glUniformMatrix4fv(glGetUniformLocation(prog, "u_pm"), 1, GL_FALSE, &pm[0][0]);
    }



    bool RGBGL_Player::setupShader() {

        ShaderCompiler shad;
        if (!shad.CompileShaderProgram(VertexShader,FragmentShader)) {
            printf("Cant open the shaders\n");
            return false;
        }
        prog = shad.GetShaderID().getID();

        glUseProgram(prog);
        glUniform1i(glGetUniformLocation(prog, "texture"), 0);

        u_pos = glGetUniformLocation(prog, "draw_pos");

        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        resize(viewport[2], viewport[3]);

        return true;
    }

}