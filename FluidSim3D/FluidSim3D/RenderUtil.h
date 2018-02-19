#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <cassert>
#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/transform.hpp>


//----------------------------------------------------------------------
//  Light Structure
//----------------------------------------------------------------------
struct Light {
	glm::vec3 position;
	glm::vec3 intensities; //a.k.a. the color of the light
};

//----------------------------------------------------------------------
// Transform Class
//----------------------------------------------------------------------
class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale) {}

	inline glm::mat4 GetModel() const {
		glm::mat4 posMatrix = glm::translate(m_pos);
		glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(m_scale);

		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline glm::vec3& GetPos() { return m_pos; }
	inline glm::vec3& GetRot() { return m_rot; }
	inline glm::vec3& GetScale() { return m_scale; }

	inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
	inline void SetRot(const glm::vec3& rot) { m_rot = rot; }
	inline void SetScale(const glm::vec3& scale) { m_scale = scale; }
private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
};

//----------------------------------------------------------------------
// Display Class
//----------------------------------------------------------------------
class Display
{
public:
	Display(int width, int height, const std::string& title, Transform* transform);

	void update(glm::vec3 &orientation, bool &pausePressed, bool &forwardPressed, int &visualMode);
	void clear(float r, float g, float b, float a);
	bool isClosed();

	~Display();
private:
	Display(const Display& other) {}
	void operator=(const Display& other) {}

	Transform* m_transform;

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
};

//----------------------------------------------------------------------
// Mesh Class
//----------------------------------------------------------------------
class Mesh {
public:
	Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<int> indices);

	void draw();
	void drawOutline();

	~Mesh();
private:
	enum {
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,	
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

//----------------------------------------------------------------------
// Line Class
//----------------------------------------------------------------------
class Line {
public:
	Line(std::vector<glm::vec3> vertices);
	
	void draw();

	~Line();
private:
	enum {
		POSITION_VB,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_verticesCount;
};

//----------------------------------------------------------------------
// Point Class
//----------------------------------------------------------------------
class Point {
public:
	Point(std::vector<glm::vec3> points);

	void draw();

	~Point();
private:
	enum {
		POSITION_VB,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_pointsCount;
};

//----------------------------------------------------------------------
// Camera Class
//----------------------------------------------------------------------
class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) {
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0, 1, 0);

	}

	inline glm::mat4 getViewProjection() const {
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}
private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	//for camera roation
	glm::vec3 m_forward;
	glm::vec3 m_up;
};

//----------------------------------------------------------------------
// Shader Class
//----------------------------------------------------------------------
class Shader {
public:
	Shader(const std::string& fileName);

	void bind();
	void update(const Transform* transform, const Camera* camera);
	void setLight(const Light& light);
	void setColor(float r, float g, float b, float a);
	
	~Shader();
private:
	static const unsigned int NUM_SHADERS = 2;

	enum {
		MODEL_U,
		CAMERA_U,
		LIGHT_POS_U,
		LIGHT_INTENSITY_U,
		COLOR,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];	
};

