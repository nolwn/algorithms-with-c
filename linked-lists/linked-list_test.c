#include <stdlib.h>
#include <stdio.h>
#include "linked-list.h"
#include "../test-runner.h"

int mock_destroy_calls = 0;

void mock_destroy(void *elmt)
{
	mock_destroy_calls++;
}

void test_macro_list_size(Result *rlt)
{
	List list = {};
	int data = 73;
	list_init(&list, NULL);

	if (list_size(&list) != list.size)
	{
		return result_error(rlt, "list_size should return the size of the list");
	}

	list_ins_next(&list, NULL, &data);

	if (list_size(&list) != list.size)
	{
		return result_error(rlt, "list_size should return the new size of the list");
	}
}

void test_macro_list_head(Result *rlt)
{
	List list = {};
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;

	list_init(&list, NULL);

	if (list_head(&list) != NULL)
	{
		return result_error(rlt, "a new list should have a head of NULL");
	}

	list_ins_next(&list, NULL, &data1);

	if (list_head(&list) == NULL)
	{
		return result_error(rlt, "a list with an item should not have a head of NULL");
	}

	if (list_head(&list)->data != &data1)
	{
		return result_error(
			rlt,
			"list_head should return the item in a list of 1");
	}

	list_ins_next(&list, list_head(&list), &data2);

	if (list_head(&list)->data != &data1)
	{
		return result_error(
			rlt,
			"list_head should not return an item inserted at the end of the list");
	}

	list_ins_next(&list, NULL, &data3);

	if (list_head(&list)->data != &data3)
	{
		return result_error(
			rlt,
			"list_head should return another item inserted at the front of the list");
	}
}

void test_macro_list_tail(Result *rlt)
{
	List list = {};
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;

	list_init(&list, NULL);

	if (list_tail(&list) != NULL)
	{
		return result_error(rlt, "a new list should have a tail of NULL");
	}

	list_ins_next(&list, NULL, &data1);

	if (list_tail(&list) == NULL)
	{
		return result_error(rlt, "a list with an item should not have a tail of NULL");
	}

	if (list_tail(&list)->data != &data1)
	{
		return result_error(
			rlt,
			"list_tail should return the item in a list of 1");
	}

	list_ins_next(&list, NULL, &data2);

	if (list_tail(&list)->data != &data1)
	{
		return result_error(
			rlt,
			"list_tail should not return an item inserted at the front of the list");
	}

	list_ins_next(&list, list_tail(&list), &data3);

	if (list_tail(&list)->data != &data3)
	{
		return result_error(
			rlt,
			"list_tail should return another item inserted at the end of the list");
	}
}

void test_list_data(Result *rlt)
{
	List list = {};
	int data = 6;

	list_init(&list, NULL);
	list_ins_next(&list, NULL, &data);

	if (list_data(list_head(&list)) != &data)
	{
		return result_error(
			rlt,
			"list_data should return the data contained in a list element");
	}
}

void test_list_next(Result *rlt)
{
	List list = {};
	ListElmt *curr;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;

	list_init(&list, NULL);
	list_ins_next(&list, NULL, &data4);
	list_ins_next(&list, NULL, &data3);
	list_ins_next(&list, NULL, &data2);
	list_ins_next(&list, NULL, &data1);

	curr = list_head(&list);
	if (list_data(curr) != &data1)
	{
		return result_error(rlt, "the list should start with 1 as its data");
	}

	curr = list_next(curr);
	if (list_data(curr) != &data2)
	{
		return result_error(rlt, "the second item in the list should have 2 as its data");
	}

	curr = list_next(curr);
	if (list_data(curr) != &data3)
	{
		return result_error(rlt, "the third item in the list should have 3 as its data");
	}

	curr = list_next(curr);
	if (list_data(curr) != &data4)
	{
		return result_error(rlt, "the fourth item in the list should have 4 as its data");
	}

	curr = list_next(curr);
	if (curr != NULL)
	{
		return result_error(rlt, "there should be no fifth item in the list");
	}
}

void test_list_init(Result *rlt)
{
	List list = {};
	list_init(&list, free);

	if (list.size != 0)
	{
		char err[35];
		sprintf(err, "expected 0, received %d", list.size);
		return result_error(rlt, err);
	}

	if (list.head != NULL)
	{
		return result_error(rlt, "expected head to be NULL");
	}

	if (list.destroy != free)
	{
		return result_error(
			rlt,
			"expected the destroy function to match the one that was passed");
	}

	return;
}

void test_list_ins_next_first_item(Result *rlt)
{
	List list = {};
	int data = 67;

	list_init(&list, NULL);
	int res = list_ins_next(&list, NULL, &data);

	if (res != 0)
	{
		char err[40];
		sprintf(err, "expected result to be 0, received %d", list_size(&list));
		return result_error(rlt, err);
	}

	if (list_size(&list) != 1)
	{
		char err[40];
		sprintf(err, "expected size to be 1, received %d", list_size(&list));
		return result_error(rlt, err);
	}
}

void test_list_ins_next_bad_element(Result *rlt)
{
	List list = {};
	int data = 98;
	ListElmt *notInList;

	list_init(&list, NULL);
	int res = list_ins_next(&list, notInList, &data);

	if (res != -1)
	{
		char err[40];
		sprintf(err, "expected an error (-1), received %d", list_size(&list));
		return result_error(rlt, err);
	}
}

void test_list_ins_next_multiple_items(Result *rlt)
{
	List list = {};
	int data = 93;

	list_init(&list, NULL);
}

void test_list_destroy(Result *rlt)
{
}

int main()
{
	printf("\n\x1b[2mLinked List Tests\x1b[24m\n");

	register_test("list_size macro gets the size of the list", test_macro_list_size);
	register_test("list_head macro returns the head of the list", test_macro_list_head);
	register_test("list_tail macro returns the tail of the list", test_macro_list_tail);
	register_test(
		"list_data macro returns the data contained in an element",
		test_list_data);

	register_test("list_next returns the element after the one provided", test_list_next);
	register_test("list_init creates a new list", test_list_init);
	register_test("list_ins_next inserts first item", test_list_ins_next_first_item);
	register_test(
		"list_ins_next returns -1 when the element does not exist in the list",
		test_list_ins_next_bad_element);

	run_tests();
	cleanup();

	return 0;
}
