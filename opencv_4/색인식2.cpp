//#include <iostream>  
//#include <opencv2/core/mat.hpp>  
//#include <opencv2/imgcodecs.hpp>  
//#include <opencv2/imgproc.hpp>  
//#include <opencv2/highgui.hpp>
//
//
//using namespace cv;
//using namespace std;
//
//
//
//int main()
//{
//	VideoCapture cap(0);
//
//	//웹캡에서 캡처되는 이미지 크기를 320x240으로 지정  
//	//cap.set(CAP_PROP_FRAME_WIDTH, 320);
//	//cap.set(CAP_PROP_FRAME_HEIGHT, 240);
//
//	if (!cap.isOpened())
//	{
//		cout << "웹캠을 열 수 없습니다." << endl;
//		return -1;
//	}
//
//	int LowH = 170;
//	int HighH = 179;
//	//red   green  indigo 3색으로
//	//red orange yellow green blue indigo violet
//	int LowH_red = 170;
//	int HighH_red = 179;
//	int LowH_yellow = 20;
//	int HighH_yellow = 29;
//	int LowH_green = 50;
//	int HighH_green = 59;
//	int LowH_blue = 80;
//	int HighH_blue = 89;
//	int LowH_indigo = 110;
//	int HighH_indigo = 119;
//	int LowH_violet = 140;
//	int HighH_violet = 149;
//
//	int LowS = 50;
//	int HighS = 255;
//
//	int LowV = 0;
//	int HighV = 255;
//
//	while (true)
//	{
//		Mat img_input, img_hsv, img_binary ,test, src_gray, addap_thr, img_hsv2, img_binary2;
//		Mat img_red, img_orange, img_yellow, img_green, img_blue, img_indigo, img_violet;//red orange yellow green blue indigo violet
//
//		cap >> img_input;
//		test = img_input.clone();
//		cvtColor(test, src_gray, CV_BGR2GRAY);   //gray로 변환  
//		adaptiveThreshold(src_gray, addap_thr, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 21, 10);
//		imshow("이진화 영상3", addap_thr);
//		//adaptiveThreshold(image, // 입력영상
//		//	binaryAdaptive, // 이진화 결과 영상
//		//	255, // 최대 화소 값 
//		//	ADAPTIVE_THRESH_MEAN_C, // Adaptive 함수
//		//	THRESH_BINARY, // 이진화 타입
//		//	blockSize,  // 이웃크기
//		//	threshold); // threshold used
//		cvtColor(addap_thr, img_hsv2, COLOR_GRAY2BGR);
//		imshow("이진화 영상4", img_hsv2);
//		cvtColor(img_hsv2, img_hsv2, COLOR_BGR2HSV);
//		inRange(img_hsv2, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), img_binary2);
//
//		//HSV로 변환
//		cvtColor(img_input, img_hsv, COLOR_BGR2HSV);
//
//		//지정한 HSV 범위를 이용하여 영상을 이진화
//		inRange(img_hsv, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), img_binary);
//
//		//morphological opening 작은 점들을 제거 
//		erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//		//morphological closing 영역의 구멍 메우기 
//		dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//		//라벨링 
//		Mat img_labels, stats, centroids;
//		int numOfLables = connectedComponentsWithStats(img_binary, img_labels,
//			stats, centroids, 8, CV_32S);
//
//		//영역박스 그리기
//		int max = -1, idx = 0;
//		for (int j = 1; j < numOfLables; j++) {
//			int area = stats.at<int>(j, CC_STAT_AREA);
//			if (max < area && area>10000)
//			{
//				max = area;
//				idx = j;
//			}
//		}
//
//		int left = stats.at<int>(idx, CC_STAT_LEFT);
//		int top = stats.at<int>(idx, CC_STAT_TOP);
//		int width = stats.at<int>(idx, CC_STAT_WIDTH);
//		int height = stats.at<int>(idx, CC_STAT_HEIGHT);
//		cout << " Point(left, top) " << Point(left + width/2, top + height/2) << endl;
//		cout << "centroids "<< centroids.at<double>(idx, 0) << endl;
//		cout << "width:" << width << "height:" << height << "left:" << left << " top:" << top << " left + width:" << left + width << " top + height:" << top + height << endl;
//		if (left != 0 || top != 0)
//		{
//			circle(img_input, Point(left + width / 2, top + height / 2), 5, Scalar(255, 0, 0), 1);
//			putText(img_input, "img_red", Point(left + width / 2, top + height / 2), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//			rectangle(img_input, Point(left, top), Point(left + width, top + height),
//				Scalar(0, 0, 255), 1);
//		}
//
//		//단순히 모든 라벨링 그리기 안좋음
//		//for (int j = 1; j < numOfLables; j++) {
//		//	int area = stats.at<int>(j, CC_STAT_AREA);
//		//	int left = stats.at<int>(j, CC_STAT_LEFT);
//		//	int top = stats.at<int>(j, CC_STAT_TOP);
//		//	int width = stats.at<int>(j, CC_STAT_WIDTH);
//		//	int height = stats.at<int>(j, CC_STAT_HEIGHT);
//		//	cout << "area-" << area << endl;
//		//	if (area>10000)
//		//	{
//		//		rectangle(img_input, Point(left, top), Point(left + width, top + height),
//		//			Scalar(0, 0, 255), 1);
//		//	}
//		//}
//		imshow("이진화 영상2", img_binary2);
//		imshow("이진화 영상", img_binary);
//		imshow("원본 영상", img_input);
//		//imshow("빨 영상", img_red);
//		//imshow("노 영상", img_yellow);
//		//imshow("초 영상", img_green);
//		//imshow("파 영상", img_blue);
//		//imshow("남 영상", img_indigo);
//		//imshow("보 영상", img_violet);
//		//ESC키 누르면 프로그램 종료
//		if (waitKey(1) == 27)
//			break;
//	}
//	return 0;
//}