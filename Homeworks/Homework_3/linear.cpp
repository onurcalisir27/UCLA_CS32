
// Return false if the somePredicate function returns false for at
          // least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    if (n <= 0)
    {
        return true;
    }
    if (n == 1)
    {
        return somePredicate(a[0]);
    }
    return (somePredicate(a[0]) && allTrue(a + 1, n - 1));
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const string a[], int n)
{
    int count = 0;
    if (n <= 0)
    {
        return 0;
    }
    if (n == 1)
    {
        if (somePredicate(a[0])) 
            return 1;
        else
            return 0;
    }
    if (somePredicate(a[0]))
        count++;

    return count + countTrue(a + 1, n - 1);

}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const string a[], int n)
{
    if (n <= 0)
    {
        return -1;
    }
    if (somePredicate(a[0]))
    {
        return 0;
    }
    int first = firstTrue(a + 1, n - 1);

    if (first == -1)
    {
        return -1;
    }
    else
        return first + 1;

}

// Return the subscript of the first string in the array that is >= all
// strings in the array (i.e., return the smallest subscript m such
// that a[m] >= a[k] for all k from 0 to n-1).  If the function is told
// that no strings are to be considered to be in the array, return -1.
int positionOfMax(const string a[], int n)
{
    if (n <= 0)
    {
        return -1;
    }
    if (n == 1)
    {
        return 0; // the max of a 1 element array is itself
    }
    int max_pos = positionOfMax(a + 1, n - 1);

    if (a[0] >= a[max_pos + 1])
    {
        return 0;
    }
    else 
        return 1 + max_pos;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "john" "sonia" "elena" "ketanji" "sonia" "elena" "samuel"
// then the function should return true if a2 is
//    "sonia" "ketanji" "samuel"
// or
//    "sonia" "elena" "elena"
// and it should return false if a2 is
//    "sonia" "samuel" "ketanji"
// or
//    "john" "ketanji" "ketanji"
bool contains(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 <= 0)
    {
        return true;
   }
    if (n1 < n2 || n1 <= 0)
    {
        return false;
    }
    if (a1[0] == a2[0])
    {
        return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    }
    else
        return contains(a1 + 1, n1 - 1, a2, n2);
}