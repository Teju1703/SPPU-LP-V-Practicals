
                #include<iostream>
                #include<stdlib.h>
                #include<omp.h>
                using namespace std;
                
                // Function Declarations
                void bubble(int *a, int n);
                void swap(int &a, int &b);
                void mergesort(int a[], int i, int j);
                void merge(int a[], int i1, int j1, int i2, int j2);
                
                // Parallel Bubble Sort (Odd-Even Transposition Sort)
                void bubble(int *a, int n)
                {
                    for (int i = 0; i < n; i++)
                    {
                        int first = i % 2;
                
                        #pragma omp parallel for shared(a, first)
                        for (int j = first; j < n - 1; j += 2)
                        {
                            if (a[j] > a[j + 1])
                            {
                                swap(a[j], a[j + 1]);
                            }
                        }
                    }
                }
                
                void swap(int &a, int &b)
                {
                    int temp = a;
                    a = b;
                    b = temp;
                }
                
                // Parallel Merge Sort
                void mergesort(int a[], int i, int j)
                {
                    int mid;
                    if (i < j)
                    {
                        mid = (i + j) / 2;
                
                        #pragma omp parallel sections
                        {
                            #pragma omp section
                            {
                                mergesort(a, i, mid);
                            }
                            #pragma omp section
                            {
                                mergesort(a, mid + 1, j);
                            }
                        }
                
                        merge(a, i, mid, mid + 1, j);
                    }
                }
                
                void merge(int a[], int i1, int j1, int i2, int j2)
                {
                    int temp[1000];
                    int i = i1, j = i2, k = 0;
                
                    while (i <= j1 && j <= j2)
                    {
                        if (a[i] < a[j])
                            temp[k++] = a[i++];
                        else
                            temp[k++] = a[j++];
                    }
                
                    while (i <= j1)
                        temp[k++] = a[i++];
                
                    while (j <= j2)
                        temp[k++] = a[j++];
                
                    for (i = i1, j = 0; i <= j2; i++, j++)
                        a[i] = temp[j];
                }
                
                // Main Function
                int main()
                {
                    int *a, n, choice;
                
                    cout << "Enter total number of elements: ";
                    cin >> n;
                
                    a = new int[n];
                    cout << "Enter elements:\n";
                    for (int i = 0; i < n; i++)
                        cin >> a[i];
                
                    cout << "\nChoose sorting algorithm:\n";
                    cout << "1. Parallel Bubble Sort (Odd-Even Transposition Sort)\n";
                    cout << "2. Parallel Merge Sort\n";
                    cout << "Enter choice (1 or 2): ";
                    cin >> choice;
                
                    switch (choice)
                    {
                        case 1:
                            bubble(a, n);
                            break;
                        case 2:
                            mergesort(a, 0, n - 1);
                            break;
                        default:
                            cout << "Invalid choice!";
                            delete[] a;
                            return 1;
                    }
                
                    cout<< "\nSorted array is:\n";
                    for (int i = 0; i < n; i++)
                        cout << a[i] << " ";
                    cout << endl;
                
                    delete[] a;
            
                    return 0;
                }
                
