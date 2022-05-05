#define t_elem_list void*
#define bool int
#define true 1
#define false 0

typedef struct list_node {
  t_elem_list value;
  struct list_node *next;
} list_node;

typedef struct list {
  list_node *head;
  int maxsize;
  int count;
} list;


list *list_new(int maxsize);

bool list_isempty(list *L);

bool list_isfull(list *L);

int list_length(list *L);

t_elem_list list_get(list *L, int index);

int list_search(list *L, t_elem_list elem);

void list_insert(list *L, int index, t_elem_list elem);

void list_delete(list *L, int index);

void list_traverse(list *L, bool look(t_elem_list elem, int index, void *ctx), void *ctx);