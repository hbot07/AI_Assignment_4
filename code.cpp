//
// Created by Parth Thakur on 28/10/23.
//


#include "startup_code.cpp"
#include <numeric>
#include <bits/stdc++.h>
#include <map>
using namespace std;


// read records.dat and store in column arrays

void read_records(const string& filename, int ncols, vector<vector<string> >& records){
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "error: couldn't open file" << filename << endl;
        return;
    }

    cout << "reading " << filename << endl;
    string line;
    cout << line << endl;
    while(getline(inputFile, line)){
//        cout << "reading line" << endl;
        size_t pos = 0;
        string token;
        vector<string> tokens;

        while((pos = line.find(" ")) != string::npos)
        {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos+1);
        }

        tokens.push_back(line);

//        cout << "tokens size: " << tokens.size() << endl;

        if(tokens.size() == ncols){
            for(int i=0; i<ncols; i++){
//                cout << "pushing " << tokens[i] << endl;
                records[i].push_back(tokens[i]);
            }
        }
        else{
            cout << "error: wrong length" << endl;
        }
    }
}

void calculate_priors(network Alarm, vector<vector<string> > records){
    vector<list<Graph_Node>::iterator> parentless_nodes;

    for(int i=0; i < Alarm.netSize(); i++){
        if(Alarm.get_nth_node(i)->get_Parents().size() == 0){
            parentless_nodes.push_back(Alarm.get_nth_node(i));
        }
    }
    cout << "parentless nodes: " << parentless_nodes.size() << endl;
}

float calc_prob(vector<string> var_names, vector<string> permutation,vector<vector<string> > records){
    int numColumns = records[0].size();
    map<string,int> variable_mapping;
    variable_mapping["A"]=0;
    variable_mapping["B"]=1;
    variable_mapping["C"]=2;
    vector<double> recordsWeightColumn(numColumns, 1.0);
    vector<bool> count(numColumns, true);
    for (int i = 0; i < var_names.size(); i++) {
        int varIndex = variable_mapping[var_names[i]]; 
        for (int j = 0; j < records.size(); j++) {
            if (records[j][varIndex] != permutation[i]) {
            count[j] = false;
            }
        }
    }
    double sumWeight = 0.0;
    for (int i = 0; i < records.size(); ++i) {
        if (count[i]) {
            sumWeight += recordsWeightColumn[i];
        }
    }
    double totalSumWeight = accumulate(recordsWeightColumn.begin(), recordsWeightColumn.end(), 0.0);

    double prob = sumWeight / totalSumWeight;
    return prob;
}

int main()
{
    network Alarm;
    Alarm=read_network();

// Example: to do something
    cout<<"Perfect! Hurrah! \n";

    int ncols = Alarm.netSize();

    vector<vector<string> > records(ncols);
    read_records("records.dat", 3, records);

    //calculate_priors(Alarm, records);
    cout<<calc_prob({"A","B"},{"True","False"},records)<<endl;
    //cout<<Alarm.get_nth_node(1)->get_name()<<endl;
    //cout << Alarm.get_nth_node(0)->get_children().size() << endl;
}
