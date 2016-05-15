# The -B switch to make, whose long form is --always-make, tells make to disregard timestamps and make the specified
# targets.
latency:
	g++ -std=c++11 -O3 -funroll-loops latency.cpp -o latency
bandwidth:
	g++ -std=c++11 -O0 -funroll-loops bandwidth.cpp -o bandwidth
pagefault:
	g++ -std=c++11 -O3 -funroll-loops pagefault.cpp -o pagefault  # sudo ./pagefault
clean:
	rm -rf *o latency
	rm -rf *o bandwidth
	rm -rf *o pagefault
