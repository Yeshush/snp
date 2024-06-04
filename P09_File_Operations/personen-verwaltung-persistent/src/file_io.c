/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */
/**
 * @file
 * @brief Lab implementation
 */
#include <stdio.h>
#include <stdlib.h>

#include "file_io.h"
#include "person.h"
#include "list.h"

void perror_and_exit(const char *context)
{
	perror(context);
	exit(EXIT_FAILURE);
} // das muss noch an einen anderen Ort, scia

// May divide your code in further functions
// BEGIN-STUDENTS-TO-ADD-CODE
FILE *f;
// END-STUDENTS-TO-ADD-CODE



/**
 * @brief Stores a list of persons to a CSV file.
 *
 * This function opens the file "person-list.csv" in write mode and writes each person in the list
 * to the file in CSV format "name;first_name;age". The function uses the `person_to_csv_string`
 * function to convert each person to a CSV string before writing it to the file.
 *
 * If the file "person-list.csv" cannot be opened, the function calls `perror_and_exit` to print an
 * error message and exit the program.
 * 
 * @note The function dynamically allocates memory for a buffer using `malloc`. It is the caller's
 * responsibility to free this memory when it is no longer needed.
 */
void store_person_list(void)
{
	// BEGIN-STUDENTS-TO-ADD-CODE
	f= fopen("person-list.csv", "w");

	if (!f)
	{
		perror_and_exit("coudlnt open person-list.csv");
	}

	person_t* person = list_getFirst();
	char *buffer;

	while (person != NULL)
	{
		buffer = malloc(255 * sizeof(char));

		person_to_csv_string(person, buffer);
		fputs(buffer, f);
		fputs("\n", f);
		person = list_getNext();
	}
	fclose(f);
	// END-STUDENTS-TO-ADD-CODE
}

/**
 * @brief Loads a list of persons from a CSV file.
 *
 * This function opens the file "person-list.csv" in read mode and reads each line of the file.
 * Each line is expected to represent a person in CSV format "name;first_name;age". The function
 * converts each line to a person structure using the `person_from_csv_string` function and inserts
 * the person into a list using the `list_insert` function.
 *
 * If the file "person-list.csv" does not exist, the function creates it. If the file cannot be
 * opened or created, the function calls `perror_and_exit` to print an error message and exit the program.
 *
 * @note The function dynamically allocates memory for each person using `malloc`. It is the caller's
 * responsibility to free this memory when it is no longer needed.
 */
void load_person_list(void)
{
	// BEGIN-STUDENTS-TO-ADD-CODE
	f = fopen("person-list.csv", "r");
	if (!f) {
    // If the file doesn't exist, create it
    f = fopen("person-list.csv", "w");
    if (!f) {
        perror_and_exit("couldn't open person-list.csv");
    }
    // Close the file after creating it
    fclose(f);

    // Reopen the file in read mode
    f = fopen("person-list.csv", "r");
    if (!f) {
        perror_and_exit("couldn't reopen person-list.csv");
    }

	}	

	char buffer[255];
	while (fgets(buffer, 255, f) != NULL)
	{
		person_t *person = malloc(sizeof(person_t));
		person_from_csv_string(person, buffer);
		list_insert(person);
	}
	fclose(f);
	// END-STUDENTS-TO-ADD-CODE
}