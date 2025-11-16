#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Book {
public:
  std::string title;
  std::string author;
  std::string genre;
  unsigned int publication_year;
};

class FunctorCmp
{
public:
  bool operator()(const Book& first, const Book& second) const
  {
    return first.author.compare(second.author) < 0;
  }
};

void print(const std::vector<Book> &books) {
  for (const Book &book : books) {
    std::cout << "  Title: " << book.title << " | Author: " << book.author
              << " | Genre: " << book.genre
              << " | Year: " << book.publication_year << std::endl;
  }
}

bool comp_by_date(const Book& first, const Book& second)
{
  return first.publication_year < second.publication_year;
}

int main() {
  // Define a list of books.
  std::vector<Book> books = {
      {"Go set a watchman", "Harper Lee", "Fiction", 2015},
      {"Animal farm", "George Orwell", "Satire", 1945},
      {"To kill a mockingbird", "Harper Lee", "Fiction", 1960},
      {"1984", "George Orwell", "Science fiction", 1949},
      {"Pride and prejudice", "Jane Austen", "Romance", 1813},
      {"Sense and sensibility", "Jane Austen", "Romance", 1811}};

  std::cout << "Original list of books:" << std::endl;
  print(books);
  std::cout << std::endl;

  // Sort in ascending order by year using a function pointer as a comparator.
  const auto cmp = &comp_by_date;
  std::sort(books.begin(), books.end(), cmp);
  std::cout << "Ordered by date (ascending) using function pointer:" << std::endl;
  print(books);
  std::cout << std::endl;

  // Sort in descending order by year using a lambda function as a comparator.
  std::sort(books.begin(), books.end(), [](const Book& first, const Book& second) { return first.publication_year > second.publication_year; });
  std::cout << "Ordered by date (descending) using lambda function:" << std::endl;
  print(books);
  std::cout << std::endl;

  // Sort in ascending order by author name using a functor as a comparator.
  const auto fct_cmp = FunctorCmp();
  std::sort(books.begin(), books.end(), fct_cmp);
  std::cout << "Ordered by author name (ascending) using functor:" << std::endl;
  print(books);
  std::cout << std::endl;

  // Filter books by author using lambdas.
  auto filtered_books = std::vector<Book>(books.size());
  std::string filter = "Harper Lee";
  std::copy_if(books.begin(), books.end(), filtered_books.begin(), [&](const Book& b)
  {
    return b.author == filter;
  });
  std::cout << "Filtered books written by Harper Lee using lambda:" << std::endl;
  print(filtered_books);
  std::cout << std::endl;

  return 0;
}
