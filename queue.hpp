
typedef struct QNode
{
    const void *data = 0;
    struct QNode *next = 0;
} QNode;

typedef struct Queue
{
    int size = 0;
    QNode *root = 0;
    QNode *tail = 0;
} Queue;

void enQ(Queue *queue, const void *str);
char *deQ(Queue *queue);
char *peek(Queue *queue);
void destroyQ(Queue *queue);
void createQ(Queue **queue);