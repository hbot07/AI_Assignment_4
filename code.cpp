//
// Created by Parth Thakur on 28/10/23.
//


#include "startup_code.cpp"
using namespace std;

void read_records(const string& filename, int ncols, vector<vector<string> >& records){
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "error: couldn't open file" << filename << endl;
        return;
    }

    cout << "reading " << filename << endl;
    string line;
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
    cout << "done reading" << endl;
}

void calculate_priors(network Alarm, vector<vector<string> > records){
    vector<list<Graph_Node>::iterator> parentless_nodes;

    for(int i=0; i < Alarm.netSize(); i++){
        if(Alarm.get_nth_node(i)->get_Parents().size() == 0){
            parentless_nodes.push_back(Alarm.get_nth_node(i));
        }
    }
    cout << "#parentless nodes: " << parentless_nodes.size() << endl;


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

    calculate_priors(Alarm, records);


}