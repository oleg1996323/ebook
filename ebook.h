#pragma once
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

    double CalculateUsersReadPagesRelation(int user_id) const;

    void Cheer(int user_id);

    void Read(int user_id, int pages);

    public:
    
    ReadingManager(std::ostream& stream);

    void ActionImpl(const Action& action);
};
