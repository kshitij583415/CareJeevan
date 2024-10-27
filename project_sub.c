#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <conio.h>

typedef struct edges
{
    int u; // starting node
    int v; // ending node
    int w; // edge weight
} edges;

typedef struct hospitals
{
    char name[100];
} hospitals;

// priority queue that will store nodes and weights
typedef struct priority_queue
{
    int node;
    int wt;
} priority_queue;

int string_to_num(char str[])
{
    // this function converts a string to its equivalent integer value
    int num = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        num = (num * 10) + (str[i] - 48);
    }
    return num;
}
void display(int **arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", arr[i][j]);
        }

        printf("\n");
    }
}

int index_bg(char bgp[])
{

    if (strcmp(bgp, "A+") == 0)
    {
        return 0;
    }
    if (strcmp(bgp, "A-") == 0)
    {
        return 1;
    }
    if (strcmp(bgp, "B+") == 0)
    {
        return 2;
    }
    if (strcmp(bgp, "B-") == 0)
    {
        return 3;
    }
    if (strcmp(bgp, "AB+") == 0)
    {
        return 4;
    }
    if (strcmp(bgp, "AB-") == 0)
    {
        return 5;
    }
    if (strcmp(bgp, "O+") == 0)
    {
        return 6;
    }
    if (strcmp(bgp, "O-") == 0)
    {
        return 7;
    }
    else
        return -1;
}
int min_distance(int *dis, int *temp, int v)
{
    int i, min = INT_MAX, index;
    for (i = 0; i < v; i++)
    {
        if (temp[i] == 0 && dis[i] <= min)
        {
            min = dis[i];
            index = i;
        }
    }
    return index;
}
void display_alldj(int *dis, int *parr, int v, int index, int **barr, int *oarr, int units, int src, hospitals p[], int sub_choice)
{
    int i;
    int flag = 1;
    for (i = 0; i < v; i++)
    {
        if (sub_choice == 1)
        {
            if (barr[i][index] >= units)
            {
                if (i == v || i == v - 1)
                    printf("%s\t%d\t\t%d\n", p[i + 1].name, dis[i], units * parr[i]);
                else
                    printf("%s\t\t%d\t\t\t%d\n", p[i + 1].name, dis[i], units * parr[i]);

                flag = 0;
            }
        }
        if (sub_choice == 2 || sub_choice == 3)
        {
            if (oarr[i] >= units)
            {
                if (i == v || i == v - 1)
                    printf("%s\t%d\t\t\t%d\n", p[i + 1].name, dis[i], units * parr[i]);
                else
                    printf("%s\t\t%d\t\t\t%d\n", p[i + 1].name, dis[i], units * parr[i]);

                flag = 0;
            }
        }
    }
    if (flag == 1)
    {
        if (sub_choice == 1)
            printf("\nREQUIRED BLOOD IS NOT AVAILABLE !\n\n");
        else
            printf("NOT AVAILABLE \n");
    }
}
void display_dj(int *dis, int *parr, int v, int index, int **barr, int *oarr, int units, int src, hospitals p[], int sub_choice)
{
    int i;
    int min = INT_MAX;
    int j = 0;
    int flag = 0;
    for (i = 0; i < v; i++)
    {
        if (sub_choice == 1)
        {
            if (barr[i][index] >= units)
            {
                if (min > dis[i])
                {
                    min = dis[i];
                    j = i;
                }
                flag = 1;
            }
        }
        if (sub_choice == 2 || sub_choice == 3)
        {
            if (oarr[i] >= units)
            {
                if (min > dis[i])
                {
                    min = dis[i];
                    j = i;
                }
                flag = 1;
            }
        }
    }
    if (flag == 1)
    {
        if (sub_choice == 1)
        {
            printf("\n\nblood is available !\n\n");
            printf("Source \t\tDestination\t\tDistance\tPrice\n");
            printf("%s \t\t %s \t\t %d\t\t%d \n", p[src + 1].name, p[j + 1].name, dis[j], (units * parr[j]));
        }
        if (sub_choice == 3 || sub_choice == 2)
        {
            printf("\n\n AVAILABLE !\n\n");
            printf("Source \t\tDestination\t\tDistance\tPrice\n");
            printf(" %s \t  %s \t\t %d \t\t %d \n", p[src + 1].name, p[j + 1].name, dis[j], (units * parr[j]));
        }
    }
    else
    {
        printf("not available !\n");
    }
}
void dj(int **a, int **barr, int *parr, int *oarr, int v, int src, int index, int units, int c, hospitals p[], int sub_choice)
{
    int dis[v], i;
    int flag = 0;
    int temp[v];
    for (i = 0; i < v; i++)
    {
        dis[i] = INT_MAX;
        temp[i] = 0;
    }
    dis[src] = 0;
    for (i = 0; i < v - 1; i++)
    {
        int u = min_distance(dis, temp, v);
        temp[u] = 1;
        int j;
        for (j = 0; j < v; j++)
        {
            if (temp[j] == 0 && a[u][j] && dis[u] != INT_MAX && dis[u] + a[u][j] <= dis[j])
                dis[j] = dis[u] + a[u][j];
        }
    }
    if (sub_choice == 1)
    {
        if (c == 2)
            display_dj(dis, parr, v, index, barr, oarr, units, src, p, sub_choice);
        if (c == 3)
            display_alldj(dis, parr, v, index, barr, oarr, units, src, p, sub_choice);
    }
    if (sub_choice == 2 || sub_choice == 3)
    {
        if (c == 2)
            display_dj(dis, parr, v, index, barr, oarr, units, src, p, sub_choice);
        if (c == 3)
            display_alldj(dis, parr, v, index, barr, oarr, units, src, p, sub_choice);
    }
}

void flloyd_warshall(int **arr, int n, hospitals p[])
{
    // to find the shortest path between all two places on the map

    // we need to do some pre-processing for flloyd warshall's algorithm
    int **graph = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        graph[i] = (int *)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                graph[i][j] = 0;
            else if (arr[i][j] != 0)
            {
                graph[i][j] = arr[i][j];
            }
            else if (arr[i][j] == 0)
            {
                graph[i][j] = 772681; // this denotes infinty in my case
            }
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int via_prev_path = graph[i][k] + graph[k][j];
                if (via_prev_path < graph[i][j])
                {
                    graph[i][j] = via_prev_path;
                }
            }
        }
    }
    // so the array named as graph will have all pair shortest path
    // system("clear");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("\nShortest path between %s to %s is %d KM.\n", p[i + 1].name, p[j + 1].name, graph[i][j]);
        }
        printf("\n");
    }
}
void platoxy_queries(int **arr, int **barr, int *parr, int *oarr, int n, edges edg[], int e, hospitals p[], int sub_choice)
{
    while (1)
    {

        printf("press :\n");
        printf("1 - know all the registered hopitals \n");
        printf("2 - know the shortest path for oxygen or platelet from your hostpital \n");
        printf("3 - know all the hospitals having required amount of oxygen or platelet \n");
        printf("4 - shortest path between all the hospitals \n");
        printf("5 - exit\n");
        printf("Enter you choice : \n");
        int ch;
        scanf("%d", &ch);
        if (ch < 1 || ch > 5)
        {
            printf("Invalid entry !\n plz continue :");
            continue;
        }
        if (ch == 1)
        {
            // clrscr();
            printf("\n\nRegisterd hospitals are : \n\n");
            if (sub_choice == 2)
                printf("HOSPITALS \t no. of oxygen cylinders\tprice of each cylinder \n");
            if (sub_choice == 3)
                printf("HOSPITALS \t platelet units \tprice of each unit\n");
            for (int i = 1; i <= n; i++)
            {
                if (i == n || i == n - 1)
                    printf("%s\t\t%d", p[i].name, oarr[i - 1]);
                else
                    printf("%s\t\t     %d", p[i].name, oarr[i - 1]);
                printf("\t\t\t\t   %d", parr[i - 1]);
                printf("\n");
            }
            printf("\n");
        }
        if (ch == 2)
        {
            int flag = 0;
            printf("Enter the source hospital : ");
            char hsp[20], bgp[10];
            int units;
            scanf("%s", hsp);
            if (sub_choice == 2)
                printf("Enter the number of oxygen cylinder required : ");
            if (sub_choice == 3)
                printf("Enter the number of units of platelet required : ");

            scanf("%d", &units);
            for (int i = 0; i < n; i++)
            {
                if (strcmp(hsp, p[i + 1].name) == 0)
                {
                    dj(arr, barr, parr, oarr, n, i, index_bg(bgp), units, 2, p, sub_choice);
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
                printf("Enter a registered hospital \n");
        }
        if (ch == 3)
        {
            int flag = 0;
            printf("Enter the source hospital : ");
            char hsp[20], bgp[10];
            int units;
            scanf("%s", hsp);
            printf("Enter the number of units required : ");
            scanf("%d", &units);
            for (int i = 0; i < n; i++)
            {
                if (strcmp(hsp, p[i + 1].name) == 0)
                {

                    printf("hospitals\tdistance form %s\tprice\n", hsp);
                    dj(arr, barr, parr, oarr, n, i, index_bg(bgp), units, 3, p, sub_choice);
                    flag = 1;
                    break;
                }
                if (flag == 0)
                    printf("Enter a registered hospital \n");
            }
        }
        if (ch == 4)
        {
            flloyd_warshall(arr, n, p);
        }
        if (ch == 5)
            break;
    }
}
void blood_queries(int **arr, int **barr, int *parr, int *oarr, int n, edges edg[], int e, hospitals p[], int sub_choice)
{
    while (1)
    {

        printf("press :\n");
        printf("1 - know all the registered hopitals \n");
        printf("2 - know the shortest path for blood from your hostpital \n");
        printf("3 - know all the hospitals with required blood type \n");
        printf("4 - shortest path between all the hospitals \n");
        printf("5 - exit ");
        printf("Enter you choice : \n");
        int ch;
        scanf("%d", &ch);
        if (ch < 1 || ch > 5)
        {
            printf("Invalid entry !\n plz continue :");
            continue;
        }
        if (ch == 1)
        {
            // clrscr();
            printf("\n\nRegisterd hospitals are : \n\n");
            printf("%s\n", p[0].name);
            printf("HOSPITALS \tA+\tA-\tB+\tB-\tAB+\tAB-\tO+\tO-\tprice per unit\n");
            for (int i = 1; i <= n; i++)
            {
                if (i == n || i == n - 1)
                    printf("%s\t", p[i].name);
                else
                    printf("%s\t\t", p[i].name);
                for (int j = 0; j < n; j++)
                {

                    printf("%d\t", barr[i - 1][j]);
                }
                printf("%d", parr[i - 1]);
                printf("\n");
            }
            printf("\n");
        }
        if (ch == 2)
        {
            int flag = 0;
            printf("Enter the source hospital : ");
            char hsp[20], bgp[10];
            int units;
            scanf("%s", hsp);
            printf("Enter the blood group required : ");
            scanf("%s", bgp);
            if (index_bg(bgp) == -1)
            {
                printf("\n\nInvalid blood group !\n\n\n");
            }
            else
            {
                printf("Enter the number of units required : ");
                scanf("%d", &units);
                for (int i = 0; i < n; i++)
                {
                    if (strcmp(hsp, p[i + 1].name) == 0)
                    {
                        dj(arr, barr, parr, oarr, n, i, index_bg(bgp), units, 2, p, sub_choice);
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                    printf("Enter a registered hospital \n");
            }
        }
        if (ch == 3)
        {
            int flag = 0;
            printf("Enter the source hospital : ");
            char hsp[20], bgp[10];
            int units;
            scanf("%s", hsp);
            printf("Enter the blood group required : ");
            scanf("%s", bgp);
            if (index_bg(bgp) == -1)
                printf("Invalid blood group !\n");
            else
            {
                printf("Enter the number of units required : ");
                scanf("%d", &units);
                for (int i = 0; i < n; i++)
                {
                    if (strcmp(hsp, p[i + 1].name) == 0)
                    {
                        printf("hospitals with required blood group :\n");
                        printf("hospitals\tdistance form %s\tprice\n", hsp);
                        dj(arr, barr, parr, oarr, n, i, index_bg(bgp), units, 3, p, sub_choice);
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                    printf("Enter a registered hospital \n");
            }
        }
        if (ch == 4)
        {
            flloyd_warshall(arr, n, p);
        }
        if (ch == 5)
            break;
    }
}
int **open_file(int **arr, int map_choice, int sub_choice)
{
    FILE *ptr = NULL;
    FILE *ptr1 = NULL;
    FILE *spots = NULL;

    if (map_choice == 1)
    {
        spots = fopen("map1.txt", "r");
        if (sub_choice == 1)
            ptr = fopen("map1_BP.txt", "r");
        else if (sub_choice == 2)
            ptr = fopen("map1_oxy.txt", "r");
        else if (sub_choice == 3)
            ptr = fopen("map1_BP.txt", "r");
    }
    char number_of_nodes[10];
    fscanf(ptr, "%s", number_of_nodes);
    // fgets(number_of_nodes, 50, ptr);
    // printf("%u\n",ptr);
    int n = string_to_num(number_of_nodes); // taking number of nodes
    // printf("\nTotal vertices : %d\n", n);

    hospitals p[n];
    int m = 1;
    char name[30];
    fscanf(spots, "%s", name);
    do
    {
        fscanf(spots, "%s", name);
        strcpy(p[m].name, name);
        // printf("%s\n",p[m].name);
        m = m + 1;
    } while (!feof(spots));

    int **barr;
    arr = (int **)malloc(sizeof(int *) * n);
    barr = (int **)malloc(sizeof(int *) * n);
    int *parr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = (int *)malloc(sizeof(int) * n);
        barr[i] = (int *)malloc(sizeof(int) * n);
        parr[i] = 0;
        for (int j = 0; j < n; j++)
        {
            arr[i][j] = 0;
            barr[i][j] = 0;
        }
    }
    // reading blood quatities in hosp

    char number_of_edges[10];
    fscanf(ptr, "%s", number_of_edges);
    int e = string_to_num(number_of_edges); // this variable stores number of edges in the graph
    printf("\nTotal edges is : %d\n", e);
    edges edg[e]; // array to store all the edges of graph;

    int l = 0;
    // till we reach the end of the file we will keep reading the file

    while (!feof(ptr))
    {
        char starting_edge[10];
        char ending_edge[10];
        char edge_weight[10];
        fscanf(ptr, "%s", starting_edge);
        fscanf(ptr, "%s", ending_edge);
        fscanf(ptr, "%s", edge_weight);
        int u = string_to_num(starting_edge);
        int v = string_to_num(ending_edge);
        int w = string_to_num(edge_weight);
        // making connections in the adjacency matrix
        arr[u][v] = w;
        arr[v][u] = w;

        edg[l].u = u;
        edg[l].v = v;
        edg[l].w = w;
        l = l + 1;
        // printf("%d %d %d\n",u,v,w);
    }
    // when the loop will end we will have adjacency matrix of graph as
    // well as the array of all the edges of the graph

    fclose(ptr);
    char bloodq[10];

    if (sub_choice == 1)
    {
        ptr1 = fopen("BS.txt", "r");
        int ii = 0, jj = 0;
        fscanf(ptr1, "%s", bloodq);
        while (!feof(ptr1))
        {
            int x = string_to_num(bloodq);
            barr[ii][jj] = x;
            // printf("%d ",barr[ii][jj]);
            jj++;
            if (jj >= n)
            {
                // printf("\n");
                jj = 0;
                ii++;
            }
            fscanf(ptr1, "%s", bloodq);
        }
        fclose(ptr1);
    }

    int *oarr; // FOR STORING THE OXYGEN OR PLATELET AVAILABLE AT EACH HOSPITAL
    ptr1 = NULL;
    if (sub_choice == 2 || sub_choice == 3)
    {
        int z = 0;
        oarr = (int *)malloc(sizeof(int) * n);
        if (sub_choice == 2)
            ptr1 = fopen("qoxy_map1.txt", "r");
        if (sub_choice == 3)
            ptr1 = fopen("qplatelet_map1.txt", "r");

        while (!feof(ptr1))
        {
            fscanf(ptr1, "%s", bloodq);
            int x = string_to_num(bloodq);
            oarr[z++] = x;
        }
    }
    ptr1 = NULL;
    int z = 0;

    if (sub_choice == 1)
    {
        // reading price from blood_price.txt
        ptr1 = fopen("blood_price.txt", "r");
    }
    if (sub_choice == 2)
        ptr1 = fopen("oxy_price.txt", "r");

    if (sub_choice == 3)
        ptr1 = fopen("platelet_price.txt", "r");
    while (!feof(ptr1))
    {
        fscanf(ptr1, "%s", bloodq);
        int x = string_to_num(bloodq);
        parr[z++] = x;
    }
    if (sub_choice == 1)
        blood_queries(arr, barr, parr, oarr, n, edg, e, p, sub_choice);
    if (sub_choice == 2 || sub_choice == 3)
        platoxy_queries(arr, barr, parr, oarr, n, edg, e, p, sub_choice);
    return arr;
}
int main()
{
    int **arr;
    while (1)
    {
        // clrscr();
        int map_choice, sub_choice;
        printf("press :\n");
        printf("1 - Hubli\n");
        printf("2 - exit\n");
        printf("Enter your choice : ");
        scanf("%d", &map_choice);
        if (map_choice == 2)
        {
            printf("\t\t\t\t\t\t\t\t\t\tT H A N K____________Y O U");
            printf("\n\n\n_____________________  ********************************         *************************************  _________________________________________");
            break;
        }
        if (map_choice > 2)
        {
            printf("Invalid entry !\n plz continue \n");
            continue;
        }
        // clrscr();

        printf("press :\n");
        printf("1 if u are in need of blood \n");
        printf("2 if u are in need of oxygen \n");
        printf("3 if u are in need of platelets \n");
        printf("Enter your choice : \n");
        scanf("%d", &sub_choice);
        if (sub_choice < 1 || sub_choice > 3)
        {
            printf("Invalid entry !\n plz continue \n");
            continue;
        }
        arr = open_file(arr, map_choice, sub_choice);
        int cl_cn_ex; // to clear the screen and continue
        printf("\n\nPress 1 to clear screen and continue.\n");
        printf("Press 2 or other keys to exit.\n");
        printf("Please enter your choice : ");
        scanf("%d", &cl_cn_ex);
        if (cl_cn_ex == 1)
        {
            // clrscr();
        }
        else
        {
            printf("\t\t\t\t\t\t\t\t\t\tT H A N K____________Y O U");
            printf("\n\n\n_____________________  ********************************         *************************************  _________________________________________");
            break;
        }
    }
}
