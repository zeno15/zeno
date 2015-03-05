#ifndef INCLUDED_SHADER_HPP
#define INCLUDED_SHADER_HPP

#include <string>
#include <vector>

#include "Vector3.hpp"

#include "Mat4x4.hpp"

class Shader
{
public:
	Shader(void);
	Shader(const std::string& _vertexPath, const std::string& _fragmentPath);
	~Shader(void);
	
	void loadVertexShader(const std::string& _vertexPath);
	void loadFragmentShader(const std::string& _fragmentPath);
	void loadShaders(const std::string& _vertexPath, const std::string& _fragmentPath);
	
	bool compileShader(void);
	std::string getCompileError(void);
	
	void bind(void);
	static void unbind(void);
	
	unsigned int getId(void);
	
	bool getLocationOfUniform(const std::string& _uniform);
	//~ Need to implement each for each type void passUniform
	//void passUniform(const std::string& _name, const Vector3<float>& _uniform);
	//void passUniform(const std::string& _name, const Mat4x4& _uniform);
	
private:
	std::string m_Error;
	
	std::string m_VertexShaderSource;
	std::string m_FragmentShaderSource;
	
	unsigned int m_ProgramId;
	
	std::vector<std::pair<std::string, int>>		m_UniformLocations;
};

#endif //~ INCLUDED_SHADER_HPP
