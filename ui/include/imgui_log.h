#ifndef IMGUI_LOG_H
#define IMGUI_LOG_H

#include "imgui.h"



namespace bsl::ui {



struct AppLog
{
	ImGuiTextBuffer     Buf;
	ImGuiTextFilter     Filter;
	ImVector<int>       LineOffsets;        // Index to lines offset
	bool                ScrollToBottom;

	void    Clear() { Buf.clear(); LineOffsets.clear(); }

	void    AddLog(const char* fmt, ...) IM_FMTARGS(2);

	void    Draw(const char* title, bool* p_open = nullptr);
};

}



#endif