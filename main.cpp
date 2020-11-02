#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

const int MAX_NUMBER_OF_CUSTOMERS = 30;
const int MAX_NUMBER_OF_ITEM_TYPES = 15;

void Print_Variables(string names[MAX_NUMBER_OF_CUSTOMERS][2], int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], int *number_of_customers, int *number_of_items, double costs[], double percents[], const string input_filename);
void Read_Customer_Orders_File(string names[MAX_NUMBER_OF_CUSTOMERS][2], int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], int *number_of_customers, int *number_of_items, const string input_filename);
void Format_Case_Of_Names(string names[MAX_NUMBER_OF_CUSTOMERS][2], const int number_of_customers);
void Compute_Total_Cost_And_Percent(int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], double costs[], double percents[], int number_of_customers, int number_of_items);
void Write_Formatted_Summary(string names[MAX_NUMBER_OF_CUSTOMERS][2],double costs[], double percents[], int number_of_customers, string output_filename);

/**
 * Main method for Beautiful orders
 *
 * Reads in customer orders and formats them in a nice output file
 */
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

/**
 * This method reads and distributes data from a text file in c++ data structures
 *
 * @param names string array for customer names
 * @param orders integer array for order amounts
 * @param prices double array for prices of each item
 * @param number_of_customers integer for number of customers in order file
 * @param number_of_items  integer for total items being sold
 * @param input_filename  string of filename give through user input
 */
void Read_Customer_Orders_File(string names[MAX_NUMBER_OF_CUSTOMERS][2], int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], int *number_of_customers, int *number_of_items, const string input_filename) {
    string line;
    ifstream input(input_filename);
    int customerNumber = 0;
    if(input.is_open()){
        while(getline(input,line)){ // while text file has another line
            if(line.find("number_of_customers") != string::npos){ // if the line contains "number_of_customers"
                *number_of_customers = stoi(line.substr(20)); // convert substring to integer
            }
            else if(line.find("number_of_items") != string::npos){ // if the line contains "number_of_items"
                *number_of_items = stoi(line.substr(16)); // convert substring to integer
            }
            else if(line.find("customer_id first_name last_name") != string::npos){  // if the line contains table headers
                string price = line.substr(33); // substring containing all prices
                for(int i = 0; i < *number_of_items; i++) {
                    size_t space = price.find(" "); // searches for ' ' character
                    if(space == string::npos){ // if space isn't found
                        prices[i] = stod(price); // add current price to price array
                        break;
                    }
                    prices[i] = stod(price.substr(0,space)); // add price from start of string until space
                    price = price.substr(space + 1); // changes the string to start with the next price
                }
            }
            else{ // if no key words are found
                line = line.substr(6); // skip 5 digit customer id start at name
                for(int i = 0; i < *number_of_items + 2; i++){ // loops through each separate data piece in current line
                    size_t space = line.find(" ");
                    if(i > 1){ // if current loop retains to the order numbers
                        if(space == string::npos){
                            orders[customerNumber][i-2] = stoi(line);
                            break;
                        }
                        orders[customerNumber][i-2] = stoi(line.substr(0,space));
                        line = line.substr(space + 1); // changes the string to start after the next space
                    }
                    else { // if current loop retains to the name of customer
                        names[customerNumber][i] = line.substr(0, space);
                        line = line.substr(space + 1); // changes the string to start after the next space
                    }
                }
                customerNumber +=1;
            }
        }
        input.close();
    }
    else cout<<"Unable to open file"<<endl;
}

/**
 * Changes names to proper format "John Doe"
 *
 * @param names string array containing customer names
 * @param number_of_customers integer containing total number of customers
 */
void Format_Case_Of_Names(string names[MAX_NUMBER_OF_CUSTOMERS][2], const int number_of_customers) {
    for(int i = 0; i < number_of_customers; i++){ // for each customer
        for(int n = 0; n < 2; n++){ // loop through first and last name
            string name = names[i][n];
            string newName;
            for(int j = 0; j < (int) name.length(); j++){ // loop through each letter of name
                int ch = int(name.at(j));
                if(j == 0){ // if current letter is the first letter in name
                    if(ch < 123 && ch > 96){ // if current letter is lowercase
                        newName = char(ch - 32);
                    }
                    else{ // current letter is uppercase
                        newName = char(ch);
                    }
                }
                else{ // if current letter is after first letter
                    if(ch < 123 && ch > 96){ // if current letter is lowercase
                        newName += char(ch);
                    }
                    else{ // current letter is uppercase
                        newName += char(ch + 32);
                    }
                }
            }
            names[i][n] = newName;
        }
    }
}

/**
 * Calculates cost for each customer and the percentage of their order compared to all orders
 *
 * @param orders integer array containing order information
 * @param prices double array containing prices for each item
 * @param costs double array containing costs for each customer
 * @param percents double array containing percent totals for each customer
 * @param number_of_customers integer containing total amount of customers
 * @param number_of_items integer containing number of items available
 */
void Compute_Total_Cost_And_Percent(int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], double costs[], double percents[], int number_of_customers, int number_of_items) {
    for(int i = 0; i < number_of_customers; i++){ // loops through each customer
        double cost = 0;
        for(int n = 0; n < number_of_items; n++){ // loops through item data pertaining to current customer
            cost += (orders[i][n] * prices[n]);
        }
        costs[i] = cost;
    }
    double total = 0;
    for(int i = 0; i < number_of_customers; i++){ // calculates total revenue from customers
        total += double(costs[i]);
    }
    for(int i = 0; i < number_of_customers; i++){ // calculates percentages for each customer
        percents[i] = (double)100 * (costs[i]/total);
    }
}

/**
 * Creates and/or formats output file
 *
 * @param names integer array containing order information
 * @param costs double array containing costs for each customer
 * @param percents double array containing percent totals for each customer
 * @param number_of_customers integer containing total number of customers
 * @param output_filename string output file name
 */
void Write_Formatted_Summary(string names[MAX_NUMBER_OF_CUSTOMERS][2], double costs[], double percents[], int number_of_customers, string output_filename) {
    ofstream output(output_filename);
    if(output.is_open()){
        for(int i = 0; i < number_of_customers; i++){ // for each customer output formatted name and data to file
           output<<names[i][1]<<", "<<setw(23 - names[i][1].length())<<left<<names[i][0]<<fixed<<setprecision(2)<<setw(15)<<right<<costs[i]<<setprecision(1)<<setw(20)<<percents[i]<<"\n";
        }
        output.close();
    }
    else cout<<"Unable to write file"<<endl;
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