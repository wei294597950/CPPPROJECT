reader:reader.o
	g++ -o reader reader.o

reader.o:reader_shm_sem.cpp
	g++ -c reader_shm_sem.cpp -o reader.o

writer:writer.o
	g++ -o writer writer.o

writer.o:writer_shm_sem.cpp
	g++ -c writer_shm_sem.cpp -o writer.o

clean:
	rm -rf *.o