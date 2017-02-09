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
//		Mat img_input, img_hsv, img_binary;
//
//
//		//ī�޶�κ��� �̹����� ������ 
//		bool ret = cap.read(img_input);
//
//		if (!ret)
//		{
//			cout << "ī�޶�κ��� �̹����� ������ �� �����ϴ�." << endl;
//			break;
//		}
//
//
//		//HSV�� ��ȯ
//		cvtColor(img_input, img_hsv, COLOR_BGR2HSV);
//
//
//		//������ HSV ������ �̿��Ͽ� ������ ����ȭ
//		inRange(img_hsv, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), img_binary);
//
//
//		//morphological opening ���� ������ ���� 
//		erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//
//		//morphological closing ������ ���� �޿�� 
//		dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
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
//
//
//		int left = stats.at<int>(idx, CC_STAT_LEFT);
//		int top = stats.at<int>(idx, CC_STAT_TOP);
//		int width = stats.at<int>(idx, CC_STAT_WIDTH);
//		int height = stats.at<int>(idx, CC_STAT_HEIGHT);
//
//
//		rectangle(img_input, Point(left, top), Point(left + width, top + height),
//			Scalar(0, 0, 255), 1);
//
//
//		imshow("����ȭ ����", img_binary);
//		imshow("���� ����", img_input);
//
//
//		//ESCŰ ������ ���α׷� ����
//		if (waitKey(1) == 27)
//			break;
//	}
//
//
//	return 0;
//}