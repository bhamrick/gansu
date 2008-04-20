#ifndef COMMON_H
#define COMMON_H

typedef	unsigned	int	u32int;
typedef	signed		int	s32int;
typedef	unsigned	short	u16int;
typedef	signed		short	s16int;
typedef	unsigned	char	u8int;
typedef	signed		char	s8int;

extern u32int end;

void register_isr(int,void*);
u32int placement_address;
void ckprintf(char*,...);
u32int kmalloc_int(u32int,int,u32int*);
u32int kmalloc(u32int);
u32int kmalloc_a(u32int);
u32int kmalloc_p(u32int,u32int*);
u32int kmalloc_ap(u32int,u32int*);
void bzero(void*,u32int);
void halt();

#endif
