require 'testit.h';

proc foo() {
  writeln("Hello!");
}

extern proc bar(f);

proc baz(f) {
  f();
}

bar(c_FnPtrTo(foo));
baz(foo);

//foo();