#include"..\sort.hpp"

//用打牌来记住选择排序和插入排序。
//插入排序是一张一张摸牌，摸到小的放左边，摸到大的放右边。即工程上的流式处理。
//选择排序是一堆牌一起排，从一堆牌从挑出小的放左边，依次下去。
//显然插入排序更省内存。

void PrintArr(const std::vector<int>& arr){
    for(auto e:arr){
        printf("%d ", e);
    }
    printf("\n");
    // for(int i = 0;i<arr.size();i++){
    //     printf("%d ",arr[i]);
    // }
}

void SelectionSort(std::vector<int>& arr){
    //边界条件 nullptr,size<2
    //重复值：略；
    if(arr.empty() || arr.size()<2){
        return ;
    }
    //暴力：略

    //规律，冗余:略
    //数据结构：vector
    //时空间复杂度:略

    //思路：从所有牌中依次选最小的牌，放入最左边。选完排好的不再进入排序
    //[0]~[1,n]
    //[1]~[2,n]
    //[2]~[3,n]
    //...
    for(int i = 0; i<arr.size(); i++){  //max(i)==9
        int MinNumIndex = i;    //选完排好的不再进入排序，即从i开始;
        for (int j = i+1; j < arr.size(); j++) {    //max(j) == 10，如果i是9,j就是10>=10，不再需要排序。
            MinNumIndex = arr[j] < arr[MinNumIndex] ? j : MinNumIndex;  //找最小值的位置
        }
        std::swap(arr[MinNumIndex],arr[i]); //遍历结束后交换.
    }    
}

int main(){
    std::vector<int> v {4,6,2,3,7,8,1,9,0,5};
    PrintArr(v);
    SelectionSort(v);
    PrintArr(v);
    return 0;
}