#ifndef _QuickSort_H
#define _QuickSort_H

#include<stdio.h>
#include<stdlib.h>

#define CutOff (3)  //AT least 4 elements

void QuickSort(int A[], int n);//n个元素排序
void QuickSort1(int A[], int Left, int Right);
void InsertSort(int A[], int n);
int QuickSelete(int A[], int k, int n);
int QuickSelete1(int A[], int k, int Left, int Right);//从A里面选出第k大的元素

#endif // !_QuickSort_H


#pragma once
