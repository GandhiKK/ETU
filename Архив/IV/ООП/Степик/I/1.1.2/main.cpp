class A
{
public:
  A() {};

private:
   A(const A&) = delete;
   A& operator=(const A&) = delete;
};