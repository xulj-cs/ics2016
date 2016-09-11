#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

void init_wp_pool() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_pool[i].NO = i;
		wp_pool[i].next = &wp_pool[i + 1];
	}
	wp_pool[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
void sort(WP *first)
{
	if(first==NULL)
		return ;
	WP *p=first;
	for(;p->next!=NULL;p=p->next)
	{
		WP *pmin=p;
		WP *q=p->next;
		for(;q!=NULL;q=q->next)
		{
			if(pmin->NO>q->NO)
				pmin=q;
			
		}
		if(pmin!=p)
		{
			char t_e[64];
			strcpy(t_e,p->e);
			strcpy(p->e,pmin->e);
			strcpy(pmin->e,t_e);

			int t_no;
			t_no=p->NO;
			p->NO=pmin->NO;
			pmin->NO=t_no;

			uint32_t t;
			t=p->old_result;
			p->old_result=pmin->old_result;
			pmin->old_result=t;	
		}
	}
	
}
int new_wp(char *e,uint32_t result)
{
	if(free_==NULL)
		assert(0);
	WP *p=free_;
	free_=free_->next;

	p->next=head;
	head=p;
	strcpy(p->e,e);
	p->old_result=result;
	sort(head);

	return p->NO;
}

bool free_wp(int no)
{
	WP* p,*q;
	for(p=head,q=p;p!=NULL;q=p,p=p->next)
	{
		if(p->NO==no)
			break;
		
	}
	if(p==NULL)
		return false;
	else
	{
		if(p!=q)
			q->next=p->next;
		else
			head=NULL;
		
		p->next=free_;
		free_=p;
		sort(free_);
		return true;	
	}
}


