#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ebook.h"
#include "reading.h"

void TestBenchmark(){
    std::fstream input("bin/input_9.txt");
    std::fstream output("bin/output_9.txt");
    std::string out;
    std::string test;
    std::ostringstream test_stream(test,std::ios::out | std::ios::in);
    std::ostringstream out_stream(out,std::ios::out | std::ios::in);

    int lines;
    input>>lines;
    ReadingManager manager(test_stream);
    
    for (int i=0;i<lines;++i){
        auto& action=Readline(input);
        manager.ActionImpl(action);
    }

    while(output>>out){
        if(output.eof())
            break;
    }

    std::string str=test_stream.str();
}
