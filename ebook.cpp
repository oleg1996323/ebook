#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <string>
#include <tuple>
#include <fstream>
#include <sstream>
#include <cassert>

constexpr int DIDNT_READ=0;
constexpr int MAX_USERS=10E5;
constexpr int MAX_PAGES=10E3;

enum class TAction{
    CHEER,
    READ
};

struct ActionBase{
    TAction type;
    int user_id;
};

struct ActionRead:public ActionBase{
    int pages_read;
};

using ActionCheer = ActionBase;
using Action = ActionRead;

class ReadingManager{
    std::vector<int> pages_by_user_id_;
    std::vector<int> number_of_users_by_pages_;
    std::ostream& output_stream;

    double CalculateUsersReadPagesRelation(int user_id) const{

        if(number_of_users_by_pages_[DIDNT_READ]<MAX_USERS-1){
            double users_read_less = std::accumulate(number_of_users_by_pages_.begin()+1,
                                                    number_of_users_by_pages_.begin()+pages_by_user_id_[user_id],
                                                    0);
            double not_less_read_users = MAX_USERS-users_read_less-number_of_users_by_pages_[0]-1;

            double all_other_active_users = not_less_read_users+users_read_less;

            return users_read_less/all_other_active_users;
        }
        else if(number_of_users_by_pages_[DIDNT_READ]==MAX_USERS-1)
            return 1;
        else return 0;
    }

    void Cheer(int user_id){
        if(pages_by_user_id_[user_id]==DIDNT_READ)
            output_stream<<0<<std::endl; 
        else
            output_stream<<CalculateUsersReadPagesRelation(user_id)<<std::endl;         
    }

    void Read(int user_id, int pages){
        --number_of_users_by_pages_[pages_by_user_id_[user_id]];
        pages_by_user_id_[user_id]=pages;
        ++number_of_users_by_pages_[pages];
    }

    public:
    
    ReadingManager(std::ostream& stream):output_stream(stream){
        pages_by_user_id_.resize(MAX_USERS+1);
        number_of_users_by_pages_.resize(MAX_PAGES+1);
        number_of_users_by_pages_[DIDNT_READ]=MAX_USERS;
    }

    void ActionImpl(const Action& action){
        if(action.type==TAction::READ){
            Read(action.user_id,action.pages_read);
        }
        else if(action.type==TAction::CHEER)
            Cheer(action.user_id);
    }
};

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

void Test(){
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

int main(){
    //Test();
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
