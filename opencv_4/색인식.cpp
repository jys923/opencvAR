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
//		// �÷� ������׷��� ���� ���� �غ�
//		histSize[0] = histSize[1] = histSize[2] = 256;
//		hranges[0] = 0.0;    // BRG ����
//		hranges[1] = 255.0;
//		ranges[0] = hranges; // ��� ä���� ���� ������ ���� 
//		ranges[1] = hranges;
//		ranges[2] = hranges;
//		channels[0] = 0;  // �� ���� ä�� 
//		channels[1] = 1;
//		channels[2] = 2;
//	}
//
//	// ����ũ�� �Բ� 1���� ���� ������׷� ���
//	// BGR ���� ������ HSV�� ��ȯ
//	// ���� ä���� ���� ȭ�Ҹ� ����
//	cv::MatND getHueHistogram(const cv::Mat &image, int minSaturation = 0) {
//		cv::MatND hist;
//		cv::Mat hsv; // HSV �÷� ���� ��ȯ
//		cv::cvtColor(image, hsv, CV_BGR2HSV); // HSV �������� ��ȯ
//		cv::Mat mask; // ����ϴ� ����ũ (�Ǵ� ������� ����)
//
//		if (minSaturation > 0) {
//			std::vector<cv::Mat> v; // 3ä���� 3�� �������� �и�
//			cv::split(hsv, v); // ���� �и�
//			cv::threshold(v[1], mask, minSaturation, 255, cv::THRESH_BINARY);
//			// ���� ä�� ȭ�Ҹ� ����ũ�� ����
//		}
//
//		// 1���� ���� ������׷� ���� �غ�
//		hranges[0] = 0.0;
//		hranges[1] = 180.0;
//		channels[0] = 0; // ���� ä��
//		cv::calcHist(&hsv, // ������׷� ��� 
//			1,   // ���� ������ ������׷���
//			channels, // ��� ä��               
//			cv::Mat(), // ����ũ ���α׷�         
//			hist,  // ��� ������׷�         
//			1,   // 1D ������׷�           
//			histSize, // �󵵼�                  
//			ranges  // ȭ�Ұ� ����             
//		);
//		return hist;
//	}
//};
//
//// ������׷� ������ �˰��򿡼� �÷� ������ ����� �� �ִ� ���
//// ���� ������ ó�� ������ ĸ��ȭ�� Ŭ������ ����
//// �ʿ��� �Ӽ��� �ʱ� �����͸� ����
//class ContentFinder {
//private:
//	float hranges[2];
//	const float* ranges[3];
//	int channels[3];
//	float threshold;
//	cv::MatND histogram;
//public:
//	ContentFinder() : threshold(-1.0f) {
//		ranges[0] = hranges; // ��� ä���� ������ ������ ����
//		ranges[1] = hranges;
//		ranges[2] = hranges;
//	}
//
//	// ���� ����� �����ֱ� ���� ���� ���� ������ �� ����ϴ� ��谪 �Ķ���͸� ����
//	// �Ķ���͸� ���� ������ �����ϸ� ���� Ȯ�� ���� ��ȯ
//	void setThreshold(float t) {
//		// ������׷� ���� [0,1]���� ��谪 ����
//		threshold = t;
//	}
//
//	float getThreshold() {
//		// ��谪 ��������
//		return threshold;
//	}
//
//	// �Է� ������׷��� �ݵ�� ����ȭ �Ǿ�� ��
//	void setHistogram(const cv::MatND& h) {
//		// ���� ������׷� ����
//		histogram = h;
//		cv::normalize(histogram, histogram, 1.0);
//	}
//
//	cv::Mat find(const cv::Mat& image) {
//		// ������׷��� ���ϴ� ȭ�� ã��
//		cv::Mat result;
//
//		hranges[0] = 0.0; // [0,255] ����
//		hranges[1] = 255.0;
//		channels[0] = 0;  // �� ���� ä�� 
//		channels[1] = 1;
//		channels[2] = 2;
//
//		cv::calcBackProject(&image, // �Է� ����
//			1,            // �� �� �� ���� ���
//			channels,     // ���� ä�ο� ���ϴ� ������׷� ������ ���� ����            
//			histogram,   // ������׷� ���                                           
//			result,       // ������ ���� ���                                          
//			ranges,       // �� ������ ���� �� ����                                    
//			255.0         // ������׷��� 1�� 255�� �����ϱ� ���� ������ �����ϸ� ���� 
//		);
//
//		if (threshold>0.0) {
//			// ���� ������ ��� ���� ������ ��谪
//			cv::threshold(result, result, 255 * threshold, 255, cv::THRESH_BINARY);
//		}
//
//		return result;
//	}
//
//	// ������׷��� �������Ϸ��� ����� ����(��� ä���� ���⼭ ������ ������ ���´ٰ� ����),
//	// ����ϴ� ä�� ����� �����ϰ� ������ �ʿ䰡 �ִ�.
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
//		cv::calcBackProject(&image, // �Է� ����
//			1,            // �� �� �� ���� ���
//			channels,     // ���� ä�ο� ���ϴ� ������׷� ������ ���� ����            
//			histogram,   // ������׷� ���                                           
//			result,       // ������ ���� ���                                          
//			ranges,       // �� ������ ���� �� ����                                    
//			255.0         // ������׷��� 1�� 255�� �����ϱ� ���� ������ �����ϸ� ���� 
//		);
//
//		if (threshold>0.0) {
//			//���� ������ ��� ���� ������ ��谪
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
//	//��ĸ���� ĸó�Ǵ� �̹��� ũ�⸦ 320x240���� ����  
//	cap.set(CAP_PROP_FRAME_WIDTH, 320);
//	cap.set(CAP_PROP_FRAME_HEIGHT, 240);
//
//	if (!cap.isOpened())
//	{
//		cout << "��ķ�� �� �� �����ϴ�." << endl;
//		return -1;
//	}
//
//
//	namedWindow("ã�� ������ ����", CV_WINDOW_AUTOSIZE);
//
//
//	//Ʈ���ٿ��� ���Ǵ� ���� �ʱ�ȭ 
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
//	//Ʈ���� ���� 
//	cvCreateTrackbar("LowH", "ã�� ������ ����", &LowH, 179); //Hue (0 - 179)
//	cvCreateTrackbar("HighH", "ã�� ������ ����", &HighH, 179);
//
//	cvCreateTrackbar("LowS", "ã�� ������ ����", &LowS, 255); //Saturation (0 - 255)
//	cvCreateTrackbar("HighS", "ã�� ������ ����", &HighS, 255);
//
//	cvCreateTrackbar("LowV", "ã�� ������ ����", &LowV, 255); //Value (0 - 255)
//	cvCreateTrackbar("HighV", "ã�� ������ ����", &HighV, 255);
//
//
//	while (true)
//	{
//
//		//��ķ���� ĸó�Ǵ� �ӵ� ���  
//		int fps = cap.get(CAP_PROP_FPS);
//		cout << fps << endl;
//
//		Mat img_input, img_hsv, img_binary, img_input_his;
//		Mat img_red, img_orange, img_yellow, img_green, img_blue, img_indigo, img_violet ;//red orange yellow green blue indigo violet
//
//		//cap >> src;
//		//ī�޶�κ��� �̹����� ������ 
//		//bool ret = cap.read(img_input);
//
//		//if (!ret)
//		//{
//		//	cout << "ī�޶�κ��� �̹����� ������ �� �����ϴ�." << endl;
//		//	break;
//		//}
//		cap >> img_input;
//
//		img_input_his= img_input.clone();
//		int minSat = 65;
//		ColorHistogram hc; // ���� ������׷� ��������
//		cv::MatND colorhist = hc.getHueHistogram(img_input_his, minSat);
//		ContentFinder finder;
//		finder.setHistogram(colorhist);
//		// ��� ������׷��� �Է����� ContentFinder Ŭ���� �ν��Ͻ��� ����
//		finder.setThreshold(0.2f);
//
//		// HSV �������� ��ȯ
//		cv::Mat hsv;
//		cv::cvtColor(img_input_his, hsv, CV_BGR2HSV);
//
//		std::vector<cv::Mat> v; // 3ä���� 3�� �������� �и�
//		cv::split(hsv, v); // ���� �и�
//
//		cv::threshold(v[1], v[1], minSat, 255, cv::THRESH_BINARY);
//		// ���� ä���� ���� ȭ�� ����
//		cv::namedWindow("Saturation");
//		cv::imshow("Saturation", v[1]);
//
//		int ch[1] = { 0 };
//		cv::Mat result = finder.find(hsv, 0.0f, 180.0f, ch, 1);
//		// ���� ������׷��� ������ ��������
//		cv::bitwise_and(result, v[1], result);
//		// ���� ä�� ȭ�� ���� (���� ä�� ȭ�� ���� ����)
//		// ���� ������׷��� ������ ��������
//		finder.setThreshold(-1.0f);
//		result = finder.find(hsv, 0.0f, 180.0f, ch, 1);
//		cv::bitwise_and(result, v[1], result);
//
//		cv::imshow("aaaaaa", result);
//
//		//HSV�� ��ȯ
//		cvtColor(img_input, img_hsv, COLOR_BGR2HSV);
//
//		//������ HSV ������ �̿��Ͽ� ������ ����ȭ
//		inRange(img_hsv, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), img_binary);
//
//		//morphological opening ���� ������ ���� 
//		erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//		//morphological closing ������ ���� �޿�� 
//		dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//		//�󺧸� 
//		Mat img_labels, stats, centroids;
//		int numOfLables = connectedComponentsWithStats(img_binary, img_labels,
//			stats, centroids, 8, CV_32S);
//
//
//		//�����ڽ� �׸���
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
//		//������
//		inRange(img_hsv, Scalar(LowH_red, LowS, LowV), Scalar(HighH_red, HighS, HighV), img_red);
//		//morphological opening ���� ������ ���� 
//		erode(img_red, img_red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_red, img_red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//morphological closing ������ ���� �޿��
//		dilate(img_red, img_red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_red, img_red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//��
//		numOfLables = connectedComponentsWithStats(img_red, img_labels,
//			stats, centroids, 8, CV_32S);
//
//		//�����ڽ� �׸���
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
//		//morphological opening ���� ������ ���� 
//		erode(img_yellow, img_yellow, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_yellow, img_yellow, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//morphological closing ������ ���� �޿��
//		dilate(img_yellow, img_yellow, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_yellow, img_yellow, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//��
//		numOfLables = connectedComponentsWithStats(img_yellow, img_labels,
//			stats, centroids, 8, CV_32S);
//
//		//�����ڽ� �׸���
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
//		//morphological opening ���� ������ ���� 
//		erode(img_green, img_green, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_green, img_green, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//morphological closing ������ ���� �޿��
//		dilate(img_green, img_green, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_green, img_green, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//��
//		numOfLables = connectedComponentsWithStats(img_green, img_labels,
//			stats, centroids, 8, CV_32S);
//
//		//�����ڽ� �׸���
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
//		//morphological opening ���� ������ ���� 
//		erode(img_blue, img_blue, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_blue, img_blue, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//morphological closing ������ ���� �޿��
//		dilate(img_blue, img_blue, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_blue, img_blue, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//��
//		numOfLables = connectedComponentsWithStats(img_blue, img_labels,
//			stats, centroids, 8, CV_32S);
//
//		//�����ڽ� �׸���
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
//		//morphological opening ���� ������ ���� 
//		erode(img_indigo, img_indigo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_indigo, img_indigo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//morphological closing ������ ���� �޿��
//		dilate(img_indigo, img_indigo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_indigo, img_indigo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//��
//		numOfLables = connectedComponentsWithStats(img_indigo, img_labels,
//			stats, centroids, 8, CV_32S);
//
//		//�����ڽ� �׸���
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
//		//morphological opening ���� ������ ���� 
//		erode(img_violet, img_violet, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_violet, img_violet, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//morphological closing ������ ���� �޿��
//		dilate(img_violet, img_violet, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_violet, img_violet, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		//��
//		numOfLables = connectedComponentsWithStats(img_violet, img_labels,
//			stats, centroids, 8, CV_32S);
//
//		//�����ڽ� �׸���
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
//		//double *centroid = centroids.at<double>(idx, 0); //�߽���ǥ  
//		//putText(img_input, "img_violet", Point2d(centroids.at<double>(idx, 0)), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//		circle(img_input, Point(centroids.at<double>(idx, 0)), 5, Scalar(255, 0, 0), 1);
//		putText(img_input, "img_violet", Point(left, top), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1);
//		rectangle(img_input, Point(left, top), Point(left + width, top + height),
//			Scalar(0, 0, 255), 1);
//
//		////�ܼ��� ��� �󺧸� �׸��� ������
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
//		//imshow("����ȭ ����", img_binary);
//		imshow("���� ����", img_input);
//		imshow("�� ����", img_red);
//		imshow("�� ����", img_yellow);
//		imshow("�� ����", img_green);
//		imshow("�� ����", img_blue);
//		imshow("�� ����", img_indigo);
//		imshow("�� ����", img_violet);
//		//ESCŰ ������ ���α׷� ����
//		if (waitKey(1) == 27)
//			break;
//	}
//	return 0;
//}
//
