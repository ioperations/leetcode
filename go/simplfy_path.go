/*
Given a string path, which is an absolute path (starting with a slash '/') to a
file or directory in a Unix-style file system, convert it to the simplified
canonical path.
In a Unix-style file system, a period '.' refers to the current directory, a
double period '..' refers to the directory up a level, and any multiple
consecutive slashes (i.e. '//') are treated as a single slash '/'. For this
problem, any other format of periods such as '...' are treated as file/directory
names.

The canonical path should have the following format:

The path starts with a single slash '/'.
Any two directories are separated by a single slash '/'.
The path does not end with a trailing '/'.
The path only contains the directories on the path from the root directory to
the target file or directory (i.e., no period '.' or double period '..') Return
the simplified canonical path.
*/

package gomod

import "strings"

type Solution struct {
}

func (s *Solution) SimplifyPath(path string) string {
	// simplifyPath takes a string path and returns the simplified canonical path
	// in a Unix-style file system.

	// It uses a stack to keep track of the directories and handles special cases
	// like ".." and "." to navigate through the path correctly.
	// The final path is constructed by joining the directories in the stack with
	// slashes and ensuring it starts with a single slash.
	// The function returns the simplified path as a string.
	// Initialize a stack to keep track of directories
	stack := []string{}
	// Split the input path by slashes
	parts := strings.Split(path, "/")
	// Iterate through each part of the path
	for _, part := range parts {
		// If the part is empty or a single dot, skip it
		if part == "" || part == "." {
			continue
		}
		// If the part is "..", pop the last directory from the stack if it's not empty
		if part == ".." {
			if len(stack) > 0 {
				stack = stack[:len(stack)-1]
			}
			continue
		}
		// Otherwise, push the part onto the stack
		stack = append(stack, part)
	}
	// If the stack is empty, return the root directory
	if len(stack) == 0 {
		return "/"
	}
	// Join the directories in the stack with slashes and ensure it starts with a single slash
	simplifiedPath := "/" + strings.Join(stack, "/")
	// Return the simplified path
	return simplifiedPath
	// The function handles edge cases like empty paths, paths with only "..",
	// and paths with multiple consecutive slashes by using the stack to keep track
	// of the directories and ensuring the final path is correctly formatted.
	// The time complexity is O(n), where n is the length of the input path,
	// and the space complexity is O(n) for the stack.
	// The function is efficient and handles all edge cases correctly.
	// The function is also easy to understand and maintain, making it a good
	// solution for the problem.

}
