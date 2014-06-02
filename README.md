High-Dimensional-LBP
====================

My implementation of high dimensional lbp feature for face recognition based on 

Dong Chen, Xudong Cao, Fang Wen, Jian Sun. Blessing of Dimensionality: High-dimensional Feature and Its Efficient Compression for Face Verification. Computer Vision and Pattern Recognition (CVPR), 2013.

I use openCV for face detection and [IntraFace](http://www.humansensing.cs.cmu.edu/intraface/) for facial landmark detection.

##Prerequisites

###openCV

Install openCV and change the first line in src/Makefile to opencv home directory:

    OPENCV_HOME = /path/to/opencv/

###IntraFace

Download IntraFace Library from http://www.humansensing.cs.cmu.edu/intraface/ (I used v1.0)

and put

1. *libintraface.a* to lib/
2. *DetectionModel-v1.5.yml*,*TrackingModel-v1.10.yml* to data/
3. *FaceAlignment.h *, *Marcos.h*, *XXDescriptor.h* to include/

##Build

change to src directory and type make

##Usage

If everythings goes right, there will be to binary files in bin/

face-detection will detect the largest face in the input images and crop the faces into a new image.

    Usage: face-detection [-m model_file -o output_dir -s output_scale -l min_size] input_images

    model_file: face detection model file, default: ../data/fdetector_model.dat
    output_dir: output directory for face images, default: ./
    output_scale: output face image size, default: 250
    min_size: minimal face size for detection, default: 100
    input_images: images for face detection

After face detection, we can extract the high dimensional LBP features using extract-lbp:

    Usage: extract-lbp [-m model_dir -o output_dir] input_images

    model_dir: model directory for landmark detection, default: ../data/
    output_dir: output directory for lbp features, default: ./
    input_images: face images for featrue extraction

The output will be  *image_name.lbp* which contains 75,520 dimensional lbp features

##Contact

If you have any questions, feel free to contact me at bcsiriuschen@gmail.com
