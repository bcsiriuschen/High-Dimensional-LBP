OPENCV_HOME = /usr/include/opencv/

CC = g++
CFLAG = -std=c++11
LIB = -lopencv_core -lopencv_objdetect -lopencv_highgui -lopencv_imgproc
INC = -I../include/ -I$(OPENCV_HOME)
OBJ = ArgumentParser.o FaceDetector.o LBPFeatureExtractor.o FaceNormalizer.o sirius_util.o
EXE = face-detection extract-lbp

all:face-detection extract-lbp

face-detection: face-detection.cpp $(OBJ)
	$(CC) -o $@ $@.cpp $(OBJ) $(LIB) $(INC) $(CFLAG)
	cp $@ ../bin/

extract-lbp: extract-lbp.cpp $(OBJ) ../lib/libintraface.a
	$(CC) -o $@ $@.cpp $(OBJ) $(LIB) $(INC) $(CFLAG) ../lib/libintraface.a
	cp $@ ../bin/

%.o: %.cpp ../include/%.h
	$(CC) -c $< $(LIB) $(INC) $(CFLAG)

clean:
	rm -rf *.o $(EXE)
