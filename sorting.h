#ifndef SORT_H
#define SORT_H

extern void bubble_sort(float *arr, unsigned int n);
extern void shell_sort(float *arr, unsigned int size);
extern unsigned int bubble_sort_pt(float** pointers, unsigned int n);
extern unsigned int shell_sort_pt(float** pointers, unsigned int n);
extern unsigned int insertion_sort_pt(float** pointers, unsigned int n) ;
extern void pointerArrayInit(float *array,float **ptArray,unsigned int size);
extern void TestSort(void);

#endif
