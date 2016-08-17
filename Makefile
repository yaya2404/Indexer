index : main.o index.o sorted-list.o tokenizer.o
	cc -o index main.o index.o sorted-list.o tokenizer.o
main.o : main.c index.h
	cc -c main.c
index.o : index.c index.h
	cc -c index.c
sorted-list.o : sorted-list.c sorted-list.h
	cc -c sorted-list.c
tokenizer.o : tokenizer.c tokenizer.h 
	cc -c tokenizer.c
clean : 
	rm index main.o index.o sorted-list.o tokenizer.o
