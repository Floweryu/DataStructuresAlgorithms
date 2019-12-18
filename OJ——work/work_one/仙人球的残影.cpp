#include <stdio.h>
int main()
{
    int N, i, j;
    int a[10][10];
    while (scanf ("%d", &N) != EOF)
    {
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
            {
                a[i][j] = 0;
            }
        for (j = 0; j < N; j++)
        {
            a[0][j] = j + 1;
        }
        for (i = 1; i < N; i++)
        {
            a[i][N - 1] = N + i;
        }
        for (j = N - 2; j >= 0; j--)
        {
            a[N - 1][j] = 2 * N + N - 2 - j;
        }
        for (i = N - 2; i >= 1; i--)
        {
            a[i][0] = a[N - 1][0] + N - 1 - i;
        }
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (!a[i][j])
                    printf ("   ");
                else
                    printf ("%3d", a[i][j]);
            }
            printf ("\n");
        }
    }
    return 0;
}
