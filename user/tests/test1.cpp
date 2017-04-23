#include "../../lib/mutex/mutex_type.h"

int main() {
  mutex_t mu;
  mutex_create(&mu);
  return 1;
}