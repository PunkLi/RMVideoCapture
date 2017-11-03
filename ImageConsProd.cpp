
#include "ImageConsProd.hpp"
#include "RMVideoCapture.hpp"

using namespace cv;

#define VIDEO_WIDTH  640
#define VIDEO_HEIGHT 480
#define BUFFER_SIZE 1

volatile unsigned int prdIdx = 0;
volatile unsigned int csmIdx = 0;

struct ImageData {
	Mat img;             // data come from camera
	unsigned int frame;  // speed of img
};

ImageData capturedata[BUFFER_SIZE];   // Buffer of capture

void ImageConsProd::ImageProducer() 
{ 									
	RMVideoCapture cap("/dev/video1", 3); 
	cap.setVideoFormat(VIDEO_WIDTH, VIDEO_HEIGHT, 1);
	cap.startStream();
	cap.info();
	while (true) {
		while (prdIdx - csmIdx >= BUFFER_SIZE);
		cap >> capturedata[prdIdx % BUFFER_SIZE].img;
		capturedata[prdIdx % BUFFER_SIZE].frame = cap.getFrameCount();
		++prdIdx;
	}
}

void ImageConsProd::ImageConsumer() {

	Mat frame;

    while(true){
		while (prdIdx - csmIdx == 0);
		capturedata[csmIdx % BUFFER_SIZE].img.copyTo(frame);
		++csmIdx;

		try {
			imshow("frame", frame);
            waitKey(30);
		}
		catch (cv::Exception e) {
			std::cout<<"error"<<std::endl;
		}			
    }
}


