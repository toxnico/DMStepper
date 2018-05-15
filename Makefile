speedtest:
	g++.exe -ospeedfunctions.exe -DCATCH_CONFIG_MAIN speedfunctions.cpp;\
	./speedfunctions.exe

gcodetest:
	g++.exe -ogcode.exe -DCATCH_CONFIG_MAIN gcodefunctions.cpp;\
	./gcode.exe

clean:
	rm speedfunctions.exe
