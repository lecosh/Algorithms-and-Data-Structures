#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:209715200")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EQUAL 1
#define UNEQUAL 0
#define CORRECT_STRING 1
#define INCORRECT_STRING 0

#define MAX(a, b) (a > b ? a : b)

#define MAX_SIZE 100000
#define MAX_NUMBER_SIZE 2501

char* get_string_array(const int size) {
	char* arr = (char*)malloc(sizeof(char) * size);
	if (arr != NULL) {
		memset(arr, '\0', sizeof(char) * size);
		return arr;
	}
	else {
		printf("Memory fail");
	}
}

char* get_static_string_array_number() {
	char arr[MAX_NUMBER_SIZE];
	memset(arr, '\0', sizeof(char) * MAX_NUMBER_SIZE);
	return arr;
}

int* get_int_array(const int size) {
	int* arr = (int*)malloc(sizeof(int) * size);
	if (arr != NULL) {
		memset(arr, 0, sizeof(int) * size);
		return arr;
	}
}

char* substr(char* str, int offset) {
	int output_size = strlen(str) - offset + 1;
	char* output = get_string_array(output_size);
	strncpy(output, &str[offset], strlen(str) - offset);
	return output;
}

int custom_atoi(const char c) {
	if (!isdigit(c)) {
		return INCORRECT_STRING;
	}
	char str[2];
	memset(str, '\0', sizeof(char) * 2);
	str[0] = c;
	int n = atoi(str);
	return n;
}

char* _reverse(char* arr) {
	int size = strlen(arr) + 2;
	char* reversed = get_string_array(size);
	strcpy(reversed, arr);
	char temp = ' ';
	for (int i = 0; i < strlen(reversed) / 2; i++) {
		temp = reversed[i];
		reversed[i] = reversed[strlen(reversed) - i - 1];
		reversed[strlen(reversed) - i - 1] = temp;
	}
	return reversed;
}

char* simple_multiple(char* arr1, char* arr2) {
	int len = MAX(strlen(arr1), strlen(arr2)) * 2 + 1;
	char* result = get_string_array(len);
	char* a = NULL;
	char* b = NULL;
	if (arr1[0] == '0' || arr2[0] == '0') {
		char* zero = get_string_array(2);
		zero[0] = '0';
		return zero;
	}
	a = _reverse(arr1);
	b = _reverse(arr2);
	int* buffer = get_int_array(strlen(a) + strlen(b) + 1);
	int i = 0, j = 0;
	for (i = 0; i < strlen(a); i++) {
		int carry = 0;
		for (j = 0; j < strlen(b); j++) {
			int cur = buffer[i + j] + custom_atoi(a[i]) * custom_atoi(b[j]) + carry;
			buffer[i + j] = cur % 10;
			carry = cur / 10;
			_itoa(cur % 10, &(result[i + j]), 10);
		}
		if (carry > 0) {
			buffer[i + j] = carry;
			_itoa(carry, &result[i + j], 10);
		}
	}
	free(buffer);
	free(a);
	free(b);
	result = _reverse(result);
	return result;
}

char* difference_for_pow(char* arr1, char* arr2) {
	int size = strlen(arr1) + 1;
	char* result = get_string_array(size);
	char* a = NULL;
	a = _reverse(arr1);
	char* b = arr2;
	unsigned short int c = 0;
	for (int i = 0; i < strlen(a); i++) {
		c = c + custom_atoi(a[i]) - custom_atoi(b[i]) + 10;
		_itoa(c % 10, &result[i], 10);
		if (c < 10) {
			c = -1;
		}
		else {
			c = 0;
		}
	}
	result = _reverse(result);
	int offset = 0;
	for (int i = 0; i < strlen(result); i++) {
		if (result[i] == '0') {
			offset++;
		}
		else {
			break;
		}
	}
	free(a);
	result = substr(result, offset);
	if (result[0] == '0') {
		char* zero = get_string_array(2);
		zero[0] = '0';
		return zero;
	}
	return result;
}

char* power(char* base, char* degree) {
	int size = strlen(base) + 1;
	char* result = get_string_array(size);
	strcpy(result, base);
	if (base[0] == '1' && strlen(base) == 1) {
		char* a = get_string_array(2);
		a[0] = '1';
		return a;
	}
	degree = difference_for_pow(degree, "1");
	while (strlen(degree) != 0) {
		int new_size = strlen(simple_multiple(result, base));
		if (new_size > strlen(result)) {
			result = (char*)realloc(result, sizeof(char) * new_size);
			memset(&result[size], '\0', sizeof(char) * (new_size - size));
			size = new_size;
		}
		result = simple_multiple(result, base);
		degree = difference_for_pow(degree, "1");
	}
	return result;
}

char* fac(char* number) {
	if (strlen(number) == 1 && number[0] == '0'){
		char* zero = get_string_array(2);
		zero[0] = '1';
		return zero;
	}
	int size = strlen(number);
	char* result = number;
	char* next_number = difference_for_pow(result, "1");
	while (strlen(next_number) != 0) {
		result = simple_multiple(result, next_number);
		next_number = difference_for_pow(next_number, "1");
	}
	return result;
}

char* sum(char* arr1, char* arr2) {
	if (arr1[0] == '0' && arr2[0] != '0') {
		char* buffer = get_string_array(strlen(arr2) + 1);
		strcpy(buffer, arr2);
		return buffer;
	}
	if (arr2[0] == '0' && arr1[0] != '0') {
		char* buffer = get_string_array(strlen(arr1) + 1);
		strcpy(buffer, arr1);
		return arr1;
	}
	else if (arr2[0] == '0' && arr1[0] == '0') {
		char* zero = get_string_array(2);
		zero[0] = '0';
		return zero;
	}
	int len = MAX(strlen(arr1), strlen(arr2)) + 2;
	char* result = get_string_array(len);
	char* a = get_string_array(len);
	char* b = get_string_array(len);
	arr1 = _reverse(arr1);
	arr2 = _reverse(arr2);
	strcpy(a, arr1);
	strcpy(b, arr2);
	free(arr1);
	free(arr2);
	unsigned short int c = 0;
	for (int i = 0; i < MAX(strlen(a), strlen(b)); i++) {
		c = c + custom_atoi(a[i]) + custom_atoi(b[i]);
		_itoa(c % 10, &result[i], 10);
		c = c / 10;
	}
	if (c > 0) {
		result[MAX(strlen(a), strlen(b))] = '1';
	}
	result = _reverse(result);
	free(a);
	free(b);
	return result;
}

char* difference(char* arr1, char* arr2, int flag) {
	int len = MAX(strlen(arr1), strlen(arr2)) + 3;
	char* result = get_string_array(len);
	char* a = get_string_array(len + 1);
	char* b = get_string_array(len + 1);
	arr1 = _reverse(arr1);
	arr2 = _reverse(arr2);
	strcpy(a, arr1);
	strcpy(b, arr2);
	unsigned short int c = 0;
	for (int i = 0; i < MAX(strlen(a), strlen(b)); i++) {
		c = c + custom_atoi(a[i]) - custom_atoi(b[i]) + 10;
		_itoa(c % 10, &result[i], 10);
		if (c < 10) {
			c = -1;
		}
		else {
			c = 0;
		}
	}
	if (flag > 0) {
		result = _reverse(result);
		int offset = 0;
		for (int i = 0; i < strlen(result); i++) {
			if (result[i] == '0') {
				offset++;
			}
			else {
				break;
			}
		}
		result = substr(result, offset);
		result = _reverse(result);
		result[strlen(result)] = '-';
		result = _reverse(result);
	}
	else {
		result = _reverse(result);
		int offset = 0;
		for (int i = 0; i < strlen(result); i++) {
			if (result[i] == '0') {
				offset++;
			}
			else {
				break;
			}
		}
		result = substr(result, offset);
	}
	return result;
}

char* compare(char* a, char* b) {
	if (strlen(a) > strlen(b)) {
		return difference(a, b, 0);
	}
	else if (strlen(a) < strlen(b)) {
		return difference(b, a, 1);
	}
	else {
		for (int i = 0; i < MAX(strlen(a), strlen(b)); i++) {
			if (a[i] > b[i]) {
				return difference(a, b, 0);

			}
			else if (a[i] < b[i]) {
				return difference(b, a, 1);
			}
		}
		char* zero = get_string_array(2);
		zero[0] = '0';
		return zero;
	}
}

int compare_for_two(char* a, char* b) {
	if (strlen(a) == strlen(b)) {
		for (int i = 0; i < strlen(a); i++) {
			if (a[i] != b[i]) {
				return UNEQUAL;
			}
		}
		return EQUAL;
	}
	else {
		return UNEQUAL;
	}
}

void from_to_both_minus(char* a, char* b) {
	char* number2 = a;
	char* buffer = get_string_array(strlen(a) + 1);
	strcpy(buffer, a);
	while (!compare_for_two(number2, b)) {
		char* result = get_string_array(strlen(a) + 1);
		number2 = difference_for_pow(number2, "1");
		int new_size = strlen(sum(buffer, number2));
		result = (char*)realloc(result, sizeof(char) * (new_size + 1));
		memset(result, '\0', sizeof(char) * strlen(result));
		buffer = (char*)realloc(buffer, sizeof(char) * (new_size + 1));
		memset(&buffer[strlen(buffer)], '\0', sizeof(char) * new_size - strlen(buffer));
		buffer = sum(buffer, number2);

	}
	printf("-%s", buffer);
}

void from_to_one_minus(char* a, char* b) {
	char* number2 = a;
	char* buffer = get_string_array(strlen(a) + 1);
	char* buffer1 = get_string_array(strlen(a) + 1);
	strcpy(buffer, a);
	while (strlen(number2) != 0) {
		number2 = difference_for_pow(number2, "1");
		int new_size = strlen(sum(buffer, number2));
		buffer = (char*)realloc(buffer, sizeof(char) * (new_size + 1));
		memset(&buffer[strlen(buffer)], '\0', sizeof(char) * new_size - strlen(buffer));
		buffer = sum(buffer, number2);
	}

	number2 = "0";
	while (!compare_for_two(number2, b)) {
		number2 = sum(number2, "1");
		int new_size = strlen(sum(buffer, number2));
		buffer1 = (char*)realloc(buffer1, sizeof(char) * (new_size + 1));
		memset(&buffer1[strlen(buffer)], '\0', sizeof(char) * new_size - strlen(buffer));
		buffer1 = sum(buffer1, number2);

	}

	printf("%s", compare(buffer1, buffer));
}

int check_for_two_minus(char* a, char* b) {
	if (strlen(a) > strlen(b)) {
		return 1;
	}
	if (strlen(a) == strlen(b)) {
		for (int i = 0; i < strlen(a); i++) {
			if (a[i] < b[i]) {
				return 0;
			}
		}
	}
	return 1;
}

int check_for_two_positive(char* a, char* b) {
	if (strlen(a) < strlen(b)) {
		return 1;
	}
	if (strlen(a) == strlen(b)) {
		for (int i = 0; i < strlen(a); i++) {
			if (a[i] > b[i]) {
				return 0;
			}
		}
	}
	return 1;
}

char* from_to(char* input) {
	char a[2501];
	memset(a, '\0', 2501);
	char b[2501];
	memset(b, '\0', 2501);

	int flag = 0;
	if (input[0] == '-') {
		int flag = 1;
		int i = 1;
		while (isdigit(input[i])) {
			a[i - 1] = input[i];
			i++;
		}
		i++;
		if (input[i] == '-') {
			i++;
			flag = 2;
		}
		int j = 0;
		while (isdigit(input[i])) {
			b[j] = input[i];
			i++;
			j++;
		}

		char* zero = compare(a, b);
		if (zero[0] == '0') {
			printf("%c", '0');
		}
		else {
			if (flag == 2) {
				if (check_for_two_minus(a, b)) {
					from_to_both_minus(a, b);
				}
			}
			else {
				from_to_one_minus(a, b);
			}
		}

	}
	else {
		if (!check_for_two_positive(a, b)) {
			return "";
		}
		int i = 0;
		while (isdigit(input[i])) {
			a[i] = input[i];
			i++;
		}
		i++;
		int j = 0;
		while (isdigit(input[i])) {
			b[j] = input[i];
			i++;
			j++;
		}
		char* result = get_string_array(strlen(a) + 1);
		strcpy(result, a);
		char* number2 = a;

		char* buffer = get_string_array(strlen(a) + 1);
		strcpy(buffer, a);
		while (!compare_for_two(number2, b)) {
			number2 = sum(number2, "1");
			int new_size = strlen(sum(buffer, number2));
			result = (char*)realloc(result, sizeof(char) * (new_size + 1));
			memset(result, '\0', sizeof(char) * strlen(result));
			buffer = sum(buffer, number2);

		}
		printf("%s", buffer);
	}
}


void parse_input(char* input) {
	int size = strlen(input);
	char result[MAX_SIZE];
	memset(result, '\0', MAX_SIZE);
	strcpy(result, input);
	int _from_to = 0;
	


	for (int i = 0; i < size; i++) {
		if (result[i] == '!') {
			char number[MAX_NUMBER_SIZE];
			memset(number, '\0', sizeof(char) * MAX_NUMBER_SIZE);
			int j = i - 1, c = 0, start = 0, fac_size = 0;;
			while (j >= 0 && isdigit(result[j])) {
				number[c] = result[j];
				j--;
				c++;
			}
			start = j + 1;
			fac_size = j - start;
			if (j == 0 && result[j] == '-') {
				return 0;
			}
			char* result_fac = fac(_reverse(number));
			int result_fac_size = strlen(result_fac);

			char* buffer = get_string_array(start + result_fac_size + strlen(result) - i + 1);

			for (int k = 0; k < start; k++) {
				buffer[k] = result[k];
			}

			memmove(&buffer[start], result_fac, result_fac_size);
			free(result_fac);
			for (int k = i + 1; k < strlen(result); k++) {
				buffer[strlen(buffer)] = result[k];
			}
			memset(result, '\0', strlen(result));
			strcpy(result, buffer);
			
			memset(buffer, '\0', strlen(buffer));
			free(buffer);
			size = strlen(result);
			i = 0;
		}
	}

	for (int i = 0; i < size; i++) {
		if (result[i] == '^') {
			int base_size_min = 2, degree_size_min = 2;
			/*char* base = get_static_string_array_number();
			char* degree = get_static_string_array_number();*/
			char base[MAX_NUMBER_SIZE];
			char degree[MAX_NUMBER_SIZE];
			memset(base, '\0', MAX_NUMBER_SIZE);
			memset(degree, '\0', MAX_NUMBER_SIZE);
			int j = i - 1, c = 0, start = 0, degree_size = 0;
			while (j >= 0 && isdigit(result[j])) {
				base[c] = result[j];
				j--;
				c++;
			}
			start = j + 1;
			j = i + 1;
			c = 0;
			while (isdigit(result[j]) && j < strlen(result)) {
				degree[c] = result[j];
				c++;
				j++;
			}
			degree_size = j - start;


			char* result_power = NULL;
			result_power = power(_reverse(base), degree);

			int power_size = strlen(result_power);
			
			char* buffer = get_string_array(start + power_size + strlen(result) - j + 1);

			for (int k = 0; k < start; k++) {
				buffer[k] = result[k];
			}
			memmove(&buffer[start], result_power, power_size);
			free(result_power);
			for (int k = j; k < strlen(result); k++) {
				buffer[strlen(buffer)] = result[k];
			}
			memset(result, '\0', strlen(result));
			strcpy(result, buffer);
			
			memset(buffer, '\0', strlen(buffer));
			free(buffer);
			size = strlen(result);
			i = 0;
		}
	}

	for (int i = 0; i < size; i++) {
		if (result[i] == '*') {
			char a[MAX_NUMBER_SIZE];
			char b[MAX_NUMBER_SIZE];
			memset(a, '\0', MAX_NUMBER_SIZE);
			memset(b, '\0', MAX_NUMBER_SIZE);
			int j = i - 1, c = 0, start = 0, multiple_size = 0;
			while (j >= 0 && isdigit(result[j])) {
				a[c] = result[j];
				c++;
				j--;
			}
			start = j + 1;
			j = i + 1;
			c = 0;
			while (isdigit(result[j]) && j < strlen(result)) {
				b[c] = result[j];
				c++;
				j++;
			}
			multiple_size = j - start;

			char* buffer = get_string_array(start + multiple_size + strlen(result) - j + 1);
			for (int k = 0; k < start; k++) {
				buffer[k] = result[k];
			}

			char* result_multiple;
			result_multiple = simple_multiple(_reverse(a), b);
			int result_multiple_size = strlen(result_multiple);

			memmove(&buffer[start], result_multiple, result_multiple_size);
			free(result_multiple);
			for (int k = j; k < strlen(result); k++) {
				buffer[strlen(buffer)] = result[k];
			}
			memset(result, '\0', strlen(result));
			strcpy(result, buffer);
			
			memset(buffer, '\0', strlen(buffer));
			size = strlen(result);
			i = 0;
			free(buffer);
		}
	}

	for (int i = 0; i < size; i++) {
		if (result[i] == '+') {
			char a[MAX_NUMBER_SIZE];
			char b[MAX_NUMBER_SIZE];
			memset(a, '\0', MAX_NUMBER_SIZE);
			memset(b, '\0', MAX_NUMBER_SIZE);
			int j = i - 1, c = 0, start = 0, sum_size = 0;
			while (j >= 0 && isdigit(result[j])) {
				a[c] = result[j];
				c++;
				j--;
			}
			start = j + 1;
			j = i + 1;
			c = 0;
			while (isdigit(result[j]) && j < strlen(result)) {
				b[c] = result[j];
				c++;
				j++;
			}
			sum_size = j - start;
			char* buffer = get_string_array(start + sum_size + strlen(result) - j + 1);
			for (int k = 0; k < start; k++) {
				buffer[k] = result[k];
			}

			char* result_sum;
			result_sum = sum(_reverse(a), b);
			int result_sum_size = strlen(result_sum);

			memmove(&buffer[start], result_sum, result_sum_size);
			free(result_sum);
			for (int k = j; k < strlen(result); k++) {
				buffer[strlen(buffer)] = result[k];
			}
			memset(result, '\0', strlen(result));
			strcpy(result, buffer);
			
			memset(buffer, '\0', strlen(buffer));
			size = strlen(result);
			i = 0;
			free(buffer);
		}
		if (result[i] == '-' && i != 0) {
			char a[MAX_NUMBER_SIZE];
			char b[MAX_NUMBER_SIZE];
			memset(a, '\0', MAX_NUMBER_SIZE);
			memset(b, '\0', MAX_NUMBER_SIZE);
			int j = i - 1, c = 0, start = 0, sum_size = 0;
			while (j >= 0 && isdigit(result[j])) {
				a[c] = result[j];
				c++;
				j--;
			}
			start = j + 1;
			j = i + 1;
			c = 0;
			while (isdigit(result[j]) && j < strlen(result)) {
				b[c] = result[j];
				c++;
				j++;
			}
			sum_size = j - start;
			char* buffer = get_string_array(start + sum_size + strlen(result) - j + 1);

			for (int k = 0; k < start; k++) {
				buffer[k] = result[k];
			}

			char* result_difference;

			result_difference = compare(_reverse(a), b);
			int result_difference_size = strlen(result_difference);

			memmove(&buffer[start], result_difference, result_difference_size);
			free(result_difference);
			for (int k = j; k < strlen(result); k++) {
				buffer[strlen(buffer)] = result[k];
			}
			memset(result, '\0', strlen(result));
			strcpy(result, buffer);
			
			memset(buffer, '\0', strlen(buffer));
			size = strlen(result);
			i = 0;
			free(buffer);
		}
		if (result[i] == '-' && i == 0) {
			char a[MAX_NUMBER_SIZE];
			char b[MAX_NUMBER_SIZE];
			memset(a, '\0', MAX_NUMBER_SIZE);
			memset(b, '\0', MAX_NUMBER_SIZE);

			int j = i + 1, c = 0, start = 0, sum_size = 0;
			while (isdigit(result[j]) && j < strlen(result)) {
				a[c] = result[j];
				c++;
				j++;
			}
			char symbol = result[j];
			j++;
			c = 0;
			while (isdigit(result[j]) && j < strlen(result)) {
				b[c] = result[j];
				c++;
				j++;
			}

			char* result_number;
			int result_size = 0;
			if (symbol == '+') {
				result_number = compare(b, a);
				result_size = strlen(result_number);
				char* buffer = get_string_array(start + result_size + strlen(result) - j + 1);
				memmove(buffer, result_number, result_size);
				free(result_number);
				for (int i = j; i < strlen(result); i++) {
					buffer[strlen(buffer)] = result[i];
				}
				memset(result, '\0', strlen(result));
				strcpy(result, buffer);
				
				memset(buffer, '\0', strlen(buffer));
				size = strlen(result);
				i = 0;
				free(buffer);
			}
			else if (symbol == '-') {
				result_number = sum(a, b);
				result_size = strlen(result_number);
				char* buffer = get_string_array(result_size + strlen(result) - j + 2);
				buffer[0] = '-';
				memmove(&buffer[1], result_number, result_size);
				free(result_number);
				for (int i = j; i < strlen(result); i++) {
					buffer[strlen(buffer)] = result[i];
				}
				memset(result, '\0', strlen(result));
				strcpy(result, buffer);
				
				memset(buffer, '\0', strlen(buffer));
				size = strlen(result);
				i = 0;
				free(buffer);
			}
		}
	}
	printf("%s", result);
}

void delete_same(char* input) {
	char buffer[MAX_SIZE];
	memset(buffer, '\0', MAX_SIZE);
	int size = strlen(input);
	int flag = 0;
	int delete_flag = 0;
	for (int i = 0; i < size; i++) {
		if (input[i] == '!') {
			flag = 1;
			char a[MAX_NUMBER_SIZE];
			memset(a, '\0', sizeof(char) * MAX_NUMBER_SIZE);
			int j = i - 1, c = 0;
			while (j >= 0 && isdigit(input[j])) {
				a[c] = input[j];
				c++;
				j--;
			}
			if (j < 0) {
				j = 0;
			}
			if (input[i + 1] == '+' || input[i + 1] == '-') {
				for (int k = i + 1; k < size; k++) {
					if (input[k] == '!') {
						delete_flag = 1;
						char b[MAX_NUMBER_SIZE];
						memset(b, '\0', sizeof(char) * MAX_NUMBER_SIZE);
						int j1 = k - 1, c = 0;
						while (j1 >= 0 && isdigit(input[j1])) {
							b[c] = input[j1];
							c++;
							j1--;
						}
						if ((input[j1] == '-' && (input[j] == '+' || j == 0)) || (input[j1] == '+' && input[j] == '-')) {
							if (strlen(a) == strlen(b)) {
								int flag = 1;
								for (int i = 0; i < strlen(a); i++) {
									if (a[i] != b[i]) {
										flag = 0;
									}
								}
								if (flag) {
									strncpy(buffer, input, j);
									strncpy(&buffer[strlen(buffer)], &input[i + 1], j1 - i - 1);
									strncpy(&buffer[strlen(buffer)], &input[k + 1], strlen(input) - k);
								}
							}
						}


					}
				}
			}

		}
	}
	if (!delete_flag) {
		parse_input(input);
	}
	else {
		if (buffer[0] == '+' && flag == 1) {
			for (int i = 0; i < strlen(buffer) - 1; i++) {
				buffer[i] = buffer[i + 1];
			}
			buffer[strlen(buffer) - 1] = '\0';
			parse_input(buffer);
		}
		else if (buffer[0] != '+' && flag == 1) {
			parse_input(buffer);
		}
		else {
			parse_input(input);
		}
	}

}

unsigned short int find(const char symbol) {
	const char correct_symbols[] = {'+', '-', '*', '^', '!', ' '};
	unsigned short int correct_symbols_size = strlen(correct_symbols);
	for (int i = 0; i < correct_symbols_size; i++) {
		if (correct_symbols[i] == symbol || isdigit(symbol)) {
			return CORRECT_STRING;
		}
	}
	return INCORRECT_STRING;
}

unsigned short int check_input(char* input) {
	int input_size = strlen(input);
	if (input_size > 1) {
		for (int i = 0; i < input_size; i++) {
			if (!find(input[i])) {
				return INCORRECT_STRING;
			}
		}
		for (int i = 0; i < input_size - 1; i++) {
			if (
				(input[i] == '+' && input[i + 1] == '+') ||
				(input[i] == '+' && input[i + 1] == '-') ||
				(input[i] == '+' && input[i + 1] == '*') ||
				(input[i] == '+' && input[i + 1] == '^') ||
				(input[i] == '+' && input[i + 1] == '!') ||
				(input[i] == '-' && input[i + 1] == '-') ||
				(input[i] == '-' && input[i + 1] == '+') ||
				(input[i] == '-' && input[i + 1] == '*') ||
				(input[i] == '-' && input[i + 1] == '^') ||
				(input[i] == '-' && input[i + 1] == '!') ||
				(input[i] == '*' && input[i + 1] == '*') ||
				(input[i] == '*' && input[i + 1] == '+') ||
				(input[i] == '*' && input[i + 1] == '-') ||
				(input[i] == '*' && input[i + 1] == '^') ||
				(input[i] == '*' && input[i + 1] == '!') ||
				(input[i] == '!' && input[i + 1] == '!') ||
				(input[i] == ' ' && input[i + 1] == ' ')
				) {
				return INCORRECT_STRING;
			}
		}
		if (input[input_size - 1] == '*' ||
			input[input_size - 1] == '+' ||
			input[input_size - 1] == '-' ||
			input[input_size - 1] == '^') {
			return INCORRECT_STRING;
		}
	}
	else {
		return INCORRECT_STRING;
	}
	delete_same(input);
}

int check_for_symbols_in_two_sum(char* a) {
	for (int i = 0; i < strlen(a); i++) {
		if (!find(a[i])) {
			return INCORRECT_STRING;
		}
	}
	return CORRECT_STRING;
}

int two_num(const char* input) {
	int spaces = 0, minus = 0;

	if (!check_for_symbols_in_two_sum(input)) {
		return INCORRECT_STRING;
	}
	if (input[0] == '-' && strlen(input) > 1) {
		minus = 1;
		for (int i = 1; i < strlen(input); i++) {
			if (!isdigit(input[i])) {
				if (input[i] == ' ') {
					spaces++;
				}
				else if (input[i] == '-') {
					minus++;
				}
				else {
					return 0;
				}
			}

		}
		if (spaces > 1 || minus > 2) {
			return INCORRECT_STRING;
		}
	}
	else {
		for (int i = 0; i < strlen(input); i++) {
			if (!isdigit(input[i])) {
				if (input[i] == ' ') {
					spaces++;
				}
				else {
					return INCORRECT_STRING;
				}

			}
		}
		if (spaces > 1) {
			return INCORRECT_STRING;
		}
	}
	return CORRECT_STRING;
}


void format_input(char* input) {
	char buffer[MAX_SIZE];
	memset(buffer, '\0', MAX_SIZE);
	int size = strlen(input);
	int j = 0;
	for (int i = 0; i < size; i++) {
		if (input[i] != ' ') {
			buffer[j] = input[i];
			j++;
		}
	}
	check_input(buffer);
}

int main() {
	char* ptr;
	char input[MAX_SIZE];
	ptr = gets(input);
	if (two_num(input)) {
		from_to(input);
	}
	else { 
		format_input(input); 
	} 
	return EXIT_SUCCESS;
}