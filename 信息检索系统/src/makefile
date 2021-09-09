CC=g++
CFLAGS=-g -Wall 
target=server
src=$(wildcard *.cc) $(wildcard ../tinyxml2/*.cc) 
obj=$(patsubst %.cc, %.o, $(src))
$(target):$(obj)
	$(CC) $(CFLAGS)  $^ -o $@ $(link)
%.o:%.cc
	$(CC) $(CFLAGS) -c $< -o $@ $(link)
clean:
	rm -rf $(target) $(obj)
