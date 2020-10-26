#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <limits>
#include <utility> // pair
#include <tuple>
#include <algorithm>
#include <iterator>     // std::distance
#include <list>         // std::list

#define MINUS_INT_MAX INT_MAX * (-1)

class Solution {
public:
    int myAtoi(std::string s) {
        int output = 0;
        int start_idx = 0;
        int sign = 1;
        int result = 0;

        // Ignore the whitespace and get the start index
        for(int i = 0; i < s.length() ; i++) {
            if(s[i] == ' ')
                start_idx++; // The first non-whitespace character
            else
                break;
        }

        // Find the sign (What's the definition of existing 2 signs in the string? ignore it?)
        if(start_idx < s.length() && (s[start_idx] == '-' || s[start_idx] == '+')){
            sign = s[start_idx] == '-' ? -1 : 1;
            start_idx++;
        }

        // Get the result
        for(int i = start_idx ; i < s.length() ; i++) {
            if(s[i] >= '0' && s[i] <= '9') { // ASCII, ignore other words, only accept the numbers 0~9
                if (result >= INT_MAX / 10 || (result == INT_MAX / 10 && s[i] - '0' > INT_MAX % 10)) {
                    // if s[i-1] == INT_MAX / 10: −214748364,
                    // in this round, s[i] should <= 7 bcuz INT_MAX == −2147483648
                    // the minimum output could be −2147483647

                    // due to we need to * 10 in each round, if result > INT_MAX / 10, then result * 10 might not be accepted.
                    return (sign == 1) ? INT_MAX : INT_MIN;
                } else {
                    // shift the previous result to the left for the each step
                    // ex: input: 2580
                    // i == 0, res = 2
                    // i == 1, res = 2*10 + 5 = 25
                    result = result * 10 + (s[i] - '0');
                }
            } else if(s[i] == '-' || s[i] == '+') {
                // sign appears again
                return 0;
            } else if(!(s[i] >= '0' && s[i] <= '9')) {
                // if the char is not a digit, stop
                break;
            }
        }
        return result * sign;
    }
};

int main(int argc, char *argv[]) {
    Solution *s = new Solution();
    printf("output:%d\n", s -> myAtoi("  123 yo 456789"));
}
