//dual pivot quicksort

int partition2(int* arr, int low, int high, int* lp); 
  
void swap(int* a, int* b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 
  
void DualPivotQuickSort(int* arr, int low, int high) 
{ 
    if (low < high) { 
        // lp means left pivot, and rp means right pivot. 
        int lp, rp; 
        rp = partition2(arr, low, high, &lp); 
        DualPivotQuickSort(arr, low, lp - 1); 
        DualPivotQuickSort(arr, lp + 1, rp - 1); 
        DualPivotQuickSort(arr, rp + 1, high); 
    } 
} 
  
int partition2(int* arr, int low, int high, int* lp) 
{ 
    if (arr[low] > arr[high]) 
        swap(&arr[low], &arr[high]); 
    // p is the left pivot, and q is the right pivot. 
    int j = low + 1; 
    int g = high - 1, k = low + 1, p = arr[low], q = arr[high]; 
    while (k <= g) { 
  
        // if elements are less than the left pivot 
        if (arr[k] < p) { 
            swap(&arr[k], &arr[j]); 
            j++; 
        } 
  
        // if elements are greater than or equal 
        // to the right pivot 
        else if (arr[k] >= q) { 
            while (arr[g] > q && k < g) 
                g--; 
            swap(&arr[k], &arr[g]); 
            g--; 
            if (arr[k] < p) { 
                swap(&arr[k], &arr[j]); 
                j++; 
            } 
        } 
        k++; 
    } 
    j--; 
    g++; 
  
    // bring pivots to their appropriate positions. 
    swap(&arr[low], &arr[j]); 
    swap(&arr[high], &arr[g]); 
  
    // returning the indices of the pivots. 
    *lp = j; // because we cannot return two elements 
    // from a function. 
  
    return g; 
} 
  
static int partition(int array[], int low, int high) {
  // Select the pivot element
  int pivot = array[high];
  int i = (low - 1);
  // Put the elements smaller than pivot on the left 
  // and greater than pivot on the right of pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }
  swap(&array[i + 1], &array[high]);
  return (i + 1);
}

static void quickSort(int array[], int low, int high) {
  if (low < high) {
    // Select pivot position and put all the elements smaller 
    // than pivot on left and greater than pivot on right
    int pi = partition(array, low, high);
    // Sort the elements on the left of pivot
    quickSort(array, low, pi - 1);
    // Sort the elements on the right of pivot
    quickSort(array, pi + 1, high);
  }
}