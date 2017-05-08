/*
 * Copyright (c) 2016 Intel Corporation
 * Author: Andi Kleen
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
/* Simple HLE spinlock */

#include "../inc/mutex_type.h"
#include "../inc/common.h"
#include "../inc/hle_emulation.h"

int mutex_create(mutex_t *m)
{
  //m->lock = UNLOCKED;
  return SUCCESS_RETVAL; 
}

void mutex_lock(mutex_t *m)
{
  while ((int)__hle_acquire_sub_fetch4((unsigned *)(m->lock), 1) < 0) {
    do
      asm volatile("pause":::"memory");
    while ((m->lock)!= 1);
  }
}

void mutex_unlock(mutex_t *m)
{
  __hle_release_store_n4((unsigned *)m->lock, 1);
}