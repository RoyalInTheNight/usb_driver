CXX=g++
CC=gcc

STANDART=-std=gnu++17
USB=src/usb_driver.cpp

lib:
	$(CXX) -c $(USB) -o $(USB).o $(STANDART)
	ar rc libusb.a $(USB).o