package com.example;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertTrue;
import static org.testng.Assert.assertFalse;
import org.testng.annotations.*;

public class SearchTest {
    private boolean isSorted(int[] array) {
        for (int i = 0; i < array.length - 1; ++i) {
            if (array[i] > array[i + 1]) {
                return false;
            }
        }
        return true;
    }

    @Test
    public void testSearchInArray() {
        var ao = new ArraySearch();
        {
            int[] nums = { 5, 6, 7, 9, 10, 11, 12, 13, 17, 89, 0, 1, 2, 3, 4 };
            // ao.search(nums, 89);
            for (int i = 0; i < nums.length; ++i) {
                int r = ao.search(nums, nums[i]);
                assertEquals(r, i);
            }
            assertEquals(ao.search(nums, -1), -1);
            assertEquals(ao.search(nums, -11), -1);
            assertEquals(ao.search(nums, 8), -1);
            assertEquals(ao.search(nums, 14), -1);
            assertEquals(ao.search(nums, 60), -1);
        }
        {
            int[] nums = { 1, 1, 5, 7, 7, 7, 9, 9, 9, 9, 9, 17, 17, 17, 17, 21 };
            var result = ao.searchRange(nums, -1);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 0);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 1);
            assertTrue(result != null && result.length == 2 && result[0] == 0 && result[1] == 1);
            result = ao.searchRange(nums, 3);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 5);
            assertTrue(result != null && result.length == 2 && result[0] == 2 && result[1] == 2);
            result = ao.searchRange(nums, 6);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 7);
            assertTrue(result != null && result.length == 2 && result[0] == 3 && result[1] == 5);
            result = ao.searchRange(nums, 8);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 9);
            assertTrue(result != null && result.length == 2 && result[0] == 6 && result[1] == 10);
            result = ao.searchRange(nums, 15);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 17);
            assertTrue(result != null && result.length == 2 && result[0] == 11 && result[1] == 14);
            result = ao.searchRange(nums, 20);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 21);
            assertTrue(result != null && result.length == 2 && result[0] == 15 && result[1] == 15);
            result = ao.searchRange(nums, 22);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 212);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
        }
        {
            int[] nums = { 1, 2, 0 };
            assertEquals(ao.firstMissingPositive(nums), 3);
        }
        {
            int[] nums = { 3, 4, -1, 1 };
            assertEquals(ao.firstMissingPositive(nums), 2);
        }
        {
            int[] nums = { 7, 8, 9, 11, 12 };
            assertEquals(ao.firstMissingPositive(nums), 1);
        }
        {
            int[] nums = { 0, 1, 2, 3, 4, 5, 6 };
            assertEquals(ao.firstMissingPositive(nums), nums.length);
        }
        {
            int[] nums = { 10, 1, 2, 3, 4, 5, 6 };
            assertEquals(ao.firstMissingPositive(nums), 7);
        }
        {
            int[] nums = { 1 };
            assertEquals(ao.firstMissingPositive(nums), 2);
        }
        {
            int[] nums = { 1, 2, 3 };
            assertEquals(ao.firstMissingPositive(nums), 4);
        }
    }

    @Test
    public void testfindMinInUniqueElements() {
        var ao = new ArraySearch();
        {
            int[] nums = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
            for (int i = 0; i < nums.length; ++i) {
                assertEquals(ao.findMinInUniqueElements(nums), 0);
                int v = nums[0];
                for (int j = 1; j < nums.length; ++j) {
                    nums[j - 1] = nums[j];
                }
                nums[nums.length - 1] = v;
            }
            assertEquals(ao.findMinInUniqueElements(nums), 0);
            assertEquals(ao.findMin(nums), 0);
        }
        {
            int[] nums = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 1, 1, 1, 2 };
            for (int i = 0; i < nums.length; ++i) {
                assertEquals(ao.findMin(nums), 0);
                int v = nums[0];
                for (int j = 1; j < nums.length; ++j) {
                    nums[j - 1] = nums[j];
                }
                nums[nums.length - 1] = v;
            }
            assertEquals(ao.findMin(nums), 0);
        }
        {
            int[] nums = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2 };
            for (int i = 0; i < nums.length; ++i) {
                assertEquals(ao.findMin(nums), 0);
                int v = nums[0];
                for (int j = 1; j < nums.length; ++j) {
                    nums[j - 1] = nums[j];
                }
                nums[nums.length - 1] = v;
            }
            assertEquals(ao.findMin(nums), 0);
        }
        {
            int[] nums = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2 };
            for (int i = 0; i < nums.length; ++i) {
                assertEquals(ao.findMin(nums), 0);
                int v = nums[0];
                for (int j = 1; j < nums.length; ++j) {
                    nums[j - 1] = nums[j];
                }
                nums[nums.length - 1] = v;
            }
            assertEquals(ao.findMin(nums), 0);
        }
    }

    @Test
    public void testSearchInRotatedSortedArray() {
        var ao = new ArraySearch();
        {
            int[] nums = { 2, 5, 6, 0, 0, 1, 2 };
            assertTrue(ao.searchInRotatedSortedArray(nums, 0));
            assertTrue(ao.searchInRotatedSortedArray(nums, 1));
            assertTrue(ao.searchInRotatedSortedArray(nums, 2));
            assertFalse(ao.searchInRotatedSortedArray(nums, 3));
            assertFalse(ao.searchInRotatedSortedArray(nums, 4));
            assertFalse(ao.searchInRotatedSortedArray(nums, 7));
            assertFalse(ao.searchInRotatedSortedArray(nums, -1));
            assertFalse(ao.searchInRotatedSortedArray(nums, -10));
            assertTrue(ao.searchInRotatedSortedArray(nums, 6));
        }
        {
            int[] nums = { 1, 1, 1, 3, 1, 1, 1, 1 };
            assertFalse(ao.searchInRotatedSortedArray(nums, 0));
            assertTrue(ao.searchInRotatedSortedArray(nums, 1));
            assertFalse(ao.searchInRotatedSortedArray(nums, 2));
            assertTrue(ao.searchInRotatedSortedArray(nums, 3));
            assertFalse(ao.searchInRotatedSortedArray(nums, 4));
            assertFalse(ao.searchInRotatedSortedArray(nums, 7));
            assertFalse(ao.searchInRotatedSortedArray(nums, -1));
            assertFalse(ao.searchInRotatedSortedArray(nums, -10));
            assertFalse(ao.searchInRotatedSortedArray(nums, 6));
        }
    }

    @Test
    public void testSortColors() {
        var ao = new ArraySearch();
        {
            int[] array = { 2, 0, 0, 0, 0, 1, 0, 0, 1 };
            ao.sortColors(array);
            assertTrue(isSorted(array));
        }
        {
            int[] array = { 0, 0, 0, 0, 0 };
            ao.sortColors(array);
            assertTrue(isSorted(array));
        }
        {
            int[] array = { 1, 1, 1, 1, 1 };
            ao.sortColors(array);
            assertTrue(isSorted(array));
        }
        {
            int[] array = { 2, 2, 2, 2, 2 };
            ao.sortColors(array);
            assertTrue(isSorted(array));
        }
        {
            int[] array = { 2, 0, 2, 1, 1, 0 };
            ao.sortColors(array);
            assertTrue(isSorted(array));
        }
        {
            int[] array = { 2, 0, 1 };
            ao.sortColors(array);
            assertTrue(isSorted(array));
        }
        {
            int[] array = { 0 };
            ao.sortColors(array);
            assertTrue(isSorted(array) && array[0] == 0);
        }
        {
            int[] array = { 1 };
            ao.sortColors(array);
            assertTrue(isSorted(array) && array[0] == 1);
        }
        {
            int[] array = { 2 };
            ao.sortColors(array);
            assertTrue(isSorted(array) && array[0] == 2);
        }
    }

    @Test
    public void testFindKthLargest() {
        var ao = new ArraySearch();
        int[] template = { 3, 2, 3, 1, 2, 4, 5, 5, 6, 7, 2, 0, 8 };
        int[] results = { 8, 7, 6, 5, 5, 4, 3, 3, 2, 2, 2, 1, 0 };
        for (int k = 1, n = template.length; k <= n; ++k) {
            int[] nums = new int[n];
            System.arraycopy(template, 0, nums, 0, n);
            var r = ao.findKthLargest(nums, k);
            assertEquals(r, results[k - 1]);
        }
    }

    @Test
    public void testHIndex() {
        var ao = new ArraySearch();
        {
            int[] citations = { 3, 0, 6, 1, 5 };
            var r = ao.hIndex(citations);
            assertEquals(r, 3);
        }
        {
            int[] citations = { 0, 0, 0, 0, 0, 0 };
            var r = ao.hIndex(citations);
            assertEquals(r, 0);
        }
        {
            int[] citations = { 0, 1, 0, 0, 2, 0 };
            var r = ao.hIndex(citations);
            assertEquals(r, 1);
        }
        {
            int[] citations = { 30, 20, 10, 4 };
            var r = ao.hIndex(citations);
            assertEquals(r, 4);
        }
        {
            int[] citations = { 4, 0, 6, 1, 5, 7 };
            var r = ao.hIndex(citations);
            assertEquals(r, 4);
        }
        {
            int[] citations = { 4, 4, 0, 0 };
            var r = ao.hIndex(citations);
            assertEquals(r, 2);
        }
    }

    @Test
    public void testBinarySearchInRepetitiveElements() {
        int[] nums = { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6 };
        int r = ArraySearch.binarySearchInRepetitiveElements(nums, 0, nums.length, 0);
        assertEquals(r, 0);
        r = ArraySearch.binarySearchInRepetitiveElements(nums, 0, nums.length, 1);
        assertEquals(r, 0);
        r = ArraySearch.binarySearchInRepetitiveElements(nums, 0, nums.length, 2);
        assertEquals(r, 1);
        r = ArraySearch.binarySearchInRepetitiveElements(nums, 2, nums.length, 2);
        assertEquals(r, 2);
        r = ArraySearch.binarySearchInRepetitiveElements(nums, 0, nums.length, 3);
        assertEquals(r, 3);
        r = ArraySearch.binarySearchInRepetitiveElements(nums, 4, nums.length, 3);
        assertEquals(r, 4);
        r = ArraySearch.binarySearchInRepetitiveElements(nums, 5, nums.length, 3);
        assertEquals(r, 5);
        r = ArraySearch.binarySearchInRepetitiveElements(nums, 0, nums.length, 4);
        assertEquals(r, 6);
        r = ArraySearch.binarySearchInRepetitiveElements(nums, 7, nums.length, 4);
        assertEquals(r, 7);
        r = ArraySearch.binarySearchInRepetitiveElements(nums, 8, nums.length, 4);
        assertEquals(r, 8);
        r = ArraySearch.binarySearchInRepetitiveElements(nums, 9, nums.length, 4);
        assertEquals(r, 9);
        r = ArraySearch.binarySearchInRepetitiveElements(nums, 0, nums.length, 5);
        assertEquals(r, 10);
        r = ArraySearch.binarySearchInRepetitiveElements(nums, 0, nums.length, 6);
        assertEquals(r, 15);
        r = ArraySearch.binarySearchInRepetitiveElements(nums, 0, nums.length, 7);
        assertEquals(r, nums.length);
    }

    @Test
    public void testIntersect() {
        var ao = new ArraySearch();
        {
            int[] nums1 = { 1, 2, 2, 1 };
            int[] nums2 = { 2, 2 };
            var r = ao.intersect(nums1, nums2);
            int[] expectation = { 2, 2 };
            assertTrue(ArrayOperationsTest.equals(r, expectation));
        }
        {
            int[] nums1 = { 4, 9, 5 };
            int[] nums2 = { 9, 4, 9, 8, 4 };
            var r = ao.intersect(nums1, nums2);
            int[] expectation = { 4, 9 };
            assertTrue(ArrayOperationsTest.equals(r, expectation));
        }
        {
            int[] nums1 = { 4, 9, 5, 9, 2, 10, 4, 0, 2, 7 };
            int[] nums2 = { 9, 4, 9, 8, -1, 4, 0, 16, 27, 32 };
            var r = ao.intersect(nums1, nums2);
            int[] expectation = { 0, 4, 4, 9, 9 };
            assertTrue(ArrayOperationsTest.equals(r, expectation));
        }
    }
}
