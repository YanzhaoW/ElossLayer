#include <vector>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include <fstream>
using namespace std;
void root2csv(){
    ofstream myfile;
    myfile.open("./out/output.csv", ios::out | ios::trunc);

    auto file = new TFile("./output.root");
    auto tree = (TTree*)file->Get("Edep");
    int bran_nb = tree->GetNbranches();
    int entry_nb = tree->GetEntries();
    auto branches = tree->GetListOfBranches();
    vector<string> branch_names;
    myfile <<"Entry";
    for(int i=0; i < bran_nb; i++){
        myfile << "," << branches->At(i)->GetName();
        cout << branches->At(i)->GetName()<< endl;
        branch_names.push_back(branches->At(i)->GetName());
    }
    myfile << endl;
    
    vector<double> buffer(bran_nb, 0);
    for(int i = 0; i < bran_nb; i++){
       tree -> SetBranchAddress(branch_names[i].c_str(), &buffer[i]);
    }
    
    for(int i =0; i < entry_nb; i++){
        tree->GetEntry(i);
        myfile << i;
        for(int j = 0; j < bran_nb; j++){
            myfile << "," << buffer[j];
        }
        myfile << endl;
    }
    myfile.close();
}
