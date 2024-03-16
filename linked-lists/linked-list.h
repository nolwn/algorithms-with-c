typedef struct ListElmt_
{
	struct ListElmt_ *next;
	const void *data;
} ListElmt;

typedef struct List_
{
	void (*destroy)(void *data);
	ListElmt *head;
	int size;
	ListElmt *tail;
} List;

/**
 * @brief Initializes the linked list specified by list. This operation must be called for
 * a linked list before the list can be used with any other operation.
 *
 * @param list list to initialize
 * @param destroy provides a way to free dynamically allocated data when list_destroy is
 * called. For example, if the list contains data dynamically allocated using malloc,
 * destroy should be set to free to tree the data as the linked list is destroyed. For
 * structured data containing several dynamically allocated members destroy should be set
 * to a user-defined function that calls free for each dynamically allocated member as
 * well as for the structure itself. For a linked list containing data that should not be
 * freed, destroy should be set to NULL.
 */
void list_init(List *list, void (*destroy)(void *data));

/**
 * @brief Inserts an element just after element in the linked list specified by list. If
 * element is NILL, the new element is inserted at the head of the list. The new element
 * contains a pointer to data, so the memory referenced by data should remain valid as
 * long as the element remains in the list. It is the responsibility of the caller to
 * manage the storage associated with data.
 *
 * @param list list to destroy
 */
void list_destroy(List *list);

/**
 * @brief Inserts an element just after element in the linked list specified by list. If
 * element is NULL, the new element is inserted at the head of the list. The new element
 * contains a pointer to data, so the memory reference bt data should remain valid as long
 * as the element remains in the list. It is the responsibility of the caller to manage
 * the storage associated with data.
 *
 * @param list the list the insert an element into
 * @param element the element to be inserted
 * @param data the data contained in the element being inserted
 * @return 0 if inserting the element is successful, or -1 otherwise.
 */
int list_ins_next(List *list, ListElmt *element, const void *data);

/**
 * @brief Removing the element just after element from the linked list specified bt list.
 * If element is NULL, the element at the head of the list is removed. Upon return, data
 * points to the data stored in the element that was removed. It is the responsibility of
 * the caller to manager the storage associated with the data.
 *
 * @param list the list to insert data into
 * @param element the element just before the element to be removed
 * @param data the data contained by the element that was removed
 * @return 0 if deleting the element is successful, or -1 otherwise.
 */
int list_rem_next(List *list, ListElmt *element, void **data);

/**
 * @brief Macro that evaluates to the number of elements in the linked list specified by
 * list.
 *
 * @param list the list to be sized.
 * @return number of elements in the list.
 */
#define list_size(list) ((list)->size)

/**
 * @brief Macro that evaluates to the element at the head of the linked list specified by
 * list.
 *
 * @param list the list to get the head of.
 * @return Element at the head of the list.
 */
#define list_head(list) ((list)->head)

/**
 * @brief Macro that evaluates to the element at the tail of the linked list specified by
 * list
 *
 * @param list the list to get the tail of.
 * @return Element at the tail of the list
 */
#define list_tail(list) ((list)->tail)

/**
 * @brief Macro that determines whether the element specified as element is at the head of
 * a linked list.
 *
 * @param element the element to be evaluated.
 * @return 1 if the element is at the head of a linked list, or 0 otherwise.
 */
int list_is_head(const ListElmt *element);

/**
 * @brief Macro that determines whether the element specified as element is at the tail of
 * a linked list.
 *
 * @param element the element to be evaluated
 * @return 1 if the element is at the tail of a linked list, or 0 otherwise
 */
int list_is_tail(const ListElmt *element);

/**
 * @brief Macro that evaluates to the data stored in the element of a linked list
 * specified by element.
 *
 * @param element the element whose data will be evaluated to
 * @return Data stored in the element.
 */
#define list_data(element) ((element)->data)

/**
 * @brief Macro that evaluates to the element of a linked list following the element
 * specified by element.
 *
 * @param element the element whose next element will be returned
 * @return Element following the specified element
 */
#define list_next(element) ((element)->next)
