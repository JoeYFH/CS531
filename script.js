// CS531 Code Review Dashboard JavaScript

// Data storage (in a real application, this would be a database)
let problems = [];
let solutions = [];

// Initialize the application
document.addEventListener('DOMContentLoaded', function() {
    initializeApp();
});

function initializeApp() {
    // Load sample data
    loadSampleData();
    
    // Set up event listeners
    setupEventListeners();
    
    // Show default section
    showSection('problems');
    
    // Update UI
    updateProblemsDisplay();
    updateProblemSelects();
    updateSolutionsDisplay();
}

function loadSampleData() {
    // Sample problems
    problems = [
        {
            id: 1,
            title: "Two Sum",
            description: "Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.",
            createdDate: new Date('2024-01-15')
        },
        {
            id: 2,
            title: "Reverse String",
            description: "Write a function that reverses a string. The input string is given as an array of characters s.",
            createdDate: new Date('2024-01-20')
        },
        {
            id: 3,
            title: "Palindrome Check",
            description: "Given a string s, return true if it is a palindrome, or false otherwise.",
            createdDate: new Date('2024-01-25')
        }
    ];

    // Sample solutions
    solutions = [
        {
            id: 1,
            problemId: 1,
            studentName: "Alice Chen",
            description: "Brute force approach with nested loops",
            code: `def two_sum(nums, target):
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            if nums[i] + nums[j] == target:
                return [i, j]
    return []`,
            language: "python",
            uploadDate: new Date('2024-01-16')
        },
        {
            id: 2,
            problemId: 1,
            studentName: "Bob Wilson",
            description: "Optimized solution using hash map",
            code: `def two_sum(nums, target):
    num_map = {}
    for i, num in enumerate(nums):
        complement = target - num
        if complement in num_map:
            return [num_map[complement], i]
        num_map[num] = i
    return []`,
            language: "python",
            uploadDate: new Date('2024-01-17')
        },
        {
            id: 3,
            problemId: 2,
            studentName: "Carol Davis",
            description: "Using built-in reverse function",
            code: `public void reverseString(char[] s) {
    int left = 0, right = s.length - 1;
    while (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
}`,
            language: "java",
            uploadDate: new Date('2024-01-21')
        }
    ];
}

function setupEventListeners() {
    // Upload form submission
    document.getElementById('upload-form').addEventListener('submit', handleSolutionUpload);
    
    // Review filters
    document.getElementById('review-problem-filter').addEventListener('change', updateSolutionsDisplay);
    document.getElementById('review-language-filter').addEventListener('change', updateSolutionsDisplay);
}

function showSection(sectionName) {
    // Hide all sections
    const sections = document.querySelectorAll('.content-section');
    sections.forEach(section => {
        section.style.display = 'none';
    });
    
    // Show selected section
    document.getElementById(sectionName).style.display = 'block';
    
    // Update navigation
    const navLinks = document.querySelectorAll('nav a');
    navLinks.forEach(link => {
        link.style.background = '';
        link.style.color = '#333';
    });
    
    const activeLink = document.querySelector(`nav a[href="#${sectionName}"]`);
    if (activeLink) {
        activeLink.style.background = '#667eea';
        activeLink.style.color = 'white';
    }
}

function updateProblemsDisplay() {
    const problemsList = document.getElementById('problems-list');
    
    if (problems.length === 0) {
        problemsList.innerHTML = '<p>No problems available yet. Add a new problem to get started!</p>';
        return;
    }
    
    const problemsHTML = problems.map(problem => {
        const solutionCount = solutions.filter(s => s.problemId === problem.id).length;
        return `
            <div class="problem-card">
                <div class="problem-title">${problem.title}</div>
                <div class="problem-description">${problem.description}</div>
                <div class="problem-meta">
                    <span class="meta-item">Solutions: ${solutionCount}</span>
                    <span class="meta-item">Created: ${problem.createdDate.toLocaleDateString()}</span>
                </div>
                <div class="mt-2">
                    <button onclick="viewProblemSolutions(${problem.id})" class="btn btn-primary">View Solutions</button>
                    <button onclick="uploadSolutionForProblem(${problem.id})" class="btn btn-secondary">Upload Solution</button>
                </div>
            </div>
        `;
    }).join('');
    
    problemsList.innerHTML = problemsHTML;
}

function updateProblemSelects() {
    const selects = ['problem-select', 'review-problem-filter'];
    
    selects.forEach(selectId => {
        const select = document.getElementById(selectId);
        const currentValue = select.value;
        
        // Clear existing options (except the first one for problem-select)
        if (selectId === 'problem-select') {
            select.innerHTML = '<option value="">-- Select a Problem --</option>';
        } else {
            select.innerHTML = '<option value="">-- All Problems --</option>';
        }
        
        // Add problem options
        problems.forEach(problem => {
            const option = document.createElement('option');
            option.value = problem.id;
            option.textContent = problem.title;
            select.appendChild(option);
        });
        
        // Restore previous selection
        select.value = currentValue;
    });
}

function updateSolutionsDisplay() {
    const solutionsList = document.getElementById('solutions-list');
    const problemFilter = document.getElementById('review-problem-filter').value;
    const languageFilter = document.getElementById('review-language-filter').value;
    
    let filteredSolutions = solutions;
    
    // Apply filters
    if (problemFilter) {
        filteredSolutions = filteredSolutions.filter(s => s.problemId == problemFilter);
    }
    
    if (languageFilter) {
        filteredSolutions = filteredSolutions.filter(s => s.language === languageFilter);
    }
    
    if (filteredSolutions.length === 0) {
        solutionsList.innerHTML = '<p>No solutions found matching the current filters.</p>';
        return;
    }
    
    const solutionsHTML = filteredSolutions.map(solution => {
        const problem = problems.find(p => p.id === solution.problemId);
        const problemTitle = problem ? problem.title : 'Unknown Problem';
        
        return `
            <div class="solution-card">
                <div class="solution-header">
                    <div>
                        <h3>${problemTitle}</h3>
                        <p><strong>By:</strong> ${solution.studentName}</p>
                    </div>
                    <div class="solution-meta">
                        <span class="meta-item">${solution.language}</span>
                        <span class="meta-item">${solution.uploadDate.toLocaleDateString()}</span>
                    </div>
                </div>
                ${solution.description ? `<p><strong>Description:</strong> ${solution.description}</p>` : ''}
                <div class="code-block">${solution.code}</div>
                <div class="mt-2">
                    <button onclick="addReviewComment(${solution.id})" class="btn btn-primary">Add Review Comment</button>
                    <button onclick="compareSolutions(${solution.problemId})" class="btn btn-secondary">Compare Solutions</button>
                </div>
            </div>
        `;
    }).join('');
    
    solutionsList.innerHTML = solutionsHTML;
}

function handleSolutionUpload(event) {
    event.preventDefault();
    
    const problemId = parseInt(document.getElementById('problem-select').value);
    const studentName = document.getElementById('student-name').value.trim();
    const description = document.getElementById('solution-description').value.trim();
    const code = document.getElementById('code-input').value.trim();
    const language = document.getElementById('language-select').value;
    
    if (!problemId || !studentName || !code) {
        alert('Please fill in all required fields.');
        return;
    }
    
    // Create new solution
    const newSolution = {
        id: solutions.length + 1,
        problemId: problemId,
        studentName: studentName,
        description: description,
        code: code,
        language: language,
        uploadDate: new Date()
    };
    
    solutions.push(newSolution);
    
    // Reset form
    document.getElementById('upload-form').reset();
    
    // Update displays
    updateProblemsDisplay();
    updateSolutionsDisplay();
    
    // Show success message
    alert('Solution uploaded successfully!');
    
    // Switch to review section
    showSection('review');
}

function addNewProblem() {
    const title = prompt('Enter problem title:');
    if (!title) return;
    
    const description = prompt('Enter problem description:');
    if (!description) return;
    
    const newProblem = {
        id: problems.length + 1,
        title: title.trim(),
        description: description.trim(),
        createdDate: new Date()
    };
    
    problems.push(newProblem);
    updateProblemsDisplay();
    updateProblemSelects();
    
    alert('Problem added successfully!');
}

function viewProblemSolutions(problemId) {
    // Set filter and switch to review section
    document.getElementById('review-problem-filter').value = problemId;
    updateSolutionsDisplay();
    showSection('review');
}

function uploadSolutionForProblem(problemId) {
    // Set problem and switch to upload section
    document.getElementById('problem-select').value = problemId;
    showSection('upload');
}

function addReviewComment(solutionId) {
    const comment = prompt('Enter your review comment:');
    if (comment) {
        alert(`Review comment added for solution ${solutionId}: "${comment}"`);
        // In a real application, this would save the comment to the database
    }
}

function compareSolutions(problemId) {
    const problemSolutions = solutions.filter(s => s.problemId === problemId);
    if (problemSolutions.length < 2) {
        alert('Need at least 2 solutions to compare.');
        return;
    }
    
    const problem = problems.find(p => p.id === problemId);
    const problemTitle = problem ? problem.title : 'Unknown Problem';
    
    // Create comparison view
    const comparisonWindow = window.open('', '_blank', 'width=1200,height=800');
    const comparisonHTML = `
        <!DOCTYPE html>
        <html>
        <head>
            <title>Solution Comparison - ${problemTitle}</title>
            <style>
                body { font-family: Arial, sans-serif; margin: 20px; }
                .solution { border: 1px solid #ccc; margin: 20px 0; padding: 15px; }
                .code { background: #f5f5f5; padding: 10px; font-family: monospace; white-space: pre-wrap; }
                h1 { color: #333; }
                h3 { color: #666; }
            </style>
        </head>
        <body>
            <h1>Solution Comparison: ${problemTitle}</h1>
            ${problemSolutions.map(solution => `
                <div class="solution">
                    <h3>${solution.studentName} (${solution.language})</h3>
                    <p><strong>Description:</strong> ${solution.description || 'No description provided'}</p>
                    <div class="code">${solution.code}</div>
                </div>
            `).join('')}
        </body>
        </html>
    `;
    
    comparisonWindow.document.write(comparisonHTML);
    comparisonWindow.document.close();
}