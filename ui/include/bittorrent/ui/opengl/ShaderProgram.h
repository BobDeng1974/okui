#pragma once

#include "bittorrent/ui/config.h"

#include "bittorrent/ui/opengl/Shader.h"

namespace bittorrent {
namespace ui {
namespace opengl {

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();

	void attachShader(const Shader& shader);

	inline void attachShaders() {}

	template <typename T, typename... Rem>
	void attachShaders(T&& shader, Rem&&... rem) {
		if (!_error.empty()) { return; }
		attachShader(std::forward<T>(shader));
		attachShaders(std::forward<Rem>(rem)...);
	}
	
	void bindAttribute(GLuint id, const char* name);
	
	void link();
	
	const std::string& error() const { return _error; } 
	
	GLuint id() const { return _program; }
	void use() const { glUseProgram(_program); }

	struct Uniform {
		Uniform() {}
		explicit Uniform(GLint location) : location(location) {}
		void operator=(GLint n) { glUniform1i(location, n); }

		GLint location = GL_INVALID_VALUE;
	};
	
	Uniform uniform(const char* name) { return Uniform(glGetUniformLocation(_program, name)); }

private:
	std::string _error;
	GLuint _program = 0;
};

}}}