#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep(x * 1000)
#endif

#define miliseconds 1000

void hidecursor();
void movecursortop(int pos);
void showcursor();
void clearscreen();

void render_array(int *arr, int size, int min, int i, int j);

int main()
{
    hidecursor();

    int arr[] = {9, 1, 8, 2, 7, 3, 6, 4, 5};
    int size = sizeof(arr) / sizeof(int);

    render_array(arr, size, 0, -1, 0);
    for (int i = 0; i < size; i++)
    {
        int min = i;

        for (int j = i; j < size; j++)
        {
            render_array(arr, size, min, i, j);
            if (arr[min] > arr[j])
            {
                min = j;
            }
            Sleep(1000);
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
    render_array(arr, size, size - 1, size, size);

    printf("Press any key to clear         \n");
    char k;
    scanf("%c", &k);
    showcursor();
    clearscreen();
}

void hidecursor()
{
    printf("\e[?25l");
}

void movecursortop(int pos)
{
    printf("\e[%iA", pos);
}

void showcursor()
{
    printf("\e[?25h");
}

void clearscreen()
{
    printf("\e[2J\e[H");
}

void render_array(int *arr, int size, int min, int i, int j)
{
    printf("Selection Sort visualization!\n\n");
    for (int k = 0; k < size; k++)
    {
        if (k == min)
            printf("MIN -> ");
        else
            printf("       ");
        printf("%d", arr[k]);

        if (k < i)
            printf("[X]\n");
        else if (k == j)
            printf(" <-\n");
        else
            printf("   \n");
    }
    movecursortop(size + 2);
}