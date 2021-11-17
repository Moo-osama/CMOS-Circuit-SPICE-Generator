#include <iostream>
#include <string>
#include "post-proc.h"
#include "recursive.h"
#include "postfix.h"

using namespace std;

int main(int argc, char *argv[])
{
    vector<CMOS> deck;
    vector<char> output_labels;
    vector<string> expressions;
    string input;

    /* User input */
    cout << "Enter valid boolean expressions separated by ';':" << endl;
    cin >> input;
    cout << endl;

    /* Generating postfix expressions*/
    output_labels = extract_output_labels(input);
    expressions = get_postfix_vec(input);

    for (int i = 0; i < expressions.size(); i++) {
        /* Generating separate expressions for both pun and pdn*/
        vector<char> pun, pdn;
        post_proc(expressions[i], pun, pdn);

        /* for testing purpose this code ptints the postfix expressions for pun and pdn */
        // for (int i = 0; i < pun.size(); i++)
        //     cout << pun[i];
        // cout << endl;

        // for (int i = 0; i < pdn.size(); i++)
        //     cout << pdn[i];
        // cout << endl;

        /* Construction of the pun and pdn*/
        bool flag = false;
        run(pun, &deck, "Y", "VDD", PMOS, flag);
        flag = false;
        run(pdn, &deck, "Y", "0", NMOS, flag);
    }

    /* Netlist output*/
    CMOS decks;
    for (int i = 0; i < deck.size(); i++){
        decks = deck[i]; 
        cout << decks.m_name << " " << decks.drain << " " << decks.gate << " "
            << decks.source << " "<< decks.body << " "
            << (decks.type == PMOS? "PMOS" : "NMOS") <<endl;
    }

    return 0;
}