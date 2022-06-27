#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//队列结点
struct queuenode
{
    int data;
    struct queuenode* next;
};

//队列
struct queue
{
    struct queuenode* front;
    struct queuenode* rear;
};

//重命名
typedef struct queue* Queue;

Queue MakeQueueNull();//建立空队列
void IsPrintEnd(int* A, int* B, int n);//判断是否打印数组
void PrintArray(int* array, int n);//打印数组
void EnQueue(int data, Queue Q);//进队
void DeQueue(Queue Q);//出队
int Front(Queue Q);//返回队首元素
int IsQueueEmpty(Queue Q);//判断队列是否为空
void Showmenu();//显示菜单
void QuickSort(int i, int j, int* array);//快速排序
int FindPivot(int i, int j, int* array);//找到基准元素
int Partition(int i, int j, int pivot, int* array);//分组
void RadixSort(int figure, int* array, int n);//基数排序
int Radix(int k, int num);//返回num的第k位数字
void Concatenate(Queue Q1, Queue Q2);//将两个队列连接起来
void Merge(int s, int m, int t, int* a1, int* a2);//将两个有序数组合到一起
void MergePass(int n, int h, int* a1, int* a2);//将h长的合成为2h长的
void MergeSort(int* array, int n);//归并排序
void BubbleSort(int* array, int n);//冒泡排序
void SelectSort(int* array, int n);//直接选择排序
void InsertSort(int* array, int n);//插入排序
void HeapSort(int* array, int n);//堆排序
void PushDown(int k, int* array, int n);//下移
void ShellSort(int* array, int n);//希尔排序

int main()
{
    clock_t start, finish;//用于计时
    double totaltime;
    int count;
    printf("请输入生成随机数(0~1000000)的个数：\n");
    scanf("%d", &count);
    srand((unsigned)time(NULL));
    int* B = malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++)
    {
        B[i] = rand() % 1000001;
    }
    printf("生成成功!\n");
    system("pause");
    system("cls");
    int ch;
    while (1)
    {
        int flag = 0;
        int* A = malloc(sizeof(int) * count);
        for (int i = 0; i < count; i++)
        {
            A[i] = B[i];
        }
        Showmenu();
        fflush(stdin);
        scanf("%d", &ch);
        switch (ch)
        {
        case 0:
            system("pause");
            return 0;
        case 1:
            start = clock();
            QuickSort(0, count - 1, A);
            finish = clock();
            totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("用时:%lfs\n", totaltime);
            break;
        case 2:
            start = clock();
            RadixSort(7, A, count);
            finish = clock();
            totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("用时:%lfs\n", totaltime);
            break;
        case 3:
            start = clock();
            HeapSort(A, count);
            finish = clock();
            totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("用时:%lfs\n", totaltime);
            break;
        case 4:
            start = clock();
            BubbleSort(A, count);
            finish = clock();
            totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("用时:%lfs\n", totaltime);
            break;
        case 5:
            start = clock();
            SelectSort(A, count);
            finish = clock();
            totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("用时:%lfs\n", totaltime);
            break;
        case 6:
            start = clock();
            InsertSort(A, count);
            finish = clock();
            totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("用时:%lfs\n", totaltime);
            break;
        case 7:
            start = clock();
            ShellSort(A, count);
            finish = clock();
            totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("用时:%lfs\n", totaltime);
            break;
        case 8:
            start = clock();
            MergeSort(A, count);
            finish = clock();
            totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("用时:%lfs\n", totaltime);
            break;
        case 9:
            printf("请输入生成随机数(0~100000)的个数：\n");
            scanf("%d", &count);
            srand((unsigned)time(NULL));
            int* B = malloc(sizeof(int) * count);
            for (int i = 0; i < count; i++)
            {
                B[i] = rand() % 100001;
            }
            printf("生成成功!\n");
            flag = 1;
            system("pause");
            system("cls");
            break;
        }
        if (!flag) {
            IsPrintEnd(A, B, count);
            system("pause");
            system("cls");
        }
    }
    return 0;
}

void Showmenu()
{
    printf("-------------------\n");
    printf("1、快速排序\n");
    printf("2、基数排序\n");
    printf("3、堆排序\n");
    printf("4、冒泡排序\n");
    printf("5、直接选择排序\n");
    printf("6、插入排序\n");
    printf("7、希尔排序\n");
    printf("8、归并排序\n");
    printf("9、重新生成随机数\n");
    printf("0、退出程序\n");
    printf("-------------------\n");
}

void IsPrintEnd(int* A, int* B, int n)
{
    printf("是否显示排序结果？（Y or N）\n");
    char ch;
    fflush(stdin);
    scanf("%c", &ch);
    switch (ch)
    {
    case 'Y':
    case 'y':
        printf("排序前：\n");
        PrintArray(B, n);
        printf("排序后：\n");
        PrintArray(A, n);
        break;
    }
}

void PrintArray(int* array, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

Queue MakeQueueNull()
{
    Queue Q = malloc(sizeof(struct queue));
    Q->front = malloc(sizeof(struct queuenode));
    Q->front->next = NULL;
    Q->rear = Q->front;
    return Q;
}

void EnQueue(int data, Queue Q)
{
    Q->rear->next = malloc(sizeof(struct queuenode));
    Q->rear = Q->rear->next;
    Q->rear->next = NULL;
    Q->rear->data = data;
}

void DeQueue(Queue Q)
{
    struct queuenode* p = Q->front->next;
    if (p->next == NULL)
    {
        Q->rear = Q->front;
    }
    Q->front->next = p->next;
    free(p);
}

int IsQueueEmpty(Queue Q)
{
    if (Q->front == Q->rear)
    {
        return 1;
    }
    return 0;
}

int Front(Queue Q)
{
    return Q->front->next->data;
}

void QuickSort(int i, int j, int* array)
{
    int pivot;
    int k;
    int pivotindex = FindPivot(i, j, array);
    if (pivotindex != -1)
    {
        pivot = array[pivotindex];
        k = Partition(i, j, pivot, array);
        QuickSort(i, k - 1, array);
        QuickSort(k, j, array);
    }
}

int Partition(int i, int j, int pivot, int* array)
{
    int l, r;
    do
    {
        for (l = i; array[l] < pivot; l++);
        for (r = j; array[r] >= pivot; r--);
        if (l < r)
        {
            int temp = array[l];
            array[l] = array[r];
            array[r] = temp;
        }
    } while (l <= r);
    return l;
}

int FindPivot(int i, int j, int* array)
{
    int firstkey = array[i];
    int k;
    for (k = i + 1; k <= j; k++)
    {
        if (array[k] > firstkey)
        {
            return k;
        }
        else if (array[k] < firstkey)
        {
            return i;
        }
    }
    return -1;
}

int Radix(int k, int num)
{
    num = num % (int)pow(10, k);
    num = num / pow(10, k - 1);
    return num;
}

void Concatenate(Queue Q1, Queue Q2)
{
    Q1->rear->next = Q2->front->next;
    Q1->rear = Q2->rear;
}

void RadixSort(int figure, int* array, int n)
{
    Queue A = MakeQueueNull();
    for (int i = 0; i < n; i++)
    {
        EnQueue(array[i], A);
    }
    for (int pass = 1; pass <= figure; pass++)
    {
        Queue Q[10];
        for (int i = 0; i < 10; i++)
        {
            Q[i] = MakeQueueNull();
        }
        while (!IsQueueEmpty(A))
        {
            int temp = Front(A);
            DeQueue(A);
            EnQueue(temp, Q[Radix(pass, temp)]);
        }
        for (int j = 1; j < 10; j++)
        {
            if (!IsQueueEmpty(Q[j]))
            {
                Concatenate(Q[0], Q[j]);
            }
        }
        A = Q[0];
    }
    int k = 0;
    while (!IsQueueEmpty(A))
    {
        array[k++] = Front(A);
        DeQueue(A);
    }
}

void Merge(int s, int m, int t, int* a1, int* a2)
{
    int i = s;
    int j = m + 1;
    int k = s;
    while (i <= m && j <= t)
    {
        a2[k++] = a1[i] < a1[j] ? a1[i++] : a1[j++];
    }
    while (i <= m)
    {
        a2[k++] = a1[i++];
    }
    while (j <= t)
    {
        a2[k++] = a1[j++];
    }
}

void MergePass(int n, int h, int* a1, int* a2)
{
    int i;
    for (i = 0; i + 2 * h <= n; i += 2 * h)
    {
        Merge(i, i + h - 1, i + 2 * h - 1, a1, a2);
    }
    if (i + h - 1 < n)
    {
        Merge(i, i + h - 1, n, a1, a2);
    }
    else
    {
        for (int j = i; j <= n; j++)
        {
            a2[j] = a1[j];
        }
    }
}

void MergeSort(int* array, int n)
{
    int h = 1;
    int* temp = malloc(sizeof(int) * n);
    while (h <= n)
    {
        MergePass(n - 1, h, array, temp);
        h *= 2;
        MergePass(n - 1, h, temp, array);
        h *= 2;
    }
}

void BubbleSort(int* array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (array[j] < array[j - 1])
            {
                int temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
            }
        }
    }
}

void SelectSort(int* array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = array[i];
        int k = i;
        for (int j = i + 1; j < n; j++)
        {
            if (array[j] < min)
            {
                min = array[j];
                k = j;
            }
        }
        int temp = array[i];
        array[i] = array[k];
        array[k] = temp;
    }
}

void InsertSort(int* array, int n)
{
    for (int i = 0; i < n; i++)
    {
        int j = i;
        while (j != 0 && array[j] < array[j - 1])
        {
            int temp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = temp;
            j--;
        }
    }
}

void PushDown(int k, int* array, int n)
{
    int parent = k;
    int child = 2 * k;
    while (parent <= n / 2)
    {
        if (parent == n / 2 && n % 2 == 0)
        {
            if (array[parent] > array[child])
            {
                int temp = array[parent];
                array[parent] = array[child];
                array[child] = temp;
            }
            break;
        }
        else
        {
            if (array[child] > array[child + 1])
            {
                child++;
            }
            if (array[parent] > array[child])
            {
                int temp = array[parent];
                array[parent] = array[child];
                array[child] = temp;
                parent = child;
                child *= 2;
            }
            else
            {
                break;
            }
        }
    }
}

void HeapSort(int* array, int n)
{
    int* A = malloc(sizeof(int) * n + 1);
    for (int i = 0; i < n; i++)
    {
        A[i + 1] = array[i];
    }
    for (int i = n / 2; i >= 1; i--)
    {
        PushDown(i, A, n);
    }
    for (int i = 0; i < n - 1; i++)
    {
        int temp = A[1];
        A[1] = A[n - i];
        A[n - i] = temp;
        PushDown(1, A, n - i - 1);
    }
    for (int i = 0; i < n; i++)
    {
        array[i] = A[n - i];
    }
}

void ShellSort(int* array, int n)
{
    for (int d = n / 2; d >= 1; d /= 2)
    {
        for (int i = d; i < n; i++)
        {
            int j = i - d;
            int pre = i;
            while (j >= 0 && array[j] > array[pre])
            {
                int temp = array[j];
                array[j] = array[pre];
                array[pre] = temp;
                pre = j;
                j = j - d;
            }
        }
    }
}
