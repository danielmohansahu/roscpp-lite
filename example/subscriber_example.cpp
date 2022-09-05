/* Example of a Subscriber created via roscpp-lite.
 */

// STL
#include <iostream>
#include <any>

// roscpp_lite
#include "roscpp_lite/subscriber.h"

// global variables
size_t message_count {0};
const std::string topic {"test"};

void callback(const std::any&)
{
  std::cout << " Got message #" << ++message_count << std::endl;
}

int main(int, char**)
{
  // construct the subscriber
  std::cout << "Creating a simple subscriber to topic '" << topic << "'..." << std::endl;
  roscpp_lite::Subscriber sub("example_subscriber", topic, callback);
  std::cout << "Subcriber constructed." << std::endl;

  // just hang out, I guess...
  std::cout << "Processing callbacks until shutdown..." << std::endl;
  while (true)
    sub.process();
}