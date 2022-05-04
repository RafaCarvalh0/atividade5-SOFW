#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int size, final_sum;
int i = 0, j = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *add(void *arg);

int main()
{
    scanf("%d", &size);
    int matriz[size][size];

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            scanf("%d", &matriz[i][j]);
    }

    pthread_t threads[size];

    for (i = 0; i < size; i++)
    {
        int *line_values = malloc(size * sizeof(int));

        for (j = 0; j < size; j++)
            line_values[j] = matriz[i][j];

        if (pthread_create(&(threads[i]), NULL, add, (void *)line_values))
            printf("ERRO AO CRIAR A MATRIZ");
    }

    for (i = 0; i < size; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("O resultado final é: %d", final_sum);
    return 0;
}

void *add(void *arg)
{
    int i = 0;

    pthread_mutex_lock(&mutex);
    int *line_values = (int *)arg;

    for (i = 0; i < size; i++)
    {
        final_sum += line_values[i];
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}
