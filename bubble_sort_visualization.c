#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep(x * 1000)
#else
#include <unistd.h>
#endif

#define second 1

void hidecursor();
void movecursortop(int pos);
void showcursor();
void clearscreen();

void render_array(int *arr, int size, int pos1, int pos2);
int largest_num(int *arr, int size);

int main()
{
    hidecursor();

    // Main content //
    int arr[] = {5, 1, 9, 6, 4, 2, 7, 3, 8};
    int size = sizeof(arr) / sizeof(int);

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            render_array(arr, size, j, j + 1);

            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            sleep(second);
        }
    }

    printf("Press any key to clear     ");
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

int largest_num(int *arr, int size)
{
    int largest = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (largest < arr[i])
            largest = arr[i];
    }
    return largest;
}

void render_array(int *arr, int size, int pos1, int pos2)
{
    int max_length = largest_num(arr, size);

    printf("Bubble sort visualization\n\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < arr[i]; j++)
        {
            printf("#");
        }
        printf(" - %d", arr[i]);

        for (int j = arr[i]; j < max_length; j++)
            printf(" ");

        if (i == pos1 && i + 1 == pos2)
        {
            printf("<- ");
            if (arr[pos1] > arr[pos2])
                printf("swap[%d<->%d]", arr[pos1], arr[pos2]);
        }
        else
            printf("              ");
        printf("\n");
    }

    movecursortop(size + 2);
}