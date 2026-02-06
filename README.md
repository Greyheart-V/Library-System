# Library-System
1. Why I used Vectors instead of Arrays

"I chose to use vectors (like vector<Book>) instead of normal arrays because arrays have a fixed size. A real library is always buying new books, so I needed a list that could grow automatically whenever I added a new item. Vectors handle that resizing for me, which makes the code much cleaner."
2. How the "Search" works

"For the search, I kept it simple. The code just loops through the list of books one by one. If the title matches what the user typed in, it stops and shows the book details. It’s a standard linear search, which is easy to understand and works perfectly for this assignment."
3. My Unique Features (The "Bonus" Marks)

"I wanted to add some logic that felt like a real-world system, so I added two things:"

    Teacher vs. Student Limits: "I figured teachers usually need more resources than students. So, I added a userType check. If you are a 'Teacher', the system lets you borrow up to 5 books. If you are a 'Student', it stops you at 3."

    Damaged Books: "Real books get torn or damaged. I added a condition variable to the Book class. The system doesn't stop you from borrowing a damaged book, but it gives you a warning message so you know to be careful. I thought that was a nice detail to include."

4. The "Remove" Function (The Tricky Part)

"Deleting a book was the only part where I had to look up a specific C++ command. I used books.erase(). Since vectors store things in a line, I had to tell it exactly where to cut. I did this by saying books.begin() + i, which basically points to the exact slot where the book was sitting and removes it."
