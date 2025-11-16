#include <iostream>
#include <numeric>
#include <string>
#include <vector>

class Product {
public:
  std::string name;
  double price;
};

void print(const std::vector<Product> &products) {
  for (const Product &product : products) {
    std::cout << product.name << ":\t$" << product.price << std::endl;
  }
}

int main() {
  // Define a list of products.
  const std::vector<Product> products = {{"Smartphone", 799.99},
                                         {"Laptop", 1299.99},
                                         {"Tablet", 349.99},
                                         {"Headphones", 99.99},
                                         {"Smartwatch", 249.99}};

  std::cout << "List of products:" << std::endl;
  print(products);
  std::cout << std::endl;

  // Compute total cost.
  const double tot_cost = std::accumulate(products.begin(), products.end(), 0.0, [] (double result, const Product &product)
  {
    std::cout << "Partial sum = " << result << std::endl;
    return result + product.price;
  });
  std::cout << std::endl;

  std::cout << "Total cost: " << tot_cost << std::endl;

  return 0;
}
