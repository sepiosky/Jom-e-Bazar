CC := g++
CCFLAGS += -w

all: Bazar.out

Bazar.out: main.o bazar.o product.o tv.o car.o mobile.o user.o customer.o manager.o buyer.o seller.o offer.o comment_classifier.o
	$(CC) main.o bazar.o product.o tv.o car.o mobile.o user.o customer.o manager.o buyer.o seller.o offer.o comment_classifier.o $(CCFLAGS) -o Bazar.out

comment_classifier.o: exceptions.h comment_classifier.h comment_classifier.cpp
	$(CC) -c comment_classifier.cpp -o comment_classifier.o

tv.o: tv.h tv.cpp
	$(CC) -c tv.cpp -o tv.o

car.o: car.h car.cpp
	$(CC) -c car.cpp -o car.o

mobile.o: mobile.h mobile.cpp
	$(CC) -c mobile.cpp -o mobile.o

product.o: offer.h product.h product.cpp
	$(CC) -c product.cpp -o product.o

offer.o: offer.h offer.cpp
	$(CC) -c offer.cpp -o offer.o

buyer.o: comment_classifier.h buyer.h buyer.cpp
	$(CC) -c buyer.cpp -o buyer.o

seller.o: seller.h seller.cpp
	$(CC) -c seller.cpp -o seller.o

customer.o: customer.h customer.cpp
	$(CC) -c customer.cpp -o customer.o

manager.o: manager.h product.h user.h tv.h car.h mobile.h manager.cpp
	$(CC) -c manager.cpp -o manager.o

user.o: product.h comment_classifier.h exceptions.h user.h user.cpp
	$(CC) -c user.cpp -o user.o

bazar.o: product.h user.h manager.h buyer.h seller.h offer.h comment_classifier.h exceptions.h bazar.h bazar.cpp
	$(CC) -c bazar.cpp  -o bazar.o

main.o: bazar.h main.cpp
	$(CC) -c main.cpp -o main.o



.PHONY: clean
clean:
	rm -r *.o
