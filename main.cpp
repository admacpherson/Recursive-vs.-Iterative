/*
 * Original function code sourced from Dr. Carlos Arias - Recursive vs. Iterative HW Assignment
 * Use of chrono library derived from https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
 *
 * By: Andrew Macpherson
 * 1/16/2023
 * */

#include <iostream>
#include <chrono>   //Used to measure runtimes
#include <fstream>  //Used to output file
using namespace std::chrono;

double iterativePower(double base, int exponent){
    double retVal = 1.0;
    if (exponent < 0){
        return 1.0 / iterativePower(base, -exponent);
    }else{
        for (int i=0; i<exponent; i++)
            retVal *= base;
    }
    return retVal;
}

double recursivePower(double base, int exponent){
    if (exponent < 0){
        return 1.0 / recursivePower(base, -exponent);
    }else if (exponent == 0){
        return 1.0;
    }else {
        return base * recursivePower(base, exponent - 1);
    }
}


int main() {
    double base = 3.14159265359;
    //Maximum value of n
    int max = 165000;

    std::ofstream data;
    data.open("data.csv");

    //CSV Headers
    data << "n," << "Iterative Runtime (ms)," << "Recursive Runtime (ms)\n";


    //Measures n as many times as possible starting at 1
    for (int n = 1; n < max+1; n++) {
        //Measures runtime of iterativePower function
        auto start = high_resolution_clock::now();
        iterativePower(base, n);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        //Saves data to CSV
        data << n << "," << duration.count();
        //std::cout << "n: " << n << "\tIterative: " << duration.count() << " ms\t";    //Output statement

        //Measures runtime of recursivePower function
        start = high_resolution_clock::now();
        recursivePower(base, n);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        //Saves data to CSV
        data << "," << duration.count() << std::endl;
        //std::cout << "Recursive: " << duration.count() << " ms\n";                    //Output statement


    }

    data.close();

    return 0;
}