#include"../sort.hpp"

void PrintArr(const std::vector<int>& arr){
    for(auto e:arr){
        printf("%d ", e);
    }
    printf("\n");
}

void InsertionSort(std::vector<int>& arr){
    //边界条件 nullptr,size<2
    //重复值：略；
    if(arr.empty() || arr.size()<2){
        return ;
    }
    //极端条件：有序时，无须再排序
    //暴力：略

    //规律，冗余:略
    //数据结构：vector
    //时空间复杂度:略

    //思路：一张一张取牌，再和已有的进行比较交换
    //0 1
    //0 1 2
    // **************暴力解法(最直白无优化的)*****************
    // for(int end = 1 ; end < arr.size(); end++){
    //     for(int j = end; j>0; j--) {
    //         if(arr[j]<arr[j-1]){
    //             std::swap(arr[j],arr[j-1]);
    //         }
    //     }
    // }

    for(int end = 1 ; end < arr.size(); end++){
        //先找最小，再挪动
        //极端条件是，有序：
        //      我不知道他整体是否有序，但我知道已经抽出的牌一定是有序的，如果比最大的牌还大，就一定是最多大的，可以走下一轮抽牌了。
        int temp = arr[end];
        int mini = end;
        for(int j = end-1; j>=0; j--) {
            if (temp < arr[j]) {
                mini = j;
            }
            else{   //比前一个大，说明有序，下一轮
                break;
            }
        }
        for (int i = end; i > mini; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[mini] = temp;
    }
}

int main()
{
    std::vector<int> v{4, 6, 2, 3, 7, 8, 1, 9, 0, 5};
    // 4,6,2,3,7,8,1,9,0,5
    // 4 6

    // 4 6 2:
    // 4 x 6
    // x 4 6

    // 2 4 6 3
    // 2 4 x 6
    // 2 x 4 6

    // std::vector<int> v{4, 6, 2, 1};
    PrintArr(v);
    InsertionSort(v);
    PrintArr(v);
    return 0;
}