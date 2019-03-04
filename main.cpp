#include <iostream>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <Python.h>

//using namespace std;

class AsyncBase : boost::noncopyable {
public:
    AsyncBase() = default;
    void Clone() { return;
      nullptr; };
private:
    void* data;
};

void DoWork()
{
  printf("task done\n");
}

int ustr_find(std::string& s, std::string& sub, size_t offset = 0)
{
  int len = 0;
  size_t pos = s.find(sub, offset);
  if (pos == std::string::npos) {
    return -1;
  }
  std::string::iterator it = s.begin();
  while (it != s.begin() + pos) {
    len += ((*it++) & 0xc0 != 0x80);
  }
  return len;
}

void ustr_find_all(std::string& s, std::string& sub)
{
  std::vector<int> positions;
  int pos = 0;
}


int main() {
  boost::thread thr;
  PyObject *k;
  Py_Initialize();
  PyRun_SimpleString("print('lollipop')");
  Py_Finalize();
  return 0;
}