/* linked_list.c - Unit Tests for Doubly Linked List
 * Copyright (C) 2018 Quytelda Kahja
 *
 * This file is part of focs.
 *
 * focs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * focs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with focs.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <check.h>

#include "list/linked_list.h"

START_TEST(test_linklist_alloc)
{
	int err;
	struct linked_list * list = NULL;

	err = linklist_alloc(&list, 0);

	ck_assert(!err);
	ck_assert(list);
	ck_assert_int_eq(list->length, 0);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_null_true)
{
	struct linked_list * list;

	linklist_alloc(&list, 0);
	ck_assert(linklist_null(list));
	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_null_false)
{
	uint8_t val = 1;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(val));
	linklist_push_head(list, &val);
	ck_assert(!linklist_null(list));
	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_push_head_single)
{
	uint8_t val = 1;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(val));
	linklist_push_head(list, &val);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);
	ck_assert_mem_eq(list->head->data, &val, sizeof(uint8_t));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_push_head_multiple)
{
	uint8_t val1 = 1;
	uint8_t val2 = 2;
	uint8_t val3 = 3;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(val1));

	linklist_push_head(list, &val1);
	linklist_push_head(list, &val2);
	linklist_push_head(list, &val3);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 3);

	struct ll_element * current = list->head;
	ck_assert_mem_eq(current->data, &val3, sizeof(val3));
	current = current->next;
	ck_assert_mem_eq(current->data, &val2, sizeof(val2));
	current = current->next;
	ck_assert_mem_eq(current->data, &val1, sizeof(val1));
	ck_assert(!current->next);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_push_tail_single)
{
	uint8_t val = 1;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));
	linklist_push_tail(list, &val);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);
	ck_assert_mem_eq(list->head->data, &val, sizeof(val));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_push_tail_multiple)
{
	uint8_t val1 = 1;
	uint8_t val2 = 2;
	uint8_t val3 = 3;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	linklist_push_tail(list, &val1);
	linklist_push_tail(list, &val2);
	linklist_push_tail(list, &val3);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 3);

	struct ll_element * current = list->head;
	ck_assert_mem_eq(current->data, &val1, sizeof(uint8_t));
	current = current->next;
	ck_assert_mem_eq(current->data, &val2, sizeof(uint8_t));
	current = current->next;
	ck_assert_mem_eq(current->data, &val3, sizeof(uint8_t));
	ck_assert(!current->next);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_pop_head_empty)
{
	void * val;
	struct linked_list * list;

	linklist_alloc(&list, 0);

	val = linklist_pop_head(list);

	ck_assert(!val);
	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_pop_head_single)
{
	uint8_t val = 1;
	uint8_t * out;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(val));
	linklist_push_head(list, &val);

	out = linklist_pop_head(list);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	free(out);
	linklist_free(&list);

}
END_TEST

START_TEST(test_linklist_pop_head_multiple)
{
	uint8_t in1 = 1;
	uint8_t in2 = 2;
	uint8_t in3 = 3;
	uint8_t * out1;
	uint8_t * out2;
	uint8_t * out3;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	linklist_push_head(list, &in1);
	linklist_push_head(list, &in2);
	linklist_push_head(list, &in3);

	out1 = (uint8_t *) linklist_pop_head(list);
	out2 = (uint8_t *) linklist_pop_head(list);
	out3 = (uint8_t *) linklist_pop_head(list);

	ck_assert(out1);
	ck_assert(out2);
	ck_assert(out3);

	ck_assert_mem_eq(out1, &in3, sizeof(in3));
	ck_assert_mem_eq(out2, &in2, sizeof(in2));
	ck_assert_mem_eq(out3, &in1, sizeof(in1));

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	free(out1);
	free(out2);
	free(out3);
	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_pop_tail_empty)
{
	void * val;
	struct linked_list * list;

	linklist_alloc(&list, 0);

	val = linklist_pop_tail(list);

	ck_assert(!val);
	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_pop_tail_single)
{
	uint8_t in = 1;
	uint8_t * out;
	struct linked_list * list;
	linklist_alloc(&list, sizeof(in));
	linklist_push_tail(list, &in);

	out = linklist_pop_tail(list);

	ck_assert_mem_eq(out, &in, sizeof(in));
	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	free(out);
	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_pop_tail_multiple)
{
	uint8_t in1 = 1;
	uint8_t in2 = 2;
	uint8_t in3 = 3;
	uint8_t * out1;
	uint8_t * out2;
	uint8_t * out3;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	linklist_push_tail(list, &in1);
	linklist_push_tail(list, &in2);
	linklist_push_tail(list, &in3);

	out1 = linklist_pop_tail(list);
	out2 = linklist_pop_tail(list);
	out3 = linklist_pop_tail(list);

	ck_assert_mem_eq(out1, &in3, sizeof(uint8_t));
	ck_assert_mem_eq(out2, &in2, sizeof(uint8_t));
	ck_assert_mem_eq(out3, &in1, sizeof(uint8_t));

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	free(out1);
	free(out2);
	free(out3);
	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_insert_single)
{
	uint8_t in = 1;
	bool success;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	success = linklist_insert(list, &in, 0);

	ck_assert(success);
	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_insert_multiple)
{
	bool r1;
	bool r2;
	bool r3;
	bool r4;
	uint8_t in1 = 1;
	uint8_t in2 = 2;
	uint8_t in3 = 3;
	uint8_t in4 = 4;
	uint8_t * out1;
	uint8_t * out2;
	uint8_t * out3;
	uint8_t * out4;

	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	/* Insert the elements out of order. */
	/* [4 1 2 3] */
	r1 = linklist_insert(list, &in1, 0);
	r2 = linklist_insert(list, &in3, 1);
	r3 = linklist_insert(list, &in2, 1);
	r4 = linklist_insert(list, &in4, 0);

	ck_assert(r1);
	ck_assert(r2);
	ck_assert(r3);
	ck_assert(r4);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 4);

	out1 = linklist_pop_head(list); /* 4 */
	out2 = linklist_pop_head(list); /* 1 */
	out3 = linklist_pop_head(list); /* 2 */
	out4 = linklist_pop_head(list); /* 3 */

	ck_assert_int_eq(*out1, in4);
	ck_assert_int_eq(*out2, in1);
	ck_assert_int_eq(*out3, in2);
	ck_assert_int_eq(*out4, in3);

	free(out1);
	free(out2);
	free(out3);
	free(out4);
	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_delete_empty)
{
	bool r1;
	bool r2;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	r1 = linklist_delete(list, 0);
	r2 = linklist_delete(list, 1);

	ck_assert(!r1);
	ck_assert(!r2);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_delete_single)
{
	uint8_t in = 1;
	bool r1;
	bool r2;
	bool r3;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(in));
	linklist_push_head(list, &in);

	r1 = linklist_delete(list, 1); /* [1] -> [1] (false) */
	r2 = linklist_delete(list, 0); /* [1] -> [] (true) */
	r3 = linklist_delete(list, 0); /* [] -> [] (false) */

	ck_assert(!r1);
	ck_assert(r2);
	ck_assert(!r3);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_delete_multiple)
{
	uint8_t in1 = 1;
	uint8_t in2 = 2;
	uint8_t in3 = 3;
	uint8_t in4 = 4;
	bool r1;
	bool r2;
	bool r3;
	bool r4;
	bool r5;
	struct linked_list * list;

	/* Create linked list: [1, 2, 3, 4] */
	linklist_alloc(&list, sizeof(uint8_t));
	linklist_push_tail(list, &in1);
	linklist_push_tail(list, &in2);
	linklist_push_tail(list, &in3);
	linklist_push_tail(list, &in4);

	/* Drop the elements out of order. */
	/* [1, 2, 3, 4] -> [1, 2, 4] (true) */
	r1 = linklist_delete(list, 2);
	/* [1, 2, 4] -> [2, 4] (true) */
	r2 = linklist_delete(list, 0);
	/* [2, 4] -> [2] (true) */
	r3 = linklist_delete(list, 1);
	/* [2] -> [] (true) */
	r4 = linklist_delete(list, 0);
	/* [] -> [] (false) */
	r5 = linklist_delete(list, 0);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	ck_assert(r1);
	ck_assert(r2);
	ck_assert(r3);
	ck_assert(r4);
	ck_assert(!r5);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_remove_empty)
{
	void * val1;
	void * val2;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	val1 = linklist_remove(list, 0);
	val2 = linklist_remove(list, 1);

	ck_assert(!val1);
	ck_assert(!val2);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_remove_single)
{
	uint8_t in = 1;
	uint8_t * out;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	linklist_push_head(list, &in);
	out = linklist_remove(list, 0);

	ck_assert(out);
	ck_assert_int_eq(*out, in);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	free(out);
	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_remove_multiple)
{
	uint8_t in1 = 1;
	uint8_t in2 = 2;
	uint8_t in3 = 3;
	uint8_t in4 = 4;
	uint8_t * out1;
	uint8_t * out2;
	uint8_t * out3;
	uint8_t * out4;
	uint8_t * out5;
	struct linked_list * list;

	/* Create linked list: [1, 2, 3, 4] */
	linklist_alloc(&list, sizeof(uint8_t));
	linklist_push_tail(list, &in1);
	linklist_push_tail(list, &in2);
	linklist_push_tail(list, &in3);
	linklist_push_tail(list, &in4);

	/* Remove the elements out of order. */
	/* [1, 2, 3, 4] -> [1, 2, 4] (3) */
	out1 = linklist_remove(list, 2);
	/* [1, 2, 4] -> [2, 4] (1) */
	out2 = linklist_remove(list, 0);
	/* [2, 4] -> [2] (4) */
	out3 = linklist_remove(list, 1);
	/* [2] -> [] (2) */
	out4 = linklist_remove(list, 0);
	/* [] -> [] (NULL) */
	out5 = linklist_remove(list, 0);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	ck_assert(out1);
	ck_assert(out2);
	ck_assert(out3);
	ck_assert(out4);
	ck_assert(!out5);

	ck_assert_int_eq(*out1, in3);
	ck_assert_int_eq(*out2, in1);
	ck_assert_int_eq(*out3, in4);
	ck_assert_int_eq(*out4, in2);

	free(out1);
	free(out2);
	free(out3);
	free(out4);
	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_fetch_empty)
{
	void * val1;
	void * val2;
	struct linked_list * list;

	linklist_alloc(&list, 0);

	val1 = linklist_fetch(list, 0);
	val2 = linklist_fetch(list, 1);

	ck_assert(!val1);
	ck_assert(!val2);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_fetch_single)
{
	uint8_t in = 1;
	uint8_t * out;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(in));
	linklist_push_head(list, &in);

	out = linklist_fetch(list, 0);

	ck_assert(out);
	ck_assert_int_eq(*out, in);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_fetch_multiple)
{
	uint8_t in1 = 1;
	uint8_t in2 = 2;
	uint8_t in3 = 3;
	uint8_t in4 = 4;
	uint8_t * out1;
	uint8_t * out2;
	uint8_t * out3;
	uint8_t * out4;
	uint8_t * out5;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	/* Create linked list: [1, 2, 3, 4] */
	linklist_push_tail(list, &in1);
	linklist_push_tail(list, &in2);
	linklist_push_tail(list, &in3);
	linklist_push_tail(list, &in4);

	/* Fetch the elements out of order. */
	out1 = linklist_fetch(list, 2); /* 3 */
	out2 = linklist_fetch(list, 0); /* 1 */
	out3 = linklist_fetch(list, 1); /* 2 */
	out4 = linklist_fetch(list, 3); /* 4 */
	out5 = linklist_fetch(list, 4); /* NULL */

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 4);

	ck_assert(out1);
	ck_assert(out2);
	ck_assert(out3);
	ck_assert(out4);
	ck_assert(!out5);

	ck_assert_int_eq(*out1, in3);
	ck_assert_int_eq(*out2, in1);
	ck_assert_int_eq(*out3, in2);
	ck_assert_int_eq(*out4, in4);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_contains_empty)
{
	bool found;
	uint8_t val = 1;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	found = linklist_contains(list, &val);

	ck_assert(!found);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_contains_single)
{
	bool found1;
	bool found2;
	uint8_t in = 1;
	uint8_t val1 = 1;
	uint8_t val2 = 2;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(in));
	linklist_push_head(list, &in);

	found1 = linklist_contains(list, &val1);
	found2 = linklist_contains(list, &val2);

	ck_assert(found1);
	ck_assert(!found2);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_contains_multiple)
{
	bool found[5];
	uint8_t in[] = {1, 2, 3, 4};
	uint8_t val[] = {1, 2, 3, 4, 5};
	struct linked_list * list;

	/* Create linked list: [1, 2, 3, 4] */
	linklist_alloc(&list, sizeof(uint8_t));
	linklist_push_tail(list, &in[0]);
	linklist_push_tail(list, &in[1]);
	linklist_push_tail(list, &in[2]);
	linklist_push_tail(list, &in[3]);

	/* Check the elements out of order. */
	found[0] = linklist_contains(list, &val[2]);
	found[1] = linklist_contains(list, &val[0]);
	found[2] = linklist_contains(list, &val[1]);
	found[3] = linklist_contains(list, &val[3]);
	found[4] = linklist_contains(list, &val[4]);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, sizeof(in));

	ck_assert(found[0]);
	ck_assert(found[1]);
	ck_assert(found[2]);
	ck_assert(found[3]);
	ck_assert(!found[4]);

	linklist_free(&list);
}
END_TEST

bool pred_gte1(uint8_t * n)
{
	return (*n >= 1);
}

bool pred_lte1(uint8_t * n)
{
	return (*n <= 1);
}

START_TEST(test_linklist_any_empty)
{
	bool any;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	any = linklist_any(list, (pred_fn_t) pred_gte1);

	ck_assert(!any);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_any_single)
{
	bool any[2];
	uint8_t in = 0;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(in));
	linklist_push_head(list, &in);

	any[0] = linklist_any(list, (pred_fn_t) pred_gte1);
	any[1] = linklist_any(list, (pred_fn_t) pred_lte1);

	ck_assert(!any[0]);
	ck_assert(any[1]);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_any_multiple)
{
	bool any[2];
	uint8_t in[] = {2, 3, 4};
	struct linked_list * list;

	/* Create linked list: [1, 2, 3, 4] */
	linklist_alloc(&list, sizeof(uint8_t));
	linklist_push_tail(list, &in[0]);
	linklist_push_tail(list, &in[1]);
	linklist_push_tail(list, &in[2]);

	/* Check the elements out of order. */
	any[0] = linklist_any(list, (pred_fn_t) pred_gte1);
	any[1] = linklist_any(list, (pred_fn_t) pred_lte1);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, sizeof(in));

	ck_assert(any[0]);
	ck_assert(!any[1]);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_all_empty)
{
	bool all;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	all = linklist_all(list, (pred_fn_t) pred_gte1);

	ck_assert(!all);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_all_single)
{
	bool all[2];
	uint8_t in = 0;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(in));
	linklist_push_head(list, &in);

	all[0] = linklist_all(list, (pred_fn_t) pred_gte1);
	all[1] = linklist_all(list, (pred_fn_t) pred_lte1);

	ck_assert(!all[0]);
	ck_assert(all[1]);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_all_multiple)
{
	bool all[2];
	uint8_t in[] = {2, 3, 4};
	struct linked_list * list;

	/* Create linked list: [1, 2, 3, 4] */
	linklist_alloc(&list, sizeof(uint8_t));
	linklist_push_tail(list, &in[0]);
	linklist_push_tail(list, &in[1]);
	linklist_push_tail(list, &in[2]);

	/* Check the elements out of order. */
	all[0] = linklist_all(list, (pred_fn_t) pred_gte1);
	all[1] = linklist_all(list, (pred_fn_t) pred_lte1);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, sizeof(in));

	ck_assert(all[0]);
	ck_assert(!all[1]);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_filter_empty)
{
	bool changed;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	changed = linklist_filter(list, (pred_fn_t) pred_gte1);

	ck_assert(!changed);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_filter_single)
{
	bool changed;
	uint8_t in = 0;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(in));
	linklist_push_head(list, &in);

	changed = linklist_filter(list, (pred_fn_t) pred_lte1);
	ck_assert(!changed);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);

	changed = linklist_filter(list, (pred_fn_t) pred_gte1);
	ck_assert(changed);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_filter_multiple)
{
	bool changed;
	uint8_t in[] = {0, 2, 0, 2};
	struct linked_list * list;

	/* Create linked list: [0, 2, 0, 2] */
	linklist_alloc(&list, sizeof(uint8_t));
	linklist_push_tail(list, &in[0]);
	linklist_push_tail(list, &in[1]);
	linklist_push_tail(list, &in[2]);
	linklist_push_tail(list, &in[3]);

	/* filter (> 1) [0, 2, 0, 2] -> [0, 0] */
	changed = linklist_filter(list, (pred_fn_t) pred_gte1);

	ck_assert(changed);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 2);

	/* filter (<= 1) [0, 0] -> [] */
	changed = linklist_filter(list, (pred_fn_t) pred_lte1);

	ck_assert(changed);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_drop_while_empty)
{
	bool changed;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	changed = linklist_drop_while(list, (pred_fn_t) pred_gte1);

	ck_assert(!changed);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_drop_while_single)
{
	bool changed;
	uint8_t in = 0;
	struct linked_list * list;

	/* Singleton List: [0] */
	linklist_alloc(&list, sizeof(in));
	linklist_push_head(list, &in);

	/* dropWhile (> 1) [0] -> [0] */
	changed = linklist_drop_while(list, (pred_fn_t) pred_gte1);

	ck_assert(!changed);
	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);

	/* dropWhile (<= 1) [0] -> [] */
	changed = linklist_drop_while(list, (pred_fn_t) pred_lte1);

	ck_assert(changed);
	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_drop_while_multiple)
{
	bool changed;
	uint8_t in[6] = {0, 0, 2, 2, 0, 0};
	struct linked_list * list;

	/* Create linked list: [0, 0, 2, 2, 0, 0] */
	linklist_alloc(&list, sizeof(uint8_t));
	linklist_push_tail(list, &in[0]);
	linklist_push_tail(list, &in[1]);
	linklist_push_tail(list, &in[2]);
	linklist_push_tail(list, &in[3]);
	linklist_push_tail(list, &in[4]);
	linklist_push_tail(list, &in[5]);

	/* dropWhile (<= 1) [0, 0, 2, 2, 0, 0] -> [2, 2, 0, 0] */
	changed = linklist_drop_while(list, (pred_fn_t) pred_lte1);

	ck_assert(changed);
	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 4);

	/* dropWhile (> 1) [2, 2, 0, 0] -> [0, 0]*/
	changed = linklist_drop_while(list, (pred_fn_t) pred_gte1);

	ck_assert(changed);
	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 2);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_take_while_empty)
{
	bool changed;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	changed = linklist_take_while(list, (pred_fn_t) pred_gte1);

	ck_assert(!changed);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_take_while_single)
{
	bool changed;
	uint8_t in = 0;
	struct linked_list * list;

	/* Singleton List: [0] */
	linklist_alloc(&list, sizeof(in));
	linklist_push_head(list, &in);

	/* takeWhile (<= 1) [0] -> [0] */
	changed = linklist_take_while(list, (pred_fn_t) pred_lte1);

	ck_assert(!changed);
	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);

	/* takeWhile (> 1) [0] -> [] */
	changed = linklist_take_while(list, (pred_fn_t) pred_gte1);

	ck_assert(changed);
	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_take_while_multiple)
{
	bool changed;
	uint8_t in[] = {1, 0, 2};
	struct linked_list * list;

	/* Create linked list: [1, 0, 2] */
	linklist_alloc(&list, sizeof(uint8_t));
	linklist_push_tail(list, &in[0]);
	linklist_push_tail(list, &in[1]);
	linklist_push_tail(list, &in[2]);

	/* takeWhile (<= 1) [1, 0, 2] -> [1, 0] */
	changed = linklist_take_while(list, (pred_fn_t) pred_lte1);

	ck_assert(changed);
	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 2);

	/* dropWhile (> 1) [1, 0] -> [1]*/
	changed = linklist_take_while(list, (pred_fn_t) pred_gte1);

	ck_assert(changed);
	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);

	linklist_free(&list);
}
END_TEST

uint8_t * map_fn(uint8_t * data)
{
	(*data)++;
	return data;
}

uint8_t * map_fn_newptr(uint8_t * data)
{
	uint8_t * n;

	n = malloc(sizeof(*data));
	memcpy(n, data, sizeof(*data));
	(*n)++;

	return n;
}

START_TEST(test_linklist_map_empty)
{
	struct linked_list * list;

	linklist_alloc(&list, 0);

	linklist_map(list, (map_fn_t) map_fn);
	linklist_map(list, (map_fn_t) map_fn_newptr);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_map_single)
{
	uint8_t in = 1;
	uint8_t * out;
	struct linked_list * list;

	/* Create single element list [1] */
	linklist_alloc(&list, sizeof(in));
	linklist_push_head(list, &in);

	/* Map two increment functions over the list. */
	linklist_map(list, (map_fn_t) map_fn); /* [1] -> [2] */
	linklist_map(list, (map_fn_t) map_fn_newptr); /* [2] -> [3] */
	out = linklist_fetch(list, 0);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);

	ck_assert_int_eq(*out, in + 2);

	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_map_multiple)
{
	uint8_t in1 = 1;
	uint8_t in2 = 2;
	uint8_t in3 = 3;
	uint8_t * out1;
	uint8_t * out2;
	uint8_t * out3;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(in1));

	/* list: [1, 2, 3] */
	linklist_push_tail(list, &in1);
	linklist_push_tail(list, &in2);
	linklist_push_tail(list, &in3);

	/* [1, 2, 3] -> [2, 3, 4] */
	linklist_map(list, (map_fn_t) map_fn);
	/* [2, 3, 4] -> [3, 4, 5] */
	linklist_map(list, (map_fn_t) map_fn_newptr);

	out1 = linklist_fetch(list, 0);
	out2 = linklist_fetch(list, 1);
	out3 = linklist_fetch(list, 2);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 3);

	ck_assert_int_eq(*out1, in1 + 2);
	ck_assert_int_eq(*out2, in2 + 2);
	ck_assert_int_eq(*out3, in3 + 2);

	linklist_free(&list);
}
END_TEST

/**
 * foldr_fn() - Right folding function for testing.
 * @c: A constant byte integer
 * @acc: The byte integer currently in the accumulator
 *
 * Subtract the value of *@acc from *@c.  Store the result in @acc, since we
 * know this is the fold accumulator in right folds.  The data structure will
 * know that since the addresses match, the accumulator has already been
 * updated.
 */
int8_t * foldr_fn(const int8_t * c, int8_t * acc)
{
	*acc = (*c) - (*acc);
	return acc;
}

/**
 * foldl_fn() - Left folding function for testing.
 * @acc: The byte integer currently in the accumulator
 * @c: A constant byte integer
 *
 * Subtract the value of *@c from *@acc.  Store the result in @acc, since we
 * know this is the fold accumulator in left folds.  The data structure will
 * know that since the addresses match, the accumulator has already been
 * updated.
 */
int8_t * foldl_fn(int8_t * acc, const int8_t * c)
{
	*acc = (*acc) - (*c);
	return acc;
}

/**
 * generic_fold_fn() - Generic folding function for testing.
 * @a: A constant byte integer
 * @b: A constant byte integer
 *
 * Subtract the value of *@b from *@a.  Store the result in a new pointer, since
 * we do not know ahead of time whether the function will be used in a left or a
 * right fold.  The data structure will know that since the addresses don't
 * match, the accumulator has not been updated, and it will update it and free
 * our new variable automatically.
 */
int8_t * generic_fold_fn(const int8_t * a, const int8_t * b)
{
	int8_t * n;

	n = malloc(sizeof(n));
	*n = (*a) - (*b);

	return n;
}

START_TEST(test_linklist_foldr_empty)
{
	int8_t init = 0;
	int8_t * out1;
	int8_t * out2;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(uint8_t));

	out1 = linklist_foldr(list, (foldr_fn_t) foldr_fn, &init);
	out2 = linklist_foldr(list, (foldr_fn_t) generic_fold_fn, &init);

	ck_assert(out1);
	ck_assert(out2);
	ck_assert_int_eq(*out1, init);
	ck_assert_int_eq(*out2, init);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	free(out1);
	free(out2);
	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_foldr_single)
{
	int8_t in = 1;
	int8_t init = 0;
	int8_t * out1;
	int8_t * out2;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(in));
	linklist_push_head(list, &in);

	out1 = linklist_foldr(list, (foldr_fn_t) foldr_fn, &init);
	out2 = linklist_foldr(list, (foldr_fn_t) generic_fold_fn, &init);

	ck_assert(out1);
	ck_assert_int_eq(*out1, 1);
	ck_assert_int_eq(*out2, 1);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);

	free(out1);
	free(out2);
	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_foldr_multiple)
{
	int8_t in1 = 1;
	int8_t in2 = 2;
	int8_t in3 = 3;
	int8_t init = 0;
	int8_t * out1;
	int8_t * out2;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(int8_t));

	linklist_push_tail(list, &in1);
	linklist_push_tail(list, &in2);
	linklist_push_tail(list, &in3);

	/* foldr (-) 0 [1, 2, 3] -> 2 */
	out1 = linklist_foldr(list, (foldr_fn_t) foldr_fn, &init);
	out2 = linklist_foldr(list, (foldr_fn_t) generic_fold_fn, &init);

	ck_assert(out1);
	ck_assert(out2);
	ck_assert_int_eq(*out1, 2);
	ck_assert_int_eq(*out2, 2);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 3);

	free(out1);
	free(out2);
	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_foldl_empty)
{
	int8_t init = 0;
	int8_t * out1;
	int8_t * out2;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(int8_t));

	out1 = linklist_foldl(list, (foldl_fn_t) foldl_fn, &init);
	out2 = linklist_foldl(list, (foldl_fn_t) generic_fold_fn, &init);

	ck_assert(out1);
	ck_assert(out2);
	ck_assert_int_eq(*out1, init);
	ck_assert_int_eq(*out2, init);

	ck_assert(!list->head);
	ck_assert(!list->tail);
	ck_assert(linklist_null(list));

	free(out1);
	free(out2);
	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_foldl_single)
{
	int8_t in = 1;
	int8_t init = 0;
	int8_t * out1;
	int8_t * out2;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(in));
	linklist_push_head(list, &in);

	/* foldl (-) 0 [1] -> -1 */
	out1 = linklist_foldl(list, (foldl_fn_t) foldl_fn, &init);
	out2 = linklist_foldl(list, (foldl_fn_t) generic_fold_fn, &init);

	ck_assert(out1);
	ck_assert(out2);
	ck_assert_int_eq(*out1, -1);
	ck_assert_int_eq(*out2, -1);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 1);

	free(out1);
	free(out2);
	linklist_free(&list);
}
END_TEST

START_TEST(test_linklist_foldl_multiple)
{
	int8_t in1 = 1;
	int8_t in2 = 2;
	int8_t in3 = 3;
	int8_t init = 0;
	int8_t * out1;
	int8_t * out2;
	struct linked_list * list;

	linklist_alloc(&list, sizeof(int8_t));

	linklist_push_tail(list, &in1);
	linklist_push_tail(list, &in2);
	linklist_push_tail(list, &in3);

	/* foldl (-) 0 [1, 2, 3] -> -6 */
	out1 = linklist_foldl(list, (foldl_fn_t) foldl_fn, &init);
	out2 = linklist_foldl(list, (foldl_fn_t) generic_fold_fn, &init);

	ck_assert(out1);
	ck_assert(out2);
	ck_assert_int_eq(*out1, -6);
	ck_assert_int_eq(*out2, -6);

	ck_assert(list->head);
	ck_assert(list->tail);
	ck_assert_int_eq(list->length, 3);

	free(out1);
	free(out2);
	linklist_free(&list);
}
END_TEST

Suite * linklist_suite(void)
{
	Suite * suite;
	TCase * case_linklist_alloc;
	TCase * case_linklist_null;
	TCase * case_linklist_push_head;
	TCase * case_linklist_push_tail;
	TCase * case_linklist_pop_head;
	TCase * case_linklist_pop_tail;
	TCase * case_linklist_insert;
	TCase * case_linklist_delete;
	TCase * case_linklist_remove;
	TCase * case_linklist_fetch;
	TCase * case_linklist_contains;
	TCase * case_linklist_any;
	TCase * case_linklist_all;
	TCase * case_linklist_filter;
	TCase * case_linklist_drop_while;
	TCase * case_linklist_take_while;
	TCase * case_linklist_map;
	TCase * case_linklist_foldl;
	TCase * case_linklist_foldr;

	suite = suite_create("Linked List");

	case_linklist_alloc = tcase_create("linklist_alloc");
	case_linklist_null = tcase_create("linklist_null");
	case_linklist_push_head = tcase_create("linklist_push_head");
	case_linklist_push_tail = tcase_create("linklist_push_tail");
	case_linklist_pop_head = tcase_create("linklist_pop_head");
	case_linklist_pop_tail = tcase_create("linklist_pop_tail");
	case_linklist_insert = tcase_create("linklist_insert");
	case_linklist_delete = tcase_create("linklist_delete");
	case_linklist_remove = tcase_create("linklist_remove");
	case_linklist_fetch = tcase_create("linklist_fetch");
	case_linklist_contains = tcase_create("linklist_contains");
	case_linklist_any = tcase_create("linklist_any");
	case_linklist_all = tcase_create("linklist_all");
	case_linklist_filter = tcase_create("linklist_filter");
	case_linklist_drop_while = tcase_create("linklist_drop_while");
	case_linklist_take_while = tcase_create("linklist_take_while");
	case_linklist_map = tcase_create("linklist_map");
	case_linklist_foldl = tcase_create("linklist_foldl");
	case_linklist_foldr = tcase_create("linklist_foldr");

	tcase_add_test(case_linklist_alloc, test_linklist_alloc);
	tcase_add_test(case_linklist_null, test_linklist_null_true);
	tcase_add_test(case_linklist_null, test_linklist_null_false);
	tcase_add_test(case_linklist_push_head, test_linklist_push_head_single);
	tcase_add_test(case_linklist_push_head, test_linklist_push_head_multiple);
	tcase_add_test(case_linklist_push_tail, test_linklist_push_tail_single);
	tcase_add_test(case_linklist_push_tail, test_linklist_push_tail_multiple);
	tcase_add_test(case_linklist_pop_head, test_linklist_pop_head_empty);
	tcase_add_test(case_linklist_pop_head, test_linklist_pop_head_single);
	tcase_add_test(case_linklist_pop_head, test_linklist_pop_head_multiple);
	tcase_add_test(case_linklist_pop_tail, test_linklist_pop_tail_empty);
	tcase_add_test(case_linklist_pop_tail, test_linklist_pop_tail_single);
	tcase_add_test(case_linklist_pop_tail, test_linklist_pop_tail_multiple);
	tcase_add_test(case_linklist_insert, test_linklist_insert_single);
	tcase_add_test(case_linklist_insert, test_linklist_insert_multiple);
	tcase_add_test(case_linklist_delete, test_linklist_delete_empty);
	tcase_add_test(case_linklist_delete, test_linklist_delete_single);
	tcase_add_test(case_linklist_delete, test_linklist_delete_multiple);
	tcase_add_test(case_linklist_remove, test_linklist_remove_empty);
	tcase_add_test(case_linklist_remove, test_linklist_remove_single);
	tcase_add_test(case_linklist_remove, test_linklist_remove_multiple);
	tcase_add_test(case_linklist_fetch, test_linklist_fetch_empty);
	tcase_add_test(case_linklist_fetch, test_linklist_fetch_single);
	tcase_add_test(case_linklist_fetch, test_linklist_fetch_multiple);
	tcase_add_test(case_linklist_contains, test_linklist_contains_empty);
	tcase_add_test(case_linklist_contains, test_linklist_contains_single);
	tcase_add_test(case_linklist_contains, test_linklist_contains_multiple);
	tcase_add_test(case_linklist_any, test_linklist_any_empty);
	tcase_add_test(case_linklist_any, test_linklist_any_single);
	tcase_add_test(case_linklist_any, test_linklist_any_multiple);
	tcase_add_test(case_linklist_all, test_linklist_all_empty);
	tcase_add_test(case_linklist_all, test_linklist_all_single);
	tcase_add_test(case_linklist_all, test_linklist_all_multiple);
	tcase_add_test(case_linklist_filter, test_linklist_filter_empty);
	tcase_add_test(case_linklist_filter, test_linklist_filter_single);
	tcase_add_test(case_linklist_filter, test_linklist_filter_multiple);
	tcase_add_test(case_linklist_drop_while, test_linklist_drop_while_empty);
	tcase_add_test(case_linklist_drop_while, test_linklist_drop_while_single);
	tcase_add_test(case_linklist_drop_while, test_linklist_drop_while_multiple);
	tcase_add_test(case_linklist_take_while, test_linklist_take_while_empty);
	tcase_add_test(case_linklist_take_while, test_linklist_take_while_single);
	tcase_add_test(case_linklist_take_while, test_linklist_take_while_multiple);
	tcase_add_test(case_linklist_map, test_linklist_map_empty);
	tcase_add_test(case_linklist_map, test_linklist_map_single);
	tcase_add_test(case_linklist_map, test_linklist_map_multiple);
	tcase_add_test(case_linklist_foldr, test_linklist_foldr_empty);
	tcase_add_test(case_linklist_foldr, test_linklist_foldr_single);
	tcase_add_test(case_linklist_foldr, test_linklist_foldr_multiple);
	tcase_add_test(case_linklist_foldl, test_linklist_foldl_empty);
	tcase_add_test(case_linklist_foldl, test_linklist_foldl_single);
	tcase_add_test(case_linklist_foldl, test_linklist_foldl_multiple);

	suite_add_tcase(suite, case_linklist_alloc);
	suite_add_tcase(suite, case_linklist_null);
	suite_add_tcase(suite, case_linklist_push_head);
	suite_add_tcase(suite, case_linklist_push_tail);
	suite_add_tcase(suite, case_linklist_pop_head);
	suite_add_tcase(suite, case_linklist_pop_tail);
	suite_add_tcase(suite, case_linklist_insert);
	suite_add_tcase(suite, case_linklist_delete);
	suite_add_tcase(suite, case_linklist_remove);
	suite_add_tcase(suite, case_linklist_fetch);
	suite_add_tcase(suite, case_linklist_contains);
	suite_add_tcase(suite, case_linklist_any);
	suite_add_tcase(suite, case_linklist_all);
	suite_add_tcase(suite, case_linklist_filter);
	suite_add_tcase(suite, case_linklist_drop_while);
	suite_add_tcase(suite, case_linklist_take_while);
	suite_add_tcase(suite, case_linklist_map);
	suite_add_tcase(suite, case_linklist_foldr);
	suite_add_tcase(suite, case_linklist_foldl);

	return suite;
}

int main(void)
{
	Suite * suite_linklist;
	SRunner * suite_runner;

	suite_linklist = linklist_suite();

	suite_runner = srunner_create(suite_linklist);
	srunner_run_all(suite_runner, CK_NORMAL);
	srunner_free(suite_runner);

	return 0;
}
