#ifndef SORT_H
#define SORT_H

extern void bubble_sort(float *arr, int n);
extern void shell_sort(float *arr, int size);
extern int bubble_sort_pt(float** pointers, int n);
extern int shell_sort_pt(float** pointers, int n);
extern int insertion_sort_pt(float** pointers, int n) ;
extern void pointerArrayInit(float *array,float **ptArray,int size);
extern void TestSort(void);

#endif
