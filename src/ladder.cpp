#include "../src/ladder.h"

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word){
        std::cout << "begin and end word same" << std::endl;
        vector <std::string> return_vec;
        //return_vec.push_back(begin_word);
        return return_vec;
    }
    queue<vector<std::string>> ladder_queue;
    vector <std::string> begin_word_ladder;
    begin_word_ladder.push_back(begin_word);
    ladder_queue.push(begin_word_ladder);
    set<std::string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()){
        vector <std::string> curr_ladder = ladder_queue.front();
        ladder_queue.pop();
        std::string last_word = curr_ladder.back();
        for (auto word : word_list){
            if (is_adjacent(last_word, word)){
                if (visited.find(word) == visited.end()){
                    visited.insert(word);
                    std::vector <std::string> new_ladder = curr_ladder;
                    new_ladder.push_back(word);
                    if (word == end_word){
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    vector <std::string> no_ladder_found;
    return no_ladder_found;
}


bool is_adjacent(const string& word1, const string& word2){
    if (word1 == word2){
        return true;
    }
    int word1_len = word1.length();
    int word2_len = word2.length();
    if (word1_len == word2_len){
        int diff = 0;
        for (int i = 0; i < word1_len; i++){
            if (tolower(word1[i]) != tolower(word2[i])){
                if (++diff > 1){
                    return false;
                }
            }
        }
        return diff == 1;
    }

    if ((word1_len - word2_len == 1) || (word1_len - word2_len == -1)){
        const std::string& longer = word1_len > word2_len ? word1 : word2;
        const std::string& shorter = word1_len < word2_len ? word1 : word2;

        int longer_index = 0;
        int shorter_index = 0;

        bool diff = false;

        while (longer_index < longer.size() && shorter_index < shorter.size()){
            if (tolower(longer[longer_index]) != tolower(shorter[shorter_index])){
                if (diff){
                    return false;
                }
                diff = true;
                ++longer_index;
            } else {
                ++longer_index;
                ++shorter_index;
            }
        }
        return true;
    }
    return false;
}

int edit_distance_helper(string str1, string str2, int i, int j){
    if (i == 0){
        return j;
    }
    if (j == 0){
        return i;
    }

    if (str1[i - 1] == str2[j - 1]){
        return edit_distance_helper(str1, str2, i - 1, j - 1);
    }

    return 1 + min(min(edit_distance_helper(str1, str2, i, j - 1), edit_distance_helper(str1, str2, i - 1, j)), edit_distance_helper(str1, str2, i - 1, j - 1));
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    return edit_distance_helper(str1, str2, str1.length(), str2.length()) <= d;
}



void load_words(set<string> & word_list, const string& file_name){
    std::ifstream in(file_name);
    for (std::string word; (in >> word);){
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.size() == 0){
        std::cout << "No word ladder found." << std::endl;
        return;
    }
    for (auto word : ladder){
        std::cout << word << " ";
    }
    std::cout << std::endl;
}

void error(string word1, string word2, string msg){
    std::cerr << "Error on words: " << word1 << " & " << word2 << std::endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder(){
    set<std::string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}