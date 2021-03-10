# Factorial

# Implementation of factorial function for large numbers

This implementation utilises a caching mechanism to store values of computed factorials in order to reduce the amount of computations. The approach considered is to store computed values of the factorial in a "book-keeping" array - each call to the factorial function then looks to find the closest neighbour for which the factorial has been computed. The resulting value is the utilised in the calculation which follows; either from successive multiplications or successive divisions, the result is obtained.

# Remarks
Long multiplication<br>The general idea is to mimic the naive approach one considers when doing long multiplication in primary school - doing multiplication “back to front” and “carrying” numbers when the resulting product is greater than 9. The former is incorporated in code by populating our array in reverse order, whilst the latter is incorporated in a variable. 

Long division<br>The approach here mimics how one does long divisionin primary school - iterating through the digits of the original dividend and suitably updating the new dividendat  each  step. However,  unlike the implementation of multiplication, the array is passed in canonical order (for example the number 123 would be represented as the array [1, 2, 3]). This is due to long division being a process which happens from “left to right”.

# How to launch
1. Navigate in terminal to directory containing file. Type the following:<br>
  (i) g++ fact.cpp -o fact<br>
  (ii) ./fact
