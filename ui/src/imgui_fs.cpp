#include "imgui_fs.h"

namespace bsl::ui {
void FileExplorer::SetCurrentDirectory(fs::path path)
	{
		if(!fs::exists(path))
		{
			throw DirectoryDontExistsException{ path.string() };
		}
		if(!fs::is_directory(path))
		{
			throw NotDirectoryException{ path.string() };
		}
		last_directory = current_directory;
		current_directory = path;
		selected_current = "";
		current_files.clear();
		for (auto& f : fs::directory_iterator(path)) {
			FileInfo fi;
			fi.file = fs::path(f);
			fi.is_folder = f.is_directory();
			if(get_folder && fi.is_folder)
			{
				current_files.emplace_back(fi);
				continue;
			}
			if (extension_filter.empty()) {
				current_files.emplace_back(fi);
				continue;
			}
			for (const auto& ext : extension_filter)
			{
				if(fi.file.extension() == ext)
				{
					current_files.emplace_back(fi);
					break;
				}
			}
		}
	}

	void FileExplorer::Start()
	{
		SetCurrentDirectory(fs::current_path());
		ImGui::OpenPopup("Ouvrir un fichier");
		is_close = false;
	}

	void FileExplorer::ChangeParent() // Change le r�pertoire courrant pour le parrent
	{
		if(!current_directory.has_parent_path())
		{
			return;
		}

		SetCurrentDirectory(current_directory.parent_path());
		
	}

	void FileExplorer::Draw(bool* p_open)
	{
		static char	buffer[100];

		static int track_line = 50, scroll_to_px = 200;

		ImGui::SetNextWindowSize(ImVec2(510, 300), ImGuiCond_FirstUseEver);
		if(ImGui::BeginPopupModal("Ouvrir un fichier",p_open))
		{

			strcpy(buffer, current_directory.string().c_str());

			if(ImGui::Button("<-"))
			{
				try
				{
					ChangeParent();
				} catch(std::exception& e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			ImGui::SameLine();
			ImGui::InputText("", buffer, 100);
			ImGui::SameLine();
			if(ImGui::Button("Ouvrir"))
			{
				// ouvre le nouveau repertoire ecrit
				try
				{
					fs::path p(buffer);
					SetCurrentDirectory(p);
				}
				catch (std::exception& e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			ImGui::Separator();
			ImGui::BeginGroup();
			ImGui::BeginChild("Fichiers", ImVec2(500, 250), true);
			ImGui::SetScrollFromPosY(ImGui::GetCursorStartPos().y + scroll_to_px);
			
			static int selected = -1;
			static FileInfo fi;

			int n = 0;
			for (const auto& f : current_files)
			{
				char buf[200];
				std::string s = f.file.filename().string();
				sprintf(buf, "%c %s", (f.is_folder) ? 'd' : 'f', s.c_str());
				if (ImGui::Selectable(buf, selected == n)) {
					if (selected == n)
					{
						fi = current_files[n];
						// double clique , si c'est un dossier on n'avance
						if (fi.is_folder) {
							fs::path c = current_directory / f.file.filename();
							SetCurrentDirectory(c);
						} else
						{
							// Choisit ce fichier comme �tant lui selectionner et ferme la fenetre
							selected_current = f.file;
							is_close = true;
							ImGui::CloseCurrentPopup();
						}
					}
					selected = n;
				}
				n++;
			}
			ImGui::EndChild();
			ImGui::EndGroup();
			ImGui::Text("Selectionner : %s", fi.file.string().c_str());
			ImGui::SameLine();
			if(ImGui::Button("Choisir"))
			{
				selected_current = fi.file;
				is_close = true;
				ImGui::CloseCurrentPopup();
			}
			if(ImGui::Button("Fermer"))
			{
				is_close = true;
				ImGui::CloseCurrentPopup();
			}
			
			ImGui::EndPopup();
		} 
	}
}