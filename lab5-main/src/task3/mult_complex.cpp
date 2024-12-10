#include <CL/sycl.hpp>
#include <iomanip>
#include <vector>
#include "dpc_common.hpp"
#include "Complex.hpp"

using namespace sycl;
using namespace std;

// Número de números complejos que se procesarán en el código DPC++
static const int num_elements = 10000;

void DpcppParallel(queue &q, std::vector<Complex2> &in_vect1,
                   std::vector<Complex2> &in_vect2,
                   std::vector<Complex2> &out_vect)
{
  auto R = range(in_vect1.size());

  buffer bufin_vect1(in_vect1);
  buffer bufin_vect2(in_vect2);
  buffer bufout_vect(out_vect);

  std::cout << "Target Device: " << q.get_device().get_info<info::device::name>() << std::endl;

  q.submit([&](auto &h)
           {
             // Accessors configurados correctamente
             accessor V1(bufin_vect1, h, read_only);
             accessor V2(bufin_vect2, h, read_only);
             accessor V3(bufout_vect, h, write_only);

             h.parallel_for(R, [=](auto i)
                            {
                              // Multiplicación de números complejos
                              V3[i] = V1[i].complex_mul(V2[i]);
                            });
           });

  // Esperar la finalización de las tareas en la cola
  q.wait();
}

void DpcppScalar(std::vector<Complex2> &in_vect1,
                 std::vector<Complex2> &in_vect2,
                 std::vector<Complex2> &out_vect)
{
  for (int i = 0; i < in_vect1.size(); i++)
  {
    out_vect[i] = in_vect1[i].complex_mul(in_vect2[i]);
  }
}

// Comparar los resultados de las salidas paralelas y escalares. Deben ser iguales.
int Compare(std::vector<Complex2> &v1, std::vector<Complex2> &v2)
{
  int ret_code = 1;
  if (v1.size() != v2.size())
  {
    ret_code = -1;
  }
  for (int i = 0; i < v1.size(); i++)
  {
    if (v1[i] != v2[i])
    {
      ret_code = -1;
      break;
    }
  }
  return ret_code;
}

int main()
{
  // Declarar vectores de entrada y salida para números complejos
  vector<Complex2> input_vect1;
  vector<Complex2> input_vect2;
  vector<Complex2> out_vect_parallel;
  vector<Complex2> out_vect_scalar;

  for (int i = 0; i < num_elements; i++)
  {
    input_vect1.push_back(Complex2(i + 2, i + 4));
    input_vect2.push_back(Complex2(i + 4, i + 6));
    out_vect_parallel.push_back(Complex2(0, 0));
    out_vect_scalar.push_back(Complex2(0, 0));
  }

  cpu_selector selector;
  queue q(selector, dpc_common::exception_handler);

  // Llamar a DpcppParallel con los vectores requeridos
  DpcppParallel(q, input_vect1, input_vect2, out_vect_parallel);

  std::cout << "****************************************Multiplying Complex numbers "
               "in Parallel****************************************" << std::endl;

  // Imprimir los resultados de la función paralela
  int indices[]{0, 1, 2, 3, 4, (num_elements - 1)};
  constexpr size_t indices_size = sizeof(indices) / sizeof(int);

  for (int i = 0; i < indices_size; i++)
  {
    int j = indices[i];
    if (i == indices_size - 1)
      std::cout << "...\n";
    std::cout << "[" << j << "] " << input_vect1[j] << " * " << input_vect2[j]
              << " = " << out_vect_parallel[j] << "\n";
  }

  // Llamar a la función escalar
  DpcppScalar(input_vect1, input_vect2, out_vect_scalar);

  // Comparar resultados
  int ret_code = Compare(out_vect_parallel, out_vect_scalar);
  if (ret_code == 1)
  {
    std::cout << "Complex multiplication successfully run on the device" << "\n";
  }
  else
    std::cout << "*********************************************Verification Failed. Results are "
           "not matched**************************" << "\n";

  return 0;
}
