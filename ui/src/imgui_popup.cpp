#include "imgui_popup.h"

void ShowErrorMessage(std::string titre, std::string message)
{
	if(ImGui::BeginPopupModal(titre.c_str()))
	{
		ImGui::Separator();
		ImGui::Text(message.c_str());
		ImGui::Separator();
		if(ImGui::Button("Fermer"))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	
}