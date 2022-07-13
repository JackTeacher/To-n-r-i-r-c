#include <stdio.h>
#include <stdlib.h>
#define INF 1000000

void Ford_Bellman(int CountApex, int **SourceMatrix, int Start, int End)
{
    int *MinChek;//Mảng trước của đỉnh
    int *MinPath;//Xuất mảng với khoảng cách đến tất cả các đỉnh
    int *MinWay;//Mảng đầu ra với đường chuyển động
    int i, j, k, l;
    int    count = 0;


    MinPath = (int *)malloc(CountApex * sizeof(int));
    if (MinPath == NULL)
    {
        printf("Error MinPath");
        return ;
    }

    for (i = 0; i < CountApex; i++)
        MinPath[i] = INF;//Không có đường dẫn tối thiểu nào đến đỉnh khi bắt đầu

    MinPath[Start] = 0;//Khoảng cách tối thiểu từ điểm xuất phát đến điểm bắt đầu là 0

    i = 0;// điền vào các phần tử cần thiết của ma trận với số vô hạn
    while (i < CountApex)
    {
        j = 0;
        while (j < CountApex)
        {
            if (SourceMatrix[i][j] == 999)
                SourceMatrix[i][j] = INF;
            j++;
        }
        i++;
    }

    //tạo một mảng các đỉnh tiền nhiệm ban đầu
    MinChek = (int *)malloc (CountApex * sizeof(int));
    if (MinChek == NULL)
    {
        printf("Error MinChek");
        return ;
    }
    i = 0;
    while (i < CountApex)
    {
        //đầu tiên chúng ta điền vào mảng với một giá trị không thể có của các đỉnh
        MinChek[i] = -1;
        i++;
    }

    for (k = 0; k < CountApex; k++)
    {
        for (i = 0; i < CountApex; ++i)
        {
            for (j = 0; j < CountApex; ++j)
            {
                if (SourceMatrix[i][j] != 0) //Nếu đỉnh đó có giá trị chưa được thăm
                    if (MinPath[j] > MinPath[i] + SourceMatrix[i][j])
                    {
                        MinPath[j] = MinPath[i] + SourceMatrix[i][j];
                        MinChek[j] = i;//Điền vào mảng các giá trị đỉnh trước đó
                    }
            }
        }
    }
    for (l = 0; l < CountApex; l++)//In ra với kết quả là đường đi ngắn nhất
                printf ("%d ", MinPath[l]);
            printf("\n");

    for (l = 0; l < CountApex; l++)//Kết quả in của đỉnh tiền nhiệm
                printf ("%d ", MinChek[l]);
            printf("\n");

    //Tạo một mảng cho quỹ đạo đường đi
    MinWay = (int *)malloc(sizeof(int) * CountApex);
    if (MinWay == NULL)
    {
        printf("Error MinWay");
        return ;
    }
    i = 0;
    while (i < CountApex)
    {
        //đầu tiên chúng ta điền vào mảng với một giá trị không thể có của các đỉnh
        MinWay[i] = -1;
        i++;
    }

    i = 0;
    int u = End;//Tạo một biến riêng biệt cho các giá trị cuối cùng
    while (MinChek[u] != Start)
    {
        MinWay[i] = u;
        u = MinChek[u];
        if (u == -1)
        {
            printf("Duong di khong duoc tao ra!");
            break;
        }
        i++;
    }
    //đưa vào mảng giá trị cuối cùng từ mảng của các giá trị trước đó
    if (MinChek[u] == Start)
    {
        MinWay[i] = u;
        i++;
    }
    //Thêm giá trị cuối cùng
    MinWay[i] = Start;

    for (l = 0; l < CountApex; l++)//In ra đường đi
                printf ("%d ", MinWay[l]);
            printf("\n");

    int *RezWay;//Mảng đường đi ở dạng tối giản nhất
    int SizeWay = 0;//Số phần tử trong mảng kết quả
    while (MinWay[SizeWay] != -1)
        SizeWay++;
    RezWay = (int *)malloc(sizeof(int) * SizeWay);
    if (RezWay == NULL)
    {
        printf("Error RezWay");
        return ;
    }
    i = SizeWay - 1;
    l = 0;
    while (i >= 0)
    {
        RezWay[i] = MinWay[l];
        i--;
        l++;
    }
    for (l = 0; l != SizeWay; l++)//Bản in kết quả ở dạng tối giản
                printf ("%d ", RezWay[l]);
            printf("\n");
    printf ("%d\n", MinPath[End]);//Bản in giá trị đường đi ngắn nhất
}

int main()
{
    int apex;//Điểm bắt đầu
    int end_apex;//Điểm kết thúc
    int CountApex;//số đỉnh trong một đồ thị
    int **mputh;//ma trận đầu vào với trọng số của các cạnh
    int i, j = 0;
    float start, end;
    FILE *in;
    char filename[20];

    //Mở tệp ma trận đầu vào của thuật toán
    printf ("Ten cua tep: ");
    scanf("%s", filename);
    in = fopen("test1.txt", "r");

    if (!in)
        printf("Error!");
    else
        printf("Doc ma tran!\n");

    //phần tử đầu tiên của tệp cho biết số đỉnh đồ thị
    fscanf(in, "%d", &CountApex);
    //phân bổ không gian bộ nhớ cần thiết cho ma trận
    mputh = (int **)malloc(CountApex * sizeof(int *));//Cột con trỏ
    for (int i = 0; i < CountApex; i++)//Bộ nhớ cho mỗi hàng của ma trận
        mputh[i] = (int *)malloc(CountApex * sizeof(int));
    //lấp đầy bộ nhớ ma trận đã tạo bằng các giá trị từ tệp
    for (i = 0; i < CountApex; i++)
    {
        for (j = 0; j < CountApex; j++)
            fscanf(in, "%d", &mputh[i][j]);
    }

    printf("Doc thanh cong\n");
    printf("Doc dinh bat dau: ");
    scanf("%d", &apex);//Đọc đỉnh bắt đầu
    printf("Doc dinh ket thuc: ");
    scanf("%d", &end_apex);//Đọc đỉnh kết thúc
    Ford_Bellman(CountApex, mputh, apex, end_apex);
    return 0;
}
