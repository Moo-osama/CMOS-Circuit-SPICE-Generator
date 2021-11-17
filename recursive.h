#pragma once

#include<vector>
#include<string>

using namespace std; 

int m_number = 0;
int curr_node = 0;
enum m_type { PMOS , NMOS };
struct CMOS {
    string m_name;
    string drain;
    string gate;
    string source;
    string body;
    m_type type; 
};

string new_node()
{
    curr_node++;
    return /*"N" + */to_string(curr_node);
}

string new_mosfet()
{
    m_number++;
    return "M" + to_string(m_number);
}

string not_f (vector<char> &expression, vector<CMOS> *deck)
{
    CMOS m1, m2; 
    string output = new_node();
    
    m1.m_name = new_mosfet();
    m1.drain = output;
    m1.gate = expression.back();
    m1.source = "VDD"; 
    m1.body = m1.source;
    m1.type = PMOS;
    
    m2.m_name = new_mosfet();
    m2.drain = output;
    m2.gate = m1.gate = expression.back();
    m2.source = "0"; 
    m2.body = m2.source;
    m2.type = NMOS;

    expression.pop_back();
    deck->push_back(m1);
    deck->push_back(m2);
    return output;
}


int is_operator(char c)
{
    switch (c)
    {
    case '`':
        return 1; 
        break;
    case '|':
        return 1; 
        break;
    case '&':
        return 1; 
        break;
    default:
        return 0;
        break;
    }
 
}

void run (vector<char> &expression, vector<CMOS> *deck , string drain , string source, m_type type, bool &found_neg)
{
    if (!is_operator(expression.back())){
        if (type == PMOS && !found_neg) {
            string not_gate = not_f(expression, deck);

            CMOS m; 
            m.gate = not_gate;
            m.drain = drain;
            m.source = source;
            m.body = source;
            m.type = type; 
            m.m_name = new_mosfet();
            deck->push_back(m);
        } else {
            CMOS m; 
            m.gate = expression.back();
            expression.pop_back();
            m.drain = drain;
            m.source = source;
            m.body = source;
            m.type = type; 
            m.m_name = new_mosfet();
            deck->push_back(m);
        }
    }
    else
    {
        
        switch (expression.back())
        {
        case '|':
            expression.pop_back();
            run(expression, deck , drain , source , type, found_neg);
            // expression.pop_back();
            run(expression, deck , drain , source , type, found_neg);           
            break;

        case '&': {
            expression.pop_back();
            string node = new_node();
            run(expression, deck , drain , node , type, found_neg);
            // expression.pop_back();
            run(expression, deck , node , source , type, found_neg); 
            break;
            }
        case '`':
            expression.pop_back();
            if (type == NMOS) {
                string not_gate = not_f(expression, deck);

                CMOS m; 
                m.gate = not_gate;
                m.drain = drain;
                m.source = source;
                m.body = source;
                m.type = type; 
                m.m_name = new_mosfet();
                deck->push_back(m);
            } else {
                found_neg = true;
                run(expression, deck , drain , source , type, found_neg);
                found_neg = false;
            }
            break;
        }
    }
}