//
//  main.cpp
//  bonds_r_inst
//  When the instantaneous interest rate curve r(t) is given explicitly (defined below in r_inst), this program computes the price of the corresponding bond. The user inputs the cash flow dates, and the cash flows corresponding to the respective dates. The computation includes an integration (via Simpson's rule) and, accordingly, the user should set the tolerance.
//  The vector of dates and cash flows should be introduced separated by a space with return at the end with no space
//  Reference: Stefanica, Primer for the Math of Fin Eng, Section 2.8
//
//  Created by carlos on 21/11/2018.
//  Copyright © 2018 carlos. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#include <iomanip> // to use setprecision() so that std output gives me more decimal places


// For different integrands EDIT HERE
double r_inst(double t) {
    double r_t = 0.0525+1/(100*(1+exp(-t*t)));
    return r_t;
}

// Simpson's integration rule
double I_numericalSS(double a, double b, int n){
    double h = (b-a)/n;
    double I_simpson=r_inst(a)/6+r_inst(b)/6;
    for(unsigned long i=1; i < n; i++) {
        I_simpson += r_inst(a+i*h)/3;
    }
    for(unsigned long i=1; i < n+1; i++) {
        I_simpson += 2*r_inst(a+h*(i-0.5))/3;
    }
    return h*I_simpson;
}


double I_numericalS(double a, double b, double tol) {
    double I_old, I_new;
    int n=4;

    I_old = I_numericalSS(a, b, n);
    I_new = I_numericalSS(a, b, 2*n);

    while(abs(I_new-I_old) > tol){
        I_old = I_new;
        n = 2*n;
        I_new = I_numericalS(a, b, 2*n);
    }
    return I_new;
}



int main() {
    
    vector <double> t_cash_flow, v_cash_flow;
    double t, v;
    cout << "vector of cash flow dates: ";
    
    cin >> t;
    t_cash_flow.push_back(t);
    while(cin.get() != '\n') {
        cin >> t;
        t_cash_flow.push_back(t);
    }
    
    cout << "vector of cash flows: ";
    cin >> v;
    v_cash_flow.push_back(v);
    while(cin.get() != '\n') {
        cin >> v;
        v_cash_flow.push_back(v);
    }
    
    
    double tol;
    cout << "Tolerance: " << endl;
    cin >> tol;
    
    

    double B=0;
    vector <double> I_numerical(t_cash_flow.size());
    vector <double> disc(t_cash_flow.size());
    for(unsigned long i=0; i < t_cash_flow.size(); i++) {
        I_numerical.at(i)=I_numericalS(0,t_cash_flow.at(i), tol);
        disc.at(i)=exp(-I_numerical.at(i));
        B += v_cash_flow.at(i)*disc.at(i);
    }
    
    cout << "\nprice of the bond B = " << setprecision (8) << B << endl;
    
    return 0;
}
