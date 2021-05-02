// ****************************************
// Program Title: Lab 05
// Project File: header.h
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 02/17/2021
// ****************************************
#define key ((key_t)(1234))
#define MAX 100

struct text_message { 
	long mesg_type;
	char mesg_text[MAX];
};
