OPENCV_HOME = /usr/local/Cellar/opencv/2.4.9/include/opencv/

CC = g++
CFLAG = -std=c++11
LIB = -L/usr/local/Cellar/opencv/2.4.9/lib/ -lopencv_core -lopencv_objdetect -lopencv_highgui -lopencv_imgproc
INC = -I../include/ -I$(OPENCV_HOME) -I../dlib-18.14/
OBJ = ArgumentParser.o FaceDetector.o LBPFeatureExtractor.o FaceNormalizer.o sirius_util.o
EXE = face-detection extract-lbp

all:face-detection extract-lbp

face-detection: face-detection.cpp $(OBJ)
	$(CC) -o $@ $@.cpp $(OBJ) $(LIB) $(INC) $(CFLAG)
	cp $@ ../bin/

extract-lbp: extract-lbp.cpp $(OBJ) ../lib/libintraface.a
	$(CC) -o $@ $@.cpp $(OBJ) $(LIB) $(INC) $(CFLAG) ../lib/libintraface.a
	cp $@ ../bin/

face_landmark_detection_ex: face_landmark_detection_ex.cpp
	$(CC) -O3 -o $@ $@.cpp $(INC) ../dlib-18.14/dlib/all/source.cpp -DDLIB_JPEG_SUPPORT -DDLIB_NO_GUI_SUPPORT -ljpeg -lpthread

%.o: %.cpp ../include/%.h
	$(CC) -c $< $(LIB) $(INC) $(CFLAG)

clean:
	rm -rf *.o $(EXE)
