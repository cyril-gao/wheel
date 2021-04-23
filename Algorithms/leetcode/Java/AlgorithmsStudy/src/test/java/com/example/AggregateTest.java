package com.example;

import java.util.*;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertTrue;
import org.testng.annotations.*;

public class AggregateTest {
    @Test
    public void testThreeSum() {
        var agg = new Aggregate();
        {
            int[] nums = { -1, 0, 1, 2, -1, -4 };
            var result = agg.threeSum(nums);
            assertEquals(result.size(), 2);
            List<Integer> l1 = new ArrayList<>(3);
            l1.add(-1);
            l1.add(-1);
            l1.add(2);
            List<Integer> l2 = new ArrayList<>(3);
            l2.add(-1);
            l2.add(0);
            l2.add(1);
            assertTrue(result.get(0).equals(l1) || result.get(0).equals(l2));
            assertTrue(result.get(1).equals(l1) || result.get(1).equals(l2));
        }
        {
            int[] nums = { 0 };
            var result = agg.threeSum(nums);
            assertTrue(result.isEmpty());
        }
        {
            int[] nums = { -1, 0, 1, 2, -1, -4 };
            var result = agg.threeSum(nums);
            assertEquals(result.size(), 2);
        }
        {
            int[] nums = { -1, 0, 1, -10, 8, 4, -11, 6, 9, -21, -8, 8, 2, -1, -4 };
            var result = agg.threeSum(nums);
            assertEquals(result.size(), 10);
        }
    }

    @Test
    public void testThreeSumClosest() {
        var agg = new Aggregate();
        {
            int[] nums = { -1, 0, 1, 2, -1, -4 };
            assertEquals(agg.threeSumClosest(nums, 0), 0);
        }
        {
            int[] nums = { -1, 2, 1, -4 };
            assertEquals(agg.threeSumClosest(nums, 1), 2);
        }
        {
            int[] nums = { 0, 0, 0 };
            assertEquals(agg.threeSumClosest(nums, 1), 0);
        }
        {
            int[] nums = { 0, 2, 1, -3 };
            assertEquals(agg.threeSumClosest(nums, 1), 0);
        }
        {
            int[] nums = { 1, 2, 4, 8, 16, 32, 64, 128 };
            assertEquals(agg.threeSumClosest(nums, 82), 82);
        }
        {
            int[] nums = { -1, 2, 1, -4, -11, -3, 8, -6, 7, 9, -28, 17, 48, 23, 3, 5, -9, 27 };
            assertEquals(agg.threeSumClosest(nums, 21), 21);
        }
    }

    @Test
    public void testFourSum() {
        var agg = new Aggregate();
        {
            int[] nums = { 1, 0, -1, 0, -2, 2 };
            var result = agg.fourSum(nums, 0);
            assertEquals(result.size(), 3);
        }
        {
            int[] input = { 1, 0, -1, 0, -2, 2 };
            var result = agg.fourSum(input, 0);
            assertEquals(result.size(), 3);
        }
        {
            int[] input = { -3, -2, -1, 0, 0, 1, 2, 3 };
            var result = agg.fourSum(input, 0);
            assertEquals(result.size(), 8);
        }
        {
            int[] input = { -1, 0, -5, -2, -2, -4, 0, 1, -2 };
            var result = agg.fourSum(input, -9);
            assertEquals(result.size(), 4);
        }
    }

    @Test
    public void testTwoSumForSortedArray() {
        var agg = new Aggregate();
        {
            int[] nums = { 2, 7, 11, 15 };
            int target = 9;
            var result = agg.twoSumForSortedArray(nums, target);
            assertTrue(result.length == 2 && result[0] == 1 && result[1] == 2);
        }
        {
            int[] nums = { 2, 3, 4 };
            int target = 6;
            var result = agg.twoSumForSortedArray(nums, target);
            assertTrue(result.length == 2 && result[0] == 1 && result[1] == 3);
        }
        {
            int[] nums = { -8, -1, 0, 2, 3 };
            int target = -1;
            var result = agg.twoSumForSortedArray(nums, target);
            assertTrue(result.length == 2 && result[0] == 2 && result[1] == 3);
        }
    }
}
