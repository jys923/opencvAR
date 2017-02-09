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
//class ColorHistogram {
//private:
//	int histSize[3];
//	float hranges[2];
//	const float* ranges[3];
//	int channels[3];
//public:
//	ColorHistogram() {
//		// 컬러 히스토그램을 위한 인자 준비
//		histSize[0] = histSize[1] = histSize[2] = 256;
//		hranges[0] = 0.0;    // BRG 범위
//		hranges[1] = 255.0;
//		ranges[0] = hranges; // 모든 채널은 같은 범위를 가짐 
//		ranges[1] = hranges;
//		ranges[2] = hranges;
//		channels[0] = 0;  // 세 가지 채널 
//		channels[1] = 1;
//		channels[2] = 2;
//	}
//
//	// 마스크와 함께 1차원 색상 히스토그램 계산
//	// BGR 원시 영상은 HSV로 변환
//	// 낮은 채도를 갖는 화소를 무시
//	cv::MatND getHueHistogram(const cv::Mat &image, int minSaturation = 0) {
//		cv::MatND hist;
//		cv::Mat hsv; // HSV 컬러 공간 변환
//		cv::cvtColor(image, hsv, CV_BGR2HSV); // HSV 공간으로 변환
//		cv::Mat mask; // 사용하는 마스크 (또는 사용하지 않음)
//
//		if (minSaturation > 0) {
//			std::vector<cv::Mat> v; // 3채널을 3개 영상으로 분리
//			cv::split(hsv, v); // 영상 분리
//			cv::threshold(v[1], mask, minSaturation, 255, cv::THRESH_BINARY);
//			// 낮은 채도 화소를 마스크로 제외
//		}
//
//		// 1차원 색상 히스토그램 인자 준비
//		hranges[0] = 0.0;
//		hranges[1] = 180.0;
//		channels[0] = 0; // 색상 채널
//		cv::calcHist(&hsv, // 히스토그램 계산 
//			1,   // 단일 영상의 히스토그램만
//			channels, // 대상 채널               
//			cv::Mat(), // 마스크 프로그램         
//			hist,  // 결과 히스토그램         
//			1,   // 1D 히스토그램           
//			histSize, // 빈도수                  
//			ranges  // 화소값 범위             
//		);
//		return hist;
//	}
//};
//
//// 히스토그램 역투영 알고리즘에서 컬러 정보를 사용할 수 있는 방법
//// 먼저 역투영 처리 과정을 캡슐화한 클래스를 정의
//// 필요한 속성과 초기 데이터를 정의
//class ContentFinder {
//private:
//	float hranges[2];
//	const float* ranges[3];
//	int channels[3];
//	float threshold;
//	cv::MatND histogram;
//public:
//	ContentFinder() : threshold(-1.0f) {
//		ranges[0] = hranges; // 모든 채널은 동일한 범위를 가짐
//		ranges[1] = hranges;
//		ranges[2] = hranges;
//	}
//
//	// 감지 결과를 보여주기 위한 이진 맵을 생성할 때 사용하는 경계값 파라미터를 정의
//	// 파라미터를 음수 값으로 설정하면 원시 확률 맵을 반환
//	void setThreshold(float t) {
//		// 히스토그램 값인 [0,1]에서 경계값 설정
//		threshold = t;
//	}
//
//	float getThreshold() {
//		// 경계값 가져오기
//		return threshold;
//	}
//
//	// 입력 히스토그램은 반드시 정규화 되어야 함
//	void setHistogram(const cv::MatND& h) {
//		// 참조 히스토그램 설정
//		histogram = h;
//		cv::normalize(histogram, histogram, 1.0);
//	}
//
//	cv::Mat find(const cv::Mat& image) {
//		// 히스토그램에 속하는 화소 찾기
//		cv::Mat result;
//
//		hranges[0] = 0.0; // [0,255] 범위
//		hranges[1] = 255.0;
//		channels[0] = 0;  // 세 가지 채널 
//		channels[1] = 1;
//		channels[2] = 2;
//
//		cv::calcBackProject(&image, // 입력 영상
//			1,            // 이 때 한 영상만 사용
//			channels,     // 영상 채널에 속하는 히스토그램 차원인 벡터 지정            
//			histogram,   // 히스토그램 사용                                           
//			result,       // 역투영 영상 결과                                          
//			ranges,       // 각 차원에 대한 값 범위                                    
//			255.0         // 히스토그램을 1을 255로 매핑하기 위해 선택한 스케일링 인자 
//		);
//
//		if (threshold>0.0) {
//			// 이진 영상을 얻기 위한 역투영 경계값
//			cv::threshold(result, result, 255 * threshold, 255, cv::THRESH_BINARY);
//		}
//
//		return result;
//	}
//
//	// 히스토그램을 역투영하려면 영상과 범위(모든 채널은 여기서 동일한 범위를 갖는다고 가정),
//	// 사용하는 채널 목록을 간단하게 지정할 필요가 있다.
//	cv::Mat find(const cv::Mat& image, float minValue, float maxValue, int *channels, int dim) {
//
//		cv::Mat result;
//
//		hranges[0] = minValue;
//		hranges[1] = maxValue;
//
//		for (int i = 0; i<dim; i++)
//			this->channels[i] = channels[i];
//
//		cv::calcBackProject(&image, // 입력 영상
//			1,            // 이 때 한 영상만 사용
//			channels,     // 영상 채널에 속하는 히스토그램 차원인 벡터 지정            
//			histogram,   // 히스토그램 사용                                           
//			result,       // 역투영 영상 결과                                          
//			ranges,       // 각 차원에 대한 값 범위                                    
//			255.0         // 히스토그램을 1을 255로 매핑하기 위해 선택한 스케일링 인자 
//		);
//
//		if (threshold>0.0) {
//			//이진 영상을 얻기 위한 역투영 경계값
//			cv::threshold(result, result, 255 * threshold, 255, cv::THRESH_BINARY);
//		}
//		return result;
//	}
//};
//
//
//int main()
//{
//	VideoCapture cap(0);
//
//	//웹캡에서 캡처되는 이미지 크기를 320x240으로 지정  
//	cap.set(CAP_PROP_FRAME_WIDTH, 320);
//	cap.set(CAP_PROP_FRAME_HEIGHT, 240);
//
//	if (!cap.isOpened())
//	{
//		cout << "웹캠을 열 수 없습니다." << endl;
//		return -1;
//	}
//
//
//	namedWindow("찾을 색범위 설정", CV_WINDOW_AUTOSIZE);
//
//
//	//트랙바에서 사용되는 변수 초기화 
//	int LowH = 170;
//	int HighH = 179;
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
//
//	//트랙바 생성 
//	cvCreateTrackbar("LowH", "찾을 색범위 설정", &LowH, 179); //Hue (0 - 179)
//	cvCreateTrackbar("HighH", "찾을 색범위 설정", &HighH, 179);
//
//	cvCreateTrackbar("LowS", "찾을 색범위 설정", &LowS, 255); //Saturation (0 - 255)
//	cvCreateTrackbar("HighS", "찾을 색범위 설정", &HighS, 255);
//
//	cvCreateTrackbar("LowV", "찾을 색범위 설정", &LowV, 255); //Value (0 - 255)
//	cvCreateTrackbar("HighV", "찾을 색범위 설정", &HighV, 255);
//
//
//	while (true)
//	{
//
//		//웹캠에서 캡처되는 속도 출력  
//		int fps = cap.get(CAP_PROP_FPS);
//		cout << fps << endl;
//
//		Mat img_input, img_hsv, img_binary, img_input_his;
//		Mat img_red, img_orange, img_yellow, img_green, img_blue, img_indigo, img_violet ;//red orange yellow green blue indigo violet
//
//		//cap >> src;
//		//카메라로부터 이미지를 가져옴 
//		//bool ret = cap.read(img_input);
//
//		//if (!ret)
//		//{
//		//	cout << "카메라로부터 이미지를 가져올 수 없습니다." << endl;
//		//	break;
//		//}
//		cap >> img_input;
//
//		img_input_his= img_input.clone();
//		int minSat = 65;
//		ColorHistogram hc; // 색상 히스토그램 가져오기
//		cv::MatND colorhist = hc.getHueHistogram(img_input_his, minSat);
//		ContentFinder finder;
//		finder.setHistogram(colorhist);
//		// 결과 히스토그램을 입력으로 ContentFinder 클래스 인스턴스에 넣음
//		finder.setThreshold(0.2f);
//
//		// HSV 공간으로 변환
//		cv::Mat hsv;
//		cv::cvtColor(img_input_his, hsv, CV_BGR2HSV);
//
//		std::vector<cv::Mat> v; // 3채널을 3개 영상으로 분리
//		cv::split(hsv, v); // 영상 분리
//
//		cv::threshold(v[1], v[1], minSat, 255, cv::THRESH_BINARY);
//		// 낮은 채도를 갖는 화소 제거
//		cv::namedWindow("Saturation");
//		cv::imshow("Saturation", v[1]);
//
//		int ch[1] = { 0 };
//		cv::Mat result = finder.find(hsv, 0.0f, 180.0f, ch, 1);
//		// 색상 히스토그램의 역투영 가져오기
//		cv::bitwise_and(result, v[1], result);
//		// 낮은 채도 화소 제거 (일정 채도 화소 이하 제거)
//		// 색상 히스토그램의 역투영 가져오기
//		finder.setThreshold(-1.0f);
//		result = finder.find(hsv, 0.0f, 180.0f, ch, 1);
//		cv::bitwise_and(result, v[1], result);
//
//		cv::imshow("aaaaaa", result);
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
//
//		//영역박스 그리기
//		int max = -1, idx = 0;
//		for (int j = 1; j < numOfLables; j++) {
//			int area = stats.at<int>(j, CC_STAT_AREA);
//			if (max < area)
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
//
//		rectangle(img_input, Point(left, top), Point(left + width, top + height),
//			Scalar(0, 0, 255), 1);
//
//		//무지개
//		inRange(img_hsv, Scalar(LowH_red, LowS, LowV), Scalar(HighH_red, HighS, HighV), img_red);
//		//morphological opening 작은 점들을 제거 
//		erode(img_red, img_red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_red, img_red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//morphological closing 영역의 구멍 메우기
//		dilate(img_red, img_red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_red, img_red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//빨
//		numOfLables = connectedComponentsWithStats(img_red, img_labels,
//			stats, centroids, 8, CV_32S);
//
//		//영역박스 그리기
//		max = -1; idx = 0;
//		for (int j = 1; j < numOfLables; j++) {
//			int area = stats.at<int>(j, CC_STAT_AREA);
//			if (max < area)
//			{
//				max = area;
//				idx = j;
//			}
//		}
//
//		left = stats.at<int>(idx, CC_STAT_LEFT);
//		top = stats.at<int>(idx, CC_STAT_TOP);
//		width = stats.at<int>(idx, CC_STAT_WIDTH);
//		height = stats.at<int>(idx, CC_STAT_HEIGHT);
//
//		putText(img_input, "img_red", Point(left, top), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//		rectangle(img_input, Point(left, top), Point(left + width, top + height),
//			Scalar(0, 0, 255), 1);
//
//
//		inRange(img_hsv, Scalar(LowH_yellow, LowS, LowV), Scalar(HighH_yellow, HighS, HighV), img_yellow);
//		//morphological opening 작은 점들을 제거 
//		erode(img_yellow, img_yellow, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_yellow, img_yellow, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//morphological closing 영역의 구멍 메우기
//		dilate(img_yellow, img_yellow, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_yellow, img_yellow, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//빨
//		numOfLables = connectedComponentsWithStats(img_yellow, img_labels,
//			stats, centroids, 8, CV_32S);
//
//		//영역박스 그리기
//		max = -1; idx = 0;
//		for (int j = 1; j < numOfLables; j++) {
//			int area = stats.at<int>(j, CC_STAT_AREA);
//			if (max < area)
//			{
//				max = area;
//				idx = j;
//			}
//		}
//
//		left = stats.at<int>(idx, CC_STAT_LEFT);
//		top = stats.at<int>(idx, CC_STAT_TOP);
//		width = stats.at<int>(idx, CC_STAT_WIDTH);
//		height = stats.at<int>(idx, CC_STAT_HEIGHT);
//
//		putText(img_input, "img_yellow", Point(left, top), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//		rectangle(img_input, Point(left, top), Point(left + width, top + height),
//			Scalar(0, 0, 255), 1);
//
//
//
//		inRange(img_hsv, Scalar(LowH_green, LowS, LowV), Scalar(HighH_green, HighS, HighV), img_green);
//		//morphological opening 작은 점들을 제거 
//		erode(img_green, img_green, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_green, img_green, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//morphological closing 영역의 구멍 메우기
//		dilate(img_green, img_green, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_green, img_green, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//빨
//		numOfLables = connectedComponentsWithStats(img_green, img_labels,
//			stats, centroids, 8, CV_32S);
//
//		//영역박스 그리기
//		max = -1; idx = 0;
//		for (int j = 1; j < numOfLables; j++) {
//			int area = stats.at<int>(j, CC_STAT_AREA);
//			if (max < area)
//			{
//				max = area;
//				idx = j;
//			}
//		}
//
//		left = stats.at<int>(idx, CC_STAT_LEFT);
//		top = stats.at<int>(idx, CC_STAT_TOP);
//		width = stats.at<int>(idx, CC_STAT_WIDTH);
//		height = stats.at<int>(idx, CC_STAT_HEIGHT);
//
//		putText(img_input, "img_green", Point(left, top), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//		rectangle(img_input, Point(left, top), Point(left + width, top + height),
//			Scalar(0, 0, 255), 1);
//
//
//		inRange(img_hsv, Scalar(LowH_blue, LowS, LowV), Scalar(HighH_blue, HighS, HighV), img_blue);
//		//morphological opening 작은 점들을 제거 
//		erode(img_blue, img_blue, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_blue, img_blue, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//morphological closing 영역의 구멍 메우기
//		dilate(img_blue, img_blue, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_blue, img_blue, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//빨
//		numOfLables = connectedComponentsWithStats(img_blue, img_labels,
//			stats, centroids, 8, CV_32S);
//
//		//영역박스 그리기
//		max = -1; idx = 0;
//		for (int j = 1; j < numOfLables; j++) {
//			int area = stats.at<int>(j, CC_STAT_AREA);
//			if (max < area)
//			{
//				max = area;
//				idx = j;
//			}
//		}
//
//		left = stats.at<int>(idx, CC_STAT_LEFT);
//		top = stats.at<int>(idx, CC_STAT_TOP);
//		width = stats.at<int>(idx, CC_STAT_WIDTH);
//		height = stats.at<int>(idx, CC_STAT_HEIGHT);
//
//		putText(img_input, "img_blue", Point(left, top), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//		rectangle(img_input, Point(left, top), Point(left + width, top + height),
//			Scalar(0, 0, 255), 1);
//
//
//		inRange(img_hsv, Scalar(LowH_indigo, LowS, LowV), Scalar(HighH_indigo, HighS, HighV), img_indigo);
//		//morphological opening 작은 점들을 제거 
//		erode(img_indigo, img_indigo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_indigo, img_indigo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//morphological closing 영역의 구멍 메우기
//		dilate(img_indigo, img_indigo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_indigo, img_indigo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//빨
//		numOfLables = connectedComponentsWithStats(img_indigo, img_labels,
//			stats, centroids, 8, CV_32S);
//
//		//영역박스 그리기
//		max = -1; idx = 0;
//		for (int j = 1; j < numOfLables; j++) {
//			int area = stats.at<int>(j, CC_STAT_AREA);
//			if (max < area)
//			{
//				max = area;
//				idx = j;
//			}
//		}
//
//		left = stats.at<int>(idx, CC_STAT_LEFT);
//		top = stats.at<int>(idx, CC_STAT_TOP);
//		width = stats.at<int>(idx, CC_STAT_WIDTH);
//		height = stats.at<int>(idx, CC_STAT_HEIGHT);
//
//		putText(img_input, "img_indigo", Point(left, top), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//		rectangle(img_input, Point(left, top), Point(left + width, top + height),
//			Scalar(0, 0, 255), 1);
//
//
//		inRange(img_hsv, Scalar(LowH_violet, LowS, LowV), Scalar(HighH_violet, HighS, HighV), img_violet);
//		//morphological opening 작은 점들을 제거 
//		erode(img_violet, img_violet, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_violet, img_violet, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//morphological closing 영역의 구멍 메우기
//		dilate(img_violet, img_violet, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_violet, img_violet, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//빨
//		numOfLables = connectedComponentsWithStats(img_violet, img_labels,
//			stats, centroids, 8, CV_32S);
//
//		//영역박스 그리기
//		max = -1; idx = 0;
//		for (int j = 1; j < numOfLables; j++) {
//			int area = stats.at<int>(j, CC_STAT_AREA);
//			if (max < area)
//			{
//				max = area;
//				idx = j;
//			}
//		}
//
//		left = stats.at<int>(idx, CC_STAT_LEFT);
//		top = stats.at<int>(idx, CC_STAT_TOP);
//		width = stats.at<int>(idx, CC_STAT_WIDTH);
//		height = stats.at<int>(idx, CC_STAT_HEIGHT);
//		//double *centroid = centroids.at<double>(idx, 0); //중심좌표  
//		//putText(img_input, "img_violet", Point2d(centroids.at<double>(idx, 0)), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//		circle(img_input, Point(centroids.at<double>(idx, 0)), 5, Scalar(255, 0, 0), 1);
//		putText(img_input, "img_violet", Point(left, top), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//		rectangle(img_input, Point(left, top), Point(left + width, top + height),
//			Scalar(0, 0, 255), 1);
//
//		////단순히 모든 라벨링 그리기 안좋음
//		//for (int j = 1; j < numOfLables; j++) {
//		//	int area = stats.at<int>(j, CC_STAT_AREA);
//		//	int left = stats.at<int>(j, CC_STAT_LEFT);
//		//	int top = stats.at<int>(j, CC_STAT_TOP);
//		//	int width = stats.at<int>(j, CC_STAT_WIDTH);
//		//	int height = stats.at<int>(j, CC_STAT_HEIGHT);
//		//	rectangle(img_input, Point(left, top), Point(left + width, top + height),
//		//		Scalar(0, 0, 255), 1);
//		//}
//
//		//imshow("이진화 영상", img_binary);
//		imshow("원본 영상", img_input);
//		imshow("빨 영상", img_red);
//		imshow("노 영상", img_yellow);
//		imshow("초 영상", img_green);
//		imshow("파 영상", img_blue);
//		imshow("남 영상", img_indigo);
//		imshow("보 영상", img_violet);
//		//ESC키 누르면 프로그램 종료
//		if (waitKey(1) == 27)
//			break;
//	}
//	return 0;
//}
//
