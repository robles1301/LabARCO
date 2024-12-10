#include <CL/sycl.hpp>

using namespace cl::sycl;

int main() {
    try {
        // Attempt to select a GPU, fallback to default_selector if not available
        cpu_selector selector;
        queue q(selector);

        auto device = q.get_device();
        std::cout << "Device: " << device.get_info<info::device::name>() << std::endl;
        std::cout << "Vendor: " << device.get_info<info::device::vendor>() << std::endl;
        std::cout << "Driver version: " << device.get_info<info::device::driver_version>() << std::endl;
        std::cout << "Max compute units: " << device.get_info<info::device::max_compute_units>() << std::endl;
        std::cout << "Global memory size (bytes): " << device.get_info<info::device::global_mem_size>() << std::endl;
    } catch (exception const &e) {
        std::cerr << "SYCL exception caught: " << e.what() << std::endl;
    }
    return 0;
}
