#define T_SL 0		//SL
#define S_EPS 0		//EPS
#define S_DS 1		//DS
#define D_DEF 0		//def
#define L_EPS 0		//EPS
#define L_CL 1		//CL
#define B_BEGIN	0	//begin
#define B_C 1		//C
#define C_PRINT 0		//print
#define C_READ 1		//read
#define C_SET 2		//set
#define C_IF 3		//if
#define C_WHILE 4		//while
#define E_ID 0		//id
#define E_NUM 1		//num
#define E_ADD 2		//add
#define E_SUB 3		//sub
#define E_EQ 4		//eq
#define E_LESS 5	//less
#define LENG 1000
struct T_t{
	int kind;
	struct S_t *s;
	struct L_t *l;
};
struct S_t{
	int kind;
	struct D_t *d;
	struct S_t *s;
};
struct D_t{
	int kind;
	char str[LENG];
	struct E_t *e;
};
struct L_t{
	int kind;
	struct C_t *c;
	struct L_t *l;
};
struct B_t{
	int kind;
	struct L_t *l;
	struct C_t *c;
};
struct C_t{
	int kind;
	char str[LENG];
	struct E_t *e;
	struct B_t *b;
	struct B_t *b_left;
	struct B_t *b_right;
};
struct E_t{
	int kind;
	char str[LENG];
	struct E_t *e_left;
	struct E_t *e_right;
};
