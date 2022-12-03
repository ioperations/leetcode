#!/usr/bin/env make
srcs_cc = $(wildcard *.cc)
target_cc = $(patsubst %.cc, %, $(srcs_cc))
dym_target = $(patsubst %.cc, %.dSYM, $(srcs_cc))


srcs_cpp = $(wildcard *.cpp)
target_cpp = $(patsubst %.cpp, %, $(srcs_cpp))


CXX=clang++
override CPPFLAGS := -std=c++20  -DTEST_ADQ -Wpedantic -Wall -fsanitize=address  -lgtest -lpthread  -lbenchmark -L/usr/local/lib -I/usr/local/include 
#-fuse-ld=lld
default:${target_cc} # ${target_ccu}
	@-echo "ok"

%_bench:%_bench.cc
	${CXX} $< -lbenchmark -lgtest -o $@

%:%.cc
	${CXX} ${CPPFLAGS} $< -o $@

run:default
	for i in ${target_cc}; do echo $$i &&  timeout 60  ./$$i || exit ; done

clean:
	@-rm -rf $(target_cc)  a.out  *.o *.i *.dSYM *.s *.hi ${dym_target} ${target_cpp} build
