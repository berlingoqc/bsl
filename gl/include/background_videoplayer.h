//
// Created by wq on 19-04-09.
//


#ifndef BSL_BACKGROUND_VIDEOPLAYER_H
#define BSL_BACKGROUND_VIDEOPLAYER_H

#include "header.h"

namespace bsl::gl {


    struct PlayerStreamInfo {
        int w = 0;
        int h = 0;
        int x = 0;
        int y = 0;
        GLuint tex = 0;

        bool loaded = false;
    };

    class RGBGL_Player {

        int win_w = 0;
        int win_h = 0;

        GLuint vao = 0;
        GLuint i_tex = 0;

        GLuint i2_tex = 0;

        GLuint vert = 0;
        GLuint frag = 0;

        GLuint prog = 0;
        GLint u_pos = -1;

        glm::mat4 pm = glm::mat4(1.0);


        std::vector<std::unique_ptr<PlayerStreamInfo>> videos;

    public:
        RGBGL_Player(int winW,int winH);

        void setPixels(int i, int pixelstorei, const void *);

        void draw();

        void remove(int i);

        void add(PlayerStreamInfo info);

        void resize(int winW, int winH);

    private:
        bool setupShader();
    };
}
#endif //BSL_BACKGROUND_VIDEOPLAYER_H
