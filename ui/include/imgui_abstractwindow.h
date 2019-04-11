//
// Created by wq on 19-04-10.
//

#ifndef BSL_IMGUI_ABSTRACTWINDOW_H
#define BSL_IMGUI_ABSTRACTWINDOW_H

namespace bsl::ui {
    class AbstractWindow {
    public:
        virtual void Draw(bool *over, bool *p_open = nullptr) {}
    };
}

#endif //BSL_IMGUI_ABSTRACTWINDOW_H
