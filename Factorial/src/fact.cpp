#include <iostream>
#include <cmath>
#include <string>
#include <limits.h>
#include <limits>

// Multiplies k and arr, updates arr and returns the number of digits in updated arr
int mult(int k, int arr[], int num_digits)
{
    int carry, product, i;
    carry = 0;
    i = 0;

    // Long multiplication of k with arr
    for (i = 0; i < num_digits; i++)
    {
        product = k * arr[i] + carry;
        arr[i] = product % 10;
        carry = product / 10;
    }

    // If the carry variable is 0, then we are done. Otherwise, we need
    // to add additional values into the array.
    while (carry != 0) 
    {
        arr[i] = carry % 10;
        carry /= 10;
        i++;
        num_digits++;
    }
    return num_digits;
}

// Divides arr by k, updates arr, and returns the number of significant digits in updated arr
int divide(int k, int arr[], int num_of_digits)
{
    int dividend;
    int i = 0;

    // Finds the smallest index of arr for which arr[0 : i] >= k
    do 
    {
        i++;
        dividend = 0;   // resets dividend if loop repeats
        for (int j = 0; j < i; j++)
        {
            dividend += arr[j] * pow(10, i - j - 1);
        }
    }
    while (dividend <= k);

    // Long division process. j accounts for the indices of the resultant array
    int j = 0;
    while (i <= num_of_digits)
    {
        arr[j] = (dividend / k);

        // Replace dividend by remainder and factor in the next array element to be included in the next iteration
        dividend = (dividend % k) * 10 + arr[i];
        i++;
        j++;
    }
    return j;
}


const int MAX_NUM_OF_DIGITS = 400; // max number of digits in final answer, I chose 400 since 200! has 375 digits.
std::string factorial_array[201]; // std::string array consisting of computed factorials up until 200! Initialised to array of "1"'s before first computation

std::string fact(int n)
{
    if (factorial_array[n] != "1") return factorial_array[n];

    // Finds nearest neighbour in factorial array
    int k_below = 0;
    int k = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        if (factorial_array[i] != "1") k_below = i;
        break;
    }
    for (int i = n + 1; i < std::min(2 * n - k_below, 201); i++)
    {
        if (factorial_array[i] != "1") k = i;
    }

    int arr[MAX_NUM_OF_DIGITS];
    if (k <= n)
    {
        std::string k_fact = factorial_array[k];
        int num_digits = k_fact.size();

        // Load k! into arr in reverse order, - 48 to account for char to int
        for (int i = 0; i < num_digits; i++)
        {
            arr[i] = k_fact[num_digits - i - 1] - 48;
        }

        // Compute factorial using n! = n(n-1)...k!
        for (int i = k + 1; i <= n; i++)
        {
            num_digits = mult(i, arr, num_digits);
        }

        // Convert final array to std::string, obtaining result, and add to factorial_array
        std::string result;
        for (int i = num_digits - 1; i >= 0; i--)
        {
            result += std::to_string(arr[i]);
            factorial_array[n] = result;
        }
        return result;
    }
    else
    {
        std::string k_fact = factorial_array[k];
        int num_digits = k_fact.size();

        // Load k into arr in canonical order, - 48 to account for char to int
        for (int i = 0; i < num_digits; i++)
        {
            arr[i] = k_fact[i] - 48;
        }

        // Compute factorial using n! = k!/(n+1)...(k-1)
        for (int i = n + 1; i <= k; i++)
        {
            num_digits = divide(i, arr, num_digits);
        }

        // Convert final array to std::string, obtaining result, and add to factorial_array
        std::string result;
        for (int i = 0; i < num_digits; i++)
        {
            result += std::to_string(arr[i]);
            factorial_array[n] = result;
        }
        return result;
    }
}

int read_input(std::string prompt, int max)
{
    int input;
    bool valid= false;
    do
    {
        std::cout << prompt << std::flush;
        std::cin >> input;
        if (std::cin.good() && input >= 0 && input <= max)
        {
            valid = true;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Invalid input; please re-enter.\n" << std::endl;
        }
    } 
    while (!valid);
    return input;
}


int main() 
{
    for (int i = 0; i < 201; i++)
    {
        factorial_array[i] = "1";
    }
    
    int T = read_input("How many times do you want to run the factorial function?\n", INT_MAX);
    
    while(T-->0)
    {
        int num = read_input("\nEnter a number you want to compute the factorial of:\n", 200);
        std::cout << "The factorial of " << num << " is:\n" << fact(num) << std::endl;
    }
}