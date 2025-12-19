## Design decisions

### Module A: Statistics toolkit
Given a data source, computing the statistics required by the assignment
does not necessitate keeping track of a state. For this reason, the utility
methods of the class are implemented statically. The only state to manage
would be the one of the data source specified by the user, such as reading
data from a JSON or CSV file, but only in the case the user wants to preemptively
load all the data into memory, otherwise it can be read on the fly from the
file itself. As such, the toolkit is organized in this way:

- All the functions calculating statistics are implemented statically on vectors
- In case the user wants to use a file as a data source, it can do so by loading
all the data into the toolkit's state, or by reading it on the fly from the file.
In the former case, the data will be imported.
- Due to the static nature of libraries offering JSON and CSV support, the statistics
functions will use template programming to support and check for the appropriate 
data types.

### Module B: Integration toolkit
Similarly, integration doesn't offer many opportunities to use dynamic polymorphism.
This is because the assignment specifies the integration of real valued functions,
which correspond to basically one type on C++, _double_. For this reason, the various
types of integration techniques are implemented as static utility methods. Alternatively,
the user can obtain a _primitive_ std::function from a factory given a starting point
for integration and n. of subdivisions.

## References used
- [cppreference.com]()