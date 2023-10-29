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

float get_prob(vector<string> var_names, vector<string> permutation,vector<vector<string> > records, map<string,int> variable_mapping) {
    int numRecords=records[0].size();
    vector<bool> count(numRecords, true);
    vector<double> records_weight_column(numRecords, float(1));
    for (int i = 0; i < var_names.size(); i++) {
        for (int j = 0; j < records[0].size(); j++) {
            string s="";
            s+="\"";
            s+=permutation[i];
            s+="\"";
            //cout<<s<<endl;
            if (records[variable_mapping[var_names[i]]][j] != s) {
                count[j] = 0;
            }
            // for(int i=0;i<count.size();i++){
            //    cout<<count[i]<<endl;
            // }
            // cout<<endl;
        }
    }
    
    double sum_weight_column = 0.0;
    for (int i = 0; i < numRecords; i++) {
        if (count[i]) {
            sum_weight_column += records_weight_column[i];
        }
    }

    double sum_all_weights = 0.0;
    for (int weight : records_weight_column) {
        sum_all_weights += weight;
    }
    //cout<<sum_all_weights;
    double prob = sum_weight_column / sum_all_weights;

    return prob;
}

void update_bif(const string& in_filename, const string& out_filename,map<string,int> variable_mapping,vector<vector<float>> CPT){
    ifstream myfile(filename); 
    string temp_input;
    string line;
    ofstream out;
    string name;
    out.open(outfile);
    if (!myfile.is_open()){
        return;
    }
    else{
        while (! myfile.eof() )
            {
                stringstream ss;
                getline (myfile,line);
                ss.str(line);

                ss>>temp_input;
                if(temp_input.compare("probability")==0)
                {                        
                    ss>>temp_input;
                    ss>>temp_input;
                    int currentID = (variable_mapping.find(temp_input)->second);
                    out << line << endl;
                    getline (myfile,line);
                    out << "    table ";
                    int i=0;
                    while(i < CPT[currentID].size())
                    {
                        if(CPT[currentID][i]<0.0001)
                            out << "0.0001" << " ";
                        else
                            out << fixed << setprecision(4) << CPT[currentID][i] << " ";
                        i++;
                    }
                    out << ";" << endl;
                }
                else if(line.compare("")!=0)
                    out << line << endl;
                else 
                    out << line;
            }
            
            myfile.close();
    }
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
    // for(int i=0;i<records.size();i++){
    //     for(int j=0;j<records[i].size();j++){
    //         cout<<records[i][j]<<' ';
    //         cout<<endl;
    //     }
    //     cout<<endl;
    // }
    //calculate_priors(Alarm, records);
    cout<<get_prob({"A","B"},{"True","False"},records)<<endl;
    //cout<<Alarm.get_nth_node(1)->get_name()<<endl;
    //cout << Alarm.get_nth_node(0)->get_children().size() << endl;
}
