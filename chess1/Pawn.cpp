#include "Pawn.h"
#include "primitive.h"


#pragma warning(disable:4996)
int pawnpos[16][2] = {
	1,0,
	1,1,
	1,2,
	1,3,
	1,4,
	1,5,
	1,6,
	1,7,
	6,0,
	6,1,
	6,2,
	6,3,
	6,4,
	6,5,
	6,6,
	6,7
};

Pawn::Pawn()
{
	rpos = 0;// row;
	cpos = 0;// col;
	colorR = 255;
	colorG = 255;
	colorB = 255;
	isTexture = 1;
	newrpos = 0.0;
	newcpos = 0.0;
	for (int i = 0; i < 16; i++)
	{
		lastrpos.push_back((float)(1.0 * (pawnpos[i][0] - 3.5)));
		lastcpos.push_back((float)(1.0 * (pawnpos[i][1] - 3.5)));
	}

	open_obj();
}

void Pawn::Reset()
{
	lastrpos.clear();
	lastcpos.clear();
	for (int i = 0; i < 16; i++)
	{
		lastrpos.push_back((float)(1.0 * (pawnpos[i][0] - 3.5)));
		lastcpos.push_back((float)(1.0 * (pawnpos[i][1] - 3.5)));
	}
}

void Pawn::SetIndex(int idx)
{
	index= idx;
}
void Pawn::SetColor(int ired, int igreen, int iblue)
{
	colorR = ired;
	colorG = igreen;
	colorB = iblue;
}
void Pawn::Draw()
{

	float r, c;
	rpos = r = lastrpos[index];
	cpos = c = lastcpos[index];

	glPushMatrix();
	glTranslatef(r, 0.0f, c);

	glScaled(0.0125, 0.0125, 0.0125);
	draw_obj();
	
	glPopMatrix();
	glFlush();

}

void Pawn::GetCurPos()
{
	lastrpos[index] = rpos;
	lastcpos[index] = cpos;
}

bool Pawn::SetNewPos(float step)
{
	newrpos = (float)(1.0 * (pawnpos[index][0] - 3.5)) + step;
	newcpos = cpos;

	return true;
}

void Pawn::Move()
{
	float r, c;
	rpos = r = newrpos;
	cpos = c = newcpos;
   
	glPushMatrix();
	glTranslatef(r, 0.0f, c);
	
	glScaled(0.0125, 0.0125, 0.0125);
	draw_obj();
	
	glPopMatrix();
}


void Pawn::calculate_normal(face_triangle f, GLdouble* normal) {
	// x
	normal[0] = (vertices[f.v2 - 1].y - vertices[f.v1 - 1].y) * (vertices[f.v3 - 1].z - vertices[f.v1 - 1].z)
		- (vertices[f.v3 - 1].y - vertices[f.v1 - 1].y) * (vertices[f.v2 - 1].z - vertices[f.v1 - 1].z);
	// y
	normal[1] = (vertices[f.v2 - 1].z - vertices[f.v1 - 1].z) * (vertices[f.v3 - 1].x - vertices[f.v1 - 1].x)
		- (vertices[f.v2 - 1].x - vertices[f.v1 - 1].x) * (vertices[f.v3 - 1].z - vertices[f.v1 - 1].z);
	// z
	normal[2] = (vertices[f.v2 - 1].x - vertices[f.v1 - 1].x) * (vertices[f.v3 - 1].y - vertices[f.v1 - 1].y)
		- (vertices[f.v3 - 1].x - vertices[f.v1 - 1].x) * (vertices[f.v2 - 1].y - vertices[f.v1 - 1].y);
}

void Pawn::draw_obj()
{
	/*
		if (render_mode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		*/
	if (is_quad) {
		for (face_quad f : faces_quads) {
			// Calculate normal by calculating two tri normals & averaging
			face_triangle f_tri1 = { f.v1, f.v2, f.v3 };
			face_triangle f_tri2 = { f.v2, f.v3, f.v4 };
			GLdouble normal_tri1[3];
			GLdouble normal_tri2[3];
			calculate_normal(f_tri1, normal_tri1);
			calculate_normal(f_tri2, normal_tri2);
			GLdouble normal[3] = {
					(normal_tri1[0] + normal_tri2[0]) / 2,
					(normal_tri1[1] + normal_tri2[1]) / 2,
					(normal_tri1[2] + normal_tri2[2]) / 2
			};

			glBegin(GL_QUADS);
			glColor3f(colorR / 255, colorG / 255, colorB / 255);
			glNormal3dv(normal);
			glVertex3d(vertices[f.v1 - 1].x, vertices[f.v1 - 1].y, vertices[f.v1 - 1].z);
			glVertex3d(vertices[f.v2 - 1].x, vertices[f.v2 - 1].y, vertices[f.v2 - 1].z);
			glVertex3d(vertices[f.v3 - 1].x, vertices[f.v3 - 1].y, vertices[f.v3 - 1].z);
			glVertex3d(vertices[f.v4 - 1].x, vertices[f.v4 - 1].y, vertices[f.v4 - 1].z);
			glEnd();
		}
	}
	else {
		for (face_triangle f : faces_triangles) {
			GLdouble normal[3];
			calculate_normal(f, normal);
			glBegin(GL_TRIANGLES);
			
//			glColor3d(colorR/255, colorG/255, colorB/255);
			glColor3d(colorR / 255.0f, colorG / 255.0f, colorB / 255.0f);


			glNormal3dv(normal);
			glVertex3d(vertices[f.v1 - 1].x, vertices[f.v1 - 1].y, vertices[f.v1 - 1].z);
			glVertex3d(vertices[f.v2 - 1].x, vertices[f.v2 - 1].y, vertices[f.v2 - 1].z);
			glVertex3d(vertices[f.v3 - 1].x, vertices[f.v3 - 1].y, vertices[f.v3 - 1].z);
			glEnd();
		}
	}
	//glFlush();
}

void Pawn::obj_parse(char* file_line) {

	if (file_line[0] == '\0') {
		// End of file
		return;
	}

	char* tokenized;
	tokenized = strtok(file_line, " ");
	char first_char = tokenized[0];

	if (first_char == '#') {
		// Comment line, ignore
		return;
	}
	else if (first_char == 'v') {
		// Vertex

		double x = strtod(strtok(NULL, " "), NULL);
		double y = strtod(strtok(NULL, " "), NULL);
		double z = strtod(strtok(NULL, " "), NULL);

		vertex v = { x * 20, y * 20, z * 20 };
		vertices.push_back(v);
	}
	else if (first_char == 'f') {
		// Face

		unsigned long v1 = strtoul(strtok(NULL, " "), NULL, 0);
		unsigned long v2 = strtoul(strtok(NULL, " "), NULL, 0);
		unsigned long v3 = strtoul(strtok(NULL, " "), NULL, 0);

		unsigned long v4;
		char* v4_str = strtok(NULL, " ");
		if (v4_str != NULL) {
			// Face is a quad
			v4 = strtoul(v4_str, NULL, 0);

			face_quad f = { v1, v2, v3, v4 };
			faces_quads.push_back(f);
		}
		else {
			// Face is a triangle
			face_triangle f = { v1, v2, v3 };
			faces_triangles.push_back(f);
		}
	}
}

void Pawn::open_obj() {

	//// Argument parsing ////


	std::string filename = PWNFILE;

	std::regex obj_regex(".+(\\.obj)$");
	if (!std::regex_match(filename, obj_regex)) {
		// Filename is invalid
		std::cout << "This application only accepts *.obj files, exiting..." << std::endl;
		exit(1);
	}

	//// Filename accepted, attempting to open ////

	std::cout << "Opening file: " << filename << std::endl;

	std::ifstream file_stream;
	file_stream.open(filename, std::ifstream::in);

	if ((file_stream.rdstate() & std::ifstream::failbit) != 0) {
		std::cerr << "Error opening " << filename << std::endl;
		exit(1);
	}

	while (file_stream.good()) {
		char file_line[100];
		file_stream.getline(file_line, 100);
		obj_parse(file_line);
	}

	file_stream.close();

	is_quad = (faces_quads.size() > faces_triangles.size());
}
