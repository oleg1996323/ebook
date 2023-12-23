#include "ebook.h"

double ReadingManager::CalculateUsersReadPagesRelation(int user_id) const{
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

void ReadingManager::Cheer(int user_id){
    if(pages_by_user_id_[user_id]==DIDNT_READ)
        output_stream<<0<<std::endl; 
    else
        output_stream<<CalculateUsersReadPagesRelation(user_id)<<std::endl;         
}

void ReadingManager::Read(int user_id, int pages){
    --number_of_users_by_pages_[pages_by_user_id_[user_id]];
    pages_by_user_id_[user_id]=pages;
    ++number_of_users_by_pages_[pages];
}

ReadingManager::ReadingManager(std::ostream& stream):output_stream(stream){
    pages_by_user_id_.resize(MAX_USERS+1);
    number_of_users_by_pages_.resize(MAX_PAGES+1);
    number_of_users_by_pages_[DIDNT_READ]=MAX_USERS;
}

void ReadingManager::ActionImpl(const Action& action){
    if(action.type==TAction::READ){
        Read(action.user_id,action.pages_read);
    }
    else if(action.type==TAction::CHEER)
        Cheer(action.user_id);
}