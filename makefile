story: story.cpp
	g++ -o story.o -c story.cpp
	windres resource.rc -o resource.o
	g++ -o story.exe story.o resource.o -mwindows

clean:
	rm story.o resource.o
