//#define _CRT_SECURE_NO_WARNINGS
//
////뭬중심장찍힘
//#include <vector>
//#include <iostream>
//#include <windows.h>
//#include <math.h>
////#include "opencv2/cvconfig.h"
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/freeglut.h>
////#include <gl\glm\glm.hpp>
//
//#include "opencv2/opencv.hpp"
//#include "opencv2/core/opengl.hpp"
//
////#include <windows.h>
////#include <iostream>
//#include <fstream>
//#include <stdio.h>
//#include <string.h>
////#include <GL/gl.h>
////#include <GL/glu.h>
////#include <GL/glut.h>
////#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <string>
////#include <vector>
//#include <cmath>
//
////#include "opencv2/core/cuda.hpp"
////#include "opencv2/highgui/highgui.hpp"
//
//using namespace std;
//using namespace cv;
//using namespace cv::cuda;
//
//int cnt_cv = 0;
//int cnt_gl = 0;
////
//vector<Mat> Projection9;
//vector<Mat> modelview9;
////vector<Mat>::iterator Projection9_Data;
////vector<Mat>::iterator modelview9_Data;
////Mat Projection;
////Mat modelview;
//Mat Projection(4, 4, CV_64FC1);
//Mat modelview(4, 4, CV_64FC1);
//
//Mat Projection0(4, 4, CV_64FC1);
//Mat modelview0(4, 4, CV_64FC1);
//Mat Projection1(4, 4, CV_64FC1);
//Mat modelview1(4, 4, CV_64FC1);
//Mat Projection2(4, 4, CV_64FC1);
//Mat modelview2(4, 4, CV_64FC1);
//Mat Projection3(4, 4, CV_64FC1);
//Mat modelview3(4, 4, CV_64FC1);
//Mat Projection4(4, 4, CV_64FC1);
//Mat modelview4(4, 4, CV_64FC1);
//Mat Projection5(4, 4, CV_64FC1);
//Mat modelview5(4, 4, CV_64FC1);
//Mat Projection6(4, 4, CV_64FC1);
//Mat modelview6(4, 4, CV_64FC1);
//
//const float zNear = 0.05;
//const float zFar = 500.0;
//int width = 640;
//int height = 480;
////
//
//int win_width = 0;
//int win_height = 0;
//
//// углы поворота
//float angx = 55, angy = 45;
////float angx = 0.0, angy = 0.0;
//float angstep = 5.0;
//String winname = "opengl";
//int argc2; char* argv2[];
////opencv
////무게중심
//Point2f center = 0;
//Mat src; Mat src2; Mat src_gray; //Mat fixed;
//int thresh = 100;
//int max_thresh = 255;
//RNG rng(12345);
//Mat threshold_output;
//vector<vector<Point> > contours;
//vector<Vec4i> hierarchy;
//vector<Point2f> imagePoints, imageFramePoints, imageOrigin, imagePoints2;
//vector<Point3f> boardPoints, framePoints, boardPoints2;
//Mat rvec = Mat(Size(3, 1), CV_64F);
//Mat tvec = Mat(Size(3, 1), CV_64F);
//Mat R;
//Mat T2(4, 4, R.type()); // T is 4x4
//
//Mat glViewMatrix2 = cv::Mat::zeros(4, 4, CV_64FC1);
//GLuint texture;  // array in which the generated texture names are stored
//
//
//int GetRotation(int code_matrix[6][6]);
//inline void swap(Point2f &c1, Point2f &c2);
//void RotateMatrix(int code_matrix[6][6], int angle_idx);
//void RotateCorner(Point2f corner[4], int angle_idx);
//int CalcMarkerID(int code_matrix[6][6]);
//void on_opengl2(void* param);
//void generateProjectionModelview(const cv::Mat& calibration, const cv::Mat& rotation, const cv::Mat& translation, cv::Mat& projection, cv::Mat& modelview);
//GLfloat* convertMatrixType(const cv::Mat& m);
//
///************************************************************************
//Window
//************************************************************************/
//
//typedef struct {
//	int width;
//	int height;
//	char* title;
//
//	float field_of_view_angle;
//	float z_near;
//	float z_far;
//} glutWindow;
//
//
//
///***************************************************************************
//OBJ Loading
//***************************************************************************/
//
//class Model_OBJ
//{
//public:
//	Model_OBJ();
//	float* Model_OBJ::calculateNormal(float* coord1, float* coord2, float* coord3);
//	int Model_OBJ::Load(char *filename);	// Loads the model
//	void Model_OBJ::Draw();					// Draws the model on the screen
//	void Model_OBJ::Release();				// Release the model
//
//	float* normals;							// Stores the normals
//	float* Faces_Triangles;					// Stores the triangles
//	float* vertexBuffer;					// Stores the points which make the object
//	long TotalConnectedPoints;				// Stores the total number of connected verteces
//	long TotalConnectedTriangles;			// Stores the total number of connected triangles
//
//};
//
//
//#define POINTS_PER_VERTEX 3
//#define TOTAL_FLOATS_IN_TRIANGLE 9
//using namespace std;
//
//Model_OBJ::Model_OBJ()
//{
//	this->TotalConnectedTriangles = 0;
//	this->TotalConnectedPoints = 0;
//}
//
//float* Model_OBJ::calculateNormal(float *coord1, float *coord2, float *coord3)
//{
//	/* calculate Vector1 and Vector2 */
//	float va[3], vb[3], vr[3], val;
//	va[0] = coord1[0] - coord2[0];
//	va[1] = coord1[1] - coord2[1];
//	va[2] = coord1[2] - coord2[2];
//
//	vb[0] = coord1[0] - coord3[0];
//	vb[1] = coord1[1] - coord3[1];
//	vb[2] = coord1[2] - coord3[2];
//
//	/* cross product */
//	vr[0] = va[1] * vb[2] - vb[1] * va[2];
//	vr[1] = vb[0] * va[2] - va[0] * vb[2];
//	vr[2] = va[0] * vb[1] - vb[0] * va[1];
//
//	/* normalization factor */
//	val = sqrt(vr[0] * vr[0] + vr[1] * vr[1] + vr[2] * vr[2]);
//
//	float norm[3];
//	norm[0] = vr[0] / val;
//	norm[1] = vr[1] / val;
//	norm[2] = vr[2] / val;
//
//
//	return norm;
//}
//
//Model_OBJ obj;
//Model_OBJ obj1;
//Model_OBJ obj2;
//Model_OBJ obj3;
//Model_OBJ obj4;
//Model_OBJ obj5;
//Model_OBJ obj6;
//float g_rotation;
//glutWindow win;
//
//int Model_OBJ::Load(char* filename)
//{
//	string line;
//	ifstream objFile(filename);
//	if (objFile.is_open())													// If obj file is open, continue
//	{
//		objFile.seekg(0, ios::end);										// Go to end of the file, 
//		long fileSize = objFile.tellg();									// get file size
//		objFile.seekg(0, ios::beg);										// we'll use this to register memory for our 3d model
//
//		vertexBuffer = (float*)malloc(fileSize);							// Allocate memory for the verteces
//		Faces_Triangles = (float*)malloc(fileSize * sizeof(float));			// Allocate memory for the triangles
//		normals = (float*)malloc(fileSize * sizeof(float));					// Allocate memory for the normals
//
//		int triangle_index = 0;												// Set triangle index to zero
//		int normal_index = 0;												// Set normal index to zero
//
//		while (!objFile.eof())											// Start reading file data
//		{
//			getline(objFile, line);											// Get line from file
//
//			if (line.c_str()[0] == 'v')										// The first character is a v: on this line is a vertex stored.
//			{
//				line[0] = ' ';												// Set first character to 0. This will allow us to use sscanf
//
//				sscanf(line.c_str(), "%f %f %f ",							// Read floats from the line: v X Y Z
//					&vertexBuffer[TotalConnectedPoints],
//					&vertexBuffer[TotalConnectedPoints + 1],
//					&vertexBuffer[TotalConnectedPoints + 2]);
//
//				TotalConnectedPoints += POINTS_PER_VERTEX;					// Add 3 to the total connected points
//			}
//			if (line.c_str()[0] == 'f')										// The first character is an 'f': on this line is a point stored
//			{
//				line[0] = ' ';												// Set first character to 0. This will allow us to use sscanf
//
//				int vertexNumber[4] = { 0, 0, 0 };
//				sscanf(line.c_str(), "%i%i%i",								// Read integers from the line:  f 1 2 3
//					&vertexNumber[0],										// First point of our triangle. This is an 
//					&vertexNumber[1],										// pointer to our vertexBuffer list
//					&vertexNumber[2]);										// each point represents an X,Y,Z.
//
//				vertexNumber[0] -= 1;										// OBJ file starts counting from 1
//				vertexNumber[1] -= 1;										// OBJ file starts counting from 1
//				vertexNumber[2] -= 1;										// OBJ file starts counting from 1
//
//
//																			/********************************************************************
//																			* Create triangles (f 1 2 3) from points: (v X Y Z) (v X Y Z) (v X Y Z).
//																			* The vertexBuffer contains all verteces
//																			* The triangles will be created using the verteces we read previously
//																			*/
//
//				int tCounter = 0;
//				for (int i = 0; i < POINTS_PER_VERTEX; i++)
//				{
//					Faces_Triangles[triangle_index + tCounter] = vertexBuffer[3 * vertexNumber[i]];
//					Faces_Triangles[triangle_index + tCounter + 1] = vertexBuffer[3 * vertexNumber[i] + 1];
//					Faces_Triangles[triangle_index + tCounter + 2] = vertexBuffer[3 * vertexNumber[i] + 2];
//					tCounter += POINTS_PER_VERTEX;
//				}
//
//				/*********************************************************************
//				* Calculate all normals, used for lighting
//				*/
//				float coord1[3] = { Faces_Triangles[triangle_index], Faces_Triangles[triangle_index + 1],Faces_Triangles[triangle_index + 2] };
//				float coord2[3] = { Faces_Triangles[triangle_index + 3],Faces_Triangles[triangle_index + 4],Faces_Triangles[triangle_index + 5] };
//				float coord3[3] = { Faces_Triangles[triangle_index + 6],Faces_Triangles[triangle_index + 7],Faces_Triangles[triangle_index + 8] };
//				float *norm = this->calculateNormal(coord1, coord2, coord3);
//
//				tCounter = 0;
//				for (int i = 0; i < POINTS_PER_VERTEX; i++)
//				{
//					normals[normal_index + tCounter] = norm[0];
//					normals[normal_index + tCounter + 1] = norm[1];
//					normals[normal_index + tCounter + 2] = norm[2];
//					tCounter += POINTS_PER_VERTEX;
//				}
//
//				triangle_index += TOTAL_FLOATS_IN_TRIANGLE;
//				normal_index += TOTAL_FLOATS_IN_TRIANGLE;
//				TotalConnectedTriangles += TOTAL_FLOATS_IN_TRIANGLE;
//			}
//		}
//		objFile.close();														// Close OBJ file
//	}
//	else
//	{
//		cout << "Unable to open file";
//	}
//	return 0;
//}
//
//void Model_OBJ::Release()
//{
//	free(this->Faces_Triangles);
//	free(this->normals);
//	free(this->vertexBuffer);
//}
//
//void Model_OBJ::Draw()
//{
//	glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
//	glEnableClientState(GL_NORMAL_ARRAY);						// Enable normal arrays
//	glVertexPointer(3, GL_FLOAT, 0, Faces_Triangles);				// Vertex Pointer to triangle array
//	glNormalPointer(GL_FLOAT, 0, normals);						// Normal pointer to normal array
//	glDrawArrays(GL_TRIANGLES, 0, TotalConnectedTriangles);		// Draw the triangles
//	glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
//	glDisableClientState(GL_NORMAL_ARRAY);						// Disable normal arrays
//}
//
//// opengl callback
//void on_opengl2(void* param)
//{
//
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // background color
//										  //glGenTextures(1, &texture); // generate texture names
//										  //glBindTexture(GL_TEXTURE_2D, texture); // bind a named texture to a texturing target
//	glLoadIdentity();
//	//GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
//	//GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
//	//GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
//	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
//	//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
//	//glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
//	//glEnable(GL_LIGHT0);
//	//glEnable(GL_COLOR_MATERIAL);
//	//glShadeModel(GL_SMOOTH);
//	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//glMatrixMode(GL_MODELVIEW);
//	//glLoadIdentity();
//
//	// make a texture
//	// set texture parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	// set texture environment parameters
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//
//	// specify a two-dimensional texture image
//	// glTexiplTexture2D(<#GLenum target#>, <#GLint level#>, <#GLenum internalformat#>, <#GLsizei width#>, <#GLsizei height#>, <#GLint border#>, <#GLenum format#>, <#GLenum type#>, <#const GLvoid * pixels#>)
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, win_width, win_height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, src2.data);
//
//	// draw 2D square plane to be mapped by the texture
//	glEnable(GL_TEXTURE_2D);
//	glColor3f(1.0f, 1.0f, 1.0f); // the drawing color
//	glBegin(GL_QUADS);
//	{
//		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
//		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
//		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
//		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
//	}
//	glEnd();
//
//
//	//while (!Projection9.empty())
//	////for (size_t i = 0; i < Projection9.size(); i++)
//	////for (Projection9_Data = Projection9.begin(); Projection9_Data != Projection9.end(); Projection9_Data++)
//	//{
//	//	cnt_gl++;
//	//	//cout << i  << endl;
//	//	//cout << modelview9.back() << endl;
//	//	glMatrixMode(GL_PROJECTION);
//	//	glLoadIdentity();
//	//	//GLfloat* projection = convertMatrixType(Projection9[i]);
//	//	//GLfloat* projection = convertMatrixType(*Projection9_Data);
//	//	GLfloat* projection = convertMatrixType(Projection9.back());
//	//	Projection9.pop_back();
//	//	//cout << "projection" << endl;
//	//	//cout << projection << endl;
//	//	glLoadMatrixf(projection);
//	//	delete[] projection;
//
//	//	glMatrixMode(GL_MODELVIEW);
//	//	glLoadIdentity();
//	//	//GLfloat* modelView = convertMatrixType(modelview9[i]);
//	//	//GLfloat* modelView = convertMatrixType(*modelview9_Data);
//	//	GLfloat* modelView = convertMatrixType(modelview9.back());
//	//	//cout << "modelview-" << i << endl;
//	//	cout << "modelview9.back()" << endl;
//	//	cout << modelview9.size() << endl;
//	//	cout << modelview9.back() << endl;
//	//	modelview9.pop_back();
//	//	glLoadMatrixf(modelView);
//	//	delete[] modelView;
//
//	//	GLUquadricObj *pQuad;
//	//	pQuad = gluNewQuadric();
//	//	gluQuadricDrawStyle(pQuad, GLU_LINE);
//	//	//gluCylinder(pQuad, 3.0, 0.0, 5.0, 20, 20);//기준이 6.0 정사각형 그러므로 반지름 3.0
//	//	glRotatef(90, 1.0f, 0.0f, 0.0f);
//	//	glScalef(0.2f, 0.2f, 0.2f);
//	//	obj.Draw();
//	//	glFlush();
//	//	//glutSolidTeapot(0.4);
//	//	//gluDeleteQuadric(pQuad);
//	//}
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	GLfloat* projection = convertMatrixType(Projection0);
//	glLoadMatrixf(projection);
//	delete[] projection;
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	GLfloat* modelView = convertMatrixType(modelview0);
//	glLoadMatrixf(modelView);
//	delete[] modelView;
//
//	GLUquadricObj *pQuad;
//	pQuad = gluNewQuadric();
//	gluQuadricDrawStyle(pQuad, GLU_LINE);
//	//gluCylinder(pQuad, 3.0, 0.0, 5.0, 20, 20);//기준이 6.0 정사각형 그러므로 반지름 3.0
//	//glRotatef(90, 1.0f, 0.0f, 0.0f);
//	//glScalef(0.2f, 0.2f, 0.2f);
//	glRotatef(90, 1.0f, 0.0f, 0.0f);
//	glScalef(0.2f, 0.2f, 0.2f);
//	obj.Draw();//비행기
//
//	glLoadIdentity();
//	modelView = convertMatrixType(modelview1);
//	glLoadMatrixf(modelView);
//	delete[] modelView;
//
//	glRotatef(90, 1.0f, 1.0f, 1.0f);
//	//glScalef(0.2f, 0.2f, 0.2f);
//	//obj3.Draw();//테디
//	obj6.Draw();//하이킥
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	modelView = convertMatrixType(modelview2);
//	glLoadMatrixf(modelView);
//	delete[] modelView;
//
//	glTranslatef(-3.0f, -3.0f, 0.0f);
//	glRotatef(90, 1.0f, 0.0f, 0.0f);
//	//glScalef(2.0f, 2.0f, 2.0f);
//	obj2.Draw();//가로등
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	modelView = convertMatrixType(modelview3);
//	glLoadMatrixf(modelView);
//	delete[] modelView;
//
//	//gluCylinder(pQuad, 3.0, 3.0, 5.0, 20, 20);
//	glRotatef(90, 1.0f, 0.0f, 0.0f);
//	glScalef(10.0f, 10.0f, 10.0f);
//	obj3.Draw();//호박
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	modelView = convertMatrixType(modelview4);
//	glLoadMatrixf(modelView);
//	delete[] modelView;
//
//	//glTranslatef(0.0f, 0.0f, 3.0f);
//	//gluSphere(pQuad, 3.0, 20, 20);
//	glRotatef(90, 1.0f, 0.0f, 0.0f);
//	glScalef(10.0f, 10.0f, 10.0f);
//	obj4.Draw();//개미
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	modelView = convertMatrixType(modelview5);
//	glLoadMatrixf(modelView);
//	delete[] modelView;
//
//	//gluCylinder(pQuad, 3.0, 1.0, 5.0, 20, 20);
//	glRotatef(90, 1.0f, 0.0f, 0.0f);
//	glScalef(1.0f, 1.0f, 1.0f);
//	obj5.Draw();//티몬
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	modelView = convertMatrixType(modelview6);
//	glLoadMatrixf(modelView);
//	delete[] modelView;
//
//	//gluDisk(pQuad, 0.1, 0.3, 10, 10);
//	gluCylinder(pQuad, 3.0, 1.0, 5.0, 20, 20);
//	glRotatef(90, 0.0f, 0.0f, 0.0f);
//	glScalef(1.0f, 1.0f, 1.0f);
//	obj6.Draw();//하이킥
//	
//	glFlush();
//}
//
//int main(int argc, char* argv[])
//{
//	VideoCapture cap(0); // open the default camera
//	if (!cap.isOpened())  // check if we succeeded
//		return -1;
//	cap >> src;
//	cout << src.size() << endl;
//
//	namedWindow(winname, CV_WINDOW_OPENGL | CV_GUI_NORMAL/*| WINDOW_AUTOSIZE  | CV_WINDOW_FREERATIO | CV_GUI_NORMAL*/);
//	//glutInit(&argc, 0);
//	resizeWindow(winname, 640, 480);
//	glViewport(0, 0, 640, 480);
//	obj.Load("./models/cessna.obj");
//	obj1.Load("./models/teddy.obj");
//	obj2.Load("./models/lamp.obj");
//	obj3.Load("./models/pumpkin.obj");
//	obj4.Load("./models/ant.obj");
//	obj5.Load("./models/timon.obj");
//	obj6.Load("./models/highkick.obj");
//
//	setOpenGlDrawCallback(winname.c_str(), on_opengl2);
//
//	while (true)
//	{
//		cap >> src; // get a new frame from camera
//					//cap >> src2;
//		if (win_width == 0)
//		{
//			win_width = src.size().width;
//			win_height = src.size().height;
//		}
//		/*marker*/
//		//cap >> src; // get a new frame from camera
//		Mat fixed = src.clone();
//		//namedWindow("main", WINDOW_AUTOSIZE);// WINDOW_OPENGL
//											 //namedWindow("main", WINDOW_OPENGL);// WINDOW_OPENGL
//											 //resizeWindow("main", 640,480);
//											 //src = imread("005.jpg");
//											 //imshow("Source", src);
//											 //Convert image to gray and blur it
//											 //generate points in the reference frame
//		framePoints.push_back(Point3d(0.0, 0.0, 0.0));
//		framePoints.push_back(Point3d(6.0, 0.0, 0.0));
//		framePoints.push_back(Point3d(0.0, 6.0, 0.0));
//		framePoints.push_back(Point3d(0.0, 0.0, 6.0));
//
//		cvtColor(src, src_gray, COLOR_BGR2GRAY);
//		blur(src_gray, src_gray, Size(3, 3));
//		threshold(src_gray, threshold_output, thresh, 255, THRESH_BINARY);
//		findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//		vector<vector<Point> > contours_poly(contours.size());
//		vector<Rect> boundRect(contours.size());
//		//CvSeq *approxContours = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 1., 1);
//		vector<RotatedRect> minRect(contours.size());
//		//vector<RotatedRect> minEllipse(contours.size());
//		cnt_cv = 0;
//		Projection9.clear();
//		modelview9.clear();
//		cout << "modelview9 초기화~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
//		cout << "for문 끝~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
//		for (size_t i = 0; i < contours.size(); i++)
//		{
//			minRect[i] = minAreaRect(Mat(contours[i]));
//			if (contours[i].size() > 3)//4개부터 사각형 가능성
//			{
//				//minEllipse[i] = fitEllipse(Mat(contours[i]));
//				approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
//				//cout << contours_poly[i].size() << endl;//사각형이면 4개
//				double area = contourArea(contours[i]);
//
//				if (contours_poly[i].size() == 4 && area > 3000 && area < src.size().area() * 80 / 100)
//				{
//					int largest_distance_index = 0;
//					double largest_distance = 0;
//					Point2f	corner[4];
//					//첫번째
//					for (size_t j = 0; j < contours[i].size(); j++) // iterate through each contour.
//					{
//						double distance = sqrt(pow(contours[i][0].x - contours[i][j].x, 2) + pow(contours[i][0].y - contours[i][j].y, 2));
//						if (distance > largest_distance)
//						{
//							largest_distance = distance;
//							largest_distance_index = j;               //Store the index of largest contour
//							corner[0] = contours[i][largest_distance_index];
//						}
//					}
//					largest_distance_index = 0;
//					largest_distance = 0;
//					//2번째
//					for (size_t j = 0; j < contours[i].size(); j++) // iterate through each contour.
//					{
//						double distance = sqrt(pow(corner[0].x - contours[i][j].x, 2) + pow(corner[0].y - contours[i][j].y, 2));
//						if (distance > largest_distance)
//						{
//							largest_distance = distance;
//							largest_distance_index = j;               //Store the index of largest contour
//							corner[1] = contours[i][largest_distance_index];
//						}
//					}
//					//3번쨰
//					largest_distance_index = 0;
//					largest_distance = 0;
//					for (size_t j = 0; j < contours[i].size(); j++) // iterate through each contour.
//					{
//						double distance = sqrt(pow(corner[0].x - contours[i][j].x, 2) + pow(corner[0].y - contours[i][j].y, 2))
//							+ sqrt(pow(corner[1].x - contours[i][j].x, 2) + pow(corner[1].y - contours[i][j].y, 2));
//						if (distance > largest_distance)
//						{
//							largest_distance = distance;
//							largest_distance_index = j;               //Store the index of largest contour
//							corner[2] = contours[i][largest_distance_index];
//						}
//					}
//					// 네 번 째 꼭지점 추출
//					// (벡터 내적을 이용하여 좌표평면에서 사각형의 너비의 최대 값을 구한다.)
//					//														 thanks to 송성원
//					int x1 = corner[0].x;	int y1 = corner[0].y;
//					int x2 = corner[1].x;	int y2 = corner[1].y;
//					int x3 = corner[2].x;	int y3 = corner[2].y;
//					int nMaxDim = 0;
//
//					for (size_t j = 0; j < contours[i].size(); j++) // iterate through each contour.
//					{
//						int nDim = abs((x1 * y2 + x2 * contours[i][j].y + contours[i][j].x  * y1) - (x2 * y1 + contours[i][j].x  * y2 + x1 * contours[i][j].y))
//							+ abs((x1 * contours[i][j].y + contours[i][j].x  * y3 + x3 * y1) - (contours[i][j].x  * y1 + x3 * contours[i][j].y + x1 * y3))
//							+ abs((contours[i][j].x  * y2 + x2 * y3 + x3 * contours[i][j].y) - (x2 * contours[i][j].y + x3 * y2 + contours[i][j].x  * y3));
//
//						if (nDim > nMaxDim)
//						{
//							nMaxDim = nDim;
//							int max = j;
//							corner[3] = contours[i][max];
//						}
//					}
//
//
//					Point2f rect_points[4];
//					rect_points[0] = corner[0];
//					rect_points[1] = corner[1];
//					rect_points[2] = corner[2];
//					rect_points[3] = corner[3];
//
//					//관심영역안에 마커찾자
//					//원본에서 찾은 4점 정렬 start
//					int cornersum[4] = {};
//
//					for (int i = 0; i < 4; i++) {
//						cornersum[i] = rect_points[i].x + rect_points[i].y;
//						//printf("%d\n", cornersum[i]);
//					}
//
//					int max = cornersum[0];
//					int min = cornersum[0];
//					int imax = 0;
//					int imin = 0;
//
//					for (int i = 0; i < 4; i++) {
//						if (cornersum[i] > max) {
//							max = cornersum[i];
//							imax = i;
//						}
//						if (cornersum[i] < min) {
//							min = cornersum[i];
//							imin = i;
//						}
//					}
//					//cout << "imax-" << imax << endl;
//					//cout << "imin-" << imin << endl;
//					Point2f TopLeft = rect_points[imin];
//					Point2f BottomRight = rect_points[imax];
//
//					Point2f corner2[2];
//					int j = 0;
//					for (int i = 0; i < 4; i++) {
//						if (i != imax && i != imin) {
//							corner2[j] = rect_points[i];
//							j++;
//						}
//					}
//
//					Point2f BottomLeft = (corner2[0].x < corner2[1].x) ? corner2[0] : corner2[1];
//					Point2f TopRight = (corner2[0].x > corner2[1].x) ? corner2[0] : corner2[1];
//					//원본에서 찾은 4점 정렬 end
//					//무게중심
//					//Point2f center = 0;
//					center.x = 0;
//					center.y = 0;
//					for (size_t i = 0; i < 4; i++)
//					{
//						center.x = center.x + rect_points[i].x;
//						center.y = center.y + rect_points[i].y;
//					}
//					center.x = center.x / 4;
//					center.y = center.y / 4;
//					circle(fixed, Point(center), 2, Scalar(255, 255, 255), 1);
//					//cout << center << endl;
//					//상대좌표 무게중심-절대 좌표//절대 좌표y값에 -붙이고 //절대좌표x-무게중심x// 절대좌표y+무게중심y
//					Point2f rect_points_relative[4];
//
//					for (size_t i = 0; i < 4; i++)
//					{
//						//rect_points_relative[i].x = center.x - rect_points[i].x;
//						//rect_points_relative[i].y = center.y - rect_points[i].y;
//
//						rect_points_relative[i].x = rect_points[i].x - center.x;
//						rect_points_relative[i].y = -rect_points[i].y + center.y;
//					}
//					//아크탄젠트로 각도 구하기
//					float Degree[4];
//					for (size_t i = 0; i < 4; i++)
//					{
//						//Degree[i] = atan(rect_points_relative[i].y/rect_points_relative[i].x) * 180 / 3.1415f;
//						Degree[i] = atan2f(rect_points_relative[i].y, rect_points_relative[i].x) * 180 / 3.1415f;
//					}
//					String msg;
//					msg += "x:";
//					msg += "x:";
//
//					//putText(src, to_string(Degree[0]), Point(rect_points[0]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//					//putText(src, to_string(Degree[1]), Point(rect_points[1]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//					//putText(src, to_string(Degree[2]), Point(rect_points[2]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//					//putText(src, to_string(Degree[3]), Point(rect_points[3]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//					float temp;    //임의로 MAX값 넣을 공간
//					Point2f temppoint;
//					for (int j = 0; j < 4; j++)
//					{
//						for (int k = 0; k < 3; k++)
//						{
//							if (Degree[k] > Degree[k + 1]) //연달아있는 두수중 앞에 있는수가 크다면
//							{
//								//위치 변경
//								temp = Degree[k];
//								Degree[k] = Degree[k + 1];
//								Degree[k + 1] = temp;
//
//								temppoint = rect_points[k];
//								rect_points[k] = rect_points[k + 1];
//								rect_points[k + 1] = temppoint;
//							}//if
//						}//for(k)
//					}//for(j)
//
//					Point2f rect_points_ro[4];
//					//Point2f rect_points_ro[4] = { 0, };
//					rect_points_ro[1] = rect_points[3];	rect_points_ro[2] = rect_points[2];
//					rect_points_ro[0] = rect_points[0]; rect_points_ro[3] = rect_points[1];
//
//					Point2f warp_points[4];
//					warp_points[1] = Point2f(0.0, 0.0);	warp_points[2] = Point2f(60.0, 0.0);
//					warp_points[0] = Point2f(0.0, 60.0); warp_points[3] = Point2f(60.0, 60.0);
//					Mat transformMatrix = getPerspectiveTransform(rect_points_ro, warp_points);
//					Mat cal(60.0, 60.0, CV_8U);
//					warpPerspective(src, cal, transformMatrix, Size(60.0, 60.0));
//
//					//Mat cal(60.0, 60.0, CV_8U);
//					//Mat cal = src(roi); //영상의 관심영역 
//					////마커계산
//					cvtColor(cal, cal, COLOR_BGR2GRAY);
//					blur(cal, cal, Size(3, 3));
//					threshold(cal, cal, thresh, 255, THRESH_BINARY);
//
//					int code_matrix[6][6]{ 0, };
//
//					for (size_t i = 0; i < 60; i++)
//					{
//						for (size_t j = 0; j < 60; j++)
//						{
//							code_matrix[i / 10][j / 10] = code_matrix[i / 10][j / 10] + (int)cal.at<uchar>(i, j);//Image.at<uchar>(y,x );
//																												 //cout << img_color.channels() << endl;
//																												 //cout << img_binary.ptr<bool>(100, 100)[0] << endl;
//																												 //cout << img_binary.ptr<bool>(85, 103)[0] << endl;// img.at<uchar>(j,i) = 255; //white
//																												 //cout << (int)img_gray.ptr<uchar>(100, 100)[0] << endl;
//																												 //cout << (int)img_gray.ptr<uchar>(85, 103)[0] << endl;// img.at<uchar>(j,i) = 255; //white
//																												 //cout << "픽셀~~~~" << to_string(i) << "-" << to_string(j) << "-" << cal.at<uchar>(i, j) << endl;
//																												 //code_matrix[i / 10][j / 10] += 1;
//						}
//					}
//
//					for (size_t i = 0; i < 6; i++)
//					{
//						for (size_t j = 0; j < 6; j++)
//						{
//							if (code_matrix[i][j] < 12500)
//							{
//								code_matrix[i][j] = 0; //black
//							}
//							else
//							{
//								code_matrix[i][j] = 1; //white
//							}
//						}
//					}
//
//					// 20칸 테두리가 모두 제대로 있는지 검사한다.
//					int sum = 0;//완벽하게 전부 검정이면 0 전부백=20
//					for (int i = 0; i < 6; i++) {
//						sum += (int)code_matrix[0][i];
//						sum += (int)code_matrix[5][i];
//						sum += (int)code_matrix[i][0];
//						sum += (int)code_matrix[i][5];
//					}
//					//sum 이 0 이어야함
//					int sum_inside = 0;
//					//패리티체크
//					// 테두리를 제외한 내부 블럭의 수는 짝수가 되어야 한다.
//					for (int y = 1; y < 5; y++) {
//						for (int x = 1; x < 5; x++) {
//							sum_inside += (int)code_matrix[y][x];
//						}
//					}
//					//cout << "안보여마지막111~~~~" << to_string(i) << "-" << sum << endl;
//					if (sum < 15 && sum_inside % 2 == 0)
//					{
//						//회전
//						int rotate_index = GetRotation(code_matrix);
//						//cout << "rotate_index" << to_string(rotate_index) << endl;
//						if (0 <= rotate_index) {
//							// 마커 인식 성공!!!
//							//imshow(to_string(i), cal);
//							// 마커의 코드를 포함한 행렬의 회전된 각도를 보정해 준다.
//							RotateMatrix(code_matrix, rotate_index);
//							RotateCorner(rect_points_ro, rotate_index);
//							int markersID = CalcMarkerID(code_matrix);
//							cout << "마커 인식 성공!!! markersID=" << to_string(markersID) << endl;
//							//string temp = to_string(i);
//							//temp.append("-"); temp.append(to_string((int)(rect_points[1].x))); temp.append(","); temp.append(to_string((int)(rect_points[1].y)));
//
//							//3D
//
//							imagePoints2.clear();
//							imagePoints2.push_back(rect_points_ro[1]);
//							imagePoints2.push_back(rect_points_ro[2]);
//							imagePoints2.push_back(rect_points_ro[3]);
//							imagePoints2.push_back(rect_points_ro[0]);
//
//							boardPoints2.clear();
//							boardPoints2.push_back(Point3f(0, 0, 0));
//							boardPoints2.push_back(Point3f(0, 6, 0));
//							boardPoints2.push_back(Point3f(6, 6, 0));
//							boardPoints2.push_back(Point3f(6, 0, 0));
//							// camera parameters
//							//double m[] = { fx, 0, cx, 0, fy, cy, 0, 0, 1 };
//							double m[] = { 559.760589, 0, 313.344287, 0, 559.343824, 244.708674, 0, 0, 1 };	// intrinsic parameters
//																											//double m[] = { 601.615485, 0, 325.944619, 0, 558.644903, 161.323432, 0, 0, 1 };	// intrinsic parameters
//							Mat A(3, 3, CV_64FC1, m);	// camera matrix
//							double d[] = { 0, 0, 0, 0 };
//							//double d[] = { 0.090651, -0.134026,  -0.011979, 0.005471 };	// k1,k2: radial distortion, p1,p2: tangential distortion
//							Mat distCoeffs(4, 1, CV_64FC1, d);
//							//solvePnP(Mat(boardPoints), Mat(imagePoints), A, distCoeffs, rvec, tvec, false);
//							solvePnP(Mat(boardPoints2), Mat(imagePoints2), A, distCoeffs, rvec, tvec, false);
//
//							projectPoints(framePoints, rvec, tvec, A, distCoeffs, imageFramePoints);
//
//							line(fixed, imageFramePoints[0], imageFramePoints[1], CV_RGB(255, 0, 0), 2);
//							line(fixed, imageFramePoints[0], imageFramePoints[2], CV_RGB(0, 255, 0), 2);
//							line(fixed, imageFramePoints[0], imageFramePoints[3], CV_RGB(0, 0, 255), 2);
//							putText(fixed, to_string(markersID), Point(rect_points_ro[1]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//
//							//사각형테두리 그리기
//							for (int j = 0; j < 4; j++)
//							{
//								line(fixed, rect_points_ro[j], rect_points_ro[(j + 1) % 4], Scalar(0, 255, 0), 1, 8);
//								circle(fixed, Point(rect_points_ro[j]), 2, Scalar(255, 0, 0), 1);
//								//putText(src, to_string(j), Point(rect_points_ro[j]), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
//							}
//
//							cv::Mat rotation;
//							cv::Rodrigues(rvec, rotation);
//							double offsetA[3][1] = { 3,3,0 };//기준이 6.0짜리 마커니까 반으로 밀으면 가운데옴
//							Mat offset(3, 1, CV_64FC1, offsetA);
//							tvec = tvec + rotation*offset;//제거하면 모서리에 찍힘
//							Projection = Scalar(0);
//							modelview = Scalar(0);
//							generateProjectionModelview(A, rotation, tvec, Projection, modelview);
//							//generateProjectionModelview(A, rotation, tvec, Projection9[cnt_cv], modelview9[cnt_cv]);
//							cout<< "cnt_cv~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~:" << cnt_cv << endl;
//							cout<< "modelview9.size()~~~~~~~~~~~~~~~~~~~~~~~~~~~:" << modelview9.size() << endl;
//							//cout << Projection << endl;
//							cout << modelview << endl;
//							Projection9.push_back(Projection);
//							modelview9.push_back(modelview);
//							cout << modelview9.back() << endl;
//							//cnt_cv++;
//							//cout << "modelview9[i]modelview9[i]modelview9[i]modelview9[i]modelview9[i]" << endl;
//							//for (size_t i = 0; i < modelview9.size(); i++)
//							//{
//							//	cout << modelview9[i] << endl;
//							//}
//							switch (cnt_cv)
//							{
//							case 0:
//								generateProjectionModelview(A, rotation, tvec, Projection0, modelview0);
//								break;
//							case 1:
//								generateProjectionModelview(A, rotation, tvec, Projection1, modelview1);
//								break;
//							case 2:
//								generateProjectionModelview(A, rotation, tvec, Projection2, modelview2);
//								break;
//							case 3:
//								generateProjectionModelview(A, rotation, tvec, Projection3, modelview3);
//								break;
//							case 4:
//								generateProjectionModelview(A, rotation, tvec, Projection4, modelview4);
//								break;
//							case 5:
//								generateProjectionModelview(A, rotation, tvec, Projection5, modelview5);
//								break;
//							case 6:
//								generateProjectionModelview(A, rotation, tvec, Projection6, modelview6);
//								break;
//							}
//							cnt_cv++;
//
//							//if (cnt_cv == 0)
//							//{
//							//	generateProjectionModelview(A, rotation, tvec, Projection0, modelview0);
//							//	//Projection0 = Projection;
//							//	//modelview0 = modelview;
//							//}
//							//if (cnt_cv == 1)
//							//{
//							//	generateProjectionModelview(A, rotation, tvec, Projection1, modelview1);
//							//}
//							//if (cnt_cv == 2)
//							//{
//							//	generateProjectionModelview(A, rotation, tvec, Projection2, modelview2);
//							//}
//							//if (cnt_cv == 3)
//							//{
//							//	generateProjectionModelview(A, rotation, tvec, Projection3, modelview3);
//							//}
//							//if (cnt_cv == 4)
//							//{
//							//	generateProjectionModelview(A, rotation, tvec, Projection4, modelview4);
//							//}
//							//if (cnt_cv == 5)
//							//{
//							//	generateProjectionModelview(A, rotation, tvec, Projection5, modelview5);
//							//}
//							//if (cnt_cv == 6)
//							//{
//							//	generateProjectionModelview(A, rotation, tvec, Projection6, modelview6);
//							//}
//							//cnt_cv++;
//						}
//					}
//				}
//			}
//			//imshow("main", src);
//		}
//		//waitKey(0);
//		//imshow("main", src);
//		imshow("fixed", fixed);
//
//		//if (waitKey(30) >= 0) break;
//		/*marker*/
//		flip(src, src2, 0);// vertical flip 나중에 연산후에 사용
//		char key = (char)waitKey(10);
//
//		//imshow(winname, NULL);
//		updateWindow(winname);
//	}
//
//	return 0;
//}
//
//int GetRotation(int code_matrix[6][6])
//{
//	if (!code_matrix[1][1] && code_matrix[1][4] && code_matrix[4][4] && code_matrix[4][1]) return 0;	// 정상
//	else if (code_matrix[1][1] && !code_matrix[1][4] && code_matrix[4][4] && code_matrix[4][1]) return 1;	// 시계방향으로 90도 회전됨
//	else if (code_matrix[1][1] && code_matrix[1][4] && !code_matrix[4][4] && code_matrix[4][1]) return 2; // 시계방향으로 180도 회전됨
//	else if (code_matrix[1][1] && code_matrix[1][4] && code_matrix[4][4] && !code_matrix[4][1]) return 3; // 시계방향으로 270도 회전됨
//	else return -1; // 있을수 없는 조합이다. 실패
//}
//
//void RotateMatrix(int code_matrix[6][6], int angle_idx)
//{
//	if (angle_idx == 0) return;
//
//	int cb[6][6];
//
//	for (int y = 0; y < 6; y++) {
//		for (int x = 0; x < 6; x++) {
//			switch (angle_idx) {
//			case 1: cb[y][x] = code_matrix[x][5 - y];		break; // 반시계 방향으로 90도 회전
//			case 2: cb[y][x] = code_matrix[5 - y][5 - x];	break; // 반시계 방향으로 180도 회전
//			case 3: cb[y][x] = code_matrix[5 - x][y];		break; // 반시계 방향으로 270도 회전
//			}
//		}
//	}
//	memcpy(code_matrix, cb, sizeof(double) * 6 * 6);
//}
//
//inline void swap(Point2f &c1, Point2f &c2)
//{
//	Point2f temp = c1;
//	c1 = c2;
//	c2 = temp;
//}
//
//void RotateCorner(Point2f corner[4], int angle_idx)
//{
//	Point2f c[4];
//
//	switch (angle_idx) {
//	case 0:
//		c[0] = corner[0];
//		c[1] = corner[1];
//		c[2] = corner[2];
//		c[3] = corner[3];
//		break; // 그대로
//	case 1:
//		c[0] = corner[1];
//		c[1] = corner[2];
//		c[2] = corner[3];
//		c[3] = corner[0];
//		break; // 반시계 방향으로 90도 회전
//	case 2:
//		c[0] = corner[2];
//		c[1] = corner[3];
//		c[2] = corner[0];
//		c[3] = corner[1];
//		break; // 반시계 방향으로 180도 회전
//	case 3:
//		c[0] = corner[3];
//		c[1] = corner[0];
//		c[2] = corner[1];
//		c[3] = corner[2];
//		break; // 반시계 방향으로 270도 회전
//	}
//	//if (dir) {
//	//	for (int i = 0; i<4; ++i) {
//	//		c[i] = corner[(i + 3 + angle_idx) % 4];
//	//	}
//	//	swap(c[1], c[3]);
//	//}
//	//else {
//	//	for (int i = 0; i<4; ++i) {
//	//		c[i] = corner[(i + 4 - angle_idx) % 4];
//	//	}
//	//}
//	memcpy(corner, c, sizeof(Point2f) * 4);
//}
//
//int CalcMarkerID(int code_matrix[6][6])
//{
//	int id = 0;
//	if (!code_matrix[4][2]) id += 1;
//	if (!code_matrix[3][4]) id += 2;
//	if (!code_matrix[3][3]) id += 4;
//	if (!code_matrix[3][2]) id += 8;
//	if (!code_matrix[3][1]) id += 16;
//	if (!code_matrix[2][4]) id += 32;
//	if (!code_matrix[2][3]) id += 64;
//	if (!code_matrix[2][2]) id += 128;
//	if (!code_matrix[2][1]) id += 256;
//	if (!code_matrix[1][3]) id += 512;
//	if (!code_matrix[1][2]) id += 1024;
//
//	return id;
//}
//
//void generateProjectionModelview(const cv::Mat& calibration, const cv::Mat& rotation, const cv::Mat& translation, cv::Mat& projection, cv::Mat& modelview)
//{
//	typedef double precision;
//
//	projection.at<precision>(0, 0) = 2 * calibration.at<precision>(0, 0) / width;
//	projection.at<precision>(1, 0) = 0;
//	projection.at<precision>(2, 0) = 0;
//	projection.at<precision>(3, 0) = 0;
//
//	projection.at<precision>(0, 1) = 0;
//	projection.at<precision>(1, 1) = 2 * calibration.at<precision>(1, 1) / height;
//	projection.at<precision>(2, 1) = 0;
//	projection.at<precision>(3, 1) = 0;
//
//	projection.at<precision>(0, 2) = 1 - 2 * calibration.at<precision>(0, 2) / width;
//	projection.at<precision>(1, 2) = -1 + (2 * calibration.at<precision>(1, 2) + 2) / height;
//	projection.at<precision>(2, 2) = (zNear + zFar) / (zNear - zFar);
//	projection.at<precision>(3, 2) = -1;
//
//	projection.at<precision>(0, 3) = 0;
//	projection.at<precision>(1, 3) = 0;
//	projection.at<precision>(2, 3) = 2 * zNear*zFar / (zNear - zFar);
//	projection.at<precision>(3, 3) = 0;
//
//
//	modelview.at<precision>(0, 0) = rotation.at<precision>(0, 0);
//	modelview.at<precision>(1, 0) = rotation.at<precision>(1, 0);
//	modelview.at<precision>(2, 0) = rotation.at<precision>(2, 0);
//	modelview.at<precision>(3, 0) = 0;
//
//	modelview.at<precision>(0, 1) = rotation.at<precision>(0, 1);
//	modelview.at<precision>(1, 1) = rotation.at<precision>(1, 1);
//	modelview.at<precision>(2, 1) = rotation.at<precision>(2, 1);
//	modelview.at<precision>(3, 1) = 0;
//
//	modelview.at<precision>(0, 2) = rotation.at<precision>(0, 2);
//	modelview.at<precision>(1, 2) = rotation.at<precision>(1, 2);
//	modelview.at<precision>(2, 2) = rotation.at<precision>(2, 2);
//	modelview.at<precision>(3, 2) = 0;
//
//	modelview.at<precision>(0, 3) = translation.at<precision>(0, 0);
//	modelview.at<precision>(1, 3) = translation.at<precision>(1, 0);
//	modelview.at<precision>(2, 3) = translation.at<precision>(2, 0);
//	modelview.at<precision>(3, 3) = 1;
//
//	// This matrix corresponds to the change of coordinate systems.
//	static double changeCoordArray[4][4] = { { 1, 0, 0, 0 },{ 0, -1, 0, 0 },{ 0, 0, -1, 0 },{ 0, 0, 0, 1 } };
//	static Mat changeCoord(4, 4, CV_64FC1, changeCoordArray);
//
//	modelview = changeCoord*modelview;
//}
//
//GLfloat* convertMatrixType(const cv::Mat& m)
//{
//	typedef double precision;
//
//	Size s = m.size();
//	GLfloat* mGL = new GLfloat[s.width*s.height];
//
//	for (int ix = 0; ix < s.width; ix++)
//	{
//		for (int iy = 0; iy < s.height; iy++)
//		{
//			mGL[ix*s.height + iy] = m.at<precision>(iy, ix);
//		}
//	}
//
//	return mGL;
//}