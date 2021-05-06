import { searchSortedArrays, findMedianSortedArrays, randomSortedNumbers, sortNumber } from "./median.of.two.sorted.arrays";

test(
    "check the result value of the call to the function searchSortedArrays, findMedianSortedArrays",
    () => {
        let nums1 = randomSortedNumbers();
        let nums2 = randomSortedNumbers();
        let nums3 = [...nums1, ...nums2];
        nums3.sort(sortNumber);
        for (let i = 0; i < nums3.length; ++i) {
            let v = searchSortedArrays(nums1, 0, nums1.length, nums2, 0, nums2.length, i);
            expect(v).toBe(nums3[i]);
        }

        nums1 = [1, 3];
        nums2 = [2];
        let result = findMedianSortedArrays(nums1, nums2);
        expect(result).toEqual(2);

        nums1 = [1, 2];
        nums2 = [3, 4];
        result = findMedianSortedArrays(nums1, nums2);
        expect(result).toEqual(2.5);

        nums1 = [0, 0];
        nums2 = [0, 0];
        result = findMedianSortedArrays(nums1, nums2);
        expect(result).toEqual(0);

        nums1 = [];
        nums2 = [1];
        result = findMedianSortedArrays(nums1, nums2);
        expect(result).toEqual(1);

        nums1 = [2];
        nums2 = [];
        result = findMedianSortedArrays(nums1, nums2);
        expect(result).toEqual(2);
    }
);
