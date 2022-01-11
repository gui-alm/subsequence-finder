#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

#define PROBLEM_1 "1"
#define PROBLEM_2 "2"

using namespace std;

/* 
 * Handles the input: adds the given sequence(s) to a vector.
 * Returns an indicator of the problem to solve.
*/
string handle_input(vector<int>& vec1, vector<int>& vec2){
    int num;
    int num2;
    string nProblem;
    string sequence;
    string sequence2;
    unordered_map <int, int> numbers_in_common;

    getline(cin >> ws, nProblem);
    getline(cin >> ws, sequence);

    istringstream ss (sequence);
    while (ss >> num) {
        vec1.push_back(num);
        if(nProblem == PROBLEM_2)
            numbers_in_common[num] = num;
    }

    if(nProblem == PROBLEM_1)
        return nProblem;
    
    getline(cin >> ws, sequence2);
    istringstream ss2 (sequence2);
    while(ss2 >> num2){
        if(numbers_in_common.find(num2) != numbers_in_common.end()){
            vec2.push_back(num2);
        }
    }
    
    return nProblem;
}

void solve_problem1(vector<int>& vec){

    int size = vec.size();
    int max_length = 1;
    int sequence_counter = 1;
    int biggest_in_sequence = vec[0];

    vector<int> table(size, 1);
    vector<int> counter(size, 1);

    for(int j = 1; j < size; j++){
        
        if(vec[j-1] < vec[j] && biggest_in_sequence < vec[j]){
            table[j] = max_length + 1; 
            counter[j] = sequence_counter; 
            biggest_in_sequence = vec[j]; 
            max_length = table[j];
            continue;
        }

        for(int i = 0; i < j; i++){

            if(vec[j] <= vec[i]){
                continue;
            }

            if(table[j] < table[i] + 1){
                table[j] = table[i] + 1;
                counter[j] = counter[i];

                if(max_length < table[j]){
                    sequence_counter = 0;
                    max_length = table[j];
                    biggest_in_sequence = vec[j];
                }

            } else if (table[j] == table[i] + 1){
                counter[j] += counter[i];
            }
        } 
        
        if(table[j] == max_length){
            sequence_counter += counter[j];
        } 
    } 

    printf("%d %d\n", max_length, sequence_counter);
}

void solve_problem2(vector<int>& vec1, vector<int>& vec2) {

    int size1 = vec1.size();
    int size2 = vec2.size();
    int max_length = 0;

    int table[size2]; 

    for(int j = 0; j < size1; j++){
        int length = 0;

        for(int i = 0; i < size2; i++){
            if (j == 0)
                table[i] = 0;

            if (vec1[j] < vec2[i])
                continue;

            else if (vec1[j] == vec2[i] && table[i] <= length){
                table[i] = length + 1;
                if (max_length < table[i])
                    max_length = table[i];
            }
            else if (vec1[j] > vec2[i] && length < table[i])
                length = table[i];
        }
    }

    printf("%d\n", max_length);
}

int main() {
    string nProblem;

    vector <int> vec1;
    vector <int> vec2;

    nProblem = handle_input(vec1, vec2);

    if(nProblem == PROBLEM_1){
        solve_problem1(vec1);
    } else if (nProblem == PROBLEM_2){
        solve_problem2(vec1, vec2);
    }

    return 0;
}