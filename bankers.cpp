# include <iostream>
# include <vector>


using namespace std;


int main(){
    int processes, resources; 
    cout << "Enter number of processes and number of resources" << endl;
    cin >> processes >> resources;
    int max_matrix[processes][resources];
    int allocation_matrix[processes][resources];
    int need_matrix[processes][resources];
    int available[resources];
	bool finished[processes];
	vector<int> safe_sequence;
    cout << "Enter allocation_matrix" << endl;
    for(int i = 0; i < processes; i++)
	for(int j = 0; j < resources; j++)
		cin >> allocation_matrix[i][j];
    cout << "Enter max max_matrix" << endl;
    for(int i = 0; i < processes; i++)
	for(int j = 0; j < resources; j++)
      		cin >> max_matrix[i][j];
    cout << "Enter available matrix" << endl;
    for(int i = 0; i < resources; i++)
	cin >> available[i];
   cout << "Need matrix"  << endl;
    for(int i = 0; i < processes; i++){
	for(int j = 0; j < resources; j++){
        	need_matrix[i][j] = max_matrix[i][j] - allocation_matrix[i][j];
		cout << need_matrix[i][j] << " ";
	}
    	cout << endl;
    }
    for(int i = 0; i < processes; i++)
	finished[i] = false;
    int process_finished = 0;
    int i = 0; 
    while(process_finished < processes){
	int another_flag = 0;
	for(int j = 0; j < processes; j++){
		int flag = 0;
        	for(int k = 0; k < resources; k++){
	   	    if(need_matrix[j][k] > available[k])
			flag = 1;
		}
		if(flag==0){
			another_flag = 1;break;}
				
	}
	if(another_flag == 0){ cout << "No safe sequence" << endl; return 0; }
	if(finished[i] == true){
	    i++;
	    continue;}
	int flag = 0;
	for(int j = 0; j < resources; j++){
		if(need_matrix[i][j] > available[j]){
	    	    flag = 1;
		    break;	
		}
        }
	if(flag == 0){
	    finished[i] = true;
	    process_finished++;
	    for(int j = 0; j < resources; j++)
		available[j] += allocation_matrix[i][j];
	    safe_sequence.push_back(i);
	}
	i = (i + 1) % processes;
	}
	cout << "The safe sequence is as follows ";
	for(vector<int>::iterator it = safe_sequence.begin(); it != safe_sequence.end(); it++)
		cout << *it << " ";
	cout << endl;

}




























































