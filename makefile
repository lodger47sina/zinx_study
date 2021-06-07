srcFile = $(wildcard *.cpp)
dstFile = $(patsubst %.cpp,%.o,$(srcFile))

LIBS=-lzinx

app = app
target=$(app)
all:$(target)

$(app):$(dstFile)
	g++ -o $@ $(dstFile) $(LIBS)

%.o:%.cpp
	g++ -c -o $@ $<

clean:
	-@rm -f $(target) *.o
