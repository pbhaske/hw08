#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "json.h"
#include <ctype.h>
#include <string.h>

bool parse_int(int* a_value, char** a_pos) {
	bool flag = false;
	bool num_valid = false;

	if(*a_pos[0] == '-') {
		flag = true;
		*a_pos += 1;
	}
	if(**a_pos >= '0' && **a_pos <= '9') {
		*a_value = (**a_pos - '0');
		num_valid = true;
		*a_pos += 1;
	while(**a_pos >= '0' && **a_pos <= '9') {
		*a_value = *a_value * 10;
		*a_value += (**a_pos - '0');
		*a_pos += 1;
	}
	}
	if(flag && num_valid) {
		*a_value *= -1;
	}
	return num_valid;
}
bool parse_string(char** a_string, char** a_pos) {
	char * head = *a_pos;

	bool num_valid = false;
	while(**a_pos != '\"') {
		if(**a_pos == '\0' || **a_pos == '\n') {
		return false;
		}
		*a_pos += 1;
	}
	char* a_tmp = *a_pos;
	int num_of_quotes = 0;
	while(**a_pos != '\0') {
		if(**a_pos == '\"') {
			num_of_quotes++;
		}
		*a_pos += 1;
	}

	if(num_of_quotes != 2){
		return false;
	}

	*a_pos = a_tmp + 1;
	while(**a_pos != '\"') {
		if(**a_pos == '\0' || **a_pos == '\n') {
			return false;
		}
		*a_pos += 1;
	}

	char* string = malloc((strlen(*a_pos) + 1) * sizeof(*string));
	char* string_temp = string;
	*a_pos = a_tmp + 1;
	while(**a_pos != '\"') {
		*string = **a_pos;
		string += 1;
		*a_pos += 1;
	}
	*string = '\0';
	*a_string = string_temp;

	if(**a_pos == '\"') {
		num_valid = true;
		*a_pos += 1;
	}
	*a_pos = head;
	return num_valid;
}

void print_element(Element element) {
	if(element.type == ELEMENT_INT) {
		printf("%d", element.as_int);
	}
	
	if(element.type == ELEMENT_STRING && element.as_string != NULL) {
		printf("\"%s\"", element.as_string);
	}
}

bool parse_element(Element* a_element, char** a_pos) {
	bool num_valid = false;
	while(isspace(**a_pos) == true) {
		*a_pos += 1;
	}
	if(isdigit(**a_pos) || **a_pos == '-') {
		a_element -> type = ELEMENT_INT;
		num_valid = parse_int(&a_element -> as_int, a_pos);
	}
	else if(**a_pos == '\"') {
		a_element -> type = ELEMENT_STRING;
		num_valid = parse_string(&a_element -> as_string, a_pos);
	}	
	return num_valid;
}

int main(int argc, char*argv[]) {
	int x = 0;
	char * y = "-99";
	char* z = "\"Fuck Kushal\"";
	char* a = "\"abc";

	if(!parse_int(&x, &y)) {
		printf("priyanka is dumbo");
	}
	printf("%d", x);
	Element *test = malloc(sizeof(*test));	
	(*test).type = ELEMENT_INT;
	printf("\n");
	(*test).as_int = 9;
	print_element(*test);
	if(!parse_element(test, &y)) {
		printf("\nWORKS");
	}
	if(parse_string(&z, &a)) {
		printf("\npriyanka is dumbo");
	}
	printf("\n%s",z);
	printf("\n%s",a);
	Element *test1 = malloc(sizeof(*test1));	
	(*test1).type = ELEMENT_STRING;
	printf("\n");
	(*test1).as_string = "Fuck Kushal Negi";
	print_element(*test1);
	if(parse_element(test1, &z)) {
		printf("\nWORKS");
	}
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
