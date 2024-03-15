#include "test-runner.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define INITIAL_ERROR_CAPACITY 2

Test *tests = NULL;
Test *tail;

void result_error(Result *rlt, char *msg)
{
	if (rlt->errors == NULL)
	{
		rlt->errors = malloc(sizeof(char *) * INITIAL_ERROR_CAPACITY);
		rlt->errors_cap = INITIAL_ERROR_CAPACITY;
		rlt->errors_size = 0;
	}
	else if (rlt->errors_size == rlt->errors_cap)
	{
		rlt->errors_cap *= 2;
		rlt->errors = realloc(rlt->errors, sizeof(char *) * rlt->errors_cap);
	}

	int length = strlen(msg);
	char *err_msg = malloc((sizeof(char) * length) + 1);

	strcpy(err_msg, msg);
	rlt->errors[rlt->errors_size++] = err_msg;
}

void register_test(char *test_name, void (*test)(Result *rlt))
{
	Test *next = malloc(sizeof(Test));
	next->name = test_name;
	next->test = test;

	if (tests == NULL)
	{
		tests = next;
		tail = tests;
	}
	else
	{
		tail->next = next;
		tail = next;
	}
}

void run_tests()
{
	Test *current = tests;
	int failures = 0;

	printf("\n");

	while (current != NULL)
	{
		Result *rlt = malloc(sizeof(Result));
		rlt->errors = NULL;
		rlt->errors_size = 0;
		rlt->errors_cap = INITIAL_ERROR_CAPACITY;

		current->rlt = rlt;
		current->test(rlt);

		if (rlt->errors_size > 0)
		{
			printf("[\x1B[31mFAIL\x1B[0m] %s\n", current->name);

			for (int i = 0; i < rlt->errors_size; i++)
			{
				printf("       \x1B[90merror: %s\x1B[0m\n", rlt->errors[i]);
			}

			printf("\n");

			failures++;
		}
		else
		{
			printf("[\x1B[32mPASS\x1B[0m] %s\n", current->name);
		}

		current = current->next;
	}

	if (failures == 1)
		printf("\nThere was 1 failure\n");
	else if (failures != 0)
		printf("\nThere were %d failures\n", failures);
	else
		printf("\nAll tests passing!\n");
}

void cleanup()
{
	Test *current = tests;
	while (current != NULL)
	{
		Test *next = current->next;

		for (int i = 0; i < current->rlt->errors_size; i++)
		{
			free(current->rlt->errors[i]);
		}

		if (current->rlt->errors != NULL)
		{
			free(current->rlt->errors);
		}

		free(current->rlt);
		free(current);

		current = next;
	}
}
