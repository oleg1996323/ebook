#pragma once
#include <iostream>
#include "ebook.h"

const Action& Readline(std::istream& stream){
    std::string command;
    std::getline(stream,command);
    stream>>command;
    static Action result;
    if(!stream.eof()){
        if(command=="CHEER"){
            int user_id;
            stream>>user_id;
            result = std::move(Action({TAction::CHEER,user_id,0}));
        }
        else
        {
            int user_id;
            int pages_read;
            stream>>user_id>>pages_read;
            result = std::move(Action({TAction::READ,user_id,pages_read}));
        }
    }
    
    return result;
}