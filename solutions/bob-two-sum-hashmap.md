# Bob Wilson - Two Sum (Hash Map)

**Problem:** Two Sum  
**Author:** Bob Wilson  
**Language:** Python  
**Approach:** Hash Map for O(n) solution  

## Description
This solution uses a hash map to store previously seen numbers and their indices, allowing us to find the complement in O(1) time.

## Time Complexity
- **Time:** O(n) where n is the length of the array
- **Space:** O(n) for the hash map in worst case

## Code
```python
def two_sum(nums, target):
    """
    Find two numbers in the array that add up to target using hash map
    Returns the indices of the two numbers
    """
    num_map = {}  # number -> index mapping
    
    for i, num in enumerate(nums):
        complement = target - num
        
        # Check if complement exists in our map
        if complement in num_map:
            return [num_map[complement], i]
        
        # Store current number and its index
        num_map[num] = i
    
    return []  # No solution found
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

# Test case 3
nums = [3, 3]
target = 6
result = two_sum(nums, target)
print(result)  # Expected: [0, 1]
```

## Pros
- O(n) time complexity - much more efficient
- Single pass through the array
- Elegant and clean solution

## Cons
- O(n) space complexity due to hash map
- Slightly more complex than brute force

## Key Insight
By storing numbers as we iterate and checking for the complement, we can solve this in a single pass!