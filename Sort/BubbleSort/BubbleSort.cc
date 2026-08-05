#include"..\sort.hpp"



void PrintArr(const std::vector<int>& arr){
    for(auto e:arr){
        printf("%d ", e);
    }
    printf("\n");
}

void BubbleSort(std::vector<int>& arr){
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

    //思路：取两数比较，后一个比前一个小就换位置，最后会吧最大的数冒出来在最后。最后的数不再参与计算

    for (int end = arr.size();end>1;end--) { // 只表示控制末尾缩小
        bool swapped = 0;
        //1,4; 1,3; 1,2 ,1 ,1
        for (int j = 1; j <end; j++)
        { // 始终从0开始
            if (arr[j - 1] > arr[j])
            {
                std::swap(arr[j - 1], arr[j]);
                swapped = 1;
            }
        }
        //如果一轮都没有交换，则说明有序，直接退出
        if(swapped == 0){
            break;
        }

    }
}

int main()
{
    std::vector<int> v {4,6,2,3,7,8,1,9,0,5};
    // std::vector<int> v{4, 6, 2, 1};
    PrintArr(v);
    BubbleSort(v);
    PrintArr(v);
    return 0;
}