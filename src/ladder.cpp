#include "ladder.h"
#include <fstream>

void error(string word1, string word2, string msg) 
{
    cout << "Error: " << msg << " for words '" << word1 << "' and '" << word2 << "'" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int len1 = str1.length();
    int len2 = str2.length();
    
    if (abs(len1 - len2) > d) 
    {
        return false;
    }
    
    if (str1 == str2) 
    {
        return false; 
    }
    
    if (d == 1) 
    {
        if (len1 == len2) 
        {
            int diff = 0;
            for (int i = 0; i < len1; i++) 
            {
                if (str1[i] != str2[i]) 
                {
                    diff++;
                }
                if (diff > d) 
                {
                    return false;
                }
            }

            return true;
        }
        
        if (len1 == len2 + 1) 
        {
            int i = 0, j = 0;
            while (i < len1 && j < len2) 
            {
                if (str1[i] != str2[j]) 
                {
                    i++;
                } 
                else 
                {
                    i++;
                    j++;
                }
            }

            return i == len1 && j == len2;
        }
        

        if (len1 == len2 - 1) 
        {
            int i = 0, j = 0;
            while (i < len1 && j < len2) 
            {
                if (str1[i] != str2[j]) 
                {
                    j++;
                } 
                else 
                {
                    i++;
                    j++;
                }
            }

            return i == len1 && j == len2;
        }
    }
    
    return false;
}

bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) 
{
    if (begin_word == end_word) 
    {
        return {begin_word};
    }
    
    string begin_word_lower = begin_word;
    string end_word_lower = end_word;
    for (char& c : begin_word_lower) c = tolower(c);
    for (char& c : end_word_lower) c = tolower(c);
    
    if (word_list.find(end_word_lower) == word_list.end()) 
    {
        return {};
    }
    
    queue<vector<string>> ladder_queue;
    
    ladder_queue.push({begin_word_lower});
    
    set<string> visited;
    visited.insert(begin_word_lower);
    
    while (!ladder_queue.empty()) 
    {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        
        string last_word = current_ladder.back();
        
        for (const string& word : word_list) 
        {
            if (visited.find(word) != visited.end()) 
            {
                continue;
            }
            
            if (is_adjacent(last_word, word)) 
            {
                visited.insert(word);
                
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);
                
                if (word == end_word_lower) 
                {
                    return new_ladder;
                }
                
                ladder_queue.push(new_ladder);
            }
        }
    }
    
    return {};
}

void load_words(set<string>& word_list, const string& file_name) 
{
    ifstream file(file_name);

    if (!file) 
    {
        cerr << "Error: Unable to open file " << file_name << endl;
        return;
    }
    
    string word;

    while (file >> word) 
    {
        for (char& c : word) 
        {
            c = tolower(c);
        }

        word_list.insert(word);
    }
    
    file.close();
}

void print_word_ladder(const vector<string>& ladder) 
{
    if (ladder.empty()) 
    {
        cout << "No word ladder found!" << endl;
        return;
    }
    
    for (size_t i = 0; i < ladder.size(); ++i) 
    {
        cout << ladder[i];
        if (i < ladder.size() - 1) 
        {
            cout << " -> ";
        }
    }
    cout << endl;
}

void verify_word_ladder() 
{
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    
    auto my_assert = [](bool condition, const string& msg) 
    {
        cout << msg << (condition ? " passed" : " failed") << endl;
    };
    
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4, 
              "generate_word_ladder(\"cat\", \"dog\", word_list).size() == 4");
    
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6, 
              "generate_word_ladder(\"marty\", \"curls\", word_list).size() == 6");
    
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6, 
              "generate_word_ladder(\"code\", \"data\", word_list).size() == 6");
    
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6, 
              "generate_word_ladder(\"work\", \"play\", word_list).size() == 6");
    
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8, 
              "generate_word_ladder(\"sleep\", \"awake\", word_list).size() == 8");
    
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4, 
              "generate_word_ladder(\"car\", \"cheat\", word_list).size() == 4");
}