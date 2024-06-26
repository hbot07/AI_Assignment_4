//
// Created by Parth Thakur on 30/10/23.
//
//
// Created by Parth Thakur on 29/10/23.
//
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <random>
#include <map>
//#include "Format_Checker.cpp"


// Format checker just assumes you have Alarm.bif and Solved_Alarm.bif (your file) in current directory
using namespace std;

// Our graph consists of a list of nodes where each node is represented as follows:
class Graph_Node{

public:
    string Node_Name;  // Variable name
    vector<int> Children; // Children of a particular node - these are index of nodes in graph.
    vector<string> Parents; // Parents of a particular node- note these are names of parents
    int nvalues;  // Number of categories a variable represented by this node can take
    vector<string> values; // Categories of possible values
    vector<float> CPT; // conditional probability table as a 1-d array . Look for BIF format to understand its meaning

public:
    // Constructor- a node is initialised with its name and its categories
    Graph_Node(string name,int n,vector<string> vals)
    {
        Node_Name=name;

        nvalues=n;
        values=vals;


    }
    string get_name()
    {
        return Node_Name;
    }
    vector<int> get_children()
    {
        return Children;
    }
    vector<string> get_Parents()
    {
        return Parents;
    }
    vector<float> get_CPT()
    {
        return CPT;
    }
    int get_nvalues()
    {
        return nvalues;
    }
    vector<string> get_values()
    {
        return values;
    }
    void set_CPT(vector<float> new_CPT)
    {
        CPT.clear();
        CPT=new_CPT;
    }
    void set_Parents(vector<string> Parent_Nodes)
    {
        Parents.clear();
        Parents=Parent_Nodes;
    }
    // add another node in a graph as a child of this node
    int add_child(int new_child_index )
    {
        for(int i=0;i<Children.size();i++)
        {
            if(Children[i]==new_child_index)
                return 0;
        }
        Children.push_back(new_child_index);
        return 1;
    }



};


// The whole network represted as a list of nodes
class network{

    list <Graph_Node> Pres_Graph;

public:
    int addNode(Graph_Node node)
    {
        Pres_Graph.push_back(node);
        return 0;
    }


    int netSize()
    {
        return Pres_Graph.size();
    }
    // get the index of node with a given name
    int get_index(string val_name)
    {
        list<Graph_Node>::iterator listIt;
        int count=0;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            if(listIt->get_name().compare(val_name)==0)
                return count;
            count++;
        }
        return -1;
    }
// get the node at nth index
    list<Graph_Node>::iterator get_nth_node(int n)
    {
        list<Graph_Node>::iterator listIt;
        int count=0;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            if(count==n)
                return listIt;
            count++;
        }
        return listIt;
    }
    //get the iterator of a node with a given name
    list<Graph_Node>::iterator search_node(string val_name)
    {
        list<Graph_Node>::iterator listIt;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            if(listIt->get_name().compare(val_name)==0)
                return listIt;
        }

        cout<<"node not found\n";
        return listIt;
    }


};

network read_network()
{
    network Alarm;
    string line;
    int find=0;
    ifstream myfile("alarm.bif");
    string temp;
    string name;
    vector<string> values;

    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            stringstream ss;
            getline (myfile,line);


            ss.str(line);
            ss>>temp;


            if(temp.compare("variable")==0)
            {

                ss>>name;
                getline (myfile,line);

                stringstream ss2;
                ss2.str(line);
                for(int i=0;i<4;i++)
                {

                    ss2>>temp;


                }
                values.clear();
                while(temp.compare("};")!=0)
                {
                    values.push_back(temp);

                    ss2>>temp;
                }
                Graph_Node new_node(name,values.size(),values);
                int pos=Alarm.addNode(new_node);


            }
            else if(temp.compare("probability")==0)
            {

                ss>>temp;
                ss>>temp;

                list<Graph_Node>::iterator listIt;
                list<Graph_Node>::iterator listIt1;
                listIt=Alarm.search_node(temp);
                int index=Alarm.get_index(temp);
                ss>>temp;
                values.clear();
                while(temp.compare(")")!=0)
                {
                    listIt1=Alarm.search_node(temp);
                    listIt1->add_child(index);
                    values.push_back(temp);

                    ss>>temp;

                }
                listIt->set_Parents(values);
                getline (myfile,line);
                stringstream ss2;

                ss2.str(line);
                ss2>> temp;

                ss2>> temp;

                vector<float> curr_CPT;
                string::size_type sz;
                while(temp.compare(";")!=0)
                {

                    curr_CPT.push_back(atof(temp.c_str()));

                    ss2>>temp;



                }

                listIt->set_CPT(curr_CPT);


            }
            else
            {

            }
        }

        if(find==1)
            myfile.close();
    }

    return Alarm;
}

network read_network(char* filename)
{
    network Alarm;
    string line;
    int find=0;
    ifstream myfile(filename);
    string temp;
    string name;
    vector<string> values;

    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            stringstream ss;
            getline (myfile,line);


            ss.str(line);
            ss>>temp;


            if(temp.compare("variable")==0)
            {

                ss>>name;
                getline (myfile,line);

                stringstream ss2;
                ss2.str(line);
                for(int i=0;i<4;i++)
                {

                    ss2>>temp;


                }
                values.clear();
                while(temp.compare("};")!=0)
                {
                    values.push_back(temp);

                    ss2>>temp;
                }
                Graph_Node new_node(name,values.size(),values);
                int pos=Alarm.addNode(new_node);


            }
            else if(temp.compare("probability")==0)
            {

                ss>>temp;
                ss>>temp;

                list<Graph_Node>::iterator listIt;
                list<Graph_Node>::iterator listIt1;
                listIt=Alarm.search_node(temp);
                int index=Alarm.get_index(temp);
                ss>>temp;
                values.clear();
                while(temp.compare(")")!=0)
                {
                    listIt1=Alarm.search_node(temp);
                    listIt1->add_child(index);
                    values.push_back(temp);

                    ss>>temp;

                }
                listIt->set_Parents(values);
                getline (myfile,line);
                stringstream ss2;

                ss2.str(line);
                ss2>> temp;

                ss2>> temp;

                vector<float> curr_CPT;
                string::size_type sz;
                while(temp.compare(";")!=0)
                {

                    curr_CPT.push_back(atof(temp.c_str()));

                    ss2>>temp;



                }

                listIt->set_CPT(curr_CPT);


            }
            else
            {

            }





        }

        if(find==1)
            myfile.close();
    }

    return Alarm;
}

void read_records(const string& filename, int ncols, vector<vector<string> >& records) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "error: couldn't open file" << filename << endl;
        return;
    }
    cout << "reading " << filename << endl;
    string line;
    while (getline(inputFile, line)) {
        size_t pos = 0;
        string token;
        vector<string> tokens;

        while ((pos = line.find(' ')) != string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }

        tokens.push_back(line);

        if (tokens.size() == ncols) {
            for (int i = 0; i < ncols; i++) {
                records[i].push_back(tokens[i]);
            }
        } else {
            cout << "error: wrong length" << endl;
            return;
        }
    }
    cout << "done reading " << filename << endl;
    cout << "number of records: " << records[0].size() << endl;
}

double get_prob(vector<vector<string> >& records, vector<string>& parent_perm_values, vector<int>& parent_indices, string& node_value, int node_index, vector<double>& records_weights){
    double numerator = 0.0001;
    for(int i=0; i<records[0].size(); i++){
        bool matching = true;
        for(int j=0; j<parent_perm_values.size(); j++){
            if(parent_perm_values[j] != records[parent_indices[j]][i]){
                matching = false;
                break;
            }
        }
        if(node_value == records[node_index][i] && matching){
            numerator += records_weights.at(i);
        }
    }
    double denominator = 0.0001;
    for(int i=0; i<records_weights.size(); i++){
        denominator += records_weights.at(i);
    }
    return numerator/denominator;
}


void cartesianHelper(const std::vector<std::vector<std::string> >& lists, std::vector<std::vector<std::string> >& result, std::vector<std::string>& current, int depth) {
    if (depth == lists.size()) {
        result.push_back(current);
        return;
    }

    for (int i = 0; i < lists[depth].size(); ++i) {
        current.push_back(lists[depth][i]);
        cartesianHelper(lists, result, current, depth + 1);
        current.pop_back();
    }
}

std::vector<std::vector<std::string> > cartesianProduct(const std::vector<std::vector<std::string> >& lists) {
    std::vector<std::vector<std::string> > result;
    std::vector<std::string> current;
    cartesianHelper(lists, result, current, 0);
    return result;
}


map<string, map<vector<string>, int > > cpt_map;
void get_one_CPT2(Graph_Node& node, vector<vector<string> >& records, vector<float>& CPT, network& Alarm, vector<double>& records_weights){
//    cout << "getting CPT for " << node.get_name() << endl;
    vector<string> node_values = node.get_values();
    vector<string> parents = node.get_Parents();

    vector<vector<string> > parents_values;
    for(auto & parent : parents){
        parents_values.push_back(Alarm.search_node(parent)->get_values());
    }

    std::vector<std::vector<std::string> > perms = cartesianProduct(parents_values);

    vector<int> parent_indices;
    for(int i=0; i<parents.size(); i++){
        parent_indices.push_back(Alarm.get_index(parents[i]));
    }
    int node_index = Alarm.get_index(node.get_name());
    int counter = 0;
    for(auto & node_val:node_values){
        for(auto & perm:perms){
            CPT.push_back(get_prob(records, perm, parent_indices, node_val, node_index, records_weights));
            cpt_map[node.get_name() + node_val][perm] = counter;
            counter++;
        }
    }
}

void normalise_CPT(vector<float>& CPT, Graph_Node& node){
    int num_values = node.get_values().size();

    for(int i=0; i<CPT.size()/num_values; i++){
        double sum = 0;
        for(int j=i; j<CPT.size(); j+=CPT.size()/num_values){
            sum += CPT[j];
        }
        for(int j=i; j<CPT.size(); j+=CPT.size()/num_values){
            CPT[j] /= sum;
        }
    }
}

void fill_all_CPT(network& Alarm, vector<vector<string> >& records, vector<double>& records_weights) {
    for(int i=0; i<Alarm.netSize(); i++){
        vector<float> CPT;
        Graph_Node& node = *Alarm.get_nth_node(i);
        get_one_CPT2(node, records, CPT, Alarm, records_weights);

        normalise_CPT(CPT, node);
        node.set_CPT(CPT);
    }
}

void write_bif(network& Alarm) {
    ifstream infile("alarm.bif");
    ofstream outfile("solved_alarm.bif");
    string line;
    while (getline(infile, line)) {
        if (line.find("probability") == 0) {
            string variable_name = line.substr(line.find("\""), line.find("\" ")-line.find(" \""));
            while(line.find("table") == string::npos){
                outfile << line << endl;
                getline(infile, line);
            }
            string new_line = line.substr(line.find("table"), 6);
            vector<float> CPT = Alarm.search_node(variable_name)->get_CPT();
            for(auto & prob:CPT){
                new_line += to_string(prob) + " ";
            }
            new_line += ";";
            outfile << new_line << endl;
        }
        else{
            if(!line.empty())
                outfile << line << endl;
        }
    }
}

double get_prob_for_weights(network& Alarm, vector<string> row, Graph_Node& node, string node_val,
                            int node_idx){
    vector<string> parents = node.get_Parents();
    vector<string> perm;
    for(int i=0; i<parents.size(); i++){
        perm.push_back(row[Alarm.get_index(parents[i])]);
    }
    return node.get_CPT().at(cpt_map.at(node.get_name() + node_val).at(perm));
}

void get_weights(network& Alarm, vector<string> row, Graph_Node& node,
                 vector<string>& node_values, vector<string>& parents, vector<double>& weights,
                 int node_idx){
    vector<string> perm;
    for(int i=0; i<parents.size(); i++){
        perm.push_back(row[Alarm.get_index(parents[i])]);
    }
    vector<int> children = node.get_children();

    vector<double> w;

    for(auto & node_val: node_values){
        row[node_idx] = node_val;
        double p = get_prob_for_weights(Alarm, row, node, node_val, node_idx);
        for(auto & child:children){
            Graph_Node& child_node = *Alarm.get_nth_node(child);
            vector<string> child_node_values = child_node.get_values();
            vector<string> child_parents = child_node.get_Parents();

            p *= get_prob_for_weights(Alarm, row, child_node, row[child], child);
        }
        w.push_back(p);
    }

    double sum = 0;
    for(auto & weight:w){
        sum += weight;
    }
    for(auto & weight:w) {
        weights.push_back(weight / sum);
    }
}

void e_process_row(network& Alarm, vector<string>& row, int node_idx, vector<vector<string> >& new_records, vector<double>& new_records_weights){
    Graph_Node& node = *Alarm.get_nth_node(node_idx);
    vector<string> node_values = node.get_values();
    vector<string> parents = node.get_Parents();

    for(auto & node_value: node_values){
        vector<string> new_row;
        for(int j=0; j<row.size(); j++){
            new_row.push_back(row[j]);
        }
        new_row[node_idx] = node_value;

        for(int j=0; j<row.size(); j++){
            new_records[j].push_back(new_row[j]);
        }
    }
    get_weights(Alarm, row, node, node_values, parents, new_records_weights, node_idx);
}

void expectation_step(network& Alarm, vector<vector<string> > records, vector<vector<string> >& new_records, vector<double> records_weights, vector<double>& new_records_weights){
    for(int i=0; i<records[0].size(); i++){
        vector<string> row;
        for(int j=0; j<records.size(); j++){
            row.push_back(records[j][i]);
        }

        auto it = find(row.begin(), row.end(), "\"?\"");
        if(it == row.end()){
            for(int j=0; j<row.size(); j++){
                new_records[j].push_back(row[j]);
            }
            new_records_weights.push_back(1.0);
        }
        else{
            e_process_row(Alarm, row, distance(row.begin(), it), new_records, new_records_weights);
        }
    }
}
network Alarm2=read_network((char*)"gold_alarm.bif");
void expectation_maximisation(network& Alarm, vector<vector<string> >& records, vector<double>& records_weights){
    int num_iterations = 0;
    double last_score = 0;
    while(true){
        network Alarm1;
        Alarm1 = Alarm;
        float score=0;
        for(int i=0;i<Alarm1.netSize();i++)
        {
            list<Graph_Node>::iterator listIt1=Alarm1.get_nth_node(i);
            list<Graph_Node>::iterator listIt2=Alarm2.get_nth_node(i);
            vector<float> cpt1=listIt1->get_CPT();
            vector<float> cpt2=listIt2->get_CPT();
            for(int j=0;j<cpt1.size();j++)
                score+=fabs(cpt1[j]-cpt2[j]);
        }
        cout <<"Score is "<<score << endl;

        num_iterations++;
        cout << "iteration " << num_iterations << endl;

        vector<vector<string> > new_records;
        for(int j=0; j<records.size(); j++){
            vector<string> temp;
            new_records.push_back(temp);
        }
        vector<double> new_records_weights;

        cout << "expectation step" << endl;
        expectation_step(Alarm, records, new_records, records_weights, new_records_weights);

        cout << "maximisation step" << endl;
        fill_all_CPT(Alarm, new_records, new_records_weights);

        write_bif(Alarm);

        if(abs(score - last_score) < 0.001){
            break;
        }
        else{
            last_score = score;
        }
    }
}

int main(){
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    network Alarm;
    Alarm=read_network();

    vector<vector<string> > records(37);
    read_records("records.dat", 37, records);

    vector<double> records_weights;
    for(int i=0; i<records[0].size(); i++){
        records_weights.push_back(1);
    }

    fill_all_CPT(Alarm, records, records_weights);

    write_bif(Alarm);
    expectation_maximisation(Alarm, records, records_weights);

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time taken = " << chrono::duration_cast<chrono::seconds>(end - begin).count() << " s" << endl;
}