package main

import "fmt"

func generate(numRows int) [][]int {
    if numRows == 1 {
        var nums [][]int
        nums = append(nums,[]int{1})
        return nums
    }
    
    nums := generate(numRows-1)
	fmt.Println(nums)
	row := make([]int,len(nums[len(nums)-1]))
	copy(row,nums[len(nums)-1])
	row = append(row,0)
	
	for i :=0;i<len(row)-1;i++ {
		row[i+1] += nums[len(nums)-1][i]
	}

	nums = append(nums,row)

    return nums
}
func main() {
	if len(os.Args)  !=2     {
			fmt.Println("please input  nums")
	}else{
		fmt.Println(generate(os.Args[1]))
	}
	    
}