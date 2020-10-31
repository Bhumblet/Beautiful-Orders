// writing on a text file
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

const int MAX_NUMBER_OF_CUSTOMERS = 30;
const int MAX_NUMBER_OF_ITEM_TYPES = 15;

/* TESTING
  To test your homework_3.cpp file, run: 
  
  ./run_tests.sh 
  
 You may need to first run - if you get a permission denied error: 
 
  chmod a+rwx run_tests.sh 

 When you first test, you will fail all test cases. Modify your code, retest, then modify again. Test driven development!
*/


// THIS IS A UTILITY FUNCTION USED FOR TESTING. DO NOT MODIFY.
void Print_Variables(string names[MAX_NUMBER_OF_CUSTOMERS][2], int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], int *number_of_customers, int *number_of_items, double costs[], double percents[], const string input_filename);

// THESE ARE THE FOUR FUNCTIONS YOU WILL IMPLEMENT.
void Read_Customer_Orders_File(string names[MAX_NUMBER_OF_CUSTOMERS][2], int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], int *number_of_customers, int *number_of_items, const string input_filename);
void Format_Case_Of_Names(string names[MAX_NUMBER_OF_CUSTOMERS][2], const int number_of_customers);
void Compute_Total_Cost_And_Percent(int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], double costs[], double percents[], int number_of_customers, int number_of_items);
void Write_Formatted_Summary(string names[MAX_NUMBER_OF_CUSTOMERS][2],double costs[], double percents[], int number_of_customers, string output_filename);

int main () {
    string customer_orders_filename, formatted_output_filename;
    cin >> customer_orders_filename >> formatted_output_filename;

    int number_of_items=0;
    int number_of_customers=0;
    string names[MAX_NUMBER_OF_CUSTOMERS][2];
    int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES];
    double prices[MAX_NUMBER_OF_ITEM_TYPES] = {0.0};
    double costs[MAX_NUMBER_OF_CUSTOMERS] = {0.0};
    double percents[MAX_NUMBER_OF_CUSTOMERS] = {0.0};

    Read_Customer_Orders_File(names, orders, prices, &number_of_customers, &number_of_items, customer_orders_filename);
    Print_Variables(names, orders, prices, &number_of_customers, &number_of_items, costs, percents, customer_orders_filename);

    Format_Case_Of_Names(names, number_of_customers);
    Print_Variables(names, orders, prices, &number_of_customers, &number_of_items, costs, percents, customer_orders_filename);

    Compute_Total_Cost_And_Percent(orders, prices, costs, percents, number_of_customers, number_of_items);
    Print_Variables(names, orders, prices, &number_of_customers, &number_of_items, costs, percents, customer_orders_filename);

    Write_Formatted_Summary(names, costs, percents, number_of_customers, formatted_output_filename);

    return 0;
}

void Read_Customer_Orders_File(string names[MAX_NUMBER_OF_CUSTOMERS][2], int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], int *number_of_customers, int *number_of_items, const string input_filename) {
    string line;
    ifstream input(input_filename);
    int customerNumber = 0;
    if(input.is_open()){
        while(getline(input,line)){
            if(line.find("number_of_customers") != string::npos){
                *number_of_customers = stoi(line.substr(20));
            }
            else if(line.find("number_of_items") != string::npos){
                *number_of_items = stoi(line.substr(16));
            }
            else if(line.find("customer_id first_name last_name") != string::npos){
                string price = line.substr(33);
                for(int i = 0; i < *number_of_items; i++) {
                    size_t space = price.find(" ");
                    if(space == string::npos){
                        prices[i] = stod(price);
                        break;
                    }
                    prices[i] = stod(price.substr(0,space));
                    price = price.substr(space + 1);
                }
            }
            else{
                line = line.substr(6);
                for(int i = 0; i < *number_of_items + 2; i++){
                    size_t space = line.find(" ");
                    if(i > 1){
                        if(space == string::npos){
                            orders[customerNumber][i-2] = stoi(line);
                            break;
                        }
                        orders[customerNumber][i-2] = stoi(line.substr(0,space));
                        line = line.substr(space + 1);
                    }
                    else {
                        names[customerNumber][i] = line.substr(0, space);
                        line = line.substr(space + 1);
                    }
                }
                customerNumber +=1;
            }
        }
        input.close();
    }
    else cout<<"Unable to open file"<<endl;
}

void Format_Case_Of_Names(string names[MAX_NUMBER_OF_CUSTOMERS][2], const int number_of_customers) {
    for(int i = 0; i < number_of_customers; i++){
        for(int n = 0; n < 2; n++){
            string name = names[i][n];
            string newName;
            for(int j = 0; j < (int) name.length(); j++){
                int ch = int(name.at(j));
                if(j == 0){
                    if(ch < 123 && ch > 96){
                        newName = char(ch - 32);
                    }
                    else{
                        newName = char(ch);
                    }
                }
                else{
                    if(ch < 123 && ch > 96){
                        newName += char(ch);
                    }
                    else{
                        newName += char(ch + 32);
                    }
                }
            }
            names[i][n] = newName;
        }
    }
}

void Compute_Total_Cost_And_Percent(int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], double costs[], double percents[], int number_of_customers, int number_of_items) {
    for(int i = 0; i < number_of_customers; i++){
        double cost = 0;
        for(int n = 0; n < number_of_items; n++){
            cost += (orders[i][n] * prices[n]);
        }
        costs[i] = cost;
    }
    double total = 0;
    for(int i = 0; i < number_of_customers; i++){
        total += double(costs[i]);
    }
    for(int i = 0; i < number_of_customers; i++){
        percents[i] = (double)100 * (costs[i]/total);
    }
}

void Write_Formatted_Summary(string names[MAX_NUMBER_OF_CUSTOMERS][2], double costs[], double percents[], int number_of_customers, string output_filename) {
    ofstream output(output_filename);
    if(output.is_open()){
        for(int i = 0; i < number_of_customers; i++){
           output<<names[i][1]<<", "<<setw(23 - names[i][1].length())<<left<<names[i][0]<<fixed<<setprecision(2)<<setw(15)<<right<<costs[i]<<setprecision(1)<<setw(20)<<percents[i]<<"\n";
        }
        output.close();
    }
}


// THIS IS A UTILITY FUNCTION USED FOR TESTING. DO NOT MODIFY.
void Print_Variables(string names[MAX_NUMBER_OF_CUSTOMERS][2], int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], int *number_of_customers, int *number_of_items, double costs[], double percents[], const string input_filename) {
    cout << "---- Start Test Output ----" << endl;
    cout << *number_of_customers << endl;
    cout << *number_of_items << endl;
    for (int i = 0; i < *number_of_items; ++i) {
        cout << "$" << prices[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < *number_of_customers; ++i) {
        cout << names[i][1] << ", " << names[i][0] << ": ";
        cout << "Orders=[";
        for (int j = 0; j < *number_of_items; ++j) {
            cout << orders[i][j] << ',';
        }
        cout << "], Cost=" << costs[i];
        cout << ", Percent=" << percents[i] << endl;
    }
    cout << "---- End Test Output ----" << endl;
}