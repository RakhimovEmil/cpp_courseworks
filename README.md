# cpp_courseworks

## unique_ptr

To ensure uniqueness of ownership, `unique_ptr` can only be created from temporary values. Class is implemented based on tests:

  * template argument - type of stored value
  * cannot be copied, but can be moved
  * make_unique method with 0...2 parameters
    * must support perfect-forwarding

Example of usage: 
```
cls09::unique_ptr<int> ptr1{new int{10}};
cls09::unique_ptr<int> ptr2{ptr1.release()};

assert(!ptr1 && ptr1.get() == nullptr);
assert(ptr2 && *ptr2 == 10);

auto ptr = cls09::make_unique<std::string>(10, 'a');
assert(*ptr == "aaaaaaaaaa");

auto ptr2 = cls09::make_unique<std::string>(*ptr);
assert(*ptr == *ptr2);

auto ptr3 = cls09::make_unique<std::string>();
assert(ptr3->empty());
```

## queue

FIFO `queue` implementation based on a custom template linked list. 

Example of usage: 
```
static_assert(std::is_move_constructible_v<cls_08::queue<std::string>>);
cls_08::queue<std::string> q;

q.push("42");
q.push("24");
assert(q.size() == 2);

std::string tmp = "tmp";
q.push(std::move(tmp));

assert(q.size() == 3);

cls_08::queue<std::string> qCopy{std::move(q)};
assert(q.size() == 0);
assert(qCopy.size() == 3);
```


## LazyString

The implementation of a string that: 

  * is cheaply copied (compared to std::string)
  * with modifier methods (compared to std::string_view)
  * ⇒ it will store its data

The implementation is via the Copy-on-Write paradigm, so the data is in the heap and can be shared across multiple objects (if the object changes, it is copied first).

The auxiliary class for the `LazyString` class is the `SharedBuffer` class:

  * `SharedBuffer` stores in itself (in a heap) an array of char and its size
  * The data does not have to be null-terminated! their size is exactly known.
  * several such objects can reference the same memory space
  * when the last of them is cleared, this memory area is also cleared

```
SharedBuffer buffer { 10 };
assert(buffer.useCount() == 1);
SharedBuffer const ref = buffer;
assert(buffer.useCount() == 2);
assert(ref.useCount() == 2);

assert(buffer.getSize() == 10);
assert(ref.getSize() == 10);

LazyString s1 = "Hello world";
assert(s1.useCount() == 1);
LazyString const s2 = s1;
assert(s1.useCount() == 2);

assert(s2.getSize() == s1.getSize());
assert(s1.cStr() == s2.cStr());

assert(s1.getSize() == sizeof("Hello world") - 1);
assert(std::strcmp(s1.cStr(), "Hello world") == 0);
```

Also implemented `LazyString::operator[]`, which returns a special wrapper over the string character (`CharWrapper`)

  * partially supporting char& interface: the element can be compared, assigned, incremented
  * if useCount > 1:
    * string copying does not occur during read-only instructions (s[2] == 'a')
    * but only on data changes (s[2] = 'a')


## json_value

Implemented json - structure, the values of which can be: `null`, `int`, unicode string bytes (`std::string`), array of jsons

```
JsonValue j;
assert(j.IsNull());

// switch to int
j = 42;
assert(j.GetInt() + 24 == 66);

// switch to array, implicitly
j.Append(42);
j.Append("foo");
j[0] = "ok";
j[1].Append(',');
j.Append(" bye");

cls07::Json::JsonValue::StringType sum = j[0].GetString() + j[1][0].GetString() + j[2].GetString();
assert(sum == "ok, bye");
```
