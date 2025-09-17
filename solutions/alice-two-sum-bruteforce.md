# Alice Chen - Two Sum (Brute Force)

**Problem:** Two Sum  
**Author:** Alice Chen  
**Language:** Python  
**Approach:** Brute Force with nested loops  

## Description
This solution uses a straightforward brute force approach with nested loops to check all possible pairs of numbers in the array.

## Time Complexity
- **Time:** O(n²) where n is the length of the array
- **Space:** O(1) constant extra space

## Code
```python
def two_sum(nums, target):
    """
    Find two numbers in the array that add up to target
    Returns the indices of the two numbers
    """
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            if nums[i] + nums[j] == target:
                return [i, j]
    return []
```

## Test Cases
```python
# Test case 1
nums = [2, 7, 11, 15]
target = 9
result = two_sum(nums, target)
print(result)  # Expected: [0, 1]

# Test case 2
nums = [3, 2, 4]
target = 6
result = two_sum(nums, target)
print(result)  # Expected: [1, 2]
```

## Pros
- Simple and easy to understand
- No extra space required
- Works for all valid inputs

## Cons
- O(n²) time complexity is inefficient for large arrays
- Not optimal for performance-critical applications