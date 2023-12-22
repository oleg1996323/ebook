#include <iostream>
#include "ebook.h"
#include "test.h"
#include "reading.h"

int main(){
    //TestBenchmark();
    int lines;
    //std::fstream input("bin/based.txt");
    //std::string out;
    //std::ostringstream out_stream(out,std::ios::out | std::ios::in);
    ReadingManager manager(std::cout);
    
    std::cin>>lines;
    for (int i=0;i<lines;++i){
        auto& action=Readline(std::cin);
        manager.ActionImpl(action);
    }
    //std::cout<<out_stream.str();
}
