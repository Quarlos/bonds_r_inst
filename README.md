# bonds_r_inst
Bond price given instantaneous interest rate curve

When the instantaneous interest rate curve r(t) is given explicitly (defined below in r_inst), 
this program computes the price of the corresponding bond. The user inputs the cash flow dates, 
and the cash flows corresponding to the respective dates. 
The computation includes an integration (via Simpson's rule) and, accordingly, the user should set the tolerance.
