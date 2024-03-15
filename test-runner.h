#define MAX_ERROR_LENGTH 120

typedef struct Result_
{
	char **errors;
	int errors_cap;
	int errors_size;
} Result;

typedef struct Test_
{
	char *name;
	struct Test_ *next;
	void (*test)(Result *rlt);
	Result *rlt;

} Test;

void cleanup();

void result_error(Result *rlt, char *msg);

void register_test(char *test_name, void (*test)(Result *));
void run_tests();
