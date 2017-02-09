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
//	//��ĸ���� ĸó�Ǵ� �̹��� ũ�⸦ 320x240���� ����  
//	//cap.set(CAP_PROP_FRAME_WIDTH, 320);
//	//cap.set(CAP_PROP_FRAME_HEIGHT, 240);
//
//	if (!cap.isOpened())
//	{
//		cout << "��ķ�� �� �� �����ϴ�." << endl;
//		return -1;
//	}
//
//	int LowH = 170;
//	int HighH = 179;
//	//red   green  indigo 3������
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
//		cvtColor(test, src_gray, CV_BGR2GRAY);   //gray�� ��ȯ  
//		adaptiveThreshold(src_gray, addap_thr, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 21, 10);
//		imshow("����ȭ ����3", addap_thr);
//		//adaptiveThreshold(image, // �Է¿���
//		//	binaryAdaptive, // ����ȭ ��� ����
//		//	255, // �ִ� ȭ�� �� 
//		//	ADAPTIVE_THRESH_MEAN_C, // Adaptive �Լ�
//		//	THRESH_BINARY, // ����ȭ Ÿ��
//		//	blockSize,  // �̿�ũ��
//		//	threshold); // threshold used
//		cvtColor(addap_thr, img_hsv2, COLOR_GRAY2BGR);
//		imshow("����ȭ ����4", img_hsv2);
//		cvtColor(img_hsv2, img_hsv2, COLOR_BGR2HSV);
//		inRange(img_hsv2, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), img_binary2);
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
//		//�����ڽ� �׸���
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
//		//�ܼ��� ��� �󺧸� �׸��� ������
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
//		imshow("����ȭ ����2", img_binary2);
//		imshow("����ȭ ����", img_binary);
//		imshow("���� ����", img_input);
//		//imshow("�� ����", img_red);
//		//imshow("�� ����", img_yellow);
//		//imshow("�� ����", img_green);
//		//imshow("�� ����", img_blue);
//		//imshow("�� ����", img_indigo);
//		//imshow("�� ����", img_violet);
//		//ESCŰ ������ ���α׷� ����
//		if (waitKey(1) == 27)
//			break;
//	}
//	return 0;
//}