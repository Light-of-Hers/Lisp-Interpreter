OBJS = main.o env.o eval-assign.o eval-begin.o eval-comb.o eval-define.o eval-if.o eval-lambda.o eval.o parse.o \
primitive.o running.o scan.o symbol.o util.o value.o error.o

CXXFLAGS = -Wall -O2 -std=c++1z

a: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean: 
	rm -rf a *.o

main.o: main.cc

env.o: env.cc

eval-assign.o: eval-assign.cc

eval-comb.o: eval-comb.cc

eval-define.o: eval-define.cc 

eval-if.o: eval-if.cc 

eval-lambda.o: eval-lambda.cc 

eval.o: eval.cc

parse.o: parse.cc 

primitive.o: primitive.cc 

running.o: running.cc 

scan.o: scan.cc 

symbol.o: symbol.cc 

util.o: util.cc 

value.o: value.cc

error.o: error.cc