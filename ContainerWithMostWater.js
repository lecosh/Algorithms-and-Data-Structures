//Leetcode 11
var maxArea = function(height) {
    let i = 0, j = height.length - 1, max = 0
    while (i < j){
        let temp = (j - i) * Math.min(height[i], height[j])
        if (temp >= max) max = temp
        if (height[i] < height[j]){
            i++
        }
        else {
            j--
        }
    }
    return max
};
