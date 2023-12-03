#include <stdio.h>
#include <stdlib.h>

#include "util.h"

#define NUM 30

struct foo
{
	unsigned long base;
	unsigned long curr;
};

struct foo *list;
size_t num,max;

int compar(const void *va,const void *vb)
{
	const struct foo *a=va;
	const struct foo *b=vb;

	if(a->curr < b->curr)
		return -1;
	else if(a->curr==b->curr)
		return 0;
	else
		return 1;
}

void grow(void)
{
	if(num<max)
		return;
	list=xrealloc(list,2*max*sizeof *list);
	max*=2;
}

int main(void)
{
	struct foo t;
	size_t next=3;
	size_t count=0;

	list=xmalloc(sizeof *list);
	num=0;
	max=1;

	t.base=2;
	t.curr=4;
	list[num++]=t;

	t.base=3;
	t.curr=9;
	grow();
	list[num++]=t;

	while(count < NUM)
	{
		qsort(list,num,sizeof *list,compar);

		while(count_digits(list[0].curr,10)*9 > next)
		{
			next++;
			t.base=next;
			t.curr=next*next;
			grow();
			list[num++]=t;
			qsort(list,num,sizeof *list,compar);
		}

		if(sum_digits(list[0].curr,10)==list[0].base)
		{
			if(list[0].curr >= 10)
			{
				printf("%lu: %lu (%lu)\n",++count,list[0].curr,list[0].base);
			}
		}

		t=list[0];
		list[0].curr*=list[0].base;
		if(list[0].curr/list[0].base!=t.curr)
		{
			/*We don't need to panic quite yet.  We might
			    have other values in the queue that we haven't
			    run out of bits for.
			*/
			list[0]=list[--num];
		}
		if(num==0)
		{
			fputs("Need wider longs!\n",stderr);
			abort();
		}
	}

	return 0;
}