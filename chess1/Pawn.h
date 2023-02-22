#pragma once
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>
#include "../gl/glut.h"

typedef struct _pos {
	int r;
	int c;
};


#define PWNFILE "pwn.obj"

const struct OBJ_COLOR {
	GLfloat red, green, blue;
	OBJ_COLOR() : red(1.0), green(1.0), blue(1.0) {}
} OBJ_COLOR;

typedef struct vertex {
	double x, y, z;
} vertex;
typedef struct face_triangle {
	unsigned long v1, v2, v3;
} face_triangle;
typedef struct face_quad {
	unsigned long v1, v2, v3, v4;
} face_quad;

class Pawn {
public:
	Pawn();

	void Draw();
	void Reset();
	void SetIndex(int idx);
	void SetColor(int ired, int igreen, int iblue);
	void GetCurPos();
	bool SetNewPos(float step);
	void Move();

private:
	void obj_parse(char* file_line);
	void open_obj();
	void draw_obj();
	void calculate_normal(face_triangle f, GLdouble* normal);


	std::vector<vertex> vertices;
	std::vector<face_quad> faces_quads;
	std::vector<face_triangle> faces_triangles;


	bool is_quad;
	bool render_mode; // true = solid body, false = wireframe



	int index;
	float rpos, cpos;
	int colorR, colorG, colorB;
	int isTexture;
	float newrpos, newcpos;
	std::vector<float> lastrpos, lastcpos;
	_pos posval;
};

