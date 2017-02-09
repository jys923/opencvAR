////레나 도는거
//#include <iostream>
//#include <windows.h>
////#include "opencv2/cvconfig.h"
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
//
//#include "opencv2/opencv.hpp"
//#include "opencv2/core/opengl.hpp"
////#include "opencv2/core/cuda.hpp"
////#include "opencv2/highgui/highgui.hpp"
//
//using namespace std;
//using namespace cv;
//using namespace cv::cuda;
//
//int win_width = 0;
//int win_height = 0;
//
//// углы поворота
//float angx = 55, angy = 45;
////float angx = 0.0, angy = 0.0;
//float angstep = 5.0;
//String winname = "opengl";
//
////opencv
////무게중심
//Point2f center = 0;
//Mat src; Mat src2; Mat src_gray; //
////Mat fixed;
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
//
//int GetRotation(int code_matrix[6][6]);
//inline void swap(Point2f &c1, Point2f &c2);
//void RotateMatrix(int code_matrix[6][6], int angle_idx);
//void RotateCorner(Point2f corner[4], int angle_idx);
//int CalcMarkerID(int code_matrix[6][6]);
//void on_opengl(void* param);
//
//// opengl callback
//void on_opengl(void* param)
//{
//	cout << "시작" << endl;
//	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // background color
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	// make a texture
//	// set texture parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	// set texture environment parameters
//	//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//
//	// specify a two-dimensional texture image
//	// glTexiplTexture2D(<#GLenum target#>, <#GLint level#>, <#GLenum internalformat#>, <#GLsizei width#>, <#GLsizei height#>, <#GLint border#>, <#GLenum format#>, <#GLenum type#>, <#const GLvoid * pixels#>)
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, win_width, win_height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, src.data);
//
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
//	glLoadIdentity();
//	cout << tvec << endl;
//	cout << rvec << endl;
//	cout << center << endl;
//	//glTranslated(tvec.at<double>(0, 0), -tvec.at<double>(0, 1), tvec.at<double>(0, 2));
//	//glTranslated((tvec.at<double>(0, 0) - (win_width / 2)) / (win_width / 2), (tvec.at<double>(0, 1) - (win_height / 2)) / (win_height / 2), 0.0);
//	//glTranslated(0.0, 0.0, 0.0);
//	//무게중심으로 출연장소 실패
//	//glTranslated((center.x - (win_width / 2))/ (win_width / 2), (center.y - (win_height / 2)) / (win_height / 2), 0.0);
//	glTranslated((center.x / 320) -1, (center.y / 240) -1, 0.0);
//
//	glRotatef(angx, 1, 0, 0);
//	glRotatef(angy, 0, 1, 0);
//	glRotatef(0, 0, 0, 1);
//
//	static const int coords[6][4][3] = {
//		{ { +1, -1, -1 },{ -1, -1, -1 },{ -1, +1, -1 },{ +1, +1, -1 } },
//		{ { +1, +1, -1 },{ -1, +1, -1 },{ -1, +1, +1 },{ +1, +1, +1 } },
//		{ { +1, -1, +1 },{ +1, -1, -1 },{ +1, +1, -1 },{ +1, +1, +1 } },
//		{ { -1, -1, -1 },{ -1, -1, +1 },{ -1, +1, +1 },{ -1, +1, -1 } },
//		{ { +1, -1, +1 },{ -1, -1, +1 },{ -1, -1, -1 },{ +1, -1, -1 } },
//		{ { -1, -1, +1 },{ +1, -1, +1 },{ +1, +1, +1 },{ -1, +1, +1 } }
//	};
//
//	//for (int i = 0; i < 6; ++i) {
//	//	glColor3ub(i * 20, 100 + i * 10, i * 42);
//	//	glBegin(GL_QUADS);
//	//	for (int j = 0; j < 4; ++j) {
//	//		glVertex3d(0.2 * coords[i][j][0], 0.2 * coords[i][j][1], 0.2 * coords[i][j][2]);
//	//	}
//	//	glEnd();
//	//}
//	cout << "끝"<< endl;
//	glColor3f(1, 0, 0);                        // 정점의 색은 빨간색
//	glPointSize(10.0);                     // 점의 크기는 10
//	glBegin(GL_POINTS);                // 점만 찍어낸다.
//	glVertex2f((center.x / (640 / 2)) - 1, (center.y / (380 / 2)) - 1);
//	//glVertex2f(-0.5, -0.5);
//	//glVertex2f(0.5, -0.5);
//	glEnd();
//}
//
//int main(int argc, char* argv[])
//{
//	VideoCapture cap(0); // open the default camera
//	if (!cap.isOpened())  // check if we succeeded
//		return -1;
//	cap >> src;
//	cout << src.size() << endl;
//	//cout << src.size() << endl;
//	//cap >> src; // get a new frame from camera
//	//cout << src.data << endl;
//	namedWindow(winname, CV_WINDOW_OPENGL /*| WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO | CV_GUI_NORMAL*/);
//	setOpenGlDrawCallback(winname.c_str(), on_opengl);
//	
//		while (true)
//		{
//			cap >> src; // get a new frame from camera
//			//cap >> src2;
//			//cout << src2.size() << endl;
//			if (win_width == 0)
//			{
//				win_width = src.size().width;
//				win_height = src.size().height;
//			}
//			/*marker*/
//			
//				
//				Mat fixed = src.clone();
//				//namedWindow("main", WINDOW_AUTOSIZE);// WINDOW_OPENGL
//													 //namedWindow("main", WINDOW_OPENGL);// WINDOW_OPENGL
//													 //resizeWindow("main", 640,480);
//													 //src = imread("005.jpg");
//													 //imshow("Source", src);
//													 //Convert image to gray and blur it
//													 //generate points in the reference frame
//				framePoints.push_back(Point3d(0.0, 0.0, 0.0));
//				framePoints.push_back(Point3d(5.0, 0.0, 0.0));
//				framePoints.push_back(Point3d(0.0, 5.0, 0.0));
//				framePoints.push_back(Point3d(0.0, 0.0, 5.0));
//
//				cvtColor(src, src_gray, COLOR_BGR2GRAY);
//				blur(src_gray, src_gray, Size(3, 3));
//				threshold(src_gray, threshold_output, thresh, 255, THRESH_BINARY);
//				findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//				vector<vector<Point> > contours_poly(contours.size());
//				vector<Rect> boundRect(contours.size());
//				//CvSeq *approxContours = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 1., 1);
//				vector<RotatedRect> minRect(contours.size());
//				//vector<RotatedRect> minEllipse(contours.size());
//				for (size_t i = 0; i < contours.size(); i++)
//				{
//					minRect[i] = minAreaRect(Mat(contours[i]));
//					if (contours[i].size() > 3)//4개부터 사각형 가능성
//					{
//
//						approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
//
//						double area = contourArea(contours[i]);
//
//						if (contours_poly[i].size() == 4 && area > 3000 && area < src.size().area() * 80 / 100)
//						{
//
//							int largest_distance_index = 0;
//							double largest_distance = 0;
//							Point2f	corner[4];
//							//첫번째
//							for (size_t j = 0; j < contours[i].size(); j++) // iterate through each contour.
//							{
//								double distance = sqrt(pow(contours[i][0].x - contours[i][j].x, 2) + pow(contours[i][0].y - contours[i][j].y, 2));
//								if (distance > largest_distance)
//								{
//									largest_distance = distance;
//									largest_distance_index = j;               //Store the index of largest contour
//									corner[0] = contours[i][largest_distance_index];
//								}
//							}
//							largest_distance_index = 0;
//							largest_distance = 0;
//							//2번째
//							for (size_t j = 0; j < contours[i].size(); j++) // iterate through each contour.
//							{
//								double distance = sqrt(pow(corner[0].x - contours[i][j].x, 2) + pow(corner[0].y - contours[i][j].y, 2));
//								if (distance > largest_distance)
//								{
//									largest_distance = distance;
//									largest_distance_index = j;               //Store the index of largest contour
//									corner[1] = contours[i][largest_distance_index];
//								}
//							}
//							//3번쨰
//							largest_distance_index = 0;
//							largest_distance = 0;
//							for (size_t j = 0; j < contours[i].size(); j++) // iterate through each contour.
//							{
//								double distance = sqrt(pow(corner[0].x - contours[i][j].x, 2) + pow(corner[0].y - contours[i][j].y, 2))
//									+ sqrt(pow(corner[1].x - contours[i][j].x, 2) + pow(corner[1].y - contours[i][j].y, 2));
//								if (distance > largest_distance)
//								{
//									largest_distance = distance;
//									largest_distance_index = j;               //Store the index of largest contour
//									corner[2] = contours[i][largest_distance_index];
//								}
//							}
//							// 네 번 째 꼭지점 추출
//							// (벡터 내적을 이용하여 좌표평면에서 사각형의 너비의 최대 값을 구한다.)
//							//														 thanks to 송성원
//							int x1 = corner[0].x;	int y1 = corner[0].y;
//							int x2 = corner[1].x;	int y2 = corner[1].y;
//							int x3 = corner[2].x;	int y3 = corner[2].y;
//							int nMaxDim = 0;
//
//							for (size_t j = 0; j < contours[i].size(); j++) // iterate through each contour.
//							{
//								int nDim = abs((x1 * y2 + x2 * contours[i][j].y + contours[i][j].x  * y1) - (x2 * y1 + contours[i][j].x  * y2 + x1 * contours[i][j].y))
//									+ abs((x1 * contours[i][j].y + contours[i][j].x  * y3 + x3 * y1) - (contours[i][j].x  * y1 + x3 * contours[i][j].y + x1 * y3))
//									+ abs((contours[i][j].x  * y2 + x2 * y3 + x3 * contours[i][j].y) - (x2 * contours[i][j].y + x3 * y2 + contours[i][j].x  * y3));
//
//								if (nDim > nMaxDim)
//								{
//									nMaxDim = nDim;
//									int max = j;
//									corner[3] = contours[i][max];
//								}
//							}
//
//
//							Point2f rect_points[4];
//							rect_points[0] = corner[0];
//							rect_points[1] = corner[1];
//							rect_points[2] = corner[2];
//							rect_points[3] = corner[3];
//
//
//
//							//관심영역안에 마커찾자
//							//원본에서 찾은 4점 정렬 start
//
//							
//							for (size_t i = 0; i < 4; i++)
//							{
//								center.x = center.x + rect_points[i].x;
//								center.y = center.y + rect_points[i].y;
//							}
//							center.x = center.x / 4;
//							center.y = center.y / 4;
//
//							//상대좌표 무게중심-절대 좌표//절대 좌표y값에 -붙이고 //절대좌표x-무게중심x// 절대좌표y+무게중심y
//							Point2f rect_points_relative[4];
//
//							for (size_t i = 0; i < 4; i++)
//							{
//								//rect_points_relative[i].x = center.x - rect_points[i].x;
//								//rect_points_relative[i].y = center.y - rect_points[i].y;
//
//								rect_points_relative[i].x = rect_points[i].x - center.x;
//								rect_points_relative[i].y = -rect_points[i].y + center.y;
//							}
//							//아크탄젠트로 각도 구하기
//							float Degree[4];
//							for (size_t i = 0; i < 4; i++)
//							{
//								//Degree[i] = atan(rect_points_relative[i].y/rect_points_relative[i].x) * 180 / 3.1415f;
//								Degree[i] = atan2f(rect_points_relative[i].y, rect_points_relative[i].x) * 180 / 3.1415f;
//							}
//
//							float temp;    //임의로 MAX값 넣을 공간
//							Point2f temppoint;
//							for (int j = 0; j < 4; j++)
//							{
//								for (int k = 0; k < 3; k++)
//								{
//									if (Degree[k] > Degree[k + 1]) //연달아있는 두수중 앞에 있는수가 크다면
//									{
//										//위치 변경
//										temp = Degree[k];
//										Degree[k] = Degree[k + 1];
//										Degree[k + 1] = temp;
//
//										temppoint = rect_points[k];
//										rect_points[k] = rect_points[k + 1];
//										rect_points[k + 1] = temppoint;
//									}//if
//								}//for(k)
//							}//for(j)
//
//							Point2f rect_points_ro[4];
//							//Point2f rect_points_ro[4] = { 0, };
//							rect_points_ro[1] = rect_points[3];	rect_points_ro[2] = rect_points[2];
//							rect_points_ro[0] = rect_points[0]; rect_points_ro[3] = rect_points[1];
//
//							Point2f warp_points[4];
//							warp_points[1] = Point2f(0.0, 0.0);	warp_points[2] = Point2f(60.0, 0.0);
//							warp_points[0] = Point2f(0.0, 60.0); warp_points[3] = Point2f(60.0, 60.0);
//							Mat transformMatrix = getPerspectiveTransform(rect_points_ro, warp_points);
//							Mat cal(60.0, 60.0, CV_8U);
//							warpPerspective(src, cal, transformMatrix, Size(60.0, 60.0));
//
//							//Mat cal(60.0, 60.0, CV_8U);
//							//Mat cal = src(roi); //영상의 관심영역 
//							////마커계산
//							cvtColor(cal, cal, COLOR_BGR2GRAY);
//							blur(cal, cal, Size(3, 3));
//							threshold(cal, cal, thresh, 255, THRESH_BINARY);
//							int code_matrix[6][6]{ 0, };
//							for (size_t i = 0; i < 60; i++)
//							{
//								for (size_t j = 0; j < 60; j++)
//								{
//									code_matrix[i / 10][j / 10] = code_matrix[i / 10][j / 10] + (int)cal.at<uchar>(i, j);//Image.at<uchar>(y,x );
//								}
//							}
//							for (size_t i = 0; i < 6; i++)
//							{
//								for (size_t j = 0; j < 6; j++)
//								{
//									if (code_matrix[i][j] < 12500)
//									{
//										code_matrix[i][j] = 0; //black
//									}
//									else
//									{
//										code_matrix[i][j] = 1; //white
//									}
//								}
//							}
//
//							// 20칸 테두리가 모두 제대로 있는지 검사한다.
//							int sum = 0;//완벽하게 전부 검정이면 0 전부백=20
//							for (int i = 0; i < 6; i++) {
//								sum += (int)code_matrix[0][i];
//								sum += (int)code_matrix[5][i];
//								sum += (int)code_matrix[i][0];
//								sum += (int)code_matrix[i][5];
//							}
//							//sum 이 0 이어야함
//							int sum_inside = 0;
//							//패리티체크
//							// 테두리를 제외한 내부 블럭의 수는 짝수가 되어야 한다.
//							for (int y = 1; y < 5; y++) {
//								for (int x = 1; x < 5; x++) {
//									sum_inside += (int)code_matrix[y][x];
//								}
//							}
//							//cout << "안보여마지막111~~~~" << to_string(i) << "-" << sum << endl;
//							if (sum < 15 && sum_inside % 2 == 0)
//							{
//								//회전
//								int rotate_index = GetRotation(code_matrix);
//								//cout << "rotate_index" << to_string(rotate_index) << endl;
//								if (0 <= rotate_index) {
//									// 마커 인식 성공!!!
//									imshow(to_string(i), cal);
//									// 마커의 코드를 포함한 행렬의 회전된 각도를 보정해 준다.
//									RotateMatrix(code_matrix, rotate_index);
//									RotateCorner(rect_points_ro, rotate_index);
//									int markersID = CalcMarkerID(code_matrix);
//									cout << "마커 인식 성공!!! markersID=" << to_string(markersID) << endl;
//									//string temp = to_string(i);
//									//temp.append("-"); temp.append(to_string((int)(rect_points[1].x))); temp.append(","); temp.append(to_string((int)(rect_points[1].y)));
//
//									//3d 시작
//									// matching pairs
//									//vector<Point3f> objectPoints;	// 3d world coordinates
//									//objectPoints.push_back(Point3f(0, 0, 0));
//									//objectPoints.push_back(Point3f(0, 60, 0));
//									//objectPoints.push_back(Point3f(60, 0, 0));
//									//objectPoints.push_back(Point3f(60, 60, 0));
//									//vector<Point2f> imagePoints;	// 2d image coordinates
//									////imagePoints.push_back(imagePoint);
//									//imagePoints.push_back(rect_points_ro[0]);
//									//imagePoints.push_back(rect_points_ro[1]);
//									//imagePoints.push_back(rect_points_ro[3]);
//									//imagePoints.push_back(rect_points_ro[2]);
//									// camera parameters
//									//double m[] = { fx, 0, cx, 0, fy, cy, 0, 0, 1 };	// intrinsic parameters
//
//									//double m[] = { 2826.87 , 0 , 1609.90,
//									//	0 , 2874.70,  951.23,
//									//	0 , 0,  1
//									//};	// intrinsic parameters
//									//Mat A(3, 3, CV_64FC1, m);// camera matrix
//									////double d[] = { k1, k2, p1, p2 };	// k1,k2: radial distortion, p1,p2: tangential distortion
//									//double d[] = { 0.054371, 0.075021, -0.006746, -0.004372 };
//									//Mat distCoeffs(4, 1, CV_64FC1, d);// estimate camera pose
//									//Mat rvec, tvec;	// rotation & translation vectors
//									//solvePnP(objectPoints, imagePoints , A, distCoeffs, rvec, tvec);// extract rotation & translation matrix
//									//Mat R;
//									//Rodrigues(rvec, R);
//									//Mat R_inv = R.inv();
//									//Mat P = -R_inv*tvec;
//									//double* p = (double *)P.data;// camera position
//									//printf("x=%lf, y=%lf, z=%lf", p[0], p[1], p[2]);
//									//그리기
//									//projectPoints(InputArray objectPoints, InputArray rvec, InputArray tvec, InputArray cameraMatrix, InputArray distCoeffs, OutputArray imagePoints, OutputArray jacobian = noArray(), double aspectRatio = 0);
//									//projectPoints(objectPoints, rvec, tvec, A, distCoeffs, imagePoints);
//
//									//3D
//
//									imagePoints2.clear();
//									imagePoints2.push_back(rect_points_ro[1]);
//									imagePoints2.push_back(rect_points_ro[2]);
//									imagePoints2.push_back(rect_points_ro[3]);
//									imagePoints2.push_back(rect_points_ro[0]);
//
//									boardPoints2.clear();
//									boardPoints2.push_back(Point3f(0, 0, 0));
//									boardPoints2.push_back(Point3f(0, 6, 0));
//									boardPoints2.push_back(Point3f(6, 6, 0));
//									boardPoints2.push_back(Point3f(6, 0, 0));
//									// camera parameters
//									//double m[] = { fx, 0, cx, 0, fy, cy, 0, 0, 1 };
//									double m[] = { 559.760589, 0, 313.344287, 0, 559.343824, 244.708674, 0, 0, 1 };	// intrinsic parameters
//																													//double m[] = { 601.615485, 0, 325.944619, 0, 558.644903, 161.323432, 0, 0, 1 };	// intrinsic parameters
//									Mat A(3, 3, CV_64FC1, m);	// camera matrix
//									double d[] = { 0, 0, 0, 0 };
//									//double d[] = { 0.090651, -0.134026,  -0.011979, 0.005471 };	// k1,k2: radial distortion, p1,p2: tangential distortion
//									Mat distCoeffs(4, 1, CV_64FC1, d);
//									//solvePnP(Mat(boardPoints), Mat(imagePoints), A, distCoeffs, rvec, tvec, false);
//									solvePnP(Mat(boardPoints2), Mat(imagePoints2), A, distCoeffs, rvec, tvec, false);
//									//find the camera extrinsic parameters
//									//solvePnP(Mat(boardPoints), Mat(imagePoints), intrinsics, distortion, rvec, tvec, false);
//									//solvePnP(Mat(boardPoints2), Mat(imagePoints2), intrinsics, distortion, rvec, tvec);
//									//solvePnP(boardPoints2, boardPoints2, intrinsics, distortion, rvec, tvec, false);
//									//project the reference frame onto the image
//									//projectPoints(framePoints, rvec, tvec, intrinsics, distortion, imageFramePoints);
//									projectPoints(framePoints, rvec, tvec, A, distCoeffs, imageFramePoints);
//
//									line(fixed, imageFramePoints[0], imageFramePoints[1], CV_RGB(255, 0, 0), 2);
//									line(fixed, imageFramePoints[0], imageFramePoints[2], CV_RGB(0, 255, 0), 2);
//									line(fixed, imageFramePoints[0], imageFramePoints[3], CV_RGB(0, 0, 255), 2);
//									putText(fixed, to_string(markersID), Point(rect_points_ro[1]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//
//									//사각형테두리 그리기
//									for (int j = 0; j < 4; j++)
//									{
//										line(fixed, rect_points_ro[j], rect_points_ro[(j + 1) % 4], Scalar(0, 255, 0), 1, 8);
//										circle(fixed, Point(rect_points_ro[j]), 2, Scalar(255, 0, 0), 1);
//										//putText(src, to_string(j), Point(rect_points_ro[j]), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
//									}
//									circle(fixed, Point(center), 2, Scalar(255, 255, 255), 5);
//									//1 2
//									//0 3
//									/*putText(fixed, to_string(Degree[0]), Point(rect_points_ro[0]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//									putText(fixed, to_string(Degree[1]), Point(rect_points_ro[1]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//									putText(fixed, to_string(Degree[2]), Point(rect_points_ro[2]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//									putText(fixed, to_string(Degree[3]), Point(rect_points_ro[3]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//									circle(fixed, Point(center), 2, Scalar(255, 255, 255), 1);
//									putText(fixed, "cneter", Point(center), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 1);*/
//
//
//									//putText(src, to_string(0), Point(rect_points_ro[0]), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 1);
//									//putText(src, to_string(1), Point(rect_points_ro[1]), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 1);
//									//putText(src, to_string(2), Point(rect_points_ro[2]), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 1);
//									//putText(src, to_string(3), Point(rect_points_ro[0]), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 1);
//
//									// TRACE ("Marker ID = %d\n", _markers[i].ID);
//
//									//FindMarkerPos3d(&_markers[i]);
//
//									//DrawMarkerInfo(&_markers[i], dst);
//
//									// 원본 마커 코드
//									//cvNamedWindow("Marker Image Org", CV_WINDOW_AUTOSIZE);
//									//cvShowImage("Marker Image Org", img_marker);
//
//									//ShowMarkerCode(cvGetSize(img_marker), code_matrix);
//
//								}
//							}
//						}
//					}
//					//imshow("main", src);
//					imshow("fixed", fixed);
//				}
//				//waitKey(0);
//			
//			/*marker*/
//			flip(src2, src2, 0);// vertical flip 나중에 연산후에 사용
//			char key = (char)waitKey(10);
//
//			if (key == 27)
//				break;
//
//			// вращаем
//			switch (key)
//			{
//			case 'w':
//				angx += angstep;
//				break;
//			case 's':
//				angx -= angstep;
//				break;
//			case 'a':
//				angy += angstep;
//				break;
//			case 'd':
//				angy -= angstep;
//				break;
//			}
//			// обновить рендер
//			//imshow(winname, NULL);
//			updateWindow(winname);
//			//angy = angy + 1;
//			//angx = angx + 1;
//		}
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
////struct DrawData
////{
////	ogl::Arrays arr;
////	ogl::Texture2D tex;
////	ogl::Buffer indices;
////};
////
////void draw(void* userdata);
////
////void draw(void* userdata)
////{
////	cout << 7 << endl;
////	DrawData* data = static_cast<DrawData*>(userdata);
////
////	glRotated(0.6, 0, 1, 0);
////
////	ogl::render(data->arr, data->indices, ogl::TRIANGLES);
////}
////
////int main(int argc, char* argv[])
////{
////	string filename;
////	if (argc < 2)
////	{
////		cout << "Usage: " << argv[0] << " image" << endl;
////		filename = "lena.jpg";
////	}
////	else
////		filename = argv[1];
////
////	Mat img = imread(filename);
////	if (img.empty())
////	{
////		cerr << "Can't open image " << filename << endl;
////		return -1;
////	}
////
////	namedWindow("OpenGL", WINDOW_OPENGL|WINDOW_AUTOSIZE);
////	//resizeWindow("OpenGL", win_width, win_height);
////
////	Mat_<Vec2f> vertex(1, 4);
////	vertex << Vec2f(-1, 1), Vec2f(-1, -1), Vec2f(1, -1), Vec2f(1, 1);
////
////	Mat_<Vec2f> texCoords(1, 4);
////	texCoords << Vec2f(0, 0), Vec2f(0, 1), Vec2f(1, 1), Vec2f(1, 0);
////
////	Mat_<int> indices(1, 6);
////	indices << 0, 1, 2, 2, 3, 0;
////
////	DrawData data;
////
////	data.arr.setVertexArray(vertex);
////	data.arr.setTexCoordArray(texCoords);
////	data.indices.copyFrom(indices);
////	data.tex.copyFrom(img);
////
////	glMatrixMode(GL_PROJECTION);
////	glLoadIdentity();
////	gluPerspective(45.0, (double)win_width / win_height, 0.1, 100.0);
////
////	glMatrixMode(GL_MODELVIEW);
////	glLoadIdentity();
////	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
////
////	glEnable(GL_TEXTURE_2D);
////	data.tex.bind();
////
////	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
////
////	glDisable(GL_CULL_FACE);
////	cout << 1 << endl;
////	setOpenGlDrawCallback("OpenGL", draw, &data);
////	cout << 2 << endl;
////	for (;;)
////	{
////		cout << 3 << endl;
////		updateWindow("OpenGL");
////		cout << 4 << endl;
////		int key = waitKey(40);
////		if ((key & 0xff) == 27)
////			break;
////	}
////	cout << 5 << endl;
////	setOpenGlDrawCallback("OpenGL", 0, 0);
////	cout << 6 << endl;
////	//destroyAllWindows();
////
////	return 0;
////}
