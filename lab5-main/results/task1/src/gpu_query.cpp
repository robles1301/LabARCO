#include <CL/sycl.hpp>

// This allows us to remove cl::sycl:: from all invocations
using namespace cl::sycl;

int main() {
    gpu_selector selector;

    queue q(selector);

    std::cout << "Device: " << q.get_device().get_info<info::device::name>() << std::endl;

    return 0;
}

