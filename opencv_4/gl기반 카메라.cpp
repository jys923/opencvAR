///* 
//*
//*	Simple example of combining OpenCvs camera interface and OpenGL
//*
//*
//*	@author Gordon Wetzstein, now @ The University of British Columbia [wetzste1@cs.ubc.ca]
//*	@date 10/15/06
//*
//*/
//#include <windows.h>
//#include <stdio.h>
//#include <gl/gl.h>
//#include <gl/glu.h>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include "opencv2/opencv.hpp"
///*
//*
//*	Simple example of combining OpenCvs camera interface and OpenGL
//*
//*
//*	@author Gordon Wetzstein, now @ The University of British Columbia [wetzste1@cs.ubc.ca]
//*	@date 10/15/06
//*
//*/
//using namespace std;
//using namespace cv;
//
////-----------------------------------------------------------------------------
//// GLUT callbacks and functions
//
//void initGlut(int argc, char **argv);
//void displayFunc(void);
//void idleFunc(void);
//void reshapeFunc(int width, int height);
//void mouseFunc(int button, int state, int x, int y);
//void mouseMotionFunc(int x, int y);
//void keyboardFunc(unsigned char key, int x, int y);
//void specialFunc(int key, int x, int y);
////-----------------------------------------------------------------------------
//
//// other [OpenGL] functions
//void countFrames(void);
//void renderBitmapString(float x, float y, float z, void *font, char *string);
//
////-----------------------------------------------------------------------------
//
//bool bFullsreen = false;
//int nWindowID;
//
////-----------------------------------------------------------------------------
//
//// parameters for the framecounter
//char pixelstring[30];
//int cframe = 0;
//int time = 0;
//int timebase = 0;
//
////-----------------------------------------------------------------------------
//
//// OpenCV variables
//
//CvCapture *cvCapture = 0;
//
//GLuint cameraImageTextureID;
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
//
//int GetRotation(int code_matrix[6][6]);
//inline void swap(Point2f &c1, Point2f &c2);
//void RotateMatrix(int code_matrix[6][6], int angle_idx);
//void RotateCorner(Point2f corner[4], int angle_idx);
//int CalcMarkerID(int code_matrix[6][6]);
//
////-----------------------------------------------------------------------------
//
//bool bInit = false;
//
////-----------------------------------------------------------------------------
//
//void displayFunc(void) {
//
//	if (!bInit) {
//
//		// initialize 1st camera on the bus
//		cvCapture = cvCreateCameraCapture(-1);
//
//		// initialze OpenGL texture		
//		glEnable(GL_TEXTURE_RECTANGLE_ARB);
//
//		glGenTextures(1, &cameraImageTextureID);
//		glBindTexture(GL_TEXTURE_RECTANGLE_ARB, cameraImageTextureID);
//
//		glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//
//		bInit = true;
//	}
//
//	IplImage* newImage = cvQueryFrame(cvCapture);
//
//	if ((newImage->width > 0) && (newImage->height > 0)) {
//
//		// clear the buffers
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glDisable(GL_DEPTH_TEST);
//		glDisable(GL_LIGHTING);
//		glEnable(GL_TEXTURE_RECTANGLE_ARB);
//
//		glMatrixMode(GL_PROJECTION);
//		glLoadIdentity();
//		gluOrtho2D(0.0, (GLdouble)newImage->width, 0.0, (GLdouble)newImage->height);
//
//		glMatrixMode(GL_MODELVIEW);
//		glLoadIdentity();
//
//		glBindTexture(GL_TEXTURE_RECTANGLE_ARB, cameraImageTextureID);
//
//		if (newImage->nChannels == 3)
//			glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB, newImage->width, newImage->height, 0, GL_BGR, GL_UNSIGNED_BYTE, newImage->imageData);
//		else if (newImage->nChannels == 4)
//			glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, newImage->width, newImage->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, newImage->imageData);
//
//		glBegin(GL_QUADS);
//		glTexCoord2i(0, 0);
//		glVertex2i(0, 0);
//		glTexCoord2i(newImage->width, 0);
//		glVertex2i(newImage->width, 0);
//		glTexCoord2i(newImage->width, newImage->height);
//		glVertex2i(newImage->width, newImage->height);
//		glTexCoord2i(0, newImage->height);
//		glVertex2i(0, newImage->height);
//		glEnd();
//		
//		src = cvarrToMat(newImage);
//		//cap >> src; // get a new frame from camera
//					//cap >> src2;
//		if (win_width == 0)
//		{
//			win_width = src.size().width;
//			win_height = src.size().height;
//		}
//		/*marker*/
//		//cap >> src; // get a new frame from camera
//		Mat fixed = src.clone();
//		namedWindow("main", WINDOW_AUTOSIZE);// WINDOW_OPENGL
//											 //namedWindow("main", WINDOW_OPENGL);// WINDOW_OPENGL
//											 //resizeWindow("main", 640,480);
//											 //src = imread("005.jpg");
//											 //imshow("Source", src);
//											 //Convert image to gray and blur it
//											 //generate points in the reference frame
//		framePoints.push_back(Point3d(0.0, 0.0, 0.0));
//		framePoints.push_back(Point3d(5.0, 0.0, 0.0));
//		framePoints.push_back(Point3d(0.0, 5.0, 0.0));
//		framePoints.push_back(Point3d(0.0, 0.0, 5.0));
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
//		for (size_t i = 0; i < contours.size(); i++)
//		{
//			minRect[i] = minAreaRect(Mat(contours[i]));
//			if (contours[i].size() > 3)//4개부터 사각형 가능성
//			{
//				//minEllipse[i] = fitEllipse(Mat(contours[i]));
//				approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
//				//cout << contours_poly[i].size() << endl;//사각형이면 4개
//				double area = contourArea(contours[i]);
//				//cout << area << endl;//사각형이면 4개
//				//src.size().area()-면적 1391776
//				//double srcSize = src.size().area();
//				//
//				//cout << srcSize << endl;
//				//작은사각형 2000~3000
//				if (contours_poly[i].size() == 4 && area > 3000 && area < src.size().area() * 80 / 100)
//				{
//					//boundRect[i] = boundingRect(Mat(contours_poly[i]));
//					//rectangle(src, boundRect[i], Scalar(0, 255, 0), 1, 8, 0);//삼각형 화면 전체 잡음 ㅡ..ㅡ
//					//Rect roi(boundRect[i].x, boundRect[i].y, boundRect[i].width, boundRect[i].height); //관심영역 
//					//Mat img_roi = src(roi); //영상의 관심영역 
//					//cvtColor(img_roi, img_roi, COLOR_BGR2GRAY);
//					//threshold(img_roi, img_roi, thresh, 255, THRESH_BINARY);
//					//vector<Point2f>  preciseCorners;
//					//cornerSubPix(img_roi, preciseCorners, Size(5, 5), Size(-1, -1), TermCriteria(CV_TERMCRIT_ITER, 30, 0.1));
//					//cout << "preciseCorners.size()" << preciseCorners.size() << endl;
//					//draw
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
//					//minRect[i] = minAreaRect(Mat(contours_poly[i]));
//					//Point2f rect_points[4];
//					//minRect[i].points(rect_points);
//					//circle(img_roi, Point((int)boundRect[i].x, (int)boundRect[i].y), 5, Scalar(255, 0, 0), 1);
//					Point2f rect_points[4];
//					rect_points[0] = corner[0];
//					rect_points[1] = corner[1];
//					rect_points[2] = corner[2];
//					rect_points[3] = corner[3];
//
//					//line(src, rect_points[0], rect_points[(1)], Scalar(255, 255, 0), 3, 8);// 1 2
//					//line(src, rect_points[2], rect_points[(3)], Scalar(255, 255, 0), 3, 8);// 0 3
//					//Mat srcCopy = src.clone();
//					//fillConvexPoly(srcCopy, rect_points, 4, Scalar(0, 0, 200));
//					//fillConvexPoly(srcCopy, rect_points, 4, cv::Scalar(0, 0, 200));
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
//					//rect_points_ro[1] = TopLeft;	rect_points_ro[2] = TopRight;
//					//rect_points_ro[0] = BottomLeft; rect_points_ro[3] = BottomRight;
//					//cout << "rect_points" << endl;
//					//cout << rect_points[2] <<","<< rect_points[3] << endl;
//					//cout << rect_points[1] << "," << rect_points[0] << endl;
//					//cout << "rect_points_ro" << endl;
//					//cout << rect_points_ro[1] << "," << rect_points_ro[2] << endl;
//					//cout << rect_points_ro[0] << "," << rect_points_ro[3] << endl;
//					//cout << "temp" << endl;
//					//cout << TopLeft << "," << TopRight << endl;
//					//cout << BottomLeft << "," << BottomRight << endl;
//					//cout << "cornersum" << endl;
//					//cout << cornersum[2] << "," << cornersum[3] << endl;
//					//cout << cornersum[1] << "," << cornersum[0] << endl;
//					//잘되는지 확인 출력
//					//string temp = to_string(i);
//					//temp.append("-"); temp.append(to_string((int)(rect_points[1].x))); temp.append(","); temp.append(to_string((int)(rect_points[1].y)));
//					//putText(src, temp, Point(rect_points[1]), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
//
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
//					//imshow(to_string(i), cal);
//					//cout << "픽셀백~~~~" << (int)threshold_output.at<bool>(370, 200) << endl;
//					//cout << "픽셀흑~~~~" << (int)threshold_output.at<bool>(400, 150) << endl;
//					//cout << "픽셀~~~~" << cal.at<uchar>(308, 320) << endl;
//					//cout << "픽셀~~~~" << cal.at<uchar>(308, 319) << endl;
//					//cout << "크기~~~~" << cal.size().height << "-" << cal.size().width << endl;
//					int code_matrix[6][6]{ 0, };
//					/*cout << "안보여0~~~~" << to_string(i) << "-" << code_matrix[0][0] << endl;
//					cout << "안보여0~~~~" << to_string(i) << "-" << code_matrix[2][2] << endl;
//					cout << "안보여0~~~~" << to_string(i) << "-" << code_matrix[1][1] << endl;
//					cout << "안보여0~~~~" << to_string(i) << "-" << code_matrix[4][4] << endl;
//					cout << "안보여숫자" << to_string(2 / 10) << "-" << to_string(11 / 10) << endl;
//					cout << "안보여숫자" << (int)cal.at<bool>(20, 30) << "-" << (int)cal.at<bool>(30, 20) << endl;*/
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
//					//cout << "안보여마지막1~~~~" << to_string(i) << endl;
//					//cout << "안보여마지막~~~~" << to_string(i) << "-" << "code_matrix[0][0]-" << code_matrix[0][0] << endl;
//					//for (size_t i = 0; i < 6; i++)
//					//{
//					//	for (size_t j = 0; j < 6; j++)
//					//	{
//					//		cout << code_matrix[i][j] << "," << ends;
//					//	}
//					//	cout << "" << endl;
//					//}
//					//cout << "" << endl;
//					// cal로 마커계산 숫자 추출
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
//					//cout << "안보여마지막2~~~~" << to_string(i) << endl;
//					//cout << "안보여마지막~~~~" << to_string(i) << "-" << "code_matrix[0][0]-" << code_matrix[0][0] << endl;
//					//for (size_t i = 0; i < 6; i++)
//					//{
//					//	for (size_t j = 0; j < 6; j++)
//					//	{
//					//		cout << code_matrix[i][j] << "," << ends;
//					//	}
//					//	cout << "" << endl;
//					//}
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
//							//3d 시작
//							// matching pairs
//							//vector<Point3f> objectPoints;	// 3d world coordinates
//							//objectPoints.push_back(Point3f(0, 0, 0));
//							//objectPoints.push_back(Point3f(0, 60, 0));
//							//objectPoints.push_back(Point3f(60, 0, 0));
//							//objectPoints.push_back(Point3f(60, 60, 0));
//							//vector<Point2f> imagePoints;	// 2d image coordinates
//							////imagePoints.push_back(imagePoint);
//							//imagePoints.push_back(rect_points_ro[0]);
//							//imagePoints.push_back(rect_points_ro[1]);
//							//imagePoints.push_back(rect_points_ro[3]);
//							//imagePoints.push_back(rect_points_ro[2]);
//							// camera parameters
//							//double m[] = { fx, 0, cx, 0, fy, cy, 0, 0, 1 };	// intrinsic parameters
//
//							//double m[] = { 2826.87 , 0 , 1609.90,
//							//	0 , 2874.70,  951.23,
//							//	0 , 0,  1
//							//};	// intrinsic parameters
//							//Mat A(3, 3, CV_64FC1, m);// camera matrix
//							////double d[] = { k1, k2, p1, p2 };	// k1,k2: radial distortion, p1,p2: tangential distortion
//							//double d[] = { 0.054371, 0.075021, -0.006746, -0.004372 };
//							//Mat distCoeffs(4, 1, CV_64FC1, d);// estimate camera pose
//							//Mat rvec, tvec;	// rotation & translation vectors
//							//solvePnP(objectPoints, imagePoints , A, distCoeffs, rvec, tvec);// extract rotation & translation matrix
//							//Mat R;
//							//Rodrigues(rvec, R);
//							//Mat R_inv = R.inv();
//							//Mat P = -R_inv*tvec;
//							//double* p = (double *)P.data;// camera position
//							//printf("x=%lf, y=%lf, z=%lf", p[0], p[1], p[2]);
//							//그리기
//							//projectPoints(InputArray objectPoints, InputArray rvec, InputArray tvec, InputArray cameraMatrix, InputArray distCoeffs, OutputArray imagePoints, OutputArray jacobian = noArray(), double aspectRatio = 0);
//							//projectPoints(objectPoints, rvec, tvec, A, distCoeffs, imagePoints);
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
//							//find the camera extrinsic parameters
//							//solvePnP(Mat(boardPoints), Mat(imagePoints), intrinsics, distortion, rvec, tvec, false);
//							//solvePnP(Mat(boardPoints2), Mat(imagePoints2), intrinsics, distortion, rvec, tvec);
//							//solvePnP(boardPoints2, boardPoints2, intrinsics, distortion, rvec, tvec, false);
//							//project the reference frame onto the image
//							//projectPoints(framePoints, rvec, tvec, intrinsics, distortion, imageFramePoints);
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
//							//1 2
//							//0 3
//							/*putText(fixed, to_string(Degree[0]), Point(rect_points_ro[0]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//							putText(fixed, to_string(Degree[1]), Point(rect_points_ro[1]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//							putText(fixed, to_string(Degree[2]), Point(rect_points_ro[2]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//							putText(fixed, to_string(Degree[3]), Point(rect_points_ro[3]), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//							circle(fixed, Point(center), 2, Scalar(255, 255, 255), 1);
//							putText(fixed, "cneter", Point(center), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 1);*/
//
//
//							//putText(src, to_string(0), Point(rect_points_ro[0]), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 1);
//							//putText(src, to_string(1), Point(rect_points_ro[1]), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 1);
//							//putText(src, to_string(2), Point(rect_points_ro[2]), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 1);
//							//putText(src, to_string(3), Point(rect_points_ro[0]), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 1);
//
//							// TRACE ("Marker ID = %d\n", _markers[i].ID);
//
//							//FindMarkerPos3d(&_markers[i]);
//
//							//DrawMarkerInfo(&_markers[i], dst);
//
//							// 원본 마커 코드
//							//cvNamedWindow("Marker Image Org", CV_WINDOW_AUTOSIZE);
//							//cvShowImage("Marker Image Org", img_marker);
//
//							//ShowMarkerCode(cvGetSize(img_marker), code_matrix);
//							/*
//							SolvePnP() -> to get rvec and tvec
//							rodrigues() -> rvec to RMatrix
//							transpose RMatrix -> RTMatrix
//							(-RTMatrix * tvec) -> to get TVector
//							create a 4×4 openGL identity matirx -> (I called it GLtransform)
//							GLtransform = glm::translate() -> translate by TVector
//							GLtransform = glm::rotate() -> rotate by rvec
//							GLtransform = glm::rotate() -> rotate to fix compatibility between CV and GL axis
//							Draw GLtransform
//							*/
//							//Mat R;
//							//Rodrigues(rvec, R);//rodrigues() -> rvec to RMatrix
//							//Mat R_inv = R.inv();//transpose RMatrix -> RTMatrix
//							//Mat P = -R_inv*tvec;//(-RTMatrix * tvec) -> to get TVector
//							//double* p = (double *)P.data;
//							//// camera position
//							//printf("x=%lf, y=%lf, z=%lf", p[0], p[1], p[2]);
//							double _rvec[3] = { -rvec.at<double>(0, 0), -rvec.at<double>(0, 1), rvec.at<double>(0, 2) };
//							Mat rvec2 = Mat(Size(3, 1), CV_64F, _rvec);
//							cout << "rvec" << endl;
//							cout << rvec << endl;
//							cout << "_rvec" << endl;
//							cout << _rvec << endl;
//							cout << "rvec2" << endl;
//							cout << rvec2 << endl;
//							Mat rotation(4, 4, CV_64F);
//							Mat viewMatrix = cv::Mat::zeros(4, 4, CV_64FC1);
//							cv::Rodrigues(rvec2, rotation);
//
//							for (unsigned int row = 0; row<3; ++row)
//							{
//								for (unsigned int col = 0; col<3; ++col)
//								{
//									viewMatrix.at<double>(row, col) = rotation.at<double>(row, col);
//								}
//								viewMatrix.at<double>(row, 3) = tvec.at<double>(row, 0);
//							}
//							viewMatrix.at<double>(3, 3) = 1.0f;
//
//							cv::Mat glViewMatrix = cv::Mat::zeros(4, 4, CV_64F);
//							cv::transpose(viewMatrix, glViewMatrix);
//							glViewMatrix2 = glViewMatrix.clone();
//
//							/*cout << rotation << endl;
//							cout << tvec << endl;
//							cout << viewMatrix << endl;
//							cout << glViewMatrix << endl;*/
//							//cout << << endl;
//							//Mat T(4, 4, R.type()); // T is 4x4
//							//T(cv::Range(0, 3), cv::Range(0, 3)) = R * 1; // copies R into T
//							//T(cv::Range(0, 3), cv::Range(3, 4)) = tvec * 1; // copies tvec into T
//							//cout << "T3" << endl;
//							//cout << T << endl;
//							//
//							//// fill the last row of T (NOTE: depending on your types, use float or double)
//							//double *p2 = T.ptr<double>(3);
//							//p2[0] = p2[1] = p2[2] = 0; p2[3] = 1;
//							//T2 = T.clone();
//							//cout << "T" << endl;
//							//cout << T << endl;
//							//cout << "T2" << endl;
//							//cout << T2 << endl;
//							//
//							//// T is your 4x4 matrix in the OpenCV frame
//							//Mat RotX = (Mat_<double>(3, 3) << 
//							//	1, 0, 0,
//							//	0, -1, 0,
//							//	0, 0, -1);
//
//							/*1, 0, 0,
//							0, cosf(180), -sinf(180),
//							0, sinf(180), cosf(180));*/
//							//Mat RotX =  // 4x4 matrix with a 180 deg rotation around X
//							//Mat Tgl = T * RotX; // OpenGL camera in the object frame
//
//							//Mat R;
//							//Rodrigues(rvec, R);
//							////Mat R_inv = R.inv();
//							//Mat R_inv;
//							//transpose(R, R_inv);
//							//Mat P = -R_inv*tvec;
//							//double* p = (double *)P.data;
//							//printf("transpose; x=%lf, y=%lf, z=%lf", p[0], p[1], p[2]);
//
//							//Mat R_inv2 = R.inv();
//							//Mat P2 = -R_inv2*tvec;
//							//double* p2 = (double *)P2.data;
//							//printf("inv(); x=%lf, y=%lf, z=%lf", p2[0], p2[1], p2[2]);
//
//						}
//					}
//				}
//			}
//			//imshow("main", src);
//		}
//
//	}
//	glLoadIdentity();
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glLoadMatrixd(&glViewMatrix2.at<double>(0, 0));
//	//glTranslated(tvec.at<double>(0, 0), -tvec.at<double>(0, 1), tvec.at<double>(0, 2));
//	glColor3f(1, 0, 0);                        // 정점의 색은 빨간색
//	glPointSize(10.0);                     // 점의 크기는 10
//	glBegin(GL_POINTS);                // 점만 찍어낸다.
//	glVertex2f(tvec.at<double>(0, 0), tvec.at<double>(0, 1));
//	glVertex2f(-0.5, -0.5);
//	//glVertex2f(0.5, -0.5);
//	//glVertex2f(0.0, 0.0);
//	glEnd();
//	glLoadIdentity();
//	cout << "glViewMatrix2```````````````````````" << endl;
//	cout << glViewMatrix2 << endl;
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	/*glutInit(&argc2, argv2);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	*/
//	glDisable(GL_TEXTURE_2D);
//	glColor3f(1.0f, 1.0f, 0.0f); // the drawing color "yellow"
//	glutSolidTeapot(0.4);
//	glTranslated(0.0, 0.0, 0.0);
//	glDisable(GL_TEXTURE_RECTANGLE_ARB);
//
//	countFrames();
//
//	glutSwapBuffers();
//}
//
////-----------------------------------------------------------------------------
//
//void initGlut(int argc, char **argv) {
//
//	// GLUT Window Initialization:
//	glutInit(&argc, argv);
//	glutInitWindowSize(640, 480);
//	glutInitWindowPosition(100, 100);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
//	nWindowID = glutCreateWindow("simpleGLUT - CvCamera");
//
//	// Register callbacks:
//	glutDisplayFunc(displayFunc);
//	glutReshapeFunc(reshapeFunc);
//	glutKeyboardFunc(keyboardFunc);
//	glutSpecialFunc(specialFunc);
//	glutMouseFunc(mouseFunc);
//	glutMotionFunc(mouseMotionFunc);
//	glutIdleFunc(idleFunc);
//}
//
//
//
////-----------------------------------------------------------------------------
//
//void idleFunc(void) {
//	glutPostRedisplay();
//}
//
////-----------------------------------------------------------------------------
//
//void reshapeFunc(int width, int height) {
//	glViewport(0, 0, width, height);
//}
//
////-----------------------------------------------------------------------------
//
//
//// mouse callback
//void mouseFunc(int button, int state, int x, int y) {
//
//}
//
////-----------------------------------------------------------------------------
//
//void mouseMotionFunc(int x, int y) {
//
//}
//
////-----------------------------------------------------------------------------
//
//void keyboardFunc(unsigned char key, int x, int y) {
//
//	switch (key) {
//
//		// -----------------------------------------
//
//#ifdef WIN32
//		// exit on escape
//	case '\033':
//
//		if (bInit) {
//			glDeleteTextures(1, &cameraImageTextureID);
//			cvReleaseCapture(&cvCapture);
//		}
//		exit(0);
//		break;
//#endif
//
//		// -----------------------------------------
//
//		// switch to fullscreen
//	case 'f':
//
//		bFullsreen = !bFullsreen;
//		if (bFullsreen)
//			glutFullScreen();
//		else {
//			glutSetWindow(nWindowID);
//			glutPositionWindow(100, 100);
//			glutReshapeWindow(640, 480);
//		}
//		break;
//
//		// -----------------------------------------
//	}
//}
//
////-----------------------------------------------------------------------------
//
//void specialFunc(int key, int x, int y) {
//	//printf("key pressed: %d\n", key);
//}
//
////-----------------------------------------------------------------------------
//
//void countFrames(void) {
//
//	time = glutGet(GLUT_ELAPSED_TIME);
//	cframe++;
//	if (time - timebase > 50) {
//		//sprintf(pixelstring, "fps: %4.2f", cframe*1000.0 / (time - timebase));
//		timebase = time;
//		cframe = 0;
//		// Draw status text and uni-logo:
//	}
//	glDisable(GL_LIGHTING);
//	glColor4f(1.0, 1.0, 1.0, 1.0);
//	glMatrixMode(GL_PROJECTION);
//	glPushMatrix();
//	glLoadIdentity();
//	gluOrtho2D(0, 200, 0, 200);
//	glMatrixMode(GL_MODELVIEW);
//	glPushMatrix();
//	glLoadIdentity();
//
//	// render the string
//	renderBitmapString(5, 5, 0.0, GLUT_BITMAP_HELVETICA_10, pixelstring);
//
//	glPopMatrix();
//	glMatrixMode(GL_PROJECTION);
//	glPopMatrix();
//	glMatrixMode(GL_MODELVIEW);
//}
//
////-----------------------------------------------------------------------------
//
//void renderBitmapString(float x, float y, float z, void *font, char *string) {
//	char *c;
//	glRasterPos3f(x, y, z);
//	for (c = string; *c != '\0'; c++) {
//		glutBitmapCharacter(font, *c);
//	}
//}
//
////-----------------------------------------------------------------------------
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
//void main(int argc, char **argv) {
//
//	initGlut(argc, argv);
//	glutMainLoop();
//
//}
//
//
//
