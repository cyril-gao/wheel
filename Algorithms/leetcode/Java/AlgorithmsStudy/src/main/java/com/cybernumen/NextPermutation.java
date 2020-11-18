package com.cybernumen;

public class NextPermutation {
    private static void iter_swap(int[] nums, int i, int j) {
        int v = nums[i];
        nums[i] = nums[j];
        nums[j] = v;
    }

    public void nextPermutation(int[] nums) {
        int n = nums != null ? nums.length : 0;
        if (n > 1) {
            int minimumIndex = nums.length - 1;
            int maximumIndex = minimumIndex;
            int medialIndex = -1;
            for (int i = minimumIndex, j = i - 1; j >= 0; i = j--) {
                if (nums[j] >= nums[i]) {
                    maximumIndex = j;
                } else {
                    medialIndex = j;
                    break;
                }
            }
            if (medialIndex >= 0) {
                int biggerIndex = maximumIndex;
                while (biggerIndex <= minimumIndex && nums[medialIndex] < nums[biggerIndex]) {
                    ++biggerIndex;
                }
                --biggerIndex;
                iter_swap(nums, biggerIndex, medialIndex);
                while (minimumIndex >= biggerIndex && maximumIndex < biggerIndex) {
                    iter_swap(nums, minimumIndex, maximumIndex);
                    ++maximumIndex;
                    --minimumIndex;
                }
                for (int i = biggerIndex - 1; maximumIndex < i; --i, ++maximumIndex) {
                    iter_swap(nums, i, maximumIndex);
                }
                while (minimumIndex > biggerIndex) {
                    iter_swap(nums, minimumIndex, biggerIndex);
                    --minimumIndex;
                    ++biggerIndex;
                }
            } else {
                for (int i = 0; i < minimumIndex; ++i, --minimumIndex) {
                    iter_swap(nums, i, minimumIndex);
                }
            }
        }
    }
}
