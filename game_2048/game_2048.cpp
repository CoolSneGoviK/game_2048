// игра 2048 - в консоле
#include <iostream>
#include <vector>

using namespace std;

/*
int arr2[][5] = { {2, 4, 4, 8, 2},
                  {8, 2, 2, 2, 2},
                  {4, 2, 2, 2, 2},
                  {4, 2, 2, 2, 2},
                  {8, 2, 2, 2, 2} };
                  */
                  // начальные значения массива
int arr3[][4] = { {0, 4, 2, 0},
                  {2, 0, 2, 2},
                  {0, 2, 0, 2},
                  {2, 2, 4, 4} };

int selector = 0, selector2 = 0, selector3 = 0;
int* ptr_selector3 = &selector3;
vector<int> I, J;
vector<int> N;
//vector<int> M;

// добавление 2 или 4 в свободную клетку
void add_2_4(int a[][4], vector<int> I, vector<int> J)
{ // добавляет 2 или 4 в свободную клетку
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (a[i][j] == 0)
            {
                I.push_back(i);
                J.push_back(j);
            }
        }
    }

    int random_place = rand() % I.size();
    int m = rand() % 2 + 1; // от 1 до 2
    int l = 0;
    if (m == 1)
    {
        l = 2;
    }
    else
    {
        l = 4;
    }
    a[I[random_place]][J[random_place]] = l;
    I.clear();
    J.clear();
}

// выравнивание вверх
void alignment_up(int a[][4], int j)
{
    /*
    for (int i = 0; i < 4; i++)
    { // замена -1 на 0
        if (a[i][j] == -1)
        {
            a[i][j] = 0;
        }
    }
    */
    selector = 0;

    while (selector == 0)
    { // сдвиг всех элементов влево, кроме 0
        selector = 1;
        for (int i = 0; i < 3; i++)
        {
            if (a[i][j] == 0)
            { // если значение равно 0 
                if (a[i + 1][j] == 0)
                { // и следующее равно 0
                    continue;
                }
                // это если следующее не равно 0, меняем их местами 
                a[i][j] = a[i + 1][j];
                a[i + 1][j] = 0;
                selector = 0;
            }
        }
    }

    selector = 0;
}
// сдвиг вверх
void shift_up(int a[][4])
{
    //for (int j = 0; j < 5; j++) // версия для массива с 5 строками и столбцами
    for (int j = 0; j < 4; j++) // для 4
    {
        while (selector == 0)
        {
            selector = 1;
            //for (int i = 0; i < 4; i++) // для 5
            for (int i = 0; i < 3; i++) // на 4
            { // сложение элементов
                if (a[i][j] == 0 && a[i + 1][j] == 0)
                {
                    continue;
                }

                if (a[i][j] == 0 && a[i + 1] != 0)
                { // если текущее значение равно 0, меняем местами элементы со следующим
                    for (int n = 0; n < N.size(); n++)
                    {
                        if (i == N[n] || i + 1 == N[n])
                        {
                            selector2 = 1;
                            break;
                        }
                    }
                    if (selector2 == 1)
                    {
                        selector2 = 0;
                        continue;
                    }

                    *ptr_selector3 = 1;

                    a[i][j] = a[i + 1][j];
                    a[i + 1][j] = 0;

                    selector = 0;
                    continue;
                }

                if (a[i][j] == a[i + 1][j])
                { // если нашли пару значений
                    for (int n = 0; n < N.size(); n++)
                    {
                        if (i == N[n] || i + 1 == N[n])
                        {
                            selector2 = 1;
                            break;
                        }
                    }
                    if (selector2 == 1)
                    {
                        selector2 = 0;
                        continue;
                    }

                    *ptr_selector3 = 1;

                    N.push_back(i);
                    N.push_back(i + 1);

                    a[i][j] *= 2;
                    a[i + 1][j] = 0;
                    //a[i + 1][j] = -1;
                    selector = 0;
                }
            }
        }
        alignment_up(a, j);
        N.clear();
    }
}

// выравнивание вниз
void aligment_down(int a[][4], int j)
{
    /*
    for (int i = 0; i < 5; i++)
    { // замена -1 на 0
        if (a[i][j] == -1)
        {
            a[i][j] = 0;
        }
    }
    */
    selector = 0;

    while (selector == 0)
    { // сдвиг всех элементов вправо, кроме 0
        selector = 1;
        for (int i = 3; i > 0; i--)
        {
            if (a[i][j] == 0)
            { // если значение равно 0 
                if (a[i - 1][j] == 0)
                { // и следующее равно 0
                    continue;
                }
                // это если следующее не равно 0, меняем их местами 
                a[i][j] = a[i - 1][j];
                a[i - 1][j] = 0;
                selector = 0;
            }
        }
    }

    selector = 0;
}
// сдвиг вниз
void shift_down(int a[][4])
{
    //for (int j = 4; j > -1; j--)
    for (int j = 0; j < 4; j++)
    {
        while (selector == 0)
        {
            selector = 1;
            for (int i = 3; i > 0; i--)
            { // сложение элементов
                if (a[i][j] == 0 && a[i - 1][j] == 0)
                { // если оба элемента равны 0, ничего не делаем и идем к следующему шагу цикла
                    continue;
                }

                if (a[i][j] == 0 && a[i - 1][j] != 0)
                { // если текущее значение равно 0, меняем местами элементы со следующим
                    for (int n = 0; n < N.size(); n++)
                    {
                        if (i == N[n] || i - 1 == N[n])
                        {
                            selector2 = 1;
                            break;
                        }
                    }
                    if (selector2 == 1)
                    {
                        selector2 = 0;
                        continue;
                    }

                    *ptr_selector3 = 1;

                    a[i][j] = a[i - 1][j];
                    a[i - 1][j] = 0;

                    selector = 0;
                    continue;
                }

                if (a[i][j] == a[i - 1][j])
                { // если нашли пару значений

                    for (int n = 0; n < N.size(); n++)
                    {
                        if (i == N[n] || i - 1 == N[n])
                        {
                            selector2 = 1;
                            break;
                        }
                    }
                    if (selector2 == 1)
                    {
                        selector2 = 0;
                        continue;
                    }

                    *ptr_selector3 = 1;

                    N.push_back(i);
                    N.push_back(i - 1);
                    //M.push_back(j);

                    a[i][j] *= 2;
                    a[i - 1][j] = 0;
                    //a[i - 1][j] = -1;
                    selector = 0;
                }
            }
        }
        aligment_down(a, j);
        //M.clear();
        N.clear();
    }
}


// выравнивание влево для одномерного массива, но можно по частям передать двумерный
void alignment_left(int a[]) // выравнивание
{ // для сдвига влево
    /*
    for (int i = 0; i < 5; i++)
    { // замена -1 на 0
        if (a[i] == -1)
        {
            a[i] = 0;
        }
    }
    */
    selector = 0;

    while (selector == 0)
    { // сдвиг всех элементов влево, кроме 0
        selector = 1;
        for (int i = 0; i < 3; i++)
        {
            if (a[i] == 0)
            { // если значение равно 0 
                if (a[i + 1] == 0)
                { // и следующее равно 0
                    continue;
                }
                // это если следующее не равно 0, меняем их местами 
                a[i] = a[i + 1];
                a[i + 1] = 0;
                selector = 0;
            }
        }
    }

    selector = 0;
}
// сдвиг влево
void shift_left(int a[])
{ // сдвиг влево
    while (selector == 0)
    {
        selector = 1;
        for (int i = 0; i < 3; i++)
        { // сложение элементов
            if (a[i] == 0 && a[i + 1] == 0)
            { // если нашли соседние 0 и 0
                continue;
            }

            if (a[i] == 0 && a[i + 1] != 0)
            { // если текущее значение равно 0, меняем местами элементы со следующим
                for (int n = 0; n < N.size(); n++)
                {
                    if (i == N[n] || i + 1 == N[n])
                    {
                        selector2 = 1;
                        break;
                    }
                }
                if (selector2 == 1)
                {
                    selector2 = 0;
                    continue;
                }

                *ptr_selector3 = 1;

                a[i] = a[i + 1];
                a[i + 1] = 0;

                selector = 0;
                continue;
            }

            if (a[i] == a[i + 1])
            { // если нашли пару значений
                for (int n = 0; n < N.size(); n++)
                {
                    if (i == N[n] || i + 1 == N[n])
                    {
                        selector2 = 1;
                        break;
                    }
                }
                if (selector2 == 1)
                {
                    selector2 = 0;
                    continue;
                }

                *ptr_selector3 = 1;

                N.push_back(i);
                N.push_back(i + 1);
                a[i] *= 2;
                a[i + 1] = 0;
                //a[i + 1] = -1;
                selector = 0;
            }
        }
    }

    alignment_left(a);
    N.clear();
}

// выравнивание вправо
void alignment_right(int a[]) // выравнивание
{ // для сдвига вправо
    /*
    for (int i = 0; i < 5; i++)
    { // замена -1 на 0
        if (a[i] == -1)
        {
            a[i] = 0;
        }
    }
    */
    selector = 0;

    while (selector == 0)
    { // сдвиг всех элементов вправо, кроме 0
        selector = 1;
        for (int i = 3; i > 0; i--)
        {
            if (a[i] == 0)
            { // если значение равно 0 
                if (a[i - 1] == 0)
                { // и следующее равно 0
                    continue;
                }
                // это если следующее не равно 0, меняем их местами 
                a[i] = a[i - 1];
                a[i - 1] = 0;
                selector = 0;
            }
        }
    }

    selector = 0;
}
// сдвиг вправо
void shift_right(int a[]) // сдвиг вправо
{
    while (selector == 0)
    {
        selector = 1;
        for (int i = 3; i > 0; i--)
        { // сложение элементов
            if (a[i] == 0 && a[i - 1] == 0)
            {
                continue;
            }

            if (a[i] == 0 && a[i - 1] != 0 && a[i - 1] != -1)
            { // если текущее значение равно 0, меняем местами элементы со следующим
                for (int n = 0; n < N.size(); n++)
                {
                    if (i == N[n] || i - 1 == N[n])
                    {
                        selector2 = 1;
                        break;
                    }
                }
                if (selector2 == 1)
                {
                    selector2 = 0;
                    continue;
                }

                *ptr_selector3 = 1;

                a[i] = a[i - 1];
                a[i - 1] = 0;

                selector = 0;
                continue;
            }

            if (a[i] == a[i - 1] && a[i] != 0 && a[i] != -1)
            { // если нашли пару значений, 2 и 2, 4 и 4 например
                for (int n = 0; n < N.size(); n++)
                {
                    if (i == N[n] || i - 1 == N[n])
                    {
                        selector2 = 1;
                        break;
                    }
                }

                if (selector2 == 1)
                {
                    selector2 = 0;
                    continue;
                }

                *ptr_selector3 = 1;

                N.push_back(i);
                N.push_back(i - 1);
                a[i] *= 2;
                a[i - 1] = 0;
                //a[i - 1] = -1;
                selector = 0;
            }
        }
    }

    alignment_right(a);
    N.clear();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    /*
    shift_left(arr);
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    */

    cout << "для окончания игры нажмите k" << endl;

    while (true)
    {
        for (int j = 0; j < 4; j++)
        { // для вывода двумерного
            for (int i = 0; i < 4; i++)
            { // вывод одномерного массива
                cout << arr3[j][i] << " ";
            }
            cout << endl;
        }

        char h = 0;

        cin >> h;

        if (h == 'w')
        {
            shift_up(arr3);
            system("cls"); // 1
            if (*ptr_selector3 == 1)
            {
                add_2_4(arr3, I, J);
                *ptr_selector3 = 0;
            }
        }

        if (h == 's')
        {
            shift_down(arr3);
            system("cls"); // 2
            if (*ptr_selector3 == 1)
            {
                add_2_4(arr3, I, J);
                *ptr_selector3 = 0;
            }
        }

        if (h == 'a')
        {
            shift_left(arr3[0]);
            shift_left(arr3[1]);
            shift_left(arr3[2]);
            shift_left(arr3[3]);
            //shift_left(arr3[4]); // изначально делал игру с сеткой 5x5
            system("cls"); // 3

            if (*ptr_selector3 == 1)
            {
                add_2_4(arr3, I, J);
                *ptr_selector3 = 0;
            }
        }

        if (h == 'd')
        {
            shift_right(arr3[0]);
            shift_right(arr3[1]);
            shift_right(arr3[2]);
            shift_right(arr3[3]);
            //shift_right(arr3[4]);
            system("cls"); // 4

            if (*ptr_selector3 == 1)
            {
                add_2_4(arr3, I, J);
                *ptr_selector3 = 0;
            }
        }
        //cout << endl;
        if (h == 'k')
        {
            break;
        }
    }

    system("pause");
    return 0;
}

