// This should generate a warning about not returning a value.

use IO;

proc foo(): int {
  var ret = 5;
  var externTyped: qio_file_ptr_t;
  // qio_file_ptr_t is an external type
  // We experienced an issue in the compiler where a method did not think it
  // had specified its return type if the method contained a separate variable
  // of an external type.
}

foo();
// Even when the result of foo is not stored in a variable, we should print a
// warning
writeln("I should print a warning");
