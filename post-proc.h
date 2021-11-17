#pragma once


#include <vector>
#include <string>

using namespace std;

void skip(vector<char> &postfix, vector<char> &temp)
{
    int count = 1;
    while (count != 0) {
        char c = postfix.back();
        postfix.pop_back();

        switch (c) {
        case '`':
            temp.push_back(c);
            break;
        
        case '|':
            temp.push_back(c);
            count++;
            break;

        case '&':
            temp.push_back(c);
            count++;
            break;
        
        default:
            temp.push_back(c);
            count--;
            break;
        }
    }
}

void neg_prog(vector<char> &postfix)
{
    vector<char> temp;
    bool done = true;

    do {
        done = true;

        while (postfix.size() != 0) {
            char c = postfix.back();
            postfix.pop_back();
            
            if (c == '`') {
                int count = 1;
                while (count != 0){
                    c = postfix.back();
                    postfix.pop_back();

                    switch (c) {
                    case '`':
                        count--;
                        done = false;
                        if (count > 0)
                            skip(postfix, temp);
                        break;
                    
                    case '|':
                        temp.push_back('&');
                        count++;
                        break;

                    case '&':
                        temp.push_back('|');
                        count++;
                        break;
                    
                    default:
                        temp.push_back('`');
                        temp.push_back(c);
                        count--;
                        break;
                    }
                }
            } else {
                temp.push_back(c);
            }
        }

        while (temp.size() != 0) {
            char c = temp.back();
            temp.pop_back();
            postfix.push_back(c);
        }
    } while (!done);
}

void post_proc(string input, vector<char> &pun, vector<char> &pdn)
{
    vector<char> postfix;
    for (int i = 0; i < input.length(); i++)
        postfix.push_back(input.at(i));

    neg_prog(postfix);
    pun = postfix;
    
    postfix.push_back('`');
    neg_prog(postfix);
    pdn = postfix;
}