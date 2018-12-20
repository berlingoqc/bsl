#include "shaders.h"

namespace bsl::gl {
	bool ShaderCompiler::CompileShaderProgram(const char* codeVertex, const char* codeFragment) {
		unsigned int vMyShader = CompileMyShader(codeVertex, GL_VERTEX_SHADER, "VERTEX");
		if (vMyShader == 0) {
			return false;
		}

		unsigned int fMyShader = CompileMyShader(codeFragment, GL_FRAGMENT_SHADER, "FRAGMENT");
		if (fMyShader == 0) {
			return false;
		}

		// cr�e le programme de MyShader
		ID = glCreateProgram();
		glAttachShader(ID, vMyShader);
		glAttachShader(ID, fMyShader);
		glLinkProgram(ID);
		bool s = CheckCompileErrors(ID, "PROGRAM");
		glDeleteShader(vMyShader);
		glDeleteShader(fMyShader);
		return s;
	}

	bool ShaderCompiler::CompileShaderProgram(fs::path vertexPath, fs::path fragmentPath) {
		std::string codeVertex = ReadMyShaderCode(vertexPath.string().c_str());
		if (codeVertex == "") {
			return false;
		}
		codeVertex = SHADER_VERSION + codeVertex;
		std::string codeFragment = ReadMyShaderCode(fragmentPath.string().c_str());
		if (codeFragment == "") {
			return false;
		}
		codeFragment = SHADER_VERSION + codeFragment;
		return CompileShaderProgram(codeVertex.c_str(),codeFragment.c_str());
	}

	Shrapper ShaderCompiler::GetShaderID() {
		return Shrapper(ID);
	}

	void ShaderCompiler::PrintErrorStack() {
		std::cout << ErrorMessage << std::endl;
	}


	// ReadMyShaderCode lit le code du MyShader depuis son fichier et le retourne
	std::string ShaderCompiler::ReadMyShaderCode(const char * filePath) {
		std::ifstream file;
		// ouvre les fichier
		file.open(filePath);
		if (!file.is_open()) {
			printf("Echec de la lecture du shader %s", filePath);
			return "";
		}

		// lit l'int�rieur dans un stream
		std::stringstream stream;
		stream << file.rdbuf();

		// close les file handle
		file.close();
		return stream.str();
;
	}
	// CompileMyShader compile le MyShader
	unsigned int ShaderCompiler::CompileMyShader(std::string code, GLenum type, std::string nameType) {
		unsigned int item;
		int success;

		const char* sPtr = code.c_str();
		const int sSize = code.size();

		item = glCreateShader(type);
		glShaderSource(item, 1, &sPtr, &sSize);
		glCompileShader(item);
		if (CheckCompileErrors(item, nameType)) {
			return item;
		}
		// retourne 0 si la compilation a fail
		return 0;
	}

	bool ShaderCompiler::CheckCompileErrors(GLuint MyShader, std::string nameType) {
		GLint success;
		char infoLog[1024];
		if (nameType != "PROGRAM") {
			glGetShaderiv(MyShader, GL_COMPILE_STATUS, &success);
			if (success == GL_FALSE) {
				int infoLength = 0;
				glGetShaderiv(MyShader, GL_INFO_LOG_LENGTH, &infoLength);
				glGetShaderInfoLog(MyShader, infoLength, NULL, infoLog);
				std::cerr << "ERROR Compilation of type : " << nameType << std::endl << infoLog << std::endl;
				return false;
			}
		}
		else {
			glGetProgramiv(MyShader, GL_LINK_STATUS, &success);
			if (success == GL_FALSE) {
				GLint maxLen = 0;
				glGetProgramInfoLog(MyShader, 1024, &maxLen, infoLog);
				std::string s(infoLog);
				std::cerr << "ERROR Compilation of typw : " << nameType << std::endl << infoLog << std::endl;
				strcpy(ErrorMessage, infoLog);
				return false;
			}
		}
		return true;
	}
};