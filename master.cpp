
#include "ImageConsProd.hpp" 
#include <thread> 
#include <unistd.h>
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char * argv[])
{
    ImageConsProd image_cons_prod;

    std::thread task0(&ImageConsProd::ImageProducer, image_cons_prod); 
    std::thread task1(&ImageConsProd::ImageConsumer, image_cons_prod);

    task0.join();
    task1.join();

	return EXIT_SUCCESS;
}
 
