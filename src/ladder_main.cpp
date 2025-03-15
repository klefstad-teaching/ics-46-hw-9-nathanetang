#include "ladder.h"

int main() 
{
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    
    string start_word, end_word;
    
    cout << "Enter the start word: ";
    cin >> start_word;
    
    cout << "Enter the end word: ";
    cin >> end_word;
    
    if (start_word == end_word) 
    {
        error(start_word, end_word, "Start and end words cannot be the same");
        return 1;
    }
    
    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    
    if (ladder.empty()) 
    {
        cout << "No word ladder found from '" << start_word << "' to '" << end_word << "'!" << endl;
    } 
    else 
    {
        cout << "Word ladder from '" << start_word << "' to '" << end_word << "':" << endl;
        print_word_ladder(ladder);
        cout << "Ladder length: " << ladder.size() << endl;
    }
    
    return 0;
}