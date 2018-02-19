#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "RenderUtil.h"
#include "SimUtil.h"

class FluidRenderer3D
{
public:
	/*
	Constructor
	Args:
	label - pointer reference to the grid containing the geometry info
	x - gridwidth
	y - gridheight
	z - griddepth	
	*/
	FluidRenderer3D::FluidRenderer3D(SimUtil::Mat3Di *labels, int gridWidth, int gridHeight, int gridDepth);
	~FluidRenderer3D();
	/*
	Draws a marching cubes case
	*/
	void drawCubes(std::vector<glm::vec3> vertices, std::vector<int> indices, std::vector<glm::vec3> darkDots, std::vector<glm::vec3> brightDots);
	/*
	Draws the fluid according to choosen visualization mode
	Args:
	particles - location of the particles
	vertices - vertices of the triangle mesh
	normals - normals of the triangle mesh
	indicies - indicies of the vertices for the triangulation
	*/
	void draw(std::vector<glm::vec3> &particles, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<int> &indicies);
	
	bool isClosed() { return m_display->isClosed(); };
	bool isPaused() { return m_isPaused; };
	bool forwardPressed() { if (m_forwardPressed) { m_forwardPressed = false; return true; } return false; };

	glm::vec3 currentOrientation() { return m_orientation; };

private:
	//output window
	Display *m_display;
	//viewing Camera
	Camera *m_camera;
	//perspective transformation
	Transform *m_transform;
	//constant color shader
	Shader *m_colorShader;
	//shader with normal dependend shading
	Shader *m_normalShader;
	//Mesh with the geometry of the solids
	Mesh *m_meshSolid;
	//Line for the edges of the solids
	Line *m_borderSolid;
	//Global Light
	Light m_gLight;
	//If simulation is paused
	bool m_isPaused;
	//forward to next frame
	bool m_forwardPressed;
	/*
	visualization mode for rendering
	1 - Draw Fluid as Particles
	2 - Draw Fluid as Triangle Mesh
	*/
	int m_visualMode;
	//stores the current orientation
	glm::vec3 m_orientation;

	void initGeom(SimUtil::Mat3Di *label, int x, int y, int z);
	void initBorderLines(int x, int y, int z, int maxGridSize);
	void capturePicture(int frame);

	void bottomLineAt(std::vector<glm::vec3> &lines, int yLoc, int crop, int x, int y, int z, int maxGridSize);
	void sideLineAt(std::vector<glm::vec3> &lines, int xLoc, int crop, int bottomCrop, int topCrop, int x, int y, int z, int maxGridSize);
	void frontLineAt(std::vector<glm::vec3> &lines, int zLoc, int crop, int bottomCrop, int topCrop, int x, int y, int z, int maxGridSize);
};

