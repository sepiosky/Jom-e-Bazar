CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD) -w
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/comment_classifier.o: domain/exceptions.h domain/comment_classifier.h domain/comment_classifier.cpp
	$(CC) -c domain/comment_classifier.cpp -o $(BUILD_DIR)/comment_classifier.o

$(BUILD_DIR)/tv.o: domain/tv.h domain/tv.cpp
	$(CC) -c domain/tv.cpp -o $(BUILD_DIR)/tv.o

$(BUILD_DIR)/car.o: domain/car.h domain/car.cpp
	$(CC) -c domain/car.cpp -o $(BUILD_DIR)/car.o

$(BUILD_DIR)/mobile.o: domain/mobile.h domain/mobile.cpp
	$(CC) -c domain/mobile.cpp -o $(BUILD_DIR)/mobile.o

$(BUILD_DIR)/product.o: domain/offer.h domain/product.h domain/product.cpp
	$(CC) -c domain/product.cpp -o $(BUILD_DIR)/product.o

$(BUILD_DIR)/offer.o: domain/offer.h domain/offer.cpp
	$(CC) -c domain/offer.cpp -o $(BUILD_DIR)/offer.o

$(BUILD_DIR)/buyer.o: domain/comment_classifier.h domain/buyer.h domain/buyer.cpp
	$(CC) -c domain/buyer.cpp -o $(BUILD_DIR)/buyer.o

$(BUILD_DIR)/seller.o: domain/seller.h domain/seller.cpp
	$(CC) -c domain/seller.cpp -o $(BUILD_DIR)/seller.o

$(BUILD_DIR)/customer.o: domain/customer.h domain/customer.cpp
	$(CC) -c domain/customer.cpp -o $(BUILD_DIR)/customer.o

$(BUILD_DIR)/manager.o: domain/manager.h domain/product.h domain/user.h domain/tv.h domain/car.h domain/mobile.h domain/manager.cpp
	$(CC) -c domain/manager.cpp -o $(BUILD_DIR)/manager.o

$(BUILD_DIR)/user.o: domain/product.h domain/comment_classifier.h domain/exceptions.h domain/user.h domain/user.cpp
	$(CC) -c domain/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/bazar.o: domain/product.h domain/user.h domain/manager.h domain/buyer.h domain/seller.h domain/offer.h domain/comment_classifier.h domain/exceptions.h domain/bazar.h domain/bazar.cpp
	$(CC) -c domain/bazar.cpp  -o $(BUILD_DIR)/bazar.o

$(BUILD_DIR)/template_parser.o: ../APHTTP/utils/template_parser.cpp ../APHTTP/utils/template_parser.hpp ../APHTTP/utils/request.cpp ../APHTTP/utils/request.hpp ../APHTTP/utils/utilities.hpp ../APHTTP/utils/utilities.cpp
	$(CC) $(CF) -c ../APHTTP/utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: ../APHTTP/utils/response.cpp ../APHTTP/utils/response.hpp ../APHTTP/utils/include.hpp
	$(CC) $(CF) -c ../APHTTP/utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: ../APHTTP/utils/request.cpp ../APHTTP/utils/request.hpp ../APHTTP/utils/include.hpp ../APHTTP/utils/utilities.hpp
	$(CC) $(CF) -c ../APHTTP/utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: ../APHTTP/utils/utilities.cpp ../APHTTP/utils/utilities.hpp
	$(CC) $(CF) -c ../APHTTP/utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: ../APHTTP/server/server.cpp ../APHTTP/server/server.hpp ../APHTTP/server/route.hpp ../APHTTP/utils/utilities.hpp ../APHTTP/utils/response.hpp ../APHTTP/utils/request.hpp ../APHTTP/utils/include.hpp ../APHTTP/utils/template_parser.hpp ../APHTTP/utils/template_parser.cpp
	$(CC) $(CF) -c ../APHTTP/server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: ../APHTTP/server/route.cpp ../APHTTP/server/route.hpp ../APHTTP/utils/utilities.hpp ../APHTTP/utils/response.hpp ../APHTTP/utils/request.hpp ../APHTTP/utils/include.hpp
	$(CC) $(CF) -c ../APHTTP/server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: handlers.cpp ../APHTTP/server/server.hpp ../APHTTP/utils/utilities.hpp ../APHTTP/utils/response.hpp ../APHTTP/utils/request.hpp ../APHTTP/utils/include.hpp domain/bazar.h
	$(CC) $(CF) -c handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: my_server.cpp ../APHTTP/server/server.hpp ../APHTTP/utils/utilities.hpp ../APHTTP/utils/response.hpp ../APHTTP/utils/request.hpp ../APHTTP/utils/include.hpp
	$(CC) $(CF) -c my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: main.cpp domain/bazar.h ../APHTTP/server/server.hpp ../APHTTP/utils/utilities.hpp ../APHTTP/utils/response.hpp ../APHTTP/utils/request.hpp ../APHTTP/utils/include.hpp
	$(CC) $(CF) -c main.cpp -o $(BUILD_DIR)/main.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/bazar.o $(BUILD_DIR)/user.o $(BUILD_DIR)/manager.o $(BUILD_DIR)/customer.o $(BUILD_DIR)/seller.o $(BUILD_DIR)/buyer.o $(BUILD_DIR)/offer.o $(BUILD_DIR)/product.o $(BUILD_DIR)/mobile.o $(BUILD_DIR)/tv.o $(BUILD_DIR)/car.o $(BUILD_DIR)/comment_classifier.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/bazar.o $(BUILD_DIR)/user.o $(BUILD_DIR)/manager.o $(BUILD_DIR)/customer.o $(BUILD_DIR)/seller.o $(BUILD_DIR)/buyer.o $(BUILD_DIR)/offer.o $(BUILD_DIR)/product.o $(BUILD_DIR)/mobile.o $(BUILD_DIR)/tv.o $(BUILD_DIR)/car.o $(BUILD_DIR)/comment_classifier.o  -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
