test:
	g++.exe -otest.exe -DCATCH_CONFIG_MAIN speedfunctions.cpp;\
	./test.exe

clean:
	rm test.exe
