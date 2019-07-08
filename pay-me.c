/*
------------
Pay in Coins
------------

Author: Luka Zoric
*/

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// return index of a value in the array
int indexOf(int val, int *arr, int size) {
	// for every index in range from 0 to size of the array
    for (int i = 0; i<size; i++) {
		// if array[index] is value then return index
        if (arr[i] == val) {
            return i;
        }
    }
	// if no index is returned then return size
    return size;
}

// generate candidates for the subset sum
int generateCandidates(int n, int arr[], int candidates[]) {

	// generate new array with values from 1 to n - for n = 5 -> arr = {1, 2, 3, 4, 5}
    for (int i = 0; i < n; i++) {
        arr[i] = i+1;
    }

	// Sieve of Eratosthenes 
	// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

	// for every number from 2 to n
	for (int i = 2; i < n; i++) {
		// for every number from previous number to n
        for (int number = i+1; number<n; number++) {
			// if that number is a multiple
            if ((number%i) == 0) {
				// take index of it and flag it as 0
                int index = indexOf(number, arr, n);
                arr[index] = 0;
                } 
            }
        }

    int a = 0;

	// boolean that flags if n is already a prime number
    bool in = false;

	// for every element that  isn't 0 in arr[] add it to the candidates array
    for (int i = 0; i <=n; i++) {
        if (arr[i] != 0) {
            candidates[a] = arr[i];
            a++;
        }
		// if n is already prime flag it
        if (arr[i] == n) {
            in = true;
        }
    }
	// if element isn't prime, append it to candidates
    if (in == false) {
        candidates[a] = n;
    }

	// return the size of candidates array
    return a;
}

int combinations(int candidates[], int target, int index, int current[], int current_len, int candidates_len, int *combos, int low_b, int up_b) {
	if (target <= 0) {
		// if target is 0 and current length of combination suits solution, increment combo value
		if ((target == 0) && (current_len >= low_b)) {
			*combos = *combos + 1;
		}
		// backtrack
		return 1;
	}

	// for every value of i in range from 0 to upper bound
	for (int i = 0; i < up_b; i++) {

		// if current length of combination is that value of i
		if (current_len == i) {
			// for every candidate
			if (index < candidates_len) {

				// set value to be the next possible candidate and append it to the current combination
				int value = candidates[index];
				current_len += 1;
				current[current_len] = value;

				// call the combinations function with decresed target
				combinations(candidates, target - value, index, current, current_len, candidates_len, combos, low_b, up_b);

				// 'remove' last element in the combination
				current_len -= 1;
				
				// recall the combinations function now with the index pointing to the next available candidate and repeat
				combinations(candidates, target, index + 1, current, current_len, candidates_len, combos, low_b, up_b);
			}
		}
	}
	return 1;
}

// parse information from the line
void parseLine(char *line, int *parsedLine) {
    int index = 0;
    int temp = 0;
    int pIndex = 0;

	// while end of the line is reached
    while (1) {
		// if new line character, end of line character or space is reached
        if (line[index] == '\n' || line[index] == '\0' || line[index] == ' ') {
			// if space is reached
            if (line[index] == ' ') {
				// devide temporary value at the current index by 10 to get its real value
                parsedLine[pIndex] = temp/10;
				// value at incremented index is now 0
                temp = 0;
				// increment index and current index
                pIndex++;
                index++;
            } else {
				// if any other character is reached '/n' or '/0'
				// get the real value of the value at index
                parsedLine[pIndex] = temp/10;

				// break
                break;
            }
        }

		// compute value of a number by adding current character int value to the temp
        temp += (line[index] - 48);
		// multiply by 10
        temp *= 10;
		// increment index to get next character in a line
        index++;
    }
}

// main function
int main() {

	printf("2801ICT Computer Algorithms - Assignment 1\n\nEnter path to the input file including the file name (eg. C/Desktop/input.txt)\nPath: ");

	// input path of the file
	char input_path[100];
	scanf("%[^\n]%*c", input_path);

	// open files, input file to read from it
    FILE *input_file = fopen(input_path, "r");
	// output file to print output
    FILE *output_file = fopen("output.txt", "w");

	// declare variables
    int line = 1;
    char current_line[20];

	// read every line till end of the file
    while (fgets(current_line, 20, input_file)) {
		// pass parsedLine as a parameter and dirrectly change the 
		int parsedLine[] = { 0, 0, 0 };
		parseLine(current_line, parsedLine);
        
		// from parsed line, declare N, low bound and high bound for the combination problem
        int n = parsedLine[0];
        int low_bound = parsedLine[1];
        int high_bound = parsedLine[2];

		// if low bound is 0, then find all solutions where combinations range from 1 to n so low bound = 1 and high bound = n
        if (low_bound == 0) {
            low_bound = 1;
            high_bound = n;
        }
		// if high bound is 0, the find all solutions in range of parsedLine[1] which is low bound and therefor high bound = low bound
        if (high_bound == 0) {
            high_bound = low_bound;
        }

		// declare array and candidates, by calling 'generateCandidates', value of a will be returned from a call and candidates array will be created
        int array[n];
        int candidates[n];
        int a = generateCandidates(n, array, candidates);


		// new candidates will be created as an array of primes size 'a'
        int new_candidates[a];
        int j = 0;
		int temp;
		// reverse all elements from candidates into new candidates array - optimization
        for (int i = a-1; i>=0; i--) {
			temp = candidates[i];
            new_candidates[j] = temp;
            j++;
        }

		// current is array that represents list of combination of primes whose sum is N
        int current[100];
		// result represents solution to the problem
        int result = 0;
		// record the time
        clock_t start = clock();

		// call the function combinations
		printf("Input: %d %d %d\n", n, low_bound, high_bound);

		combinations(new_candidates, n, 0, current, 0, a, &result, low_bound, high_bound);

		// stop recording the time
        clock_t end = clock();

		// compute time
        double time_spent = (double)(end-start)/CLOCKS_PER_SEC;

		// output result to file
        fprintf(output_file, "%d\n", result);
        
		// go to the next line
		line++;

		printf("Completed in %f seconds. Result: %d\n\n", time_spent, result);
    }

	// close all file pointers
    fclose(output_file);
    fclose(input_file);

	// end of program
    return 0;
}
