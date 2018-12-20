#ifndef IMGUI_FS_H
#define IMGUI_FS_H

#include "imgui.h"
#include <cstdarg>
#include <iostream>

#include <filesystem>

namespace bsl::ui {

namespace fs = std::filesystem;

struct DirectoryDontExistsException : public std::exception
{
	std::string directory;

	DirectoryDontExistsException(std::string dir)
	{
		directory = dir;
	}

	const char* what() const throw()
	{
		return ("Le repertoire n'existe pas " + directory).c_str();
	}
};
struct NotDirectoryException : public std::exception
{
	std::string file;

	NotDirectoryException(std::string f)
	{
		file = f;
	}

	const char* what() const throw()
	{
		return ("Ce fichier n'est pas un dossier " + file).c_str();
	}
};
struct FileInfo
{
	fs::path	file;
	bool		is_folder;
};

struct FileExplorer
{
	fs::path			current_directory;

	fs::path			last_directory;

	fs::path			selected_current;

	std::vector<FileInfo>	current_files;

	std::vector<std::string>		extension_filter;

	bool				is_close = true;

	bool				get_folder = false;


	void SetCurrentDirectory(fs::path path);
	

	void Start();


	void ChangeParent();

	void Draw(bool* p_open = nullptr);
};

}



#endif