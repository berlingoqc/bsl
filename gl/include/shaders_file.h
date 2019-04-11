//
// Created by wq on 19-04-09.
//

#ifndef BSL_SHADER_VIDEOPLAYER_H
#define BSL_SHADER_VIDEOPLAYER_H

const char* FragmentShader = "uniform sampler2D texture;\n"
                             "\n"
                             "in vec2 v_coord;\n"
                             "\n"
                             "out vec4 color;\n"
                             "\n"
                             "void main() {\n"
                             "\tcolor = texture2D(texture, v_coord);\n"
                             "}";

const static char* VertexShader = "uniform mat4 u_pm;\n"
                                  "uniform vec4 draw_pos;\n"
                                  "\n"
                                  "const vec2 verts[4] = vec2[] (\n"
                                  "  vec2(-0.5,  0.5),\n"
                                  "  vec2(-0.5, -0.5),\n"
                                  "  vec2( 0.5,  0.5),\n"
                                  "  vec2( 0.5, -0.5)\n"
                                  ");\n"
                                  "\n"
                                  "const vec2 texcoords[4] = vec2[] (\n"
                                  "  vec2(0.0, 1.0),\n"
                                  "  vec2(0.0, 0.0),\n"
                                  "  vec2(1.0, 1.0),\n"
                                  "  vec2(1.0, 0.0)\n"
                                  ");\n"
                                  "\n"
                                  "out vec2 v_coord;\n"
                                  "\n"
                                  "void main() {\n"
                                  "   vec2 vert = verts[gl_VertexID];\n"
                                  "   vec4 p = vec4((0.5 * draw_pos.z) + draw_pos.x + (vert.x * draw_pos.z),\n"
                                  "                 (0.5 * draw_pos.w) + draw_pos.y + (vert.y * draw_pos.w),\n"
                                  "                 0, 1);\n"
                                  "   gl_Position = u_pm * p;\n"
                                  "   v_coord = texcoords[gl_VertexID];\n"
                                  "}";

#endif //BSL_SHADER_VIDEOPLAYER_H
