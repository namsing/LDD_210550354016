#define MAGIC_NUMBER '0'

#define ADD _IOWR(MAGIC_NUMBER, 8, int)
#define SUB _IOWR(MAGIC_NUMBER, 9, int)
#define MUL _IOWR(MAGIC_NUMBER, 10, int)
#define DIV _IOWR(MAGIC_NUMBER, 11, int)
