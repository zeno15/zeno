#ifndef INCLUDED_ZENO_GRAPHICS_SHADER_HPP
#define INCLUDED_ZENO_GRAPHICS_SHADER_HPP

#include <string>
#include <vector>

#include <zeno/System/Vector2.hpp>
#include <zeno/System/Vector3.hpp>
#include <zeno/System/Mat4x4.hpp>

#include <zeno/Graphics/Colour.hpp>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	OpenGL Shader class
//
////////////////////////////////////////////////////////////
class Shader
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Default constructor
	//
	////////////////////////////////////////////////////////////
	Shader(void);
	////////////////////////////////////////////////////////////
	//
	//	Constructor which takes the paths to the shaders files
	//
	////////////////////////////////////////////////////////////
	Shader(const std::string& _vertexPath, const std::string& _fragmentPath);
	////////////////////////////////////////////////////////////
	//
	//	Deconstructor, deketes the shader program
	//
	////////////////////////////////////////////////////////////
	~Shader(void);

	////////////////////////////////////////////////////////////
	//
	//	Loads the vertex shader from its file
	//
	////////////////////////////////////////////////////////////
	void loadVertexShader(const std::string& _vertexPath);
	////////////////////////////////////////////////////////////
	//
	//	Loads the geometry shader from its file
	//
	////////////////////////////////////////////////////////////
	void loadGeometryShader(const std::string& _geometryPath);
	////////////////////////////////////////////////////////////
	//
	//	Loads the fragment shader from its file
	//
	////////////////////////////////////////////////////////////
	void loadFragmentShader(const std::string& _fragmentPath);
	////////////////////////////////////////////////////////////
	//
	//	Loads both shaders from their files
	//
	////////////////////////////////////////////////////////////
	void loadShaders(const std::string& _vertexPath, const std::string& _fragmentPath);
	////////////////////////////////////////////////////////////
	//
	//	Loads both shaders from the given strings
	//
	////////////////////////////////////////////////////////////
	void loadShadersFromStrings(const std::string& _vertexSource, const std::string& _fragmentSource);
	
	////////////////////////////////////////////////////////////
	//
	//	Loads vertex, geometry and fragment shaders from files
	//
	////////////////////////////////////////////////////////////
	void loadVGFShaders(const std::string& _vertexPath, const std::string& _geometryPath, const std::string& _fragmentPath);


	////////////////////////////////////////////////////////////
	//
	//	Returns whether or not the shaders compile successfully
	//
	////////////////////////////////////////////////////////////
	bool compileShader(void);
	////////////////////////////////////////////////////////////
	//
	//	Used to get the compilation error if compileShader 
	//	returns false
	//
	////////////////////////////////////////////////////////////
	std::string getCompileError(void);

	////////////////////////////////////////////////////////////
	//
	//	Binds the shader for rendering use
	//
	////////////////////////////////////////////////////////////
	void bind(void);
	////////////////////////////////////////////////////////////
	//
	//	Unbinds the currently bound shader
	//
	////////////////////////////////////////////////////////////
	static void unbind(void);

	////////////////////////////////////////////////////////////
	//
	//	Gets the program Id
	//
	////////////////////////////////////////////////////////////
	unsigned int getId(void);

	////////////////////////////////////////////////////////////
	//
	//	Returns whether or not the given uniform is found within
	//	the shader
	//
	////////////////////////////////////////////////////////////
	bool getLocationOfUniform(const std::string& _uniform);
	////////////////////////////////////////////////////////////
	//
	//	Passes the uniform with the given name of type Vector2
	//	to the shader
	//
	////////////////////////////////////////////////////////////
	void passUniform(const std::string& _name, const Vector2<float>& _uniform);
	////////////////////////////////////////////////////////////
	//
	//	Passes the uniform with the given name of type Vector3
	//	to the shader
	//
	////////////////////////////////////////////////////////////
	void passUniform(const std::string& _name, const Vector3<float>& _uniform);
	////////////////////////////////////////////////////////////
	//
	//	Passes the uniform with the given name of type Vector4
	//	to the shader
	//
	////////////////////////////////////////////////////////////
	void passUniform(const std::string& _name, const Vector4<float>& _uniform);
	////////////////////////////////////////////////////////////
	//
	//	Passes the uniform with the given name of type Colour
	//	to the shader
	//
	////////////////////////////////////////////////////////////
	void passUniform(const std::string& _name, const Colour& _uniform);
	////////////////////////////////////////////////////////////
	//
	//	Passes the uniform with the given name of type Mat4x4
	//	to the shader
	//
	////////////////////////////////////////////////////////////
	void passUniform(const std::string& _name, const Mat4x4& _uniform);
	
private:
	////////////////////////////////////////////////////////////
	//
	//
	//
	////////////////////////////////////////////////////////////
	bool			m_UsingGeometry;

	////////////////////////////////////////////////////////////
	//
	//	Stores the error associated with the last compilation
	//
	////////////////////////////////////////////////////////////
	std::string m_Error;

	////////////////////////////////////////////////////////////
	//
	//	Contains the vertex shader
	//
	////////////////////////////////////////////////////////////
	std::string m_VertexShaderSource;
	////////////////////////////////////////////////////////////
	//
	//	Contains the geometry shader
	//
	////////////////////////////////////////////////////////////
	std::string m_GeometryShaderSource;
	////////////////////////////////////////////////////////////
	//
	//	Contains the fragment shader
	//
	////////////////////////////////////////////////////////////
	std::string m_FragmentShaderSource;

	////////////////////////////////////////////////////////////
	//
	//	The shader program id
	//
	////////////////////////////////////////////////////////////
	unsigned int m_ProgramId;

	////////////////////////////////////////////////////////////
	//
	//	Vector of uniforms and their locations
	//
	////////////////////////////////////////////////////////////
	std::vector<std::pair<std::string, int>>		m_UniformLocations;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_SHADER_HPP
