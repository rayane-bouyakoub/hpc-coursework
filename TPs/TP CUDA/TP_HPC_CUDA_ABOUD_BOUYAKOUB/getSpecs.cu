/******************HPC TP CUDA 2024/2025******************/
/******************ABOUD IBRAHIM**************************/
/******************BOUYAKOUB RAYANE***********************/
/********CODE QUI AFFICHE LES SPECS DU GPU****************/

#include <iostream>
#include <cuda_runtime.h>

int main()
{
    int deviceCount;
    cudaError_t err = cudaGetDeviceCount(&deviceCount);

    if (err != cudaSuccess)
    {
        std::cerr << "CUDA error: " << cudaGetErrorString(err) << std::endl;
        return -1;
    }

    for (int device = 0; device < deviceCount; ++device)
    {
        cudaDeviceProp deviceProp;
        cudaGetDeviceProperties(&deviceProp, device);

        std::cout << "Device " << device << ": " << deviceProp.name << std::endl;
        std::cout << "  Compute capability: " << deviceProp.major << "." << deviceProp.minor << std::endl;

        std::cout << "  Multiprocessors (SMs): " << deviceProp.multiProcessorCount << std::endl;
        std::cout << "  CUDA cores per SM: " << (deviceProp.major == 7 ? 64 : 128) << std::endl; // Adjust for architecture
        std::cout << "  Total CUDA cores: " << (deviceProp.multiProcessorCount * (deviceProp.major == 7 ? 64 : 128)) << std::endl;
        std::cout << "  Warp size: " << deviceProp.warpSize << std::endl;
        std::cout << "  Shared memory per SM: " << deviceProp.sharedMemPerMultiprocessor / 1024.0 << " KB" << std::endl;
        std::cout << "  Registers per SM: " << deviceProp.regsPerMultiprocessor << std::endl;
        std::cout << "  Max threads per block: " << deviceProp.maxThreadsPerBlock << std::endl;
        std::cout << "  Max threads per SM: " << deviceProp.maxThreadsPerMultiProcessor << std::endl;
        std::cout << "  Maximum blocks per SM: " << cudaDevAttrMaxBlocksPerMultiprocessor << std::endl;
        std::cout << "  Max block dimensions: [ " << deviceProp.maxThreadsDim[0] << ", " << deviceProp.maxThreadsDim[1] << ", " << deviceProp.maxThreadsDim[2] << " ]" << std::endl;
        std::cout << "  Max grid dimensions:  [ " << deviceProp.maxGridSize[0] << ", " << deviceProp.maxGridSize[1] << ", " << deviceProp.maxGridSize[2] << " ]" << std::endl;
        std::cout << "  Total global memory: " << deviceProp.totalGlobalMem / (1024.0 * 1024.0) << " MB" << std::endl;
        std::cout << "  Memory bus width: " << deviceProp.memoryBusWidth << " bits" << std::endl;
        std::cout << "  Clock rate: " << deviceProp.clockRate / 1000.0 << " MHz" << std::endl;
        std::cout << "  Memory clock rate: " << deviceProp.memoryClockRate / 1000.0 << " MHz" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
    }

    return 0;
}