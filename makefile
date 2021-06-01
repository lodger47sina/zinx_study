srcFile = $(wildcard *.cpp)
dstFile = $(patsubst %.cpp,%.o,$(srcFile))

LIBS = -lzinx

app = zinx_study
target=$(app)

all:$(target)

$(app):$(dstFile)
	g++ -o $@ $(dstFile) $(LIBS) -g

%.o:%.cpp
	g++ -o $@ -c $<

clean:
	-@rm -f $(dstFile) $(target)
